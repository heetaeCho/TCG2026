#include <gtest/gtest.h>
#include "HtmlFonts.h"

// Helper to create HtmlFontColor with specific RGB and opacity values
// Since we only have two constructors: default and GfxRGB-based,
// we'll use what's available.

class HtmlFontColorTest_2617 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that default-constructed HtmlFontColor objects are equal to each other
TEST_F(HtmlFontColorTest_2617, DefaultConstructedColorsAreEqual_2617) {
    HtmlFontColor col1;
    HtmlFontColor col2;
    EXPECT_TRUE(col1.isEqual(col2));
    EXPECT_TRUE(col2.isEqual(col1));
}

// Test that a default-constructed color is equal to itself
TEST_F(HtmlFontColorTest_2617, ColorIsEqualToItself_2617) {
    HtmlFontColor col;
    EXPECT_TRUE(col.isEqual(col));
}

// Test that a GfxRGB-constructed color is equal to another with same values
TEST_F(HtmlFontColorTest_2617, SameGfxRGBColorsAreEqual_2617) {
    GfxRGB rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;
    double opacity = 1.0;
    HtmlFontColor col1(rgb, opacity);
    HtmlFontColor col2(rgb, opacity);
    EXPECT_TRUE(col1.isEqual(col2));
    EXPECT_TRUE(col2.isEqual(col1));
}

// Test that different RGB values produce non-equal colors
TEST_F(HtmlFontColorTest_2617, DifferentRGBColorsAreNotEqual_2617) {
    GfxRGB rgb1;
    rgb1.r = 0;
    rgb1.g = 0;
    rgb1.b = 0;

    GfxRGB rgb2;
    rgb2.r = 65535; // max value for GfxColorComp
    rgb2.g = 0;
    rgb2.b = 0;

    HtmlFontColor col1(rgb1, 1.0);
    HtmlFontColor col2(rgb2, 1.0);
    EXPECT_FALSE(col1.isEqual(col2));
    EXPECT_FALSE(col2.isEqual(col1));
}

// Test that different opacity values produce non-equal colors
TEST_F(HtmlFontColorTest_2617, DifferentOpacityColorsAreNotEqual_2617) {
    GfxRGB rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;

    HtmlFontColor col1(rgb, 1.0);
    HtmlFontColor col2(rgb, 0.5);
    EXPECT_FALSE(col1.isEqual(col2));
}

// Test that default constructed color compared with GfxRGB(0,0,0) and full opacity
TEST_F(HtmlFontColorTest_2617, DefaultVsBlackFullOpacity_2617) {
    HtmlFontColor defaultCol;
    GfxRGB rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;
    HtmlFontColor blackCol(rgb, 1.0);
    // Default has r=0, g=0, b=0, opacity=255
    // GfxRGB(0,0,0) with opacity 1.0 should also map to r=0, g=0, b=0, opacity=255
    EXPECT_TRUE(defaultCol.isEqual(blackCol));
}

// Test symmetry of isEqual
TEST_F(HtmlFontColorTest_2617, IsEqualIsSymmetric_2617) {
    GfxRGB rgb1;
    rgb1.r = 32768;
    rgb1.g = 16384;
    rgb1.b = 49152;

    GfxRGB rgb2;
    rgb2.r = 32768;
    rgb2.g = 16384;
    rgb2.b = 49152;

    HtmlFontColor col1(rgb1, 0.75);
    HtmlFontColor col2(rgb2, 0.75);
    EXPECT_TRUE(col1.isEqual(col2));
    EXPECT_TRUE(col2.isEqual(col1));
}

// Test colors differing only in green channel
TEST_F(HtmlFontColorTest_2617, DifferentGreenChannelNotEqual_2617) {
    GfxRGB rgb1;
    rgb1.r = 0;
    rgb1.g = 0;
    rgb1.b = 0;

    GfxRGB rgb2;
    rgb2.r = 0;
    rgb2.g = 65535;
    rgb2.b = 0;

    HtmlFontColor col1(rgb1, 1.0);
    HtmlFontColor col2(rgb2, 1.0);
    EXPECT_FALSE(col1.isEqual(col2));
}

