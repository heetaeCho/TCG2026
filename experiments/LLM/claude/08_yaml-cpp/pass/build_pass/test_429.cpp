#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include "contrib/dragonbox.h"

class DragonboxTest_429 : public ::testing::Test {
protected:
    // Helper to verify that to_decimal round-trips correctly
    // significand * 10^exponent should reconstruct the original value
    template <typename Float>
    void VerifyRoundTrip(Float value) {
        auto result = YAML::jkj::dragonbox::to_decimal(value);
        // Reconstruct the value from significand and exponent
        double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
        if (value < 0) {
            EXPECT_TRUE(result.is_negative);
            EXPECT_DOUBLE_EQ(static_cast<double>(-value), reconstructed);
        } else {
            EXPECT_FALSE(result.is_negative);
            EXPECT_DOUBLE_EQ(static_cast<double>(value), reconstructed);
        }
    }
};

// ============ Normal Operation Tests ============

TEST_F(DragonboxTest_429, PositiveDoubleOne_429) {
    double x = 1.0;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
    // 1.0 = significand * 10^exponent
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(1.0, reconstructed);
}

TEST_F(DragonboxTest_429, NegativeDoubleOne_429) {
    double x = -1.0;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_TRUE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(1.0, reconstructed);
}

TEST_F(DragonboxTest_429, PositiveFloatOne_429) {
    float x = 1.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_FLOAT_EQ(1.0f, static_cast<float>(reconstructed));
}

TEST_F(DragonboxTest_429, PositiveDoubleSmallInteger_429) {
    double x = 5.0;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(5.0, reconstructed);
}

TEST_F(DragonboxTest_429, PositiveDoubleLargeInteger_429) {
    double x = 1234567890.0;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(1234567890.0, reconstructed);
}

TEST_F(DragonboxTest_429, PositiveDoubleFractional_429) {
    double x = 0.1;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(0.1, reconstructed);
}

TEST_F(DragonboxTest_429, PositiveDoublePi_429) {
    double x = 3.141592653589793;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(x, reconstructed);
}

TEST_F(DragonboxTest_429, NegativeDoubleFractional_429) {
    double x = -0.5;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_TRUE(result.is_negative);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(0.5, reconstructed);
}

TEST_F(DragonboxTest_429, NegativeFloatFractional_429) {
    float x = -0.25f;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_TRUE(result.is_negative);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_FLOAT_EQ(0.25f, static_cast<float>(reconstructed));
}

// ============ Boundary Condition Tests ============

TEST_F(DragonboxTest_429, SmallestPositiveNormalDouble_429) {
    double x = std::numeric_limits<double>::min();  // smallest positive normal
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, LargestFiniteDouble_429) {
    double x = std::numeric_limits<double>::max();
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, SmallestPositiveNormalFloat_429) {
    float x = std::numeric_limits<float>::min();
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, LargestFiniteFloat_429) {
    float x = std::numeric_limits<float>::max();
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, SmallestPositiveDenormalDouble_429) {
    double x = std::numeric_limits<double>::denorm_min();
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, SmallestPositiveDenormalFloat_429) {
    float x = std::numeric_limits<float>::denorm_min();
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, NegativeSmallestNormalDouble_429) {
    double x = -std::numeric_limits<double>::min();
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_TRUE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, NegativeLargestFiniteDouble_429) {
    double x = -std::numeric_limits<double>::max();
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_TRUE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

// ============ Various Value Tests ============

TEST_F(DragonboxTest_429, DoubleEpsilon_429) {
    double x = std::numeric_limits<double>::epsilon();
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, FloatEpsilon_429) {
    float x = std::numeric_limits<float>::epsilon();
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, DoublePowerOfTwo_429) {
    double x = 1024.0;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(1024.0, reconstructed);
}

TEST_F(DragonboxTest_429, FloatPowerOfTwo_429) {
    float x = 0.5f;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_FLOAT_EQ(0.5f, static_cast<float>(reconstructed));
}

TEST_F(DragonboxTest_429, DoublePointOneTwoThree_429) {
    double x = 0.123;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(0.123, reconstructed);
}

TEST_F(DragonboxTest_429, SignificandIsNonZeroForNonZeroInput_429) {
    double x = 42.0;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, DoubleVerySmallPositive_429) {
    double x = 1e-300;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, DoubleVeryLargePositive_429) {
    double x = 1e+300;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, FloatVerySmallPositive_429) {
    float x = 1e-38f;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, FloatVeryLargePositive_429) {
    float x = 1e+38f;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, static_cast<decltype(result.significand)>(0));
}

TEST_F(DragonboxTest_429, DoubleNegativeExponentResult_429) {
    double x = 0.001;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(0.001, reconstructed);
}

TEST_F(DragonboxTest_429, DoublePositiveExponentResult_429) {
    double x = 1000.0;
    auto result = YAML::jkj::dragonbox::to_decimal(x);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = static_cast<double>(result.significand) * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(1000.0, reconstructed);
}

TEST_F(DragonboxTest_429, DoubleRoundTrip_429) {
    VerifyRoundTrip(2.71828182845904523536);
}

TEST_F(DragonboxTest_429, FloatRoundTrip_429) {
    VerifyRoundTrip(2.71828f);
}

TEST_F(DragonboxTest_429, NegativeDoubleRoundTrip_429) {
    VerifyRoundTrip(-9.99);
}

TEST_F(DragonboxTest_429, NegativeFloatRoundTrip_429) {
    VerifyRoundTrip(-9.99f);
}
