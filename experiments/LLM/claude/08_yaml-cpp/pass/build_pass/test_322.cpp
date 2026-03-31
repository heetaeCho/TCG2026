#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"
#include <cmath>
#include <cstdint>

using namespace YAML::jkj::dragonbox::detail::log;

class FloorLog10Pow2MinusLog10_4Over3Test_322 : public ::testing::Test {
protected:
    // Helper to compute expected value using floating point math
    // floor(e * log10(2) - log10(4/3))
    static int expected_value(int e) {
        double log10_2 = std::log10(2.0);
        double log10_4_over_3 = std::log10(4.0 / 3.0);
        double result = static_cast<double>(e) * log10_2 - log10_4_over_3;
        return static_cast<int>(std::floor(result));
    }
};

// Test with exponent = 0
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, ZeroExponent_322) {
    auto result = floor_log10_pow2_minus_log10_4_over_3(0);
    // floor(0 * log10(2) - log10(4/3)) = floor(-log10(4/3)) = floor(-0.12494...) = -1
    EXPECT_EQ(result, expected_value(0));
}

// Test with exponent = 1
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, ExponentOne_322) {
    auto result = floor_log10_pow2_minus_log10_4_over_3(1);
    // floor(log10(2) - log10(4/3)) = floor(0.30103 - 0.12494) = floor(0.17609) = 0
    EXPECT_EQ(result, expected_value(1));
}

// Test with exponent = -1
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, ExponentNegativeOne_322) {
    auto result = floor_log10_pow2_minus_log10_4_over_3(-1);
    // floor(-log10(2) - log10(4/3)) = floor(-0.30103 - 0.12494) = floor(-0.42597) = -1
    EXPECT_EQ(result, expected_value(-1));
}

// Test with small positive exponents
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, SmallPositiveExponents_322) {
    for (int e = 0; e <= 100; ++e) {
        auto result = floor_log10_pow2_minus_log10_4_over_3(e);
        EXPECT_EQ(result, expected_value(e)) << "Failed for e=" << e;
    }
}

// Test with small negative exponents
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, SmallNegativeExponents_322) {
    for (int e = -100; e < 0; ++e) {
        auto result = floor_log10_pow2_minus_log10_4_over_3(e);
        EXPECT_EQ(result, expected_value(e)) << "Failed for e=" << e;
    }
}

// Test with exponent = 10
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, ExponentTen_322) {
    auto result = floor_log10_pow2_minus_log10_4_over_3(10);
    // floor(10 * 0.30103 - 0.12494) = floor(3.0103 - 0.12494) = floor(2.88536) = 2
    EXPECT_EQ(result, expected_value(10));
}

// Test with larger positive exponents
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, LargerPositiveExponents_322) {
    for (int e = 100; e <= 1000; e += 50) {
        auto result = floor_log10_pow2_minus_log10_4_over_3(e);
        EXPECT_EQ(result, expected_value(e)) << "Failed for e=" << e;
    }
}

// Test with larger negative exponents
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, LargerNegativeExponents_322) {
    for (int e = -1000; e <= -100; e += 50) {
        auto result = floor_log10_pow2_minus_log10_4_over_3(e);
        EXPECT_EQ(result, expected_value(e)) << "Failed for e=" << e;
    }
}

// Test boundary: minimum default exponent
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, MinDefaultExponent_322) {
    auto result = floor_log10_pow2_minus_log10_4_over_3(-2985);
    EXPECT_EQ(result, expected_value(-2985));
}

// Test boundary: maximum default exponent
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, MaxDefaultExponent_322) {
    auto result = floor_log10_pow2_minus_log10_4_over_3(2936);
    EXPECT_EQ(result, expected_value(2936));
}

// Test near boundary: one above minimum
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, NearMinExponent_322) {
    auto result = floor_log10_pow2_minus_log10_4_over_3(-2984);
    EXPECT_EQ(result, expected_value(-2984));
}

// Test near boundary: one below maximum
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, NearMaxExponent_322) {
    auto result = floor_log10_pow2_minus_log10_4_over_3(2935);
    EXPECT_EQ(result, expected_value(2935));
}

// Test that result is monotonically non-decreasing
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, MonotonicallyNonDecreasing_322) {
    int prev = floor_log10_pow2_minus_log10_4_over_3(-500);
    for (int e = -499; e <= 500; ++e) {
        int curr = floor_log10_pow2_minus_log10_4_over_3(e);
        EXPECT_GE(curr, prev) << "Not monotonic at e=" << e;
        prev = curr;
    }
}

// Test constexpr evaluation
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, ConstexprEvaluation_322) {
    constexpr auto result = floor_log10_pow2_minus_log10_4_over_3(0);
    EXPECT_EQ(result, expected_value(0));
}

// Test constexpr with positive
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, ConstexprPositive_322) {
    constexpr auto result = floor_log10_pow2_minus_log10_4_over_3(100);
    EXPECT_EQ(result, expected_value(100));
}

// Test constexpr with negative
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, ConstexprNegative_322) {
    constexpr auto result = floor_log10_pow2_minus_log10_4_over_3(-100);
    EXPECT_EQ(result, expected_value(-100));
}

// Test with custom template parameters for narrower range
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, CustomRange_322) {
    auto result = floor_log10_pow2_minus_log10_4_over_3<-100, 100>(50);
    EXPECT_EQ(result, expected_value(50));
}

// Test specific known values around where the floor function steps
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, StepValues_322) {
    // e=4: floor(4*0.30103 - 0.12494) = floor(1.07918) = 1
    EXPECT_EQ(floor_log10_pow2_minus_log10_4_over_3(4), expected_value(4));
    
    // e=7: floor(7*0.30103 - 0.12494) = floor(1.98227) = 1
    EXPECT_EQ(floor_log10_pow2_minus_log10_4_over_3(7), expected_value(7));
    
    // e=3: floor(3*0.30103 - 0.12494) = floor(0.77815) = 0
    EXPECT_EQ(floor_log10_pow2_minus_log10_4_over_3(3), expected_value(3));
}

// Comprehensive range test for typical float/double exponent ranges
TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, FloatExponentRange_322) {
    // IEEE 754 float: exponents roughly -149 to 127
    for (int e = -149; e <= 127; ++e) {
        auto result = floor_log10_pow2_minus_log10_4_over_3(e);
        EXPECT_EQ(result, expected_value(e)) << "Failed for e=" << e;
    }
}

TEST_F(FloorLog10Pow2MinusLog10_4Over3Test_322, DoubleExponentRange_322) {
    // IEEE 754 double: exponents roughly -1074 to 1023
    for (int e = -1074; e <= 1023; ++e) {
        auto result = floor_log10_pow2_minus_log10_4_over_3(e);
        EXPECT_EQ(result, expected_value(e)) << "Failed for e=" << e;
    }
}
