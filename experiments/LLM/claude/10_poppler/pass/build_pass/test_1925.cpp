#include <gtest/gtest.h>
#include <cstdint>

// Re-declare the static function for testing purposes.
// Since we're testing the function as a black box based on its interface,
// we include its signature here. The actual implementation is in CairoOutputDev.cc.
// We need to replicate the function signature to test it.
static int luminocity(uint32_t x)
{
    int r = (x >> 16) & 0xff;
    int g = (x >> 8) & 0xff;
    int b = (x >> 0) & 0xff;
    int y = (r * 19661 + g * 38666 + b * 7209 + 32829) >> 16;
    return y;
}

class LuminocityTest_1925 : public ::testing::Test {
protected:
};

// Test black (0x00000000) - all channels zero
TEST_F(LuminocityTest_1925, BlackReturnsZero_1925)
{
    // Black: R=0, G=0, B=0
    // y = (0 + 0 + 0 + 32829) >> 16 = 32829 >> 16 = 0
    uint32_t black = 0x00000000;
    int result = luminocity(black);
    EXPECT_EQ(result, 0);
}

// Test white (0x00FFFFFF) - all channels max
TEST_F(LuminocityTest_1925, WhiteReturnsMax_1925)
{
    // White: R=255, G=255, B=255
    // y = (255*19661 + 255*38666 + 255*7209 + 32829) >> 16
    // = (5013555 + 9859830 + 1838295 + 32829) >> 16
    // = 16744509 >> 16
    // = 255
    uint32_t white = 0x00FFFFFF;
    int result = luminocity(white);
    EXPECT_EQ(result, 255);
}

// Test pure red (0x00FF0000)
TEST_F(LuminocityTest_1925, PureRedLuminocity_1925)
{
    // R=255, G=0, B=0
    // y = (255*19661 + 0 + 0 + 32829) >> 16
    // = (5013555 + 32829) >> 16
    // = 5046384 >> 16
    // = 77
    uint32_t red = 0x00FF0000;
    int result = luminocity(red);
    EXPECT_EQ(result, 77);
}

// Test pure green (0x0000FF00)
TEST_F(LuminocityTest_1925, PureGreenLuminocity_1925)
{
    // R=0, G=255, B=0
    // y = (0 + 255*38666 + 0 + 32829) >> 16
    // = (9859830 + 32829) >> 16
    // = 9892659 >> 16
    // = 150
    uint32_t green = 0x0000FF00;
    int result = luminocity(green);
    EXPECT_EQ(result, 150);
}

// Test pure blue (0x000000FF)
TEST_F(LuminocityTest_1925, PureBlueLuminocity_1925)
{
    // R=0, G=0, B=255
    // y = (0 + 0 + 255*7209 + 32829) >> 16
    // = (1838295 + 32829) >> 16
    // = 1871124 >> 16
    // = 28
    uint32_t blue = 0x000000FF;
    int result = luminocity(blue);
    EXPECT_EQ(result, 28);
}

// Test that luminocity components sum approximately to 255 for white
TEST_F(LuminocityTest_1925, ComponentsSumToWhite_1925)
{
    int r_lum = luminocity(0x00FF0000);
    int g_lum = luminocity(0x0000FF00);
    int b_lum = luminocity(0x000000FF);
    int white_lum = luminocity(0x00FFFFFF);

    // Due to rounding, the sum of individual channels should be close to white
    // but may not be exact
    EXPECT_NEAR(r_lum + g_lum + b_lum, white_lum, 1);
}

// Test that the upper 8 bits (alpha or unused) are ignored
TEST_F(LuminocityTest_1925, UpperBitsIgnored_1925)
{
    // The function only looks at the lower 24 bits
    uint32_t with_alpha = 0xFF000000;
    int result = luminocity(with_alpha);
    EXPECT_EQ(result, 0);

    // Same color with different alpha should give same result
    uint32_t color1 = 0x00808080;
    uint32_t color2 = 0xFF808080;
    EXPECT_EQ(luminocity(color1), luminocity(color2));
}

// Test mid-gray (0x00808080)
TEST_F(LuminocityTest_1925, MidGrayLuminocity_1925)
{
    // R=128, G=128, B=128
    // y = (128*19661 + 128*38666 + 128*7209 + 32829) >> 16
    // = (2516608 + 4949248 + 922752 + 32829) >> 16
    // = 8421437 >> 16
    // = 128
    uint32_t midgray = 0x00808080;
    int result = luminocity(midgray);
    EXPECT_EQ(result, 128);
}

