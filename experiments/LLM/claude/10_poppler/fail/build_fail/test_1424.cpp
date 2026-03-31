#include <gtest/gtest.h>
#include <QColor>
#include <array>
#include "poppler-annotation.h"
#include "Annot.h"

namespace Poppler {
    QColor convertAnnotColor(const AnnotColor *color);
}

class ConvertAnnotColorTest_1424 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test null pointer input returns invalid/default QColor
TEST_F(ConvertAnnotColorTest_1424, NullColorReturnsDefaultQColor_1424) {
    QColor result = Poppler::convertAnnotColor(nullptr);
    EXPECT_FALSE(result.isValid());
}

// Test transparent color space
TEST_F(ConvertAnnotColorTest_1424, TransparentColorSpace_1424) {
    AnnotColor color;  // Default constructor creates transparent
    QColor result = Poppler::convertAnnotColor(&color);
    // Transparent should map to Qt::transparent
    EXPECT_EQ(result, QColor(Qt::transparent));
    EXPECT_EQ(result.alpha(), 0);
}

// Test grayscale color - black (0.0)
TEST_F(ConvertAnnotColorTest_1424, GrayColorBlack_1424) {
    AnnotColor color(0.0);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_EQ(result.redF(), 0.0);
    EXPECT_EQ(result.greenF(), 0.0);
    EXPECT_EQ(result.blueF(), 0.0);
}

// Test grayscale color - white (1.0)
TEST_F(ConvertAnnotColorTest_1424, GrayColorWhite_1424) {
    AnnotColor color(1.0);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_NEAR(result.redF(), 1.0, 0.01);
    EXPECT_NEAR(result.greenF(), 1.0, 0.01);
    EXPECT_NEAR(result.blueF(), 1.0, 0.01);
}

// Test grayscale color - mid gray (0.5)
TEST_F(ConvertAnnotColorTest_1424, GrayColorMidGray_1424) {
    AnnotColor color(0.5);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_NEAR(result.redF(), 0.5, 0.01);
    EXPECT_NEAR(result.greenF(), 0.5, 0.01);
    EXPECT_NEAR(result.blueF(), 0.5, 0.01);
}

// Test RGB color - pure red
TEST_F(ConvertAnnotColorTest_1424, RGBColorPureRed_1424) {
    AnnotColor color(1.0, 0.0, 0.0);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_NEAR(result.redF(), 1.0, 0.01);
    EXPECT_NEAR(result.greenF(), 0.0, 0.01);
    EXPECT_NEAR(result.blueF(), 0.0, 0.01);
}

// Test RGB color - pure green
TEST_F(ConvertAnnotColorTest_1424, RGBColorPureGreen_1424) {
    AnnotColor color(0.0, 1.0, 0.0);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_NEAR(result.redF(), 0.0, 0.01);
    EXPECT_NEAR(result.greenF(), 1.0, 0.01);
    EXPECT_NEAR(result.blueF(), 0.0, 0.01);
}

// Test RGB color - pure blue
TEST_F(ConvertAnnotColorTest_1424, RGBColorPureBlue_1424) {
    AnnotColor color(0.0, 0.0, 1.0);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_NEAR(result.redF(), 0.0, 0.01);
    EXPECT_NEAR(result.greenF(), 0.0, 0.01);
    EXPECT_NEAR(result.blueF(), 1.0, 0.01);
}

// Test RGB color - white
TEST_F(ConvertAnnotColorTest_1424, RGBColorWhite_1424) {
    AnnotColor color(1.0, 1.0, 1.0);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_NEAR(result.redF(), 1.0, 0.01);
    EXPECT_NEAR(result.greenF(), 1.0, 0.01);
    EXPECT_NEAR(result.blueF(), 1.0, 0.01);
}

// Test RGB color - black
TEST_F(ConvertAnnotColorTest_1424, RGBColorBlack_1424) {
    AnnotColor color(0.0, 0.0, 0.0);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_NEAR(result.redF(), 0.0, 0.01);
    EXPECT_NEAR(result.greenF(), 0.0, 0.01);
    EXPECT_NEAR(result.blueF(), 0.0, 0.01);
}

// Test RGB color - mixed values
TEST_F(ConvertAnnotColorTest_1424, RGBColorMixed_1424) {
    AnnotColor color(0.25, 0.5, 0.75);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_NEAR(result.redF(), 0.25, 0.01);
    EXPECT_NEAR(result.greenF(), 0.5, 0.01);
    EXPECT_NEAR(result.blueF(), 0.75, 0.01);
}

