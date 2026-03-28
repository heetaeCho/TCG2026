#include <gtest/gtest.h>
#include <algorithm>

// Reproduce the function under test (it's a static function, so we need to define it here
// to be able to test it. We're treating it as a black box based on its signature.)
static int getSat(int r, int g, int b) {
    int rgbMin = std::min({ r, g, b });
    int rgbMax = std::max({ r, g, b });
    return rgbMax - rgbMin;
}

// Normal operation tests

TEST(GetSatTest_1589, AllZeros_1589) {
    EXPECT_EQ(0, getSat(0, 0, 0));
}

TEST(GetSatTest_1589, AllSamePositive_1589) {
    EXPECT_EQ(0, getSat(128, 128, 128));
}

TEST(GetSatTest_1589, AllSameValue255_1589) {
    EXPECT_EQ(0, getSat(255, 255, 255));
}

TEST(GetSatTest_1589, MaxRedMinGreenBlue_1589) {
    EXPECT_EQ(255, getSat(255, 0, 0));
}

TEST(GetSatTest_1589, MaxGreenMinRedBlue_1589) {
    EXPECT_EQ(255, getSat(0, 255, 0));
}

TEST(GetSatTest_1589, MaxBlueMinRedGreen_1589) {
    EXPECT_EQ(255, getSat(0, 0, 255));
}

TEST(GetSatTest_1589, TypicalRGBValues_1589) {
    // r=100, g=200, b=150 => max=200, min=100 => sat=100
    EXPECT_EQ(100, getSat(100, 200, 150));
}

TEST(GetSatTest_1589, RedIsMax_1589) {
    // r=200, g=50, b=100 => max=200, min=50 => sat=150
    EXPECT_EQ(150, getSat(200, 50, 100));
}

TEST(GetSatTest_1589, GreenIsMax_1589) {
    // r=10, g=250, b=30 => max=250, min=10 => sat=240
    EXPECT_EQ(240, getSat(10, 250, 30));
}

TEST(GetSatTest_1589, BlueIsMax_1589) {
    // r=20, g=30, b=240 => max=240, min=20 => sat=220
    EXPECT_EQ(220, getSat(20, 30, 240));
}

TEST(GetSatTest_1589, TwoComponentsSame_MaxRG_1589) {
    // r=200, g=200, b=50 => max=200, min=50 => sat=150
    EXPECT_EQ(150, getSat(200, 200, 50));
}

TEST(GetSatTest_1589, TwoComponentsSame_MinRG_1589) {
    // r=50, g=50, b=200 => max=200, min=50 => sat=150
    EXPECT_EQ(150, getSat(50, 50, 200));
}

TEST(GetSatTest_1589, TwoComponentsSame_MaxRB_1589) {
    // r=200, g=50, b=200 => max=200, min=50 => sat=150
    EXPECT_EQ(150, getSat(200, 50, 200));
}

TEST(GetSatTest_1589, TwoComponentsSame_MinRB_1589) {
    // r=50, g=200, b=50 => max=200, min=50 => sat=150
    EXPECT_EQ(150, getSat(50, 200, 50));
}

// Boundary conditions

TEST(GetSatTest_1589, MinDifference_1589) {
    // Adjacent values
    EXPECT_EQ(1, getSat(127, 128, 128));
}

TEST(GetSatTest_1589, FullRange_1589) {
    EXPECT_EQ(255, getSat(0, 255, 128));
}

TEST(GetSatTest_1589, SingleUnitDifference_1589) {
    EXPECT_EQ(1, getSat(0, 0, 1));
}

TEST(GetSatTest_1589, SingleUnitDifferenceReverse_1589) {
    EXPECT_EQ(1, getSat(1, 0, 0));
}

// Negative value tests (edge case - int allows negatives)

TEST(GetSatTest_1589, NegativeValues_1589) {
    // r=-10, g=-20, b=-5 => max=-5, min=-20 => sat=15
    EXPECT_EQ(15, getSat(-10, -20, -5));
}

TEST(GetSatTest_1589, MixedNegativePositive_1589) {
    // r=-100, g=100, b=0 => max=100, min=-100 => sat=200
    EXPECT_EQ(200, getSat(-100, 100, 0));
}

TEST(GetSatTest_1589, AllNegativeSame_1589) {
    EXPECT_EQ(0, getSat(-50, -50, -50));
}

// Large values

TEST(GetSatTest_1589, LargeValues_1589) {
    EXPECT_EQ(0, getSat(1000000, 1000000, 1000000));
}

TEST(GetSatTest_1589, LargeRange_1589) {
    // max=1000000, min=0 => sat=1000000
    EXPECT_EQ(1000000, getSat(0, 1000000, 500000));
}

// Ordering permutation tests - ensure all orderings give same result

TEST(GetSatTest_1589, Permutation_RGB_1589) {
    EXPECT_EQ(80, getSat(10, 50, 90));
}

TEST(GetSatTest_1589, Permutation_RBG_1589) {
    EXPECT_EQ(80, getSat(10, 90, 50));
}

TEST(GetSatTest_1589, Permutation_GRB_1589) {
    EXPECT_EQ(80, getSat(50, 10, 90));
}

TEST(GetSatTest_1589, Permutation_GBR_1589) {
    EXPECT_EQ(80, getSat(90, 10, 50));
}

TEST(GetSatTest_1589, Permutation_BRG_1589) {
    EXPECT_EQ(80, getSat(50, 90, 10));
}

TEST(GetSatTest_1589, Permutation_BGR_1589) {
    EXPECT_EQ(80, getSat(90, 50, 10));
}
