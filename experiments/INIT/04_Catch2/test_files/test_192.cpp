// tests/any_true_matcher_describe_192_test.cpp
#include <gtest/gtest.h>

// Use the provided header (interface only)
#include "catch2/matchers/catch_matchers_quantifiers.hpp"

using Catch::Matchers::AnyTrueMatcher;

class AnyTrueMatcherTest_192 : public ::testing::Test {};

TEST_F(AnyTrueMatcherTest_192, DescribeReturnsExpected_192) {
    AnyTrueMatcher matcher;
    EXPECT_EQ(matcher.describe(), "contains at least one true");
}

TEST_F(AnyTrueMatcherTest_192, DescribeIsConsistentOnRepeatedCalls_192) {
    const AnyTrueMatcher matcher;
    const std::string first = matcher.describe();
    const std::string second = matcher.describe();

    EXPECT_EQ(first, "contains at least one true");
    EXPECT_EQ(second, "contains at least one true");
    EXPECT_EQ(first, second);
}
