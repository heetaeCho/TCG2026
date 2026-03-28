#include <gtest/gtest.h>
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class TagRegExTest_142 : public ::testing::Test {
protected:
    const RegEx& tag = Exp::Tag();
};

// Test that Tag() returns a consistent reference (singleton pattern)
TEST_F(TagRegExTest_142, ReturnsSameReference_142) {
    const RegEx& tag1 = Exp::Tag();
    const RegEx& tag2 = Exp::Tag();
    EXPECT_EQ(&tag1, &tag2);
}

// Test that basic word characters match (letters)
TEST_F(TagRegExTest_142, MatchesLowercaseLetters_142) {
    EXPECT_TRUE(tag.Matches('a'));
    EXPECT_TRUE(tag.Matches('m'));
    EXPECT_TRUE(tag.Matches('z'));
}

TEST_F(TagRegExTest_142, MatchesUppercaseLetters_142) {
    EXPECT_TRUE(tag.Matches('A'));
    EXPECT_TRUE(tag.Matches('M'));
    EXPECT_TRUE(tag.Matches('Z'));
}

TEST_F(TagRegExTest_142, MatchesDigits_142) {
    EXPECT_TRUE(tag.Matches('0'));
    EXPECT_TRUE(tag.Matches('5'));
    EXPECT_TRUE(tag.Matches('9'));
}

TEST_F(TagRegExTest_142, MatchesHyphen_142) {
    EXPECT_TRUE(tag.Matches('-'));
}

// Test special tag characters from the set "#;/?:@&=+$_.~*'()"
TEST_F(TagRegExTest_142, MatchesHashSign_142) {
    EXPECT_TRUE(tag.Matches('#'));
}

TEST_F(TagRegExTest_142, MatchesSemicolon_142) {
    EXPECT_TRUE(tag.Matches(';'));
}

TEST_F(TagRegExTest_142, MatchesSlash_142) {
    EXPECT_TRUE(tag.Matches('/'));
}

TEST_F(TagRegExTest_142, MatchesQuestionMark_142) {
    EXPECT_TRUE(tag.Matches('?'));
}

TEST_F(TagRegExTest_142, MatchesColon_142) {
    EXPECT_TRUE(tag.Matches(':'));
}

TEST_F(TagRegExTest_142, MatchesAtSign_142) {
    EXPECT_TRUE(tag.Matches('@'));
}

TEST_F(TagRegExTest_142, MatchesAmpersand_142) {
    EXPECT_TRUE(tag.Matches('&'));
}

TEST_F(TagRegExTest_142, MatchesEquals_142) {
    EXPECT_TRUE(tag.Matches('='));
}

TEST_F(TagRegExTest_142, MatchesPlus_142) {
    EXPECT_TRUE(tag.Matches('+'));
}

TEST_F(TagRegExTest_142, MatchesDollar_142) {
    EXPECT_TRUE(tag.Matches('$'));
}

TEST_F(TagRegExTest_142, MatchesUnderscore_142) {
    EXPECT_TRUE(tag.Matches('_'));
}

TEST_F(TagRegExTest_142, MatchesDot_142) {
    EXPECT_TRUE(tag.Matches('.'));
}

TEST_F(TagRegExTest_142, MatchesTilde_142) {
    EXPECT_TRUE(tag.Matches('~'));
}

TEST_F(TagRegExTest_142, MatchesAsterisk_142) {
    EXPECT_TRUE(tag.Matches('*'));
}

TEST_F(TagRegExTest_142, MatchesSingleQuote_142) {
    EXPECT_TRUE(tag.Matches('\''));
}

TEST_F(TagRegExTest_142, MatchesOpenParen_142) {
    EXPECT_TRUE(tag.Matches('('));
}

TEST_F(TagRegExTest_142, MatchesCloseParen_142) {
    EXPECT_TRUE(tag.Matches(')'));
}

// Test characters that should NOT match
TEST_F(TagRegExTest_142, DoesNotMatchSpace_142) {
    EXPECT_FALSE(tag.Matches(' '));
}

TEST_F(TagRegExTest_142, DoesNotMatchTab_142) {
    EXPECT_FALSE(tag.Matches('\t'));
}

TEST_F(TagRegExTest_142, DoesNotMatchNewline_142) {
    EXPECT_FALSE(tag.Matches('\n'));
}

TEST_F(TagRegExTest_142, DoesNotMatchDoubleQuote_142) {
    EXPECT_FALSE(tag.Matches('"'));
}

TEST_F(TagRegExTest_142, DoesNotMatchBackslash_142) {
    EXPECT_FALSE(tag.Matches('\\'));
}

