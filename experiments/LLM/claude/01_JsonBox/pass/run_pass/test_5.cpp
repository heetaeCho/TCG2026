#include <gtest/gtest.h>
#include <sstream>
#include <streambuf>
#include "JsonBox/IndentCanceller.h"

class IndentCancellerTest_5 : public ::testing::Test {
protected:
    JsonBox::IndentCanceller canceller;
    std::stringbuf destBuf;

    std::streambuf::int_type feed(char c) {
        return canceller(destBuf, std::streambuf::traits_type::to_int_type(c));
    }

    std::string getOutput() {
        return destBuf.str();
    }
};

// Test that a regular character is written to destination
TEST_F(IndentCancellerTest_5, RegularCharacterIsWritten_5) {
    auto result = feed('a');
    EXPECT_EQ(getOutput(), "a");
    EXPECT_NE(result, 0);
}

// Test that newline is stripped (returns 0, not written)
TEST_F(IndentCancellerTest_5, NewLineIsStripped_5) {
    auto result = feed('\n');
    EXPECT_EQ(getOutput(), "");
    EXPECT_EQ(result, 0);
}

// Test that horizontal tab is stripped
TEST_F(IndentCancellerTest_5, HorizontalTabIsStripped_5) {
    auto result = feed('\t');
    EXPECT_EQ(getOutput(), "");
    EXPECT_EQ(result, 0);
}

// Test that carriage return is stripped
TEST_F(IndentCancellerTest_5, CarriageReturnIsStripped_5) {
    auto result = feed('\r');
    EXPECT_EQ(getOutput(), "");
    EXPECT_EQ(result, 0);
}

// Test that space outside of string is stripped
TEST_F(IndentCancellerTest_5, SpaceOutsideStringIsStripped_5) {
    auto result = feed(' ');
    EXPECT_EQ(getOutput(), "");
    EXPECT_EQ(result, 0);
}

// Test that space inside a string is preserved
TEST_F(IndentCancellerTest_5, SpaceInsideStringIsPreserved_5) {
    feed('"'); // enter string
    auto result = feed(' ');
    EXPECT_NE(result, 0);
    EXPECT_EQ(getOutput(), "\" ");
}

// Test that newline inside a string is still stripped
TEST_F(IndentCancellerTest_5, NewLineInsideStringIsStillStripped_5) {
    feed('"'); // enter string
    auto result = feed('\n');
    EXPECT_EQ(result, 0);
    EXPECT_EQ(getOutput(), "\"");
}

// Test that tab inside a string is still stripped
TEST_F(IndentCancellerTest_5, TabInsideStringIsStillStripped_5) {
    feed('"'); // enter string
    auto result = feed('\t');
    EXPECT_EQ(result, 0);
    EXPECT_EQ(getOutput(), "\"");
}

// Test entering and exiting a string
TEST_F(IndentCancellerTest_5, EnterAndExitString_5) {
    feed('"');  // enter string
    feed('a');
    feed('"');  // exit string
    auto result = feed(' '); // space outside string should be stripped
    EXPECT_EQ(result, 0);
    EXPECT_EQ(getOutput(), "\"a\"");
}

// Test that escaped quote does not toggle string state
TEST_F(IndentCancellerTest_5, EscapedQuoteDoesNotExitString_5) {
    feed('"');   // enter string
    feed('\\');  // backslash
    feed('"');   // escaped quote, should NOT exit string
    auto result = feed(' '); // space inside string should be preserved
    EXPECT_NE(result, 0);
    EXPECT_EQ(getOutput(), "\"\\\" ");
}

// Test that double backslash resets escape state
TEST_F(IndentCancellerTest_5, DoubleBackslashResetsEscapeState_5) {
    feed('"');   // enter string
    feed('\\');  // first backslash
    feed('\\');  // second backslash (escapes the first, afterBackSlash becomes false)
    feed('"');   // this quote should exit the string
    auto result = feed(' '); // space outside string should be stripped
    EXPECT_EQ(result, 0);
    EXPECT_EQ(getOutput(), "\"\\\\\"");
}

