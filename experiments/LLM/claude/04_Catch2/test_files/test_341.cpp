#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// Include the header under test
#include "./TestProjects/Catch2/src/catch2/internal/catch_uniform_floating_point_distribution.hpp"

namespace {

// Test fixture for calculate_max_steps_in_one_go
class CalculateMaxStepsInOneGoTest_341 : public ::testing::Test {
protected:
};

// Test: When gamma equals the special value, should return 9007199254740991 (2^53 - 1)
TEST_F(CalculateMaxStepsInOneGoTest_341, ReturnsMaxSafeIntegerForSpecialGamma_341) {
    double special_gamma = 1.99584030953472e+292;
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(special_gamma);
    EXPECT_EQ(result, static_cast<std::uint64_t>(9007199254740991));
}

// Test: When gamma is 0.0, should return static_cast<uint64_t>(-1) i.e., UINT64_MAX
TEST_F(CalculateMaxStepsInOneGoTest_341, ReturnsUint64MaxForZeroGamma_341) {
    double gamma = 0.0;
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint64_t>(-1));
}

// Test: When gamma is 1.0, should return UINT64_MAX
TEST_F(CalculateMaxStepsInOneGoTest_341, ReturnsUint64MaxForOneGamma_341) {
    double gamma = 1.0;
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint64_t>(-1));
}

// Test: When gamma is negative, should return UINT64_MAX
TEST_F(CalculateMaxStepsInOneGoTest_341, ReturnsUint64MaxForNegativeGamma_341) {
    double gamma = -1.0;
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint64_t>(-1));
}

// Test: When gamma is a very small positive number, should return UINT64_MAX
TEST_F(CalculateMaxStepsInOneGoTest_341, ReturnsUint64MaxForVerySmallPositiveGamma_341) {
    double gamma = std::numeric_limits<double>::min();
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint64_t>(-1));
}

// Test: When gamma is a very large number (but not the special value), should return UINT64_MAX
TEST_F(CalculateMaxStepsInOneGoTest_341, ReturnsUint64MaxForLargeNonSpecialGamma_341) {
    double gamma = 1.0e+292;
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint64_t>(-1));
}

// Test: When gamma is max double, should return UINT64_MAX
TEST_F(CalculateMaxStepsInOneGoTest_341, ReturnsUint64MaxForMaxDoubleGamma_341) {
    double gamma = std::numeric_limits<double>::max();
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint64_t>(-1));
}

// Test: Value close to special gamma but not equal should return UINT64_MAX
TEST_F(CalculateMaxStepsInOneGoTest_341, ReturnsUint64MaxForNearSpecialGamma_341) {
    // Slightly different from the special value
    double gamma = 1.99584030953473e+292;
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint64_t>(-1));
}

// Test: Another value close to special gamma but slightly less
TEST_F(CalculateMaxStepsInOneGoTest_341, ReturnsUint64MaxForSlightlyLessSpecialGamma_341) {
    double gamma = 1.99584030953471e+292;
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint64_t>(-1));
}

// Test: The special return value is exactly 2^53 - 1
TEST_F(CalculateMaxStepsInOneGoTest_341, SpecialReturnValueIs2Power53Minus1_341) {
    double special_gamma = 1.99584030953472e+292;
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(special_gamma);
    std::uint64_t expected = (static_cast<std::uint64_t>(1) << 53) - 1;
    EXPECT_EQ(result, expected);
}

// Test: constexpr evaluation works at compile time
TEST_F(CalculateMaxStepsInOneGoTest_341, ConstexprEvaluationSpecialGamma_341) {
    constexpr std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(1.99584030953472e+292);
    EXPECT_EQ(result, static_cast<std::uint64_t>(9007199254740991));
}

// Test: constexpr evaluation works at compile time for non-special value
TEST_F(CalculateMaxStepsInOneGoTest_341, ConstexprEvaluationNonSpecialGamma_341) {
    constexpr std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(42.0);
    EXPECT_EQ(result, static_cast<std::uint64_t>(-1));
}

// Test: Positive infinity should return UINT64_MAX
TEST_F(CalculateMaxStepsInOneGoTest_341, ReturnsUint64MaxForPositiveInfinity_341) {
    double gamma = std::numeric_limits<double>::infinity();
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint64_t>(-1));
}

// Test: Negative infinity should return UINT64_MAX
TEST_F(CalculateMaxStepsInOneGoTest_341, ReturnsUint64MaxForNegativeInfinity_341) {
    double gamma = -std::numeric_limits<double>::infinity();
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint64_t>(-1));
}

// Test: Denormalized number should return UINT64_MAX
TEST_F(CalculateMaxStepsInOneGoTest_341, ReturnsUint64MaxForDenormalizedGamma_341) {
    double gamma = std::numeric_limits<double>::denorm_min();
    std::uint64_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);
    EXPECT_EQ(result, static_cast<std::uint64_t>(-1));
}

} // anonymous namespace
