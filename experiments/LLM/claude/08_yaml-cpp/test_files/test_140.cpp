#include <gtest/gtest.h>
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class AnchorEndTest_140 : public ::testing::Test {
protected:
    const RegEx& anchorEnd = Exp::AnchorEnd();
};

// Test that AnchorEnd returns the same instance every time (static)
TEST_F(AnchorEndTest_140, ReturnsSameInstance_140) {
    const RegEx& first = Exp::AnchorEnd();
    const RegEx& second = Exp::AnchorEnd();
    EXPECT_EQ(&first, &second);
}

// Test that '?' matches AnchorEnd
TEST_F(AnchorEndTest_140, MatchesQuestionMark_140) {
    EXPECT_TRUE(anchorEnd.Matches('?'));
}

// Test that ':' matches AnchorEnd
TEST_F(AnchorEndTest_140, MatchesColon_140) {
    EXPECT_TRUE(anchorEnd.Matches(':'));
}

// Test that ',' matches AnchorEnd
TEST_F(AnchorEndTest_140, MatchesComma_140) {
    EXPECT_TRUE(anchorEnd.Matches(','));
}

// Test that ']' matches AnchorEnd
TEST_F(AnchorEndTest_140, MatchesCloseBracket_140) {
    EXPECT_TRUE(anchorEnd.Matches(']'));
}

// Test that '}' matches AnchorEnd
TEST_F(AnchorEndTest_140, MatchesCloseBrace_140) {
    EXPECT_TRUE(anchorEnd.Matches('}'));
}

// Test that '%' matches AnchorEnd
TEST_F(AnchorEndTest_140, MatchesPercent_140) {
    EXPECT_TRUE(anchorEnd.Matches('%'));
}

// Test that '@' matches AnchorEnd
TEST_F(AnchorEndTest_140, MatchesAtSign_140) {
    EXPECT_TRUE(anchorEnd.Matches('@'));
}

// Test that '`' matches AnchorEnd
TEST_F(AnchorEndTest_140, MatchesBacktick_140) {
    EXPECT_TRUE(anchorEnd.Matches('`'));
}

// Test that space (blank) matches AnchorEnd
TEST_F(AnchorEndTest_140, MatchesSpace_140) {
    EXPECT_TRUE(anchorEnd.Matches(' '));
}

// Test that tab (blank) matches AnchorEnd
TEST_F(AnchorEndTest_140, MatchesTab_140) {
    EXPECT_TRUE(anchorEnd.Matches('\t'));
}

// Test that newline (break) matches AnchorEnd
TEST_F(AnchorEndTest_140, MatchesNewline_140) {
    EXPECT_TRUE(anchorEnd.Matches('\n'));
}

// Test that carriage return (break) matches AnchorEnd
TEST_F(AnchorEndTest_140, MatchesCarriageReturn_140) {
    EXPECT_TRUE(anchorEnd.Matches('\r'));
}

// Test that regular alphanumeric characters do NOT match AnchorEnd
TEST_F(AnchorEndTest_140, DoesNotMatchAlpha_140) {
    EXPECT_FALSE(anchorEnd.Matches('a'));
    EXPECT_FALSE(anchorEnd.Matches('z'));
    EXPECT_FALSE(anchorEnd.Matches('A'));
    EXPECT_FALSE(anchorEnd.Matches('Z'));
}

TEST_F(AnchorEndTest_140, DoesNotMatchDigit_140) {
    EXPECT_FALSE(anchorEnd.Matches('0'));
    EXPECT_FALSE(anchorEnd.Matches('9'));
}

// Test that hyphen does NOT match AnchorEnd (valid anchor char)
TEST_F(AnchorEndTest_140, DoesNotMatchHyphen_140) {
    EXPECT_FALSE(anchorEnd.Matches('-'));
}

