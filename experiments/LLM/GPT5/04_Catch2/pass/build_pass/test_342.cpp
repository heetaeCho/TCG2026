// File: test_calculate_max_steps_in_one_go_342.cpp

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <cmath>

// Include the header under test
#include "Catch2/src/catch2/internal/catch_uniform_floating_point_distribution.hpp"

using Catch::Detail::calculate_max_steps_in_one_go;

namespace {

// Optional compile-time checks (allowed because the function is constexpr)
static_assert(
    calculate_max_steps_in_one_go(2.028241e+31f) == 16777215u,
    "Exact gamma should yield 16777215");
static_assert(
    calculate_max_steps_in_one_go(0.0f) == static_cast<std::uint32_t>(-1),
    "Any other value should yield UINT32_MAX");

class UniformFloatingPointDistributionTest_342 : public ::testing::Test {};

} // namespace

// Normal operation: exact match returns the special value
TEST_F(UniformFloatingPointDistributionTest_342, ExactMatchReturnsExpected_342) {
    const float gamma = 2.028241e+31f;
    EXPECT_EQ(16777215u, calculate_max_steps_in_one_go(gamma));
}

// Boundary-ish: values very close but not exactly equal fall back to UINT32_MAX
TEST_F(UniformFloatingPointDistributionTest_342, NextAfterDownIsNotEqual_342) {
    const float target = 2.028241e+31f;
    const float just_below = std::nextafterf(target, -std::numeric_limits<float>::infinity());
    ASSERT_NE(just_below, target); // guard: ensure it's actually different
    EXPECT_EQ(std::numeric_limits<std::uint32_t>::max(),
              calculate_max_steps_in_one_go(just_below));
}

TEST_F(UniformFloatingPointDistributionTest_342, NextAfterUpIsNotEqual_342) {
    const float target = 2.028241e+31f;
    const float just_above = std::nextafterf(target, std::numeric_limits<float>::infinity());
    ASSERT_NE(just_above, target); // guard: ensure it's actually different
    EXPECT_EQ(std::numeric_limits<std::uint32_t>::max(),
              calculate_max_steps_in_one_go(just_above));
}

// Typical non-matching inputs return UINT32_MAX
TEST_F(UniformFloatingPointDistributionTest_342, ZeroReturnsMaxUint32_342) {
    EXPECT_EQ(std::numeric_limits<std::uint32_t>::max(),
              calculate_max_steps_in_one_go(0.0f));
}

TEST_F(UniformFloatingPointDistributionTest_342, OneReturnsMaxUint32_342) {
    EXPECT_EQ(std::numeric_limits<std::uint32_t>::max(),
              calculate_max_steps_in_one_go(1.0f));
}

TEST_F(UniformFloatingPointDistributionTest_342, NegativeValueReturnsMaxUint32_342) {
    EXPECT_EQ(std::numeric_limits<std::uint32_t>::max(),
              calculate_max_steps_in_one_go(-1.0f));
}

// Exceptional/edge floating values: NaN and infinities are not equal to target
TEST_F(UniformFloatingPointDistributionTest_342, NaNReturnsMaxUint32_342) {
    const float nan = std::numeric_limits<float>::quiet_NaN();
    // (nan == x) is false; function should take the "else" branch
    EXPECT_EQ(std::numeric_limits<std::uint32_t>::max(),
              calculate_max_steps_in_one_go(nan));
}

TEST_F(UniformFloatingPointDistributionTest_342, PosInfinityReturnsMaxUint32_342) {
    const float inf = std::numeric_limits<float>::infinity();
    EXPECT_EQ(std::numeric_limits<std::uint32_t>::max(),
              calculate_max_steps_in_one_go(inf));
}

TEST_F(UniformFloatingPointDistributionTest_342, NegInfinityReturnsMaxUint32_342) {
    const float ninf = -std::numeric_limits<float>::infinity();
    EXPECT_EQ(std::numeric_limits<std::uint32_t>::max(),
              calculate_max_steps_in_one_go(ninf));
}

