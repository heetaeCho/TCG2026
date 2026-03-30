// File: gstrtod_test.cc
// Unit tests for ./TestProjects/poppler/goo/gstrtod.cc
//
// These tests treat gstrtod as a black box and validate only observable behavior.

#include <gtest/gtest.h>

#include <cerrno>
#include <clocale>
#include <cmath>
#include <cstring>
#include <limits>
#include <string>

extern "C" double gstrtod(const char* nptr, char** endptr);

namespace {

class ScopedNumericLocale {
 public:
  ScopedNumericLocale() {
    const char* cur = std::setlocale(LC_NUMERIC, nullptr);
    saved_ = cur ? cur : "C";
  }

  ~ScopedNumericLocale() { std::setlocale(LC_NUMERIC, saved_.c_str()); }

  // Tries to set LC_NUMERIC to a locale name. Returns true if setlocale succeeded.
  bool Set(const char* locale_name) {
    return std::setlocale(LC_NUMERIC, locale_name) != nullptr;
  }

  std::string CurrentDecimalPoint() const {
    lconv* lc = localeconv();
    return (lc && lc->decimal_point) ? std::string(lc->decimal_point) : std::string(".");
  }

 private:
  std::string saved_;
};

static const char* FindNonDotDecimalLocale() {
  // Try a list of common locales that typically use a comma decimal separator.
  static const char* kCandidates[] = {
      "de_DE.UTF-8", "de_DE.utf8", "de_DE",
      "fr_FR.UTF-8", "fr_FR.utf8", "fr_FR",
      "it_IT.UTF-8", "it_IT.utf8", "it_IT",
      "es_ES.UTF-8", "es_ES.utf8", "es_ES",
      "pt_BR.UTF-8", "pt_BR.utf8", "pt_BR",
      "ru_RU.UTF-8", "ru_RU.utf8", "ru_RU",
      "nl_NL.UTF-8", "nl_NL.utf8", "nl_NL",
      "sv_SE.UTF-8", "sv_SE.utf8", "sv_SE",
      // Some minimal/container environments may only have "C" and "POSIX".
      // We'll skip if we can't find a comma-decimal locale.
  };

  ScopedNumericLocale loc;
  for (const char* cand : kCandidates) {
    if (!loc.Set(cand)) continue;
    if (loc.CurrentDecimalPoint() != ".") return cand;
  }
  return nullptr;
}

static void ExpectEndptrAtOffset(const char* base, char* endptr, size_t off) {
  ASSERT_NE(base, nullptr);
  ASSERT_NE(endptr, nullptr);
  EXPECT_EQ(base + off, endptr);
}

class GStrtodTest_31 : public ::testing::Test {};

}  // namespace

TEST_F(GStrtodTest_31, ParsesSimpleDecimalAndSetsEndptr_31) {
  ScopedNumericLocale loc;
  ASSERT_TRUE(loc.Set("C") || loc.Set("POSIX"));

  const char* s = "12.34abc";
  char* end = nullptr;

  errno = 0;
  double v = gstrtod(s, &end);

  EXPECT_NEAR(v, 12.34, 1e-12);
  ASSERT_NE(end, nullptr);
  EXPECT_EQ(*end, 'a');
  ExpectEndptrAtOffset(s, end, std::strlen("12.34"));
  EXPECT_EQ(errno, 0);
}

TEST_F(GStrtodTest_31, SkipsLeadingWhitespaceAndParsesSignAndExponent_31) {
  ScopedNumericLocale loc;
  ASSERT_TRUE(loc.Set("C") || loc.Set("POSIX"));

  const char* s = " \t\n-0.25e2XYZ";
  char* end = nullptr;

  errno = 0;
  double v = gstrtod(s, &end);

  EXPECT_NEAR(v, -25.0, 1e-12);
  ASSERT_NE(end, nullptr);
  EXPECT_EQ(*end, 'X');
  // Parsed portion should end right before 'X' in the original string.
  EXPECT_EQ(std::string(s, static_cast<size_t>(end - s)), " \t\n-0.25e2");
  EXPECT_EQ(errno, 0);
}

