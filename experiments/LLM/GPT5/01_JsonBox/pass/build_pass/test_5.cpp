// File: test/IndentCancellerTest_5.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <streambuf>
#include <string>

#include "JsonBox/IndentCanceller.h"  // class under test

using JsonBox::IndentCanceller;

namespace {

// Helper to feed text through IndentCanceller, character by character.
static std::string RunThrough(IndentCanceller& ic, const std::string& input) {
    std::stringbuf out;
    for (unsigned char c : input) {
        ic(out, std::streambuf::traits_type::to_int_type(c));
    }
    return out.str();
}

class IndentCancellerTest_5 : public ::testing::Test {
protected:
    IndentCanceller ic_; // fresh instance per test
};

} // namespace

// Normal operation: non-whitespace outside strings passes through unchanged.
TEST_F(IndentCancellerTest_5, KeepsNonWhitespace_5) {
    std::string in  = "{}:[],0129truefalse";
    std::string out = RunThrough(ic_, in);
    EXPECT_EQ(out, in);
}

// Whitespace outside strings is removed (spaces, tabs, newlines, carriage returns).
TEST_F(IndentCancellerTest_5, RemovesWhitespaceOutsideStrings_5) {
    std::string in  = " \t\n\r a \t b \n\r ";
    std::string out = RunThrough(ic_, in);
    EXPECT_EQ(out, "ab");
}

// Spaces inside strings are preserved.
TEST_F(IndentCancellerTest_5, PreservesSpacesInsideStrings_5) {
    std::string in  = "\"a b c\"";
    std::string out = RunThrough(ic_, in);
    EXPECT_EQ(out, "\"a b c\"");
}

// Escaped quote inside a string should NOT terminate the string;
// the space following the escaped quote remains inside the string and is preserved.
TEST_F(IndentCancellerTest_5, HandlesEscapedQuoteInsideString_5) {
    std::string in  = "\"a\\\" b\"";
    std::string out = RunThrough(ic_, in);
    EXPECT_EQ(out, "\"a\\\" b\"");
}

// Raw tab/newline/carriage-return characters are removed even when they appear between quotes,
// but escaped sequences (backslash + 't'/'n'/'r') are preserved verbatim.
TEST_F(IndentCancellerTest_5, DropsRawControlWhitespaceInsideString_5) {
    // Contains a real tab and a real newline between quotes.
    std::string in  = "\"a\tb\nc\rd\"";
    std::string out = RunThrough(ic_, in);
    // The tab/newline/carriage-return are removed; other characters, including quotes, remain.
    EXPECT_EQ(out, "\"abcd\"");
}

// Backslashes that occur OUTSIDE of strings do not affect string state;
// they are not whitespace and therefore pass through unchanged.
TEST_F(IndentCancellerTest_5, IgnoresBackslashOutsideString_5) {
    std::string in  = "\\\"x\""; // backslash, quote, x, quote
    // Expect the initial backslash and quote to pass, then start string at the quote.
    std::string out = RunThrough(ic_, in);
    EXPECT_EQ(out, "\\\"x\"");
}

// End-to-end minification example: structural whitespace is stripped, while string content is preserved.
TEST_F(IndentCancellerTest_5, MinifiesJsonLikeSnippet_5) {
    std::string in  = " { \n  \"k e y\"  : \t 1 \r } \n";
    std::string out = RunThrough(ic_, in);
    EXPECT_EQ(out, "{\"k e y\":1}");
}

// Boundary: empty input yields empty output.
TEST_F(IndentCancellerTest_5, EmptyInput_5) {
    std::string out = RunThrough(ic_, "");
    EXPECT_TRUE(out.empty());
}

// Boundary: input with only whitespace outside strings yields empty output.
TEST_F(IndentCancellerTest_5, OnlyWhitespaceOutsideStrings_5) {
    std::string out = RunThrough(ic_, " \t\n\r \t\r\n ");
    EXPECT_TRUE(out.empty());
}

// Observable return value: filtered characters (e.g., a space outside a string) return 0.
TEST_F(IndentCancellerTest_5, ReturnsZeroWhenFiltering_5) {
    std::stringbuf out;
    // A single space outside a string should be filtered and return 0 (per interface behavior).
    auto ret = ic_(out, std::streambuf::traits_type::to_int_type(' '));
    EXPECT_EQ(ret, std::streambuf::int_type(0));
}

// Stateful processing across calls: feeding in chunks should behave the same as one pass.
TEST_F(IndentCancellerTest_5, StatefulAcrossMultipleCallsSameBuffer_5) {
    std::string first  = " { \n  \"k\"";
    std::string second = "  : \t 1 \r } \n";

    std::stringbuf out;
    for (unsigned char c : first) {
        ic_(out, std::streambuf::traits_type::to_int_type(c));
    }
    for (unsigned char c : second) {
        ic_(out, std::streambuf::traits_type::to_int_type(c));
    }
    EXPECT_EQ(out.str(), "{\"k\":1}");
}
