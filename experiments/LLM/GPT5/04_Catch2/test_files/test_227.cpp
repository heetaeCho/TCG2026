// File: ends_with_matcher_test_227.cpp

#include <gtest/gtest.h>
#include <string>

// Catch2 matchers interface under test
#include <catch2/matchers/catch_matchers_string.hpp>

using Catch::CaseSensitive;
using Catch::Matchers::EndsWith;

class EndsWithMatcherTest_227 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(EndsWithMatcherTest_227, Match_SucceedsOnValidSuffix_227) {
    auto m = EndsWith("world", CaseSensitive::Yes);
    EXPECT_TRUE(m.match(std::string("hello world")));
}

TEST_F(EndsWithMatcherTest_227, Match_FailsWhenNotASuffix_227) {
    auto m = EndsWith("world", CaseSensitive::Yes);
    EXPECT_FALSE(m.match(std::string("worldwide")));
    EXPECT_FALSE(m.match(std::string("hello worl")));
}

// --- Case sensitivity options ---

TEST_F(EndsWithMatcherTest_227, Match_CaseSensitive_FailsOnDifferentCase_227) {
    auto m = EndsWith("World", CaseSensitive::Yes);
    EXPECT_FALSE(m.match(std::string("hello world")));
}

TEST_F(EndsWithMatcherTest_227, Match_CaseInsensitive_SucceedsOnDifferentCase_227) {
    auto m = EndsWith("WoRLd", CaseSensitive::No);
    EXPECT_TRUE(m.match(std::string("hello world")));
}

// --- Boundary conditions ---

TEST_F(EndsWithMatcherTest_227, Boundary_ExactMatch_227) {
    auto m = EndsWith("abc", CaseSensitive::Yes);
    EXPECT_TRUE(m.match(std::string("abc")));
}

TEST_F(EndsWithMatcherTest_227, Boundary_EmptySuffix_MatchesAnyString_227) {
    auto m = EndsWith("", CaseSensitive::Yes);
    EXPECT_TRUE(m.match(std::string("anything")));
    EXPECT_TRUE(m.match(std::string("")));
}

TEST_F(EndsWithMatcherTest_227, Boundary_EmptyHaystackWithNonEmptySuffix_Fails_227) {
    auto m = EndsWith("x", CaseSensitive::Yes);
    EXPECT_FALSE(m.match(std::string("")));
}

// --- Description (observable text output) ---

TEST_F(EndsWithMatcherTest_227, Describe_IncludesEndsWithAndNeedle_227) {
    const std::string needle = "xyz";
    auto m = EndsWith(needle, CaseSensitive::Yes);
    const std::string desc = m.describe();

    // Avoid depending on exact wording/formatting; just check key parts.
    EXPECT_NE(desc.find("ends"), std::string::npos);
    EXPECT_NE(desc.find("with"), std::string::npos);
    EXPECT_NE(desc.find(needle), std::string::npos);
}
