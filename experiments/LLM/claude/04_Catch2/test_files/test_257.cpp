#include <gtest/gtest.h>
#include <string>

// Include the necessary headers
#include "catch2/catch_tostring.hpp"
#include "catch2/internal/catch_stringref.hpp"

// If the header doesn't directly expose the function, declare it
namespace Catch {
namespace Detail {
    std::string convertIntoString(Catch::StringRef string, bool escapeInvisibles);
}
}

class ConvertIntoStringTest_257 : public ::testing::Test {
protected:
    // Helper to call the function under test
    std::string convert(const std::string& input, bool escapeInvisibles) {
        Catch::StringRef ref(input);
        return Catch::Detail::convertIntoString(ref, escapeInvisibles);
    }
};

// === Normal operation tests ===

TEST_F(ConvertIntoStringTest_257, SimpleStringNoEscape_257) {
    std::string result = convert("hello", false);
    EXPECT_EQ(result, "\"hello\"");
}

TEST_F(ConvertIntoStringTest_257, SimpleStringWithEscapeEnabled_257) {
    std::string result = convert("hello", true);
    EXPECT_EQ(result, "\"hello\"");
}

TEST_F(ConvertIntoStringTest_257, EmptyStringNoEscape_257) {
    std::string result = convert("", false);
    EXPECT_EQ(result, "\"\"");
}

TEST_F(ConvertIntoStringTest_257, EmptyStringWithEscape_257) {
    std::string result = convert("", true);
    EXPECT_EQ(result, "\"\"");
}

// === Escape character tests ===

TEST_F(ConvertIntoStringTest_257, CarriageReturnEscaped_257) {
    std::string result = convert("a\rb", true);
    EXPECT_EQ(result, "\"a\\rb\"");
}

TEST_F(ConvertIntoStringTest_257, NewlineEscaped_257) {
    std::string result = convert("a\nb", true);
    EXPECT_EQ(result, "\"a\\nb\"");
}

TEST_F(ConvertIntoStringTest_257, TabEscaped_257) {
    std::string result = convert("a\tb", true);
    EXPECT_EQ(result, "\"a\\tb\"");
}

TEST_F(ConvertIntoStringTest_257, FormFeedEscaped_257) {
    std::string result = convert("a\fb", true);
    EXPECT_EQ(result, "\"a\\fb\"");
}

TEST_F(ConvertIntoStringTest_257, CarriageReturnNotEscapedWhenFlagFalse_257) {
    std::string result = convert("a\rb", false);
    EXPECT_EQ(result, "\"a\rb\"");
}

TEST_F(ConvertIntoStringTest_257, NewlineNotEscapedWhenFlagFalse_257) {
    std::string result = convert("a\nb", false);
    EXPECT_EQ(result, "\"a\nb\"");
}

TEST_F(ConvertIntoStringTest_257, TabNotEscapedWhenFlagFalse_257) {
    std::string result = convert("a\tb", false);
    EXPECT_EQ(result, "\"a\tb\"");
}

TEST_F(ConvertIntoStringTest_257, FormFeedNotEscapedWhenFlagFalse_257) {
    std::string result = convert("a\fb", false);
    EXPECT_EQ(result, "\"a\fb\"");
}

// === Multiple escape characters ===

TEST_F(ConvertIntoStringTest_257, MultipleEscapeCharacters_257) {
    std::string result = convert("\r\n\t\f", true);
    EXPECT_EQ(result, "\"\\r\\n\\t\\f\"");
}

TEST_F(ConvertIntoStringTest_257, MixedContentWithEscapes_257) {
    std::string result = convert("line1\nline2\ttab\rcarriage\fform", true);
    EXPECT_EQ(result, "\"line1\\nline2\\ttab\\rcarriage\\fform\"");
}

TEST_F(ConvertIntoStringTest_257, ConsecutiveEscapeCharacters_257) {
    std::string result = convert("\n\n\n", true);
    EXPECT_EQ(result, "\"\\n\\n\\n\"");
}

// === Boundary conditions ===

TEST_F(ConvertIntoStringTest_257, SingleCharacterNoEscape_257) {
    std::string result = convert("x", false);
    EXPECT_EQ(result, "\"x\"");
}

