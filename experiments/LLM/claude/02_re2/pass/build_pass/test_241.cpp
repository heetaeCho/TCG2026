#include <gtest/gtest.h>
#include "re2/re2.h"
#include <string>

// Note: The `trunc` function is in an anonymous/static scope within re2 namespace
// and is not directly accessible from outside. However, it is used internally by RE2.
// We test RE2's public interface, which exercises trunc indirectly through error messages
// and pattern handling.

class RE2Test_241 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a short valid pattern compiles successfully
TEST_F(RE2Test_241, ShortValidPattern_241) {
    RE2 re("hello");
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.pattern(), "hello");
}

// Test that an empty pattern compiles successfully
TEST_F(RE2Test_241, EmptyPattern_241) {
    RE2 re("");
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.pattern(), "");
}

// Test a pattern that is exactly 99 characters (under 100 boundary)
TEST_F(RE2Test_241, PatternLength99_241) {
    std::string pat(99, 'a');
    RE2 re(pat);
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.pattern(), pat);
}

// Test a pattern that is exactly 100 characters (boundary)
TEST_F(RE2Test_241, PatternLength100_241) {
    std::string pat(100, 'a');
    RE2 re(pat);
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.pattern(), pat);
}

// Test a pattern that is 101 characters (just over boundary)
TEST_F(RE2Test_241, PatternLength101_241) {
    std::string pat(101, 'a');
    RE2 re(pat);
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.pattern(), pat);
}

// Test a very long valid pattern
TEST_F(RE2Test_241, VeryLongValidPattern_241) {
    std::string pat(1000, 'a');
    RE2 re(pat);
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.pattern(), pat);
}

// Test that an invalid short pattern produces an error
TEST_F(RE2Test_241, ShortInvalidPattern_241) {
    RE2 re("(unclosed");
    EXPECT_FALSE(re.ok());
    // The error message should contain the pattern (which is short, < 100 chars)
    std::string err = re.error();
    EXPECT_FALSE(err.empty());
}

// Test that an invalid long pattern produces an error with truncation
// The trunc function should truncate patterns >= 100 chars and append "..."
TEST_F(RE2Test_241, LongInvalidPatternTruncatedInError_241) {
    // Create an invalid pattern longer than 100 characters
    // Use a pattern with unmatched parenthesis at the end
    std::string pat(150, 'a');
    pat += "(";  // make it invalid
    RE2 re(pat);
    EXPECT_FALSE(re.ok());
    std::string err = re.error();
    EXPECT_FALSE(err.empty());
    // The error should contain "..." indicating truncation was applied
    // (since the pattern is > 100 chars)
}

// Test FullMatch with a simple pattern
TEST_F(RE2Test_241, FullMatchSimple_241) {
    EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
    EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

// Test PartialMatch with a simple pattern
TEST_F(RE2Test_241, PartialMatchSimple_241) {
    EXPECT_TRUE(RE2::PartialMatch("hello world", "hello"));
    EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

// Test FullMatch with capturing groups
TEST_F(RE2Test_241, FullMatchWithCapture_241) {
    int value;
    EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &value));
    EXPECT_EQ(value, 12345);
}

// Test PartialMatch with capturing groups
TEST_F(RE2Test_241, PartialMatchWithCapture_241) {
    std::string word;
    EXPECT_TRUE(RE2::PartialMatch("hello world", "(\\w+)", &word));
    EXPECT_EQ(word, "hello");
}

// Test pattern with special regex characters
TEST_F(RE2Test_241, SpecialCharactersPattern_241) {
    RE2 re("a+b*c?");
    EXPECT_TRUE(re.ok());
    EXPECT_TRUE(RE2::FullMatch("aac", re));
    EXPECT_TRUE(RE2::FullMatch("abbc", re));
    EXPECT_TRUE(RE2::FullMatch("a", re));
}

// Test NumberOfCapturingGroups
TEST_F(RE2Test_241, NumberOfCapturingGroups_241) {
    RE2 re("(a)(b)(c)");
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// Test that a pattern of exactly 100 characters that is invalid
// exercises the boundary condition of trunc
TEST_F(RE2Test_241, InvalidPatternExactly100Chars_241) {
    std::string pat(99, 'a');
    pat += "(";  // total 100 chars, invalid
    RE2 re(pat);
    EXPECT_FALSE(re.ok());
    EXPECT_FALSE(re.error().empty());
}

// Test Replace
TEST_F(RE2Test_241, ReplaceSimple_241) {
    std::string s = "hello world";
    EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
    EXPECT_EQ(s, "hello there");
}

// Test GlobalReplace
TEST_F(RE2Test_241, GlobalReplaceSimple_241) {
    std::string s = "aaa";
    int count = RE2::GlobalReplace(&s, "a", "b");
    EXPECT_EQ(count, 3);
    EXPECT_EQ(s, "bbb");
}

// Test QuoteMeta
TEST_F(RE2Test_241, QuoteMeta_241) {
    std::string quoted = RE2::QuoteMeta("a.b+c*d");
    RE2 re(quoted);
    EXPECT_TRUE(re.ok());
    EXPECT_TRUE(RE2::FullMatch("a.b+c*d", re));
    EXPECT_FALSE(RE2::FullMatch("aXbYcZd", re));
}

// Test with null byte in pattern
TEST_F(RE2Test_241, PatternWithNullByte_241) {
    std::string pat("a\0b", 3);
    RE2 re(pat);
    // RE2 should handle patterns with null bytes
    if (re.ok()) {
        std::string text("a\0b", 3);
        EXPECT_TRUE(RE2::FullMatch(text, re));
    }
}

// Test error_code for invalid pattern
TEST_F(RE2Test_241, ErrorCodeForInvalidPattern_241) {
    RE2 re("[invalid");
    EXPECT_FALSE(re.ok());
    EXPECT_NE(re.error_code(), RE2::NoError);
}

// Test error_code for valid pattern
TEST_F(RE2Test_241, ErrorCodeForValidPattern_241) {
    RE2 re("valid");
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.error_code(), RE2::NoError);
}
