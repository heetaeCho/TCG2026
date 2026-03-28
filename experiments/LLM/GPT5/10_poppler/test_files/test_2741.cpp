// parseargs_isint_test_2741.cc
#include <gtest/gtest.h>

#include <cctype>
#include <clocale>

// Forward declaration of the function under test (defined in parseargs.cc)
bool isInt(const char *s);

class IsIntTest_2741 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure stable behavior for ctype classification (isdigit) across environments.
    // This avoids locale-specific surprises.
    std::setlocale(LC_CTYPE, "C");
  }
};

TEST_F(IsIntTest_2741, AcceptsZero_2741) {
  EXPECT_TRUE(isInt("0"));
}

TEST_F(IsIntTest_2741, AcceptsPositiveInteger_2741) {
  EXPECT_TRUE(isInt("12345"));
}

TEST_F(IsIntTest_2741, AcceptsNegativeInteger_2741) {
  EXPECT_TRUE(isInt("-987"));
}

TEST_F(IsIntTest_2741, AcceptsExplicitPlusSign_2741) {
  EXPECT_TRUE(isInt("+42"));
}

TEST_F(IsIntTest_2741, RejectsEmptyString_2741) {
  EXPECT_FALSE(isInt(""));
}

TEST_F(IsIntTest_2741, RejectsSignOnlyMinus_2741) {
  EXPECT_FALSE(isInt("-"));
}

TEST_F(IsIntTest_2741, RejectsSignOnlyPlus_2741) {
  EXPECT_FALSE(isInt("+"));
}

TEST_F(IsIntTest_2741, RejectsLeadingWhitespace_2741) {
  EXPECT_FALSE(isInt(" 123"));
}

TEST_F(IsIntTest_2741, RejectsTrailingWhitespace_2741) {
  EXPECT_FALSE(isInt("123 "));
}

TEST_F(IsIntTest_2741, RejectsEmbeddedWhitespace_2741) {
  EXPECT_FALSE(isInt("12 3"));
}

TEST_F(IsIntTest_2741, RejectsAlphabeticCharacters_2741) {
  EXPECT_FALSE(isInt("abc"));
  EXPECT_FALSE(isInt("123abc"));
  EXPECT_FALSE(isInt("abc123"));
}

TEST_F(IsIntTest_2741, RejectsDecimalPointAndFractional_2741) {
  EXPECT_FALSE(isInt("1.0"));
  EXPECT_FALSE(isInt("-3.14"));
  EXPECT_FALSE(isInt(".5"));
}

TEST_F(IsIntTest_2741, RejectsExponentNotation_2741) {
  EXPECT_FALSE(isInt("1e3"));
  EXPECT_FALSE(isInt("-2E10"));
}

TEST_F(IsIntTest_2741, RejectsHexLikePrefix_2741) {
  EXPECT_FALSE(isInt("0x10"));
  EXPECT_FALSE(isInt("-0XFF"));
}

TEST_F(IsIntTest_2741, RejectsDoubleSign_2741) {
  EXPECT_FALSE(isInt("--1"));
  EXPECT_FALSE(isInt("+-1"));
  EXPECT_FALSE(isInt("-+1"));
  EXPECT_FALSE(isInt("++1"));
}

TEST_F(IsIntTest_2741, RejectsNonDigitPunctuation_2741) {
  EXPECT_FALSE(isInt("123,456"));
  EXPECT_FALSE(isInt("1_000"));
  EXPECT_FALSE(isInt("42!"));
}

TEST_F(IsIntTest_2741, RejectsNewlineOrTab_2741) {
  EXPECT_FALSE(isInt("123\n"));
  EXPECT_FALSE(isInt("123\t"));
  EXPECT_FALSE(isInt("\n123"));
  EXPECT_FALSE(isInt("\t123"));
}

TEST_F(IsIntTest_2741, HandlesVeryLongDigitString_2741) {
  // Boundary-ish: very long sequence of digits should still be classified as integer text.
  std::string s(10000, '9');
  EXPECT_TRUE(isInt(s.c_str()));
}

TEST_F(IsIntTest_2741, HandlesVeryLongDigitStringWithSign_2741) {
  std::string s = "-";
  s.append(10000, '8');
  EXPECT_TRUE(isInt(s.c_str()));
}

TEST_F(IsIntTest_2741, RejectsNullTerminatedAtStartByEmbeddedNul_2741) {
  // Observable behavior: C-string ends at NUL, so it should behave like "123".
  const char buf[] = {'1', '2', '3', '\0', 'x', 'y', 'z', '\0'};
  EXPECT_TRUE(isInt(buf));
}

TEST_F(IsIntTest_2741, DISABLED_NullPointerIsUndefined_DoNotCall_2741) {
  // The interface does not specify behavior for nullptr, and the implementation
  // would dereference it. This test is intentionally disabled to avoid UB.
  // Enable only if the production contract changes to define nullptr behavior.
  EXPECT_FALSE(isInt(nullptr));
}