// optional_not_equal_417_tests.cpp
#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "catch2/internal/catch_optional.hpp"

using Catch::Optional;

//
// TEST_ID = 417
//

// Normal operation: equal engaged values => not-equal is false (both directions)
TEST(OptionalNotEqualTest_417, EngagedEqualValuesAreNotNotEqual_417) {
    Optional<int> a{42};
    Optional<int> b{42};

    EXPECT_FALSE(a != b);
    EXPECT_FALSE(b != a);
}

// Normal operation: different engaged values => not-equal is true (both directions)
TEST(OptionalNotEqualTest_417, EngagedDifferentValuesAreNotEqual_417) {
    Optional<int> a{1};
    Optional<int> b{2};

    EXPECT_TRUE(a != b);
    EXPECT_TRUE(b != a);
}

// Boundary: one engaged, one empty => not-equal is true (both directions)
TEST(OptionalNotEqualTest_417, EngagedAndEmptyAreNotEqual_417) {
    Optional<int> engaged{7};
    Optional<int> empty;

    EXPECT_TRUE(engaged != empty);
    EXPECT_TRUE(empty != engaged);
}

// Boundary: both empty => not-equal is false
TEST(OptionalNotEqualTest_417, BothEmptyAreNotNotEqual_417) {
    Optional<int> a;
    Optional<int> b;

    EXPECT_FALSE(a != b);
}

// Sanity: self-comparison should never be not-equal
TEST(OptionalNotEqualTest_417, SelfComparisonIsNotNotEqual_417) {
    Optional<int> a{123};
    EXPECT_FALSE(a != a);

    Optional<int> empty;
    EXPECT_FALSE(empty != empty);
}

// Type coverage: string values with identical content => not-equal is false
TEST(OptionalNotEqualTest_417, StringEngagedEqualContentAreNotNotEqual_417) {
    Optional<std::string> a{std::string("hello")};
    Optional<std::string> b{std::string("hello")};

    EXPECT_FALSE(a != b);
}

// Type coverage: string values with different content => not-equal is true
TEST(OptionalNotEqualTest_417, StringEngagedDifferentContentAreNotEqual_417) {
    Optional<std::string> a{std::string("hello")};
    Optional<std::string> b{std::string("world")};

    EXPECT_TRUE(a != b);
}
