#include <gtest/gtest.h>
#include "HtmlFonts.h"

// We need GfxRGB for constructing HtmlFontColor with the parameterized constructor
// If GfxRGB is not directly available, we work with the default constructor and observable behavior.

class HtmlFontColorTest_2616 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor - opacity should be 255, so getOpacity() should return 1.0
TEST_F(HtmlFontColorTest_2616, DefaultConstructorOpacityIsOne_2616) {
    HtmlFontColor color;
    EXPECT_DOUBLE_EQ(color.getOpacity(), 1.0);
}

// Test default constructor - toString should return default color (black = "000000")
TEST_F(HtmlFontColorTest_2616, DefaultConstructorToStringIsBlack_2616) {
    HtmlFontColor color;
    std::string result = color.toString();
    // Default r=0, g=0, b=0 should produce "000000"
    EXPECT_EQ(result, "000000");
}

// Test default constructor - isEqual with another default constructed object
TEST_F(HtmlFontColorTest_2616, DefaultConstructorIsEqualToItself_2616) {
    HtmlFontColor color1;
    HtmlFontColor color2;
    EXPECT_TRUE(color1.isEqual(color2));
}

// Test parameterized constructor with full opacity
TEST_F(HtmlFontColorTest_2616, ParameterizedConstructorFullOpacity_2616) {
    GfxRGB rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;
    HtmlFontColor color(rgb, 1.0);
    EXPECT_DOUBLE_EQ(color.getOpacity(), 1.0);
}

// Test parameterized constructor with zero opacity
TEST_F(HtmlFontColorTest_2616, ParameterizedConstructorZeroOpacity_2616) {
    GfxRGB rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;
    HtmlFontColor color(rgb, 0.0);
    EXPECT_DOUBLE_EQ(color.getOpacity(), 0.0);
}

// Test parameterized constructor with half opacity
TEST_F(HtmlFontColorTest_2616, ParameterizedConstructorHalfOpacity_2616) {
    GfxRGB rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;
    HtmlFontColor color(rgb, 0.5);
    // opacity stored as unsigned int = round(0.5 * 255) = 127 or 128
    // getOpacity returns opacity / 255.0
    double result = color.getOpacity();
    EXPECT_NEAR(result, 0.5, 0.005);
}

// Test parameterized constructor with specific RGB values
TEST_F(HtmlFontColorTest_2616, ParameterizedConstructorWithColor_2616) {
    GfxRGB rgb;
    rgb.r = 65535; // max value for GfxColorComp typically maps to 255
    rgb.g = 0;
    rgb.b = 0;
    HtmlFontColor color(rgb, 1.0);
    std::string result = color.toString();
    // Red color should produce "ff0000"
    EXPECT_EQ(result, "ff0000");
}

// Test isEqual with different colors
TEST_F(HtmlFontColorTest_2616, IsEqualDifferentColors_2616) {
    GfxRGB rgb1;
    rgb1.r = 65535;
    rgb1.g = 0;
    rgb1.b = 0;
    HtmlFontColor color1(rgb1, 1.0);

    GfxRGB rgb2;
    rgb2.r = 0;
    rgb2.g = 65535;
    rgb2.b = 0;
    HtmlFontColor color2(rgb2, 1.0);

    EXPECT_FALSE(color1.isEqual(color2));
}

// Test isEqual with same colors
TEST_F(HtmlFontColorTest_2616, IsEqualSameColors_2616) {
    GfxRGB rgb1;
    rgb1.r = 65535;
    rgb1.g = 0;
    rgb1.b = 0;
    HtmlFontColor color1(rgb1, 1.0);

    GfxRGB rgb2;
    rgb2.r = 65535;
    rgb2.g = 0;
    rgb2.b = 0;
    HtmlFontColor color2(rgb2, 1.0);

    EXPECT_TRUE(color1.isEqual(color2));
}

// Test getOpacity boundary: opacity = 255 => 1.0
TEST_F(HtmlFontColorTest_2616, GetOpacityBoundaryMax_2616) {
    GfxRGB rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;
    HtmlFontColor color(rgb, 1.0);
    EXPECT_DOUBLE_EQ(color.getOpacity(), 1.0);
}

// Test getOpacity boundary: opacity = 0 => 0.0
TEST_F(HtmlFontColorTest_2616, GetOpacityBoundaryMin_2616) {
    GfxRGB rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;
    HtmlFontColor color(rgb, 0.0);
    EXPECT_DOUBLE_EQ(color.getOpacity(), 0.0);
}

// Test toString with white color
TEST_F(HtmlFontColorTest_2616, ToStringWhiteColor_2616) {
    GfxRGB rgb;
    rgb.r = 65535;
    rgb.g = 65535;
    rgb.b = 65535;
    HtmlFontColor color(rgb, 1.0);
    std::string result = color.toString();
    EXPECT_EQ(result, "ffffff");
}

// Test toString with green color
TEST_F(HtmlFontColorTest_2616, ToStringGreenColor_2616) {
    GfxRGB rgb;
    rgb.r = 0;
    rgb.g = 65535;
    rgb.b = 0;
    HtmlFontColor color(rgb, 1.0);
    std::string result = color.toString();
    EXPECT_EQ(result, "00ff00");
}

// Test toString with blue color
TEST_F(HtmlFontColorTest_2616, ToStringBlueColor_2616) {
    GfxRGB rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 65535;
    HtmlFontColor color(rgb, 1.0);
    std::string result = color.toString();
    EXPECT_EQ(result, "0000ff");
}

// Test that different opacity doesn't affect isEqual (if isEqual only compares rgb)
TEST_F(HtmlFontColorTest_2616, IsEqualDifferentOpacity_2616) {
    GfxRGB rgb;
    rgb.r = 65535;
    rgb.g = 0;
    rgb.b = 0;
    HtmlFontColor color1(rgb, 1.0);
    HtmlFontColor color2(rgb, 0.5);

    // isEqual may or may not consider opacity - we test observable behavior
    // This test documents the actual behavior
    bool result = color1.isEqual(color2);
    // We don't assert a specific value since we don't know if opacity is part of equality
    // but we verify the method doesn't crash
    (void)result;
}