// Test with R=1, G=0, B=0 (minimal non-zero red)
TEST_F(LuminocityTest_1925, MinimalRedLuminocity_1925)
{
    // R=1, G=0, B=0
    // y = (1*19661 + 0 + 0 + 32829) >> 16
    // = 52490 >> 16
    // = 0
    uint32_t minred = 0x00010000;
    int result = luminocity(minred);
    EXPECT_EQ(result, 0);
}

// Test with R=0, G=1, B=0 (minimal non-zero green)
TEST_F(LuminocityTest_1925, MinimalGreenLuminocity_1925)
{
    // R=0, G=1, B=0
    // y = (0 + 1*38666 + 0 + 32829) >> 16
    // = 71495 >> 16
    // = 1
    uint32_t mingreen = 0x00000100;
    int result = luminocity(mingreen);
    EXPECT_EQ(result, 1);
}

// Test with R=0, G=0, B=1 (minimal non-zero blue)
TEST_F(LuminocityTest_1925, MinimalBlueLuminocity_1925)
{
    // R=0, G=0, B=1
    // y = (0 + 0 + 1*7209 + 32829) >> 16
    // = 40038 >> 16
    // = 0
    uint32_t minblue = 0x00000001;
    int result = luminocity(minblue);
    EXPECT_EQ(result, 0);
}

// Test a known color: typical skin tone or common color
TEST_F(LuminocityTest_1925, KnownColorYellow_1925)
{
    // Yellow: R=255, G=255, B=0
    // y = (255*19661 + 255*38666 + 0 + 32829) >> 16
    // = (5013555 + 9859830 + 32829) >> 16
    // = 14906214 >> 16
    // = 227
    uint32_t yellow = 0x00FFFF00;
    int result = luminocity(yellow);
    EXPECT_EQ(result, 227);
}

// Test a known color: cyan
TEST_F(LuminocityTest_1925, KnownColorCyan_1925)
{
    // Cyan: R=0, G=255, B=255
    // y = (0 + 255*38666 + 255*7209 + 32829) >> 16
    // = (9859830 + 1838295 + 32829) >> 16
    // = 11730954 >> 16
    // = 178 (= 150 + 28)
    uint32_t cyan = 0x0000FFFF;
    int result = luminocity(cyan);
    EXPECT_EQ(result, 178);
}

// Test a known color: magenta
TEST_F(LuminocityTest_1925, KnownColorMagenta_1925)
{
    // Magenta: R=255, G=0, B=255
    // y = (255*19661 + 0 + 255*7209 + 32829) >> 16
    // = (5013555 + 1838295 + 32829) >> 16
    // = 6884679 >> 16
    // = 105
    uint32_t magenta = 0x00FF00FF;
    int result = luminocity(magenta);
    EXPECT_EQ(result, 105);
}

// Test return value is always non-negative
TEST_F(LuminocityTest_1925, AlwaysNonNegative_1925)
{
    // Even with all zeros, the rounding constant ensures non-negative
    EXPECT_GE(luminocity(0x00000000), 0);
    EXPECT_GE(luminocity(0xFFFFFFFF), 0);
    EXPECT_GE(luminocity(0x00010101), 0);
}

// Test return value does not exceed 255
TEST_F(LuminocityTest_1925, NeverExceeds255_1925)
{
    EXPECT_LE(luminocity(0x00FFFFFF), 255);
    EXPECT_LE(luminocity(0xFFFFFFFF), 255);
}

// Test monotonicity: increasing all channels should not decrease luminocity
TEST_F(LuminocityTest_1925, MonotonicWithUniformIncrease_1925)
{
    int prev = luminocity(0x00000000);
    for (int i = 1; i <= 255; i++)
    {
        uint32_t color = (i << 16) | (i << 8) | i;
        int current = luminocity(color);
        EXPECT_GE(current, prev);
        prev = current;
    }
}

// Test that green has more weight than red, and red more than blue
TEST_F(LuminocityTest_1925, GreenWeightGreaterThanRedGreaterThanBlue_1925)
{
    int r_lum = luminocity(0x00FF0000);
    int g_lum = luminocity(0x0000FF00);
    int b_lum = luminocity(0x000000FF);

    EXPECT_GT(g_lum, r_lum);
    EXPECT_GT(r_lum, b_lum);
}

// Test specific intermediate value
TEST_F(LuminocityTest_1925, IntermediateValue_1925)
{
    // R=100, G=150, B=200
    // y = (100*19661 + 150*38666 + 200*7209 + 32829) >> 16
    // = (1966100 + 5799900 + 1441800 + 32829) >> 16
    // = 9240629 >> 16
    // = 141
    uint32_t color = 0x006496C8;
    int result = luminocity(color);
    EXPECT_EQ(result, 141);
}
