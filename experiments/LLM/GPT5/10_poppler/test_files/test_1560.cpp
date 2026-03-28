#include <gtest/gtest.h>
#include "./TestProjects/poppler/splash/SplashMath.h"

// Test class to group related test cases
class SplashMathTest_1560 : public ::testing::Test {
protected:
    // Set-up code (if needed) goes here
    void SetUp() override {}
    
    // Tear-down code (if needed) goes here
    void TearDown() override {}
};

// Normal operation test case
TEST_F(SplashMathTest_1560, splashAvg_NormalOperation_1560) {
    // Test the splashAvg function with positive integers
    SplashCoord x = 2;
    SplashCoord y = 4;
    SplashCoord result = splashAvg(x, y);
    
    // Verify the result
    EXPECT_DOUBLE_EQ(result, 3.0);  // 0.5 * (2 + 4) = 3
}

// Test with negative values
TEST_F(SplashMathTest_1560, splashAvg_NegativeValues_1560) {
    // Test with negative values
    SplashCoord x = -2;
    SplashCoord y = -4;
    SplashCoord result = splashAvg(x, y);
    
    // Verify the result
    EXPECT_DOUBLE_EQ(result, -3.0);  // 0.5 * (-2 + -4) = -3
}

// Boundary test case with zero values
TEST_F(SplashMathTest_1560, splashAvg_ZeroValues_1560) {
    // Test with zero values
    SplashCoord x = 0;
    SplashCoord y = 0;
    SplashCoord result = splashAvg(x, y);
    
    // Verify the result
    EXPECT_DOUBLE_EQ(result, 0.0);  // 0.5 * (0 + 0) = 0
}

// Boundary test case with large values
TEST_F(SplashMathTest_1560, splashAvg_LargeValues_1560) {
    // Test with large values
    SplashCoord x = 1e6;
    SplashCoord y = 2e6;
    SplashCoord result = splashAvg(x, y);
    
    // Verify the result
    EXPECT_DOUBLE_EQ(result, 1.5e6);  // 0.5 * (1e6 + 2e6) = 1.5e6
}

// Test for exceptional behavior (though no exceptional cases are defined here)
TEST_F(SplashMathTest_1560, splashAvg_ExceptionalCase_1560) {
    // Since splashAvg is simple, there's no defined exception case.
    // But we can assert that it doesn't throw any exceptions.
    SplashCoord x = 2;
    SplashCoord y = 4;
    
    EXPECT_NO_THROW({
        splashAvg(x, y);
    });
}