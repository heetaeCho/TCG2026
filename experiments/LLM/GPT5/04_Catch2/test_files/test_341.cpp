// File: test_calculate_max_steps_in_one_go_341.cpp
#include <gtest/gtest.h>
#include <limits>
#include <cmath>
#include <cstdint>

// SUT header
#include "catch2/internal/catch_uniform_floating_point_distribution.hpp"

namespace {
    using Catch::Detail::calculate_max_steps_in_one_go;

    // Compile-time check: function is usable in constant expressions
    constexpr double kMagicGamma = 1.99584030953472e+292;
    static_assert(calculate_max_steps_in_one_go(kMagicGamma) == 9007199254740991ULL,
                  "calculate_max_steps_in_one_go must be constexpr for magic gamma");
}

TEST(CalculateMaxStepsInOneGo_341, ReturnsSpecialValueForKnownGamma_341) {
    constexpr double gamma = 1.99584030953472e+292; // exact literal from interface
    const auto result = calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, 9007199254740991ULL); // 2^53 - 1
}

TEST(CalculateMaxStepsInOneGo_341, ReturnsUint64MaxForTypicalOtherValues_341) {
    const auto result_zero = calculate_max_steps_in_one_go(0.0);
    const auto result_one  = calculate_max_steps_in_one_go(1.0);
    constexpr auto u64max = std::numeric_limits<std::uint64_t>::max();
    EXPECT_EQ(result_zero, u64max);
    EXPECT_EQ(result_one,  u64max);
}

TEST(CalculateMaxStepsInOneGo_341, ReturnsUint64MaxForNaN_341) {
    const double nan_val = std::numeric_limits<double>::quiet_NaN();
    const auto result = calculate_max_steps_in_one_go(nan_val);
    EXPECT_EQ(result, std::numeric_limits<std::uint64_t>::max());
}

TEST(CalculateMaxStepsInOneGo_341, ReturnsUint64MaxForInfinity_341) {
    const double pos_inf = std::numeric_limits<double>::infinity();
    const double neg_inf = -std::numeric_limits<double>::infinity();
    const auto result_pos = calculate_max_steps_in_one_go(pos_inf);
    const auto result_neg = calculate_max_steps_in_one_go(neg_inf);
    constexpr auto u64max = std::numeric_limits<std::uint64_t>::max();
    EXPECT_EQ(result_pos, u64max);
    EXPECT_EQ(result_neg, u64max);
}

TEST(CalculateMaxStepsInOneGo_341, NearButNotEqualDoesNotTriggerSpecialCase_341) {
    // Move by 1 ULP away from the exact magic constant to ensure inequality
    const double gamma_next = std::nextafter(kMagicGamma, std::numeric_limits<double>::infinity());
    ASSERT_NE(gamma_next, kMagicGamma); // sanity: ensure they differ
    const auto result = calculate_max_steps_in_one_go(gamma_next);
    EXPECT_EQ(result, std::numeric_limits<std::uint64_t>::max());
}

TEST(CalculateMaxStepsInOneGo_341, ConstexprUseInsideTestBody_341) {
    // Additional check that it can be evaluated at compile time in a constexpr context
    constexpr auto v = calculate_max_steps_in_one_go(kMagicGamma);
    static_assert(v == 9007199254740991ULL, "constexpr evaluation should match special value");
    EXPECT_EQ(v, 9007199254740991ULL);
}
