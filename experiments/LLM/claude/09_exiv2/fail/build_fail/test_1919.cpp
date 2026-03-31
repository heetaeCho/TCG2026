#include <gtest/gtest.h>
#include <string>

// We need access to the static function and its dependencies.
// Including the XMP SDK headers for the types and helper functions.
#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"
#include "XMP_Const.h"

// Since ApplyQuotes is static, we include the source to get access
// We may need to extract or expose it. For testing purposes, we replicate the declaration.
// In practice, this would require a test-friend mechanism or making the function non-static.

typedef unsigned long UniCodePoint;

// Forward declare or include the function. Since it's static in the cpp, 
// we include it in this translation unit.
#include "XMPUtils-FileInfo.cpp"

class ApplyQuotesTest_1919 : public ::testing::Test {
protected:
    // Common quote characters (ASCII double quote)
    static const UniCodePoint kDoubleQuoteOpen = 0x22;   // "
    static const UniCodePoint kDoubleQuoteClose = 0x22;  // "
    // Unicode left/right double quotation marks
    static const UniCodePoint kLeftDoubleQuote = 0x201C;  // "
    static const UniCodePoint kRightDoubleQuote = 0x201D; // "
};

// Test: Simple string without special characters should remain unchanged
TEST_F(ApplyQuotesTest_1919, SimpleStringUnchanged_1919) {
    std::string item = "hello";
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, false);
    EXPECT_EQ(item, "hello");
}

// Test: String with multiple consecutive spaces gets quoted
TEST_F(ApplyQuotesTest_1919, MultipleSpacesCauseQuoting_1919) {
    std::string item = "hello  world";
    std::string original = item;
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, false);
    // The string should now be different (quoted)
    EXPECT_NE(item, original);
    // Should start with a quote character
    EXPECT_EQ(item[0], '"');
    // Should end with a quote character
    EXPECT_EQ(item[item.size() - 1], '"');
}

// Test: String with semicolon gets quoted
TEST_F(ApplyQuotesTest_1919, SemicolonCausesQuoting_1919) {
    std::string item = "hello;world";
    std::string original = item;
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, false);
    EXPECT_NE(item, original);
    EXPECT_EQ(item[0], '"');
    EXPECT_EQ(item[item.size() - 1], '"');
}

// Test: String with comma gets quoted when allowCommas is false
TEST_F(ApplyQuotesTest_1919, CommaQuotedWhenNotAllowed_1919) {
    std::string item = "hello,world";
    std::string original = item;
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, false);
    EXPECT_NE(item, original);
    EXPECT_EQ(item[0], '"');
}

// Test: String with comma remains unchanged when allowCommas is true
TEST_F(ApplyQuotesTest_1919, CommaUnchangedWhenAllowed_1919) {
    std::string item = "hello,world";
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, true);
    // Comma alone shouldn't trigger quoting when allowed
    EXPECT_EQ(item, "hello,world");
}

// Test: Empty string should remain unchanged
TEST_F(ApplyQuotesTest_1919, EmptyStringUnchanged_1919) {
    std::string item = "";
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, false);
    EXPECT_EQ(item, "");
}

// Test: Single space should not trigger quoting (only multiple spaces do)
TEST_F(ApplyQuotesTest_1919, SingleSpaceNoQuoting_1919) {
    std::string item = "hello world";
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, true);
    EXPECT_EQ(item, "hello world");
}

// Test: String already starting with a quote character should remain unchanged
TEST_F(ApplyQuotesTest_1919, AlreadyQuotedStringUnchanged_1919) {
    std::string item = "\"hello  world\"";
    std::string original = item;
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, false);
    EXPECT_EQ(item, original);
}

// Test: Single character string
TEST_F(ApplyQuotesTest_1919, SingleCharString_1919) {
    std::string item = "a";
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, false);
    EXPECT_EQ(item, "a");
}

// Test: String with existing quotes inside that match surrounding quotes gets them doubled
TEST_F(ApplyQuotesTest_1919, InternalQuotesDoubled_1919) {
    std::string item = "he\"llo  world";
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, false);
    // The internal quote should be doubled and the whole thing wrapped
    // Check it starts and ends with quote
    EXPECT_EQ(item[0], '"');
    EXPECT_EQ(item[item.size() - 1], '"');
    // The internal quote at position should be doubled
    // Find the doubled quote
    size_t pos = item.find("\"\"", 1);
    EXPECT_NE(pos, std::string::npos);
}

// Test: String with only spaces (multiple)
TEST_F(ApplyQuotesTest_1919, OnlyMultipleSpaces_1919) {
    std::string item = "  ";
    std::string original = item;
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, false);
    // Multiple spaces should trigger quoting
    EXPECT_NE(item, original);
    EXPECT_EQ(item[0], '"');
    EXPECT_EQ(item[item.size() - 1], '"');
}

// Test: Trailing spaces after normal text with a break point
TEST_F(ApplyQuotesTest_1919, TrailingMultipleSpaces_1919) {
    std::string item = "abc  ";
    std::string original = item;
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, false);
    EXPECT_NE(item, original);
    EXPECT_EQ(item[0], '"');
}

// Test: Semicolon at the beginning
TEST_F(ApplyQuotesTest_1919, SemicolonAtBeginning_1919) {
    std::string item = ";hello";
    std::string original = item;
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, false);
    EXPECT_NE(item, original);
    EXPECT_EQ(item[0], '"');
    EXPECT_EQ(item[item.size() - 1], '"');
}

// Test: Tab character (control) causes quoting
TEST_F(ApplyQuotesTest_1919, ControlCharCausesQuoting_1919) {
    std::string item = "hello\tworld";
    std::string original = item;
    ApplyQuotes(&item, kDoubleQuoteOpen, kDoubleQuoteClose, false);
    EXPECT_NE(item, original);
    EXPECT_EQ(item[0], '"');
}
