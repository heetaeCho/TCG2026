// File: tests/all_true_matcher_test_188.cpp

#include <gtest/gtest.h>
#include <string>

// Include the public header that declares AllTrueMatcher
#include "catch2/matchers/catch_matchers_quantifiers.hpp"

using Catch::Matchers::AllTrueMatcher;

class AllTrueMatcherTest_188 : public ::testing::Test {};

// Verifies the user-visible description string returned by describe()
TEST_F(AllTrueMatcherTest_188, DescribeReturnsExactMessage_188) {
    AllTrueMatcher matcher;
    EXPECT_EQ(matcher.describe(), "contains only true");
}

// Calling describe() repeatedly should yield the same (stable) text
TEST_F(AllTrueMatcherTest_188, DescribeIsIdempotent_188) {
    AllTrueMatcher matcher;
    const std::string first = matcher.describe();
    const std::string second = matcher.describe();
    const std::string third = matcher.describe();

    EXPECT_EQ(first, "contains only true");
    EXPECT_EQ(second, "contains only true");
    EXPECT_EQ(third, "contains only true");
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

// describe() must be callable on a const instance (interface stability)
TEST_F(AllTrueMatcherTest_188, DescribeWorksWithConstInstance_188) {
    const AllTrueMatcher matcher;
    const std::string desc = matcher.describe();

    EXPECT_FALSE(desc.empty());
    EXPECT_EQ(desc, "contains only true");
}

// Basic sanity: describe() returns a non-empty, human-readable phrase
TEST_F(AllTrueMatcherTest_188, DescribeNonEmptyHumanReadable_188) {
    AllTrueMatcher matcher;
    const std::string desc = matcher.describe();

    EXPECT_FALSE(desc.empty());
    // Avoid over-specifying formatting; just ensure it has spaces (human-readable phrase)
    EXPECT_NE(desc.find(' '), std::string::npos);
}
