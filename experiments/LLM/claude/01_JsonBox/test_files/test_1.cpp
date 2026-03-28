#include <gtest/gtest.h>
#include <sstream>
#include <streambuf>
#include <string>

#include "JsonBox/Escaper.h"
#include "JsonBox/Value.h"
#include "JsonBox/Grammar.h"

// Helper function to feed a string through the Escaper and collect output
static std::string escapeString(const std::string& input) {
    std::stringbuf dest;
    JsonBox::Escaper escaper;
    for (char c : input) {
        escaper(dest, std::streambuf::traits_type::to_int_type(c));
    }
    return dest.str();
}

class EscaperTest_1 : public ::testing::Test {
protected:
    JsonBox::Escaper escaper;
    std::stringbuf destination;
};

// Test that characters outside a string are passed through without escaping
TEST_F(EscaperTest_1, NonStringCharactersPassThrough_1) {
    std::string input = "hello";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "hello");
}

// Test that a quote character toggles string mode
TEST_F(EscaperTest_1, QuoteTogglesStringMode_1) {
    // "abc" — the quotes themselves should pass through, content inside should be processed
    std::string input = "\"abc\"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\"abc\"");
}

// Test escaping backslash inside a string
TEST_F(EscaperTest_1, BackslashEscapedInsideString_1) {
    // Input: "\" (a quote, then a backslash, then a quote)
    std::string input = "\"\\\"";
    std::string result = escapeString(input);
    // Inside string, backslash should become "\\\\"
    EXPECT_EQ(result, "\"\\\\\"");
}

// Test escaping backspace inside a string
TEST_F(EscaperTest_1, BackspaceEscapedInsideString_1) {
    std::string input = "\"";
    input += '\b';
    input += "\"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\"\\b\"");
}

// Test escaping form feed inside a string
TEST_F(EscaperTest_1, FormFeedEscapedInsideString_1) {
    std::string input = "\"";
    input += '\f';
    input += "\"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\"\\f\"");
}

// Test escaping line feed inside a string
TEST_F(EscaperTest_1, LineFeedEscapedInsideString_1) {
    std::string input = "\"";
    input += '\n';
    input += "\"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\"\\n\"");
}

// Test escaping tab inside a string
TEST_F(EscaperTest_1, TabEscapedInsideString_1) {
    std::string input = "\"";
    input += '\t';
    input += "\"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\"\\t\"");
}

// Test that control characters (0x00-0x1f) other than the specific ones get unicode-escaped
TEST_F(EscaperTest_1, ControlCharacterUnicodeEscaped_1) {
    std::string input = "\"";
    input += '\x01';
    input += "\"";
    std::string result = escapeString(input);
    // Should be escaped to \u0001
    EXPECT_EQ(result, "\"\\u0001\"");
}

// Test control character \x00 inside a string
TEST_F(EscaperTest_1, NullCharacterUnicodeEscaped_1) {
    std::string input = "\"";
    input += std::string(1, '\x00');
    input += "\"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\"\\u0000\"");
}

// Test that backslash is NOT escaped outside of a string
TEST_F(EscaperTest_1, BackslashNotEscapedOutsideString_1) {
    std::string input = "\\";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\\");
}

// Test that special characters are NOT escaped outside of a string
TEST_F(EscaperTest_1, SpecialCharsNotEscapedOutsideString_1) {
    std::string input = "\n\t\b\f";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\n\t\b\f");
}

// Test normal characters inside a string are not escaped
TEST_F(EscaperTest_1, NormalCharsInsideStringNotEscaped_1) {
    std::string input = "\"Hello World 123!\"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\"Hello World 123!\"");
}

// Test that after a backslash escape in JSON, the next character is not treated as special
// e.g., \" inside a string: the backslash is an escape begin, so the following quote 
// doesn't end the string
TEST_F(EscaperTest_1, EscapedQuoteDoesNotEndString_1) {
    // We want to construct: "hello\"world"
    // which in the source is: "hello\x5c"world"
    // The escaper sees: " h e l l o \ " w o r l d "
    // After the backslash (escape begin), the next " should not toggle inString
    // So 'w', 'o', 'r', 'l', 'd' should still be inside a string
    std::string input;
    input += '"';        // begin string
    input += 'h';
    input += 'e';
    input += 'l';
    input += 'l';
    input += 'o';
    input += '\\';       // backslash in string -> gets escaped to "\\\\"
    input += '"';        // this quote is after backslash, so inString remains true
    input += '\n';       // newline inside string -> gets escaped
    input += '"';        // this ends the string
    
    std::string result = escapeString(input);
    // Expected: "hello\\"\\n"
    // " -> "
    // hello -> hello
    // \ -> \\ (escaped)
    // " -> " (but afterBackSlash was true, so inString stays true... wait, 
    //   the backslash was escaped, but afterBackSlash is set based on the original char)
    // Actually: afterBackSlash = inString && !afterBackSlash && (tmpChar == '\\')
    // For the backslash char: afterBackSlash was false, tmpChar is '\\', inString=true => afterBackSlash = true
    // For the quote after backslash: inString = !inString || afterBackSlash = !true || true = true
    //   So inString stays true. afterBackSlash = true && !true && ... = false... 
    //   Wait: afterBackSlash = inString && !afterBackSlash && (tmpChar == '\\')
    //   afterBackSlash was true from previous step. So: inString(true) && !true && ... = false
    // For \n: inString=true, afterBackSlash=false, so it gets escaped to \\n
    // For final ": inString = !true || false = false. String ends.
    
    EXPECT_EQ(result, "\"hello\\\\\"\\n\"");
}

