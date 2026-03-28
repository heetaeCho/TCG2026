#include <gtest/gtest.h>
#include "./TestProjects/poppler/splash/SplashBitmap.h"

// Test fixture for SplashBitmap
class SplashBitmapTest_1121 : public ::testing::Test {
protected:
    SplashBitmapTest_1121() {
        // Setup code (if needed)
    }

    // You can create a SplashBitmap instance here for repeated use in tests
    SplashBitmap* splashBitmap;
};

// Normal Operation Test: Verifying getRowPad() function
TEST_F(SplashBitmapTest_1121, GetRowPad_1121) {
    // Create a SplashBitmap with a rowPad value of 10
    splashBitmap = new SplashBitmap(100, 100, 10, SplashColorMode::splashModeRGB, false, true, nullptr);

    // Verify that the getRowPad function returns the correct value
    EXPECT_EQ(splashBitmap->getRowPad(), 10);

    // Clean up
    delete splashBitmap;
}

// Boundary Condition Test: Verifying behavior with 0 rowPad
TEST_F(SplashBitmapTest_1121, GetRowPad_Zero_1121) {
    // Create a SplashBitmap with a rowPad value of 0
    splashBitmap = new SplashBitmap(100, 100, 0, SplashColorMode::splashModeRGB, false, true, nullptr);

    // Verify that the getRowPad function returns the correct value
    EXPECT_EQ(splashBitmap->getRowPad(), 0);

    // Clean up
    delete splashBitmap;
}

// Exceptional/Error Case Test: Invalid SplashBitmap creation (if applicable)
TEST_F(SplashBitmapTest_1121, GetRowPad_InvalidBitmap_1121) {
    // Assuming we can't create a SplashBitmap with a negative rowPad, as a validation
    // Create an invalid SplashBitmap with a negative rowPad value
    splashBitmap = new SplashBitmap(100, 100, -1, SplashColorMode::splashModeRGB, false, true, nullptr);

    // Assuming this would be handled internally and that getRowPad() may return an invalid value in such cases
    // Here, we just check if the result is what we expect in an invalid situation (e.g., default value)
    EXPECT_EQ(splashBitmap->getRowPad(), -1); // Or you may expect a default/valid return here depending on the class implementation

    // Clean up
    delete splashBitmap;
}

// Verifying external interaction: Assuming SplashBitmap interacts with other dependencies (e.g., SplashColorMode)
TEST_F(SplashBitmapTest_1121, GetMode_1121) {
    // Create a SplashBitmap with a specific mode
    splashBitmap = new SplashBitmap(100, 100, 10, SplashColorMode::splashModeCMYK, false, true, nullptr);

    // Verify that the getMode function returns the correct mode
    EXPECT_EQ(splashBitmap->getMode(), SplashColorMode::splashModeCMYK);

    // Clean up
    delete splashBitmap;
}

// Boundary condition: Large bitmap size and rowPad
TEST_F(SplashBitmapTest_1121, GetRowPad_LargeBitmap_1121) {
    // Create a large SplashBitmap (e.g., 10000x10000 size) and a large rowPad
    splashBitmap = new SplashBitmap(10000, 10000, 10000, SplashColorMode::splashModeRGB, true, true, nullptr);

    // Verify that the getRowPad function returns the correct value
    EXPECT_EQ(splashBitmap->getRowPad(), 10000);

    // Clean up
    delete splashBitmap;
}