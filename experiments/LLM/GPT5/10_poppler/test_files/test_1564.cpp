#include <gtest/gtest.h>
#include <cmath>  // For fabs

// Mock for the dependencies if needed, based on external collaborators (not required in this case)

class SplashMathTest_1564 : public ::testing::Test {
protected:
    // Setup and tear down methods can be added if needed
    void SetUp() override {
        // Optional setup if needed
    }

    void TearDown() override {
        // Optional cleanup if needed
    }
};

// Test normal operation: the determinant is greater than or equal to epsilon
TEST_F(SplashMathTest_1564, TestSplashCheckDet_EqualToEpsilon_1564) {
    SplashCoord m11 = 3.0, m12 = 1.0, m21 = 1.0, m22 = 2.0, epsilon = 1.0;
    bool result = splashCheckDet(m11, m12, m21, m22, epsilon);
    EXPECT_TRUE(result);  // The determinant is >= epsilon (fabs(3.0 * 2.0 - 1.0 * 1.0) = 5.0, which is >= 1.0)
}

// Test normal operation: the determinant is less than epsilon
TEST_F(SplashMathTest_1564, TestSplashCheckDet_LessThanEpsilon_1564) {
    SplashCoord m11 = 1.0, m12 = 0.0, m21 = 0.0, m22 = 1.0, epsilon = 2.0;
    bool result = splashCheckDet(m11, m12, m21, m22, epsilon);
    EXPECT_FALSE(result);  // The determinant is fabs(1.0 * 1.0 - 0.0 * 0.0) = 1.0, which is less than 2.0
}

// Test boundary condition: determinant exactly equals epsilon
TEST_F(SplashMathTest_1564, TestSplashCheckDet_ExactMatchEpsilon_1564) {
    SplashCoord m11 = 1.0, m12 = 1.0, m21 = 1.0, m22 = 2.0, epsilon = 1.0;
    bool result = splashCheckDet(m11, m12, m21, m22, epsilon);
    EXPECT_TRUE(result);  // The determinant is fabs(1.0 * 2.0 - 1.0 * 1.0) = 1.0, which is exactly 1.0 (epsilon)
}

// Test exceptional case: determinant equals zero (should be handled by function)
TEST_F(SplashMathTest_1564, TestSplashCheckDet_ZeroDeterminant_1564) {
    SplashCoord m11 = 0.0, m12 = 0.0, m21 = 0.0, m22 = 0.0, epsilon = 1.0;
    bool result = splashCheckDet(m11, m12, m21, m22, epsilon);
    EXPECT_FALSE(result);  // The determinant is fabs(0.0 * 0.0 - 0.0 * 0.0) = 0.0, which is less than 1.0
}

// Test boundary case: very small epsilon
TEST_F(SplashMathTest_1564, TestSplashCheckDet_SmallEpsilon_1564) {
    SplashCoord m11 = 10.0, m12 = 5.0, m21 = 1.0, m22 = 2.0, epsilon = 0.00001;
    bool result = splashCheckDet(m11, m12, m21, m22, epsilon);
    EXPECT_TRUE(result);  // The determinant is fabs(10.0 * 2.0 - 5.0 * 1.0) = 15.0, which is greater than 0.00001
}