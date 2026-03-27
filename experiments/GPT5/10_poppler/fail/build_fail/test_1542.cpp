#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/splash/SplashState.h"

// Test for setStrokeOverprint function in SplashState class
class SplashStateTest_1542 : public ::testing::Test {
protected:
    SplashStateTest_1542() : splashState(100, 100, true, nullptr) {}

    SplashState splashState;
};

// Normal operation test for setStrokeOverprint
TEST_F(SplashStateTest_1542, setStrokeOverprint_NormalOperation_1542) {
    // Arrange
    bool strokeOverprintValue = true;

    // Act
    splashState.setStrokeOverprint(strokeOverprintValue);

    // Assert
    // We cannot directly assert internal state, but we assume that any function that calls setStrokeOverprint
    // will modify some observable state or trigger some observable behavior.
    // The test passes if no crashes or errors occur.
    SUCCEED();
}

// Boundary condition test for setStrokeOverprint
TEST_F(SplashStateTest_1542, setStrokeOverprint_BoundaryConditions_1542) {
    // Act & Assert
    EXPECT_NO_FATAL_FAILURE(splashState.setStrokeOverprint(true));
    EXPECT_NO_FATAL_FAILURE(splashState.setStrokeOverprint(false));
}

// Exceptional case: check for possible errors when invoking setStrokeOverprint with unusual values
TEST_F(SplashStateTest_1542, setStrokeOverprint_ExceptionalCase_1542) {
    // Normally, this function takes a bool, but in this case, we test the behavior
    // of the class with different edge scenarios in a black-box fashion.

    // The test passes as long as the function doesn't crash or throw exceptions.
    EXPECT_NO_THROW(splashState.setStrokeOverprint(true));
    EXPECT_NO_THROW(splashState.setStrokeOverprint(false));
}