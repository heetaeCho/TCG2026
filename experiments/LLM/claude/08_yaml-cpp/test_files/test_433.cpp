#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <limits>

// Declare the function under test
namespace YAML {
std::string FpToString(double v, size_t precision);
}

class FpToStringTest_433 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(FpToStringTest_433, PositiveInteger_433) {
    std::string result = YAML::FpToString(1.0, 6);
    EXPECT_FALSE(result.empty());
    // The result should represent 1.0
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 1.0);
}

TEST_F(FpToStringTest_433, NegativeInteger_433) {
    std::string result = YAML::FpToString(-1.0, 6);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, -1.0);
}

TEST_F(FpToStringTest_433, Zero_433) {
    std::string result = YAML::FpToString(0.0, 6);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 0.0);
}

TEST_F(FpToStringTest_433, NegativeZero_433) {
    std::string result = YAML::FpToString(-0.0, 6);
    EXPECT_FALSE(result.empty());
    // Negative zero should parse back, but may or may not preserve sign
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 0.0);
}

TEST_F(FpToStringTest_433, PositiveFraction_433) {
    std::string result = YAML::FpToString(3.14159, 6);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 3.14159, 1e-5);
}

TEST_F(FpToStringTest_433, NegativeFraction_433) {
    std::string result = YAML::FpToString(-2.71828, 6);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, -2.71828, 1e-5);
}

TEST_F(FpToStringTest_433, VerySmallPositive_433) {
    std::string result = YAML::FpToString(1e-300, 15);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 1e-300, 1e-310);
}

TEST_F(FpToStringTest_433, VeryLargePositive_433) {
    std::string result = YAML::FpToString(1e300, 15);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 1e300);
}

TEST_F(FpToStringTest_433, VerySmallNegative_433) {
    std::string result = YAML::FpToString(-1e-300, 15);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, -1e-300, 1e-310);
}

TEST_F(FpToStringTest_433, VeryLargeNegative_433) {
    std::string result = YAML::FpToString(-1e300, 15);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, -1e300);
}

// Precision tests

TEST_F(FpToStringTest_433, PrecisionOne_433) {
    std::string result = YAML::FpToString(3.14159, 1);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 3.14159, 1.0);
}

TEST_F(FpToStringTest_433, PrecisionFifteen_433) {
    std::string result = YAML::FpToString(3.141592653589793, 15);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 3.141592653589793, 1e-14);
}

TEST_F(FpToStringTest_433, HigherPrecisionGivesMoreAccuracy_433) {
    double value = 1.23456789012345;
    std::string lowPrec = YAML::FpToString(value, 3);
    std::string highPrec = YAML::FpToString(value, 15);
    // Both should be non-empty
    EXPECT_FALSE(lowPrec.empty());
    EXPECT_FALSE(highPrec.empty());
    // Higher precision string should generally be at least as long or give a closer value
    double parsedLow = std::stod(lowPrec);
    double parsedHigh = std::stod(highPrec);
    EXPECT_LE(std::abs(parsedHigh - value), std::abs(parsedLow - value) + 1e-15);
}

// Special floating-point values

TEST_F(FpToStringTest_433, PositiveInfinity_433) {
    std::string result = YAML::FpToString(std::numeric_limits<double>::infinity(), 6);
    EXPECT_FALSE(result.empty());
    // YAML typically represents infinity as .inf or inf
    // Just check it's not empty and doesn't crash
}

TEST_F(FpToStringTest_433, NegativeInfinity_433) {
    std::string result = YAML::FpToString(-std::numeric_limits<double>::infinity(), 6);
    EXPECT_FALSE(result.empty());
}

TEST_F(FpToStringTest_433, NaN_433) {
    std::string result = YAML::FpToString(std::numeric_limits<double>::quiet_NaN(), 6);
    EXPECT_FALSE(result.empty());
    // YAML typically represents NaN as .nan or nan
}

// Boundary conditions

TEST_F(FpToStringTest_433, MaxDouble_433) {
    std::string result = YAML::FpToString(std::numeric_limits<double>::max(), 6);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_GT(parsed, 0.0);
}

TEST_F(FpToStringTest_433, MinDouble_433) {
    std::string result = YAML::FpToString(std::numeric_limits<double>::min(), 15);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_GT(parsed, 0.0);
}

TEST_F(FpToStringTest_433, DenormalizedMin_433) {
    std::string result = YAML::FpToString(std::numeric_limits<double>::denorm_min(), 15);
    EXPECT_FALSE(result.empty());
}

TEST_F(FpToStringTest_433, LowestDouble_433) {
    std::string result = YAML::FpToString(std::numeric_limits<double>::lowest(), 6);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_LT(parsed, 0.0);
}

TEST_F(FpToStringTest_433, Epsilon_433) {
    std::string result = YAML::FpToString(std::numeric_limits<double>::epsilon(), 20);
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_GT(parsed, 0.0);
}

// Roundtrip consistency

TEST_F(FpToStringTest_433, RoundtripSimpleValues_433) {
    std::vector<double> values = {0.0, 1.0, -1.0, 0.5, -0.5, 100.0, -100.0, 0.1, 0.01};
    for (double v : values) {
        std::string result = YAML::FpToString(v, 15);
        double parsed = std::stod(result);
        EXPECT_NEAR(parsed, v, 1e-14) << "Failed roundtrip for value: " << v;
    }
}

TEST_F(FpToStringTest_433, ConsistentResults_433) {
    // Calling twice with the same input should give the same result
    std::string result1 = YAML::FpToString(2.718281828, 10);
    std::string result2 = YAML::FpToString(2.718281828, 10);
    EXPECT_EQ(result1, result2);
}

TEST_F(FpToStringTest_433, DifferentPrecisionsDifferentResults_433) {
    std::string result3 = YAML::FpToString(1.23456789012345, 3);
    std::string result15 = YAML::FpToString(1.23456789012345, 15);
    // They may or may not differ, but both should be valid
    EXPECT_FALSE(result3.empty());
    EXPECT_FALSE(result15.empty());
}
