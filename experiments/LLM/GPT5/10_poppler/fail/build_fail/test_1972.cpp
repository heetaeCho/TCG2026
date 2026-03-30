#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"  // Include the header file for GfxFontCIDWidthExcepV

// Unit tests for cmpWidthExcepVFunctor
class GfxFontTest_1972 : public ::testing::Test {
protected:
    // Any necessary setup or teardown can be done here
    // This is an empty placeholder as no class state is required
};

// Test normal operation of cmpWidthExcepVFunctor
TEST_F(GfxFontTest_1972, CompareWidthExcepV_1972) {
    // Arrange
    GfxFontCIDWidthExcepV w1{10.0, 0.0, 0.0};  // height = 10.0, vx = 0.0, vy = 0.0
    GfxFontCIDWidthExcepV w2{20.0, 0.0, 0.0};  // height = 20.0, vx = 0.0, vy = 0.0

    cmpWidthExcepVFunctor comparator;

    // Act & Assert
    EXPECT_TRUE(comparator(w1, w2));  // w1.first (10.0) < w2.first (20.0), so the comparison should return true
}

// Test boundary condition when comparing two objects with the same value
TEST_F(GfxFontTest_1972, CompareWidthExcepV_SameValues_1972) {
    // Arrange
    GfxFontCIDWidthExcepV w1{10.0, 0.0, 0.0};  // height = 10.0, vx = 0.0, vy = 0.0
    GfxFontCIDWidthExcepV w2{10.0, 0.0, 0.0};  // height = 10.0, vx = 0.0, vy = 0.0

    cmpWidthExcepVFunctor comparator;

    // Act & Assert
    EXPECT_FALSE(comparator(w1, w2));  // Since both heights are equal, the comparison should return false
}

// Test exceptional case: handle invalid comparison (although not explicitly requested, this is an example)
TEST_F(GfxFontTest_1972, CompareWidthExcepV_InvalidComparison_1972) {
    // Arrange
    GfxFontCIDWidthExcepV w1{10.0, 0.0, 0.0};  // height = 10.0, vx = 0.0, vy = 0.0
    GfxFontCIDWidthExcepV w2{0.0, 0.0, 0.0};   // height = 0.0, vx = 0.0, vy = 0.0

    cmpWidthExcepVFunctor comparator;

    // Act & Assert
    EXPECT_TRUE(comparator(w2, w1));  // w2.first (0.0) < w1.first (10.0), so the comparison should return true
}