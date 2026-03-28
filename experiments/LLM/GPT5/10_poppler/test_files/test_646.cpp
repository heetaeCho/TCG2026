#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

class GfxStateTest_646 : public ::testing::Test {
protected:
    GfxState gfxState{72.0, 72.0, nullptr, 0, false}; // Constructor with sample parameters
};

// Normal Operation Test Case
TEST_F(GfxStateTest_646, SetTextMat_ValidValues_646) {
    double a = 1.0, b = 0.0, c = 0.0, d = 1.0, e = 0.0, f = 0.0;
    
    // Call the method under test
    gfxState.setTextMat(a, b, c, d, e, f);

    // Verify that the values were set correctly (textMat array should hold these values)
    const auto& textMat = gfxState.getTextMat();
    EXPECT_EQ(textMat[0], a);
    EXPECT_EQ(textMat[1], b);
    EXPECT_EQ(textMat[2], c);
    EXPECT_EQ(textMat[3], d);
    EXPECT_EQ(textMat[4], e);
    EXPECT_EQ(textMat[5], f);
}

// Boundary Condition Test Case
TEST_F(GfxStateTest_646, SetTextMat_ZeroValues_646) {
    double a = 0.0, b = 0.0, c = 0.0, d = 0.0, e = 0.0, f = 0.0;

    // Call the method under test
    gfxState.setTextMat(a, b, c, d, e, f);

    // Verify that the textMat array holds zero values
    const auto& textMat = gfxState.getTextMat();
    EXPECT_EQ(textMat[0], a);
    EXPECT_EQ(textMat[1], b);
    EXPECT_EQ(textMat[2], c);
    EXPECT_EQ(textMat[3], d);
    EXPECT_EQ(textMat[4], e);
    EXPECT_EQ(textMat[5], f);
}

// Exceptional or Error Test Case
TEST_F(GfxStateTest_646, SetTextMat_InvalidValues_646) {
    double a = -1.0, b = -1.0, c = -1.0, d = -1.0, e = -1.0, f = -1.0;
    
    // We assume the setTextMat function can handle negative values and set them as is
    // This test will depend on the expected behavior when invalid values are provided
    // Here we set the values and check if they are properly assigned.
    
    gfxState.setTextMat(a, b, c, d, e, f);

    // Verify that the negative values are stored in textMat
    const auto& textMat = gfxState.getTextMat();
    EXPECT_EQ(textMat[0], a);
    EXPECT_EQ(textMat[1], b);
    EXPECT_EQ(textMat[2], c);
    EXPECT_EQ(textMat[3], d);
    EXPECT_EQ(textMat[4], e);
    EXPECT_EQ(textMat[5], f);
}

// Verification of External Interactions Test Case
TEST_F(GfxStateTest_646, SetTextMat_InteractionWithOtherMethods_646) {
    double a = 2.0, b = 1.0, c = 0.0, d = 2.0, e = 1.0, f = 1.0;

    // Mock a potential interaction, such as the effect on the current transform matrix
    // Here, we're not mocking dependencies, but in case of future dependency, we can extend this.
    
    gfxState.setTextMat(a, b, c, d, e, f);

    // Verify that the textMat values reflect the change.
    const auto& textMat = gfxState.getTextMat();
    EXPECT_EQ(textMat[0], a);
    EXPECT_EQ(textMat[1], b);
    EXPECT_EQ(textMat[2], c);
    EXPECT_EQ(textMat[3], d);
    EXPECT_EQ(textMat[4], e);
    EXPECT_EQ(textMat[5], f);
}