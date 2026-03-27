// StartsWithMatcher_tests_228.cpp
#include <gtest/gtest.h>
#include <string>

// Catch2 matcher interface header
#include <catch2/matchers/catch_matchers_string.hpp>

using Catch::Matchers::StartsWith;
using Catch::CaseSensitive;

class StartsWithMatcherTest_228 : public ::testing::Test {};

// [Normal] Case-sensitive: matches when prefix is at the start
TEST_F(StartsWithMatcherTest_228, CaseSensitiveYes_MatchAtStart_228) {
    auto m = StartsWith("abc", CaseSensitive::Yes);
    EXPECT_TRUE(m.match(std::string("abcdef")));
}

// [Negative] Case-sensitive: does NOT match when prefix occurs later
TEST_F(StartsWithMatcherTest_228, CaseSensitiveYes_NotAtStart_228) {
    auto m = StartsWith("abc", CaseSensitive::Yes);
    EXPECT_FALSE(m.match(std::string("zabc")));
}

// [Normal] Case-insensitive: matches regardless of case when at the start
TEST_F(StartsWithMatcherTest_228, CaseInsensitive_MatchDifferentCase_228) {
    auto m = StartsWith("AbC", CaseSensitive::No);
    EXPECT_TRUE(m.match(std::string("aBcdef")));
}

// [Boundary] Empty pattern: should match any string (including empty)
TEST_F(StartsWithMatcherTest_228, EmptyPattern_MatchesAnyString_228) {
    auto m = StartsWith("", CaseSensitive::Yes);
    EXPECT_TRUE(m.match(std::string("anything")));
    EXPECT_TRUE(m.match(std::string("")));
}

// [Boundary] Exact match: whole string equals the prefix
TEST_F(StartsWithMatcherTest_228, ExactMatch_EqualsPrefix_228) {
    auto m = StartsWith("abc", CaseSensitive::Yes);
    EXPECT_TRUE(m.match(std::string("abc")));
}

// [Boundary/Negative] Empty target: non-empty prefix cannot match
TEST_F(StartsWithMatcherTest_228, EmptyTarget_NonEmptyPrefix_False_228) {
    auto m = StartsWith("a", CaseSensitive::Yes);
    EXPECT_FALSE(m.match(std::string("")));
}

// [Describe] The description should mention the expected prefix (observable text)
TEST_F(StartsWithMatcherTest_228, Describe_IncludesPattern_228) {
    auto m = StartsWith("AbC", CaseSensitive::No);
    const std::string desc = m.describe();
    // Only assert observable inclusion of the pattern (avoid relying on exact phrasing)
    ASSERT_NE(desc.find("AbC"), std::string::npos);
}
