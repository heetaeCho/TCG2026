#include <gtest/gtest.h>
#include "GfxState.h"

// TEST_ID: 616
// Test normal operation of getCurX
TEST_F(GfxStateTest_616, GetCurX_ReturnsCorrectValue_616) {
    // Arrange
    GfxState gfxState(300.0, 300.0, nullptr, 0, false);
    
    // Act
    double result = gfxState.getCurX();
    
    // Assert
    EXPECT_EQ(result, 0.0);  // assuming the default value of curX is 0.0
}

// TEST_ID: 617
// Test normal operation of getCurX after modification
TEST_F(GfxStateTest_617, GetCurX_AfterSet_ReturnsModifiedValue_617) {
    // Arrange
    GfxState gfxState(300.0, 300.0, nullptr, 0, false);
    // Using a setter or direct modification to set curX
    gfxState.moveTo(100.0, 150.0);  // Assuming moveTo modifies curX and curY
    
    // Act
    double result = gfxState.getCurX();
    
    // Assert
    EXPECT_EQ(result, 100.0);  // assuming moveTo sets curX to 100.0
}

// TEST_ID: 618
// Test boundary condition where curX is negative
TEST_F(GfxStateTest_618, GetCurX_NegativeValue_618) {
    // Arrange
    GfxState gfxState(300.0, 300.0, nullptr, 0, false);
    gfxState.moveTo(-100.0, 150.0);  // Moving to negative x coordinate
    
    // Act
    double result = gfxState.getCurX();
    
    // Assert
    EXPECT_EQ(result, -100.0);  // Verifying negative x value is properly handled
}

// TEST_ID: 619
// Test boundary condition where curX is a very large number
TEST_F(GfxStateTest_619, GetCurX_LargeValue_619) {
    // Arrange
    GfxState gfxState(300.0, 300.0, nullptr, 0, false);
    double largeX = 1e6;  // large value for curX
    gfxState.moveTo(largeX, 150.0);
    
    // Act
    double result = gfxState.getCurX();
    
    // Assert
    EXPECT_EQ(result, largeX);  // Verifying large value is handled correctly
}

// TEST_ID: 620
// Test exceptional case where curX is set to NaN (Not-a-Number)
TEST_F(GfxStateTest_620, GetCurX_NaNValue_620) {
    // Arrange
    GfxState gfxState(300.0, 300.0, nullptr, 0, false);
    double nanValue = std::nan("1");  // NaN value
    gfxState.moveTo(nanValue, 150.0);
    
    // Act
    double result = gfxState.getCurX();
    
    // Assert
    EXPECT_TRUE(std::isnan(result));  // Verifying that NaN is returned
}

// TEST_ID: 621
// Test boundary condition for curX at extreme value
TEST_F(GfxStateTest_621, GetCurX_ZeroValue_621) {
    // Arrange
    GfxState gfxState(300.0, 300.0, nullptr, 0, false);
    gfxState.moveTo(0.0, 0.0);  // Moving to origin
    
    // Act
    double result = gfxState.getCurX();
    
    // Assert
    EXPECT_EQ(result, 0.0);  // Verifying the value is correctly set to 0
}