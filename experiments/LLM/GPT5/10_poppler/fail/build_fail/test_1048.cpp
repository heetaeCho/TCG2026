#include <gtest/gtest.h>

// Mocking the SplashColorConstPtr for test purposes
typedef int SplashColorConstPtr[SPOT_NCOMPS + 4];

class SplashTypesTest_1048 : public ::testing::Test {
protected:
    // Helper function to initialize SplashColorConstPtr with specific values
    void initializeColor(SplashColorConstPtr color, const int values[SPOT_NCOMPS + 4]) {
        for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
            color[i] = values[i];
        }
    }
};

// Normal operation test: testing splashColorEqual when both colors are identical
TEST_F(SplashTypesTest_1048, splashColorEqual_IdenticalColors_1048) {
    SplashColorConstPtr color1;
    SplashColorConstPtr color2;
    int values[SPOT_NCOMPS + 4] = {1, 2, 3, 4};  // Example values for the color

    initializeColor(color1, values);
    initializeColor(color2, values);

    EXPECT_TRUE(splashColorEqual(color1, color2));
}

// Normal operation test: testing splashColorEqual when colors are different
TEST_F(SplashTypesTest_1048, splashColorEqual_DifferentColors_1048) {
    SplashColorConstPtr color1;
    SplashColorConstPtr color2;
    int values1[SPOT_NCOMPS + 4] = {1, 2, 3, 4};  // Example values for color 1
    int values2[SPOT_NCOMPS + 4] = {4, 3, 2, 1};  // Different values for color 2

    initializeColor(color1, values1);
    initializeColor(color2, values2);

    EXPECT_FALSE(splashColorEqual(color1, color2));
}

// Boundary test: testing splashColorEqual with extreme values
TEST_F(SplashTypesTest_1048, splashColorEqual_BoundaryValues_1048) {
    SplashColorConstPtr color1;
    SplashColorConstPtr color2;
    int values1[SPOT_NCOMPS + 4] = {INT_MIN, INT_MIN, INT_MIN, INT_MIN};  // Boundary test with minimum int values
    int values2[SPOT_NCOMPS + 4] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};  // Boundary test with maximum int values

    initializeColor(color1, values1);
    initializeColor(color2, values2);

    EXPECT_FALSE(splashColorEqual(color1, color2));
}

// Exceptional case: testing splashColorEqual with uninitialized values (this would depend on the behavior in your actual implementation)
// Assuming uninitialized pointers would be NULL or have garbage values and the behavior can be tested as an error
TEST_F(SplashTypesTest_1048, splashColorEqual_UninitializedColors_1048) {
    SplashColorConstPtr color1;
    SplashColorConstPtr color2;

    // Not initializing the colors, expecting an error or false outcome
    EXPECT_FALSE(splashColorEqual(color1, color2));
}