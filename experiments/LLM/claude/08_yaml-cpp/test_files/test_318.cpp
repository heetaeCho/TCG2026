#include "gtest/gtest.h"
#include "contrib/dragonbox.h"

// The dragonbox.h header in yaml-cpp defines several log computation helpers.
// We test the publicly available floor_log10_pow2, floor_log2_pow10, 
// floor_log10_pow2_minus_log10_4_over_3 functions which use compute internally.

namespace {

using namespace YAML::jkj::dragonbox::detail;

// Tests for floor_log10_pow2
class FloorLog10Pow2Test_318 : public ::testing::Test {};

TEST_F(FloorLog10Pow2Test_318, ZeroExponent_318) {
    // floor(0 * log10(2)) = 0
    auto result = log::floor_log10_pow2(0);
    EXPECT_EQ(result, 0);
}

TEST_F(FloorLog10Pow2Test_318, PositiveExponent_318) {
    // floor(10 * log10(2)) = floor(3.0103) = 3
    auto result = log::floor_log10_pow2(10);
    EXPECT_EQ(result, 3);
}

TEST_F(FloorLog10Pow2Test_318, ExponentOne_318) {
    // floor(1 * log10(2)) = floor(0.30103) = 0
    auto result = log::floor_log10_pow2(1);
    EXPECT_EQ(result, 0);
}

TEST_F(FloorLog10Pow2Test_318, ExponentThree_318) {
    // floor(3 * log10(2)) = floor(0.903) = 0
    auto result = log::floor_log10_pow2(3);
    EXPECT_EQ(result, 0);
}

TEST_F(FloorLog10Pow2Test_318, ExponentFour_318) {
    // floor(4 * log10(2)) = floor(1.204) = 1
    auto result = log::floor_log10_pow2(4);
    EXPECT_EQ(result, 1);
}

TEST_F(FloorLog10Pow2Test_318, NegativeExponent_318) {
    // floor(-1 * log10(2)) = floor(-0.30103) = -1
    auto result = log::floor_log10_pow2(-1);
    EXPECT_EQ(result, -1);
}

TEST_F(FloorLog10Pow2Test_318, NegativeExponentTen_318) {
    // floor(-10 * log10(2)) = floor(-3.0103) = -4
    auto result = log::floor_log10_pow2(-10);
    EXPECT_EQ(result, -4);
}

TEST_F(FloorLog10Pow2Test_318, LargePositiveExponent_318) {
    // floor(100 * log10(2)) = floor(30.103) = 30
    auto result = log::floor_log10_pow2(100);
    EXPECT_EQ(result, 30);
}

TEST_F(FloorLog10Pow2Test_318, LargeNegativeExponent_318) {
    // floor(-100 * log10(2)) = floor(-30.103) = -31
    auto result = log::floor_log10_pow2(-100);
    EXPECT_EQ(result, -31);
}

// Tests for floor_log2_pow10
class FloorLog2Pow10Test_318 : public ::testing::Test {};

TEST_F(FloorLog2Pow10Test_318, ZeroExponent_318) {
    // floor(0 * log2(10)) = 0
    auto result = log::floor_log2_pow10(0);
    EXPECT_EQ(result, 0);
}

TEST_F(FloorLog2Pow10Test_318, PositiveExponentOne_318) {
    // floor(1 * log2(10)) = floor(3.3219) = 3
    auto result = log::floor_log2_pow10(1);
    EXPECT_EQ(result, 3);
}

TEST_F(FloorLog2Pow10Test_318, PositiveExponentTwo_318) {
    // floor(2 * log2(10)) = floor(6.6439) = 6
    auto result = log::floor_log2_pow10(2);
    EXPECT_EQ(result, 6);
}

TEST_F(FloorLog2Pow10Test_318, NegativeExponentOne_318) {
    // floor(-1 * log2(10)) = floor(-3.3219) = -4
    auto result = log::floor_log2_pow10(-1);
    EXPECT_EQ(result, -4);
}

TEST_F(FloorLog2Pow10Test_318, PositiveExponentTen_318) {
    // floor(10 * log2(10)) = floor(33.219) = 33
    auto result = log::floor_log2_pow10(10);
    EXPECT_EQ(result, 33);
}

TEST_F(FloorLog2Pow10Test_318, NegativeExponentTen_318) {
    // floor(-10 * log2(10)) = floor(-33.219) = -34
    auto result = log::floor_log2_pow10(-10);
    EXPECT_EQ(result, -34);
}

// Tests for floor_log10_pow2_minus_log10_4_over_3
class FloorLog10Pow2MinusLog10FourOverThreeTest_318 : public ::testing::Test {};

TEST_F(FloorLog10Pow2MinusLog10FourOverThreeTest_318, ZeroExponent_318) {
    // floor(0 * log10(2) - log10(4/3)) = floor(-0.12494) = -1
    auto result = log::floor_log10_pow2_minus_log10_4_over_3(0);
    EXPECT_EQ(result, -1);
}

TEST_F(FloorLog10Pow2MinusLog10FourOverThreeTest_318, PositiveExponentOne_318) {
    // floor(1 * log10(2) - log10(4/3)) = floor(0.30103 - 0.12494) = floor(0.17609) = 0
    auto result = log::floor_log10_pow2_minus_log10_4_over_3(1);
    EXPECT_EQ(result, 0);
}

TEST_F(FloorLog10Pow2MinusLog10FourOverThreeTest_318, PositiveExponentTen_318) {
    // floor(10 * log10(2) - log10(4/3)) = floor(3.0103 - 0.12494) = floor(2.8854) = 2
    auto result = log::floor_log10_pow2_minus_log10_4_over_3(10);
    EXPECT_EQ(result, 2);
}

TEST_F(FloorLog10Pow2MinusLog10FourOverThreeTest_318, NegativeExponentOne_318) {
    // floor(-1 * log10(2) - log10(4/3)) = floor(-0.30103 - 0.12494) = floor(-0.42597) = -1
    auto result = log::floor_log10_pow2_minus_log10_4_over_3(-1);
    EXPECT_EQ(result, -1);
}

// Constexpr tests
class ConstexprLogTest_318 : public ::testing::Test {};

TEST_F(ConstexprLogTest_318, FloorLog10Pow2IsConstexpr_318) {
    constexpr auto val = log::floor_log10_pow2(10);
    EXPECT_EQ(val, 3);
}

TEST_F(ConstexprLogTest_318, FloorLog2Pow10IsConstexpr_318) {
    constexpr auto val = log::floor_log2_pow10(1);
    EXPECT_EQ(val, 3);
}

TEST_F(ConstexprLogTest_318, ConsistencyCheck_318) {
    // For various exponents, verify that floor_log10_pow2 and floor_log2_pow10 
    // are roughly inverse operations
    for (int e = 1; e <= 50; ++e) {
        int log10_result = log::floor_log10_pow2(e);
        int log2_result = log::floor_log2_pow10(log10_result);
        // log2(10^floor(e*log10(2))) should be <= e
        EXPECT_LE(log2_result, e) << "Failed for e=" << e;
    }
}

} // namespace