// Test CMYK color - all zeros (white in CMYK)
TEST_F(ConvertAnnotColorTest_1424, CMYKColorAllZeros_1424) {
    AnnotColor color(0.0, 0.0, 0.0, 0.0);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_TRUE(result.isValid());
    EXPECT_EQ(result.spec(), QColor::Cmyk);
    EXPECT_NEAR(result.cyanF(), 0.0, 0.01);
    EXPECT_NEAR(result.magentaF(), 0.0, 0.01);
    EXPECT_NEAR(result.yellowF(), 0.0, 0.01);
    EXPECT_NEAR(result.blackF(), 0.0, 0.01);
}

// Test CMYK color - full black
TEST_F(ConvertAnnotColorTest_1424, CMYKColorFullBlack_1424) {
    AnnotColor color(0.0, 0.0, 0.0, 1.0);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_TRUE(result.isValid());
    EXPECT_NEAR(result.blackF(), 1.0, 0.01);
}

// Test CMYK color - mixed values
TEST_F(ConvertAnnotColorTest_1424, CMYKColorMixed_1424) {
    AnnotColor color(0.1, 0.2, 0.3, 0.4);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_TRUE(result.isValid());
    EXPECT_NEAR(result.cyanF(), 0.1, 0.01);
    EXPECT_NEAR(result.magentaF(), 0.2, 0.01);
    EXPECT_NEAR(result.yellowF(), 0.3, 0.01);
    EXPECT_NEAR(result.blackF(), 0.4, 0.01);
}

// Test CMYK color - full cyan
TEST_F(ConvertAnnotColorTest_1424, CMYKColorFullCyan_1424) {
    AnnotColor color(1.0, 0.0, 0.0, 0.0);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_TRUE(result.isValid());
    EXPECT_NEAR(result.cyanF(), 1.0, 0.01);
    EXPECT_NEAR(result.magentaF(), 0.0, 0.01);
    EXPECT_NEAR(result.yellowF(), 0.0, 0.01);
    EXPECT_NEAR(result.blackF(), 0.0, 0.01);
}

// Test that result QColor from valid color is always valid
TEST_F(ConvertAnnotColorTest_1424, ValidColorProducesValidQColor_1424) {
    AnnotColor gray(0.5);
    QColor grayResult = Poppler::convertAnnotColor(&gray);
    EXPECT_TRUE(grayResult.isValid());

    AnnotColor rgb(0.5, 0.5, 0.5);
    QColor rgbResult = Poppler::convertAnnotColor(&rgb);
    EXPECT_TRUE(rgbResult.isValid());

    AnnotColor cmyk(0.5, 0.5, 0.5, 0.5);
    QColor cmykResult = Poppler::convertAnnotColor(&cmyk);
    EXPECT_TRUE(cmykResult.isValid());
}

// Test that gray color space returns same value for R, G, B
TEST_F(ConvertAnnotColorTest_1424, GrayColorHasEqualRGB_1424) {
    AnnotColor color(0.7);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_NEAR(result.redF(), result.greenF(), 0.001);
    EXPECT_NEAR(result.greenF(), result.blueF(), 0.001);
}

// Test boundary: grayscale at exact 0.0
TEST_F(ConvertAnnotColorTest_1424, GrayBoundaryZero_1424) {
    AnnotColor color(0.0);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_NEAR(result.redF(), 0.0, 0.01);
    EXPECT_NEAR(result.greenF(), 0.0, 0.01);
    EXPECT_NEAR(result.blueF(), 0.0, 0.01);
}

// Test boundary: RGB at exact boundary values
TEST_F(ConvertAnnotColorTest_1424, RGBBoundaryValues_1424) {
    AnnotColor color(0.0, 0.0, 0.0);
    QColor result = Poppler::convertAnnotColor(&color);
    EXPECT_NEAR(result.redF(), 0.0, 0.01);

    AnnotColor color2(1.0, 1.0, 1.0);
    QColor result2 = Poppler::convertAnnotColor(&color2);
    EXPECT_NEAR(result2.redF(), 1.0, 0.01);
    EXPECT_NEAR(result2.greenF(), 1.0, 0.01);
    EXPECT_NEAR(result2.blueF(), 1.0, 0.01);
}