// Test that underscore does NOT match AnchorEnd (valid anchor char)
TEST_F(AnchorEndTest_140, DoesNotMatchUnderscore_140) {
    EXPECT_FALSE(anchorEnd.Matches('_'));
}

// Test that dot does NOT match AnchorEnd
TEST_F(AnchorEndTest_140, DoesNotMatchDot_140) {
    EXPECT_FALSE(anchorEnd.Matches('.'));
}

// Test that '[' (open bracket) does NOT match AnchorEnd
TEST_F(AnchorEndTest_140, DoesNotMatchOpenBracket_140) {
    EXPECT_FALSE(anchorEnd.Matches('['));
}

// Test that '{' (open brace) does NOT match AnchorEnd
TEST_F(AnchorEndTest_140, DoesNotMatchOpenBrace_140) {
    EXPECT_FALSE(anchorEnd.Matches('{'));
}

// Test string matching - single char string that should match
TEST_F(AnchorEndTest_140, MatchesSingleCharString_140) {
    EXPECT_TRUE(anchorEnd.Matches(std::string("?")));
    EXPECT_TRUE(anchorEnd.Matches(std::string(",")));
    EXPECT_TRUE(anchorEnd.Matches(std::string(" ")));
}

// Test string matching - single char string that should NOT match
TEST_F(AnchorEndTest_140, DoesNotMatchAlphaString_140) {
    EXPECT_FALSE(anchorEnd.Matches(std::string("a")));
    EXPECT_FALSE(anchorEnd.Matches(std::string("x")));
}

// Test Match returns correct length for matching strings
TEST_F(AnchorEndTest_140, MatchReturnLengthForMatchingChar_140) {
    int result = anchorEnd.Match(std::string("?"));
    EXPECT_EQ(result, 1);
}

TEST_F(AnchorEndTest_140, MatchReturnLengthForSpace_140) {
    int result = anchorEnd.Match(std::string(" "));
    EXPECT_EQ(result, 1);
}

// Test Match returns -1 for non-matching strings
TEST_F(AnchorEndTest_140, MatchReturnNegativeForNonMatch_140) {
    int result = anchorEnd.Match(std::string("a"));
    EXPECT_EQ(result, -1);
}

// Test with empty string
TEST_F(AnchorEndTest_140, MatchReturnNegativeForEmptyString_140) {
    int result = anchorEnd.Match(std::string(""));
    EXPECT_EQ(result, -1);
}

// Test that various special YAML characters are recognized
TEST_F(AnchorEndTest_140, MatchesAllSpecialChars_140) {
    const std::string specialChars = "?:,]}%@`";
    for (char ch : specialChars) {
        EXPECT_TRUE(anchorEnd.Matches(ch)) << "Expected match for char: " << ch;
    }
}

// Test that null character does NOT match
TEST_F(AnchorEndTest_140, DoesNotMatchNullChar_140) {
    // Null might be treated specially but typically not a blank or break
    // This tests boundary behavior
    EXPECT_FALSE(anchorEnd.Matches('!'));
    EXPECT_FALSE(anchorEnd.Matches('#'));
    EXPECT_FALSE(anchorEnd.Matches('&'));
    EXPECT_FALSE(anchorEnd.Matches('*'));
}

// Test various non-matching punctuation
TEST_F(AnchorEndTest_140, DoesNotMatchOtherPunctuation_140) {
    EXPECT_FALSE(anchorEnd.Matches('/'));
    EXPECT_FALSE(anchorEnd.Matches('\\'));
    EXPECT_FALSE(anchorEnd.Matches('"'));
    EXPECT_FALSE(anchorEnd.Matches('\''));
    EXPECT_FALSE(anchorEnd.Matches('('));
    EXPECT_FALSE(anchorEnd.Matches(')'));
    EXPECT_FALSE(anchorEnd.Matches('+'));
    EXPECT_FALSE(anchorEnd.Matches('='));
}

}  // namespace
}  // namespace YAML
