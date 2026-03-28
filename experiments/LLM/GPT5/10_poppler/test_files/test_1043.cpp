#include <gtest/gtest.h>
#include "./TestProjects/poppler/splash/SplashTypes.h"

class SplashTypesTest_1043 : public ::testing::Test {
protected:
    // Setup code if needed (currently not needed for this simple test)
};

TEST_F(SplashTypesTest_1043, SplashDeviceN8C_NormalOperation_1043) {
    // Test with a typical array of values
    unsigned char deviceN8[] = {255, 100, 50, 0}; // Example array
    unsigned char result = splashDeviceN8C(deviceN8);
    
    // The expected result should be the first element of the array
    EXPECT_EQ(result, 255);
}

TEST_F(SplashTypesTest_1043, SplashDeviceN8C_EmptyArray_1043) {
    // Test with an empty array (invalid case)
    unsigned char deviceN8[] = {}; // Empty array
    
    // We should expect a failure here, possibly an error or undefined behavior,
    // but let's check if the function handles it.
    // Depending on implementation, the result might be garbage or a defined behavior
    // (e.g., returning 0 in case of empty input).
    unsigned char result = splashDeviceN8C(deviceN8);
    
    // Here, we'll expect 0 as the result if no other behavior is defined for empty input
    EXPECT_EQ(result, 0);
}

TEST_F(SplashTypesTest_1043, SplashDeviceN8C_SingleElementArray_1043) {
    // Test with an array containing just one element
    unsigned char deviceN8[] = {128}; // Single element array
    unsigned char result = splashDeviceN8C(deviceN8);
    
    // The result should be the only element in the array
    EXPECT_EQ(result, 128);
}

TEST_F(SplashTypesTest_1043, SplashDeviceN8C_NegativeValues_1043) {
    // Test with values that may be negative (treated as unsigned)
    unsigned char deviceN8[] = {0, 255}; // Valid unsigned char values, 0 and 255
    unsigned char result = splashDeviceN8C(deviceN8);
    
    // The result should still be 0, the first element in the array
    EXPECT_EQ(result, 0);
}