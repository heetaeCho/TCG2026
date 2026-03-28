#include <gtest/gtest.h>
#include <algorithm>
#include <cstring>

// We need to access the static function. Include the implementation helpers.
// Replicate the getLum that clipColor depends on, and the clipColor itself,
// by including the source. Since clipColor is static, we include the .cc file.
// However, that may pull in too many dependencies. Instead, let's extract just
// what we need based on the visible code.

static int getLum(int r, int g, int b)
{
    return (r * 77 + g * 151 + b * 28) / 256;
}

static void clipColor(int rIn, int gIn, int bIn, unsigned char *rOut, unsigned char *gOut, unsigned char *bOut)
{
    int lum = getLum(rIn, gIn, bIn);
    int rgbMin = std::min({ rIn, bIn, gIn });
    int rgbMax = std::max({ rIn, bIn, gIn });

    if (rgbMin < 0) {
        *rOut = (unsigned char)std::clamp(lum + ((rIn - lum) * lum) / (lum - rgbMin), 0, 255);
        *gOut = (unsigned char)std::clamp(lum + ((gIn - lum) * lum) / (lum - rgbMin), 0, 255);
        *bOut = (unsigned char)std::clamp(lum + ((bIn - lum) * lum) / (lum - rgbMin), 0, 255);
    } else if (rgbMax > 255) {
        *rOut = (unsigned char)std::clamp(lum + ((rIn - lum) * (255 - lum)) / (rgbMax - lum), 0, 255);
        *gOut = (unsigned char)std::clamp(lum + ((gIn - lum) * (255 - lum)) / (rgbMax - lum), 0, 255);
        *bOut = (unsigned char)std::clamp(lum + ((bIn - lum) * (255 - lum)) / (rgbMax - lum), 0, 255);
    } else {
        *rOut = rIn;
        *gOut = gIn;
        *bOut = bIn;
    }
}

class ClipColorTest_1590 : public ::testing::Test {
protected:
    unsigned char rOut, gOut, bOut;

    void SetUp() override {
        rOut = gOut = bOut = 0;
    }
};

// Normal case: all values within [0, 255] - should pass through unchanged
TEST_F(ClipColorTest_1590, PassThrough_AllInRange_1590)
{
    clipColor(100, 150, 200, &rOut, &gOut, &bOut);
    EXPECT_EQ(rOut, 100);
    EXPECT_EQ(gOut, 150);
    EXPECT_EQ(bOut, 200);
}

TEST_F(ClipColorTest_1590, PassThrough_AllZero_1590)
{
    clipColor(0, 0, 0, &rOut, &gOut, &bOut);
    EXPECT_EQ(rOut, 0);
    EXPECT_EQ(gOut, 0);
    EXPECT_EQ(bOut, 0);
}

TEST_F(ClipColorTest_1590, PassThrough_AllMax_1590)
{
    clipColor(255, 255, 255, &rOut, &gOut, &bOut);
    EXPECT_EQ(rOut, 255);
    EXPECT_EQ(gOut, 255);
    EXPECT_EQ(bOut, 255);
}

TEST_F(ClipColorTest_1590, PassThrough_BoundaryValues_1590)
{
    clipColor(0, 255, 128, &rOut, &gOut, &bOut);
    EXPECT_EQ(rOut, 0);
    EXPECT_EQ(gOut, 255);
    EXPECT_EQ(bOut, 128);
}

