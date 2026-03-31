#include <gtest/gtest.h>
#include "contrib/dragonbox.h"
#include <cstdint>
#include <limits>
#include <cmath>

// The dragonbox implementation in yaml-cpp provides float/double to string conversion.
// We test the publicly accessible dragonbox functionality through the header.

namespace {

// Test the dragonbox to_decimal conversion for float
class DragonboxFloatTest_319 : public ::testing::Test {};

// Test the dragonbox to_decimal conversion for double  
class DragonboxDoubleTest_319 : public ::testing::Test {};

// Tests for float conversions
TEST_F(DragonboxFloatTest_319, ZeroValue_319) {
    float v = 0.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_EQ(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

TEST_F(DragonboxFloatTest_319, NegativeZeroValue_319) {
    float v = -0.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_EQ(result.significand, 0u);
    EXPECT_TRUE(result.is_negative);
}

TEST_F(DragonboxFloatTest_319, PositiveOne_319) {
    float v = 1.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

TEST_F(DragonboxFloatTest_319, NegativeOne_319) {
    float v = -1.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_TRUE(result.is_negative);
}

TEST_F(DragonboxFloatTest_319, SmallPositiveFloat_319) {
    float v = 0.1f;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
    // 0.1f should produce significand=1, exponent=-1
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxFloatTest_319, LargeFloat_319) {
    float v = 1000000.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloatTest_319, SmallestNormalFloat_319) {
    float v = std::numeric_limits<float>::min();
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloatTest_319, LargestFloat_319) {
    float v = std::numeric_limits<float>::max();
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloatTest_319, SmallestDenormalFloat_319) {
    float v = std::numeric_limits<float>::denorm_min();
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloatTest_319, PositiveTen_319) {
    float v = 10.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 1);
}

TEST_F(DragonboxFloatTest_319, PointFive_319) {
    float v = 0.5f;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, -1);
}

// Tests for double conversions
TEST_F(DragonboxDoubleTest_319, ZeroValue_319) {
    double v = 0.0;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_EQ(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

TEST_F(DragonboxDoubleTest_319, NegativeZeroValue_319) {
    double v = -0.0;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_EQ(result.significand, 0u);
    EXPECT_TRUE(result.is_negative);
}

TEST_F(DragonboxDoubleTest_319, PositiveOne_319) {
    double v = 1.0;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

TEST_F(DragonboxDoubleTest_319, NegativeOne_319) {
    double v = -1.0;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_TRUE(result.is_negative);
}

TEST_F(DragonboxDoubleTest_319, SmallPositiveDouble_319) {
    double v = 0.1;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxDoubleTest_319, LargeDouble_319) {
    double v = 1e15;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxDoubleTest_319, SmallestNormalDouble_319) {
    double v = std::numeric_limits<double>::min();
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxDoubleTest_319, LargestDouble_319) {
    double v = std::numeric_limits<double>::max();
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxDoubleTest_319, SmallestDenormalDouble_319) {
    double v = std::numeric_limits<double>::denorm_min();
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxDoubleTest_319, PositiveTen_319) {
    double v = 10.0;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 1);
}

TEST_F(DragonboxDoubleTest_319, NegativeLargeValue_319) {
    double v = -123456789.0;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_TRUE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxDoubleTest_319, Pi_319) {
    double v = 3.141592653589793;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxDoubleTest_319, PointFive_319) {
    double v = 0.5;
    auto result = YAML::jkj::dragonbox::to_decimal(v);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, -1);
}

// Verify round-trip consistency: the decimal representation should reconstruct the original value
TEST_F(DragonboxDoubleTest_319, RoundTripConsistency_319) {
    double values[] = {1.0, 0.1, 0.5, 123.456, 1e-10, 1e10, 3.14159};
    for (double v : values) {
        auto result = YAML::jkj::dragonbox::to_decimal(v);
        double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
        EXPECT_DOUBLE_EQ(v, reconstructed) << "Failed for value: " << v;
    }
}

TEST_F(DragonboxFloatTest_319, RoundTripConsistency_319) {
    float values[] = {1.0f, 0.1f, 0.5f, 123.456f, 1e-5f, 1e5f, 3.14f};
    for (float v : values) {
        auto result = YAML::jkj::dragonbox::to_decimal(v);
        float reconstructed = static_cast<float>(result.significand) * std::pow(10.0f, result.exponent);
        EXPECT_FLOAT_EQ(v, reconstructed) << "Failed for value: " << v;
    }
}

TEST_F(DragonboxDoubleTest_319, PowersOfTwo_319) {
    for (int i = 0; i < 20; ++i) {
        double v = std::pow(2.0, i);
        auto result = YAML::jkj::dragonbox::to_decimal(v);
        EXPECT_FALSE(result.is_negative);
        EXPECT_GT(result.significand, 0u);
        double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
        EXPECT_DOUBLE_EQ(v, reconstructed);
    }
}

TEST_F(DragonboxDoubleTest_319, PowersOfTen_319) {
    for (int i = 0; i < 15; ++i) {
        double v = std::pow(10.0, i);
        auto result = YAML::jkj::dragonbox::to_decimal(v);
        EXPECT_FALSE(result.is_negative);
        EXPECT_EQ(result.significand, 1u);
        EXPECT_EQ(result.exponent, i);
    }
}

} // namespace
