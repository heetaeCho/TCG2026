// File: tests/within_abs_matcher_1049_tests.cpp

#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"

using Catch::Matchers::WithinAbsMatcher;

class WithinAbsMatcherTest_1049 : public ::testing::Test {};

// --- Construction / parameter validation ---

TEST_F(WithinAbsMatcherTest_1049, Construct_NonNegativeMargin_DoesNotThrow_1049) {
    EXPECT_NO_THROW(WithinAbsMatcher(1.23, 0.0));
    EXPECT_NO_THROW(WithinAbsMatcher(1.23, 5.0));
}

TEST_F(WithinAbsMatcherTest_1049, Construct_NegativeMargin_Throws_1049) {
    // The interface enforces non-negative margin; we only assert that an exception is thrown,
    // without depending on the concrete exception type.
    EXPECT_ANY_THROW(WithinAbsMatcher(1.0, -0.001));
}

// --- Matching behavior ---

TEST_F(WithinAbsMatcherTest_1049, Match_ExactTargetWithZeroMargin_True_1049) {
    WithinAbsMatcher m(10.0, 0.0);
    EXPECT_TRUE(m.match(10.0));
    EXPECT_FALSE(m.match(10.000001)); // outside zero margin
}

TEST_F(WithinAbsMatcherTest_1049, Match_WithinMargin_ReturnsTrue_1049) {
    WithinAbsMatcher m(10.0, 2.0);
    EXPECT_TRUE(m.match(11.5));
    EXPECT_TRUE(m.match(8.5));
}

TEST_F(WithinAbsMatcherTest_1049, Match_AtBoundaryMargin_ReturnsTrue_1049) {
    WithinAbsMatcher m(10.0, 2.0);
    EXPECT_TRUE(m.match(12.0)); // exactly +margin
    EXPECT_TRUE(m.match(8.0));  // exactly -margin
}

TEST_F(WithinAbsMatcherTest_1049, Match_JustOutsideMargin_ReturnsFalse_1049) {
    WithinAbsMatcher m(10.0, 2.0);
    EXPECT_FALSE(m.match(12.1));
    EXPECT_FALSE(m.match(7.9));
}

TEST_F(WithinAbsMatcherTest_1049, Match_SymmetricBelowTarget_1049) {
    WithinAbsMatcher m(100.0, 1.0);
    EXPECT_TRUE(m.match(99.1));
    EXPECT_FALSE(m.match(98.9));
}

// --- Description behavior (observable, non-format-specific) ---

TEST_F(WithinAbsMatcherTest_1049, Describe_ReturnsNonEmpty_1049) {
    WithinAbsMatcher m(3.14, 0.01);
    std::string d = m.describe();
    // Do not depend on exact wording/format; just require it to be a non-empty, usable message.
    EXPECT_FALSE(d.empty());
}
