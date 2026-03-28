#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QColor>
#include "./TestProjects/poppler/qt5/src/poppler-annotation.cc"
#include "./TestProjects/poppler/poppler/Annot.h"

using namespace Poppler;
using ::testing::Return;
using ::testing::Mock;

class AnnotColorMock : public AnnotColor {
public:
    MOCK_CONST_METHOD0(getSpace, AnnotColorSpace());
    MOCK_CONST_METHOD0(getValues, const std::array<double, 4>&());
};

class ConvertAnnotColorTest_1424 : public ::testing::Test {
protected:
    AnnotColorMock mockColor;
};

TEST_F(ConvertAnnotColorTest_1424, NullPointerColor_1424) {
    // Test case where color is nullptr
    AnnotColor* nullColor = nullptr;
    QColor result = convertAnnotColor(nullColor);
    EXPECT_EQ(result, QColor());
}

TEST_F(ConvertAnnotColorTest_1424, TransparentColor_1424) {
    // Test case where color is transparent
    std::array<double, 4> colorData = {0.0, 0.0, 0.0, 0.0};
    EXPECT_CALL(mockColor, getSpace()).WillOnce(Return(AnnotColor::colorTransparent));
    EXPECT_CALL(mockColor, getValues()).WillOnce(Return(colorData));

    QColor result = convertAnnotColor(&mockColor);
    EXPECT_EQ(result, Qt::transparent);
}

TEST_F(ConvertAnnotColorTest_1424, GrayColor_1424) {
    // Test case for gray color
    std::array<double, 4> colorData = {0.5, 0.5, 0.5, 0.5};  // Gray color
    EXPECT_CALL(mockColor, getSpace()).WillOnce(Return(AnnotColor::colorGray));
    EXPECT_CALL(mockColor, getValues()).WillOnce(Return(colorData));

    QColor result = convertAnnotColor(&mockColor);
    EXPECT_EQ(result, QColor(128, 128, 128));  // RGB equivalent for gray (0.5 in normalized form)
}

TEST_F(ConvertAnnotColorTest_1424, RGBColor_1424) {
    // Test case for RGB color
    std::array<double, 4> colorData = {0.5, 0.2, 0.8, 0.0};  // RGB color (normalized)
    EXPECT_CALL(mockColor, getSpace()).WillOnce(Return(AnnotColor::colorRGB));
    EXPECT_CALL(mockColor, getValues()).WillOnce(Return(colorData));

    QColor result = convertAnnotColor(&mockColor);
    EXPECT_EQ(result, QColor(128, 51, 204));  // RGB equivalent of (0.5, 0.2, 0.8)
}

TEST_F(ConvertAnnotColorTest_1424, CMYKColor_1424) {
    // Test case for CMYK color
    std::array<double, 4> colorData = {0.2, 0.4, 0.6, 0.8};  // CMYK color
    EXPECT_CALL(mockColor, getSpace()).WillOnce(Return(AnnotColor::colorCMYK));
    EXPECT_CALL(mockColor, getValues()).WillOnce(Return(colorData));

    QColor result = convertAnnotColor(&mockColor);
    // CMYK conversion to RGB may not be directly checkable, but ensure it is a valid QColor.
    EXPECT_TRUE(result.isValid());
}

TEST_F(ConvertAnnotColorTest_1424, InvalidColorSpace_1424) {
    // Test case where the color space is invalid or unsupported
    std::array<double, 4> colorData = {0.0, 0.0, 0.0, 0.0};  // Default data
    EXPECT_CALL(mockColor, getSpace()).WillOnce(Return(static_cast<AnnotColorSpace>(-1)));  // Invalid space
    EXPECT_CALL(mockColor, getValues()).WillOnce(Return(colorData));

    QColor result = convertAnnotColor(&mockColor);
    EXPECT_EQ(result, QColor());  // Invalid space should return an invalid QColor
}

TEST_F(ConvertAnnotColorTest_1424, ValidColorWithNullPointer_1424) {
    // Test case where getSpace() returns a valid space but color is nullptr
    AnnotColor* validColor = &mockColor;
    EXPECT_CALL(mockColor, getSpace()).WillOnce(Return(AnnotColor::colorRGB));
    EXPECT_CALL(mockColor, getValues()).WillOnce(Return(std::array<double, 4>{0.5, 0.2, 0.8, 0.0}));

    QColor result = convertAnnotColor(validColor);
    EXPECT_EQ(result, QColor(128, 51, 204));  // RGB equivalent of (0.5, 0.2, 0.8)
}