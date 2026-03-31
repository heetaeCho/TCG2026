#include <gtest/gtest.h>
#include "Annot.h"

// Test default constructor
TEST(AnnotColorTest_755, DefaultConstructor_755) {
    AnnotColor color;
    const auto &values = color.getValues();
    // Default constructor should initialize values
    // We just verify it doesn't crash and returns a valid reference
    EXPECT_EQ(values.size(), 4u);
}

// Test grayscale constructor
TEST(AnnotColorTest_755, GrayConstructor_755) {
    AnnotColor color(0.5);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.5);
}

// Test grayscale constructor with 0.0
TEST(AnnotColorTest_755, GrayConstructorZero_755) {
    AnnotColor color(0.0);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.0);
}

// Test grayscale constructor with 1.0
TEST(AnnotColorTest_755, GrayConstructorOne_755) {
    AnnotColor color(1.0);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 1.0);
}

// Test RGB constructor
TEST(AnnotColorTest_755, RGBConstructor_755) {
    AnnotColor color(0.1, 0.2, 0.3);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.1);
    EXPECT_DOUBLE_EQ(values[1], 0.2);
    EXPECT_DOUBLE_EQ(values[2], 0.3);
}

// Test RGB constructor with all zeros
TEST(AnnotColorTest_755, RGBConstructorAllZeros_755) {
    AnnotColor color(0.0, 0.0, 0.0);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.0);
    EXPECT_DOUBLE_EQ(values[1], 0.0);
    EXPECT_DOUBLE_EQ(values[2], 0.0);
}

// Test RGB constructor with all ones
TEST(AnnotColorTest_755, RGBConstructorAllOnes_755) {
    AnnotColor color(1.0, 1.0, 1.0);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 1.0);
    EXPECT_DOUBLE_EQ(values[1], 1.0);
    EXPECT_DOUBLE_EQ(values[2], 1.0);
}

// Test CMYK constructor
TEST(AnnotColorTest_755, CMYKConstructor_755) {
    AnnotColor color(0.1, 0.2, 0.3, 0.4);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.1);
    EXPECT_DOUBLE_EQ(values[1], 0.2);
    EXPECT_DOUBLE_EQ(values[2], 0.3);
    EXPECT_DOUBLE_EQ(values[3], 0.4);
}

// Test CMYK constructor with all zeros
TEST(AnnotColorTest_755, CMYKConstructorAllZeros_755) {
    AnnotColor color(0.0, 0.0, 0.0, 0.0);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.0);
    EXPECT_DOUBLE_EQ(values[1], 0.0);
    EXPECT_DOUBLE_EQ(values[2], 0.0);
    EXPECT_DOUBLE_EQ(values[3], 0.0);
}

// Test CMYK constructor with all ones
TEST(AnnotColorTest_755, CMYKConstructorAllOnes_755) {
    AnnotColor color(1.0, 1.0, 1.0, 1.0);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 1.0);
    EXPECT_DOUBLE_EQ(values[1], 1.0);
    EXPECT_DOUBLE_EQ(values[2], 1.0);
    EXPECT_DOUBLE_EQ(values[3], 1.0);
}

// Test getSpace for grayscale
TEST(AnnotColorTest_755, GetSpaceGray_755) {
    AnnotColor color(0.5);
    AnnotColor::AnnotColorSpace space = color.getSpace();
    // Gray should be a specific color space enum value
    // We verify it returns without error and is consistent
    AnnotColor color2(0.7);
    EXPECT_EQ(color.getSpace(), color2.getSpace());
}

// Test getSpace for RGB
TEST(AnnotColorTest_755, GetSpaceRGB_755) {
    AnnotColor color(0.1, 0.2, 0.3);
    AnnotColor::AnnotColorSpace space = color.getSpace();
    // RGB space should differ from gray space
    AnnotColor grayColor(0.5);
    EXPECT_NE(color.getSpace(), grayColor.getSpace());
}

// Test getSpace for CMYK
TEST(AnnotColorTest_755, GetSpaceCMYK_755) {
    AnnotColor color(0.1, 0.2, 0.3, 0.4);
    AnnotColor::AnnotColorSpace space = color.getSpace();
    // CMYK should differ from RGB and gray
    AnnotColor rgbColor(0.1, 0.2, 0.3);
    AnnotColor grayColor(0.5);
    EXPECT_NE(color.getSpace(), rgbColor.getSpace());
    EXPECT_NE(color.getSpace(), grayColor.getSpace());
}

// Test getValues returns a reference to the same data
TEST(AnnotColorTest_755, GetValuesReturnsSameReference_755) {
    AnnotColor color(0.1, 0.2, 0.3);
    const auto &values1 = color.getValues();
    const auto &values2 = color.getValues();
    EXPECT_EQ(&values1, &values2);
}

// Test values array size is always 4
TEST(AnnotColorTest_755, ValuesArraySizeIsFour_755) {
    AnnotColor gray(0.5);
    EXPECT_EQ(gray.getValues().size(), 4u);

    AnnotColor rgb(0.1, 0.2, 0.3);
    EXPECT_EQ(rgb.getValues().size(), 4u);

    AnnotColor cmyk(0.1, 0.2, 0.3, 0.4);
    EXPECT_EQ(cmyk.getValues().size(), 4u);
}

// Test boundary values near limits
TEST(AnnotColorTest_755, BoundaryValuesRGB_755) {
    AnnotColor color(0.0, 0.5, 1.0);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.0);
    EXPECT_DOUBLE_EQ(values[1], 0.5);
    EXPECT_DOUBLE_EQ(values[2], 1.0);
}

// Test that different constructors produce different color spaces
TEST(AnnotColorTest_755, DifferentConstructorsDifferentSpaces_755) {
    AnnotColor defaultColor;
    AnnotColor grayColor(0.5);
    AnnotColor rgbColor(0.1, 0.2, 0.3);
    AnnotColor cmykColor(0.1, 0.2, 0.3, 0.4);

    // At minimum, RGB, gray, and CMYK should have different spaces
    EXPECT_NE(grayColor.getSpace(), rgbColor.getSpace());
    EXPECT_NE(rgbColor.getSpace(), cmykColor.getSpace());
    EXPECT_NE(grayColor.getSpace(), cmykColor.getSpace());
}

// Test copy semantics
TEST(AnnotColorTest_755, CopyConstructor_755) {
    AnnotColor original(0.1, 0.2, 0.3);
    AnnotColor copy(original);
    const auto &origValues = original.getValues();
    const auto &copyValues = copy.getValues();
    EXPECT_DOUBLE_EQ(origValues[0], copyValues[0]);
    EXPECT_DOUBLE_EQ(origValues[1], copyValues[1]);
    EXPECT_DOUBLE_EQ(origValues[2], copyValues[2]);
    EXPECT_EQ(original.getSpace(), copy.getSpace());
}

// Test small fractional values
TEST(AnnotColorTest_755, SmallFractionalValues_755) {
    AnnotColor color(0.001, 0.002, 0.003, 0.004);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.001);
    EXPECT_DOUBLE_EQ(values[1], 0.002);
    EXPECT_DOUBLE_EQ(values[2], 0.003);
    EXPECT_DOUBLE_EQ(values[3], 0.004);
}
