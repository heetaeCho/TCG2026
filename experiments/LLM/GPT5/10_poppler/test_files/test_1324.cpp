#include <gtest/gtest.h>
#include "PSOutputDev.h"

// TEST_ID: 1324
class PSOutputDevTest_1324 : public ::testing::Test {
protected:
    // Setup the test case with a default PSOutputDev object
    PSOutputDev* psOutputDev;

    virtual void SetUp() {
        // Assuming constructor takes (const char*, PDFDoc*, char*, int, PSOutMode, int, int, bool, bool, int, int, int, int, PSForceRasterize, bool, PSOutCustomCodeCbk, void*, PSLevel)
        psOutputDev = new PSOutputDev("output.ps", nullptr, "Test PS", 1, PSOutMode::ePSOut, 612, 792, false, false, 0, 0, 612, 792, PSForceRasterize::eForce, false, nullptr, nullptr, PSLevel::ePSLevel0);
    }

    virtual void TearDown() {
        delete psOutputDev;
    }
};

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, getEnableFlate_True) {
    // Test that getEnableFlate returns the correct value when enabled
    psOutputDev->setEnableFlate(true);
    EXPECT_TRUE(psOutputDev->getEnableFlate());
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, getEnableFlate_False) {
    // Test that getEnableFlate returns the correct value when disabled
    psOutputDev->setEnableFlate(false);
    EXPECT_FALSE(psOutputDev->getEnableFlate());
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, setEnableFlate_True) {
    // Test that setEnableFlate sets the value correctly to true
    psOutputDev->setEnableFlate(true);
    EXPECT_TRUE(psOutputDev->getEnableFlate());
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, setEnableFlate_False) {
    // Test that setEnableFlate sets the value correctly to false
    psOutputDev->setEnableFlate(false);
    EXPECT_FALSE(psOutputDev->getEnableFlate());
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, setRasterResolution_PositiveValue) {
    // Test that setRasterResolution correctly sets a positive value
    psOutputDev->setRasterResolution(300.0);
    // Add assertions or mock behavior to confirm the value was set
    // Example assertion: (Assuming there's a getter method for resolution)
    // EXPECT_EQ(psOutputDev->getRasterResolution(), 300.0);
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, setRasterResolution_NegativeValue) {
    // Test that setRasterResolution rejects negative values
    psOutputDev->setRasterResolution(-150.0);
    // Add validation to confirm it's not set
    // Example assertion: (Assuming there's a getter method for resolution)
    // EXPECT_LT(psOutputDev->getRasterResolution(), 0.0);
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, setRasterAntialias_True) {
    // Test that setRasterAntialias correctly sets antialiasing to true
    psOutputDev->setRasterAntialias(true);
    // Add assertions or mock behavior to confirm the value was set
    // Example: EXPECT_TRUE(psOutputDev->getRasterAntialias());
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, setRasterAntialias_False) {
    // Test that setRasterAntialias correctly sets antialiasing to false
    psOutputDev->setRasterAntialias(false);
    // Add assertions or mock behavior to confirm the value was set
    // Example: EXPECT_FALSE(psOutputDev->getRasterAntialias());
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, getEnableLZW_True) {
    // Test that getEnableLZW returns the correct value when LZW compression is enabled
    psOutputDev->setEnableLZW(true);
    EXPECT_TRUE(psOutputDev->getEnableLZW());
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, getEnableLZW_False) {
    // Test that getEnableLZW returns the correct value when LZW compression is disabled
    psOutputDev->setEnableLZW(false);
    EXPECT_FALSE(psOutputDev->getEnableLZW());
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, setRasterMono) {
    // Test that setRasterMono correctly sets monochrome raster
    psOutputDev->setRasterMono();
    // Add assertions or mock behavior to confirm the setting
    // Example: EXPECT_TRUE(psOutputDev->isRasterMono());
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, setProcessColorFormat_RGB) {
    // Test that setProcessColorFormat correctly sets RGB color format
    psOutputDev->setProcessColorFormat(SplashColorMode::eRGB);
    // Example: EXPECT_EQ(psOutputDev->getProcessColorFormat(), SplashColorMode::eRGB);
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, setProcessColorFormat_CMYK) {
    // Test that setProcessColorFormat correctly sets CMYK color format
    psOutputDev->setProcessColorFormat(SplashColorMode::eCMYK);
    // Example: EXPECT_EQ(psOutputDev->getProcessColorFormat(), SplashColorMode::eCMYK);
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, checkPageSlice_ValidParams) {
    // Test that checkPageSlice behaves correctly with valid parameters
    // Assuming necessary mock functions or validations
    EXPECT_TRUE(psOutputDev->checkPageSlice(nullptr, 300.0, 300.0, 0, true, true, 0, 0, 100, 100, true, nullptr, nullptr, nullptr, nullptr));
}

// TEST_ID: 1324
TEST_F(PSOutputDevTest_1324, checkPageSlice_InvalidParams) {
    // Test that checkPageSlice returns false for invalid parameters
    EXPECT_FALSE(psOutputDev->checkPageSlice(nullptr, 300.0, 300.0, 0, false, false, 0, 0, 100, 100, true, nullptr, nullptr, nullptr, nullptr));
}