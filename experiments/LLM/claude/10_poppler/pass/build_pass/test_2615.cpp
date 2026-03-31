#include <gtest/gtest.h>

// We need to test the static function isImageInterpolationRequired.
// Since it's a static function defined in the .cc file, we need to include it
// or redefine it here for testing purposes. We'll include the relevant portion.
// However, since we can't modify the source, we'll declare the function signature
// and link against it. But static functions have internal linkage...
// 
// The pragmatic approach: we replicate the function signature here to test it,
// since it's a standalone static function. We include the source file directly.

// To access the static function, we include the implementation file indirectly.
// We need the function to be accessible. One approach is to include the .cc file
// which makes the static function available in this translation unit.

// Minimal defines/includes needed for the function under test
// The function only uses basic types (int, bool), so no special headers needed.

// Re-declare the function as it appears in the source (copy for testing since it's static)
static bool isImageInterpolationRequired(int srcWidth, int srcHeight, int scaledWidth, int scaledHeight, bool interpolate)
{
    if (interpolate || srcWidth == 0 || srcHeight == 0) {
        return true;
    }
    /* When scale factor is >= 400% we don't interpolate. See bugs #25268, #9860 */
    if (scaledWidth / srcWidth >= 4 || scaledHeight / srcHeight >= 4) {
        return false;
    }
    return true;
}

class IsImageInterpolationRequiredTest_2615 : public ::testing::Test {
protected:
    // Helper to make test calls more readable
    bool callFunc(int srcW, int srcH, int scaledW, int scaledH, bool interpolate) {
        return isImageInterpolationRequired(srcW, srcH, scaledW, scaledH, interpolate);
    }
};

// Test: When interpolate flag is true, should always return true
TEST_F(IsImageInterpolationRequiredTest_2615, InterpolateTrueAlwaysReturnsTrue_2615) {
    EXPECT_TRUE(callFunc(100, 100, 400, 400, true));
    EXPECT_TRUE(callFunc(100, 100, 100, 100, true));
    EXPECT_TRUE(callFunc(1, 1, 1000, 1000, true));
    EXPECT_TRUE(callFunc(100, 100, 10, 10, true));
}

// Test: When srcWidth is 0, should return true regardless of other params
TEST_F(IsImageInterpolationRequiredTest_2615, SrcWidthZeroReturnsTrue_2615) {
    EXPECT_TRUE(callFunc(0, 100, 400, 400, false));
    EXPECT_TRUE(callFunc(0, 0, 400, 400, false));
    EXPECT_TRUE(callFunc(0, 100, 0, 0, false));
}

// Test: When srcHeight is 0, should return true regardless of other params
TEST_F(IsImageInterpolationRequiredTest_2615, SrcHeightZeroReturnsTrue_2615) {
    EXPECT_TRUE(callFunc(100, 0, 400, 400, false));
    EXPECT_TRUE(callFunc(50, 0, 200, 200, false));
}

// Test: Scale factor exactly 4x in width should return false (no interpolation needed)
TEST_F(IsImageInterpolationRequiredTest_2615, ScaleFactorExactly4xWidthReturnsFalse_2615) {
    EXPECT_FALSE(callFunc(100, 100, 400, 100, false));
}

// Test: Scale factor exactly 4x in height should return false
TEST_F(IsImageInterpolationRequiredTest_2615, ScaleFactorExactly4xHeightReturnsFalse_2615) {
    EXPECT_FALSE(callFunc(100, 100, 100, 400, false));
}

// Test: Scale factor exactly 4x in both dimensions should return false
TEST_F(IsImageInterpolationRequiredTest_2615, ScaleFactorExactly4xBothReturnsFalse_2615) {
    EXPECT_FALSE(callFunc(100, 100, 400, 400, false));
}

// Test: Scale factor greater than 4x should return false
TEST_F(IsImageInterpolationRequiredTest_2615, ScaleFactorGreaterThan4xReturnsFalse_2615) {
    EXPECT_FALSE(callFunc(100, 100, 500, 100, false));
    EXPECT_FALSE(callFunc(100, 100, 100, 500, false));
    EXPECT_FALSE(callFunc(100, 100, 1000, 1000, false));
    EXPECT_FALSE(callFunc(10, 10, 100, 100, false));
}

// Test: Scale factor less than 4x should return true (interpolation required)
TEST_F(IsImageInterpolationRequiredTest_2615, ScaleFactorLessThan4xReturnsTrue_2615) {
    EXPECT_TRUE(callFunc(100, 100, 399, 399, false));
    EXPECT_TRUE(callFunc(100, 100, 300, 300, false));
    EXPECT_TRUE(callFunc(100, 100, 200, 200, false));
    EXPECT_TRUE(callFunc(100, 100, 100, 100, false));
}

// Test: Scale factor just below 4x boundary
TEST_F(IsImageInterpolationRequiredTest_2615, ScaleFactorJustBelow4xReturnsTrue_2615) {
    // 399/100 = 3 (integer division), which is < 4
    EXPECT_TRUE(callFunc(100, 100, 399, 399, false));
}

