// File: within_abs_matcher_test_197.cpp
#include <gtest/gtest.h>

// Include the public interface under test.
// Adjust the include path if your project layout differs.
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using Catch::Matchers::WithinAbsMatcher;

class WithinAbsMatcherTest_197 : public ::testing::Test {};

// --- Normal operation ---

// Exact equality should match when the value equals the target.
TEST_F(WithinAbsMatcherTest_197, ExactMatchReturnsTrue_197) {
    const double target = 10.0;
    const double margin = 0.5;
    WithinAbsMatcher matcher(target, margin);

    EXPECT_TRUE(matcher.match(target));
}

// Value slightly above the target but within the margin should match.
TEST_F(WithinAbsMatcherTest_197, WithinUpperMarginReturnsTrue_197) {
    const double target = 100.0;
    const double margin = 1.0;
    WithinAbsMatcher matcher(target, margin);

    EXPECT_TRUE(matcher.match(100.8));
}

// Value slightly below the target but within the margin should match.
TEST_F(WithinAbsMatcherTest_197, WithinLowerMarginReturnsTrue_197) {
    const double target = -5.0;
    const double margin = 0.25;
    WithinAbsMatcher matcher(target, margin);

    EXPECT_TRUE(matcher.match(-5.2 + 0.2)); // -5.0 within margin
}

// --- Boundary conditions ---

// Exactly on the upper boundary (target + margin) should match.
TEST_F(WithinAbsMatcherTest_197, OnUpperBoundaryReturnsTrue_197) {
    const double target = 0.0;
    const double margin = 1.25;
    WithinAbsMatcher matcher(target, margin);

    EXPECT_TRUE(matcher.match(target + margin));
}

// Exactly on the lower boundary (target - margin) should match.
TEST_F(WithinAbsMatcherTest_197, OnLowerBoundaryReturnsTrue_197) {
    const double target = 42.0;
    const double margin = 0.001;
    WithinAbsMatcher matcher(target, margin);

    EXPECT_TRUE(matcher.match(target - margin));
}

// Just outside the upper boundary should not match.
TEST_F(WithinAbsMatcherTest_197, JustOutsideUpperBoundaryReturnsFalse_197) {
    const double target = 1.0;
    const double margin = 0.1;
    WithinAbsMatcher matcher(target, margin);

    EXPECT_FALSE(matcher.match(target + margin + 1e-12));
}

// Just outside the lower boundary should not match.
TEST_F(WithinAbsMatcherTest_197, JustOutsideLowerBoundaryReturnsFalse_197) {
    const double target = -2.0;
    const double margin = 0.5;
    WithinAbsMatcher matcher(target, margin);

    EXPECT_FALSE(matcher.match(target - margin - 1e-12));
}

// Zero margin: only exact target should match.
TEST_F(WithinAbsMatcherTest_197, ZeroMarginExactMatchTrue_197) {
    const double target = 3.14159;
    const double margin = 0.0;
    WithinAbsMatcher matcher(target, margin);

    EXPECT_TRUE(matcher.match(target));
}

TEST_F(WithinAbsMatcherTest_197, ZeroMarginNearbyValueFalse_197) {
    const double target = 3.14159;
    const double margin = 0.0;
    WithinAbsMatcher matcher(target, margin);

    EXPECT_FALSE(matcher.match(target + std::numeric_limits<double>::epsilon()));
}

// --- Exceptional / special floating cases (observable through interface) ---

// NaN comparisons are not equal; verify observable behavior remains false.
TEST_F(WithinAbsMatcherTest_197, NaNMatcheeReturnsFalse_197) {
    const double target = 0.0;
    const double margin = 10.0;
    WithinAbsMatcher matcher(target, margin);

    const double nanVal = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(matcher.match(nanVal));
}

// Infinite values: only match if they are within the defined margin behavior.
TEST_F(WithinAbsMatcherTest_197, InfiniteValuesBehavior_197) {
    const double target = 1e9;
    const double margin = 1e3;
    WithinAbsMatcher matcher(target, margin);

    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(matcher.match(-std::numeric_limits<double>::infinity()));
}

// Symmetric distances around the target should yield the same observable result.
TEST_F(WithinAbsMatcherTest_197, SymmetricDistancesHaveSameResult_197) {
    const double target = 10.0;
    const double margin = 0.25;
    WithinAbsMatcher matcher(target, margin);

    const double d = 0.2;
    EXPECT_TRUE(matcher.match(target + d));
    EXPECT_TRUE(matcher.match(target - d));

    const double outside = 0.3000001;
    EXPECT_FALSE(matcher.match(target + outside));
    EXPECT_FALSE(matcher.match(target - outside));
}
