#include <gtest/gtest.h>



// Mocking external collaborators if needed would go here.

// However, for this specific function, there are no dependencies.



// The function to test is defined as:

// static inline unsigned char splashBGR8R(SplashColorPtr bgr8) { return bgr8[2]; }



// Define a test fixture class if necessary. For this simple function, it's not needed,

// but we will define one for consistency and potential future extensions.

class SplashTypesTest_1036 : public ::testing::Test {

protected:

    // No need to set up or tear down anything for this simple function.

};



TEST_F(SplashTypesTest_1036, ReturnsCorrectRedValueForValidInput_1036) {

    unsigned char bgr8[] = {0x11, 0x22, 0x33}; // Example BGR values

    EXPECT_EQ(splashBGR8R(bgr8), 0x33);

}



TEST_F(SplashTypesTest_1036, ReturnsZeroForNullInput_1036) {

    unsigned char* bgr8 = nullptr;

    EXPECT_DEATH(splashBGR8R(bgr8), ".*"); // Assuming dereferencing null is undefined and will cause a crash

}



TEST_F(SplashTypesTest_1036, ReturnsCorrectRedValueForBoundaryValues_1036) {

    unsigned char bgr8_min[] = {0x00, 0x00, 0x00}; // Minimum BGR values

    unsigned char bgr8_max[] = {0xFF, 0xFF, 0xFF}; // Maximum BGR values



    EXPECT_EQ(splashBGR8R(bgr8_min), 0x00);

    EXPECT_EQ(splashBGR8R(bgr8_max), 0xFF);

}



TEST_F(SplashTypesTest_1036, ReturnsCorrectRedValueForVariousInputs_1036) {

    unsigned char bgr8_a[] = {0xAA, 0xBB, 0xCC}; // Arbitrary BGR values

    unsigned char bgr8_b[] = {0x12, 0x34, 0x56};

    unsigned char bgr8_c[] = {0xF1, 0xF2, 0xF3};



    EXPECT_EQ(splashBGR8R(bgr8_a), 0xCC);

    EXPECT_EQ(splashBGR8R(bgr8_b), 0x56);

    EXPECT_EQ(splashBGR8R(bgr8_c), 0xF3);

}
