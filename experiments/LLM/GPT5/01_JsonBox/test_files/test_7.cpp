// OutputFilter_overflow_test_7.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <limits>
#include "JsonBox/OutputFilter.h"

using Traits = std::char_traits<char>;
using IntType = Traits::int_type;

namespace {

// A simple inserter that writes the byte to the destination and returns the same int_type.
struct WritingInserter {
  int calls = 0;
  IntType last = Traits::eof();

  IntType operator()(std::streambuf& dest, IntType ch) {
    ++calls;
    last = ch;
    dest.sputc(Traits::to_char_type(ch));
    return ch; // propagate value
  }
};

// An inserter that returns eof() without writing (to simulate downstream failure).
struct EofInserter {
  int calls = 0;

  IntType operator()(std::streambuf&, IntType) {
    ++calls;
    return Traits::eof();
  }
};

// Testable subclass to observe sync() being invoked and to control its return.
template <typename Inserter>
struct TestableOutputFilter : public JsonBox::OutputFilter<Inserter> {
  using Base = JsonBox::OutputFilter<Inserter>;
  bool sync_called = false;
  int sync_return = 0; // value to return from sync()

  TestableOutputFilter(std::streambuf* dest, Inserter ins)
      : Base(dest, ins) {}

  int sync() override {
    sync_called = true;
    return sync_return;
  }
};

} // namespace

// Normal operation: inserter is called, writes to destination, and return value is propagated.
TEST(OutputFilterTest_7, Overflow_WritesUsingInserterAndReturnsValue_7) {
  std::stringbuf dest;
  WritingInserter ins;
  JsonBox::OutputFilter<WritingInserter> filter(&dest, ins);

  const IntType ch = Traits::to_int_type('A');
  const IntType ret = filter.overflow(ch);

  EXPECT_EQ(1, ins.calls);
  EXPECT_EQ(ch, ins.last);
  EXPECT_EQ("A", dest.str());
  EXPECT_EQ(ch, ret);
}

// EOF path: overflow(EOF) must call sync() and return its value; inserter is NOT called.
TEST(OutputFilterTest_7, Overflow_EofCallsSyncAndReturnsItsValue_7) {
  std::stringbuf dest;
  WritingInserter ins;
  TestableOutputFilter<WritingInserter> filter(&dest, ins);
  filter.sync_return = 123; // arbitrary non-eof integer

  const IntType ret = filter.overflow(Traits::eof());

  EXPECT_TRUE(filter.sync_called);
  EXPECT_EQ(0, ins.calls) << "Inserter must not be called for EOF.";
  EXPECT_EQ(123, ret);
}

// Null destination: non-EOF input with no destination should return eof() and not call inserter.
TEST(OutputFilterTest_7, Overflow_NullDestinationReturnsEof_7) {
  WritingInserter ins;
  JsonBox::OutputFilter<WritingInserter> filter(nullptr, ins);

  const IntType ch = Traits::to_int_type('Z');
  const IntType ret = filter.overflow(ch);

  EXPECT_EQ(0, ins.calls);
  EXPECT_EQ(Traits::eof(), ret);
}

// Boundary inputs (0 and UCHAR_MAX) are accepted and passed to inserter.
TEST(OutputFilterTest_7, Overflow_BoundaryValuesPassedToInserter_7) {
  std::stringbuf dest;
  WritingInserter ins;
  JsonBox::OutputFilter<WritingInserter> filter(&dest, ins);

  const unsigned char min_b = 0u;
  const unsigned char max_b = std::numeric_limits<unsigned char>::max();

  const IntType ret0 = filter.overflow(static_cast<IntType>(min_b));
  const IntType ret1 = filter.overflow(static_cast<IntType>(max_b));

  ASSERT_EQ(2, ins.calls);
  EXPECT_EQ(static_cast<IntType>(max_b), ins.last); // last call recorded

  // Verify two bytes written (as raw chars)
  const std::string s = dest.str();
  ASSERT_EQ(2u, s.size());
  EXPECT_EQ(static_cast<unsigned char>(s[0]), min_b);
  EXPECT_EQ(static_cast<unsigned char>(s[1]), max_b);

  EXPECT_EQ(static_cast<IntType>(min_b), ret0);
  EXPECT_EQ(static_cast<IntType>(max_b), ret1);
}

// Inserter failure: when inserter returns eof(), overflow must propagate eof().
TEST(OutputFilterTest_7, Overflow_PropagatesInserterEof_7) {
  std::stringbuf dest;
  EofInserter ins;
  JsonBox::OutputFilter<EofInserter> filter(&dest, ins);

  const IntType ch = 42; // any in-range value
  const IntType ret = filter.overflow(ch);

  EXPECT_EQ(1, ins.calls);
  EXPECT_EQ(Traits::eof(), ret);
}

// Argument range assertion: values beyond unsigned char max should trigger an assertion.
// This is a death test and only works when assertions are enabled (no NDEBUG).
#if GTEST_HAS_DEATH_TEST
TEST(OutputFilterTest_7, Overflow_OutOfRangeTriggersAssert_7) {
  std::stringbuf dest;
  WritingInserter ins;
  JsonBox::OutputFilter<WritingInserter> filter(&dest, ins);

  const int too_large = static_cast<int>(std::numeric_limits<unsigned char>::max()) + 1;
#if defined(NDEBUG)
  GTEST_SKIP() << "Assertions disabled; skipping death test.";
#else
  EXPECT_DEATH({ (void)filter.overflow(static_cast<IntType>(too_large)); }, "");
#endif
}
#endif
