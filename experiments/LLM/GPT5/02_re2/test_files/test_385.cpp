#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"
#include "re2/filtered_re2.h"
#include "re2/set.h"

// Declare the function under test.
void TestOneInput(absl::string_view pattern,
                  const RE2::Options& options,
                  RE2::Anchor anchor,
                  absl::string_view text);

// ---------------- Test Fixture ----------------
class Re2FuzzerTest_385 : public ::testing::Test {
protected:
    RE2::Options default_options;
};

// ---------------- Test Cases ----------------

// Normal operation: simple literal pattern, no capture groups.
TEST_F(Re2FuzzerTest_385, LiteralPatternNoCapture_385) {
    std::string pattern = "abc";
    std::string text = "abc";
    EXPECT_NO_THROW({
        TestOneInput(pattern, default_options, RE2::UNANCHORED, text);
    });
}

// Normal operation: pattern with a capturing group.
TEST_F(Re2FuzzerTest_385, PatternWithCapturingGroup_385) {
    std::string pattern = "(abc)";
    std::string text = "zzzabczzz";
    EXPECT_NO_THROW({
        TestOneInput(pattern, default_options, RE2::UNANCHORED, text);
    });
}

// Boundary condition: empty pattern.
TEST_F(Re2FuzzerTest_385, EmptyPattern_385) {
    std::string pattern = "";
    std::string text = "some text";
    EXPECT_NO_THROW({
        TestOneInput(pattern, default_options, RE2::UNANCHORED, text);
    });
}

// Boundary condition: empty text.
TEST_F(Re2FuzzerTest_385, EmptyText_385) {
    std::string pattern = "abc";
    std::string text = "";
    EXPECT_NO_THROW({
        TestOneInput(pattern, default_options, RE2::UNANCHORED, text);
    });
}

// Exceptional case: invalid regex pattern.
TEST_F(Re2FuzzerTest_385, InvalidPattern_385) {
    std::string pattern = "(abc";  // Unbalanced parenthesis
    std::string text = "abc";
    EXPECT_NO_THROW({
        TestOneInput(pattern, default_options, RE2::UNANCHORED, text);
    });
}

// Test pattern with escaped character classes and backslash-p (unicode property).
TEST_F(Re2FuzzerTest_385, PatternWithEscapedAndBackslashP_385) {
    std::string pattern = "\\d+\\p{L}";
    std::string text = "123a";
    EXPECT_NO_THROW({
        TestOneInput(pattern, default_options, RE2::UNANCHORED, text);
    });
}

// Test with RE2::ANCHOR_BOTH (boundary condition on anchor type).
TEST_F(Re2FuzzerTest_385, AnchoredMatch_385) {
    std::string pattern = "abc";
    std::string text = "abc";
    EXPECT_NO_THROW({
        TestOneInput(pattern, default_options, RE2::ANCHOR_BOTH, text);
    });
}

// Test with large but valid pattern and text.
TEST_F(Re2FuzzerTest_385, LargePatternAndText_385) {
    std::string pattern(50, 'a');  // "aaaa...."
    std::string text(200, 'a');
    EXPECT_NO_THROW({
        TestOneInput(pattern, default_options, RE2::UNANCHORED, text);
    });
}

// Test with pattern triggering replacement and global replace paths.
TEST_F(Re2FuzzerTest_385, ReplaceAndGlobalReplace_385) {
    std::string pattern = "x+";
    std::string text = "xxxyyyxxx";
    EXPECT_NO_THROW({
        TestOneInput(pattern, default_options, RE2::UNANCHORED, text);
    });
}

// Test with special characters that require quoting.
TEST_F(Re2FuzzerTest_385, QuoteMetaPattern_385) {
    std::string pattern = "a.c*";
    std::string text = "abc";
    EXPECT_NO_THROW({
        TestOneInput(pattern, default_options, RE2::UNANCHORED, text);
    });
}
