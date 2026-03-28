#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

// Test fixture for QuoteMeta tests
class RE2QuoteMetaTest_259 : public ::testing::Test {
protected:
};

// Normal operation: lowercase letters should not be escaped
TEST_F(RE2QuoteMetaTest_259, LowercaseLettersNotEscaped_259) {
    std::string result = RE2::QuoteMeta("abcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(result, "abcdefghijklmnopqrstuvwxyz");
}

// Normal operation: uppercase letters should not be escaped
TEST_F(RE2QuoteMetaTest_259, UppercaseLettersNotEscaped_259) {
    std::string result = RE2::QuoteMeta("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    EXPECT_EQ(result, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

// Normal operation: digits should not be escaped
TEST_F(RE2QuoteMetaTest_259, DigitsNotEscaped_259) {
    std::string result = RE2::QuoteMeta("0123456789");
    EXPECT_EQ(result, "0123456789");
}

// Normal operation: underscore should not be escaped
TEST_F(RE2QuoteMetaTest_259, UnderscoreNotEscaped_259) {
    std::string result = RE2::QuoteMeta("_");
    EXPECT_EQ(result, "_");
}

// Normal operation: mixed alphanumeric and underscore
TEST_F(RE2QuoteMetaTest_259, MixedAlphanumericUnderscore_259) {
    std::string result = RE2::QuoteMeta("Hello_World123");
    EXPECT_EQ(result, "Hello_World123");
}

// Special characters should be escaped
TEST_F(RE2QuoteMetaTest_259, SpecialCharactersEscaped_259) {
    std::string result = RE2::QuoteMeta(".");
    EXPECT_EQ(result, "\\.");
}

TEST_F(RE2QuoteMetaTest_259, AsteriskEscaped_259) {
    std::string result = RE2::QuoteMeta("*");
    EXPECT_EQ(result, "\\*");
}

TEST_F(RE2QuoteMetaTest_259, PlusEscaped_259) {
    std::string result = RE2::QuoteMeta("+");
    EXPECT_EQ(result, "\\+");
}

TEST_F(RE2QuoteMetaTest_259, QuestionMarkEscaped_259) {
    std::string result = RE2::QuoteMeta("?");
    EXPECT_EQ(result, "\\?");
}

TEST_F(RE2QuoteMetaTest_259, ParenthesesEscaped_259) {
    std::string result = RE2::QuoteMeta("()");
    EXPECT_EQ(result, "\\(\\)");
}

TEST_F(RE2QuoteMetaTest_259, BracketsEscaped_259) {
    std::string result = RE2::QuoteMeta("[]");
    EXPECT_EQ(result, "\\[\\]");
}

TEST_F(RE2QuoteMetaTest_259, BracesEscaped_259) {
    std::string result = RE2::QuoteMeta("{}");
    EXPECT_EQ(result, "\\{\\}");
}

TEST_F(RE2QuoteMetaTest_259, BackslashEscaped_259) {
    std::string result = RE2::QuoteMeta("\\");
    EXPECT_EQ(result, "\\\\");
}

TEST_F(RE2QuoteMetaTest_259, CaretEscaped_259) {
    std::string result = RE2::QuoteMeta("^");
    EXPECT_EQ(result, "\\^");
}

TEST_F(RE2QuoteMetaTest_259, DollarEscaped_259) {
    std::string result = RE2::QuoteMeta("$");
    EXPECT_EQ(result, "\\$");
}

TEST_F(RE2QuoteMetaTest_259, PipeEscaped_259) {
    std::string result = RE2::QuoteMeta("|");
    EXPECT_EQ(result, "\\|");
}

TEST_F(RE2QuoteMetaTest_259, DashEscaped_259) {
    std::string result = RE2::QuoteMeta("-");
    EXPECT_EQ(result, "\\-");
}

// Boundary: empty string
TEST_F(RE2QuoteMetaTest_259, EmptyString_259) {
    std::string result = RE2::QuoteMeta("");
    EXPECT_EQ(result, "");
}

// Boundary: single character
TEST_F(RE2QuoteMetaTest_259, SingleAlphaChar_259) {
    std::string result = RE2::QuoteMeta("a");
    EXPECT_EQ(result, "a");
}

TEST_F(RE2QuoteMetaTest_259, SingleSpecialChar_259) {
    std::string result = RE2::QuoteMeta("!");
    EXPECT_EQ(result, "\\!");
}

// Special handling: null character
TEST_F(RE2QuoteMetaTest_259, NullCharacter_259) {
    std::string input(1, '\0');
    std::string result = RE2::QuoteMeta(absl::string_view(input.data(), input.size()));
    EXPECT_EQ(result, "\\x00");
}

// Null character embedded in string
TEST_F(RE2QuoteMetaTest_259, EmbeddedNullCharacter_259) {
    std::string input = "a";
    input += '\0';
    input += "b";
    std::string result = RE2::QuoteMeta(absl::string_view(input.data(), input.size()));
    EXPECT_EQ(result, "a\\x00b");
}

// Multiple null characters
TEST_F(RE2QuoteMetaTest_259, MultipleNullCharacters_259) {
    std::string input(3, '\0');
    std::string result = RE2::QuoteMeta(absl::string_view(input.data(), input.size()));
    EXPECT_EQ(result, "\\x00\\x00\\x00");
}

// High-bit characters (byte value >= 128) should not be escaped
TEST_F(RE2QuoteMetaTest_259, HighBitCharNotEscaped_259) {
    std::string input(1, static_cast<char>(128));
    std::string result = RE2::QuoteMeta(absl::string_view(input.data(), input.size()));
    EXPECT_EQ(result, input);
}

TEST_F(RE2QuoteMetaTest_259, HighBitChar255NotEscaped_259) {
    std::string input(1, static_cast<char>(255));
    std::string result = RE2::QuoteMeta(absl::string_view(input.data(), input.size()));
    EXPECT_EQ(result, input);
}

TEST_F(RE2QuoteMetaTest_259, UTF8CharNotEscaped_259) {
    // UTF-8 encoded é (0xC3 0xA9)
    std::string input = "\xC3\xA9";
    std::string result = RE2::QuoteMeta(absl::string_view(input.data(), input.size()));
    EXPECT_EQ(result, input);
}

// Mixed content: letters, digits, special chars, high-bit chars
TEST_F(RE2QuoteMetaTest_259, MixedContent_259) {
    std::string result = RE2::QuoteMeta("a.b*c");
    EXPECT_EQ(result, "a\\.b\\*c");
}

// Space character should be escaped
TEST_F(RE2QuoteMetaTest_259, SpaceEscaped_259) {
    std::string result = RE2::QuoteMeta(" ");
    EXPECT_EQ(result, "\\ ");
}

// Tab character should be escaped
TEST_F(RE2QuoteMetaTest_259, TabEscaped_259) {
    std::string result = RE2::QuoteMeta("\t");
    EXPECT_EQ(result, "\\\t");
}

// Newline character should be escaped
TEST_F(RE2QuoteMetaTest_259, NewlineEscaped_259) {
    std::string result = RE2::QuoteMeta("\n");
    EXPECT_EQ(result, "\\\n");
}

// Complex regex pattern should be fully escaped
TEST_F(RE2QuoteMetaTest_259, ComplexRegexPattern_259) {
    std::string result = RE2::QuoteMeta("^foo.*bar$");
    EXPECT_EQ(result, "\\^foo\\.\\*bar\\$");
}

// Verify QuoteMeta output can be used as a literal match in RE2
TEST_F(RE2QuoteMetaTest_259, QuotedStringMatchesLiteral_259) {
    std::string special = "hello.world*foo+bar";
    std::string quoted = RE2::QuoteMeta(special);
    RE2 re(quoted);
    ASSERT_TRUE(re.ok());
    EXPECT_TRUE(RE2::FullMatch(special, re));
    EXPECT_FALSE(RE2::FullMatch("helloXworldYfooZbar", re));
}

// Test with at-sign, hash, etc.
TEST_F(RE2QuoteMetaTest_259, VariousSpecialChars_259) {
    std::string result = RE2::QuoteMeta("@#%&=~`");
    EXPECT_EQ(result, "\\@\\#\\%\\&\\=\\~\\`");
}

// Test with quotes
TEST_F(RE2QuoteMetaTest_259, QuotesEscaped_259) {
    std::string result = RE2::QuoteMeta("\"'");
    EXPECT_EQ(result, "\\\"\\'");
}

// Test with comma and semicolon
TEST_F(RE2QuoteMetaTest_259, CommaAndSemicolonEscaped_259) {
    std::string result = RE2::QuoteMeta(",;");
    EXPECT_EQ(result, "\\,\\;");
}

// Test with colon
TEST_F(RE2QuoteMetaTest_259, ColonEscaped_259) {
    std::string result = RE2::QuoteMeta(":");
    EXPECT_EQ(result, "\\:");
}

// Test boundary between escaped and non-escaped characters
TEST_F(RE2QuoteMetaTest_259, BoundaryChar_Slash_259) {
    // '/' is ASCII 47, not alphanumeric, not underscore, not high-bit => escaped
    std::string result = RE2::QuoteMeta("/");
    EXPECT_EQ(result, "\\/");
}

TEST_F(RE2QuoteMetaTest_259, BoundaryChar_AtSign_259) {
    // '@' is ASCII 64, between '9' (57) and 'A' (65) => escaped
    std::string result = RE2::QuoteMeta("@");
    EXPECT_EQ(result, "\\@");
}

TEST_F(RE2QuoteMetaTest_259, BoundaryChar_Backtick_259) {
    // '`' is ASCII 96, between 'Z' (90) and 'a' (97) => escaped
    std::string result = RE2::QuoteMeta("`");
    EXPECT_EQ(result, "\\`");
}

TEST_F(RE2QuoteMetaTest_259, BoundaryChar_DEL_259) {
    // DEL is ASCII 127, not alphanumeric, not underscore, bit 7 is 0 => escaped
    std::string input(1, '\x7f');
    std::string result = RE2::QuoteMeta(absl::string_view(input.data(), input.size()));
    EXPECT_EQ(result, std::string("\\") + input);
}

// Long string test
TEST_F(RE2QuoteMetaTest_259, LongString_259) {
    std::string input(1000, '.');
    std::string expected;
    for (int i = 0; i < 1000; ++i) {
        expected += "\\.";
    }
    std::string result = RE2::QuoteMeta(input);
    EXPECT_EQ(result, expected);
}

// Long alphanumeric string (no escaping needed)
TEST_F(RE2QuoteMetaTest_259, LongAlphanumericString_259) {
    std::string input(1000, 'a');
    std::string result = RE2::QuoteMeta(input);
    EXPECT_EQ(result, input);
}

}  // namespace re2