// Test multiple regular characters are all written
TEST_F(IndentCancellerTest_5, MultipleRegularCharactersWritten_5) {
    feed('h');
    feed('e');
    feed('l');
    feed('l');
    feed('o');
    EXPECT_EQ(getOutput(), "hello");
}

// Test that backslash outside string does not affect escaping
TEST_F(IndentCancellerTest_5, BackslashOutsideStringDoesNotEscape_5) {
    feed('\\'); // backslash outside string
    feed('"');  // this should enter string (afterBackSlash should be false outside string)
    auto result = feed(' '); // inside string, space preserved
    EXPECT_NE(result, 0);
    EXPECT_EQ(getOutput(), "\\\" ");
}

// Test whitespace stripping for a JSON-like input
TEST_F(IndentCancellerTest_5, JsonLikeInputWhitespaceStripped_5) {
    // Simulating: { \n\t "key" : "value" \n}
    feed('{');
    feed('\n');
    feed('\t');
    feed('"');
    feed('k');
    feed('e');
    feed('y');
    feed('"');
    feed(' ');
    feed(':');
    feed(' ');
    feed('"');
    feed('v');
    feed('a');
    feed('l');
    feed('u');
    feed('e');
    feed('"');
    feed('\n');
    feed('}');
    EXPECT_EQ(getOutput(), "{\"key\":\"value\"}");
}

// Test that space inside string with surrounding text works
TEST_F(IndentCancellerTest_5, SpaceInsideStringWithText_5) {
    feed('"');
    feed('h');
    feed('e');
    feed('l');
    feed('l');
    feed('o');
    feed(' ');
    feed('w');
    feed('o');
    feed('r');
    feed('l');
    feed('d');
    feed('"');
    EXPECT_EQ(getOutput(), "\"hello world\"");
}

// Test escaped backslash followed by escaped quote inside string
TEST_F(IndentCancellerTest_5, EscapedBackslashThenEscapedQuote_5) {
    feed('"');   // enter string
    feed('\\');  // backslash (afterBackSlash = true)
    feed('\\');  // escaped backslash (afterBackSlash = false)
    feed('\\');  // another backslash (afterBackSlash = true)
    feed('"');   // escaped quote (afterBackSlash was true, so inString stays true)
    auto result = feed(' '); // still inside string
    EXPECT_NE(result, 0);
    EXPECT_EQ(getOutput(), "\"\\\\\\\" ");
}

// Test carriage return inside string is stripped
TEST_F(IndentCancellerTest_5, CarriageReturnInsideStringIsStripped_5) {
    feed('"');
    auto result = feed('\r');
    EXPECT_EQ(result, 0);
    EXPECT_EQ(getOutput(), "\"");
}

// Test default constructed canceller starts not in string
TEST_F(IndentCancellerTest_5, DefaultStateNotInString_5) {
    // Space should be stripped since we're not in a string
    auto result = feed(' ');
    EXPECT_EQ(result, 0);
    EXPECT_EQ(getOutput(), "");
}

// Test that after exiting string, backslash doesn't set afterBackSlash
TEST_F(IndentCancellerTest_5, BackslashAfterExitingString_5) {
    feed('"');   // enter
    feed('"');   // exit
    feed('\\');  // backslash outside string - afterBackSlash should NOT be set
    feed('"');   // should enter string
    auto result = feed(' '); // inside string, should preserve
    EXPECT_NE(result, 0);
}

// Test empty string literal
TEST_F(IndentCancellerTest_5, EmptyStringLiteral_5) {
    feed('"');
    feed('"');
    // Now outside string again
    auto result = feed(' ');
    EXPECT_EQ(result, 0);
    EXPECT_EQ(getOutput(), "\"\"");
}

// Test digits pass through
TEST_F(IndentCancellerTest_5, DigitsPassThrough_5) {
    feed('1');
    feed('2');
    feed('3');
    EXPECT_EQ(getOutput(), "123");
}

// Test structural characters pass through outside string
TEST_F(IndentCancellerTest_5, StructuralCharactersPassThrough_5) {
    feed('{');
    feed('[');
    feed(']');
    feed('}');
    feed(':');
    feed(',');
    EXPECT_EQ(getOutput(), "{[]}:,");
}
