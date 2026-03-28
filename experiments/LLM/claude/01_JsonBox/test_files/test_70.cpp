#include <gtest/gtest.h>
#include <sstream>
#include <streambuf>
#include "JsonBox/SolidusEscaper.h"

using namespace JsonBox;

class SolidusEscaperTest_70 : public ::testing::Test {
protected:
    SolidusEscaper escaper;
    std::stringbuf outputBuf;

    // Helper to feed a string through the escaper character by character
    std::string processString(const std::string &input) {
        std::stringbuf outBuf;
        SolidusEscaper esc;
        for (char c : input) {
            esc(outBuf, std::streambuf::traits_type::to_int_type(c));
        }
        return outBuf.str();
    }
};

// Test that a regular character outside a string is passed through unchanged
TEST_F(SolidusEscaperTest_70, RegularCharOutsideString_70) {
    std::streambuf::int_type result = escaper(outputBuf, std::streambuf::traits_type::to_int_type('a'));
    EXPECT_EQ(outputBuf.str(), "a");
    EXPECT_NE(result, std::streambuf::traits_type::eof());
}

// Test that a solidus outside a string is NOT escaped (not inside quotes)
TEST_F(SolidusEscaperTest_70, SolidusOutsideStringNotEscaped_70) {
    std::string result = processString("/");
    EXPECT_EQ(result, "/");
}

// Test that a solidus inside a string IS escaped to \/
TEST_F(SolidusEscaperTest_70, SolidusInsideStringEscaped_70) {
    std::string result = processString("\"/\"");
    EXPECT_EQ(result, "\"\\/\"");
}

// Test that quotation mark toggles string state
TEST_F(SolidusEscaperTest_70, QuotationMarkTogglesStringState_70) {
    // "abc" - opening and closing quotes, characters inside passed through
    std::string result = processString("\"abc\"");
    EXPECT_EQ(result, "\"abc\"");
}

// Test multiple soliduses inside a string
TEST_F(SolidusEscaperTest_70, MultipleSolidusesInsideString_70) {
    std::string result = processString("\"//\"");
    EXPECT_EQ(result, "\"\\/\\/\"");
}

// Test solidus after closing string is not escaped
TEST_F(SolidusEscaperTest_70, SolidusAfterClosingStringNotEscaped_70) {
    std::string result = processString("\"a\"/");
    EXPECT_EQ(result, "\"a\"/");
}

// Test that backslash-escaped quote inside string does NOT toggle string state
TEST_F(SolidusEscaperTest_70, BackslashEscapedQuoteDoesNotCloseString_70) {
    // Input: "a\"/" 
    // The \" should not close the string, so / should still be escaped
    std::string input = "\"a\\\"/\"";
    std::string result = processString(input);
    // Inside the string: a, \, ", /, then closing "
    // The \" keeps us in the string, so / gets escaped
    EXPECT_EQ(result, "\"a\\\"\\/\"");
}

// Test that a backslash outside string is just passed through
TEST_F(SolidusEscaperTest_70, BackslashOutsideString_70) {
    std::string result = processString("\\");
    EXPECT_EQ(result, "\\");
}

// Test that double backslash inside string resets afterBackSlash
TEST_F(SolidusEscaperTest_70, DoubleBackslashInsideString_70) {
    // "\\\/" - inside string: \\, then /
    // After \\, afterBackSlash should be false, so / should be escaped
    std::string result = processString("\"\\\\/" "\"");
    EXPECT_EQ(result, "\"\\\\\\/\"");
}

// Test empty input produces empty output
TEST_F(SolidusEscaperTest_70, EmptyInput_70) {
    std::string result = processString("");
    EXPECT_EQ(result, "");
}

// Test single quote character
TEST_F(SolidusEscaperTest_70, SingleQuoteCharacter_70) {
    std::string result = processString("\"");
    EXPECT_EQ(result, "\"");
}

// Test that after backslash+quote (escaped quote), a solidus is still escaped
TEST_F(SolidusEscaperTest_70, SolidusAfterEscapedQuoteStillInString_70) {
    // "test\"/end" - the \" is an escaped quote, so we're still in string
    std::string result = processString("\"test\\\"/end\"");
    // 'end' includes no solidus, but '/' before 'end' should be escaped
    // Actually: "test\"/end" -> t,e,s,t,\,",/,e,n,d
    // After \, afterBackSlash=true, then " doesn't close string
    // Then / is inside string and not after backslash -> escaped
    EXPECT_EQ(result, "\"test\\\"\\/end\"");
}

// Test regular characters inside string are not modified
TEST_F(SolidusEscaperTest_70, RegularCharsInsideStringUnchanged_70) {
    std::string result = processString("\"hello world\"");
    EXPECT_EQ(result, "\"hello world\"");
}

// Test alternating strings and non-strings with soliduses
TEST_F(SolidusEscaperTest_70, AlternatingStringsWithSoliduses_70) {
    // /:  "/"  :  "/"
    std::string result = processString("/\"/\"/ \"/\"");
    // First / outside string: not escaped -> /
    // " opens string
    // / inside string: escaped -> \/
    // " closes string
    // / outside string: not escaped -> /
    // space outside: passed
    // " opens string
    // / inside string: escaped -> \/
    // " closes string
    EXPECT_EQ(result, "/\"\\/\"/ \"\\/\"");
}

// Test that the return value for escaped solidus is 0
TEST_F(SolidusEscaperTest_70, ReturnValueForEscapedSolidus_70) {
    SolidusEscaper esc;
    std::stringbuf buf;
    // Enter string
    esc(buf, std::streambuf::traits_type::to_int_type('"'));
    // Feed solidus - should return 0
    std::streambuf::int_type result = esc(buf, std::streambuf::traits_type::to_int_type('/'));
    EXPECT_EQ(result, 0);
}

// Test that the return value for non-escaped character is sputc result
TEST_F(SolidusEscaperTest_70, ReturnValueForNonEscapedChar_70) {
    SolidusEscaper esc;
    std::stringbuf buf;
    std::streambuf::int_type result = esc(buf, std::streambuf::traits_type::to_int_type('x'));
    EXPECT_EQ(result, std::streambuf::traits_type::to_int_type('x'));
}

// Test backslash followed by non-quote character inside string
TEST_F(SolidusEscaperTest_70, BackslashFollowedByNonQuote_70) {
    // "\n/" - \n inside string, then / should be escaped
    std::string result = processString("\"\\n/\"");
    EXPECT_EQ(result, "\"\\n\\/\"");
}

// Test that backslash only affects the immediately following character
TEST_F(SolidusEscaperTest_70, BackslashOnlyAffectsNextChar_70) {
    // "\a" inside string: after \, afterBackSlash is true
    // then 'a': afterBackSlash resets to false
    // then ": this should close the string
    std::string result = processString("\"\\a\"/");
    EXPECT_EQ(result, "\"\\a\"/");
}

// Test construction - fresh escaper should start outside string
TEST_F(SolidusEscaperTest_70, FreshEscaperStartsOutsideString_70) {
    SolidusEscaper esc;
    std::stringbuf buf;
    // Solidus outside string should not be escaped
    esc(buf, std::streambuf::traits_type::to_int_type('/'));
    EXPECT_EQ(buf.str(), "/");
}
