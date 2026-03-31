#include <gtest/gtest.h>
#include <cmath>
#include <cstdint>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::detail::log;

// Helper to compute the expected value: floor(e * log5(2) - log5(3))
// log5(2) = ln(2)/ln(5), log5(3) = ln(3)/ln(5)
inline int expected_floor_log5_pow2_minus_log5_3(int e) {
    double log5_2 = std::log(2.0) / std::log(5.0);
    double log5_3 = std::log(3.0) / std::log(5.0);
    double result = static_cast<double>(e) * log5_2 - log5_3;
    return static_cast<int>(std::floor(result));
}

class FloorLog5Pow2MinusLog5_3Test_324 : public ::testing::Test {};

// Test with exponent e = 0
// floor(0 * log5(2) - log5(3)) = floor(-log5(3)) = floor(-0.6826...) = -1
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, ExponentZero_324) {
    constexpr auto result = floor_log5_pow2_minus_log5_3(0);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(0));
    EXPECT_EQ(result, -1);
}

// Test with exponent e = 1
// floor(1 * log5(2) - log5(3)) = floor(0.4307 - 0.6826) = floor(-0.2519) = -1
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, ExponentOne_324) {
    constexpr auto result = floor_log5_pow2_minus_log5_3(1);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(1));
}

// Test with exponent e = 2
// floor(2 * log5(2) - log5(3)) = floor(0.8614 - 0.6826) = floor(0.1787) = 0
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, ExponentTwo_324) {
    constexpr auto result = floor_log5_pow2_minus_log5_3(2);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(2));
    EXPECT_EQ(result, 0);
}

// Test with a negative exponent e = -1
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, ExponentNegativeOne_324) {
    constexpr auto result = floor_log5_pow2_minus_log5_3(-1);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(-1));
}

// Test with a larger positive exponent
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, ExponentPositiveLarge_324) {
    constexpr auto result = floor_log5_pow2_minus_log5_3(100);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(100));
}

// Test with a larger negative exponent
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, ExponentNegativeLarge_324) {
    constexpr auto result = floor_log5_pow2_minus_log5_3(-100);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(-100));
}

// Test with exponent e = 10
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, ExponentTen_324) {
    constexpr auto result = floor_log5_pow2_minus_log5_3(10);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(10));
}

// Test near the default min_exponent boundary
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, NearMinExponentBoundary_324) {
    constexpr auto result = floor_log5_pow2_minus_log5_3(-3543);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(-3543));
}

// Test near the default max_exponent boundary
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, NearMaxExponentBoundary_324) {
    constexpr auto result = floor_log5_pow2_minus_log5_3(2427);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(2427));
}

// Test constexpr-ness
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, IsConstexpr_324) {
    constexpr auto val = floor_log5_pow2_minus_log5_3(5);
    // Just verifying it compiles as constexpr
    EXPECT_EQ(val, expected_floor_log5_pow2_minus_log5_3(5));
}

// Test noexcept
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, IsNoexcept_324) {
    EXPECT_TRUE(noexcept(floor_log5_pow2_minus_log5_3(0)));
}

// Test with various exponents in a range to ensure consistency
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, RangeOfExponents_324) {
    for (int e = -1000; e <= 1000; e += 50) {
        auto result = floor_log5_pow2_minus_log5_3(e);
        int expected = expected_floor_log5_pow2_minus_log5_3(e);
        EXPECT_EQ(result, expected) << "Failed for exponent e = " << e;
    }
}

// Test with exponent e = -2 
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, ExponentNegativeTwo_324) {
    constexpr auto result = floor_log5_pow2_minus_log5_3(-2);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(-2));
}

// Test with exponent e = 3
// floor(3 * log5(2) - log5(3))
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, ExponentThree_324) {
    constexpr auto result = floor_log5_pow2_minus_log5_3(3);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(3));
}

// Monotonicity: result should be non-decreasing as e increases
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, Monotonicity_324) {
    for (int e = -500; e < 500; ++e) {
        auto r1 = floor_log5_pow2_minus_log5_3(e);
        auto r2 = floor_log5_pow2_minus_log5_3(e + 1);
        EXPECT_LE(r1, r2) << "Monotonicity violated at e = " << e;
    }
}

// Test with custom narrower range template parameters
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, CustomRange_324) {
    constexpr auto result = floor_log5_pow2_minus_log5_3<-100, 100>(50);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(50));
}

// Test with int32_t explicit type
TEST_F(FloorLog5Pow2MinusLog5_3Test_324, ExplicitInt32Input_324) {
    int32_t e = 42;
    auto result = floor_log5_pow2_minus_log5_3(e);
    EXPECT_EQ(result, expected_floor_log5_pow2_minus_log5_3(42));
}

}  // namespace
