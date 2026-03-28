#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/qt5/src/poppler-annotation.cc"

#include "TestProjects/poppler/poppler/Annot.h"



using namespace Poppler;

using namespace AnnotColor;



// Mock class for AnnotColor

class MockAnnotColor : public AnnotColor {

public:

    MOCK_CONST_METHOD0(getSpace, AnnotColorSpace());

    MOCK_CONST_METHOD0(getValues, const std::array<double, 4>&());

};



TEST(AnnotColorConversionTest_1424, ConvertNullPointerReturnsTransparent_1424) {

    EXPECT_EQ(convertAnnotColor(nullptr), QColor(Qt::transparent));

}



TEST(AnnotColorConversionTest_1424, ConvertTransparentReturnsTransparent_1424) {

    MockAnnotColor mockColor;

    EXPECT_CALL(mockColor, getSpace()).WillOnce(testing::Return(colorTransparent));



    EXPECT_EQ(convertAnnotColor(&mockColor), QColor(Qt::transparent));

}



TEST(AnnotColorConversionTest_1424, ConvertGrayReturnsCorrectColor_1424) {

    MockAnnotColor mockColor;

    const std::array<double, 4> colorData = {0.5, 0.5, 0.5, 0.5};

    EXPECT_CALL(mockColor, getSpace()).WillOnce(testing::Return(colorGray));

    EXPECT_CALL(mockColor, getValues()).WillOnce(testing::ReturnRef(colorData));



    QColor expectedColor;

    expectedColor.setRgbF(0.5, 0.5, 0.5);

    EXPECT_EQ(convertAnnotColor(&mockColor), expectedColor);

}



TEST(AnnotColorConversionTest_1424, ConvertRGBReturnsCorrectColor_1424) {

    MockAnnotColor mockColor;

    const std::array<double, 4> colorData = {0.1, 0.2, 0.3, 0.4};

    EXPECT_CALL(mockColor, getSpace()).WillOnce(testing::Return(colorRGB));

    EXPECT_CALL(mockColor, getValues()).WillOnce(testing::ReturnRef(colorData));



    QColor expectedColor;

    expectedColor.setRgbF(0.1, 0.2, 0.3);

    EXPECT_EQ(convertAnnotColor(&mockColor), expectedColor);

}



TEST(AnnotColorConversionTest_1424, ConvertCMYKReturnsCorrectColor_1424) {

    MockAnnotColor mockColor;

    const std::array<double, 4> colorData = {0.1, 0.2, 0.3, 0.4};

    EXPECT_CALL(mockColor, getSpace()).WillOnce(testing::Return(colorCMYK));

    EXPECT_CALL(mockColor, getValues()).WillOnce(testing::ReturnRef(colorData));



    QColor expectedColor;

    expectedColor.setCmykF(0.1, 0.2, 0.3, 0.4);

    EXPECT_EQ(convertAnnotColor(&mockColor), expectedColor);

}



TEST(AnnotColorConversionTest_1424, ConvertUnknownSpaceReturnsTransparent_1424) {

    MockAnnotColor mockColor;

    EXPECT_CALL(mockColor, getSpace()).WillOnce(testing::Return(static_cast<AnnotColorSpace>(5))); // Invalid space



    EXPECT_EQ(convertAnnotColor(&mockColor), QColor(Qt::transparent));

}
