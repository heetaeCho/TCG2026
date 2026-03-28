#include <gtest/gtest.h>

// The function to be tested
static inline unsigned char splashDeviceN8Y(SplashColorPtr deviceN8) { return deviceN8[2]; }

// Test Fixture Class for SplashTypes
class SplashTypesTest_1045 : public ::testing::Test {
protected:
    SplashColorPtr deviceN8;
    
    // Set up test data if needed
    void SetUp() override {
        // Example setup, assuming deviceN8 is a valid pointer
        deviceN8 = new unsigned char[3]{255, 128, 64}; // Sample data
    }

    void TearDown() override {
        // Clean up if necessary
        delete[] deviceN8;
    }
};

// Normal operation test case for splashDeviceN8Y_1045
TEST_F(SplashTypesTest_1045, splashDeviceN8Y_ReturnsCorrectValue_1045) {
    // Arrange (test data is already set in SetUp)
    unsigned char expected_value = 64;

    // Act
    unsigned char result = splashDeviceN8Y(deviceN8);

    // Assert
    EXPECT_EQ(result, expected_value);
}

// Boundary test case for splashDeviceN8Y_1045
TEST_F(SplashTypesTest_1045, splashDeviceN8Y_BoundaryCondition_1045) {
    // Arrange (testing the smallest possible array, ensuring index is safe)
    unsigned char testData[3] = {0, 0, 0}; // edge case with zero values
    unsigned char expected_value = 0;

    // Act
    unsigned char result = splashDeviceN8Y(testData);

    // Assert
    EXPECT_EQ(result, expected_value);
}

// Exceptional or error case test case for splashDeviceN8Y_1045
TEST_F(SplashTypesTest_1045, splashDeviceN8Y_NullPointer_1045) {
    // Arrange (test with a null pointer)
    SplashColorPtr nullPointer = nullptr;

    // Act & Assert (expecting a crash or undefined behavior, which may need handling in the actual code)
    EXPECT_DEATH({
        splashDeviceN8Y(nullPointer);
    }, ".*");
}