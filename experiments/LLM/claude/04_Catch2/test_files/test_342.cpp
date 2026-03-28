#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// Include the header under test
#include "catch2/internal/catch_uniform_floating_point_distribution.hpp"

namespace {

// Test normal operation: when gamma equals the special value 2.028241e+31f
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsSpecialValueForSpecificGamma_342) {
    float gamma = 2.028241e+31f;
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, 16777215u);
}

// Test normal operation: when gamma is not the special value, should return UINT32_MAX
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsMaxUint32ForNonSpecialGamma_342) {
    float gamma = 1.0f;
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));
}

// Test with gamma = 0.0f
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsMaxUint32ForZeroGamma_342) {
    float gamma = 0.0f;
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));
}

// Test with gamma = negative value
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsMaxUint32ForNegativeGamma_342) {
    float gamma = -1.0f;
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));
}

// Test with gamma = very large positive value (not the special value)
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsMaxUint32ForLargeGamma_342) {
    float gamma = 1.0e+38f;
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));
}

// Test with gamma = very small positive value
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsMaxUint32ForVerySmallGamma_342) {
    float gamma = 1.0e-38f;
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));
}

// Test with gamma = float max
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsMaxUint32ForFloatMax_342) {
    float gamma = std::numeric_limits<float>::max();
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));
}

// Test with gamma = float min (smallest positive normalized)
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsMaxUint32ForFloatMin_342) {
    float gamma = std::numeric_limits<float>::min();
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));
}

// Test with gamma = float epsilon
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsMaxUint32ForFloatEpsilon_342) {
    float gamma = std::numeric_limits<float>::epsilon();
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));
}

// Test with gamma = infinity
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsMaxUint32ForInfinity_342) {
    float gamma = std::numeric_limits<float>::infinity();
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));
}

// Test with gamma = negative infinity
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsMaxUint32ForNegativeInfinity_342) {
    float gamma = -std::numeric_limits<float>::infinity();
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));
}

// Test that the special return value 16777215 equals 2^24 - 1
TEST(CalculateMaxStepsInOneGoTest_342, SpecialReturnValueIs2Pow24Minus1_342) {
    float gamma = 2.028241e+31f;
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, (1u << 24) - 1u);
}

// Test constexpr-ness: the function should be usable in constexpr context
TEST(CalculateMaxStepsInOneGoTest_342, IsConstexpr_342) {
    constexpr std::uint32_t result_special = Catch::Detail::calculate_max_steps_in_one_go(2.028241e+31f);
    constexpr std::uint32_t result_other = Catch::Detail::calculate_max_steps_in_one_go(1.0f);
    EXPECT_EQ(result_special, 16777215u);
    EXPECT_EQ(result_other, static_cast<std::uint32_t>(-1));
}

// Test with a value very close to the special gamma but not equal
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsMaxUint32ForNearbyGammaValue_342) {
    float gamma = 2.028241e+31f;
    // Get next representable float value
    float gamma_next = std::nextafter(gamma, std::numeric_limits<float>::max());
    float gamma_prev = std::nextafter(gamma, 0.0f);
    
    if (gamma_next != gamma) {
        std::uint32_t result_next = Catch::Detail::calculate_max_steps_in_one_go(gamma_next);
        EXPECT_EQ(result_next, static_cast<std::uint32_t>(-1));
    }
    if (gamma_prev != gamma) {
        std::uint32_t result_prev = Catch::Detail::calculate_max_steps_in_one_go(gamma_prev);
        EXPECT_EQ(result_prev, static_cast<std::uint32_t>(-1));
    }
}

// Test with the negative of the special gamma value
TEST(CalculateMaxStepsInOneGoTest_342, ReturnsMaxUint32ForNegativeSpecialGamma_342) {
    float gamma = -2.028241e+31f;
    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));
}

} // namespace
