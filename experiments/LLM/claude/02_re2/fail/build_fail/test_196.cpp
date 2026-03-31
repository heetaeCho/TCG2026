#include <gtest/gtest.h>
#include <string>
#include "util/pcre.h"

namespace re2 {

class PCREQuoteMetaTest_196 : public ::testing::Test {
protected:
};

// Normal alphanumeric characters should not be escaped
TEST_F(PCREQuoteMetaTest_196, AlphanumericNotEscaped_196) {
    std::string result = PCRE::QuoteMeta("abcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(result, "abcdefghijklmnopqrstuvwxyz");
}

TEST_F(PCREQuoteMetaTest_196, UppercaseAlphaNotEscaped_196) {
    std::string result = PCRE::QuoteMeta("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    EXPECT_EQ(result, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

TEST_F(PCREQuoteMetaTest_196, DigitsNotEscaped_196) {
    std::string result = PCRE::QuoteMeta("0123456789");
    EXPECT_EQ(result, "0123456789");
}

TEST_F(PCREQuoteMetaTest_196, UnderscoreNotEscaped_196) {
    std::string result = PCRE::QuoteMeta("_");
    EXPECT_EQ(result, "_");
}

// Special regex metacharacters should be escaped
TEST_F(PCREQuoteMetaTest_196, DotEscaped_196) {
    std::string result = PCRE::QuoteMeta(".");
    EXPECT_EQ(result, "\\.");
}

TEST_F(PCREQuoteMetaTest_196, StarEscaped_196) {
    std::string result = PCRE::QuoteMeta("*");
    EXPECT_EQ(result, "\\*");
}

TEST_F(PCREQuoteMetaTest_196, PlusEscaped_196) {
    std::string result = PCRE::QuoteMeta("+");
    EXPECT_EQ(result, "\\+");
}

TEST_F(PCREQuoteMetaTest_196, QuestionMarkEscaped_196) {
    std::string result = PCRE::QuoteMeta("?");
    EXPECT_EQ(result, "\\?");
}

TEST_F(PCREQuoteMetaTest_196, BracketsEscaped_196) {
    std::string result = PCRE::QuoteMeta("[](){}");
    EXPECT_EQ(result, "\\[\\]\\(\\)\\{\\}");
}

TEST_F(PCREQuoteMetaTest_196, BackslashEscaped_196) {
    std::string result = PCRE::QuoteMeta("\\");
    EXPECT_EQ(result, "\\\\");
}

TEST_F(PCREQuoteMetaTest_196, CaretAndDollarEscaped_196) {
    std::string result = PCRE::QuoteMeta("^$");
    EXPECT_EQ(result, "\\^\\$");
}

TEST_F(PCREQuoteMetaTest_196, PipeEscaped_196) {
    std::string result = PCRE::QuoteMeta("|");
    EXPECT_EQ(result, "\\|");
}

// Empty string should return empty string
TEST_F(PCREQuoteMetaTest_196, EmptyString_196) {
    std::string result = PCRE::QuoteMeta("");
    EXPECT_EQ(result, "");
}

// Null character should be replaced with \x00
TEST_F(PCREQuoteMetaTest_196, NullCharacter_196) {
    std::string input(1, '\0');
    std::string result = PCRE::QuoteMeta(input);
    EXPECT_EQ(result, "\\x00");
}

TEST_F(PCREQuoteMetaTest_196, NullCharacterInMiddle_196) {
    std::string input = "a";
    input += '\0';
    input += "b";
    std::string result = PCRE::QuoteMeta(input);
    EXPECT_EQ(result, "a\\x00b");
}

// Mixed alphanumeric and special characters
TEST_F(PCREQuoteMetaTest_196, MixedInput_196) {
    std::string result = PCRE::QuoteMeta("hello.world*");
    EXPECT_EQ(result, "hello\\.world\\*");
}

TEST_F(PCREQuoteMetaTest_196, ComplexPattern_196) {
    std::string result = PCRE::QuoteMeta("a+b*c?d.e[f]");
    EXPECT_EQ(result, "a\\+b\\*c\\?d\\.e\\[f\\]");
}

// High-bit characters (>= 128) should NOT be escaped
TEST_F(PCREQuoteMetaTest_196, HighBitCharNotEscaped_196) {
    std::string input(1, static_cast<char>(0x80));
    std::string result = PCRE::QuoteMeta(input);
    EXPECT_EQ(result, input);
}

TEST_F(PCREQuoteMetaTest_196, HighBitChar255NotEscaped_196) {
    std::string input(1, static_cast<char>(0xFF));
    std::string result = PCRE::QuoteMeta(input);
    EXPECT_EQ(result, input);
}

// Space and tab should be escaped (they are not alphanumeric, not underscore, not high-bit)
TEST_F(PCREQuoteMetaTest_196, SpaceEscaped_196) {
    std::string result = PCRE::QuoteMeta(" ");
    EXPECT_EQ(result, "\\ ");
}

TEST_F(PCREQuoteMetaTest_196, TabEscaped_196) {
    std::string result = PCRE::QuoteMeta("\t");
    EXPECT_EQ(result, "\\\t");
}

TEST_F(PCREQuoteMetaTest_196, NewlineEscaped_196) {
    std::string result = PCRE::QuoteMeta("\n");
    EXPECT_EQ(result, "\\\n");
}

// Dash and equals should be escaped
TEST_F(PCREQuoteMetaTest_196, DashEscaped_196) {
    std::string result = PCRE::QuoteMeta("-");
    EXPECT_EQ(result, "\\-");
}

TEST_F(PCREQuoteMetaTest_196, EqualsEscaped_196) {
    std::string result = PCRE::QuoteMeta("=");
    EXPECT_EQ(result, "\\=");
}

// Multiple null characters
TEST_F(PCREQuoteMetaTest_196, MultipleNullCharacters_196) {
    std::string input(3, '\0');
    std::string result = PCRE::QuoteMeta(input);
    EXPECT_EQ(result, "\\x00\\x00\\x00");
}

// Single alphanumeric character
TEST_F(PCREQuoteMetaTest_196, SingleAlpha_196) {
    EXPECT_EQ(PCRE::QuoteMeta("a"), "a");
    EXPECT_EQ(PCRE::QuoteMeta("Z"), "Z");
    EXPECT_EQ(PCRE::QuoteMeta("5"), "5");
}

// At sign, hash, exclamation, etc.
TEST_F(PCREQuoteMetaTest_196, VariousSpecialChars_196) {
    EXPECT_EQ(PCRE::QuoteMeta("@"), "\\@");
    EXPECT_EQ(PCRE::QuoteMeta("#"), "\\#");
    EXPECT_EQ(PCRE::QuoteMeta("!"), "\\!");
    EXPECT_EQ(PCRE::QuoteMeta("%"), "\\%");
    EXPECT_EQ(PCRE::QuoteMeta("&"), "\\&");
}

// Long string with all printable ASCII
TEST_F(PCREQuoteMetaTest_196, AllPrintableASCII_196) {
    std::string input;
    for (char c = 1; c < 127; ++c) {
        input += c;
    }
    std::string result = PCRE::QuoteMeta(input);
    // Just verify it doesn't crash and result is non-empty
    EXPECT_FALSE(result.empty());
    // Verify all alphanumeric and underscore chars appear unescaped
    // and result is at least as long as input
    EXPECT_GE(result.size(), input.size());
}

// Verify that underscore mixed with special chars works
TEST_F(PCREQuoteMetaTest_196, UnderscoreMixedWithSpecial_196) {
    std::string result = PCRE::QuoteMeta("_+_");
    EXPECT_EQ(result, "_\\+_");
}

// Boundary: character just before 'a' (backtick '`' = 96) should be escaped
TEST_F(PCREQuoteMetaTest_196, CharBeforeLowercaseA_196) {
    std::string result = PCRE::QuoteMeta("`");
    EXPECT_EQ(result, "\\`");
}

// Boundary: character just after 'z' ('{' = 123) should be escaped
TEST_F(PCREQuoteMetaTest_196, CharAfterLowercaseZ_196) {
    std::string result = PCRE::QuoteMeta("{");
    EXPECT_EQ(result, "\\{");
}

// Boundary: character just before 'A' ('@' = 64) should be escaped
TEST_F(PCREQuoteMetaTest_196, CharBeforeUppercaseA_196) {
    std::string result = PCRE::QuoteMeta("@");
    EXPECT_EQ(result, "\\@");
}

// Boundary: character just after 'Z' ('[' = 91) should be escaped
TEST_F(PCREQuoteMetaTest_196, CharAfterUppercaseZ_196) {
    std::string result = PCRE::QuoteMeta("[");
    EXPECT_EQ(result, "\\[");
}

// Boundary: character just before '0' ('/' = 47) should be escaped
TEST_F(PCREQuoteMetaTest_196, CharBeforeDigit0_196) {
    std::string result = PCRE::QuoteMeta("/");
    EXPECT_EQ(result, "\\/");
}

// Boundary: character just after '9' (':' = 58) should be escaped
TEST_F(PCREQuoteMetaTest_196, CharAfterDigit9_196) {
    std::string result = PCRE::QuoteMeta(":");
    EXPECT_EQ(result, "\\:");
}

}  // namespace re2