TEST_F(GStrtodTest_31, NoConversionReturnsZeroAndEndptrAtStart_31) {
  ScopedNumericLocale loc;
  ASSERT_TRUE(loc.Set("C") || loc.Set("POSIX"));

  const char* s = "not_a_number";
  char* end = reinterpret_cast<char*>(0x1);  // ensure it gets overwritten

  errno = 0;
  double v = gstrtod(s, &end);

  EXPECT_EQ(v, 0.0);
  ASSERT_NE(end, nullptr);
  EXPECT_EQ(end, s);
  EXPECT_EQ(errno, 0);
}

TEST_F(GStrtodTest_31, NullEndptrIsAllowed_31) {
  ScopedNumericLocale loc;
  ASSERT_TRUE(loc.Set("C") || loc.Set("POSIX"));

  const char* s = "3.14159";
  errno = 0;

  double v = gstrtod(s, nullptr);

  EXPECT_NEAR(v, 3.14159, 1e-12);
  EXPECT_EQ(errno, 0);
}

TEST_F(GStrtodTest_31, OverflowSetsErrnoErangeAndConsumesExponent_31) {
  ScopedNumericLocale loc;
  ASSERT_TRUE(loc.Set("C") || loc.Set("POSIX"));

  const char* s = "1e309";
  char* end = nullptr;

  errno = 0;
  double v = gstrtod(s, &end);

  // strtod overflow typically returns HUGE_VAL (+/-) and sets ERANGE.
  EXPECT_TRUE(std::isinf(v) || v == std::numeric_limits<double>::infinity() ||
              v == std::numeric_limits<double>::max());
  EXPECT_EQ(errno, ERANGE);

  ASSERT_NE(end, nullptr);
  ExpectEndptrAtOffset(s, end, std::strlen("1e309"));
}

TEST_F(GStrtodTest_31, UnderflowCanSetErrnoErangeForTinyValues_31) {
  ScopedNumericLocale loc;
  ASSERT_TRUE(loc.Set("C") || loc.Set("POSIX"));

  const char* s = "1e-324";  // smaller than DBL_MIN subnormal threshold in many libs
  char* end = nullptr;

  errno = 0;
  double v = gstrtod(s, &end);

  // Underflow behavior varies by libc; check only observable, portable aspects:
  // - It should parse something (endptr moves past digits/exponent).
  // - Value should be non-negative and very small (often 0).
  ASSERT_NE(end, nullptr);
  ExpectEndptrAtOffset(s, end, std::strlen("1e-324"));
  EXPECT_GE(v, 0.0);

  // errno may be 0 or ERANGE depending on implementation; accept both.
  EXPECT_TRUE(errno == 0 || errno == ERANGE);
}

TEST_F(GStrtodTest_31, InCommaDecimalLocaleAcceptsDotDecimalInput_31) {
  const char* locale_name = FindNonDotDecimalLocale();
  if (!locale_name) {
    GTEST_SKIP() << "No non-dot decimal locale available on this system.";
  }

  ScopedNumericLocale loc;
  ASSERT_TRUE(loc.Set(locale_name));
  ASSERT_NE(loc.CurrentDecimalPoint(), ".");

  const char* s = "1.25Z";
  char* end = nullptr;

  errno = 0;
  double v = gstrtod(s, &end);

  EXPECT_NEAR(v, 1.25, 1e-12);
  ASSERT_NE(end, nullptr);
  EXPECT_EQ(*end, 'Z');
  ExpectEndptrAtOffset(s, end, std::strlen("1.25"));
  EXPECT_EQ(errno, 0);
}

TEST_F(GStrtodTest_31, InCommaDecimalLocaleAcceptsLocaleDecimalInput_31) {
  const char* locale_name = FindNonDotDecimalLocale();
  if (!locale_name) {
    GTEST_SKIP() << "No non-dot decimal locale available on this system.";
  }

  ScopedNumericLocale loc;
  ASSERT_TRUE(loc.Set(locale_name));
  const std::string dp = loc.CurrentDecimalPoint();
  ASSERT_NE(dp, ".");

  // Build "2<dp>5Q"
  std::string s = "2" + dp + "5Q";
  char* end = nullptr;

  errno = 0;
  double v = gstrtod(s.c_str(), &end);

  EXPECT_NEAR(v, 2.5, 1e-12);
  ASSERT_NE(end, nullptr);
  EXPECT_EQ(*end, 'Q');
  ExpectEndptrAtOffset(s.c_str(), end, s.size() - 1);
  EXPECT_EQ(errno, 0);
}