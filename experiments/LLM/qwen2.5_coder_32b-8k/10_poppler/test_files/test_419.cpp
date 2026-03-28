#include <gtest/gtest.h>

#include "GfxState.h"



class GfxCalGrayColorSpaceTest_419 : public ::testing::Test {

protected:

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxCalGrayColorSpace>();

    }

};



TEST_F(GfxCalGrayColorSpaceTest_419, GetBlackY_ReturnsCorrectValue_419) {

    // Assuming blackY is initialized to a known value in the constructor

    double expectedBlackY = 0.0; // This value should be replaced with the actual expected value if known

    EXPECT_EQ(expectedBlackY, colorSpace->getBlackY());

}



TEST_F(GfxCalGrayColorSpaceTest_419, GetWhiteX_ReturnsCorrectValue_419) {

    // Assuming whiteX is initialized to a known value in the constructor

    double expectedWhiteX = 0.9505; // Example typical D65 illuminant value

    EXPECT_EQ(expectedWhiteX, colorSpace->getWhiteX());

}



TEST_F(GfxCalGrayColorSpaceTest_419, GetWhiteY_ReturnsCorrectValue_419) {

    // Assuming whiteY is initialized to a known value in the constructor

    double expectedWhiteY = 1.0; // Example typical D65 illuminant value

    EXPECT_EQ(expectedWhiteY, colorSpace->getWhiteY());

}



TEST_F(GfxCalGrayColorSpaceTest_419, GetWhiteZ_ReturnsCorrectValue_419) {

    // Assuming whiteZ is initialized to a known value in the constructor

    double expectedWhiteZ = 1.089; // Example typical D65 illuminant value

    EXPECT_EQ(expectedWhiteZ, colorSpace->getWhiteZ());

}



TEST_F(GfxCalGrayColorSpaceTest_419, GetBlackX_ReturnsCorrectValue_419) {

    // Assuming blackX is initialized to a known value in the constructor

    double expectedBlackX = 0.0; // This value should be replaced with the actual expected value if known

    EXPECT_EQ(expectedBlackX, colorSpace->getBlackX());

}



TEST_F(GfxCalGrayColorSpaceTest_419, GetBlackZ_ReturnsCorrectValue_419) {

    // Assuming blackZ is initialized to a known value in the constructor

    double expectedBlackZ = 0.0; // This value should be replaced with the actual expected value if known

    EXPECT_EQ(expectedBlackZ, colorSpace->getBlackZ());

}



TEST_F(GfxCalGrayColorSpaceTest_419, GetGamma_ReturnsCorrectValue_419) {

    // Assuming gamma is initialized to a known value in the constructor

    double expectedGamma = 1.0; // This value should be replaced with the actual expected value if known

    EXPECT_EQ(expectedGamma, colorSpace->getGamma());

}



TEST_F(GfxCalGrayColorSpaceTest_419, GetMode_ReturnsCorrectValue_419) {

    // Assuming getMode returns a valid GfxColorSpaceMode enum value

    GfxColorSpaceMode expectedMode = gfxDeviceGray; // This value should be replaced with the actual expected value if known

    EXPECT_EQ(expectedMode, colorSpace->getMode());

}



TEST_F(GfxCalGrayColorSpaceTest_419, GetNComps_ReturnsCorrectValue_419) {

    // Assuming getNComps returns a valid number of components for GfxCalGrayColorSpace

    int expectedComponents = 1; // CalGray typically has 1 component

    EXPECT_EQ(expectedComponents, colorSpace->getNComps());

}
