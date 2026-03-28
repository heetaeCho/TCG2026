#include <gtest/gtest.h>
#include "Annot.h"

// Test default constructor
TEST_F(AnnotColorTest_754, DefaultConstructor_754) {
    // Note: We cannot use TEST_F without a fixture, use TEST instead
}

// Using TEST instead since we don't have a fixture class defined
class AnnotColorTest_754 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor - should create a colorTransparent (length 0)
TEST_F(AnnotColorTest_754, DefaultConstructorCreatesTransparent_754) {
    AnnotColor color;
    EXPECT_EQ(color.getSpace(), AnnotColor::colorTransparent);
}

// Test single-argument constructor (gray) - should create colorGray (length 1)
TEST_F(AnnotColorTest_754, GrayConstructorCreatesGrayColorSpace_754) {
    AnnotColor color(0.5);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorGray);
}

// Test gray constructor with 0.0
TEST_F(AnnotColorTest_754, GrayConstructorWithZero_754) {
    AnnotColor color(0.0);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorGray);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.0);
}

// Test gray constructor with 1.0
TEST_F(AnnotColorTest_754, GrayConstructorWithOne_754) {
    AnnotColor color(1.0);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorGray);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 1.0);
}

// Test RGB constructor - should create colorRGB (length 3)
TEST_F(AnnotColorTest_754, RGBConstructorCreatesRGBColorSpace_754) {
    AnnotColor color(0.1, 0.2, 0.3);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorRGB);
}

// Test RGB constructor values
TEST_F(AnnotColorTest_754, RGBConstructorStoresCorrectValues_754) {
    AnnotColor color(0.1, 0.2, 0.3);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.1);
    EXPECT_DOUBLE_EQ(values[1], 0.2);
    EXPECT_DOUBLE_EQ(values[2], 0.3);
}

// Test RGB constructor with all zeros
TEST_F(AnnotColorTest_754, RGBConstructorAllZeros_754) {
    AnnotColor color(0.0, 0.0, 0.0);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorRGB);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.0);
    EXPECT_DOUBLE_EQ(values[1], 0.0);
    EXPECT_DOUBLE_EQ(values[2], 0.0);
}

// Test RGB constructor with all ones
TEST_F(AnnotColorTest_754, RGBConstructorAllOnes_754) {
    AnnotColor color(1.0, 1.0, 1.0);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorRGB);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 1.0);
    EXPECT_DOUBLE_EQ(values[1], 1.0);
    EXPECT_DOUBLE_EQ(values[2], 1.0);
}

// Test CMYK constructor - should create colorCMYK (length 4)
TEST_F(AnnotColorTest_754, CMYKConstructorCreatesCMYKColorSpace_754) {
    AnnotColor color(0.1, 0.2, 0.3, 0.4);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorCMYK);
}

// Test CMYK constructor values
TEST_F(AnnotColorTest_754, CMYKConstructorStoresCorrectValues_754) {
    AnnotColor color(0.1, 0.2, 0.3, 0.4);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.1);
    EXPECT_DOUBLE_EQ(values[1], 0.2);
    EXPECT_DOUBLE_EQ(values[2], 0.3);
    EXPECT_DOUBLE_EQ(values[3], 0.4);
}

// Test CMYK constructor with all zeros
TEST_F(AnnotColorTest_754, CMYKConstructorAllZeros_754) {
    AnnotColor color(0.0, 0.0, 0.0, 0.0);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorCMYK);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.0);
    EXPECT_DOUBLE_EQ(values[1], 0.0);
    EXPECT_DOUBLE_EQ(values[2], 0.0);
    EXPECT_DOUBLE_EQ(values[3], 0.0);
}

// Test CMYK constructor with all ones
TEST_F(AnnotColorTest_754, CMYKConstructorAllOnes_754) {
    AnnotColor color(1.0, 1.0, 1.0, 1.0);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorCMYK);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 1.0);
    EXPECT_DOUBLE_EQ(values[1], 1.0);
    EXPECT_DOUBLE_EQ(values[2], 1.0);
    EXPECT_DOUBLE_EQ(values[3], 1.0);
}

// Test getValues returns reference to internal array
TEST_F(AnnotColorTest_754, GetValuesReturnsConsistentReference_754) {
    AnnotColor color(0.5, 0.6, 0.7);
    const auto &values1 = color.getValues();
    const auto &values2 = color.getValues();
    EXPECT_EQ(&values1, &values2);
}

// Test gray value with mid-range
TEST_F(AnnotColorTest_754, GrayMidRange_754) {
    AnnotColor color(0.5);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.5);
}

// Test boundary: RGB with values at extremes
TEST_F(AnnotColorTest_754, RGBBoundaryValues_754) {
    AnnotColor color(0.0, 0.5, 1.0);
    EXPECT_EQ(color.getSpace(), AnnotColor::colorRGB);
    const auto &values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.0);
    EXPECT_DOUBLE_EQ(values[1], 0.5);
    EXPECT_DOUBLE_EQ(values[2], 1.0);
}

// Test that getSpace returns correct enum for each constructor
TEST_F(AnnotColorTest_754, GetSpaceConsistencyAcrossConstructors_754) {
    AnnotColor transparent;
    AnnotColor gray(0.5);
    AnnotColor rgb(0.1, 0.2, 0.3);
    AnnotColor cmyk(0.1, 0.2, 0.3, 0.4);

    // Verify each has a different color space
    EXPECT_NE(transparent.getSpace(), gray.getSpace());
    EXPECT_NE(gray.getSpace(), rgb.getSpace());
    EXPECT_NE(rgb.getSpace(), cmyk.getSpace());
}
