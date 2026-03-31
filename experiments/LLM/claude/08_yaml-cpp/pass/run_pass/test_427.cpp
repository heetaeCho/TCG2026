#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <cstdint>
#include <cstring>

// Include the dragonbox header
#include "contrib/dragonbox.h"

namespace {

// Helper to get float bits
uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    return bits;
}

uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(bits));
    return bits;
}

class DragonboxTest_427 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal float conversion - positive value
TEST_F(DragonboxTest_427, FloatPositiveNormal_427) {
    float value = 1.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    // 1.0f should have significand 1 and exponent 0
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

// Test normal float conversion - negative value
TEST_F(DragonboxTest_427, FloatNegativeNormal_427) {
    float value = -1.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_TRUE(result.is_negative);
}

// Test float conversion for a simple decimal
TEST_F(DragonboxTest_427, FloatSimpleDecimal_427) {
    float value = 0.1f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    // 0.1f should produce significand 1, exponent -1
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, -1);
    EXPECT_FALSE(result.is_negative);
}

// Test float conversion for integer value
TEST_F(DragonboxTest_427, FloatIntegerValue_427) {
    float value = 100.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 2);
    EXPECT_FALSE(result.is_negative);
}

// Test float conversion for small value
TEST_F(DragonboxTest_427, FloatSmallValue_427) {
    float value = 0.001f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, -3);
    EXPECT_FALSE(result.is_negative);
}

// Test double conversion - positive value
TEST_F(DragonboxTest_427, DoublePositiveNormal_427) {
    double value = 1.0;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

// Test double conversion - negative value
TEST_F(DragonboxTest_427, DoubleNegativeNormal_427) {
    double value = -1.0;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_TRUE(result.is_negative);
}

// Test double conversion - 0.1
TEST_F(DragonboxTest_427, DoublePointOne_427) {
    double value = 0.1;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, -1);
    EXPECT_FALSE(result.is_negative);
}

// Test float with value 3.14
TEST_F(DragonboxTest_427, FloatPi_427) {
    float value = 3.14f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 314u);
    EXPECT_EQ(result.exponent, -2);
    EXPECT_FALSE(result.is_negative);
}

// Test double with value 3.14
TEST_F(DragonboxTest_427, DoublePi_427) {
    double value = 3.14;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 314u);
    EXPECT_EQ(result.exponent, -2);
    EXPECT_FALSE(result.is_negative);
}

// Test float - large value
TEST_F(DragonboxTest_427, FloatLargeValue_427) {
    float value = 1.0e30f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_GT(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

// Test float - very small positive value
TEST_F(DragonboxTest_427, FloatVerySmallPositive_427) {
    float value = 1.0e-30f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_LT(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

// Test double - large value
TEST_F(DragonboxTest_427, DoubleLargeValue_427) {
    double value = 1.0e200;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_GT(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

// Test double - very small positive value
TEST_F(DragonboxTest_427, DoubleVerySmallPositive_427) {
    double value = 1.0e-200;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_LT(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

// Test float - smallest normal
TEST_F(DragonboxTest_427, FloatSmallestNormal_427) {
    float value = std::numeric_limits<float>::min();
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test double - smallest normal
TEST_F(DragonboxTest_427, DoubleSmallestNormal_427) {
    double value = std::numeric_limits<double>::min();
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test float - largest finite
TEST_F(DragonboxTest_427, FloatLargestFinite_427) {
    float value = std::numeric_limits<float>::max();
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test double - largest finite
TEST_F(DragonboxTest_427, DoubleLargestFinite_427) {
    double value = std::numeric_limits<double>::max();
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test float - denormalized smallest
TEST_F(DragonboxTest_427, FloatDenormSmallest_427) {
    float value = std::numeric_limits<float>::denorm_min();
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test double - denormalized smallest
TEST_F(DragonboxTest_427, DoubleDenormSmallest_427) {
    double value = std::numeric_limits<double>::denorm_min();
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test float value 2.5
TEST_F(DragonboxTest_427, FloatTwoPointFive_427) {
    float value = 2.5f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 25u);
    EXPECT_EQ(result.exponent, -1);
    EXPECT_FALSE(result.is_negative);
}

// Test double value 2.5
TEST_F(DragonboxTest_427, DoubleTwoPointFive_427) {
    double value = 2.5;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 25u);
    EXPECT_EQ(result.exponent, -1);
    EXPECT_FALSE(result.is_negative);
}

// Test float - negative large
TEST_F(DragonboxTest_427, FloatNegativeLarge_427) {
    float value = -1.0e20f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_TRUE(result.is_negative);
}

// Test double - negative large
TEST_F(DragonboxTest_427, DoubleNegativeLarge_427) {
    double value = -1.0e100;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_TRUE(result.is_negative);
}

// Test specific known float conversion: 1.5f
TEST_F(DragonboxTest_427, FloatOnePointFive_427) {
    float value = 1.5f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 15u);
    EXPECT_EQ(result.exponent, -1);
    EXPECT_FALSE(result.is_negative);
}

// Test specific known double conversion: 1.5
TEST_F(DragonboxTest_427, DoubleOnePointFive_427) {
    double value = 1.5;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 15u);
    EXPECT_EQ(result.exponent, -1);
    EXPECT_FALSE(result.is_negative);
}

// Test float 10.0
TEST_F(DragonboxTest_427, FloatTen_427) {
    float value = 10.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 1);
    EXPECT_FALSE(result.is_negative);
}

// Test double 10.0
TEST_F(DragonboxTest_427, DoubleTen_427) {
    double value = 10.0;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 1);
    EXPECT_FALSE(result.is_negative);
}

// Roundtrip consistency: significand * 10^exponent should reconstruct the value
TEST_F(DragonboxTest_427, FloatRoundtripConsistency_427) {
    float value = 1.23456f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    double reconstructed = result.significand * std::pow(10.0, result.exponent);
    EXPECT_FLOAT_EQ(static_cast<float>(reconstructed), std::abs(value));
}

TEST_F(DragonboxTest_427, DoubleRoundtripConsistency_427) {
    double value = 1.23456789012345;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    double reconstructed = result.significand * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(reconstructed, std::abs(value));
}

// Test that sign is correctly detected for negative float
TEST_F(DragonboxTest_427, FloatSignDetection_427) {
    float pos = 42.0f;
    float neg = -42.0f;
    auto res_pos = YAML::jkj::dragonbox::to_decimal(pos);
    auto res_neg = YAML::jkj::dragonbox::to_decimal(neg);
    EXPECT_FALSE(res_pos.is_negative);
    EXPECT_TRUE(res_neg.is_negative);
    EXPECT_EQ(res_pos.significand, res_neg.significand);
    EXPECT_EQ(res_pos.exponent, res_neg.exponent);
}

// Test that sign is correctly detected for negative double
TEST_F(DragonboxTest_427, DoubleSignDetection_427) {
    double pos = 42.0;
    double neg = -42.0;
    auto res_pos = YAML::jkj::dragonbox::to_decimal(pos);
    auto res_neg = YAML::jkj::dragonbox::to_decimal(neg);
    EXPECT_FALSE(res_pos.is_negative);
    EXPECT_TRUE(res_neg.is_negative);
    EXPECT_EQ(res_pos.significand, res_neg.significand);
    EXPECT_EQ(res_pos.exponent, res_neg.exponent);
}

} // namespace
