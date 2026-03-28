// File: SolidusEscaperTest_70.cpp
#include <gtest/gtest.h>
#include <streambuf>
#include <string>
#include <sstream>

#include "JsonBox/SolidusEscaper.h"
#include "JsonBox/Grammar.h"

// Small helper to feed one character and return operator()'s return value.
static std::streambuf::int_type Feed(JsonBox::SolidusEscaper& esc,
                                     std::streambuf& dest,
                                     char ch) {
    return esc(dest, std::char_traits<char>::to_int_type(ch));
}

// NOTE: Using std::stringbuf so we only assert on what the class writes out
// via the public streambuf interface (sputc/sputn). No peeking at internals.

class SolidusEscaperTest_70 : public ::testing::Test {
protected:
    std::string getStr() const { return sb.str(); }
    std::stringbuf sb;
};

// Outside of a string, '/' must NOT be escaped.
TEST_F(SolidusEscaperTest_70, OutsideString_NoEscape_70) {
    JsonBox::SolidusEscaper esc;
    Feed(esc, sb, 'a');
    Feed(esc, sb, JsonBox::Strings::Std::SOLIDUS); // '/'
    Feed(esc, sb, 'b');
    EXPECT_EQ(getStr(), std::string("a/") + "b");
}

// Inside a JSON string, '/' must be escaped as "\\/"
TEST_F(SolidusEscaperTest_70, InsideString_SolidusEscaped_70) {
    JsonBox::SolidusEscaper esc;
    Feed(esc, sb, JsonBox::Strings::Std::QUOTATION_MARK); // enter string
    Feed(esc, sb, 'x');
    auto ret = Feed(esc, sb, JsonBox::Strings::Std::SOLIDUS); // '/'
    Feed(esc, sb, 'y');
    Feed(esc, sb, JsonBox::Strings::Std::QUOTATION_MARK); // exit string
    EXPECT_EQ(getStr(), std::string("\"x") + JsonBox::Strings::Json::SOLIDUS + "y\"");
    // When escaping occurs, operator() returns 0 (per implementation contract).
    EXPECT_EQ(ret, std::streambuf::int_type(0));
}

// Inside a string, if the previous char was a backslash, '/' must NOT be escaped.
TEST_F(SolidusEscaperTest_70, InsideString_AfterBackslash_NoEscape_70) {
    JsonBox::SolidusEscaper esc;
    Feed(esc, sb, '"'); // in-string
    Feed(esc, sb, JsonBox::Strings::Json::Escape::BEGIN_ESCAPE); // '\'
    Feed(esc, sb, JsonBox::Strings::Std::SOLIDUS); // should NOT be escaped
    Feed(esc, sb, '"'); // out-of-string
    EXPECT_EQ(getStr(), "\"\\/\"");
}

// An escaped quote inside a string should NOT toggle string state.
TEST_F(SolidusEscaperTest_70, EscapedQuotation_DoesNotToggleString_70) {
    JsonBox::SolidusEscaper esc;
    Feed(esc, sb, '"');                                   // enter
    Feed(esc, sb, '\\');                                  // escape next
    Feed(esc, sb, JsonBox::Strings::Std::QUOTATION_MARK); // escaped quote
    // still inside string here; a '/' must be escaped
    Feed(esc, sb, JsonBox::Strings::Std::SOLIDUS);
    // now close the string
    Feed(esc, sb, JsonBox::Strings::Std::QUOTATION_MARK);
    EXPECT_EQ(getStr(), std::string("\"\\\"") + JsonBox::Strings::Json::SOLIDUS + "\"");
}

// Verify we do toggle out of the string on an unescaped closing quote.
TEST_F(SolidusEscaperTest_70, ClosingQuote_TogglesOutOfString_70) {
    JsonBox::SolidusEscaper esc;
    Feed(esc, sb, '"'); // in
    Feed(esc, sb, 'a');
    Feed(esc, sb, '"'); // out
    // Now outside: '/' should NOT be escaped
    Feed(esc, sb, JsonBox::Strings::Std::SOLIDUS);
    EXPECT_EQ(getStr(), "\"a\"/");
}

// Multiple '/' inside a string should ALL be escaped.
TEST_F(SolidusEscaperTest_70, MultipleSolidus_AllEscapedInsideString_70) {
    JsonBox::SolidusEscaper esc;
    Feed(esc, sb, '"');
    Feed(esc, sb, '/');
    Feed(esc, sb, '/');
    Feed(esc, sb, '/');
    Feed(esc, sb, '"');
    // Expect three occurrences of "\\/"
    EXPECT_EQ(getStr(), std::string("\"")
                         + JsonBox::Strings::Json::SOLIDUS
                         + JsonBox::Strings::Json::SOLIDUS
                         + JsonBox::Strings::Json::SOLIDUS
                         + "\"");
}

// Return value should be non-EOF when character is directly written (no escaping).
TEST_F(SolidusEscaperTest_70, ReturnValue_NonEscaped_IsNotEOF_70) {
    JsonBox::SolidusEscaper esc;
    auto r1 = Feed(esc, sb, 'A'); // outside string, direct write
    EXPECT_NE(r1, std::char_traits<char>::eof());
}

// Backslashes outside a string should not arm escaping or affect subsequent writes.
TEST_F(SolidusEscaperTest_70, BackslashOutsideString_NoEffect_70) {
    JsonBox::SolidusEscaper esc;
    Feed(esc, sb, '\\');
    Feed(esc, sb, '/'); // still outside string, so not escaped
    EXPECT_EQ(getStr(), "\\/");
}