// Test multiple strings in sequence
TEST_F(EscaperTest_1, MultipleStringsInSequence_1) {
    std::string input = "\"ab\",\"cd\"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\"ab\",\"cd\"");
}

// Test empty string
TEST_F(EscaperTest_1, EmptyStringLiteral_1) {
    std::string input = "\"\"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\"\"");
}

// Test empty input
TEST_F(EscaperTest_1, EmptyInput_1) {
    std::string input = "";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "");
}

// Test return value: when character is not escaped, sputc return value is returned
TEST_F(EscaperTest_1, ReturnValueNotEscaped_1) {
    std::stringbuf dest;
    JsonBox::Escaper esc;
    // Outside string, 'A' should not be escaped, returns sputc result
    auto ret = esc(dest, std::streambuf::traits_type::to_int_type('A'));
    EXPECT_NE(ret, std::streambuf::traits_type::eof());
    EXPECT_EQ(dest.str(), "A");
}

// Test return value: when character is escaped, 0 is returned
TEST_F(EscaperTest_1, ReturnValueWhenEscaped_1) {
    std::stringbuf dest;
    JsonBox::Escaper esc;
    // Enter string mode
    esc(dest, std::streambuf::traits_type::to_int_type('"'));
    // Send a tab inside string — should be escaped
    auto ret = esc(dest, std::streambuf::traits_type::to_int_type('\t'));
    EXPECT_EQ(ret, 0);
}

// Test control character 0x1f (boundary)
TEST_F(EscaperTest_1, ControlCharBoundary0x1F_1) {
    std::string input = "\"";
    input += '\x1f';
    input += "\"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\"\\u001f\"");
}

// Test character 0x20 (space) is NOT unicode-escaped inside a string
TEST_F(EscaperTest_1, SpaceNotEscapedInsideString_1) {
    std::string input = "\" \"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\" \"");
}

// Test that multiple backslashes in a row alternate the afterBackSlash state
TEST_F(EscaperTest_1, MultipleBackslashesInsideString_1) {
    // Inside a string: \\ -> each \ is escaped to \\
    // First \: afterBackSlash becomes true, output: "\\"
    // Second \: afterBackSlash was true, so !afterBackSlash is false, 
    //   so we enter the regular escape path? No:
    //   inString=true, !afterBackSlash=false, so the if (inString && !afterBackSlash) is false
    //   So the second backslash is NOT escaped, just passed through
    //   afterBackSlash = inString && !afterBackSlash && (tmpChar=='\\') = true && false && true = false
    // Wait, let me re-read: afterBackSlash = inString && !afterBackSlash && (tmpChar == '\\')
    // For second backslash: afterBackSlash was true, so !true = false => afterBackSlash = false
    // And since inString && !afterBackSlash was false, notEscaped stays true, so sputc is called
    
    std::string input = "\"";
    input += '\\';
    input += '\\';
    input += "\"";
    std::string result = escapeString(input);
    // First backslash: escaped to "\\\\"
    // Second backslash: not escaped, just "\\"... wait, sputc('\\') outputs single backslash
    EXPECT_EQ(result, "\"\\\\\\\"");
}

// Test freshly constructed Escaper starts not in string and not after backslash
TEST_F(EscaperTest_1, FreshEscaperStartsOutsideString_1) {
    std::stringbuf dest;
    JsonBox::Escaper esc;
    // A tab outside a string should not be escaped
    auto ret = esc(dest, std::streambuf::traits_type::to_int_type('\t'));
    EXPECT_EQ(dest.str(), std::string(1, '\t'));
}

// Test various control characters inside a string
TEST_F(EscaperTest_1, ControlChar0x02InsideString_1) {
    std::string input = "\"";
    input += '\x02';
    input += "\"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\"\\u0002\"");
}

TEST_F(EscaperTest_1, ControlChar0x10InsideString_1) {
    std::string input = "\"";
    input += '\x10';
    input += "\"";
    std::string result = escapeString(input);
    EXPECT_EQ(result, "\"\\u0010\"");
}
