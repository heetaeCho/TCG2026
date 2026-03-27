#include <gtest/gtest.h>

// Assuming splashBGR8B is declared in SplashTypes.h
extern "C" {
    static inline unsigned char splashBGR8B(unsigned char* bgr8) { return bgr8[0]; }
}

// Test case for normal operation
TEST_F(SplashTypesTest_1038, SplashBGR8B_NormalOperation_1038) {
    unsigned char color[] = { 255, 0, 0 };  // Red in BGR format
    EXPECT_EQ(splashBGR8B(color), 255);      // Expect the first byte (255)
}

// Test case for boundary condition with minimal size
TEST_F(SplashTypesTest_1038, SplashBGR8B_SingleElementArray_1038) {
    unsigned char color[] = { 123 };  // Only one byte
    EXPECT_EQ(splashBGR8B(color), 123); // Expect the first byte (123)
}

// Test case for exceptional case: Null pointer
TEST_F(SplashTypesTest_1038, SplashBGR8B_NullPointer_1038) {
    unsigned char* color = nullptr;
    EXPECT_DEATH(splashBGR8B(color), ".*");  // Expect the function to terminate due to nullptr dereference
}