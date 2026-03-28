// -----------------------------------------------------------------------------
// TEST_ID: 677
// File: test_iptcdatum_count_677.cpp
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <cstddef>
#include <limits>
#include <string>

// Exiv2 headers (expected available in the real codebase)
#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

// A small test double for Exiv2::Value that lets us control the observable
// behavior of Value::count() without assuming anything about Iptcdatum internals.
class CountingValue final : public Exiv2::Value {
 public:
  explicit CountingValue(std::size_t c)
      : Exiv2::Value(Exiv2::asciiString), count_(c) {}

  const std::size_t count() override { return count_; }

  void setCount(std::size_t c) { count_ = c; }

 private:
  std::size_t count_;
};

// Helper to construct an IptcKey in a way that is consistent with typical Exiv2 usage.
// This relies only on public interface and does not assume internal behavior.
// If your Exiv2 build uses a different key-string format, adjust the literal accordingly.
inline Exiv2::IptcKey MakeAnyIptcKey() {
  return Exiv2::IptcKey("Iptc.Application2.ObjectName");
}

class IptcdatumTest_677 : public ::testing::Test {
 protected:
  Exiv2::IptcKey key_ = MakeAnyIptcKey();
};

}  // namespace

// Normal / boundary: nullptr value should yield count() == 0 (observable behavior).
TEST_F(IptcdatumTest_677, CountReturnsZeroWhenConstructedWithNullValue_677) {
  Exiv2::Iptcdatum datum(key_, nullptr);
  EXPECT_EQ(datum.count(), 0u);
}

// Normal: when constructed with a Value, count() should reflect the Value's count().
TEST_F(IptcdatumTest_677, CountReflectsProvidedValueCount_677) {
  CountingValue v(3);
  Exiv2::Iptcdatum datum(key_, &v);

  EXPECT_EQ(datum.count(), 3u);
}

// Boundary: a zero-count value should be handled.
TEST_F(IptcdatumTest_677, CountCanBeZeroWhenValueProvided_677) {
  CountingValue v(0);
  Exiv2::Iptcdatum datum(key_, &v);

  EXPECT_EQ(datum.count(), 0u);
}

// Boundary: very large count values should be returned intact (no truncation observable).
TEST_F(IptcdatumTest_677, CountSupportsLargeValues_677) {
  const std::size_t big = (std::numeric_limits<std::size_t>::max)() / 2;
  CountingValue v(big);
  Exiv2::Iptcdatum datum(key_, &v);

  EXPECT_EQ(datum.count(), big);
}

// Normal: setValue(nullptr) should make count() observable as zero.
TEST_F(IptcdatumTest_677, SetValueNullMakesCountZero_677) {
  CountingValue v(7);
  Exiv2::Iptcdatum datum(key_, &v);
  ASSERT_EQ(datum.count(), 7u);

  datum.setValue(nullptr);
  EXPECT_EQ(datum.count(), 0u);
}

// Normal: setValue(non-null) should change the observable count().
TEST_F(IptcdatumTest_677, SetValueReplacesCountObservable_677) {
  CountingValue v1(2);
  CountingValue v2(9);

  Exiv2::Iptcdatum datum(key_, &v1);
  ASSERT_EQ(datum.count(), 2u);

  datum.setValue(&v2);
  EXPECT_EQ(datum.count(), 9u);
}

// Normal: copy construction should preserve observable count() behavior.
TEST_F(IptcdatumTest_677, CopyConstructionPreservesCount_677) {
  CountingValue v(5);
  Exiv2::Iptcdatum original(key_, &v);
  ASSERT_EQ(original.count(), 5u);

  Exiv2::Iptcdatum copy(original);
  EXPECT_EQ(copy.count(), 5u);
}

// Normal: copy assignment should preserve observable count() behavior.
TEST_F(IptcdatumTest_677, CopyAssignmentPreservesCount_677) {
  CountingValue v1(4);
  CountingValue v2(1);

  Exiv2::Iptcdatum a(key_, &v1);
  Exiv2::Iptcdatum b(key_, &v2);

  ASSERT_EQ(a.count(), 4u);
  ASSERT_EQ(b.count(), 1u);

  b = a;
  EXPECT_EQ(b.count(), 4u);
}