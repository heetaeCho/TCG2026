#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <limits>

// We need to include the header that declares FpToString.
// Based on the file path, we'll try to include it appropriately.
// The function is in namespace YAML::detail::fp_formatting

namespace YAML {
namespace detail {
namespace fp_formatting {
template <typename T>
std::string FpToString(T v, int precision = 0);
}
}
}

using YAML::detail::fp_formatting::FpToString;

// ============================================================
// Tests for double
// ============================================================

class FpToStringDoubleTest_431 : public ::testing::Test {};

// --- Zero values ---

TEST_F(FpToStringDoubleTest_431, PositiveZero_431) {
    std::string result = FpToString(0.0);
    EXPECT_EQ(result, "0");
}

TEST_F(FpToStringDoubleTest_431, NegativeZero_431) {
    std::string result = FpToString(-0.0);
    // -0 might produce "-0" or "0"
    EXPECT_TRUE(result == "-0" || result == "0");
}

// --- Infinity ---

TEST_F(FpToStringDoubleTest_431, PositiveInfinity_431) {
    std::string result = FpToString(std::numeric_limits<double>::infinity());
    EXPECT_EQ(result, "inf");
}

TEST_F(FpToStringDoubleTest_431, NegativeInfinity_431) {
    std::string result = FpToString(-std::numeric_limits<double>::infinity());
    EXPECT_EQ(result, "-inf");
}

// --- NaN ---

TEST_F(FpToStringDoubleTest_431, NaN_431) {
    std::string result = FpToString(std::numeric_limits<double>::quiet_NaN());
    // NaN typically produces "nan" or "-nan"
    EXPECT_TRUE(result == "nan" || result == "-nan" || result == "NaN");
}

// --- Simple positive values ---

TEST_F(FpToStringDoubleTest_431, SimplePositiveInteger_431) {
    std::string result = FpToString(1.0);
    EXPECT_EQ(result, "1");
}

TEST_F(FpToStringDoubleTest_431, SimplePositiveValue_431) {
    std::string result = FpToString(1.5);
    EXPECT_EQ(result, "1.5");
}

TEST_F(FpToStringDoubleTest_431, SimplePositiveValue2_431) {
    std::string result = FpToString(3.14);
    // Should be some reasonable representation of 3.14
    EXPECT_FALSE(result.empty());
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 3.14);
}

// --- Simple negative values ---

TEST_F(FpToStringDoubleTest_431, SimpleNegativeValue_431) {
    std::string result = FpToString(-1.0);
    EXPECT_EQ(result[0], '-');
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, -1.0);
}

TEST_F(FpToStringDoubleTest_431, SimpleNegativeDecimal_431) {
    std::string result = FpToString(-2.5);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, -2.5);
}

// --- Values that should use scientific notation (large exponent) ---

TEST_F(FpToStringDoubleTest_431, LargeValueScientificNotation_431) {
    std::string result = FpToString(1e10);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 1e10);
}

TEST_F(FpToStringDoubleTest_431, VeryLargeValue_431) {
    std::string result = FpToString(1.23456e20);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 1.23456e20);
}

// --- Values that should use scientific notation (small exponent) ---

TEST_F(FpToStringDoubleTest_431, VerySmallPositiveValue_431) {
    std::string result = FpToString(1e-10);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 1e-10);
}

TEST_F(FpToStringDoubleTest_431, SmallNegativeExponent_431) {
    std::string result = FpToString(1e-6);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 1e-6);
}

// --- Boundary exponent values ---

TEST_F(FpToStringDoubleTest_431, ExponentAtUpperThreshold_431) {
    // upperExponentThreshold for precision=0 is 6
    // exponent == 5 should be fixed notation
    std::string result = FpToString(100000.0); // 1e5
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 100000.0);
}

TEST_F(FpToStringDoubleTest_431, ExponentAtUpperThresholdBoundary_431) {
    // exponent == 6 triggers scientific notation
    std::string result = FpToString(1000000.0); // 1e6
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 1000000.0);
}

TEST_F(FpToStringDoubleTest_431, ExponentAtLowerThresholdBoundary_431) {
    // lowerExponentThreshold is -5
    // exponent == -5 triggers scientific notation
    std::string result = FpToString(1e-5);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 1e-5);
}

TEST_F(FpToStringDoubleTest_431, ExponentJustAboveLowerThreshold_431) {
    // exponent == -4 should be fixed notation
    std::string result = FpToString(1e-4);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 1e-4);
}

// --- With precision parameter ---

TEST_F(FpToStringDoubleTest_431, WithPrecision1_431) {
    std::string result = FpToString(3.14159, 1);
    double parsed = std::stod(result);
    // With precision 1, we expect roughly 3
    EXPECT_NEAR(parsed, 3.0, 0.5);
}

TEST_F(FpToStringDoubleTest_431, WithPrecision3_431) {
    std::string result = FpToString(3.14159, 3);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 3.14, 0.01);
}

TEST_F(FpToStringDoubleTest_431, WithPrecision10_431) {
    std::string result = FpToString(3.14159265358979, 10);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 3.14159265358979, 1e-9);
}

TEST_F(FpToStringDoubleTest_431, PrecisionAffectsUpperExponentThreshold_431) {
    // With precision=3, upperExponentThreshold becomes 3
    // So 1000.0 (exponent=3) should use scientific notation
    std::string result = FpToString(1000.0, 3);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 1000.0);
    // Check it uses scientific notation
    EXPECT_NE(result.find('e'), std::string::npos);
}

// --- Rounding ---

TEST_F(FpToStringDoubleTest_431, RoundingUp_431) {
    // 1.999999 with precision 3 should round
    std::string result = FpToString(1.999999, 3);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 2.0, 0.01);
}

