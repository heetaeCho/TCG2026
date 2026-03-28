// File: string_equals_matcher_tests_219.cpp

#include <gtest/gtest.h>
#include "catch2/matchers/catch_matchers_string.hpp"

using Catch::Matchers::CasedString;
using Catch::Matchers::StringEqualsMatcher;

namespace {

TEST(StringEqualsMatcher_219, ExactMatch_CaseSensitive_219) {
    // Normal path: identical strings should match when case sensitive
    CasedString cmp("Hello World", CaseSensitive::Yes);
    StringEqualsMatcher matcher(cmp);

    EXPECT_TRUE(matcher.match("Hello World"));
}

TEST(StringEqualsMatcher_219, CaseDiff_Fails_WhenCaseSensitive_219) {
    // Negative path: different letter casing should NOT match when case sensitive
    CasedString cmp("Hello", CaseSensitive::Yes);
    StringEqualsMatcher matcher(cmp);

    EXPECT_FALSE(matcher.match("hello"));
}

TEST(StringEqualsMatcher_219, CaseDiff_Matches_WhenCaseInsensitive_219) {
    // Normal path for case-insensitive behavior: different casing should be considered equal
    CasedString cmp("Hello", CaseSensitive::No);
    StringEqualsMatcher matcher(cmp);

    EXPECT_TRUE(matcher.match("hELLo"));
}

TEST(StringEqualsMatcher_219, EmptyStrings_Match_219) {
    // Boundary: empty vs empty should match
    CasedString cmp("", CaseSensitive::Yes);
    StringEqualsMatcher matcher(cmp);

    EXPECT_TRUE(matcher.match(""));
}

TEST(StringEqualsMatcher_219, EmptyVsNonEmpty_Fails_219) {
    // Negative boundary: empty vs non-empty should not match (both sensitivities)
    {
        CasedString cmp("", CaseSensitive::Yes);
        StringEqualsMatcher matcher(cmp);
        EXPECT_FALSE(matcher.match("a"));
    }
    {
        CasedString cmp("", CaseSensitive::No);
        StringEqualsMatcher matcher(cmp);
        EXPECT_FALSE(matcher.match("A"));
    }
}

TEST(StringEqualsMatcher_219, VeryLongString_Matches_IfIdentical_219) {
    // Boundary: large input
    const std::string big(10000, 'x');  // 10k 'x'
    CasedString cmp(big, CaseSensitive::Yes);
    StringEqualsMatcher matcher(cmp);

    EXPECT_TRUE(matcher.match(big));
}

TEST(StringEqualsMatcher_219, VeryLongString_Fails_WhenDifferent_219) {
    // Boundary negative: same length but one char differs
    std::string a(5000, 'a');
    a += std::string(5000, 'b');  // 10k chars
    std::string b = a;
    b[9999] = 'c'; // differ at last character

    CasedString cmp(a, CaseSensitive::Yes);
    StringEqualsMatcher matcher(cmp);

    EXPECT_FALSE(matcher.match(b));
}

TEST(StringEqualsMatcher_219, MixedWhitespace_RespectsExactness_WhenCaseSensitive_219) {
    // Negative path: strings that differ in whitespace should not match under exact (case-sensitive) comparison
    // (We do NOT assume trimming or normalization; we only check observable mismatch.)
    CasedString cmp("value", CaseSensitive::Yes);
    StringEqualsMatcher matcher(cmp);

    EXPECT_FALSE(matcher.match("value "));
    EXPECT_FALSE(matcher.match(" value"));
    EXPECT_FALSE(matcher.match("val ue"));
}

} // namespace
