// File: test_value_escape_minimum_characters_11.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"
#include "JsonBox/Grammar.h"

using namespace JsonBox;

namespace {

// Helper to call the target API without assuming static/non-static.
static std::string CallEscapeMinimum(const std::string& in) {
    Value v;
    return v.escapeMinimumCharacters(in);
}

} // namespace

// 1) Empty input -> empty output
TEST(ValueEscapeTest_11, EmptyString_ReturnsEmpty_11) {
    EXPECT_EQ("", CallEscapeMinimum(""));
}

// 2) No escapable characters -> unchanged
TEST(ValueEscapeTest_11, LeavesRegularCharsUnchanged_11) {
    const std::string input = "abcXYZ012_-+=., ";
    EXPECT_EQ(input, CallEscapeMinimum(input));
}

// 3) Escapes quotation mark
TEST(ValueEscapeTest_11, EscapesQuotationMark_11) {
    const std::string input(1, Strings::Std::QUOTATION_MARK); // "\""
    const std::string expected = Strings::Json::QUOTATION_MARK; // "\\\""
    EXPECT_EQ(expected, CallEscapeMinimum(input));
}

// 4) Escapes reverse solidus (backslash)
TEST(ValueEscapeTest_11, EscapesReverseSolidus_11) {
    const std::string input(1, Strings::Std::REVERSE_SOLIDUS); // "\\"
    const std::string expected = Strings::Json::REVERSE_SOLIDUS; // "\\\\"
    EXPECT_EQ(expected, CallEscapeMinimum(input));
}

// 5) Escapes explicit control characters: \b \f \n \r \t
TEST(ValueEscapeTest_11, EscapesExplicitControls_11) {
    std::string input;
    input.push_back(Strings::Std::BACKSPACE);
    input.push_back(Strings::Std::FORM_FEED);
    input.push_back(Strings::Std::LINE_FEED);
    input.push_back(Whitespace::CARRIAGE_RETURN); // or Strings::Std::CARRIAGE_RETURN if declared there
    input.push_back(Strings::Std::TAB);

    const std::string expected =
        Strings::Json::BACKSPACE +
        Strings::Json::FORM_FEED +
        Strings::Json::LINE_FEED +
        Strings::Json::CARRIAGE_RETURN +
        Strings::Json::TAB;

    EXPECT_EQ(expected, CallEscapeMinimum(input));
}

// 6) Unmapped control chars (0x00..0x1F excluding the explicit ones) -> unicode escape via Value::escapeToUnicode
TEST(ValueEscapeTest_11, EscapesUnmappedControlsToUnicode_11) {
    // Choose a few representative unmapped control characters.
    const char c1 = '\0';
    const char c2 = '\x01';
    const char c3 = '\x1f';

    std::string input;
    input.push_back(c1);
    input.push_back(c2);
    input.push_back(c3);

    const std::string expected =
        Value::escapeToUnicode(c1) +
        Value::escapeToUnicode(c2) +
        Value::escapeToUnicode(c3);

    EXPECT_EQ(expected, CallEscapeMinimum(input));
}

// 7) Mixed string: plain + escapable + plain (order preserved)
TEST(ValueEscapeTest_11, MixedString_MultipleEscapesAndPlain_11) {
    std::string input = "a";
    input.push_back(Strings::Std::QUOTATION_MARK);   // "
    input += "b";
    input.push_back(Strings::Std::REVERSE_SOLIDUS);  // \
    input += "c";
    input.push_back(Strings::Std::LINE_FEED);        // \n
    input += "d";

    const std::string expected =
        std::string("a") +
        Strings::Json::QUOTATION_MARK +
        "b" +
        Strings::Json::REVERSE_SOLIDUS +
        "c" +
        Strings::Json::LINE_FEED +
        "d";

    EXPECT_EQ(expected, CallEscapeMinimum(input));
}

// 8) Embedded NUL should be converted (string must be built with length)
TEST(ValueEscapeTest_11, EmbeddedNullHandled_11) {
    const std::string input = std::string("A\0B", 3);
    const std::string expected = std::string("A") + Value::escapeToUnicode('\0') + "B";
    EXPECT_EQ(expected, CallEscapeMinimum(input));
}

// 9) UTF-8 multibyte characters pass through unchanged
TEST(ValueEscapeTest_11, UTF8PassThrough_11) {
    const std::string input = u8"café ☕"; // multibyte UTF-8 (no ASCII control chars)
    EXPECT_EQ(input, CallEscapeMinimum(input));
}
