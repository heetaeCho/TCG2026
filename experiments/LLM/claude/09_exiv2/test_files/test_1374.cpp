#include <gtest/gtest.h>
#include <cmath>

// Declare the function under test
namespace Exiv2 {
namespace Internal {
float fnumber(float apertureValue);
}
}

using Exiv2::Internal::fnumber;

class FnumberTest_1374 : public ::testing::Test {
protected:
};

// Test that aperture value 0 gives fnumber = 2^0 = 1.0
TEST_F(FnumberTest_1374, ApertureValueZero_ReturnsOne_1374) {
    float result = fnumber(0.0F);
    EXPECT_FLOAT_EQ(result, 1.0F);
}

// Test that aperture value 2 gives fnumber = 2^1 = 2.0
TEST_F(FnumberTest_1374, ApertureValueTwo_ReturnsTwo_1374) {
    float result = fnumber(2.0F);
    EXPECT_FLOAT_EQ(result, 2.0F);
}

// Test that aperture value 4 gives fnumber = 2^2 = 4.0
TEST_F(FnumberTest_1374, ApertureValueFour_ReturnsFour_1374) {
    float result = fnumber(4.0F);
    EXPECT_FLOAT_EQ(result, 4.0F);
}

// Test that aperture value 6 gives fnumber = 2^3 = 8.0
TEST_F(FnumberTest_1374, ApertureValueSix_ReturnsEight_1374) {
    float result = fnumber(6.0F);
    EXPECT_FLOAT_EQ(result, 8.0F);
}

// Test that aperture value 8 gives fnumber = 2^4 = 16.0
TEST_F(FnumberTest_1374, ApertureValueEight_ReturnsSixteen_1374) {
    float result = fnumber(8.0F);
    EXPECT_FLOAT_EQ(result, 16.0F);
}

// Test that aperture value 1 gives fnumber = 2^0.5 = sqrt(2) ≈ 1.4142
TEST_F(FnumberTest_1374, ApertureValueOne_ReturnsSqrtTwo_1374) {
    float result = fnumber(1.0F);
    float expected = std::sqrt(2.0F);
    EXPECT_NEAR(result, expected, 0.001F);
}

// Test that aperture value 10 gives fnumber = 2^5 = 32.0
TEST_F(FnumberTest_1374, ApertureValueTen_ReturnsThirtyTwo_1374) {
    float result = fnumber(10.0F);
    EXPECT_FLOAT_EQ(result, 32.0F);
}

// Test the special case: result near 3.5 gets clamped to exactly 3.5
// 2^(apertureValue/2) = 3.5 => apertureValue/2 = log2(3.5) => apertureValue = 2*log2(3.5)
TEST_F(FnumberTest_1374, ApertureValueForThreePointFive_ReturnsExactlyThreePointFive_1374) {
    float apertureValue = 2.0F * std::log2(3.5F);
    float result = fnumber(apertureValue);
    EXPECT_FLOAT_EQ(result, 3.5F);
}

// Test values slightly below 3.5 threshold (within 0.1 of 3.5) still get clamped to 3.5
// We want 2^(av/2) = 3.41 (which is within 0.1 of 3.5)
TEST_F(FnumberTest_1374, ApertureValueNearThreePointFive_BelowThreshold_ClampedToThreePointFive_1374) {
    float target = 3.41F;  // |3.41 - 3.5| = 0.09 < 0.1
    float apertureValue = 2.0F * std::log2(target);
    float result = fnumber(apertureValue);
    EXPECT_FLOAT_EQ(result, 3.5F);
}

// Test values slightly above 3.5 threshold (within 0.1 of 3.5) still get clamped to 3.5
// We want 2^(av/2) = 3.59 (which is within 0.1 of 3.5)
TEST_F(FnumberTest_1374, ApertureValueNearThreePointFive_AboveThreshold_ClampedToThreePointFive_1374) {
    float target = 3.59F;  // |3.59 - 3.5| = 0.09 < 0.1
    float apertureValue = 2.0F * std::log2(target);
    float result = fnumber(apertureValue);
    EXPECT_FLOAT_EQ(result, 3.5F);
}

// Test value just outside the 3.5 clamping range (below)
// 2^(av/2) = 3.39 => |3.39 - 3.5| = 0.11 >= 0.1, so no clamping
TEST_F(FnumberTest_1374, ApertureValueOutsideThreePointFive_Below_NoClamping_1374) {
    float target = 3.39F;  // |3.39 - 3.5| = 0.11 >= 0.1
    float apertureValue = 2.0F * std::log2(target);
    float result = fnumber(apertureValue);
    EXPECT_NE(result, 3.5F);
    EXPECT_NEAR(result, target, 0.01F);
}

// Test value just outside the 3.5 clamping range (above)
// 2^(av/2) = 3.61 => |3.61 - 3.5| = 0.11 >= 0.1, so no clamping
TEST_F(FnumberTest_1374, ApertureValueOutsideThreePointFive_Above_NoClamping_1374) {
    float target = 3.61F;  // |3.61 - 3.5| = 0.11 >= 0.1
    float apertureValue = 2.0F * std::log2(target);
    float result = fnumber(apertureValue);
    EXPECT_NE(result, 3.5F);
    EXPECT_NEAR(result, target, 0.01F);
}

// Test negative aperture value: aperture value -2 gives 2^(-1) = 0.5
TEST_F(FnumberTest_1374, NegativeApertureValue_ReturnsLessThanOne_1374) {
    float result = fnumber(-2.0F);
    EXPECT_FLOAT_EQ(result, 0.5F);
}

// Test large aperture value
TEST_F(FnumberTest_1374, LargeApertureValue_ReturnsLargeNumber_1374) {
    float result = fnumber(20.0F);
    EXPECT_FLOAT_EQ(result, 1024.0F);
}

// Test aperture value 3 gives fnumber = 2^1.5 ≈ 2.828
TEST_F(FnumberTest_1374, ApertureValueThree_ReturnsTwoSqrtTwo_1374) {
    float result = fnumber(3.0F);
    float expected = std::exp2(1.5F);
    EXPECT_NEAR(result, expected, 0.001F);
}

// Test aperture value 5 gives fnumber = 2^2.5 ≈ 5.657
TEST_F(FnumberTest_1374, ApertureValueFive_ReturnsExpected_1374) {
    float result = fnumber(5.0F);
    float expected = std::exp2(2.5F);
    EXPECT_NEAR(result, expected, 0.001F);
}

// Test that result is always positive for finite positive aperture values
TEST_F(FnumberTest_1374, PositiveApertureValue_ReturnsPositive_1374) {
    for (float av = 0.0F; av <= 14.0F; av += 0.5F) {
        float result = fnumber(av);
        EXPECT_GT(result, 0.0F) << "Failed for aperture value: " << av;
    }
}

// Test very small positive aperture value
TEST_F(FnumberTest_1374, VerySmallPositiveApertureValue_1374) {
    float result = fnumber(0.001F);
    float expected = std::exp2(0.001F / 2.0F);
    EXPECT_NEAR(result, expected, 0.0001F);
}

// Test large negative aperture value gives very small positive number
TEST_F(FnumberTest_1374, LargeNegativeApertureValue_ReturnsSmallPositive_1374) {
    float result = fnumber(-20.0F);
    float expected = std::exp2(-10.0F);
    EXPECT_FLOAT_EQ(result, expected);
    EXPECT_GT(result, 0.0F);
}
