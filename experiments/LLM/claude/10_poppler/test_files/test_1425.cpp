#include <gtest/gtest.h>
#include <QColor>
#include <memory>

// Forward declare the function we're testing
namespace Poppler {
class AnnotColor;
std::unique_ptr<AnnotColor> convertQColor(const QColor &c);
}

// Since we need to inspect the AnnotColor object, we include the poppler headers
#include <Annot.h>

namespace {

class ConvertQColorTest_1425 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Transparent color (alpha == 0) returns nullptr
TEST_F(ConvertQColorTest_1425, TransparentColorReturnsNull_1425) {
    QColor transparentColor(0, 0, 0, 0); // fully transparent
    auto result = Poppler::convertQColor(transparentColor);
    EXPECT_EQ(result, nullptr);
}

// Test: Invalid QColor returns nullptr
TEST_F(ConvertQColorTest_1425, InvalidColorReturnsNull_1425) {
    QColor invalidColor; // default constructed QColor is invalid
    EXPECT_FALSE(invalidColor.isValid());
    auto result = Poppler::convertQColor(invalidColor);
    EXPECT_EQ(result, nullptr);
}

// Test: Fully opaque RGB color returns non-null AnnotColor with 3 components
TEST_F(ConvertQColorTest_1425, OpaqueRgbColorReturnsAnnotColor_1425) {
    QColor rgbColor(255, 0, 0, 255); // opaque red
    auto result = Poppler::convertQColor(rgbColor);
    ASSERT_NE(result, nullptr);
    // AnnotColor for RGB should have 3 values
    EXPECT_EQ(result->getSpace(), AnnotColor::colorRGB);
    const double *values = result->getValues();
    ASSERT_NE(values, nullptr);
    EXPECT_NEAR(values[0], 1.0, 0.01); // red
    EXPECT_NEAR(values[1], 0.0, 0.01); // green
    EXPECT_NEAR(values[2], 0.0, 0.01); // blue
}

// Test: Opaque green RGB color
TEST_F(ConvertQColorTest_1425, OpaqueGreenRgbColor_1425) {
    QColor greenColor(0, 255, 0, 255);
    auto result = Poppler::convertQColor(greenColor);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getSpace(), AnnotColor::colorRGB);
    const double *values = result->getValues();
    ASSERT_NE(values, nullptr);
    EXPECT_NEAR(values[0], 0.0, 0.01);
    EXPECT_NEAR(values[1], 1.0, 0.01);
    EXPECT_NEAR(values[2], 0.0, 0.01);
}

// Test: Opaque blue RGB color
TEST_F(ConvertQColorTest_1425, OpaqueBlueRgbColor_1425) {
    QColor blueColor(0, 0, 255, 255);
    auto result = Poppler::convertQColor(blueColor);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getSpace(), AnnotColor::colorRGB);
    const double *values = result->getValues();
    ASSERT_NE(values, nullptr);
    EXPECT_NEAR(values[0], 0.0, 0.01);
    EXPECT_NEAR(values[1], 0.0, 0.01);
    EXPECT_NEAR(values[2], 1.0, 0.01);
}

// Test: White RGB color
TEST_F(ConvertQColorTest_1425, WhiteRgbColor_1425) {
    QColor white(255, 255, 255, 255);
    auto result = Poppler::convertQColor(white);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getSpace(), AnnotColor::colorRGB);
    const double *values = result->getValues();
    ASSERT_NE(values, nullptr);
    EXPECT_NEAR(values[0], 1.0, 0.01);
    EXPECT_NEAR(values[1], 1.0, 0.01);
    EXPECT_NEAR(values[2], 1.0, 0.01);
}

// Test: Black RGB color
TEST_F(ConvertQColorTest_1425, BlackRgbColor_1425) {
    QColor black(0, 0, 0, 255);
    auto result = Poppler::convertQColor(black);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getSpace(), AnnotColor::colorRGB);
    const double *values = result->getValues();
    ASSERT_NE(values, nullptr);
    EXPECT_NEAR(values[0], 0.0, 0.01);
    EXPECT_NEAR(values[1], 0.0, 0.01);
    EXPECT_NEAR(values[2], 0.0, 0.01);
}

