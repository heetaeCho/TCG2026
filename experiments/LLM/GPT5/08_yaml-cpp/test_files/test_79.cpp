// TEST_ID: 79
// File: yaml-cpp/traits_test_79.cpp

#include <gtest/gtest.h>

#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>

#include "yaml-cpp/traits.h"

namespace {

class GlobalLocaleGuard_79 {
 public:
  explicit GlobalLocaleGuard_79(const std::locale& loc)
      : old_(std::locale::global(loc)) {}
  ~GlobalLocaleGuard_79() { std::locale::global(old_); }

  GlobalLocaleGuard_79(const GlobalLocaleGuard_79&) = delete;
  GlobalLocaleGuard_79& operator=(const GlobalLocaleGuard_79&) = delete;

 private:
  std::locale old_;
};

// Custom facet to make decimal point ',' so we can detect whether classic locale is used.
class CommaDecimalNumpunct_79 : public std::numpunct<char> {
 protected:
  char do_decimal_point() const override { return ','; }
};

// A type whose operator<< increments an external counter.
struct CountingStreamable_79 {
  int* counter{};
};

inline std::ostream& operator<<(std::ostream& os, const CountingStreamable_79& v) {
  if (v.counter) {
    ++(*v.counter);
  }
  os << "counted";
  return os;
}

// A type whose operator<< throws.
struct ThrowingStreamable_79 {};

inline std::ostream& operator<<(std::ostream&, const ThrowingStreamable_79&) {
  throw std::runtime_error("stream failed");
}

}  // namespace

// Normal operation: returns the streamed representation.
TEST(StreamableToStringTest_79, ReturnsStreamedText_79) {
  const int value = 12345;
  const std::string s = streamable_to_string<int, true>::impl(value);
  EXPECT_EQ(s, "12345");
}

// Boundary-ish: works for empty string keys (streaming string yields itself).
TEST(StreamableToStringTest_79, HandlesEmptyString_79) {
  const std::string empty;
  const std::string s = streamable_to_string<std::string, true>::impl(empty);
  EXPECT_TRUE(s.empty());
}

// Observable locale behavior: impl() imbues std::locale::classic() on its stringstream.
// We set a custom global locale that would format doubles with ',' and verify impl still uses '.'.
TEST(StreamableToStringTest_79, UsesClassicLocaleIndependentlyOfGlobalLocale_79) {
  const std::locale custom(std::locale::classic(), new CommaDecimalNumpunct_79());
  GlobalLocaleGuard_79 guard(custom);

  // Sanity: with the global custom locale, a default-constructed stringstream uses ','.
  {
    std::stringstream ss;
    ss << 1.5;
    EXPECT_NE(ss.str().find(','), std::string::npos);
  }

  // The impl should use classic locale and therefore produce '.'.
  const std::string s = streamable_to_string<double, true>::impl(1.5);
  EXPECT_NE(s.find('.'), std::string::npos);
  EXPECT_EQ(s.find(','), std::string::npos);
}

// Verification of external interaction: operator<< is invoked (observable via counter).
TEST(StreamableToStringTest_79, InvokesStreamInsertionOperator_79) {
  int calls = 0;
  CountingStreamable_79 key{&calls};

  const std::string s = streamable_to_string<CountingStreamable_79, true>::impl(key);

  EXPECT_EQ(calls, 1);
  EXPECT_EQ(s, "counted");
}

// Exceptional/error case: if streaming throws, impl should surface that (observable).
TEST(StreamableToStringTest_79, PropagatesExceptionFromStreamInsertion_79) {
  ThrowingStreamable_79 key;
  EXPECT_THROW((streamable_to_string<ThrowingStreamable_79, true>::impl(key)), std::runtime_error);
}
