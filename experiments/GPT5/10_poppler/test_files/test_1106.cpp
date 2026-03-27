#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/SplashOutputDev.h"

class SplashOutputDevTest_1106 : public ::testing::Test {
protected:
    SplashOutputDev* splashOutputDev;

    void SetUp() override {
        splashOutputDev = new SplashOutputDev(/* pass necessary constructor parameters */);
    }

    void TearDown() override {
        delete splashOutputDev;
    }
};

// Normal operation tests
TEST_F(SplashOutputDevTest_1106, UseShadedFills_ValidType_ReturnsTrue_1106) {
    EXPECT_TRUE(splashOutputDev->useShadedFills(1));  // Valid type in the range [1, 5]
    EXPECT_TRUE(splashOutputDev->useShadedFills(5));  // Valid type at the upper bound
}

TEST_F(SplashOutputDevTest_1106, UseShadedFills_InvalidType_ReturnsFalse_1106) {
    EXPECT_FALSE(splashOutputDev->useShadedFills(0));  // Type less than 1
    EXPECT_FALSE(splashOutputDev->useShadedFills(6));  // Type greater than 5
}

// Boundary condition tests
TEST_F(SplashOutputDevTest_1106, UseShadedFills_BoundaryValues_ReturnsExpected_1106) {
    EXPECT_TRUE(splashOutputDev->useShadedFills(1));  // Lower boundary valid
    EXPECT_FALSE(splashOutputDev->useShadedFills(0)); // Lower boundary invalid
    EXPECT_TRUE(splashOutputDev->useShadedFills(5));  // Upper boundary valid
    EXPECT_FALSE(splashOutputDev->useShadedFills(6)); // Upper boundary invalid
}

// Exceptional or error cases (edge cases)
TEST_F(SplashOutputDevTest_1106, UseShadedFills_NegativeValue_ReturnsFalse_1106) {
    EXPECT_FALSE(splashOutputDev->useShadedFills(-1));  // Invalid negative type
}

TEST_F(SplashOutputDevTest_1106, UseShadedFills_AboveMaxValue_ReturnsFalse_1106) {
    EXPECT_FALSE(splashOutputDev->useShadedFills(100));  // Excessively large type
}

// Verification of external interactions (if any mockable behavior was involved)
class MockSplashOutputDev : public SplashOutputDev {
public:
    MOCK_METHOD(bool, useShadedFills, (int type), (override));
};

TEST_F(SplashOutputDevTest_1106, UseShadedFills_CallsCorrectMethod_1106) {
    MockSplashOutputDev mockDev;
    EXPECT_CALL(mockDev, useShadedFills(2)).WillOnce(testing::Return(true));
    
    EXPECT_TRUE(mockDev.useShadedFills(2));  // Ensure the mock was called as expected
}