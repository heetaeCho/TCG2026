// File: contains_substring_tests_226.cpp

#include <gtest/gtest.h>
#include <string>

// Catch2 matcher headers (public interface)
#include <catch2/matchers/catch_matchers_string.hpp>

using Catch::CaseSensitive;
using Catch::Matchers::ContainsSubstring;

//
// Normal operation: case-sensitive compare
//
TEST(StringContainsMatcherTest_226, CaseSensitive_MatchAndMismatch_226) {
    auto m = ContainsSubstring("World", CaseSensitive::Yes);

    EXPECT_TRUE(m.match("Hello World!"))    << "Expected to match when exact case substring exists";
    EXPECT_FALSE(m.match("hello world!"))   << "Expected not to match when case differs under CaseSensitive::Yes";
}

//
// Normal operation: case-insensitive compare
//
TEST(StringContainsMatcherTest_226, CaseInsensitive_MatchesDifferentCase_226) {
    auto m = ContainsSubstring("World", CaseSensitive::No);

    EXPECT_TRUE(m.match("hello world!"))    << "Should match regardless of case";
    EXPECT_TRUE(m.match("WORLD-CLASS"))     << "Should match when substring appears in different casing";
    EXPECT_FALSE(m.match("whirled"))        << "Different letters should not match";
}

//
// Boundary coverage: substring at start, middle, end
//
TEST(StringContainsMatcherTest_226, Positions_StartMiddleEnd_226) {
    auto m = ContainsSubstring("cat", CaseSensitive::Yes);

    EXPECT_TRUE(m.match("catapult"))        << "Matches at the beginning";
    EXPECT_TRUE(m.match("concatenate"))     << "Matches in the middle";
    EXPECT_TRUE(m.match("tomcat"))          << "Matches at the end";
}

//
// Boundary coverage: whole string equals the needle
//
TEST(StringContainsMatcherTest_226, WholeStringEqualsNeedle_226) {
    auto m = ContainsSubstring("abc", CaseSensitive::Yes);
    EXPECT_TRUE(m.match("abc"))             << "Exact equality should satisfy 'contains'";
}

//
// Error/edge observable behavior: empty haystack with non-empty needle
//
TEST(StringContainsMatcherTest_226, EmptyHaystack_NoMatchForNonEmptyNeedle_226) {
    auto m = ContainsSubstring("x", CaseSensitive::Yes);
    EXPECT_FALSE(m.match(""))               << "Empty haystack cannot contain a non-empty substring";
}

//
// Description verification: ensure the description surfaces the needle (public API)
//
TEST(StringContainsMatcherTest_226, Describe_IncludesNeedle_226) {
    auto m = ContainsSubstring("Abc", CaseSensitive::No);
    const std::string desc = m.describe();

    EXPECT_FALSE(desc.empty())                       << "Description should be non-empty";
    EXPECT_NE(std::string::npos, desc.find("Abc"))   << "Description should include the requested substring";
    // Note: We intentionally avoid asserting exact wording to not couple tests to internal phrasing.
}