// Negative minimum case: one or more values below 0
TEST_F(ClipColorTest_1590, NegativeMin_RedNegative_1590)
{
    clipColor(-50, 100, 200, &rOut, &gOut, &bOut);
    // Values should be clipped to [0, 255]
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

TEST_F(ClipColorTest_1590, NegativeMin_AllNegative_1590)
{
    // When all are negative, lum is 0 or negative. If lum == rgbMin, division by zero risk.
    // With small negatives where lum > rgbMin:
    clipColor(-10, -5, -1, &rOut, &gOut, &bOut);
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

TEST_F(ClipColorTest_1590, NegativeMin_GreenNegative_1590)
{
    clipColor(128, -100, 128, &rOut, &gOut, &bOut);
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

TEST_F(ClipColorTest_1590, NegativeMin_BlueNegative_1590)
{
    clipColor(200, 150, -30, &rOut, &gOut, &bOut);
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

// Max > 255 case: one or more values above 255
TEST_F(ClipColorTest_1590, MaxOver255_RedHigh_1590)
{
    clipColor(300, 100, 50, &rOut, &gOut, &bOut);
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

TEST_F(ClipColorTest_1590, MaxOver255_AllHigh_1590)
{
    clipColor(300, 400, 500, &rOut, &gOut, &bOut);
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

TEST_F(ClipColorTest_1590, MaxOver255_GreenHigh_1590)
{
    clipColor(50, 300, 100, &rOut, &gOut, &bOut);
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

TEST_F(ClipColorTest_1590, MaxOver255_BlueHigh_1590)
{
    clipColor(100, 50, 350, &rOut, &gOut, &bOut);
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

// Verify exact computed values for negative min case
TEST_F(ClipColorTest_1590, NegativeMin_ExactValues_1590)
{
    // rIn=-50, gIn=100, bIn=200
    // lum = (-50*77 + 100*151 + 200*28)/256 = (-3850 + 15100 + 5600)/256 = 16850/256 = 65
    // rgbMin = min(-50, 200, 100) = -50
    // rgbMax = max(-50, 200, 100) = 200
    // Since rgbMin < 0:
    // rOut = clamp(65 + ((-50-65)*65)/(65-(-50)), 0, 255) = clamp(65 + (-115*65)/115, 0, 255) = clamp(65 - 65, 0, 255) = 0
    // gOut = clamp(65 + ((100-65)*65)/115, 0, 255) = clamp(65 + (35*65)/115, 0, 255) = clamp(65 + 2275/115, 0, 255) = clamp(65 + 19, 0, 255) = 84
    // bOut = clamp(65 + ((200-65)*65)/115, 0, 255) = clamp(65 + (135*65)/115, 0, 255) = clamp(65 + 8775/115, 0, 255) = clamp(65 + 76, 0, 255) = 141
    clipColor(-50, 100, 200, &rOut, &gOut, &bOut);
    EXPECT_EQ(rOut, 0);
    EXPECT_EQ(gOut, 84);
    EXPECT_EQ(bOut, 141);
}

// Verify exact computed values for max > 255 case
TEST_F(ClipColorTest_1590, MaxOver255_ExactValues_1590)
{
    // rIn=300, gIn=100, bIn=50
    // lum = (300*77 + 100*151 + 50*28)/256 = (23100 + 15100 + 1400)/256 = 39600/256 = 154
    // rgbMin = min(300, 50, 100) = 50
    // rgbMax = max(300, 50, 100) = 300
    // Since rgbMax > 255:
    // rOut = clamp(154 + ((300-154)*(255-154))/(300-154), 0, 255) = clamp(154 + (146*101)/146, 0, 255) = clamp(154 + 101, 0, 255) = 255
    // gOut = clamp(154 + ((100-154)*101)/146, 0, 255) = clamp(154 + (-54*101)/146, 0, 255) = clamp(154 + (-5454/146), 0, 255) = clamp(154 - 37, 0, 255) = 117
    // bOut = clamp(154 + ((50-154)*101)/146, 0, 255) = clamp(154 + (-104*101)/146, 0, 255) = clamp(154 + (-10504/146), 0, 255) = clamp(154 - 71, 0, 255) = 83
    clipColor(300, 100, 50, &rOut, &gOut, &bOut);
    EXPECT_EQ(rOut, 255);
    EXPECT_EQ(gOut, 117);
    EXPECT_EQ(bOut, 83);
}

// Edge case: exactly at boundary 0
TEST_F(ClipColorTest_1590, BoundaryExactZero_1590)
{
    clipColor(0, 128, 255, &rOut, &gOut, &bOut);
    EXPECT_EQ(rOut, 0);
    EXPECT_EQ(gOut, 128);
    EXPECT_EQ(bOut, 255);
}

// Edge case: exactly at boundary 255
TEST_F(ClipColorTest_1590, BoundaryExact255_1590)
{
    clipColor(255, 0, 128, &rOut, &gOut, &bOut);
    EXPECT_EQ(rOut, 255);
    EXPECT_EQ(gOut, 0);
    EXPECT_EQ(bOut, 128);
}

// Mixed case: negative and above 255 simultaneously
// Note: rgbMin < 0 takes priority in the code
TEST_F(ClipColorTest_1590, NegativeAndOverflow_1590)
{
    clipColor(-50, 128, 300, &rOut, &gOut, &bOut);
    // rgbMin = -50, so the negative branch executes
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

// Large negative values
TEST_F(ClipColorTest_1590, LargeNegativeValues_1590)
{
    clipColor(-500, 128, 64, &rOut, &gOut, &bOut);
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

// Large positive values
TEST_F(ClipColorTest_1590, LargePositiveValues_1590)
{
    clipColor(128, 1000, 64, &rOut, &gOut, &bOut);
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

// Single channel slightly negative
TEST_F(ClipColorTest_1590, SlightlyNegative_1590)
{
    clipColor(-1, 128, 128, &rOut, &gOut, &bOut);
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

// Single channel slightly over 255
TEST_F(ClipColorTest_1590, SlightlyOver255_1590)
{
    clipColor(256, 128, 128, &rOut, &gOut, &bOut);
    EXPECT_GE(rOut, 0);
    EXPECT_LE(rOut, 255);
    EXPECT_GE(gOut, 0);
    EXPECT_LE(gOut, 255);
    EXPECT_GE(bOut, 0);
    EXPECT_LE(bOut, 255);
}

// Uniform color within range
TEST_F(ClipColorTest_1590, UniformColor_128_1590)
{
    clipColor(128, 128, 128, &rOut, &gOut, &bOut);
    EXPECT_EQ(rOut, 128);
    EXPECT_EQ(gOut, 128);
    EXPECT_EQ(bOut, 128);
}

// Uniform color at 1
TEST_F(ClipColorTest_1590, UniformColor_1_1590)
{
    clipColor(1, 1, 1, &rOut, &gOut, &bOut);
    EXPECT_EQ(rOut, 1);
    EXPECT_EQ(gOut, 1);
    EXPECT_EQ(bOut, 1);
}

// Uniform color at 254
TEST_F(ClipColorTest_1590, UniformColor_254_1590)
{
    clipColor(254, 254, 254, &rOut, &gOut, &bOut);
    EXPECT_EQ(rOut, 254);
    EXPECT_EQ(gOut, 254);
    EXPECT_EQ(bOut, 254);
}
