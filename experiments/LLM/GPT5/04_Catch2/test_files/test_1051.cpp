// File: tests/WithinRelMatcherTests_1051.cpp

#include <gtest/gtest.h>
#include <limits>
#include <type_traits>
#include <cmath>

// Headers under test (paths follow the Partial Code)
#include "Catch2/src/catch2/matchers/catch_matchers_floating_point.hpp"
#include "Catch2/src/catch2/matchers/catch_matchers.hpp"

using Catch::Matchers::WithinRelMatcher;
using Catch::Matchers::MatcherBase;

class WithinRelMatcherTest_1051 : public ::testing::Test {};

// --- Type relationship smoke test ---
TEST_F(WithinRelMatcherTest_1051, InheritsFromMatcherBaseDouble_1051) {
    // Compile-time + runtime check that WithinRelMatcher models a MatcherBase<double>
    EXPECT_TRUE((std::is_base_of<MatcherBase<double>, WithinRelMatcher>::value));
}

// --- Constructor: normal cases ---
TEST_F(WithinRelMatcherTest_1051, Constructor_AllowsZeroEpsilon_1051) {
    EXPECT_NO_THROW({
        WithinRelMatcher m(123.0, 0.0);
        (void)m;
    });
}

TEST_F(WithinRelMatcherTest_1051, Constructor_AllowsEpsilonJustBelowOne_1051) {
    const double eps = std::nextafter(1.0, 0.0); // largest double < 1
    EXPECT_NO_THROW({
        WithinRelMatcher m(1.0, eps);
        (void)m;
    });
}

TEST_F(WithinRelMatcherTest_1051, Constructor_AllowsTypicalSmallEpsilon_1051) {
    EXPECT_NO_THROW({
        WithinRelMatcher m(42.0, 1e-6);
        (void)m;
    });
}

// --- Constructor: boundary & exceptional cases ---
TEST_F(WithinRelMatcherTest_1051, Constructor_RejectsNegativeEpsilon_1051) {
    EXPECT_ANY_THROW({
        WithinRelMatcher m(0.0, -1e-12);
        (void)m;
    });
}

TEST_F(WithinRelMatcherTest_1051, Constructor_RejectsEpsilonEqualToOne_1051) {
    EXPECT_ANY_THROW({
        WithinRelMatcher m(0.0, 1.0);
        (void)m;
    });
}

TEST_F(WithinRelMatcherTest_1051, Constructor_RejectsEpsilonGreaterThanOne_1051) {
    EXPECT_ANY_THROW({
        WithinRelMatcher m(0.0, 1.0000000001);
        (void)m;
    });
}

TEST_F(WithinRelMatcherTest_1051, Constructor_RejectsNaNEpsilon_1051) {
    const double nan = std::numeric_limits<double>::quiet_NaN();
    EXPECT_ANY_THROW({
        WithinRelMatcher m(3.14, nan);
        (void)m;
    });
}

TEST_F(WithinRelMatcherTest_1051, Constructor_RejectsPositiveInfinityEpsilon_1051) {
    const double pinf = std::numeric_limits<double>::infinity();
    EXPECT_ANY_THROW({
        WithinRelMatcher m(3.14, pinf);
        (void)m;
    });
}

TEST_F(WithinRelMatcherTest_1051, Constructor_RejectsNegativeInfinityEpsilon_1051) {
    const double ninf = -std::numeric_limits<double>::infinity();
    EXPECT_ANY_THROW({
        WithinRelMatcher m(3.14, ninf);
        (void)m;
    });
}

// --- Interface smoke tests (callability only; no internal behavior assumptions) ---
TEST_F(WithinRelMatcherTest_1051, Describe_IsCallableAndDoesNotThrow_1051) {
    WithinRelMatcher m(10.0, 1e-3);
    EXPECT_NO_THROW({
        std::string d = m.describe();
        (void)d; // We do not assert on contents to avoid inferring internal formatting.
    });
}

TEST_F(WithinRelMatcherTest_1051, Match_IsCallableAndDoesNotThrow_1051) {
    WithinRelMatcher m(10.0, 1e-3);
    EXPECT_NO_THROW({
        bool r = m.match(10.0); // We do not assert true/false to avoid inferring internal logic.
        (void)r;
    });
}
