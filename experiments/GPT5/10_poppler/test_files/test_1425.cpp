#include <gtest/gtest.h>
#include <QColor>
#include <memory>
#include "poppler-annotation.h" // Include the header file where the `convertQColor` function is declared

namespace {

class AnnotColorTest_1425 : public ::testing::Test {
protected:
    // Setup code if needed
    void SetUp() override {
        // No setup required for this example.
    }
};

// Test for transparent color (alpha == 0)
TEST_F(AnnotColorTest_1425, ConvertQColorTransparent_1425) {
    QColor transparentColor(0, 0, 0, 0);
    auto result = Poppler::convertQColor(transparentColor);
    EXPECT_EQ(result, nullptr) << "Expected null for transparent color";
}

// Test for RGB color
TEST_F(AnnotColorTest_1425, ConvertQColorRgb_1425) {
    QColor rgbColor(255, 0, 0); // Red color
    auto result = Poppler::convertQColor(rgbColor);

    ASSERT_NE(result, nullptr) << "Expected valid AnnotColor for RGB color";
    EXPECT_FLOAT_EQ(result->red(), 1.0f) << "Expected red value of 1.0";
    EXPECT_FLOAT_EQ(result->green(), 0.0f) << "Expected green value of 0.0";
    EXPECT_FLOAT_EQ(result->blue(), 0.0f) << "Expected blue value of 0.0";
}

// Test for CMYK color
TEST_F(AnnotColorTest_1425, ConvertQColorCmyk_1425) {
    QColor cmykColor(0, 255, 255, 0); // Cyan and Magenta color
    auto result = Poppler::convertQColor(cmykColor);

    ASSERT_NE(result, nullptr) << "Expected valid AnnotColor for CMYK color";
    EXPECT_FLOAT_EQ(result->cyan(), 1.0f) << "Expected cyan value of 1.0";
    EXPECT_FLOAT_EQ(result->magenta(), 1.0f) << "Expected magenta value of 1.0";
    EXPECT_FLOAT_EQ(result->yellow(), 0.0f) << "Expected yellow value of 0.0";
    EXPECT_FLOAT_EQ(result->black(), 0.0f) << "Expected black value of 0.0";
}

// Test for invalid QColor
TEST_F(AnnotColorTest_1425, ConvertQColorInvalid_1425) {
    QColor invalidColor; // Invalid QColor
    auto result = Poppler::convertQColor(invalidColor);
    EXPECT_EQ(result, nullptr) << "Expected null for invalid color";
}

// Test for HSL color
TEST_F(AnnotColorTest_1425, ConvertQColorHsl_1425) {
    QColor hslColor(0, 255, 255); // HSL color (Red)
    auto result = Poppler::convertQColor(hslColor);

    ASSERT_NE(result, nullptr) << "Expected valid AnnotColor for HSL color";
    EXPECT_FLOAT_EQ(result->red(), 1.0f) << "Expected red value of 1.0";
    EXPECT_FLOAT_EQ(result->green(), 0.0f) << "Expected green value of 0.0";
    EXPECT_FLOAT_EQ(result->blue(), 0.0f) << "Expected blue value of 0.0";
}

// Test for HSV color
TEST_F(AnnotColorTest_1425, ConvertQColorHsv_1425) {
    QColor hsvColor(0, 255, 255); // HSV color (Red)
    auto result = Poppler::convertQColor(hsvColor);

    ASSERT_NE(result, nullptr) << "Expected valid AnnotColor for HSV color";
    EXPECT_FLOAT_EQ(result->red(), 1.0f) << "Expected red value of 1.0";
    EXPECT_FLOAT_EQ(result->green(), 0.0f) << "Expected green value of 0.0";
    EXPECT_FLOAT_EQ(result->blue(), 0.0f) << "Expected blue value of 0.0";
}

}  // namespace