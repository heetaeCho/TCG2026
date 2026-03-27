#include <gtest/gtest.h>
#include <memory>
#include <array>
#include "GfxState.h"  // Include the header for GfxState

class GfxStateTest_649 : public ::testing::Test {
protected:
    // Test setup code (if any) goes here. For now, we're focusing on individual test cases.

    GfxStateTest_649() = default;

    ~GfxStateTest_649() override = default;
};

// Normal Operation Test
TEST_F(GfxStateTest_649, SetHorizScaling_NormalValue_649) {
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    double scale = 100.0;
    gfxState.setHorizScaling(scale);
    
    // Test that the horizScaling is correctly set (should be scale * 0.01)
    EXPECT_DOUBLE_EQ(gfxState.getHorizScaling(), 1.0);
}

// Boundary Test 1: Scaling with zero value
TEST_F(GfxStateTest_649, SetHorizScaling_ZeroValue_649) {
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    double scale = 0.0;
    gfxState.setHorizScaling(scale);
    
    // Test that the horizScaling is correctly set (should be 0.0)
    EXPECT_DOUBLE_EQ(gfxState.getHorizScaling(), 0.0);
}

// Boundary Test 2: Scaling with negative value
TEST_F(GfxStateTest_649, SetHorizScaling_NegativeValue_649) {
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    double scale = -100.0;
    gfxState.setHorizScaling(scale);
    
    // Test that the horizScaling is correctly set (should be -1.0)
    EXPECT_DOUBLE_EQ(gfxState.getHorizScaling(), -1.0);
}

// Exceptional Case: Handle an excessively large scaling factor
TEST_F(GfxStateTest_649, SetHorizScaling_LargeValue_649) {
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    double scale = 1e6;  // A very large scaling factor
    gfxState.setHorizScaling(scale);
    
    // Test that the horizScaling is correctly set (should be 10000.0)
    EXPECT_DOUBLE_EQ(gfxState.getHorizScaling(), 10000.0);
}

// Exceptional Case: Handle a very small scaling factor (near zero but positive)
TEST_F(GfxStateTest_649, SetHorizScaling_SmallValue_649) {
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);
    double scale = 0.001;
    gfxState.setHorizScaling(scale);
    
    // Test that the horizScaling is correctly set (should be 0.00001)
    EXPECT_DOUBLE_EQ(gfxState.getHorizScaling(), 0.00001);
}