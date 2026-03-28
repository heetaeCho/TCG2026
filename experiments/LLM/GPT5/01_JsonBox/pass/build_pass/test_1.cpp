// File: EscaperTest.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <streambuf>
#include <string>

#include "JsonBox/Escaper.h"
#include "JsonBox/Value.h"
#include "JsonBox/Grammar.h"

using JsonBox::Escaper;
using Traits = std::streambuf::traits_type;

class EscaperTest_1 : public ::testing::Test {
protected:
    std::stringbuf dest_;
    Escaper esc_;

    // Convenience wrapper to call operator() with a char
    std::streambuf::int_type Put(char c) {
        return esc_(dest_, Traits::to_int_type(c));
    }

    std::string out() const { return dest_.str(); }
};

// Normal operation outside of a string: character is passed through unchanged.
TEST_F(EscaperTest_1, WritesNormalCharOutsideString_1) {
    auto ret = Put('A');
    EXPECT_EQ(out(), std::string("A"));
    EXPECT_EQ(ret, Traits::to_int_type('A'));  // unescaped => sputc return
}

// Enter and exit string on quotes: quotes themselves are written and toggling occurs.
TEST_F(EscaperTest_1, EntersAndExitsString_TogglesOnQuote_1) {
    auto r1 = Put(JsonBox::Structural::BEGIN_END_STRING); // open "
    auto r2 = Put('x');                                    // inside
    auto r3 = Put(JsonBox::Structural::BEGIN_END_STRING); // close "
    EXPECT_EQ(out(), std::string("\"x\""));
    EXPECT_EQ(r1, Traits::to_int_type('"'));
    EXPECT_EQ(r2, Traits::to_int_type('x'));
    EXPECT_EQ(r3, Traits::to_int_type('"'));
}

// Inside string: backslash is escaped as "\\\\" and returns 0 from operator().
TEST_F(EscaperTest_1, EscapesBackslashInsideString_1) {
    Put('"');                           // enter string
    auto ret = Put(JsonBox::Strings::Std::REVERSE_SOLIDUS); // '\'
    Put('"');                           // exit string
    EXPECT_EQ(out(), std::string("\"") + JsonBox::Strings::Json::REVERSE_SOLIDUS + "\"");
    EXPECT_EQ(ret, 0); // escaped path returns 0
}

// Inside string: common control characters are escaped to their JSON sequences.
TEST_F(EscaperTest_1, EscapesCommonControlCharsInsideString_1) {
    Put('"'); // enter
    auto rb = Put(JsonBox::Strings::Std::BACKSPACE);
    auto rf = Put(JsonBox::Strings::Std::FORM_FEED);
    auto rn = Put(JsonBox::Strings::Std::LINE_FEED);
    auto rt = Put(JsonBox::Strings::Std::TAB);
    Put('"'); // exit

    std::string expected = std::string("\"")
        + JsonBox::Strings::Json::BACKSPACE
        + JsonBox::Strings::Json::FORM_FEED
        + JsonBox::Strings::Json::LINE_FEED
        + JsonBox::Strings::Json::TAB
        + "\"";

    EXPECT_EQ(out(), expected);
    EXPECT_EQ(rb, 0);
    EXPECT_EQ(rf, 0);
    EXPECT_EQ(rn, 0);
    EXPECT_EQ(rt, 0);
}

// Inside string: other control chars (e.g., '\r') escape to Unicode using Value::escapeToUnicode.
TEST_F(EscaperTest_1, EscapesOtherControlCharToUnicodeInsideString_1) {
    Put('"'); // enter
    char cr = '\r';
    auto ret = Put(cr);
    Put('"'); // exit

    std::string expected = std::string("\"") + JsonBox::Value::escapeToUnicode(cr) + "\"";
    EXPECT_EQ(out(), expected);
    EXPECT_EQ(ret, 0);
}

// Outside string: control characters are not escaped by Escaper (they pass through).
TEST_F(EscaperTest_1, ControlCharOutsideStringNotEscaped_1) {
    char lf = '\n';
    auto ret = Put(lf);
    EXPECT_EQ(out(), std::string(1, lf));     // raw newline in buffer
    EXPECT_EQ(ret, Traits::to_int_type(lf));  // unescaped => sputc return
}

// Backslash before quote inside string: quote does not end the string (after-backslash behavior).
TEST_F(EscaperTest_1, AfterBackslashPreventsStringToggle_1) {
    Put('"');                                        // open string
    auto rSlash = Put(JsonBox::Strings::Std::REVERSE_SOLIDUS); // '\'
    auto rQuote = Put(JsonBox::Structural::BEGIN_END_STRING);  // '"', should be content
    auto rX     = Put('x');                          // still inside
    Put('"');                                        // final closing quote

    // Expected: "\"" + "\\\\" + "\"" + "x" + "\""
    std::string expected = std::string("\"")
        + JsonBox::Strings::Json::REVERSE_SOLIDUS
        + "\"x\"";
    EXPECT_EQ(out(), expected);
    EXPECT_EQ(rSlash, 0);                            // escaped
    EXPECT_EQ(rQuote, Traits::to_int_type('"'));     // written as content
    EXPECT_EQ(rX,     Traits::to_int_type('x'));
}

// After-backslash flag only applies to the immediate next character (one-shot).
TEST_F(EscaperTest_1, AfterBackslashIsOneShot_1) {
    Put('"');                                        // open
    Put(JsonBox::Strings::Std::REVERSE_SOLIDUS);     // sets afterBackSlash
    auto rA = Put('a');                              // consumes afterBackSlash, normal char
    auto rClose = Put('"');                          // now closes the string
    EXPECT_EQ(out(), std::string("\"")
                      + JsonBox::Strings::Json::REVERSE_SOLIDUS
                      + "a\"");                      // backslash escaped + 'a' + closing quote
    EXPECT_EQ(rA, Traits::to_int_type('a'));
    EXPECT_EQ(rClose, Traits::to_int_type('"'));
}
