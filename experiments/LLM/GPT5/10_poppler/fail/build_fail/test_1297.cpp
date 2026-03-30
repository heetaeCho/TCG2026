#include <gtest/gtest.h>
#include "PSOutputDev.h"

class PSOutputDevTest_1297 : public ::testing::Test {
protected:
    PSOutputDev *psOutputDev;

    void SetUp() override {
        psOutputDev = new PSOutputDev("test.ps", nullptr, "Test PS Title", 1, PSOutMode::ePSLevel3, 100, 100, false, false, 0, 0, 100, 100, PSForceRasterize::eRasterize, false, nullptr, nullptr, PSLevel::eLevel1);
    }

    void TearDown() override {
        delete psOutputDev;
    }
};

// Test for useDrawForm function
TEST_F(PSOutputDevTest_1297, useDrawForm_ReturnsPreloadImagesForms_1297) {
    // Test the behavior of the useDrawForm function
    // Setting preloadImagesForms to true should make useDrawForm return true
    psOutputDev->setPreloadImagesForms(true);
    EXPECT_TRUE(psOutputDev->useDrawForm());

    // Setting preloadImagesForms to false should make useDrawForm return false
    psOutputDev->setPreloadImagesForms(false);
    EXPECT_FALSE(psOutputDev->useDrawForm());
}

// Test for getEmbedType1 function
TEST_F(PSOutputDevTest_1297, getEmbedType1_ReturnsExpectedValue_1297) {
    // Test the behavior of the getEmbedType1 function
    psOutputDev->setEmbedType1(true);
    EXPECT_TRUE(psOutputDev->getEmbedType1());

    psOutputDev->setEmbedType1(false);
    EXPECT_FALSE(psOutputDev->getEmbedType1());
}

// Test for getEmbedTrueType function
TEST_F(PSOutputDevTest_1297, getEmbedTrueType_ReturnsExpectedValue_1297) {
    // Test the behavior of the getEmbedTrueType function
    psOutputDev->setEmbedTrueType(true);
    EXPECT_TRUE(psOutputDev->getEmbedTrueType());

    psOutputDev->setEmbedTrueType(false);
    EXPECT_FALSE(psOutputDev->getEmbedTrueType());
}

// Test for getEnableLZW function
TEST_F(PSOutputDevTest_1297, getEnableLZW_ReturnsExpectedValue_1297) {
    // Test the behavior of the getEnableLZW function
    psOutputDev->setEnableLZW(true);
    EXPECT_TRUE(psOutputDev->getEnableLZW());

    psOutputDev->setEnableLZW(false);
    EXPECT_FALSE(psOutputDev->getEnableLZW());
}

// Test for getEnableFlate function
TEST_F(PSOutputDevTest_1297, getEnableFlate_ReturnsExpectedValue_1297) {
    // Test the behavior of the getEnableFlate function
    psOutputDev->setEnableFlate(true);
    EXPECT_TRUE(psOutputDev->getEnableFlate());

    psOutputDev->setEnableFlate(false);
    EXPECT_FALSE(psOutputDev->getEnableFlate());
}

// Test for setForceRasterize function
TEST_F(PSOutputDevTest_1297, setForceRasterize_UpdatesForceRasterize_1297) {
    // Test that the setForceRasterize function updates the forceRasterize field
    psOutputDev->setForceRasterize(PSForceRasterize::eForceRasterize);
    // Assuming forceRasterize is a private member and we can't directly check it, 
    // we check its effect on a public method (e.g., that it properly sets internal flags)
    EXPECT_TRUE(psOutputDev->getForceRasterize()); // Assuming a getter exists for testing purposes
}

// Test for exceptional case in setRasterResolution function
TEST_F(PSOutputDevTest_1297, setRasterResolution_ThrowsOnNegativeValue_1297) {
    // Test the exceptional case where setting raster resolution to a negative value
    EXPECT_THROW(psOutputDev->setRasterResolution(-1.0), std::invalid_argument);
}

// Test for exceptional case in setRasterResolution function
TEST_F(PSOutputDevTest_1297, setRasterResolution_ThrowsOnZeroValue_1297) {
    // Test the exceptional case where setting raster resolution to zero is invalid
    EXPECT_THROW(psOutputDev->setRasterResolution(0.0), std::invalid_argument);
}