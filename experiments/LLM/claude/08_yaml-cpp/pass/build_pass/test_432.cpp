#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <limits>

// We need to include the header that declares YAML::FpToString
// Based on the source file, we need the yaml-cpp headers
#include "yaml-cpp/yaml.h"

// If the above doesn't expose FpToString directly, try:
// #include "yaml-cpp/emitter.h"
// or declare it manually based on the known signature:
namespace YAML {
    std::string FpToString(float v, size_t precision);
}

class FpToStringTest_432 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(FpToStringTest_432, PositiveInteger_432) {
    std::string result = YAML::FpToString(1.0f, 6);
    EXPECT_FALSE(result.empty());
    // The string should represent 1.0
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, 1.0f);
}

TEST_F(FpToStringTest_432, NegativeInteger_432) {
    std::string result = YAML::FpToString(-1.0f, 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, -1.0f);
}

TEST_F(FpToStringTest_432, Zero_432) {
    std::string result = YAML::FpToString(0.0f, 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, 0.0f);
}

TEST_F(FpToStringTest_432, NegativeZero_432) {
    std::string result = YAML::FpToString(-0.0f, 6);
    EXPECT_FALSE(result.empty());
    // Negative zero should parse back; the sign may or may not be preserved
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, 0.0f);
}

TEST_F(FpToStringTest_432, SmallPositiveFloat_432) {
    std::string result = YAML::FpToString(0.123456f, 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_NEAR(parsed, 0.123456f, 1e-5f);
}

TEST_F(FpToStringTest_432, LargePositiveFloat_432) {
    std::string result = YAML::FpToString(123456.789f, 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_NEAR(parsed, 123456.789f, 1.0f);
}

TEST_F(FpToStringTest_432, LargeNegativeFloat_432) {
    std::string result = YAML::FpToString(-987654.321f, 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_NEAR(parsed, -987654.321f, 1.0f);
}

TEST_F(FpToStringTest_432, VerySmallFloat_432) {
    std::string result = YAML::FpToString(1e-30f, 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_NEAR(parsed, 1e-30f, 1e-35f);
}

TEST_F(FpToStringTest_432, VeryLargeFloat_432) {
    std::string result = YAML::FpToString(1e30f, 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, 1e30f);
}

// Precision tests

TEST_F(FpToStringTest_432, PrecisionOne_432) {
    std::string result = YAML::FpToString(3.14159f, 1);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_NEAR(parsed, 3.14159f, 0.5f);
}

TEST_F(FpToStringTest_432, PrecisionTwo_432) {
    std::string result = YAML::FpToString(3.14159f, 2);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_NEAR(parsed, 3.14159f, 0.05f);
}

TEST_F(FpToStringTest_432, PrecisionTen_432) {
    std::string result = YAML::FpToString(3.14159f, 10);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, 3.14159f);
}

TEST_F(FpToStringTest_432, DefaultPrecisionSix_432) {
    std::string result = YAML::FpToString(2.71828f, 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_NEAR(parsed, 2.71828f, 1e-5f);
}

// Boundary / special value tests

TEST_F(FpToStringTest_432, PositiveInfinity_432) {
    std::string result = YAML::FpToString(std::numeric_limits<float>::infinity(), 6);
    EXPECT_FALSE(result.empty());
    // YAML typically represents infinity as ".inf"
    // We check it's a non-empty string; exact format depends on implementation
}

TEST_F(FpToStringTest_432, NegativeInfinity_432) {
    std::string result = YAML::FpToString(-std::numeric_limits<float>::infinity(), 6);
    EXPECT_FALSE(result.empty());
}

TEST_F(FpToStringTest_432, NaN_432) {
    std::string result = YAML::FpToString(std::numeric_limits<float>::quiet_NaN(), 6);
    EXPECT_FALSE(result.empty());
    // YAML typically represents NaN as ".nan"
}

TEST_F(FpToStringTest_432, FloatMax_432) {
    std::string result = YAML::FpToString(std::numeric_limits<float>::max(), 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, std::numeric_limits<float>::max());
}

TEST_F(FpToStringTest_432, FloatMin_432) {
    std::string result = YAML::FpToString(std::numeric_limits<float>::min(), 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, std::numeric_limits<float>::min());
}

TEST_F(FpToStringTest_432, FloatLowest_432) {
    std::string result = YAML::FpToString(std::numeric_limits<float>::lowest(), 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, std::numeric_limits<float>::lowest());
}

TEST_F(FpToStringTest_432, FloatDenormMin_432) {
    std::string result = YAML::FpToString(std::numeric_limits<float>::denorm_min(), 6);
    EXPECT_FALSE(result.empty());
    // denorm_min is the smallest positive denormalized float
    float parsed = std::stof(result);
    EXPECT_GT(parsed, 0.0f);
}

TEST_F(FpToStringTest_432, FloatEpsilon_432) {
    std::string result = YAML::FpToString(std::numeric_limits<float>::epsilon(), 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, std::numeric_limits<float>::epsilon());
}

// Round-trip consistency tests

TEST_F(FpToStringTest_432, RoundTripPi_432) {
    float original = 3.14159265f;
    std::string result = YAML::FpToString(original, 9);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, original);
}

TEST_F(FpToStringTest_432, RoundTripNegative_432) {
    float original = -42.5f;
    std::string result = YAML::FpToString(original, 6);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, original);
}

TEST_F(FpToStringTest_432, RoundTripOneThird_432) {
    float original = 1.0f / 3.0f;
    std::string result = YAML::FpToString(original, 9);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, original);
}

// Edge precision values

TEST_F(FpToStringTest_432, PrecisionZero_432) {
    // Precision 0 may or may not be meaningful; test it doesn't crash
    std::string result = YAML::FpToString(3.14f, 0);
    // Just ensure it doesn't crash and returns something
    // The result may be empty or a rounded value
}

TEST_F(FpToStringTest_432, HighPrecision_432) {
    std::string result = YAML::FpToString(1.23456789f, 20);
    EXPECT_FALSE(result.empty());
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, 1.23456789f);
}
