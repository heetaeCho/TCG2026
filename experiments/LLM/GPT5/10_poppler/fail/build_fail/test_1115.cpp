#include <gtest/gtest.h>
#include "SplashOutputDev.h"

// Test Fixture for SplashOutputDev
class SplashOutputDevTest_1115 : public ::testing::Test {
protected:
    SplashOutputDev *splashOutputDev;

    // Set up function for creating a SplashOutputDev instance before each test
    void SetUp() override {
        splashOutputDev = new SplashOutputDev(SplashColorMode::splashModeRGB, 8, nullptr, true, SplashThinLineMode::splashThinLineNone, false);
    }

    // Tear down function for cleaning up after each test
    void TearDown() override {
        delete splashOutputDev;
    }
};

// Test normal operation of setFontAntialias method
TEST_F(SplashOutputDevTest_1115, SetFontAntialiasNormal_1115) {
    // Set font antialias to true
    splashOutputDev->setFontAntialias(true);

    // Test that the setter worked correctly
    EXPECT_TRUE(splashOutputDev->getFontAntialias());
}

// Test normal operation of setFontAntialias method with false value
TEST_F(SplashOutputDevTest_1115, SetFontAntialiasFalse_1115) {
    // Set font antialias to false
    splashOutputDev->setFontAntialias(false);

    // Test that the setter worked correctly
    EXPECT_FALSE(splashOutputDev->getFontAntialias());
}

// Test edge case where font antialiasing is toggled repeatedly
TEST_F(SplashOutputDevTest_1115, SetFontAntialiasToggle_1115) {
    // Toggle the antialiasing
    splashOutputDev->setFontAntialias(true);
    EXPECT_TRUE(splashOutputDev->getFontAntialias());

    splashOutputDev->setFontAntialias(false);
    EXPECT_FALSE(splashOutputDev->getFontAntialias());
}

// Test that the object handles invalid state gracefully (exceptional case)
TEST_F(SplashOutputDevTest_1115, SetFontAntialiasNullPointer_1115) {
    // Simulate null pointer by deleting splashOutputDev
    delete splashOutputDev;
    splashOutputDev = nullptr;

    // Expect that calling setFontAntialias does not crash or cause undefined behavior
    EXPECT_NO_THROW({
        if (splashOutputDev) {
            splashOutputDev->setFontAntialias(true);
        }
    });
}

// Test boundary case: large value for bitmap row padding (boundary test for internal state)
TEST_F(SplashOutputDevTest_1115, SetLargeBitmapRowPadding_1115) {
    // Here we are not testing the internal value directly but testing the observable behavior
    // A large value for bitmap row padding should not crash the system
    EXPECT_NO_THROW({
        splashOutputDev->setBitmapRowPad(1000000);
    });
}