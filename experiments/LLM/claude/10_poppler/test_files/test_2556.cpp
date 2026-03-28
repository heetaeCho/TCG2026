#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Poppler includes
#include "Object.h"
#include "Array.h"
#include "poppler-page.h"

// We need to access the convert_color function. Since it's static inline in the .cc file,
// we include it or declare it. We'll include the relevant portion.
// Since convert_color is static inline, we replicate the declaration for testing.
#include "poppler-structure-element.cc"

class ConvertColorTest_2556 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create an Object array with 3 doubles
    Object makeColorArray(double r, double g, double b) {
        Array *arr = new Array(nullptr);
        arr->add(Object(r));
        arr->add(Object(g));
        arr->add(Object(b));
        return Object(arr);
    }
};

// Test normal color conversion with typical values
TEST_F(ConvertColorTest_2556, NormalColorConversion_2556) {
    Object obj = makeColorArray(1.0, 0.5, 0.0);
    PopplerColor color;
    convert_color(&obj, &color);

    EXPECT_EQ(color.red, static_cast<int>(1.0 * 65535));
    EXPECT_EQ(color.green, static_cast<int>(0.5 * 65535));
    EXPECT_EQ(color.blue, static_cast<int>(0.0 * 65535));
}

// Test with all zeros (black)
TEST_F(ConvertColorTest_2556, BlackColor_2556) {
    Object obj = makeColorArray(0.0, 0.0, 0.0);
    PopplerColor color;
    convert_color(&obj, &color);

    EXPECT_EQ(color.red, 0);
    EXPECT_EQ(color.green, 0);
    EXPECT_EQ(color.blue, 0);
}

// Test with all ones (white)
TEST_F(ConvertColorTest_2556, WhiteColor_2556) {
    Object obj = makeColorArray(1.0, 1.0, 1.0);
    PopplerColor color;
    convert_color(&obj, &color);

    EXPECT_EQ(color.red, 65535);
    EXPECT_EQ(color.green, 65535);
    EXPECT_EQ(color.blue, 65535);
}

// Test with fractional values
TEST_F(ConvertColorTest_2556, FractionalValues_2556) {
    Object obj = makeColorArray(0.25, 0.75, 0.1);
    PopplerColor color;
    convert_color(&obj, &color);

    EXPECT_EQ(color.red, static_cast<int>(0.25 * 65535));
    EXPECT_EQ(color.green, static_cast<int>(0.75 * 65535));
    EXPECT_EQ(color.blue, static_cast<int>(0.1 * 65535));
}

// Test with pure red
TEST_F(ConvertColorTest_2556, PureRed_2556) {
    Object obj = makeColorArray(1.0, 0.0, 0.0);
    PopplerColor color;
    convert_color(&obj, &color);

    EXPECT_EQ(color.red, 65535);
    EXPECT_EQ(color.green, 0);
    EXPECT_EQ(color.blue, 0);
}

// Test with pure green
TEST_F(ConvertColorTest_2556, PureGreen_2556) {
    Object obj = makeColorArray(0.0, 1.0, 0.0);
    PopplerColor color;
    convert_color(&obj, &color);

    EXPECT_EQ(color.red, 0);
    EXPECT_EQ(color.green, 65535);
    EXPECT_EQ(color.blue, 0);
}

// Test with pure blue
TEST_F(ConvertColorTest_2556, PureBlue_2556) {
    Object obj = makeColorArray(0.0, 0.0, 1.0);
    PopplerColor color;
    convert_color(&obj, &color);

    EXPECT_EQ(color.red, 0);
    EXPECT_EQ(color.green, 0);
    EXPECT_EQ(color.blue, 65535);
}

// Test with very small values near zero
TEST_F(ConvertColorTest_2556, SmallValues_2556) {
    Object obj = makeColorArray(0.001, 0.002, 0.003);
    PopplerColor color;
    convert_color(&obj, &color);

    EXPECT_EQ(color.red, static_cast<int>(0.001 * 65535));
    EXPECT_EQ(color.green, static_cast<int>(0.002 * 65535));
    EXPECT_EQ(color.blue, static_cast<int>(0.003 * 65535));
}

// Test with mid-range gray
TEST_F(ConvertColorTest_2556, MidGray_2556) {
    Object obj = makeColorArray(0.5, 0.5, 0.5);
    PopplerColor color;
    convert_color(&obj, &color);

    int expected = static_cast<int>(0.5 * 65535);
    EXPECT_EQ(color.red, expected);
    EXPECT_EQ(color.green, expected);
    EXPECT_EQ(color.blue, expected);
}

// Test that null color pointer triggers assertion (death test)
TEST_F(ConvertColorTest_2556, NullColorDeath_2556) {
    Object obj = makeColorArray(1.0, 0.0, 0.0);
    EXPECT_DEATH(convert_color(&obj, nullptr), "");
}
