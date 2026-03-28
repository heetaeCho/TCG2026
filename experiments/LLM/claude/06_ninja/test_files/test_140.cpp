#include <gtest/gtest.h>
#include <string>

// Forward declaration of the function under test
void GetShellEscapedString(const std::string& input, std::string* result);

// Helper to check if a string needs shell escaping (inferred from the implementation)
// We don't reimplement it; we just test the observable behavior of GetShellEscapedString.

class GetShellEscapedStringTest_140 : public ::testing::Test {
protected:
    std::string result;
};

// Test: Simple alphanumeric string that doesn't need escaping
TEST_F(GetShellEscapedStringTest_140, SimpleAlphanumericString_140) {
    std::string input = "hello";
    GetShellEscapedString(input, &result);
    // Simple strings without special characters should either be passed through
    // directly or quoted. We check that the input appears in the result.
    // If no escaping needed, result should just be the input.
    EXPECT_FALSE(result.empty());
    // At minimum the input content should be present
    EXPECT_NE(result.find("hello"), std::string::npos);
}

// Test: Empty string
TEST_F(GetShellEscapedStringTest_140, EmptyString_140) {
    std::string input = "";
    GetShellEscapedString(input, &result);
    // An empty string either stays empty or gets quoted
    // Either way it should not crash
    // Empty string likely doesn't need escaping
    EXPECT_EQ(result, "");
}

// Test: String with a single quote should be escaped
TEST_F(GetShellEscapedStringTest_140, StringWithSingleQuote_140) {
    std::string input = "it's";
    GetShellEscapedString(input, &result);
    // The single quote triggers escaping. The result should be quoted
    // and single quotes should be escaped with the sequence '\'
    EXPECT_FALSE(result.empty());
    // Result should start and end with single quotes
    EXPECT_EQ(result.front(), '\'');
    EXPECT_EQ(result.back(), '\'');
    // The escape sequence '\' should appear in the result
    EXPECT_NE(result.find("'\\''"), std::string::npos);
}

// Test: String with spaces should be escaped
TEST_F(GetShellEscapedStringTest_140, StringWithSpaces_140) {
    std::string input = "hello world";
    GetShellEscapedString(input, &result);
    // Spaces typically require shell escaping
    EXPECT_FALSE(result.empty());
    // Should be wrapped in single quotes
    EXPECT_EQ(result.front(), '\'');
    EXPECT_EQ(result.back(), '\'');
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

// Test: String with special shell characters
TEST_F(GetShellEscapedStringTest_140, StringWithSpecialCharacters_140) {
    std::string input = "foo;bar";
    GetShellEscapedString(input, &result);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.front(), '\'');
    EXPECT_EQ(result.back(), '\'');
    EXPECT_NE(result.find("foo;bar"), std::string::npos);
}

// Test: String with multiple single quotes
TEST_F(GetShellEscapedStringTest_140, MultipleSingleQuotes_140) {
    std::string input = "a'b'c";
    GetShellEscapedString(input, &result);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.front(), '\'');
    EXPECT_EQ(result.back(), '\'');
    // Each single quote in the input should produce the escape sequence
    // Count occurrences of '\'' in the result
    size_t count = 0;
    size_t pos = 0;
    while ((pos = result.find("'\\''", pos)) != std::string::npos) {
        count++;
        pos += 4;
    }
    EXPECT_EQ(count, 2u);  // Two single quotes in input
}

// Test: String that is only a single quote
TEST_F(GetShellEscapedStringTest_140, OnlySingleQuote_140) {
    std::string input = "'";
    GetShellEscapedString(input, &result);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.front(), '\'');
    EXPECT_EQ(result.back(), '\'');
    EXPECT_NE(result.find("'\\''"), std::string::npos);
}

// Test: Result is appended, not overwritten
TEST_F(GetShellEscapedStringTest_140, ResultIsAppended_140) {
    result = "prefix_";
    std::string input = "simple";
    GetShellEscapedString(input, &result);
    // The result should start with the prefix
    EXPECT_EQ(result.substr(0, 7), "prefix_");
    EXPECT_NE(result.find("simple"), std::string::npos);
}

