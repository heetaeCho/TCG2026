#include <gtest/gtest.h>
#include <string>

// Declaration of the function under test
std::string escape_arg(const std::string& arg);

// Test: Empty string should be escaped with quotes
TEST(EscapeArgTest_880, EmptyStringReturnsQuoted_880) {
    std::string result = escape_arg("");
    EXPECT_EQ(result, "\"\"");
}

// Test: Simple argument with no special characters returns unchanged
TEST(EscapeArgTest_880, SimpleArgNoEscaping_880) {
    std::string result = escape_arg("hello");
    EXPECT_EQ(result, "hello");
}

// Test: Argument with a space is quoted
TEST(EscapeArgTest_880, ArgWithSpaceIsQuoted_880) {
    std::string result = escape_arg("hello world");
    // Should be wrapped in quotes
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
}

// Test: Argument with a tab is quoted
TEST(EscapeArgTest_880, ArgWithTabIsQuoted_880) {
    std::string result = escape_arg("hello\tworld");
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
}

// Test: Argument with a newline is quoted
TEST(EscapeArgTest_880, ArgWithNewlineIsQuoted_880) {
    std::string result = escape_arg("hello\nworld");
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
}

// Test: Argument with a vertical tab is quoted
TEST(EscapeArgTest_880, ArgWithVerticalTabIsQuoted_880) {
    std::string result = escape_arg("hello\vworld");
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
}

// Test: Argument with a double quote is quoted and escaped
TEST(EscapeArgTest_880, ArgWithDoubleQuoteIsEscaped_880) {
    std::string result = escape_arg("hello\"world");
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
    // The quote inside should be escaped
    // Expected: "hello\\"world" — based on the algorithm:
    // For '"': num_backslashes=0, append (0+1)*2=2 backslashes, then '"', then the char '"'
    // So: "hello\\""world"
    EXPECT_EQ(result, "\"hello\\\\\"\"world\"");
}

// Test: Argument with trailing backslashes
TEST(EscapeArgTest_880, ArgWithTrailingBackslashes_880) {
    std::string result = escape_arg("hello\\\\");
    // No special characters besides backslashes, and no spaces/tabs/etc.
    // find_first_of(" \t\n\v\"") == npos, so it should return unchanged
    EXPECT_EQ(result, "hello\\\\");
}

// Test: Argument with trailing backslashes AND a space (needs escaping)
TEST(EscapeArgTest_880, ArgWithTrailingBackslashesAndSpace_880) {
    // "hello\\ " has a space, so it needs quoting
    // Trailing backslashes before end: 2 backslashes become 4
    std::string input = "hello\\\\ ";
    std::string result = escape_arg(input);
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
}

// Test: Argument with backslash before a quote
TEST(EscapeArgTest_880, BackslashBeforeQuote_880) {
    // Input: hello\"
    std::string input = "hello\\\"";
    std::string result = escape_arg(input);
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
    // For the backslash before quote: num_backslashes=1, append (1+1)*2=4 backslashes, then '"', then '"'
    // So: "hello\\\\""" 
    EXPECT_EQ(result, "\"hello\\\\\\\\\"\"\"");
}

// Test: Only spaces
TEST(EscapeArgTest_880, OnlySpaces_880) {
    std::string result = escape_arg("   ");
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
    EXPECT_EQ(result, "\"   \"");
}

// Test: Single character, no special
TEST(EscapeArgTest_880, SingleCharNoSpecial_880) {
    std::string result = escape_arg("a");
    EXPECT_EQ(result, "a");
}

// Test: Single space
TEST(EscapeArgTest_880, SingleSpace_880) {
    std::string result = escape_arg(" ");
    EXPECT_EQ(result, "\" \"");
}

// Test: Single backslash (no special chars)
TEST(EscapeArgTest_880, SingleBackslash_880) {
    std::string result = escape_arg("\\");
    // No special char in " \t\n\v\"", backslash alone doesn't trigger quoting
    EXPECT_EQ(result, "\\");
}

// Test: Single backslash with space triggers quoting and backslash doubling at end
TEST(EscapeArgTest_880, SingleBackslashWithSpace_880) {
    // Input: "\ " — has a space, backslash at position 0, space at position 1
    std::string input = "\\ ";
    std::string result = escape_arg(input);
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
    // Processing: backslash is not at end, not before quote, so append 1 backslash then space
    // Result: "\ "
    EXPECT_EQ(result, "\"\\ \"");
}

// Test: Multiple backslashes followed by quote
TEST(EscapeArgTest_880, MultipleBackslashesBeforeQuote_880) {
    // Input: \\\" (3 backslashes + quote)
    std::string input = "\\\\\\\"";
    std::string result = escape_arg(input);
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
    // num_backslashes=3 before quote: append (3+1)*2=8 backslashes, then '"', then '"'
    // Result: "\\\\\\\\""" 
    EXPECT_EQ(result, "\"\\\\\\\\\\\\\\\\\"\"\"");
}

// Test: Argument that is just a double quote
TEST(EscapeArgTest_880, JustADoubleQuote_880) {
    std::string result = escape_arg("\"");
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
    // num_backslashes=0 before '"': append (0+1)*2=2 backslashes, '"', '"'
    // Result: "\\""" 
    EXPECT_EQ(result, "\"\\\\\"\"\"");
}

// Test: Normal path-like argument with no special chars
TEST(EscapeArgTest_880, PathLikeNoSpecial_880) {
    std::string result = escape_arg("/usr/bin/gcc");
    EXPECT_EQ(result, "/usr/bin/gcc");
}

// Test: Windows path with spaces
TEST(EscapeArgTest_880, WindowsPathWithSpaces_880) {
    std::string input = "C:\\Program Files\\app";
    std::string result = escape_arg(input);
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
}

// Test: Argument with only backslashes and needs quoting due to embedded space
TEST(EscapeArgTest_880, TrailingBackslashesDoubledWhenQuoted_880) {
    // "test\\" + space: The trailing backslashes should be doubled
    std::string input = "test\\\\ ";
    std::string result = escape_arg(input);
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
}

// Test: Complex mixed input
TEST(EscapeArgTest_880, ComplexMixedInput_880) {
    // A string with spaces, backslashes, and quotes mixed
    std::string input = "a b\\c\"d";
    std::string result = escape_arg(input);
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
    // Verify it contains some form of escaping - the exact output depends on implementation
    EXPECT_GT(result.size(), input.size());
}
