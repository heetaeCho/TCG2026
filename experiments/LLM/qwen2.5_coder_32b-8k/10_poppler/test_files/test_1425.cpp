#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation.cc"  // Assuming the function is in this file or linked appropriately



namespace {



using namespace Poppler;



TEST(AnnotColorConversionTest_1425, ConvertTransparentQColor_ReturnsNullPtr_1425) {

    QColor transparentColor(Qt::transparent);

    std::unique_ptr<AnnotColor> color = convertQColor(transparentColor);

    EXPECT_EQ(color.get(), nullptr);

}



TEST(AnnotColorConversionTest_1425, ConvertRgbQColor_ReturnsValidAnnotColor_1425) {

    QColor rgbColor(Qt::red);

    std::unique_ptr<AnnotColor> color = convertQColor(rgbColor);

    EXPECT_NE(color.get(), nullptr);

    // Assuming AnnotColor constructor sets values correctly

}



TEST(AnnotColorConversionTest_1425, ConvertHslQColor_ReturnsValidAnnotColor_1425) {

    QColor hslColor;

    hslColor.setHsl(120, 255, 192); // Green color in HSL

    std::unique_ptr<AnnotColor> color = convertQColor(hslColor);

    EXPECT_NE(color.get(), nullptr);

}



TEST(AnnotColorConversionTest_1425, ConvertHsvQColor_ReturnsValidAnnotColor_1425) {

    QColor hsvColor;

    hsvColor.setHsv(60, 255, 255); // Yellow color in HSV

    std::unique_ptr<AnnotColor> color = convertQColor(hsvColor);

    EXPECT_NE(color.get(), nullptr);

}



TEST(AnnotColorConversionTest_1425, ConvertCmykQColor_ReturnsValidAnnotColor_1425) {

    QColor cmykColor;

    cmykColor.setCmyk(0, 100, 100, 0); // Red color in CMYK

    std::unique_ptr<AnnotColor> color = convertQColor(cmykColor);

    EXPECT_NE(color.get(), nullptr);

}



TEST(AnnotColorConversionTest_1425, ConvertInvalidQColor_ReturnsNullPtr_1425) {

    QColor invalidColor;

    invalidColor.setNamedColor("invalid_color");

    std::unique_ptr<AnnotColor> color = convertQColor(invalidColor);

    EXPECT_EQ(color.get(), nullptr);

}



TEST(AnnotColorConversionTest_1425, ConvertDefaultConstructedQColor_ReturnsNullPtr_1425) {

    QColor defaultColor;

    std::unique_ptr<AnnotColor> color = convertQColor(defaultColor);

    EXPECT_EQ(color.get(), nullptr);

}



}  // namespace
