#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>

class GfxStateTest_628 : public testing::Test {
protected:
    GfxStateTest_628() : gfxState(/* parameters for GfxState constructor */) {}
    GfxState gfxState;  // Assuming constructor takes parameters as defined in the class.
};

// Test for normal operation of textTransformDelta method
TEST_F(GfxStateTest_628, TextTransformDelta_NormalOperation_628) {
    // Test data
    double x1 = 10.0;
    double y1 = 20.0;
    double x2 = 0.0;
    double y2 = 0.0;
    
    // Call the function under test
    gfxState.textTransformDelta(x1, y1, &x2, &y2);
    
    // Verify the result (expected transformation based on textMat)
    // Assuming textMat is defined as part of the object, use the known matrix for testing.
    // Here we assume the transformation matrix [a, b, c, d, e, f] as an example.
    double expectedX = /* expected transformed X */;
    double expectedY = /* expected transformed Y */;
    
    EXPECT_DOUBLE_EQ(x2, expectedX);
    EXPECT_DOUBLE_EQ(y2, expectedY);
}

// Test for boundary condition: textTransformDelta with zero input
TEST_F(GfxStateTest_628, TextTransformDelta_ZeroInput_628) {
    double x1 = 0.0;
    double y1 = 0.0;
    double x2 = 0.0;
    double y2 = 0.0;
    
    gfxState.textTransformDelta(x1, y1, &x2, &y2);
    
    double expectedX = /* expected transformed X for 0,0 */;
    double expectedY = /* expected transformed Y for 0,0 */;
    
    EXPECT_DOUBLE_EQ(x2, expectedX);
    EXPECT_DOUBLE_EQ(y2, expectedY);
}

// Test for exceptional case: null pointers for output parameters
TEST_F(GfxStateTest_628, TextTransformDelta_NullPointer_628) {
    double x1 = 1.0;
    double y1 = 2.0;
    
    // Test that the function throws an exception or handles null pointer gracefully
    EXPECT_THROW(gfxState.textTransformDelta(x1, y1, nullptr, nullptr), std::invalid_argument);
}

// Test for normal operation of textTransform method
TEST_F(GfxStateTest_628, TextTransform_NormalOperation_628) {
    double x1 = 15.0;
    double y1 = 25.0;
    double x2 = 0.0;
    double y2 = 0.0;
    
    gfxState.textTransform(x1, y1, &x2, &y2);
    
    double expectedX = /* expected transformed X */;
    double expectedY = /* expected transformed Y */;
    
    EXPECT_DOUBLE_EQ(x2, expectedX);
    EXPECT_DOUBLE_EQ(y2, expectedY);
}

// Test for boundary condition: textTransform with zero input
TEST_F(GfxStateTest_628, TextTransform_ZeroInput_628) {
    double x1 = 0.0;
    double y1 = 0.0;
    double x2 = 0.0;
    double y2 = 0.0;
    
    gfxState.textTransform(x1, y1, &x2, &y2);
    
    double expectedX = /* expected transformed X for 0,0 */;
    double expectedY = /* expected transformed Y for 0,0 */;
    
    EXPECT_DOUBLE_EQ(x2, expectedX);
    EXPECT_DOUBLE_EQ(y2, expectedY);
}

// Test for exceptional case: null pointers for output parameters in textTransform
TEST_F(GfxStateTest_628, TextTransform_NullPointer_628) {
    double x1 = 1.0;
    double y1 = 2.0;
    
    // Test that the function throws an exception or handles null pointer gracefully
    EXPECT_THROW(gfxState.textTransform(x1, y1, nullptr, nullptr), std::invalid_argument);
}