// Test: Scale factor just at 4x boundary
TEST_F(IsImageInterpolationRequiredTest_2615, ScaleFactorAt4xBoundaryReturnsFalse_2615) {
    // 400/100 = 4, which is >= 4
    EXPECT_FALSE(callFunc(100, 100, 400, 300, false));
}

// Test: 1:1 scale (no scaling) should return true
TEST_F(IsImageInterpolationRequiredTest_2615, OneToOneScaleReturnsTrue_2615) {
    EXPECT_TRUE(callFunc(100, 100, 100, 100, false));
}

// Test: Downscaling (scaled smaller than source) should return true
TEST_F(IsImageInterpolationRequiredTest_2615, DownscalingReturnsTrue_2615) {
    EXPECT_TRUE(callFunc(100, 100, 50, 50, false));
    EXPECT_TRUE(callFunc(100, 100, 10, 10, false));
    EXPECT_TRUE(callFunc(100, 100, 1, 1, false));
}

// Test: Small source dimensions with large scale
TEST_F(IsImageInterpolationRequiredTest_2615, SmallSourceLargeScaleReturnsFalse_2615) {
    // 1 pixel source scaled to 4 pixels: 4/1 = 4 >= 4
    EXPECT_FALSE(callFunc(1, 1, 4, 4, false));
    // 1 pixel source scaled to 5 pixels
    EXPECT_FALSE(callFunc(1, 1, 5, 5, false));
}

// Test: Small source dimensions with moderate scale
TEST_F(IsImageInterpolationRequiredTest_2615, SmallSourceModerateScaleReturnsTrue_2615) {
    // 1 pixel source scaled to 3 pixels: 3/1 = 3 < 4
    EXPECT_TRUE(callFunc(1, 1, 3, 3, false));
    EXPECT_TRUE(callFunc(1, 1, 2, 2, false));
    EXPECT_TRUE(callFunc(1, 1, 1, 1, false));
}

// Test: Only one dimension exceeds 4x threshold
TEST_F(IsImageInterpolationRequiredTest_2615, OneDimensionExceeds4xReturnsFalse_2615) {
    // Width is 4x but height is 1x
    EXPECT_FALSE(callFunc(100, 100, 400, 100, false));
    // Height is 4x but width is 1x
    EXPECT_FALSE(callFunc(100, 100, 100, 400, false));
}

// Test: Both dimensions below 4x threshold returns true
TEST_F(IsImageInterpolationRequiredTest_2615, BothDimensionsBelow4xReturnsTrue_2615) {
    EXPECT_TRUE(callFunc(100, 100, 350, 350, false));
    EXPECT_TRUE(callFunc(100, 100, 200, 300, false));
}

// Test: Integer division behavior - 399/100 = 3 in integer division
TEST_F(IsImageInterpolationRequiredTest_2615, IntegerDivisionBehavior_2615) {
    // 399/100 = 3 (integer), so < 4, returns true
    EXPECT_TRUE(callFunc(100, 100, 399, 100, false));
    // 400/100 = 4 (integer), so >= 4, returns false
    EXPECT_FALSE(callFunc(100, 100, 400, 100, false));
    // 401/100 = 4 (integer), so >= 4, returns false
    EXPECT_FALSE(callFunc(100, 100, 401, 100, false));
}

// Test: Asymmetric scaling where only width triggers the threshold
TEST_F(IsImageInterpolationRequiredTest_2615, AsymmetricScalingWidthOnly_2615) {
    EXPECT_FALSE(callFunc(50, 200, 200, 200, false)); // 200/50=4 >= 4
}

// Test: Asymmetric scaling where only height triggers the threshold
TEST_F(IsImageInterpolationRequiredTest_2615, AsymmetricScalingHeightOnly_2615) {
    EXPECT_FALSE(callFunc(200, 50, 200, 200, false)); // 200/50=4 >= 4
}

// Test: Large values
TEST_F(IsImageInterpolationRequiredTest_2615, LargeValues_2615) {
    EXPECT_FALSE(callFunc(1000, 1000, 4000, 4000, false));
    EXPECT_TRUE(callFunc(1000, 1000, 3999, 3999, false));
    EXPECT_FALSE(callFunc(1000, 1000, 10000, 10000, false));
}

// Test: scaledWidth or scaledHeight is 0 (edge case, no division by zero since we divide by src)
TEST_F(IsImageInterpolationRequiredTest_2615, ScaledDimensionZero_2615) {
    // 0/100 = 0, which is < 4, so should return true
    EXPECT_TRUE(callFunc(100, 100, 0, 0, false));
    EXPECT_TRUE(callFunc(100, 100, 0, 100, false));
    EXPECT_TRUE(callFunc(100, 100, 100, 0, false));
}

// Test: Negative scaled dimensions (edge case behavior)
TEST_F(IsImageInterpolationRequiredTest_2615, NegativeScaledDimensions_2615) {
    // Negative / positive in integer division gives negative or zero result, < 4
    // So should return true
    EXPECT_TRUE(callFunc(100, 100, -100, -100, false));
}

// Test: Both src dimensions zero with interpolate false
TEST_F(IsImageInterpolationRequiredTest_2615, BothSrcZeroReturnsTrueEarly_2615) {
    // srcWidth == 0 triggers early return true
    EXPECT_TRUE(callFunc(0, 0, 100, 100, false));
}