TEST_F(FpToStringDoubleTest_431, RoundingCarryOver_431) {
    // 9.999 with precision 1 should carry over
    std::string result = FpToString(9.999, 1);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 10.0, 0.5);
}

// --- Float type ---

class FpToStringFloatTest_431 : public ::testing::Test {};

TEST_F(FpToStringFloatTest_431, SimpleFloat_431) {
    std::string result = FpToString(1.5f);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 1.5, 0.001);
}

TEST_F(FpToStringFloatTest_431, FloatZero_431) {
    std::string result = FpToString(0.0f);
    EXPECT_EQ(result, "0");
}

TEST_F(FpToStringFloatTest_431, FloatInfinity_431) {
    std::string result = FpToString(std::numeric_limits<float>::infinity());
    EXPECT_EQ(result, "inf");
}

TEST_F(FpToStringFloatTest_431, FloatNaN_431) {
    std::string result = FpToString(std::numeric_limits<float>::quiet_NaN());
    EXPECT_TRUE(result == "nan" || result == "-nan" || result == "NaN");
}

TEST_F(FpToStringFloatTest_431, NegativeFloat_431) {
    std::string result = FpToString(-2.5f);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, -2.5, 0.001);
}

TEST_F(FpToStringFloatTest_431, LargeFloat_431) {
    std::string result = FpToString(1.0e10f);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 1.0e10, 1e5);
}

TEST_F(FpToStringFloatTest_431, SmallFloat_431) {
    std::string result = FpToString(1.0e-10f);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 1.0e-10, 1e-15);
}

TEST_F(FpToStringFloatTest_431, FloatWithPrecision_431) {
    std::string result = FpToString(3.14f, 2);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 3.1, 0.1);
}

// --- Edge cases with values near boundaries ---

TEST_F(FpToStringDoubleTest_431, ValueOne_431) {
    std::string result = FpToString(1.0);
    EXPECT_EQ(result, "1");
}

TEST_F(FpToStringDoubleTest_431, ValueMinusOne_431) {
    std::string result = FpToString(-1.0);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, -1.0);
}

TEST_F(FpToStringDoubleTest_431, SmallestNormalDouble_431) {
    double val = std::numeric_limits<double>::min();
    std::string result = FpToString(val);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, val, val * 1e-6);
}

TEST_F(FpToStringDoubleTest_431, LargestDouble_431) {
    double val = std::numeric_limits<double>::max();
    std::string result = FpToString(val);
    EXPECT_FALSE(result.empty());
    // Should be parseable
    double parsed = std::stod(result);
    // Allow some tolerance for very large values
    EXPECT_GT(parsed, 0);
}

TEST_F(FpToStringDoubleTest_431, DenormalizedDouble_431) {
    double val = std::numeric_limits<double>::denorm_min();
    std::string result = FpToString(val);
    EXPECT_FALSE(result.empty());
}

// --- Decimal point placement ---

TEST_F(FpToStringDoubleTest_431, ValueWithTrailingZeros_431) {
    std::string result = FpToString(10.0);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 10.0);
}

TEST_F(FpToStringDoubleTest_431, ValueBetweenZeroAndOne_431) {
    std::string result = FpToString(0.5);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 0.5);
}

TEST_F(FpToStringDoubleTest_431, ValueWithLeadingZerosAfterDecimal_431) {
    std::string result = FpToString(0.001);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 0.001);
}

TEST_F(FpToStringDoubleTest_431, ValueHundred_431) {
    std::string result = FpToString(100.0);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 100.0);
}

TEST_F(FpToStringDoubleTest_431, Value99999_431) {
    std::string result = FpToString(99999.0);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 99999.0);
}

// --- Scientific notation format verification ---

TEST_F(FpToStringDoubleTest_431, ScientificNotationContainsE_431) {
    std::string result = FpToString(1e20);
    EXPECT_NE(result.find('e'), std::string::npos);
}

TEST_F(FpToStringDoubleTest_431, NegativeScientificNotation_431) {
    std::string result = FpToString(-1e20);
    EXPECT_EQ(result[0], '-');
    EXPECT_NE(result.find('e'), std::string::npos);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, -1e20);
}

TEST_F(FpToStringDoubleTest_431, ScientificNotationPositiveExponentSign_431) {
    std::string result = FpToString(1e10);
    auto epos = result.find('e');
    ASSERT_NE(epos, std::string::npos);
    EXPECT_EQ(result[epos + 1], '+');
}

TEST_F(FpToStringDoubleTest_431, ScientificNotationNegativeExponentSign_431) {
    std::string result = FpToString(1e-10);
    auto epos = result.find('e');
    ASSERT_NE(epos, std::string::npos);
    EXPECT_EQ(result[epos + 1], '-');
}

// --- Various precision values ---

TEST_F(FpToStringDoubleTest_431, PrecisionZeroDefault_431) {
    // precision=0 should default to 6
    std::string result = FpToString(1.23456789);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 1.23456789, 1e-5);
}

TEST_F(FpToStringDoubleTest_431, HighPrecision_431) {
    std::string result = FpToString(1.23456789012345, 15);
    double parsed = std::stod(result);
    EXPECT_NEAR(parsed, 1.23456789012345, 1e-14);
}

// --- Verify roundtrip for common values ---

TEST_F(FpToStringDoubleTest_431, RoundtripCommonValues_431) {
    double values[] = {0.1, 0.2, 0.3, 1.0, 2.0, 10.0, 100.0, 0.5, 0.25, 0.125};
    for (double v : values) {
        std::string result = FpToString(v);
        double parsed = std::stod(result);
        EXPECT_NEAR(parsed, v, v * 1e-6) << "Failed for value: " << v << " result: " << result;
    }
}