// Test: Result is appended when escaping is needed
TEST_F(GetShellEscapedStringTest_140, ResultIsAppendedWithEscaping_140) {
    result = "prefix_";
    std::string input = "hello world";
    GetShellEscapedString(input, &result);
    EXPECT_EQ(result.substr(0, 7), "prefix_");
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

// Test: String with dollar sign
TEST_F(GetShellEscapedStringTest_140, StringWithDollarSign_140) {
    std::string input = "$HOME";
    GetShellEscapedString(input, &result);
    EXPECT_FALSE(result.empty());
    // Dollar sign likely needs escaping
    EXPECT_EQ(result.front(), '\'');
    EXPECT_EQ(result.back(), '\'');
}

// Test: String with backslash
TEST_F(GetShellEscapedStringTest_140, StringWithBackslash_140) {
    std::string input = "path\\to\\file";
    GetShellEscapedString(input, &result);
    EXPECT_FALSE(result.empty());
    // Backslashes typically need shell escaping
    // The content should be preserved within the quotes
}

// Test: String with tab character
TEST_F(GetShellEscapedStringTest_140, StringWithTab_140) {
    std::string input = "hello\tworld";
    GetShellEscapedString(input, &result);
    EXPECT_FALSE(result.empty());
}

// Test: String with newline character
TEST_F(GetShellEscapedStringTest_140, StringWithNewline_140) {
    std::string input = "hello\nworld";
    GetShellEscapedString(input, &result);
    EXPECT_FALSE(result.empty());
}

// Test: String with pipe character
TEST_F(GetShellEscapedStringTest_140, StringWithPipe_140) {
    std::string input = "foo|bar";
    GetShellEscapedString(input, &result);
    EXPECT_FALSE(result.empty());
}

// Test: Purely numeric string (should not need escaping)
TEST_F(GetShellEscapedStringTest_140, NumericString_140) {
    std::string input = "12345";
    GetShellEscapedString(input, &result);
    // Numeric strings shouldn't need escaping
    EXPECT_EQ(result, "12345");
}

// Test: String with underscores and hyphens (typically safe)
TEST_F(GetShellEscapedStringTest_140, SafeSpecialChars_140) {
    std::string input = "foo-bar_baz";
    GetShellEscapedString(input, &result);
    // Underscores and hyphens are typically safe
    EXPECT_NE(result.find("foo-bar_baz"), std::string::npos);
}

// Test: String starting with single quote
TEST_F(GetShellEscapedStringTest_140, StartsWithSingleQuote_140) {
    std::string input = "'hello";
    GetShellEscapedString(input, &result);
    EXPECT_EQ(result.front(), '\'');
    EXPECT_EQ(result.back(), '\'');
    EXPECT_NE(result.find("'\\''"), std::string::npos);
}

// Test: String ending with single quote
TEST_F(GetShellEscapedStringTest_140, EndsWithSingleQuote_140) {
    std::string input = "hello'";
    GetShellEscapedString(input, &result);
    EXPECT_EQ(result.front(), '\'');
    EXPECT_EQ(result.back(), '\'');
    EXPECT_NE(result.find("'\\''"), std::string::npos);
}

// Test: String with consecutive single quotes
TEST_F(GetShellEscapedStringTest_140, ConsecutiveSingleQuotes_140) {
    std::string input = "a''b";
    GetShellEscapedString(input, &result);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.front(), '\'');
    EXPECT_EQ(result.back(), '\'');
    // Two escape sequences for two consecutive quotes
    size_t count = 0;
    size_t pos = 0;
    while ((pos = result.find("'\\''", pos)) != std::string::npos) {
        count++;
        pos += 4;
    }
    EXPECT_EQ(count, 2u);
}

// Test: Long string without special characters
TEST_F(GetShellEscapedStringTest_140, LongSimpleString_140) {
    std::string input(1000, 'a');
    GetShellEscapedString(input, &result);
    EXPECT_EQ(result, input);
}

// Test: String with only spaces
TEST_F(GetShellEscapedStringTest_140, OnlySpaces_140) {
    std::string input = "   ";
    GetShellEscapedString(input, &result);
    EXPECT_EQ(result.front(), '\'');
    EXPECT_EQ(result.back(), '\'');
}