// Test: CMYK color returns AnnotColor with 4 components
TEST_F(ConvertQColorTest_1425, CmykColorReturnsAnnotColor_1425) {
    QColor cmykColor;
    cmykColor.setCmykF(1.0, 0.0, 0.0, 0.0, 1.0); // full cyan, opaque
    ASSERT_EQ(cmykColor.spec(), QColor::Cmyk);
    auto result = Poppler::convertQColor(cmykColor);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getSpace(), AnnotColor::colorCMYK);
    const double *values = result->getValues();
    ASSERT_NE(values, nullptr);
    EXPECT_NEAR(values[0], 1.0, 0.01); // cyan
    EXPECT_NEAR(values[1], 0.0, 0.01); // magenta
    EXPECT_NEAR(values[2], 0.0, 0.01); // yellow
    EXPECT_NEAR(values[3], 0.0, 0.01); // black
}

// Test: CMYK color with all components set
TEST_F(ConvertQColorTest_1425, CmykColorAllComponents_1425) {
    QColor cmykColor;
    cmykColor.setCmykF(0.25, 0.50, 0.75, 0.10, 1.0);
    ASSERT_EQ(cmykColor.spec(), QColor::Cmyk);
    auto result = Poppler::convertQColor(cmykColor);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getSpace(), AnnotColor::colorCMYK);
    const double *values = result->getValues();
    ASSERT_NE(values, nullptr);
    EXPECT_NEAR(values[0], 0.25, 0.02);
    EXPECT_NEAR(values[1], 0.50, 0.02);
    EXPECT_NEAR(values[2], 0.75, 0.02);
    EXPECT_NEAR(values[3], 0.10, 0.02);
}

// Test: Transparent CMYK color returns nullptr
TEST_F(ConvertQColorTest_1425, TransparentCmykReturnsNull_1425) {
    QColor cmykColor;
    cmykColor.setCmykF(1.0, 0.0, 0.0, 0.0, 0.0); // alpha = 0
    ASSERT_EQ(cmykColor.alpha(), 0);
    auto result = Poppler::convertQColor(cmykColor);
    EXPECT_EQ(result, nullptr);
}

// Test: HSV color gets converted as RGB (redF, greenF, blueF)
TEST_F(ConvertQColorTest_1425, HsvColorReturnsAnnotColor_1425) {
    QColor hsvColor;
    hsvColor.setHsvF(0.0, 1.0, 1.0, 1.0); // pure red in HSV
    ASSERT_EQ(hsvColor.spec(), QColor::Hsv);
    auto result = Poppler::convertQColor(hsvColor);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getSpace(), AnnotColor::colorRGB);
    const double *values = result->getValues();
    ASSERT_NE(values, nullptr);
    // HSV(0, 1, 1) = RGB(255, 0, 0)
    EXPECT_NEAR(values[0], 1.0, 0.02);
    EXPECT_NEAR(values[1], 0.0, 0.02);
    EXPECT_NEAR(values[2], 0.0, 0.02);
}

// Test: HSL color gets converted as RGB (redF, greenF, blueF)
TEST_F(ConvertQColorTest_1425, HslColorReturnsAnnotColor_1425) {
    QColor hslColor;
    hslColor.setHslF(0.333, 1.0, 0.5, 1.0); // approximately green in HSL
    ASSERT_EQ(hslColor.spec(), QColor::Hsl);
    auto result = Poppler::convertQColor(hslColor);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getSpace(), AnnotColor::colorRGB);
}

// Test: Semi-transparent RGB color (alpha != 0) still returns AnnotColor
TEST_F(ConvertQColorTest_1425, SemiTransparentRgbReturnsAnnotColor_1425) {
    QColor semiTransparent(128, 64, 32, 128); // alpha = 128, not 0
    ASSERT_NE(semiTransparent.alpha(), 0);
    auto result = Poppler::convertQColor(semiTransparent);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getSpace(), AnnotColor::colorRGB);
}

// Test: Alpha == 1 (minimum non-zero alpha) should still return valid result
TEST_F(ConvertQColorTest_1425, MinNonZeroAlphaReturnsAnnotColor_1425) {
    QColor almostTransparent(100, 100, 100, 1);
    ASSERT_NE(almostTransparent.alpha(), 0);
    auto result = Poppler::convertQColor(almostTransparent);
    ASSERT_NE(result, nullptr);
}

// Test: Mid-range RGB values
TEST_F(ConvertQColorTest_1425, MidRangeRgbValues_1425) {
    QColor midColor(128, 128, 128, 255);
    auto result = Poppler::convertQColor(midColor);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getSpace(), AnnotColor::colorRGB);
    const double *values = result->getValues();
    ASSERT_NE(values, nullptr);
    // 128/255 ≈ 0.502
    EXPECT_NEAR(values[0], 128.0 / 255.0, 0.02);
    EXPECT_NEAR(values[1], 128.0 / 255.0, 0.02);
    EXPECT_NEAR(values[2], 128.0 / 255.0, 0.02);
}

} // namespace
