#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <limits>

// Declaration of the function under test
namespace YAML {
std::string FpToString(long double v, size_t precision);
}

class FpToStringTest_434 : public ::testing::Test {};

// Normal operation tests

TEST_F(FpToStringTest_434, PositiveInteger_434) {
    std::string result = YAML::FpToString(1.0L, 0);
    EXPECT_EQ(result, "1");
}

TEST_F(FpToStringTest_434, NegativeInteger_434) {
    std::string result = YAML::FpToString(-1.0L, 0);
    EXPECT_EQ(result, "-1");
}

TEST_F(FpToStringTest_434, Zero_434) {
    std::string result = YAML::FpToString(0.0L, 0);
    EXPECT_EQ(result, "0");
}

TEST_F(FpToStringTest_434, PositiveDecimal_434) {
    std::string result = YAML::FpToString(3.14L, 3);
    EXPECT_EQ(result, "3.14");
}

TEST_F(FpToStringTest_434, NegativeDecimal_434) {
    std::string result = YAML::FpToString(-3.14L, 3);
    EXPECT_EQ(result, "-3.14");
}

TEST_F(FpToStringTest_434, PrecisionOne_434) {
    std::string result = YAML::FpToString(3.14159L, 1);
    EXPECT_EQ(result, "3");
}

TEST_F(FpToStringTest_434, PrecisionTwo_434) {
    std::string result = YAML::FpToString(3.14159L, 2);
    EXPECT_EQ(result, "3.1");
}

TEST_F(FpToStringTest_434, PrecisionFive_434) {
    std::string result = YAML::FpToString(3.14159265L, 5);
    EXPECT_EQ(result, "3.1416");
}

TEST_F(FpToStringTest_434, DefaultPrecisionZeroUsesMaxDigits_434) {
    // When precision is 0, it should use max_digits10 for long double
    std::string result = YAML::FpToString(1.0L / 3.0L, 0);
    // The result should have many digits of precision
    EXPECT_FALSE(result.empty());
    // Should start with "0.333..."
    EXPECT_EQ(result.substr(0, 4), "0.33");
}

TEST_F(FpToStringTest_434, LargePositiveNumber_434) {
    std::string result = YAML::FpToString(1.0e+15L, 0);
    EXPECT_FALSE(result.empty());
    // Should contain the number in some form
}

TEST_F(FpToStringTest_434, LargeNegativeNumber_434) {
    std::string result = YAML::FpToString(-1.0e+15L, 0);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result[0], '-');
}

TEST_F(FpToStringTest_434, SmallPositiveNumber_434) {
    std::string result = YAML::FpToString(1.0e-15L, 0);
    EXPECT_FALSE(result.empty());
    // Should contain 'e' for scientific notation or a very small decimal
    EXPECT_NE(result, "0");
}

// Boundary conditions

TEST_F(FpToStringTest_434, NegativeZero_434) {
    std::string result = YAML::FpToString(-0.0L, 0);
    // Negative zero might be printed as "0" or "-0"
    EXPECT_FALSE(result.empty());
}

TEST_F(FpToStringTest_434, Infinity_434) {
    long double inf = std::numeric_limits<long double>::infinity();
    std::string result = YAML::FpToString(inf, 0);
    EXPECT_FALSE(result.empty());
    // Common representations: "inf", "Inf", "infinity"
    EXPECT_TRUE(result == "inf" || result == "Inf" || result == "infinity" || result == "INF");
}

TEST_F(FpToStringTest_434, NegativeInfinity_434) {
    long double neg_inf = -std::numeric_limits<long double>::infinity();
    std::string result = YAML::FpToString(neg_inf, 0);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result[0], '-');
}

TEST_F(FpToStringTest_434, NaN_434) {
    long double nan_val = std::numeric_limits<long double>::quiet_NaN();
    std::string result = YAML::FpToString(nan_val, 0);
    EXPECT_FALSE(result.empty());
    // Common representations: "nan", "NaN", "-nan"
    EXPECT_TRUE(result == "nan" || result == "NaN" || result == "-nan" || result == "-NaN" || result == "NAN" || result == "-NAN");
}

TEST_F(FpToStringTest_434, MaxLongDouble_434) {
    long double max_val = std::numeric_limits<long double>::max();
    std::string result = YAML::FpToString(max_val, 0);
    EXPECT_FALSE(result.empty());
}

TEST_F(FpToStringTest_434, MinLongDouble_434) {
    long double min_val = std::numeric_limits<long double>::min();
    std::string result = YAML::FpToString(min_val, 0);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "0");
}

TEST_F(FpToStringTest_434, DenormMinLongDouble_434) {
    long double denorm_min = std::numeric_limits<long double>::denorm_min();
    std::string result = YAML::FpToString(denorm_min, 0);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "0");
}

TEST_F(FpToStringTest_434, LowestLongDouble_434) {
    long double lowest_val = std::numeric_limits<long double>::lowest();
    std::string result = YAML::FpToString(lowest_val, 0);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result[0], '-');
}

// Precision specific tests

TEST_F(FpToStringTest_434, ExplicitHighPrecision_434) {
    std::string result = YAML::FpToString(1.0L / 7.0L, 20);
    EXPECT_FALSE(result.empty());
    // With precision 20, we should have many digits
    // Count digits after decimal point
    auto dot_pos = result.find('.');
    EXPECT_NE(dot_pos, std::string::npos);
}

TEST_F(FpToStringTest_434, PrecisionOneWithSmallNumber_434) {
    std::string result = YAML::FpToString(0.0001L, 1);
    EXPECT_FALSE(result.empty());
}

// Locale independence test (the function uses classic locale)
TEST_F(FpToStringTest_434, UsesClassicLocaleDecimalPoint_434) {
    std::string result = YAML::FpToString(1.5L, 2);
    // In the classic ("C") locale, the decimal separator is always '.'
    EXPECT_NE(result.find('.'), std::string::npos);
    EXPECT_EQ(result.find(','), std::string::npos);
}

TEST_F(FpToStringTest_434, ExactRepresentation_434) {
    // 0.5 is exactly representable in floating point
    std::string result = YAML::FpToString(0.5L, 1);
    EXPECT_EQ(result, "0.5");
}

TEST_F(FpToStringTest_434, WholeNumberWithPrecision_434) {
    std::string result = YAML::FpToString(42.0L, 4);
    EXPECT_EQ(result, "42");
}

TEST_F(FpToStringTest_434, VeryLargeExponent_434) {
    long double val = 1.23456e+100L;
    std::string result = YAML::FpToString(val, 6);
    EXPECT_FALSE(result.empty());
    // Should likely use scientific notation
}

TEST_F(FpToStringTest_434, VerySmallExponent_434) {
    long double val = 1.23456e-100L;
    std::string result = YAML::FpToString(val, 6);
    EXPECT_FALSE(result.empty());
}

TEST_F(FpToStringTest_434, EpsilonValue_434) {
    long double eps = std::numeric_limits<long double>::epsilon();
    std::string result = YAML::FpToString(eps, 0);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "0");
}