TEST_F(TagRegExTest_142, DoesNotMatchOpenBracket_142) {
    EXPECT_FALSE(tag.Matches('['));
}

TEST_F(TagRegExTest_142, DoesNotMatchCloseBracket_142) {
    EXPECT_FALSE(tag.Matches(']'));
}

TEST_F(TagRegExTest_142, DoesNotMatchOpenBrace_142) {
    EXPECT_FALSE(tag.Matches('{'));
}

TEST_F(TagRegExTest_142, DoesNotMatchCloseBrace_142) {
    EXPECT_FALSE(tag.Matches('}'));
}

TEST_F(TagRegExTest_142, DoesNotMatchComma_142) {
    EXPECT_FALSE(tag.Matches(','));
}

TEST_F(TagRegExTest_142, DoesNotMatchExclamation_142) {
    EXPECT_FALSE(tag.Matches('!'));
}

TEST_F(TagRegExTest_142, DoesNotMatchPercent_142) {
    // '%' alone should not match; it needs to be followed by two hex digits
    EXPECT_FALSE(tag.Matches('%'));
}

TEST_F(TagRegExTest_142, DoesNotMatchCaretChar_142) {
    EXPECT_FALSE(tag.Matches('^'));
}

TEST_F(TagRegExTest_142, DoesNotMatchBacktick_142) {
    EXPECT_FALSE(tag.Matches('`'));
}

TEST_F(TagRegExTest_142, DoesNotMatchPipe_142) {
    EXPECT_FALSE(tag.Matches('|'));
}

TEST_F(TagRegExTest_142, DoesNotMatchLessThan_142) {
    EXPECT_FALSE(tag.Matches('<'));
}

TEST_F(TagRegExTest_142, DoesNotMatchGreaterThan_142) {
    EXPECT_FALSE(tag.Matches('>'));
}

// Test string matching for percent-encoded sequences
TEST_F(TagRegExTest_142, MatchesPercentEncodedHex_142) {
    // %XX where X is hex digit should match with length 3
    int result = tag.Match(std::string("%2F"));
    EXPECT_EQ(result, 3);
}

TEST_F(TagRegExTest_142, MatchesPercentEncodedLowerHex_142) {
    int result = tag.Match(std::string("%2f"));
    EXPECT_EQ(result, 3);
}

TEST_F(TagRegExTest_142, MatchesPercentEncodedAllDigits_142) {
    int result = tag.Match(std::string("%20"));
    EXPECT_EQ(result, 3);
}

TEST_F(TagRegExTest_142, MatchesPercentEncodedUpperHex_142) {
    int result = tag.Match(std::string("%AB"));
    EXPECT_EQ(result, 3);
}

// Test string matching for simple word characters
TEST_F(TagRegExTest_142, MatchesSingleWordCharString_142) {
    int result = tag.Match(std::string("a"));
    EXPECT_EQ(result, 1);
}

TEST_F(TagRegExTest_142, MatchesSingleDigitString_142) {
    int result = tag.Match(std::string("5"));
    EXPECT_EQ(result, 1);
}

TEST_F(TagRegExTest_142, MatchesSingleSpecialCharString_142) {
    int result = tag.Match(std::string("#"));
    EXPECT_EQ(result, 1);
}

// Test no match on empty string
TEST_F(TagRegExTest_142, DoesNotMatchEmptyString_142) {
    int result = tag.Match(std::string(""));
    EXPECT_LE(result, 0);
}

// Test no match on invalid characters
TEST_F(TagRegExTest_142, DoesNotMatchInvalidCharString_142) {
    int result = tag.Match(std::string(" "));
    EXPECT_LE(result, 0);
}

// Test that percent followed by non-hex doesn't match as 3 characters
TEST_F(TagRegExTest_142, PercentFollowedByNonHexDoesNotMatchAsThree_142) {
    int result = tag.Match(std::string("%GG"));
    // '%' alone isn't a valid tag char, and %GG isn't valid percent-encoding
    // This should not match as 3
    EXPECT_NE(result, 3);
}

TEST_F(TagRegExTest_142, PercentFollowedByOneHexDoesNotMatchAsThree_142) {
    int result = tag.Match(std::string("%2"));
    // Incomplete percent encoding
    EXPECT_NE(result, 3);
}

// Boundary: NUL character
TEST_F(TagRegExTest_142, DoesNotMatchNullChar_142) {
    EXPECT_FALSE(tag.Matches('\0'));
}

// Boundary: high ASCII value
TEST_F(TagRegExTest_142, DoesNotMatchHighAscii_142) {
    EXPECT_FALSE(tag.Matches('\x7F'));
}

}  // namespace
}  // namespace YAML
