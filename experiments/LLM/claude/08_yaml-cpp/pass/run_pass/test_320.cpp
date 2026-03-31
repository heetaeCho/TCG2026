#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"
#include <cmath>
#include <cstdint>

namespace {

using namespace YAML::jkj::dragonbox::detail::log;

class FloorLog10Pow2Test_320 : public ::testing::Test {
protected:
    // Helper to compute the expected value using floating point math
    // floor(e * log10(2))
    static int expected_floor_log10_pow2(int e) {
        // log10(2) ≈ 0.30102999566...
        return static_cast<int>(std::floor(static_cast<double>(e) * std::log10(2.0)));
    }
};

// Test zero exponent: floor(log10(2^0)) = floor(log10(1)) = 0
TEST_F(FloorLog10Pow2Test_320, ZeroExponent_320) {
    auto result = floor_log10_pow2(0);
    EXPECT_EQ(result, 0);
}

// Test exponent 1: floor(log10(2^1)) = floor(log10(2)) = floor(0.301...) = 0
TEST_F(FloorLog10Pow2Test_320, ExponentOne_320) {
    auto result = floor_log10_pow2(1);
    EXPECT_EQ(result, 0);
}

// Test exponent 10: floor(log10(2^10)) = floor(log10(1024)) = floor(3.0103...) = 3
TEST_F(FloorLog10Pow2Test_320, ExponentTen_320) {
    auto result = floor_log10_pow2(10);
    EXPECT_EQ(result, 3);
}

// Test negative exponent -1: floor(log10(2^-1)) = floor(log10(0.5)) = floor(-0.301...) = -1
TEST_F(FloorLog10Pow2Test_320, NegativeExponentOne_320) {
    auto result = floor_log10_pow2(-1);
    EXPECT_EQ(result, -1);
}

// Test negative exponent -10: floor(log10(2^-10)) = floor(-3.0103...) = -4
TEST_F(FloorLog10Pow2Test_320, NegativeExponentTen_320) {
    auto result = floor_log10_pow2(-10);
    EXPECT_EQ(result, -4);
}

// Test exponent where result is exact: 2^10 = 1024, floor(log10(1024)) = 3
TEST_F(FloorLog10Pow2Test_320, ExponentProducingKnownPower_320) {
    auto result = floor_log10_pow2(10);
    EXPECT_EQ(result, 3);
}

// Test small positive exponents
TEST_F(FloorLog10Pow2Test_320, SmallPositiveExponents_320) {
    // floor(log10(2^3)) = floor(log10(8)) = floor(0.903...) = 0
    EXPECT_EQ(floor_log10_pow2(3), 0);
    // floor(log10(2^4)) = floor(log10(16)) = floor(1.204...) = 1
    EXPECT_EQ(floor_log10_pow2(4), 1);
    // floor(log10(2^7)) = floor(log10(128)) = floor(2.107...) = 2
    EXPECT_EQ(floor_log10_pow2(7), 2);
}

// Test small negative exponents
TEST_F(FloorLog10Pow2Test_320, SmallNegativeExponents_320) {
    // floor(log10(2^-3)) = floor(-0.903...) = -1
    EXPECT_EQ(floor_log10_pow2(-3), -1);
    // floor(log10(2^-4)) = floor(-1.204...) = -2
    EXPECT_EQ(floor_log10_pow2(-4), -2);
    // floor(log10(2^-7)) = floor(-2.107...) = -3
    EXPECT_EQ(floor_log10_pow2(-7), -3);
}

// Test larger positive exponents
TEST_F(FloorLog10Pow2Test_320, LargerPositiveExponents_320) {
    // floor(log10(2^100)) = floor(30.103...) = 30
    EXPECT_EQ(floor_log10_pow2(100), 30);
    // floor(log10(2^1000)) = floor(301.03...) = 301
    EXPECT_EQ(floor_log10_pow2(1000), 301);
    // floor(log10(2^1023)) = floor(307.95...) = 307
    EXPECT_EQ(floor_log10_pow2(1023), 307);
}

// Test larger negative exponents
TEST_F(FloorLog10Pow2Test_320, LargerNegativeExponents_320) {
    // floor(log10(2^-100)) = floor(-30.103...) = -31
    EXPECT_EQ(floor_log10_pow2(-100), -31);
    // floor(log10(2^-1000)) = floor(-301.03...) = -302
    EXPECT_EQ(floor_log10_pow2(-1000), -302);
    // floor(log10(2^-1074)) = floor(-323.306...) = -324
    EXPECT_EQ(floor_log10_pow2(-1074), -324);
}

// Test boundary values near the default template parameter limits
TEST_F(FloorLog10Pow2Test_320, BoundaryExponents_320) {
    // At or near the max_exponent default of 2620
    auto result_max = floor_log10_pow2(2620);
    EXPECT_EQ(result_max, expected_floor_log10_pow2(2620));
    
    // At or near the min_exponent default of -2620
    auto result_min = floor_log10_pow2(-2620);
    EXPECT_EQ(result_min, expected_floor_log10_pow2(-2620));
}

// Test exponents relevant to IEEE 754 double precision
TEST_F(FloorLog10Pow2Test_320, DoublePrecisionExponents_320) {
    // Max exponent for double: 1023
    EXPECT_EQ(floor_log10_pow2(1023), expected_floor_log10_pow2(1023));
    // Min exponent for double (subnormal): -1074
    EXPECT_EQ(floor_log10_pow2(-1074), expected_floor_log10_pow2(-1074));
    // Min normal exponent for double: -1022
    EXPECT_EQ(floor_log10_pow2(-1022), expected_floor_log10_pow2(-1022));
}

// Test exponents relevant to IEEE 754 single precision
TEST_F(FloorLog10Pow2Test_320, SinglePrecisionExponents_320) {
    // Max exponent for float: 127
    EXPECT_EQ(floor_log10_pow2(127), expected_floor_log10_pow2(127));
    // Min exponent for float (subnormal): -149
    EXPECT_EQ(floor_log10_pow2(-149), expected_floor_log10_pow2(-149));
    // Min normal exponent for float: -126
    EXPECT_EQ(floor_log10_pow2(-126), expected_floor_log10_pow2(-126));
}

// Test constexpr evaluation
TEST_F(FloorLog10Pow2Test_320, ConstexprEvaluation_320) {
    constexpr auto val = floor_log10_pow2(10);
    EXPECT_EQ(val, 3);
    
    constexpr auto val_neg = floor_log10_pow2(-10);
    EXPECT_EQ(val_neg, -4);
    
    constexpr auto val_zero = floor_log10_pow2(0);
    EXPECT_EQ(val_zero, 0);
}

// Test a range of positive values for consistency with mathematical definition
TEST_F(FloorLog10Pow2Test_320, PositiveRangeConsistency_320) {
    for (int e = 0; e <= 2620; ++e) {
        auto result = floor_log10_pow2(e);
        int expected = expected_floor_log10_pow2(e);
        EXPECT_EQ(result, expected) << "Failed for exponent e=" << e;
    }
}

// Test a range of negative values for consistency with mathematical definition
TEST_F(FloorLog10Pow2Test_320, NegativeRangeConsistency_320) {
    for (int e = -2620; e < 0; ++e) {
        auto result = floor_log10_pow2(e);
        int expected = expected_floor_log10_pow2(e);
        EXPECT_EQ(result, expected) << "Failed for exponent e=" << e;
    }
}

// Test with exponent 2: floor(log10(4)) = floor(0.602...) = 0
TEST_F(FloorLog10Pow2Test_320, ExponentTwo_320) {
    EXPECT_EQ(floor_log10_pow2(2), 0);
}

// Test with exponent that gives exact integer log10: none are exact for powers of 2 except 0
// But test near boundaries where floor changes
TEST_F(FloorLog10Pow2Test_320, FloorTransitionPoints_320) {
    // 2^3 = 8 < 10, so floor(log10(8)) = 0
    EXPECT_EQ(floor_log10_pow2(3), 0);
    // 2^4 = 16 > 10, so floor(log10(16)) = 1
    EXPECT_EQ(floor_log10_pow2(4), 1);
    
    // 2^6 = 64 < 100, so floor(log10(64)) = 1
    EXPECT_EQ(floor_log10_pow2(6), 1);
    // 2^7 = 128 > 100, so floor(log10(128)) = 2
    EXPECT_EQ(floor_log10_pow2(7), 2);
    
    // 2^9 = 512 < 1000, so floor(log10(512)) = 2
    EXPECT_EQ(floor_log10_pow2(9), 2);
    // 2^10 = 1024 > 1000, so floor(log10(1024)) = 3
    EXPECT_EQ(floor_log10_pow2(10), 3);
}

// Test noexcept guarantee
TEST_F(FloorLog10Pow2Test_320, NoexceptGuarantee_320) {
    EXPECT_TRUE(noexcept(floor_log10_pow2(0)));
    EXPECT_TRUE(noexcept(floor_log10_pow2(100)));
    EXPECT_TRUE(noexcept(floor_log10_pow2(-100)));
}

} // namespace
