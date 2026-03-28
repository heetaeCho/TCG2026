// EndsWithMatcher_tests_222.cpp
#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_string.hpp"

using namespace Catch::Matchers;

class EndsWithMatcherTest_222 : public ::testing::Test {
protected:
    // Helper to build an EndsWithMatcher with desired case sensitivity
    static EndsWithMatcher MakeMatcher(const std::string& needle,
                                       CaseSensitive cs = CaseSensitive::Yes) {
        CasedString cmp(needle, cs);
        return EndsWithMatcher(cmp);
    }
};

// --- Normal operation ---

TEST_F(EndsWithMatcherTest_222, ReturnsTrueWhenSourceEndsWithNeedle_222) {
    auto m = EndsWithMatcherTest_222::MakeMatcher("cd", CaseSensitive::Yes);
    EXPECT_TRUE(m.match("abcd"));
}

TEST_F(EndsWithMatcherTest_222, ReturnsFalseWhenSourceDoesNotEndWithNeedle_222) {
    auto m = EndsWithMatcherTest_222::MakeMatcher("ab", CaseSensitive::Yes);
    EXPECT_FALSE(m.match("abcd"));
}

// --- Case sensitivity ---

TEST_F(EndsWithMatcherTest_222, RespectsCaseSensitivityWhenEnabled_222) {
    auto m = EndsWithMatcherTest_222::MakeMatcher("CD", CaseSensitive::Yes);
    EXPECT_FALSE(m.match("abcd"));   // different case -> should not match
}

TEST_F(EndsWithMatcherTest_222, IgnoresCaseWhenCaseInsensitive_222) {
    auto m = EndsWithMatcherTest_222::MakeMatcher("CD", CaseSensitive::No);
    EXPECT_TRUE(m.match("abcd"));    // case-insensitive -> should match
}

// --- Boundary conditions ---

TEST_F(EndsWithMatcherTest_222, WholeStringMatchReturnsTrue_222) {
    auto m = EndsWithMatcherTest_222::MakeMatcher("abcd", CaseSensitive::Yes);
    EXPECT_TRUE(m.match("abcd"));
}

TEST_F(EndsWithMatcherTest_222, NeedleLongerThanSourceReturnsFalse_222) {
    auto m = EndsWithMatcherTest_222::MakeMatcher("abcdef", CaseSensitive::Yes);
    EXPECT_FALSE(m.match("abc"));
}

TEST_F(EndsWithMatcherTest_222, EmptyNeedleMatchesEndOfNonEmptySource_222) {
    auto m = EndsWithMatcherTest_222::MakeMatcher("", CaseSensitive::Yes);
    EXPECT_TRUE(m.match("anything"));
}

TEST_F(EndsWithMatcherTest_222, EmptySourceAndEmptyNeedleBoundary_222) {
    auto m = EndsWithMatcherTest_222::MakeMatcher("", CaseSensitive::Yes);
    EXPECT_TRUE(m.match("")); // Observable end-with-empty behavior
}

TEST_F(EndsWithMatcherTest_222, EmptySourceWithNonEmptyNeedleReturnsFalse_222) {
    auto m = EndsWithMatcherTest_222::MakeMatcher("x", CaseSensitive::Yes);
    EXPECT_FALSE(m.match(""));
}
