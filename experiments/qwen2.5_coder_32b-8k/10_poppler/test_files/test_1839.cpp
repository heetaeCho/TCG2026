#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/JBIG2Stream.cc"



// Test fixture for JBIG2Stream tests with TEST_ID 1839

class JBIG2StreamTest_1839 : public ::testing::Test {

protected:

    // Additional setup if necessary can be done here

};



// Test case to verify normal operation of isPixelOutsideAdaptiveField within the adaptive field

TEST_F(JBIG2StreamTest_1839, PixelInsideAdaptiveField_1839) {

    EXPECT_FALSE(isPixelOutsideAdaptiveField(0, 0));

    EXPECT_FALSE(isPixelOutsideAdaptiveField(-127, -1));

    EXPECT_FALSE(isPixelOutsideAdaptiveField(127, -1));

}



// Test case to verify normal operation of isPixelOutsideAdaptiveField outside the adaptive field

TEST_F(JBIG2StreamTest_1839, PixelOutsideAdaptiveField_1839) {

    EXPECT_TRUE(isPixelOutsideAdaptiveField(-129, 0)); // x < -128

    EXPECT_TRUE(isPixelOutsideAdaptiveField(128, 0));   // x > 127 when y == 0

    EXPECT_TRUE(isPixelOutsideAdaptiveField(128, -1));  // x > 127 when y < 0

    EXPECT_TRUE(isPixelOutsideAdaptiveField(0, 1));     // y > 0

    EXPECT_TRUE(isPixelOutsideAdaptiveField(-129, -1)); // x < -128 and y < 0

}



// Test case to verify boundary conditions of isPixelOutsideAdaptiveField

TEST_F(JBIG2StreamTest_1839, BoundaryConditionsAdaptiveField_1839) {

    EXPECT_FALSE(isPixelOutsideAdaptiveField(-128, -1)); // x == -128 and y < 0

    EXPECT_TRUE(isPixelOutsideAdaptiveField(-128, 0));   // x == -128 and y == 0

    EXPECT_FALSE(isPixelOutsideAdaptiveField(127, -1));   // x == 127 and y < 0

    EXPECT_TRUE(isPixelOutsideAdaptiveField(126, 0));    // x == 126 and y == 0

}



// Test case to verify exceptional or error cases (if any) of isPixelOutsideAdaptiveField

TEST_F(JBIG2StreamTest_1839, ExceptionalCasesAdaptiveField_1839) {

    // No exceptional cases expected for this function as it only checks boundaries.

}
