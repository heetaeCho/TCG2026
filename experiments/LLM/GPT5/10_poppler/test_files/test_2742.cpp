// isfp_test_2742.cc
//
// Unit tests for isFP() in ./TestProjects/poppler/utils/parseargs.cc
//
// Constraints honored:
// - Treat implementation as black box: only assert on observable return value.
// - No private state access.
// - Boundary + error cases covered.
//
// Note: isFP() is a free function; use TEST (not TEST_F).

#include <gtest/gtest.h>

extern bool isFP(const char *s);

namespace {

TEST(IsFPTest_2742, AcceptsSimpleIntegers_2742) {
  EXPECT_TRUE(isFP("0"));
  EXPECT_TRUE(isFP("7"));
  EXPECT_TRUE(isFP("123456"));
}

TEST(IsFPTest_2742, AcceptsLeadingSign_2742) {
  EXPECT_TRUE(isFP("+0"));
  EXPECT_TRUE(isFP("-0"));
  EXPECT_TRUE(isFP("+42"));
  EXPECT_TRUE(isFP("-42"));
}

TEST(IsFPTest_2742, AcceptsDecimalPointForms_2742) {
  // With fractional part
  EXPECT_TRUE(isFP("0.0"));
  EXPECT_TRUE(isFP("3.14159"));
  EXPECT_TRUE(isFP("-2.5"));
  EXPECT_TRUE(isFP("+10.25"));

  // Trailing dot is permitted (digits exist overall)
  EXPECT_TRUE(isFP("1."));
  EXPECT_TRUE(isFP("-1."));
  EXPECT_TRUE(isFP("+1."));

  // Leading dot without any digit is not permitted by this interface behavior
  EXPECT_FALSE(isFP(".1"));
  EXPECT_FALSE(isFP("-.1"));
  EXPECT_FALSE(isFP("+.1"));

  // Bare dot is not a number
  EXPECT_FALSE(isFP("."));
  EXPECT_FALSE(isFP("-."));
  EXPECT_FALSE(isFP("+."));
}

TEST(IsFPTest_2742, AcceptsExponentNotation_2742) {
  EXPECT_TRUE(isFP("1e0"));
  EXPECT_TRUE(isFP("1E0"));
  EXPECT_TRUE(isFP("12e34"));
  EXPECT_TRUE(isFP("12E34"));
  EXPECT_TRUE(isFP("1.0e10"));
  EXPECT_TRUE(isFP("1.e10"));

  // Exponent sign
  EXPECT_TRUE(isFP("1e+10"));
  EXPECT_TRUE(isFP("1e-10"));
  EXPECT_TRUE(isFP("-1e+10"));
  EXPECT_TRUE(isFP("+1E-10"));
}

TEST(IsFPTest_2742, RejectsMissingDigitsEverywhere_2742) {
  EXPECT_FALSE(isFP(""));    // empty
  EXPECT_FALSE(isFP("+"));   // sign only
  EXPECT_FALSE(isFP("-"));   // sign only
}

TEST(IsFPTest_2742, RejectsExponentWithoutDigits_2742) {
  // 'e' present but no exponent digits -> must be false
  EXPECT_FALSE(isFP("1e"));
  EXPECT_FALSE(isFP("1E"));
  EXPECT_FALSE(isFP("1e+"));
  EXPECT_FALSE(isFP("1e-"));

  // Digits required immediately after optional exponent sign
  EXPECT_FALSE(isFP("1e+X"));
  EXPECT_FALSE(isFP("1e-X"));
}

TEST(IsFPTest_2742, RejectsNonNumericTrailingCharacters_2742) {
  EXPECT_FALSE(isFP("1a"));
  EXPECT_FALSE(isFP("1.0f"));
  EXPECT_FALSE(isFP("1e10x"));
  EXPECT_FALSE(isFP("0x10"));
  EXPECT_FALSE(isFP("NaN"));
  EXPECT_FALSE(isFP("inf"));
  EXPECT_FALSE(isFP("Infinity"));
}

TEST(IsFPTest_2742, RejectsEmbeddedWhitespace_2742) {
  // No leading/trailing/embedded spaces allowed (must consume entire string)
  EXPECT_FALSE(isFP(" 1"));
  EXPECT_FALSE(isFP("1 "));
  EXPECT_FALSE(isFP("1 2"));
  EXPECT_FALSE(isFP("\t1"));
  EXPECT_FALSE(isFP("1\n"));
}

TEST(IsFPTest_2742, RejectsSecondDecimalPointOrMalformedPunctuation_2742) {
  EXPECT_FALSE(isFP("1..0"));
  EXPECT_FALSE(isFP("1.0.0"));
  EXPECT_FALSE(isFP(".."));
  EXPECT_FALSE(isFP("1e1.0"));
  EXPECT_FALSE(isFP("1.e1.0"));
}

TEST(IsFPTest_2742, BoundaryLargeDigitSequences_2742) {
  // Long but valid numeric strings should still be accepted.
  // (No claim about range/overflow; this parser is syntactic.)
  const std::string many_digits(1024, '9');
  EXPECT_TRUE(isFP(many_digits.c_str()));

  std::string with_decimal = many_digits + "." + many_digits;
  EXPECT_TRUE(isFP(with_decimal.c_str()));

  std::string with_exp = many_digits + "e" + many_digits;
  EXPECT_TRUE(isFP(with_exp.c_str()));
}

TEST(IsFPTest_2742, BoundaryExponentWithLeadingZeros_2742) {
  EXPECT_TRUE(isFP("1e000"));
  EXPECT_TRUE(isFP("1e-000"));
  EXPECT_TRUE(isFP("1e+000"));
}

} // namespace