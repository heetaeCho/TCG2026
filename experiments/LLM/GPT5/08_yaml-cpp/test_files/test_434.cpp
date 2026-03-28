#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <limits>
#include <locale>
#include <string>

namespace YAML {
std::string FpToString(long double v, size_t precision);
}

// Custom numpunct facet to force a comma decimal separator in a locale.
// This lets us verify FpToString uses std::locale::classic() internally.
class CommaDecimalNumpunct : public std::numpunct<char> {
 protected:
  char do_decimal_point() const override { return ','; }
};

TEST(FpToStringTest_434, PrecisionZeroMatchesMaxDigits10_434) {
  const long double v = 1.0L / 3.0L;
  const size_t max_digits = std::numeric_limits<long double>::max_digits10;

  const std::string a = YAML::FpToString(v, 0);
  const std::string b = YAML::FpToString(v, max_digits);

  EXPECT_EQ(a, b);
  EXPECT_FALSE(a.empty());
}

TEST(FpToStringTest_434, ExplicitPrecisionProducesDeterministicSimpleInteger_434) {
  // With significant-digit formatting, 1.0 should remain "1" for small precisions.
  EXPECT_EQ(YAML::FpToString(1.0L, 1), "1");
  EXPECT_EQ(YAML::FpToString(1.0L, 2), "1");
  EXPECT_EQ(YAML::FpToString(0.0L, 1), "0");
}

TEST(FpToStringTest_434, ExplicitPrecisionAffectsSignificantDigits_434) {
  const long double v = 1.23456789L;

  const std::string p2 = YAML::FpToString(v, 2);
  const std::string p5 = YAML::FpToString(v, 5);

  EXPECT_FALSE(p2.empty());
  EXPECT_FALSE(p5.empty());
  // Higher precision should generally not be shorter than lower precision for typical values.
  EXPECT_LE(p2.size(), p5.size());
  // Both should start with '1' for this positive value.
  EXPECT_EQ(p2.front(), '1');
  EXPECT_EQ(p5.front(), '1');
}

TEST(FpToStringTest_434, NegativeValueKeepsLeadingMinus_434) {
  const std::string s = YAML::FpToString(-2.5L, 3);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.front(), '-');
}

TEST(FpToStringTest_434, VeryLargePrecisionDoesNotThrowAndReturnsNonEmpty_434) {
  // Boundary-ish: large precision value.
  EXPECT_NO_THROW({
    const std::string s = YAML::FpToString(1.0L / 7.0L, 100);
    EXPECT_FALSE(s.empty());
  });
}

TEST(FpToStringTest_434, SpecialValuesNaNAndInfinityReturnNonEmpty_434) {
  const long double inf = std::numeric_limits<long double>::infinity();
  const long double nan = std::numeric_limits<long double>::quiet_NaN();

  const std::string sinf = YAML::FpToString(inf, 0);
  const std::string snan = YAML::FpToString(nan, 0);

  EXPECT_FALSE(sinf.empty());
  EXPECT_FALSE(snan.empty());

  auto to_lower = [](std::string x) {
    std::transform(x.begin(), x.end(), x.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return x;
  };

  const std::string linf = to_lower(sinf);
  const std::string lnan = to_lower(snan);

  // Stream formatting varies ("inf", "infinity", "nan", "nan(ind)", etc.).
  EXPECT_NE(linf.find("inf"), std::string::npos);
  EXPECT_NE(lnan.find("nan"), std::string::npos);
}

TEST(FpToStringTest_434, UsesClassicLocaleRegardlessOfGlobalLocale_434) {
  // Install a global locale that uses comma as decimal separator.
  const std::locale original = std::locale();
  std::locale comma_locale(original, new CommaDecimalNumpunct());
  std::locale::global(comma_locale);

  // For 1.5, a comma-locale stream would typically print "1,5".
  // FpToString should still use '.' because it imbues classic locale internally.
  const std::string s = YAML::FpToString(1.5L, 2);

  // Restore global locale for test hygiene.
  std::locale::global(original);

  EXPECT_FALSE(s.empty());
  EXPECT_NE(s.find('.'), std::string::npos);
  EXPECT_EQ(s.find(','), std::string::npos);
}