#include <gtest/gtest.h>

static inline unsigned char splashRGB8B(SplashColorPtr rgb8) {
    return rgb8[2];
}

// TEST_F(SplashRGB8BTest_1035, NormalOperation_1035)
TEST_F(SplashRGB8BTest_1035, NormalOperation_1035) {
    // Normal RGB value
    unsigned char rgb8[] = {255, 0, 123};  // B = 123
    EXPECT_EQ(splashRGB8B(rgb8), 123);
}

// TEST_F(SplashRGB8BTest_1035, BoundaryCondition_EmptyArray_1035)
TEST_F(SplashRGB8BTest_1035, BoundaryCondition_EmptyArray_1035) {
    // Edge case with an empty array, if this is a valid input, depends on the system.
    // Assuming that there will be no out-of-bounds access.
    unsigned char rgb8[] = {};  // An empty array
    // This case depends on your expected behavior. If it throws or crashes, we should test that as well.
    // For now, it might be useful to assume undefined behavior, unless further context is provided.
    EXPECT_ANY_THROW(splashRGB8B(rgb8)); // Exception if undefined behavior occurs
}

// TEST_F(SplashRGB8BTest_1035, BoundaryCondition_SmallArray_1035)
TEST_F(SplashRGB8BTest_1035, BoundaryCondition_SmallArray_1035) {
    // Array with just 1 or 2 elements
    unsigned char rgb8[] = {255, 0};  // Less than 3 elements
    EXPECT_ANY_THROW(splashRGB8B(rgb8));  // This should throw or be handled as an error since it's out of bounds.
}

// TEST_F(SplashRGB8BTest_1035, LargeValues_1035)
TEST_F(SplashRGB8BTest_1035, LargeValues_1035) {
    // Test with large values (RGB components beyond 255)
    unsigned char rgb8[] = {256, 512, 1024};  // Values exceed the valid byte range
    EXPECT_EQ(splashRGB8B(rgb8), 1024);  // Check if the function handles out-of-bound values.
}

// TEST_F(SplashRGB8BTest_1035, NullPointer_1035)
TEST_F(SplashRGB8BTest_1035, NullPointer_1035) {
    // Null pointer case
    SplashColorPtr rgb8 = nullptr;
    EXPECT_ANY_THROW(splashRGB8B(rgb8));  // Expecting some kind of exception or crash handling for null
}

// TEST_F(SplashRGB8BTest_1035, NonArrayInput_1035)
TEST_F(SplashRGB8BTest_1035, NonArrayInput_1035) {
    // Invalid input (not an array)
    EXPECT_ANY_THROW(splashRGB8B(nullptr));  // Trying a non-array input
}