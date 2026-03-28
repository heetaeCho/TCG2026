// File: regex_matcher_describe_tests_224.cpp
#include <gtest/gtest.h>
#include <string>

// Include the provided headers for the class under test.
#include "catch2/catch_case_sensitive.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

using Catch::CaseSensitive;
using Catch::Matchers::RegexMatcher;

class RegexMatcherDescribeTest_224 : public ::testing::Test {};

// Normal operation: case-sensitive suffix should be present.
TEST_F(RegexMatcherDescribeTest_224, Describe_AppendsCaseSensitiveSuffix_224) {
    const std::string pattern = "^[A-Z]+$";
    RegexMatcher matcher(pattern, CaseSensitive::Yes);

    const std::string desc = matcher.describe();

    // Must contain the fixed prefix and the correct sensitivity suffix.
    ASSERT_NE(desc.find("matches "), std::string::npos);
    ASSERT_NE(desc.find("case sensitively"), std::string::npos);

    // The description should contain the pattern (stringified); we only
    // assert that the raw pattern appears as a substring to avoid depending
    // on exact stringify formatting.
    ASSERT_NE(desc.find("A-Z"), std::string::npos);
}

// Normal operation: case-insensitive suffix should be present.
TEST_F(RegexMatcherDescribeTest_224, Describe_AppendsCaseInsensitiveSuffix_224) {
    const std::string pattern = "(?i)abc.*";
    RegexMatcher matcher(pattern, CaseSensitive::No);

    const std::string desc = matcher.describe();

    ASSERT_NE(desc.find("matches "), std::string::npos);
    ASSERT_NE(desc.find("case insensitively"), std::string::npos);
    ASSERT_NE(desc.find("abc"), std::string::npos);
}

// Boundary: empty regex pattern should still yield a well-formed description.
TEST_F(RegexMatcherDescribeTest_224, Describe_HandlesEmptyPattern_224) {
    const std::string pattern; // empty
    RegexMatcher matcher(pattern, CaseSensitive::Yes);

    const std::string desc = matcher.describe();

    // Still must have the fixed pieces; we don't assume how empty is stringified.
    ASSERT_NE(desc.find("matches "), std::string::npos);
    ASSERT_NE(desc.find("case sensitively"), std::string::npos);
    // Description should not be an empty string.
    ASSERT_FALSE(desc.empty());
}

// Boundary: special regex metacharacters should not break the description string.
TEST_F(RegexMatcherDescribeTest_224, Describe_IncludesMetacharactersSafely_224) {
    const std::string pattern = R"((^\d{3}\.\d{3}\.\d{3}\.\d{3}$)|(\w+\@\w+\.\w+))";
    RegexMatcher matcher(pattern, CaseSensitive::No);

    const std::string desc = matcher.describe();

    ASSERT_NE(desc.find("matches "), std::string::npos);
    ASSERT_NE(desc.find("case insensitively"), std::string::npos);
    // Spot-check a couple of distinctive substrings from the pattern.
    ASSERT_NE(desc.find(R"(\d{3}\.)"), std::string::npos);
    ASSERT_NE(desc.find(R"(\w+\@)"), std::string::npos);
}

// Robustness: very long pattern still yields a description containing prefix/suffix.
TEST_F(RegexMatcherDescribeTest_224, Describe_SupportsLongPatterns_224) {
    std::string pattern(1024, 'a'); // 1KB of 'a'
    RegexMatcher matcher(pattern, CaseSensitive::Yes);

    const std::string desc = matcher.describe();

    ASSERT_NE(desc.find("matches "), std::string::npos);
    ASSERT_NE(desc.find("case sensitively"), std::string::npos);
    // Ensure at least a chunk of the long pattern appears.
    ASSERT_NE(desc.find(std::string(16, 'a')), std::string::npos);
}
