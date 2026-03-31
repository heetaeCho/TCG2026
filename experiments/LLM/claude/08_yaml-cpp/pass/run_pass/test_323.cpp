#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"
#include <cstdint>
#include <cmath>

namespace {

// Helper to compute the expected floor(log5(2^e)) = floor(e * log5(2)) = floor(e * ln(2)/ln(5))
// log5(2) = ln(2)/ln(5) ≈ 0.43067655807339306
double exact_floor_log5_pow2(int e) {
    if (e >= 0) {
        return std::floor(static_cast<double>(e) * std::log(2.0) / std::log(5.0));
    } else {
        return std::floor(static_cast<double>(e) * std::log(2.0) / std::log(5.0));
    }
}

using namespace YAML::jkj::dragonbox::detail::log;

// Test with zero exponent
TEST(FloorLog5Pow2Test_323, ZeroExponent_323) {
    // floor(log5(2^0)) = floor(log5(1)) = floor(0) = 0
    auto result = floor_log5_pow2(0);
    EXPECT_EQ(result, 0);
}

// Test with exponent = 1
TEST(FloorLog5Pow2Test_323, ExponentOne_323) {
    // floor(log5(2^1)) = floor(log5(2)) = floor(0.43067...) = 0
    auto result = floor_log5_pow2(1);
    EXPECT_EQ(result, 0);
}

// Test with exponent = 2
TEST(FloorLog5Pow2Test_323, ExponentTwo_323) {
    // floor(log5(2^2)) = floor(log5(4)) = floor(0.8613...) = 0
    auto result = floor_log5_pow2(2);
    EXPECT_EQ(result, 0);
}

// Test with exponent = 3
TEST(FloorLog5Pow2Test_323, ExponentThree_323) {
    // floor(log5(2^3)) = floor(log5(8)) = floor(1.292...) = 1
    auto result = floor_log5_pow2(3);
    EXPECT_EQ(result, 1);
}

// Test with small positive exponents
TEST(FloorLog5Pow2Test_323, SmallPositiveExponents_323) {
    for (int e = 0; e <= 100; ++e) {
        auto result = floor_log5_pow2(e);
        int expected = static_cast<int>(exact_floor_log5_pow2(e));
        EXPECT_EQ(result, expected) << "Failed for e=" << e;
    }
}

// Test with negative exponents
TEST(FloorLog5Pow2Test_323, NegativeExponentMinusOne_323) {
    // floor(log5(2^(-1))) = floor(-0.43067...) = -1
    auto result = floor_log5_pow2(-1);
    EXPECT_EQ(result, -1);
}

// Test with exponent = -2
TEST(FloorLog5Pow2Test_323, NegativeExponentMinusTwo_323) {
    // floor(log5(2^(-2))) = floor(-0.8613...) = -1
    auto result = floor_log5_pow2(-2);
    EXPECT_EQ(result, -1);
}

// Test with exponent = -3
TEST(FloorLog5Pow2Test_323, NegativeExponentMinusThree_323) {
    // floor(log5(2^(-3))) = floor(-1.292...) = -2
    auto result = floor_log5_pow2(-3);
    EXPECT_EQ(result, -2);
}

// Test small negative exponents
TEST(FloorLog5Pow2Test_323, SmallNegativeExponents_323) {
    for (int e = -100; e < 0; ++e) {
        auto result = floor_log5_pow2(e);
        int expected = static_cast<int>(exact_floor_log5_pow2(e));
        EXPECT_EQ(result, expected) << "Failed for e=" << e;
    }
}

// Test with larger positive exponents
TEST(FloorLog5Pow2Test_323, LargerPositiveExponents_323) {
    for (int e = 100; e <= 500; ++e) {
        auto result = floor_log5_pow2(e);
        int expected = static_cast<int>(exact_floor_log5_pow2(e));
        EXPECT_EQ(result, expected) << "Failed for e=" << e;
    }
}

// Test with larger negative exponents
TEST(FloorLog5Pow2Test_323, LargerNegativeExponents_323) {
    for (int e = -500; e <= -100; ++e) {
        auto result = floor_log5_pow2(e);
        int expected = static_cast<int>(exact_floor_log5_pow2(e));
        EXPECT_EQ(result, expected) << "Failed for e=" << e;
    }
}

// Test boundary: near default min_exponent
TEST(FloorLog5Pow2Test_323, NearDefaultMinExponent_323) {
    // Test near the default min_exponent of -1831
    auto result = floor_log5_pow2(-1831);
    int expected = static_cast<int>(exact_floor_log5_pow2(-1831));
    EXPECT_EQ(result, expected);
}

// Test boundary: near default max_exponent
TEST(FloorLog5Pow2Test_323, NearDefaultMaxExponent_323) {
    // Test near the default max_exponent of 1831
    auto result = floor_log5_pow2(1831);
    int expected = static_cast<int>(exact_floor_log5_pow2(1831));
    EXPECT_EQ(result, expected);
}

// Test at exact default min exponent boundary
TEST(FloorLog5Pow2Test_323, ExactMinExponentBoundary_323) {
    auto result = floor_log5_pow2(-1831);
    // floor(-1831 * log5(2)) = floor(-1831 * 0.43067...) = floor(-788.77...) = -789
    int expected = static_cast<int>(std::floor(-1831.0 * std::log(2.0) / std::log(5.0)));
    EXPECT_EQ(result, expected);
}

// Test at exact default max exponent boundary
TEST(FloorLog5Pow2Test_323, ExactMaxExponentBoundary_323) {
    auto result = floor_log5_pow2(1831);
    // floor(1831 * log5(2)) = floor(1831 * 0.43067...) = floor(788.77...) = 788
    int expected = static_cast<int>(std::floor(1831.0 * std::log(2.0) / std::log(5.0)));
    EXPECT_EQ(result, expected);
}

// Test that function is constexpr
TEST(FloorLog5Pow2Test_323, ConstexprEvaluation_323) {
    constexpr auto result = floor_log5_pow2(10);
    // floor(log5(2^10)) = floor(log5(1024)) = floor(4.3067...) = 4
    EXPECT_EQ(result, 4);
}

// Test with exponent that gives exact integer result (if any exist)
TEST(FloorLog5Pow2Test_323, ExponentGivingNearIntegerResult_323) {
    // log5(2) is irrational, so e * log5(2) never exactly equals an integer for nonzero integer e
    // But we test that near-integer cases are handled correctly
    // e=7: 7 * 0.43067... = 3.01473... -> floor = 3
    auto result = floor_log5_pow2(7);
    EXPECT_EQ(result, 3);
}

// Comprehensive range test with moderate range
TEST(FloorLog5Pow2Test_323, ComprehensiveRangeTest_323) {
    for (int e = -1000; e <= 1000; ++e) {
        auto result = floor_log5_pow2(e);
        int expected = static_cast<int>(exact_floor_log5_pow2(e));
        EXPECT_EQ(result, expected) << "Failed for e=" << e;
    }
}

// Test with int32_t type explicitly
TEST(FloorLog5Pow2Test_323, Int32Input_323) {
    int32_t e = 42;
    auto result = floor_log5_pow2(e);
    int expected = static_cast<int>(exact_floor_log5_pow2(42));
    EXPECT_EQ(result, expected);
}

// Test with powers of 2 as exponents
TEST(FloorLog5Pow2Test_323, PowersOfTwoAsExponents_323) {
    auto r1 = floor_log5_pow2(1);
    EXPECT_EQ(r1, 0);
    
    auto r2 = floor_log5_pow2(2);
    EXPECT_EQ(r2, 0);
    
    auto r4 = floor_log5_pow2(4);
    EXPECT_EQ(r4, 1);
    
    auto r8 = floor_log5_pow2(8);
    EXPECT_EQ(r8, 3);
    
    auto r16 = floor_log5_pow2(16);
    EXPECT_EQ(r16, 6);
    
    auto r32 = floor_log5_pow2(32);
    EXPECT_EQ(r32, 13);
    
    auto r64 = floor_log5_pow2(64);
    EXPECT_EQ(r64, 27);
    
    auto r128 = floor_log5_pow2(128);
    EXPECT_EQ(r128, 55);
    
    auto r256 = floor_log5_pow2(256);
    EXPECT_EQ(r256, 110);
    
    auto r512 = floor_log5_pow2(512);
    EXPECT_EQ(r512, 220);
    
    auto r1024 = floor_log5_pow2(1024);
    EXPECT_EQ(r1024, 440);
}

// Test negative powers of 2 as exponents
TEST(FloorLog5Pow2Test_323, NegativePowersOfTwoAsExponents_323) {
    auto r = floor_log5_pow2(-1);
    EXPECT_EQ(r, -1);
    
    r = floor_log5_pow2(-2);
    EXPECT_EQ(r, -1);
    
    r = floor_log5_pow2(-4);
    EXPECT_EQ(r, -2);
    
    r = floor_log5_pow2(-8);
    EXPECT_EQ(r, -4);
    
    r = floor_log5_pow2(-16);
    EXPECT_EQ(r, -7);
    
    r = floor_log5_pow2(-64);
    EXPECT_EQ(r, -28);
    
    r = floor_log5_pow2(-256);
    EXPECT_EQ(r, -111);
    
    r = floor_log5_pow2(-1024);
    EXPECT_EQ(r, -441);
}

} // anonymous namespace
