// File: tests/coverage_helper_escape_arg_880_tests.cpp

#include <gtest/gtest.h>
#include <string>

// Forward declaration from Catch2/tools/misc/coverage-helper.cpp
// (Function is in the global namespace per the provided snippet.)
std::string escape_arg(const std::string& arg);

class EscapeArgTest_880 : public ::testing::Test {};

// [Normal] No whitespace or quotes -> returned unchanged
TEST_F(EscapeArgTest_880, ReturnsUnchangedWhenNoSpacesOrQuotes_880) {
    EXPECT_EQ(escape_arg("abc"), "abc");
    EXPECT_EQ(escape_arg("C:\\path\\file"), "C:\\path\\file"); // backslashes alone should not trigger quoting
}

// [Boundary] Empty string -> becomes quoted empty string
TEST_F(EscapeArgTest_880, EmptyStringBecomesQuotedEmpty_880) {
    EXPECT_EQ(escape_arg(""), "\"\"");
}

// [Normal] Contains whitespace -> becomes quoted (simple case)
TEST_F(EscapeArgTest_880, StringWithSpaceIsQuoted_880) {
    EXPECT_EQ(escape_arg("a b"), "\"a b\"");
}

// [Boundary] Contains control whitespace (tab/newline/vtab) -> becomes quoted
TEST_F(EscapeArgTest_880, StringWithTabNewlineVTabIsQuoted_880) {
    EXPECT_EQ(escape_arg("a\tb"), "\"a\tb\"");
    EXPECT_EQ(escape_arg("a\nb"), "\"a\nb\"");
    EXPECT_EQ(escape_arg(std::string("a\vb")), "\"a\vb\"");
}

// [Edge] Trailing backslashes with quoting required -> trailing backslashes are doubled inside quotes
// Input contains a space (forces quoting) and ends with backslashes.
TEST_F(EscapeArgTest_880, TrailingBackslashesAreDoubledWhenQuoted_880) {
    // "path with space\\" -> inside quotes, trailing "\\" must become "\\\\"
    const std::string in  = "path with space\\\\";
    const std::string out = "\"path with space\\\\\\\\\"";
    EXPECT_EQ(escape_arg(in), out);
}

// [Edge] Embedded double quote: verify escaping pattern produced by the implementation
TEST_F(EscapeArgTest_880, EmbeddedDoubleQuoteEscapingPattern_880) {
    // Input: say"hi
    // Based on the provided implementation, an embedded `"` leads to:
    // - prepend (num_backslashes + 1) * 2 backslashes (here 2),
    // - then append a quote twice.
    // So expected inside the outer quotes: say\\\"\"hi
    const std::string in  = "say\"hi";
    const std::string out = "\"say\\\\\\\"\\\"hi\"";
    EXPECT_EQ(escape_arg(in), out);
}
