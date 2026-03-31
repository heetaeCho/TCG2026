#include <gtest/gtest.h>
#include <cmath>
#include <cstring>
#include <limits>

// Include the dragonbox header and any necessary yaml-cpp headers
#include "contrib/dragonbox.h"

// If there's a higher-level to_decimal function, we may need it
// The dragonbox namespace typically provides to_decimal as a convenience wrapper

namespace {

using namespace YAML::jkj::dragonbox;

class DragonboxTest_428 : public ::testing::Test {
protected:
    // Helper to get IEEE bits from a float
    static uint32_t float_to_bits(float f) {
        uint32_t bits;
        std::memcpy(&bits, &f, sizeof(bits));
        return bits;
    }

    // Helper to get IEEE bits from a double
    static uint64_t double_to_bits(double d) {
        uint64_t bits;
        std::memcpy(&bits, &d, sizeof(bits));
        return bits;
    }
};

// Test basic conversion of a simple float value
TEST_F(DragonboxTest_428, SimpleFloatConversion_428) {
    float value = 1.0f;
    auto result = to_decimal(value);
    // 1.0 should have significand 1 and exponent 0
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

// Test conversion of negative float
TEST_F(DragonboxTest_428, NegativeFloatConversion_428) {
    float value = -1.0f;
    auto result = to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_TRUE(result.is_negative);
}

// Test conversion of simple double value
TEST_F(DragonboxTest_428, SimpleDoubleConversion_428) {
    double value = 1.0;
    auto result = to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

// Test conversion of negative double
TEST_F(DragonboxTest_428, NegativeDoubleConversion_428) {
    double value = -1.0;
    auto result = to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_TRUE(result.is_negative);
}

// Test small float value
TEST_F(DragonboxTest_428, SmallFloatValue_428) {
    float value = 0.1f;
    auto result = to_decimal(value);
    // 0.1f -> significand * 10^exponent should reconstruct ~0.1
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test large float value
TEST_F(DragonboxTest_428, LargeFloatValue_428) {
    float value = 1.0e30f;
    auto result = to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_GT(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

// Test small double value
TEST_F(DragonboxTest_428, SmallDoubleValue_428) {
    double value = 0.1;
    auto result = to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test float value 3.14
TEST_F(DragonboxTest_428, FloatPi_428) {
    float value = 3.14f;
    auto result = to_decimal(value);
    EXPECT_EQ(result.significand, 314u);
    EXPECT_EQ(result.exponent, -2);
    EXPECT_FALSE(result.is_negative);
}

// Test double value 3.14
TEST_F(DragonboxTest_428, DoublePi_428) {
    double value = 3.14;
    auto result = to_decimal(value);
    EXPECT_EQ(result.significand, 314u);
    EXPECT_EQ(result.exponent, -2);
    EXPECT_FALSE(result.is_negative);
}

// Test smallest positive normal float
TEST_F(DragonboxTest_428, SmallestNormalFloat_428) {
    float value = std::numeric_limits<float>::min();
    auto result = to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test largest finite float
TEST_F(DragonboxTest_428, LargestFiniteFloat_428) {
    float value = std::numeric_limits<float>::max();
    auto result = to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test smallest positive normal double
TEST_F(DragonboxTest_428, SmallestNormalDouble_428) {
    double value = std::numeric_limits<double>::min();
    auto result = to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test largest finite double
TEST_F(DragonboxTest_428, LargestFiniteDouble_428) {
    double value = std::numeric_limits<double>::max();
    auto result = to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test smallest positive subnormal float
TEST_F(DragonboxTest_428, SmallestSubnormalFloat_428) {
    float value = std::numeric_limits<float>::denorm_min();
    auto result = to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test smallest positive subnormal double
TEST_F(DragonboxTest_428, SmallestSubnormalDouble_428) {
    double value = std::numeric_limits<double>::denorm_min();
    auto result = to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test float value 10.0
TEST_F(DragonboxTest_428, FloatTen_428) {
    float value = 10.0f;
    auto result = to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 1);
    EXPECT_FALSE(result.is_negative);
}

// Test double value 10.0
TEST_F(DragonboxTest_428, DoubleTen_428) {
    double value = 10.0;
    auto result = to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 1);
    EXPECT_FALSE(result.is_negative);
}

// Test float value 100.0
TEST_F(DragonboxTest_428, FloatHundred_428) {
    float value = 100.0f;
    auto result = to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 2);
    EXPECT_FALSE(result.is_negative);
}

// Test float value 0.5
TEST_F(DragonboxTest_428, FloatHalf_428) {
    float value = 0.5f;
    auto result = to_decimal(value);
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, -1);
    EXPECT_FALSE(result.is_negative);
}

// Test double value 0.5
TEST_F(DragonboxTest_428, DoubleHalf_428) {
    double value = 0.5;
    auto result = to_decimal(value);
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, -1);
    EXPECT_FALSE(result.is_negative);
}

// Test roundtrip consistency: significand * 10^exponent should approximate the original
TEST_F(DragonboxTest_428, FloatRoundtripConsistency_428) {
    float value = 1.234567f;
    auto result = to_decimal(value);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_NEAR(reconstructed, static_cast<double>(value), 1e-6);
}

// Test roundtrip consistency for double
TEST_F(DragonboxTest_428, DoubleRoundtripConsistency_428) {
    double value = 1.23456789012345;
    auto result = to_decimal(value);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_NEAR(reconstructed, value, 1e-14);
}

// Test negative small float
TEST_F(DragonboxTest_428, NegativeSmallFloat_428) {
    float value = -0.001f;
    auto result = to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_TRUE(result.is_negative);
}

// Test negative large double
TEST_F(DragonboxTest_428, NegativeLargeDouble_428) {
    double value = -1.0e100;
    auto result = to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_TRUE(result.is_negative);
}

// Test float value 999999.0
TEST_F(DragonboxTest_428, FloatLargeInteger_428) {
    float value = 999999.0f;
    auto result = to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_NEAR(reconstructed, static_cast<double>(value), 1.0);
}

// Test double with many significant digits
TEST_F(DragonboxTest_428, DoubleManySigDigits_428) {
    double value = 1.7976931348623157e+308; // near max double
    auto result = to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

} // namespace
