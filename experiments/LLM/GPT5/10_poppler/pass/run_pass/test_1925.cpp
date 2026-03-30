#include <gtest/gtest.h>

// The partial function definition
static int luminocity(uint32_t x) { 
    int r = (x >> 16) & 0xff; 
    int g = (x >> 8) & 0xff; 
    int b = (x >> 0) & 0xff; 
    int y = (r * 19661 + g * 38666 + b * 7209 + 32829) >> 16; 
    return y; 
}

// Test fixture
class LuminocityTest_1925 : public ::testing::Test {
protected:
    // Any setup code goes here
    void SetUp() override {
        // Initialize necessary data for the tests if needed
    }
    
    // Any teardown code goes here
    void TearDown() override {
        // Clean up
    }
};

// Test Case 1: Normal Operation - Testing with a common color (e.g., white).
TEST_F(LuminocityTest_1925, LuminocityForWhiteColor_1925) {
    uint32_t white = 0xFFFFFF; // RGB(255, 255, 255)
    int result = luminocity(white);
    EXPECT_EQ(result, 255) << "Luminocity of white should be 255.";
}

// Test Case 2: Normal Operation - Testing with a black color.
TEST_F(LuminocityTest_1925, LuminocityForBlackColor_1925) {
    uint32_t black = 0x000000; // RGB(0, 0, 0)
    int result = luminocity(black);
    EXPECT_EQ(result, 0) << "Luminocity of black should be 0.";
}

// Test Case 3: Normal Operation - Testing with a mid-range color (e.g., grey).
TEST_F(LuminocityTest_1925, LuminocityForGreyColor_1925) {
    uint32_t grey = 0x808080; // RGB(128, 128, 128)
    int result = luminocity(grey);
    EXPECT_EQ(result, 128) << "Luminocity of grey should be 128.";
}

// Test Case 4: Boundary condition - Test with minimum non-zero RGB value.
TEST_F(LuminocityTest_1925, LuminocityForMinimumNonZeroRGB_1925) {
    uint32_t minNonZero = 0x000001; // RGB(0, 0, 1)
    int result = luminocity(minNonZero);
    EXPECT_GT(result, 0) << "Luminocity of minimum non-zero color should be greater than 0.";
}

// Test Case 5: Boundary condition - Test with maximum RGB value (full saturation).
TEST_F(LuminocityTest_1925, LuminocityForMaximumRGB_1925) {
    uint32_t maxRGB = 0xFFFFFF; // RGB(255, 255, 255)
    int result = luminocity(maxRGB);
    EXPECT_EQ(result, 255) << "Luminocity for full saturation RGB should be 255.";
}

// Test Case 6: Exceptional case - Testing with an arbitrary RGB value.
TEST_F(LuminocityTest_1925, LuminocityForArbitraryColor_1925) {
    uint32_t arbitrary = 0xAABBCC; // RGB(170, 187, 204)
    int result = luminocity(arbitrary);
    EXPECT_NE(result, 0) << "Luminocity for arbitrary color should not be zero.";
}

// Test Case 7: Verification of external interactions (if applicable).
TEST_F(LuminocityTest_1925, LuminocityFunctionCallVerification_1925) {
    // If the function were interacting with an external mockable service, you'd mock it and verify the interactions.
    // However, luminocity does not have external interactions, so this test case may not be applicable.
}