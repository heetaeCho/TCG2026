#include <gtest/gtest.h>

#include "GfxState.h"



class GfxCalGrayColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxCalGrayColorSpace>();

    }

};



TEST_F(GfxCalGrayColorSpaceTest_420, GetBlackZ_ReturnsCorrectValue_420) {

    // Assuming getBlackZ returns a specific value that can be verified

    double expectedBlackZ = 0.0; // Example value, replace with actual expected value if known

    EXPECT_DOUBLE_EQ(expectedBlackZ, colorSpace->getBlackZ());

}



TEST_F(GfxCalGrayColorSpaceTest_420, GetWhiteX_ReturnsCorrectValue_420) {

    // Assuming getWhiteX returns a specific value that can be verified

    double expectedWhiteX = 1.0; // Example value, replace with actual expected value if known

    EXPECT_DOUBLE_EQ(expectedWhiteX, colorSpace->getWhiteX());

}



TEST_F(GfxCalGrayColorSpaceTest_420, GetWhiteY_ReturnsCorrectValue_420) {

    // Assuming getWhiteY returns a specific value that can be verified

    double expectedWhiteY = 1.0; // Example value, replace with actual expected value if known

    EXPECT_DOUBLE_EQ(expectedWhiteY, colorSpace->getWhiteY());

}



TEST_F(GfxCalGrayColorSpaceTest_420, GetWhiteZ_ReturnsCorrectValue_420) {

    // Assuming getWhiteZ returns a specific value that can be verified

    double expectedWhiteZ = 1.0; // Example value, replace with actual expected value if known

    EXPECT_DOUBLE_EQ(expectedWhiteZ, colorSpace->getWhiteZ());

}



TEST_F(GfxCalGrayColorSpaceTest_420, GetBlackX_ReturnsCorrectValue_420) {

    // Assuming getBlackX returns a specific value that can be verified

    double expectedBlackX = 0.0; // Example value, replace with actual expected value if known

    EXPECT_DOUBLE_EQ(expectedBlackX, colorSpace->getBlackX());

}



TEST_F(GfxCalGrayColorSpaceTest_420, GetBlackY_ReturnsCorrectValue_420) {

    // Assuming getBlackY returns a specific value that can be verified

    double expectedBlackY = 0.0; // Example value, replace with actual expected value if known

    EXPECT_DOUBLE_EQ(expectedBlackY, colorSpace->getBlackY());

}



TEST_F(GfxCalGrayColorSpaceTest_420, GetGamma_ReturnsCorrectValue_420) {

    // Assuming getGamma returns a specific value that can be verified

    double expectedGamma = 1.0; // Example value, replace with actual expected value if known

    EXPECT_DOUBLE_EQ(expectedGamma, colorSpace->getGamma());

}



TEST_F(GfxCalGrayColorSpaceTest_420, GetMode_ReturnsCorrectValue_420) {

    // Assuming getMode returns a specific enum value that can be verified

    GfxColorSpaceMode expectedMode = gfxDeviceGray; // Example value, replace with actual expected value if known

    EXPECT_EQ(expectedMode, colorSpace->getMode());

}



TEST_F(GfxCalGrayColorSpaceTest_420, GetNComps_ReturnsCorrectValue_420) {

    // Assuming getNComps returns a specific integer value that can be verified

    int expectedNComps = 1; // Example value, replace with actual expected value if known

    EXPECT_EQ(expectedNComps, colorSpace->getNComps());

}
