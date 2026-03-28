// File: test_value_escape_all_characters_12.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"
#include "JsonBox/Grammar.h"

using namespace JsonBox;

class ValueEscapeAllCharactersTest_12 : public ::testing::Test {
protected:
    Value v; // We'll call the member overload as shown in the partial Value.cpp
};

TEST_F(ValueEscapeAllCharactersTest_12, EmptyString_ReturnsEmpty_12) {
    EXPECT_EQ("", v.escapeAllCharacters(""));
}

TEST_F(ValueEscapeAllCharactersTest_12, PassThrough_NormalAscii_12) {
    const std::string input = "abcXYZ123 +-=_:.";
    EXPECT_EQ(input, v.escapeAllCharacters(input));
}

TEST_F(ValueEscapeAllCharactersTest_12, Escape_QuotationMark_12) {
    EXPECT_EQ(Strings::Json::QUOTATION_MARK, v.escapeAllCharacters(std::string(1, Strings::Std::QUOTATION_MARK)));
}

TEST_F(ValueEscapeAllCharactersTest_12, Escape_ReverseSolidus_12) {
    EXPECT_EQ(Strings::Json::REVERSE_SOLIDUS, v.escapeAllCharacters(std::string(1, Strings::Std::REVERSE_SOLIDUS)));
}

TEST_F(ValueEscapeAllCharactersTest_12, Escape_Solidus_12) {
    EXPECT_EQ(Strings::Json::SOLIDUS, v.escapeAllCharacters(std::string(1, Strings::Std::SOLIDUS)));
}

TEST_F(ValueEscapeAllCharactersTest_12, Escape_Backspace_12) {
    EXPECT_EQ(Strings::Json::BACKSPACE, v.escapeAllCharacters(std::string(1, Strings::Std::BACKSPACE)));
}

TEST_F(ValueEscapeAllCharactersTest_12, Escape_FormFeed_12) {
    EXPECT_EQ(Strings::Json::FORM_FEED, v.escapeAllCharacters(std::string(1, Strings::Std::FORM_FEED)));
}

TEST_F(ValueEscapeAllCharactersTest_12, Escape_LineFeed_12) {
    EXPECT_EQ(Strings::Json::LINE_FEED, v.escapeAllCharacters(std::string(1, Strings::Std::LINE_FEED)));
}

TEST_F(ValueEscapeAllCharactersTest_12, Escape_CarriageReturn_12) {
    // Uses the JSON escape constant to validate observable behavior.
    const std::string input(1, '\r');
    EXPECT_EQ(Strings::Json::CARRIAGE_RETURN, v.escapeAllCharacters(input));
}

TEST_F(ValueEscapeAllCharactersTest_12, Escape_Tab_12) {
    EXPECT_EQ(Strings::Json::TAB, v.escapeAllCharacters(std::string(1, Strings::Std::TAB)));
}

TEST_F(ValueEscapeAllCharactersTest_12, ControlChar_LowBoundary_UnicodeEscape_12) {
    // 0x00 should be escaped using the public escapeToUnicode API for expected value
    const char c = '\x00';
    const std::string expected = Value::escapeToUnicode(c);
    EXPECT_EQ(expected, v.escapeAllCharacters(std::string(1, c)));
}

TEST_F(ValueEscapeAllCharactersTest_12, ControlChar_HighBoundary_UnicodeEscape_12) {
    // 0x1F should be escaped; 0x20 (space) should NOT be escaped.
    const char c1 = '\x1f';
    const char c2 = '\x20'; // space
    const std::string input = std::string(1, c1) + std::string(1, c2);
    const std::string expected = Value::escapeToUnicode(c1) + std::string(1, c2);
    EXPECT_EQ(expected, v.escapeAllCharacters(input));
}

TEST_F(ValueEscapeAllCharactersTest_12, MixedString_AllEscapesAndNormals_12) {
    // Build expected only with public constants / methods.
    const std::string input =
        std::string("a") +
        std::string(1, Strings::Std::QUOTATION_MARK) +       // "
        std::string(1, Strings::Std::LINE_FEED) +            // \n
        std::string(1, Strings::Std::SOLIDUS) +              // /
        std::string(1, Strings::Std::TAB) +                  // \t
        std::string(1, Strings::Std::REVERSE_SOLIDUS) +      // \
        std::string(1, Strings::Std::BACKSPACE) +            // \b
        std::string(1, '\r') +                                // \r (carriage return)
        std::string(1, Strings::Std::FORM_FEED) +            // \f
        std::string("z");

    const std::string expected =
        std::string("a") +
        Strings::Json::QUOTATION_MARK +
        Strings::Json::LINE_FEED +
        Strings::Json::SOLIDUS +
        Strings::Json::TAB +
        Strings::Json::REVERSE_SOLIDUS +
        Strings::Json::BACKSPACE +
        Strings::Json::CARRIAGE_RETURN +
        Strings::Json::FORM_FEED +
        std::string("z");

    EXPECT_EQ(expected, v.escapeAllCharacters(input));
}

TEST_F(ValueEscapeAllCharactersTest_12, UTF8_NonAscii_PassedThrough_12) {
    // No JSON special/control characters; should pass through as-is.
    const std::string input = u8"한글 😀";
    EXPECT_EQ(input, v.escapeAllCharacters(input));
}

TEST_F(ValueEscapeAllCharactersTest_12, LongString_NoSpecials_Unchanged_12) {
    const std::string input(1024, 'A'); // 1024 'A's
    EXPECT_EQ(input, v.escapeAllCharacters(input));
}
