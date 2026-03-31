#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::detail::log;

// Test normal operation with exponent 0
TEST(FloorLog2Pow10Test_321, ExponentZero_321) {
    // floor(log2(10^0)) = floor(log2(1)) = 0
    auto result = floor_log2_pow10(0);
    EXPECT_EQ(result, 0);
}

// Test with exponent 1
TEST(FloorLog2Pow10Test_321, ExponentOne_321) {
    // floor(log2(10^1)) = floor(log2(10)) = floor(3.3219...) = 3
    auto result = floor_log2_pow10(1);
    EXPECT_EQ(result, 3);
}

// Test with exponent 2
TEST(FloorLog2Pow10Test_321, ExponentTwo_321) {
    // floor(log2(10^2)) = floor(log2(100)) = floor(6.6438...) = 6
    auto result = floor_log2_pow10(2);
    EXPECT_EQ(result, 6);
}

// Test with exponent 3
TEST(FloorLog2Pow10Test_321, ExponentThree_321) {
    // floor(log2(10^3)) = floor(log2(1000)) = floor(9.9657...) = 9
    auto result = floor_log2_pow10(3);
    EXPECT_EQ(result, 9);
}

// Test with exponent 10
TEST(FloorLog2Pow10Test_321, ExponentTen_321) {
    // floor(log2(10^10)) = floor(33.2192...) = 33
    auto result = floor_log2_pow10(10);
    EXPECT_EQ(result, 33);
}

// Test with negative exponent -1
TEST(FloorLog2Pow10Test_321, ExponentNegativeOne_321) {
    // floor(log2(10^(-1))) = floor(log2(0.1)) = floor(-3.3219...) = -4
    auto result = floor_log2_pow10(-1);
    EXPECT_EQ(result, -4);
}

// Test with negative exponent -2
TEST(FloorLog2Pow10Test_321, ExponentNegativeTwo_321) {
    // floor(log2(10^(-2))) = floor(log2(0.01)) = floor(-6.6438...) = -7
    auto result = floor_log2_pow10(-2);
    EXPECT_EQ(result, -7);
}

// Test with negative exponent -10
TEST(FloorLog2Pow10Test_321, ExponentNegativeTen_321) {
    // floor(log2(10^(-10))) = floor(-33.2192...) = -34
    auto result = floor_log2_pow10(-10);
    EXPECT_EQ(result, -34);
}

// Test with exponent 100
TEST(FloorLog2Pow10Test_321, ExponentHundred_321) {
    // floor(log2(10^100)) = floor(332.192...) = 332
    auto result = floor_log2_pow10(100);
    EXPECT_EQ(result, 332);
}

// Test with exponent -100
TEST(FloorLog2Pow10Test_321, ExponentNegativeHundred_321) {
    // floor(log2(10^(-100))) = floor(-332.192...) = -333
    auto result = floor_log2_pow10(-100);
    EXPECT_EQ(result, -333);
}

// Test boundary: max default exponent 1233
TEST(FloorLog2Pow10Test_321, MaxDefaultExponent_321) {
    // floor(log2(10^1233)) = floor(1233 * 3.32192809...) = floor(4095.73...) = 4095
    auto result = floor_log2_pow10(1233);
    EXPECT_EQ(result, 4095);
}

// Test boundary: min default exponent -1233
TEST(FloorLog2Pow10Test_321, MinDefaultExponent_321) {
    // floor(log2(10^(-1233))) = floor(-1233 * 3.32192809...) = floor(-4095.73...) = -4096
    auto result = floor_log2_pow10(-1233);
    EXPECT_EQ(result, -4096);
}

// Test with small positive exponent 4
TEST(FloorLog2Pow10Test_321, ExponentFour_321) {
    // floor(log2(10^4)) = floor(log2(10000)) = floor(13.2877...) = 13
    auto result = floor_log2_pow10(4);
    EXPECT_EQ(result, 13);
}

// Test with exponent 5
TEST(FloorLog2Pow10Test_321, ExponentFive_321) {
    // floor(log2(10^5)) = floor(16.6096...) = 16
    auto result = floor_log2_pow10(5);
    EXPECT_EQ(result, 16);
}

// Test constexpr evaluation
TEST(FloorLog2Pow10Test_321, ConstexprEvaluation_321) {
    constexpr auto result = floor_log2_pow10(0);
    EXPECT_EQ(result, 0);
    
    constexpr auto result1 = floor_log2_pow10(1);
    EXPECT_EQ(result1, 3);
    
    constexpr auto result_neg1 = floor_log2_pow10(-1);
    EXPECT_EQ(result_neg1, -4);
}

// Test with custom template parameters for narrower range
TEST(FloorLog2Pow10Test_321, CustomRangeSmall_321) {
    auto result = floor_log2_pow10<-100, 100>(50);
    // floor(log2(10^50)) = floor(166.096...) = 166
    EXPECT_EQ(result, 166);
}

// Test exponent 300
TEST(FloorLog2Pow10Test_321, ExponentThreeHundred_321) {
    // floor(log2(10^300)) = floor(996.578...) = 996
    auto result = floor_log2_pow10(300);
    EXPECT_EQ(result, 996);
}

// Test exponent -300
TEST(FloorLog2Pow10Test_321, ExponentNegativeThreeHundred_321) {
    // floor(log2(10^(-300))) = floor(-996.578...) = -997
    auto result = floor_log2_pow10(-300);
    EXPECT_EQ(result, -997);
}

// Test noexcept
TEST(FloorLog2Pow10Test_321, IsNoexcept_321) {
    EXPECT_TRUE(noexcept(floor_log2_pow10(0)));
    EXPECT_TRUE(noexcept(floor_log2_pow10(1)));
    EXPECT_TRUE(noexcept(floor_log2_pow10(-1)));
}

// Test several known values for consistency
TEST(FloorLog2Pow10Test_321, ConsistencyCheck_321) {
    // Verify the relationship: floor_log2_pow10(e) == floor(e * log2(10))
    // For a range of values, check monotonicity
    for (int e = -100; e < 100; ++e) {
        auto current = floor_log2_pow10(e);
        auto next = floor_log2_pow10(e + 1);
        // log2(10) is ~3.32, so the difference should be 3 or 4
        auto diff = next - current;
        EXPECT_TRUE(diff == 3 || diff == 4) 
            << "Unexpected difference " << diff << " at exponent " << e;
    }
}

} // namespace