// Test colors differing only in blue channel
TEST_F(HtmlFontColorTest_2617, DifferentBlueChannelNotEqual_2617) {
    GfxRGB rgb1;
    rgb1.r = 0;
    rgb1.g = 0;
    rgb1.b = 0;

    GfxRGB rgb2;
    rgb2.r = 0;
    rgb2.g = 0;
    rgb2.b = 65535;

    HtmlFontColor col1(rgb1, 1.0);
    HtmlFontColor col2(rgb2, 1.0);
    EXPECT_FALSE(col1.isEqual(col2));
}

// Test getOpacity for default constructed color
TEST_F(HtmlFontColorTest_2617, DefaultOpacityValue_2617) {
    HtmlFontColor col;
    // Default opacity is 255, getOpacity should return something related
    double opacity = col.getOpacity();
    // opacity=255 corresponds to 1.0 (fully opaque) or 255 as raw
    // We test it's a valid value
    EXPECT_GE(opacity, 0.0);
}

// Test getOpacity for GfxRGB-constructed color with full opacity
TEST_F(HtmlFontColorTest_2617, FullOpacityGetOpacity_2617) {
    GfxRGB rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;
    HtmlFontColor col(rgb, 1.0);
    double opacity = col.getOpacity();
    EXPECT_GE(opacity, 0.0);
}

// Test getOpacity for color with zero opacity
TEST_F(HtmlFontColorTest_2617, ZeroOpacityGetOpacity_2617) {
    GfxRGB rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;
    HtmlFontColor col(rgb, 0.0);
    double opacity = col.getOpacity();
    EXPECT_GE(opacity, 0.0);
}

// Test toString returns a non-empty string for default color
TEST_F(HtmlFontColorTest_2617, ToStringDefaultColor_2617) {
    HtmlFontColor col;
    std::string str = col.toString();
    EXPECT_FALSE(str.empty());
}

// Test toString returns a non-empty string for a colored font
TEST_F(HtmlFontColorTest_2617, ToStringColoredFont_2617) {
    GfxRGB rgb;
    rgb.r = 65535;
    rgb.g = 0;
    rgb.b = 0;
    HtmlFontColor col(rgb, 1.0);
    std::string str = col.toString();
    EXPECT_FALSE(str.empty());
}

// Test toString for black color should contain "000000" or equivalent
TEST_F(HtmlFontColorTest_2617, ToStringBlackColor_2617) {
    HtmlFontColor col;
    std::string str = col.toString();
    // Default is black (0,0,0), toString should represent this
    EXPECT_NE(str.find("00"), std::string::npos);
}

// Test that two colors with all different channels are not equal
TEST_F(HtmlFontColorTest_2617, AllDifferentChannelsNotEqual_2617) {
    GfxRGB rgb1;
    rgb1.r = 0;
    rgb1.g = 0;
    rgb1.b = 0;

    GfxRGB rgb2;
    rgb2.r = 65535;
    rgb2.g = 65535;
    rgb2.b = 65535;

    HtmlFontColor col1(rgb1, 1.0);
    HtmlFontColor col2(rgb2, 1.0);
    EXPECT_FALSE(col1.isEqual(col2));
}

// Test transitivity: if a == b and b == c, then a == c
TEST_F(HtmlFontColorTest_2617, IsEqualIsTransitive_2617) {
    GfxRGB rgb;
    rgb.r = 12345;
    rgb.g = 23456;
    rgb.b = 34567;

    HtmlFontColor col1(rgb, 0.8);
    HtmlFontColor col2(rgb, 0.8);
    HtmlFontColor col3(rgb, 0.8);

    EXPECT_TRUE(col1.isEqual(col2));
    EXPECT_TRUE(col2.isEqual(col3));
    EXPECT_TRUE(col1.isEqual(col3));
}
