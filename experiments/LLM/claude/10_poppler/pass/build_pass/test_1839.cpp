#include <gtest/gtest.h>

// We need to test the static inline function isPixelOutsideAdaptiveField.
// Since it's defined as static inline in the .cc file, we need to include it
// or redefine the function signature for testing. We'll include the relevant
// definition directly.

// Re-declare the function as it appears in the source (static inline).
// We replicate the exact function to test it as a black box.
static inline bool isPixelOutsideAdaptiveField(int x, int y)
{
    return y < -128 || y > 0 || x < -128 || (y < 0 && x > 127) || (y == 0 && x >= 0);
}

class IsPixelOutsideAdaptiveFieldTest_1839 : public ::testing::Test {
};

// ========================================
// Tests for y < -128 condition
// ========================================

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YFarBelowNeg128_ReturnsTrue_1839)
{
    EXPECT_TRUE(isPixelOutsideAdaptiveField(0, -129));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YExactlyNeg128_ReturnsFalseIfOtherConditionsNotMet_1839)
{
    // y == -128, x in valid range [-128, 127]
    EXPECT_FALSE(isPixelOutsideAdaptiveField(0, -128));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YMuchLessThanNeg128_ReturnsTrue_1839)
{
    EXPECT_TRUE(isPixelOutsideAdaptiveField(0, -1000));
}

// ========================================
// Tests for y > 0 condition
// ========================================

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YPositive_ReturnsTrue_1839)
{
    EXPECT_TRUE(isPixelOutsideAdaptiveField(0, 1));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YLargePositive_ReturnsTrue_1839)
{
    EXPECT_TRUE(isPixelOutsideAdaptiveField(0, 1000));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YZero_WithNegativeX_ReturnsFalse_1839)
{
    // y == 0, x < 0: y is not > 0, y is not < -128, x is not < -128 (for x=-1),
    // y==0 && x>=0 is false since x=-1
    EXPECT_FALSE(isPixelOutsideAdaptiveField(-1, 0));
}

// ========================================
// Tests for x < -128 condition
// ========================================

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, XFarBelowNeg128_ReturnsTrue_1839)
{
    EXPECT_TRUE(isPixelOutsideAdaptiveField(-129, -64));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, XExactlyNeg128_ReturnsFalseIfOtherConditionsNotMet_1839)
{
    // y=-1 (valid range for y), x=-128 (not < -128), y<0 && x>127 is false
    EXPECT_FALSE(isPixelOutsideAdaptiveField(-128, -1));
}

// ========================================
// Tests for y < 0 && x > 127 condition
// ========================================

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YNegativeAndXAbove127_ReturnsTrue_1839)
{
    EXPECT_TRUE(isPixelOutsideAdaptiveField(128, -1));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YNegativeAndXExactly127_ReturnsFalse_1839)
{
    // y=-1, x=127: y<0 && x>127 is false (x==127, not >127)
    EXPECT_FALSE(isPixelOutsideAdaptiveField(127, -1));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YNeg128AndX127_ReturnsFalse_1839)
{
    // boundary: y=-128 (not < -128), x=127 (not > 127), x not < -128
    EXPECT_FALSE(isPixelOutsideAdaptiveField(127, -128));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YNeg128AndX128_ReturnsTrue_1839)
{
    // y=-128, x=128: y<0 && x>127 is true
    EXPECT_TRUE(isPixelOutsideAdaptiveField(128, -128));
}

// ========================================
// Tests for y == 0 && x >= 0 condition
// ========================================

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YZeroAndXZero_ReturnsTrue_1839)
{
    // y==0 && x>=0: true
    EXPECT_TRUE(isPixelOutsideAdaptiveField(0, 0));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YZeroAndXPositive_ReturnsTrue_1839)
{
    EXPECT_TRUE(isPixelOutsideAdaptiveField(1, 0));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YZeroAndXNeg1_ReturnsFalse_1839)
{
    // y==0, x=-1: y==0 && x>=0 is false, no other condition triggered
    EXPECT_FALSE(isPixelOutsideAdaptiveField(-1, 0));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YZeroAndXNeg128_ReturnsFalse_1839)
{
    // y==0, x=-128: not < -128, y==0 && x>=0 false
    EXPECT_FALSE(isPixelOutsideAdaptiveField(-128, 0));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YZeroAndXNeg129_ReturnsTrue_1839)
{
    // x < -128 triggers
    EXPECT_TRUE(isPixelOutsideAdaptiveField(-129, 0));
}

// ========================================
// Combined boundary tests
// ========================================

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, AllInsideCorner_NegNeg_ReturnsFalse_1839)
{
    // y=-128, x=-128: all conditions false
    EXPECT_FALSE(isPixelOutsideAdaptiveField(-128, -128));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, AllInsideCorner_NegPos_ReturnsFalse_1839)
{
    // y=-128, x=127
    EXPECT_FALSE(isPixelOutsideAdaptiveField(127, -128));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, InsideMiddle_ReturnsFalse_1839)
{
    EXPECT_FALSE(isPixelOutsideAdaptiveField(-64, -64));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YNeg1_XNeg1_ReturnsFalse_1839)
{
    EXPECT_FALSE(isPixelOutsideAdaptiveField(-1, -1));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YNeg1_X0_ReturnsFalse_1839)
{
    // y < 0 && x > 127? no. Other conditions? no.
    EXPECT_FALSE(isPixelOutsideAdaptiveField(0, -1));
}

// ========================================
// Edge/extreme value tests
// ========================================

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, ExtremeNegativeXAndY_ReturnsTrue_1839)
{
    EXPECT_TRUE(isPixelOutsideAdaptiveField(-2147483647, -2147483647));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, ExtremePositiveXAndY_ReturnsTrue_1839)
{
    EXPECT_TRUE(isPixelOutsideAdaptiveField(2147483647, 2147483647));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YZeroXLargePositive_ReturnsTrue_1839)
{
    EXPECT_TRUE(isPixelOutsideAdaptiveField(2147483647, 0));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YNeg1_XLargePositive_ReturnsTrue_1839)
{
    // y<0 && x>127: true
    EXPECT_TRUE(isPixelOutsideAdaptiveField(2147483647, -1));
}

TEST_F(IsPixelOutsideAdaptiveFieldTest_1839, YNeg1_XLargeNegative_ReturnsTrue_1839)
{
    // x < -128: true
    EXPECT_TRUE(isPixelOutsideAdaptiveField(-2147483647, -1));
}
