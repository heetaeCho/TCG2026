#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h" // Include the class header file

// Test suite for GfxState
class GfxStateTest : public ::testing::Test {
protected:
    // Initialize GfxState instance before each test
    GfxStateTest() : gfxState(72.0, 72.0, nullptr, 0, false) {}

    GfxState gfxState;  // Instance of GfxState for testing
};

// Test for the setStrokeOpacity method
TEST_F(GfxStateTest, SetStrokeOpacity_Normal_634) {
    double opacity = 0.5;

    // Call the method to set the stroke opacity
    gfxState.setStrokeOpacity(opacity);

    // Verify that the opacity is set correctly
    EXPECT_DOUBLE_EQ(gfxState.getStrokeOpacity(), opacity);
}

// Test for boundary conditions with the setStrokeOpacity method
TEST_F(GfxStateTest, SetStrokeOpacity_Boundary_635) {
    // Test boundary values for opacity
    gfxState.setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(gfxState.getStrokeOpacity(), 0.0);

    gfxState.setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(gfxState.getStrokeOpacity(), 1.0);
}

// Test for exceptional case where invalid opacity is provided
TEST_F(GfxStateTest, SetStrokeOpacity_Invalid_636) {
    // Test setting an invalid opacity value (negative)
    gfxState.setStrokeOpacity(-0.5);
    EXPECT_DOUBLE_EQ(gfxState.getStrokeOpacity(), -0.5);  // Assuming no internal validation

    // Test setting an invalid opacity value (greater than 1)
    gfxState.setStrokeOpacity(1.5);
    EXPECT_DOUBLE_EQ(gfxState.getStrokeOpacity(), 1.5);  // Assuming no internal validation
}

// Test for the setLineDash method with normal behavior
TEST_F(GfxStateTest, SetLineDash_Normal_637) {
    std::vector<double> dashPattern = {1.0, 2.0, 3.0};
    double start = 0.0;

    gfxState.setLineDash(std::move(dashPattern), start);

    std::vector<double> returnedPattern = gfxState.getLineDash(nullptr);
    EXPECT_EQ(returnedPattern, std::vector<double>({1.0, 2.0, 3.0}));
}

// Test for boundary conditions with the setLineDash method
TEST_F(GfxStateTest, SetLineDash_EmptyPattern_638) {
    std::vector<double> emptyPattern;
    double start = 0.0;

    gfxState.setLineDash(std::move(emptyPattern), start);

    std::vector<double> returnedPattern = gfxState.getLineDash(nullptr);
    EXPECT_TRUE(returnedPattern.empty());
}

// Test for exceptional case with an invalid line dash pattern
TEST_F(GfxStateTest, SetLineDash_InvalidPattern_639) {
    std::vector<double> invalidPattern = {-1.0, -2.0};
    double start = -1.0;

    gfxState.setLineDash(std::move(invalidPattern), start);

    std::vector<double> returnedPattern = gfxState.getLineDash(nullptr);
    EXPECT_EQ(returnedPattern, std::vector<double>({-1.0, -2.0}));
}

// Test for the setFillOpacity method
TEST_F(GfxStateTest, SetFillOpacity_Normal_640) {
    double opacity = 0.75;

    gfxState.setFillOpacity(opacity);

    EXPECT_DOUBLE_EQ(gfxState.getFillOpacity(), opacity);
}

// Test for boundary conditions with the setFillOpacity method
TEST_F(GfxStateTest, SetFillOpacity_Boundary_641) {
    gfxState.setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(gfxState.getFillOpacity(), 0.0);

    gfxState.setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(gfxState.getFillOpacity(), 1.0);
}

// Test for the setFillColor method with a color value
TEST_F(GfxStateTest, SetFillColor_Normal_642) {
    GfxColor color = {0.5, 0.5, 0.5}; // Gray color

    gfxState.setFillColor(&color);

    const GfxColor* returnedColor = gfxState.getFillColor();
    EXPECT_EQ(returnedColor->r, color.r);
    EXPECT_EQ(returnedColor->g, color.g);
    EXPECT_EQ(returnedColor->b, color.b);
}

// Test for exceptional case with null pointer for color
TEST_F(GfxStateTest, SetFillColor_NullPointer_643) {
    gfxState.setFillColor(nullptr);

    const GfxColor* returnedColor = gfxState.getFillColor();
    EXPECT_EQ(returnedColor, nullptr);
}