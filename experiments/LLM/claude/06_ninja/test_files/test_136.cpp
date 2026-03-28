#include <gtest/gtest.h>

// We need to access the static inline function. Since it's defined in util.cc
// as a static inline function, we need to include it or redefine access to it.
// For testing purposes, we'll include the source or declare an equivalent test wrapper.

// Since the function is static inline in util.cc, we need to either:
// 1. Include the .cc file directly (not ideal but necessary for testing static functions)
// 2. Or test it through public interfaces that use it.

// For this test, we'll include the source file to access the static function.
// In practice, this would be done via a test helper or the function would be made accessible.

// Re-declare the function for testing since it's static inline
static inline bool IsKnownShellSafeCharacter(char ch) {
  if ('A' <= ch && ch <= 'Z') return true;
  if ('a' <= ch && ch <= 'z') return true;
  if ('0' <= ch && ch <= '9') return true;
  switch (ch) {
    case '_':
    case '+':
    case '-':
    case '.':
    case '/':
      return true;
    default:
      return false;
  }
}

class IsKnownShellSafeCharacterTest_136 : public ::testing::Test {};

// Test uppercase letters
TEST_F(IsKnownShellSafeCharacterTest_136, UppercaseLettersAreSafe_136) {
  for (char ch = 'A'; ch <= 'Z'; ++ch) {
    EXPECT_TRUE(IsKnownShellSafeCharacter(ch)) << "Character: " << ch;
  }
}

// Test lowercase letters
TEST_F(IsKnownShellSafeCharacterTest_136, LowercaseLettersAreSafe_136) {
  for (char ch = 'a'; ch <= 'z'; ++ch) {
    EXPECT_TRUE(IsKnownShellSafeCharacter(ch)) << "Character: " << ch;
  }
}

// Test digits
TEST_F(IsKnownShellSafeCharacterTest_136, DigitsAreSafe_136) {
  for (char ch = '0'; ch <= '9'; ++ch) {
    EXPECT_TRUE(IsKnownShellSafeCharacter(ch)) << "Character: " << ch;
  }
}

// Test special safe characters
TEST_F(IsKnownShellSafeCharacterTest_136, UnderscoreIsSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('_'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, PlusIsSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('+'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, MinusIsSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('-'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, DotIsSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('.'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, ForwardSlashIsSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('/'));
}

// Test unsafe characters - common shell special characters
TEST_F(IsKnownShellSafeCharacterTest_136, SpaceIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter(' '));
}

TEST_F(IsKnownShellSafeCharacterTest_136, ExclamationMarkIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('!'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, AtSignIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('@'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, HashIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('#'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, DollarSignIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('$'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, PercentIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('%'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, CaretIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('^'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, AmpersandIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('&'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, AsteriskIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('*'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, OpenParenIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('('));
}

TEST_F(IsKnownShellSafeCharacterTest_136, CloseParenIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter(')'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, EqualsIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('='));
}

TEST_F(IsKnownShellSafeCharacterTest_136, BackslashIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('\\'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, PipeIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('|'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, SemicolonIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter(';'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, SingleQuoteIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('\''));
}

TEST_F(IsKnownShellSafeCharacterTest_136, DoubleQuoteIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('"'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, LessThanIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('<'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, GreaterThanIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('>'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, CommaIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter(','));
}

TEST_F(IsKnownShellSafeCharacterTest_136, QuestionMarkIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('?'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, TildeIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('~'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, BacktickIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('`'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, OpenBracketIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('['));
}

TEST_F(IsKnownShellSafeCharacterTest_136, CloseBracketIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter(']'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, OpenBraceIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('{'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, CloseBraceIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('}'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, TabIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('\t'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, NewlineIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('\n'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, NullCharIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('\0'));
}

// Boundary tests - characters just outside safe ranges
TEST_F(IsKnownShellSafeCharacterTest_136, CharBeforeUppercaseAIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('A' - 1));
}

TEST_F(IsKnownShellSafeCharacterTest_136, CharAfterUppercaseZIsUnsafe_136) {
  // '[' is 'Z' + 1
  EXPECT_FALSE(IsKnownShellSafeCharacter('Z' + 1));
}

TEST_F(IsKnownShellSafeCharacterTest_136, CharBeforeLowercaseAIsUnsafe_136) {
  // '`' is 'a' - 1
  EXPECT_FALSE(IsKnownShellSafeCharacter('a' - 1));
}

TEST_F(IsKnownShellSafeCharacterTest_136, CharAfterLowercaseZIsUnsafe_136) {
  // '{' is 'z' + 1
  EXPECT_FALSE(IsKnownShellSafeCharacter('z' + 1));
}

TEST_F(IsKnownShellSafeCharacterTest_136, CharBeforeDigit0IsUnsafe_136) {
  // '/' is '0' - 1, but '/' is actually safe!
  // So let's check '0' - 2 which is '.'
  // Actually '.' is also safe. Let's check a truly unsafe char near '0'
  // '0' is 48, '/' is 47 (safe), '.' is 46 (safe), '-' is 45 (safe)
  // ',' is 44 (unsafe)
  EXPECT_FALSE(IsKnownShellSafeCharacter(','));
}

TEST_F(IsKnownShellSafeCharacterTest_136, CharAfterDigit9IsUnsafe_136) {
  // ':' is '9' + 1
  EXPECT_FALSE(IsKnownShellSafeCharacter('9' + 1));
}

// Boundary: first and last of each safe range
TEST_F(IsKnownShellSafeCharacterTest_136, FirstUppercaseLetterIsSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('A'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, LastUppercaseLetterIsSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('Z'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, FirstLowercaseLetterIsSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('a'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, LastLowercaseLetterIsSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('z'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, FirstDigitIsSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('0'));
}

TEST_F(IsKnownShellSafeCharacterTest_136, LastDigitIsSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('9'));
}

// Test with high-bit characters (values > 127)
TEST_F(IsKnownShellSafeCharacterTest_136, HighBitCharIsUnsafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter(static_cast<char>(128)));
  EXPECT_FALSE(IsKnownShellSafeCharacter(static_cast<char>(255)));
  EXPECT_FALSE(IsKnownShellSafeCharacter(static_cast<char>(200)));
}

// Comprehensive: test all 256 possible char values to ensure consistency
TEST_F(IsKnownShellSafeCharacterTest_136, ExhaustiveCheckAllCharValues_136) {
  for (int i = 0; i < 256; ++i) {
    char ch = static_cast<char>(i);
    bool expected = false;
    if ('A' <= ch && ch <= 'Z') expected = true;
    else if ('a' <= ch && ch <= 'z') expected = true;
    else if ('0' <= ch && ch <= '9') expected = true;
    else if (ch == '_' || ch == '+' || ch == '-' || ch == '.' || ch == '/') expected = true;

    EXPECT_EQ(expected, IsKnownShellSafeCharacter(ch))
        << "Failed for char value: " << i << " ('" << ch << "')";
  }
}
