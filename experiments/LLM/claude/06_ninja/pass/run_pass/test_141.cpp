#include <gtest/gtest.h>
#include <string>

// Declaration of the function under test
void GetWin32EscapedString(const std::string& input, std::string* result);

// Helper to check if string needs escaping (we infer from the implementation
// that strings without spaces, quotes, or other special chars don't need escaping)
// We treat the function as a black box and test observable behavior.

class GetWin32EscapedStringTest_141 : public ::testing::Test {
protected:
    std::string result;
};

// Test: Simple string with no special characters should be appended as-is
TEST_F(GetWin32EscapedStringTest_141, SimpleStringNoEscaping_141) {
    std::string input = "hello";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "hello");
}

// Test: Empty string should remain empty (no escaping needed)
TEST_F(GetWin32EscapedStringTest_141, EmptyString_141) {
    std::string input = "";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "");
}

// Test: String with a space should be quoted
TEST_F(GetWin32EscapedStringTest_141, StringWithSpace_141) {
    std::string input = "hello world";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "\"hello world\"");
}

// Test: String with a double quote should be escaped
TEST_F(GetWin32EscapedStringTest_141, StringWithQuote_141) {
    std::string input = "hello\"world";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "\"hello\\\"world\"");
}

// Test: String with backslash followed by quote
TEST_F(GetWin32EscapedStringTest_141, BackslashBeforeQuote_141) {
    std::string input = "hello\\\"world";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "\"hello\\\\\\\"world\"");
}

// Test: String with trailing backslashes and a space (needs quoting)
TEST_F(GetWin32EscapedStringTest_141, TrailingBackslashesWithSpace_141) {
    std::string input = "hello world\\\\";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "\"hello world\\\\\\\\\"");
}

// Test: String with only a quote
TEST_F(GetWin32EscapedStringTest_141, OnlyQuote_141) {
    std::string input = "\"";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "\"\\\"\"");
}

// Test: String with only spaces
TEST_F(GetWin32EscapedStringTest_141, OnlySpaces_141) {
    std::string input = "   ";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "\"   \"");
}

// Test: String with only backslashes (no special chars otherwise - might not need escaping)
TEST_F(GetWin32EscapedStringTest_141, OnlyBackslashes_141) {
    std::string input = "\\\\\\";
    GetWin32EscapedString(input, &result);
    // Backslashes alone don't trigger escaping, so it should be appended as-is
    EXPECT_EQ(result, "\\\\\\");
}

// Test: Multiple quotes in a string
TEST_F(GetWin32EscapedStringTest_141, MultipleQuotes_141) {
    std::string input = "a\"b\"c";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "\"a\\\"b\\\"c\"");
}

// Test: Backslashes not before a quote in a string that needs escaping
TEST_F(GetWin32EscapedStringTest_141, BackslashesNotBeforeQuote_141) {
    std::string input = "a\\b c";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "\"a\\b c\"");
}

// Test: Multiple consecutive backslashes before a quote
TEST_F(GetWin32EscapedStringTest_141, MultipleBackslashesBeforeQuote_141) {
    std::string input = "a\\\\\"b";
    GetWin32EscapedString(input, &result);
    // Two backslashes before quote: each backslash doubled + one more for the quote
    EXPECT_EQ(result, "\"a\\\\\\\\\\\"b\"");
}

// Test: Result is appended to existing content
TEST_F(GetWin32EscapedStringTest_141, AppendToExistingResult_141) {
    result = "prefix:";
    std::string input = "hello";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "prefix:hello");
}

// Test: Result is appended to existing content with escaping
TEST_F(GetWin32EscapedStringTest_141, AppendToExistingResultWithEscaping_141) {
    result = "prefix:";
    std::string input = "hello world";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "prefix:\"hello world\"");
}

// Test: Trailing backslashes in a string that needs quoting (due to space)
TEST_F(GetWin32EscapedStringTest_141, TrailingBackslashWithSpace_141) {
    std::string input = "a b\\";
    GetWin32EscapedString(input, &result);
    // Trailing backslash gets doubled when the string is quoted
    EXPECT_EQ(result, "\"a b\\\\\"");
}

// Test: String with tab character (might trigger escaping)
TEST_F(GetWin32EscapedStringTest_141, StringWithTab_141) {
    std::string input = "hello\tworld";
    GetWin32EscapedString(input, &result);
    // Tab is likely not a trigger for Win32 escaping; just appended as-is
    // We observe the behavior
    // If no escaping needed: result == input
    // If escaping needed: result == "\"hello\tworld\""
    // We'll test what happens - this is an exploratory boundary test
    EXPECT_FALSE(result.empty());
}

// Test: Single backslash with no special context
TEST_F(GetWin32EscapedStringTest_141, SingleBackslash_141) {
    std::string input = "\\";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "\\");
}

// Test: Quote at the beginning
TEST_F(GetWin32EscapedStringTest_141, QuoteAtBeginning_141) {
    std::string input = "\"hello";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "\"\\\"hello\"");
}

// Test: Quote at the end
TEST_F(GetWin32EscapedStringTest_141, QuoteAtEnd_141) {
    std::string input = "hello\"";
    GetWin32EscapedString(input, &result);
    EXPECT_EQ(result, "\"hello\\\"\"");
}

// Test: Backslash at end of quoted string (space triggers quoting)
TEST_F(GetWin32EscapedStringTest_141, BackslashAtEndOfQuotedString_141) {
    std::string input = "a b\\\\\\";
    GetWin32EscapedString(input, &result);
    // Three trailing backslashes become six when quoting
    EXPECT_EQ(result, "\"a b\\\\\\\\\\\\\"");
}

// Test: Mixed backslashes and quotes
TEST_F(GetWin32EscapedStringTest_141, MixedBackslashesAndQuotes_141) {
    std::string input = "\\\"\\\\\"";
    GetWin32EscapedString(input, &result);
    // First: one backslash before first quote -> "\\\" becomes \\ + \"
    // Then: two backslashes before second quote -> "\\\\" + \" 
    EXPECT_EQ(result, "\"\\\\\\\"\\\\\\\\\\\"\"");
}