TEST_F(ConvertIntoStringTest_257, SingleCharacterWithEscape_257) {
    std::string result = convert("x", true);
    EXPECT_EQ(result, "\"x\"");
}

TEST_F(ConvertIntoStringTest_257, SingleNewlineEscaped_257) {
    std::string result = convert("\n", true);
    EXPECT_EQ(result, "\"\\n\"");
}

TEST_F(ConvertIntoStringTest_257, SingleCarriageReturnEscaped_257) {
    std::string result = convert("\r", true);
    EXPECT_EQ(result, "\"\\r\"");
}

TEST_F(ConvertIntoStringTest_257, SingleTabEscaped_257) {
    std::string result = convert("\t", true);
    EXPECT_EQ(result, "\"\\t\"");
}

TEST_F(ConvertIntoStringTest_257, SingleFormFeedEscaped_257) {
    std::string result = convert("\f", true);
    EXPECT_EQ(result, "\"\\f\"");
}

// === Strings containing quotes ===

TEST_F(ConvertIntoStringTest_257, StringWithQuotesNoEscape_257) {
    std::string result = convert("say \"hi\"", false);
    EXPECT_EQ(result, "\"say \"hi\"\"");
}

TEST_F(ConvertIntoStringTest_257, StringWithQuotesWithEscape_257) {
    std::string result = convert("say \"hi\"", true);
    EXPECT_EQ(result, "\"say \"hi\"\"");
}

// === Strings with backslashes ===

TEST_F(ConvertIntoStringTest_257, StringWithBackslashNoEscape_257) {
    std::string result = convert("a\\b", false);
    EXPECT_EQ(result, "\"a\\b\"");
}

TEST_F(ConvertIntoStringTest_257, StringWithBackslashWithEscape_257) {
    std::string result = convert("a\\b", true);
    EXPECT_EQ(result, "\"a\\b\"");
}

// === Result always starts and ends with quotes ===

TEST_F(ConvertIntoStringTest_257, ResultStartsWithQuoteNoEscape_257) {
    std::string result = convert("test", false);
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
}

TEST_F(ConvertIntoStringTest_257, ResultStartsWithQuoteWithEscape_257) {
    std::string result = convert("test", true);
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
}

// === Length verification for escaped strings ===

TEST_F(ConvertIntoStringTest_257, EscapedStringLengthIsCorrect_257) {
    // "a\nb" with escape -> "\"a\\nb\"" which is 6 chars: " a \\ n b "
    std::string result = convert("a\nb", true);
    // Expected: "a\nb" -> quotes + a + \n (as two chars) + b = 2 + 1 + 2 + 1 = 6
    EXPECT_EQ(result.size(), 6u);
}

TEST_F(ConvertIntoStringTest_257, NonEscapedStringLengthIsCorrect_257) {
    // "abc" without escape -> "\"abc\"" which is 5 chars
    std::string result = convert("abc", false);
    EXPECT_EQ(result.size(), 5u);
}

// === Only specified characters are escaped ===

TEST_F(ConvertIntoStringTest_257, OtherControlCharsNotEscaped_257) {
    // \a (bell) and \v (vertical tab) should NOT be escaped
    std::string input = "a\ab\vc";
    std::string result = convert(input, true);
    // These chars should pass through as-is, so length = 2 (quotes) + 5 (a, \a, b, \v, c) = 7
    EXPECT_EQ(result.size(), 7u);
}

// === Long string test ===

TEST_F(ConvertIntoStringTest_257, LongStringNoEscape_257) {
    std::string longStr(1000, 'a');
    std::string result = convert(longStr, false);
    EXPECT_EQ(result.size(), 1002u); // 1000 + 2 quotes
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
}

TEST_F(ConvertIntoStringTest_257, LongStringWithEscapeNoSpecialChars_257) {
    std::string longStr(1000, 'a');
    std::string result = convert(longStr, true);
    EXPECT_EQ(result.size(), 1002u);
}

TEST_F(ConvertIntoStringTest_257, LongStringAllNewlines_257) {
    std::string longStr(100, '\n');
    std::string result = convert(longStr, true);
    // Each \n becomes \n (2 chars), plus 2 quotes
    EXPECT_EQ(result.size(), 202u);
}
