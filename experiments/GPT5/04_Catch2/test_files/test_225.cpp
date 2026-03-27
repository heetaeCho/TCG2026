// equals_matcher_tests_225.cpp
#include <gtest/gtest.h>
#include <string>

// Catch2 matcher interface under test
#include <catch2/matchers/catch_matchers_string.hpp>

using Catch::Matchers::Equals;
using Catch::CaseSensitive;

//
// Normal operation: exact match with case sensitivity enabled
//
TEST(EqualsMatcherTest_225, MatchesExactly_WhenCaseSensitiveYes_225) {
    auto matcher = Equals(std::string("Hello World"), CaseSensitive::Yes);
    EXPECT_TRUE(matcher.match(std::string("Hello World")));
}

//
// Normal operation: case difference should fail when case sensitive
//
TEST(EqualsMatcherTest_225, FailsOnCaseDifference_WhenCaseSensitiveYes_225) {
    auto matcher = Equals(std::string("Hello"), CaseSensitive::Yes);
    EXPECT_FALSE(matcher.match(std::string("hello")));
}

//
// Normal operation: case-insensitive compare should match regardless of case
//
TEST(EqualsMatcherTest_225, MatchesIgnoringCase_WhenCaseSensitiveNo_225) {
    auto matcher = Equals(std::string("TeStInG"), CaseSensitive::No);
    EXPECT_TRUE(matcher.match(std::string("testing")));
    EXPECT_TRUE(matcher.match(std::string("TESTING")));
    EXPECT_TRUE(matcher.match(std::string("TeStInG")));
}

//
// Boundary condition: empty string comparisons
//
TEST(EqualsMatcherTest_225, EmptyStringMatchesOnlyEmptyString_225) {
    auto cs_yes = Equals(std::string(""), CaseSensitive::Yes);
    auto cs_no  = Equals(std::string(""), CaseSensitive::No);

    EXPECT_TRUE(cs_yes.match(std::string("")));
    EXPECT_FALSE(cs_yes.match(std::string(" ")));   // non-empty different

    EXPECT_TRUE(cs_no.match(std::string("")));
    EXPECT_FALSE(cs_no.match(std::string(" ")));
}

//
// Non-match cases: different lengths / minor differences should fail
//
TEST(EqualsMatcherTest_225, FailsOnDifferentContentOrLength_225) {
    auto matcher_cs_yes = Equals(std::string("abc"), CaseSensitive::Yes);
    auto matcher_cs_no  = Equals(std::string("abc"), CaseSensitive::No);

    // One character off
    EXPECT_FALSE(matcher_cs_yes.match(std::string("ab")));
    EXPECT_FALSE(matcher_cs_yes.match(std::string("abcd")));
    EXPECT_FALSE(matcher_cs_yes.match(std::string("abx")));

    // Even in case-insensitive mode, different content should fail
    EXPECT_FALSE(matcher_cs_no.match(std::string("abx")));
    EXPECT_FALSE(matcher_cs_no.match(std::string("abcd")));
}

//
// Optional: description should be present (observable text, not format-specific)
//
TEST(EqualsMatcherTest_225, HasNonEmptyDescription_225) {
    auto matcher = Equals(std::string("needle"), CaseSensitive::Yes);
    const std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}
