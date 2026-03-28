#include <gtest/gtest.h>

#include "GfxState.h"



class GfxCalGrayColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxCalGrayColorSpace>();

    }

};



TEST_F(GfxCalGrayColorSpaceTest_415, GetWhiteX_ReturnsCorrectValue_415) {

    double whiteX = colorSpace->getWhiteX();

    // Assuming a default value for whiteX is 0.95047, which is typical for D65 illuminant

    EXPECT_DOUBLE_EQ(whiteX, 0.95047);

}



TEST_F(GfxCalGrayColorSpaceTest_415, GetWhiteY_ReturnsCorrectValue_415) {

    double whiteY = colorSpace->getWhiteY();

    // Assuming a default value for whiteY is 1.00000, which is typical for D65 illuminant

    EXPECT_DOUBLE_EQ(whiteY, 1.00000);

}



TEST_F(GfxCalGrayColorSpaceTest_415, GetWhiteZ_ReturnsCorrectValue_415) {

    double whiteZ = colorSpace->getWhiteZ();

    // Assuming a default value for whiteZ is 1.08883, which is typical for D65 illuminant

    EXPECT_DOUBLE_EQ(whiteZ, 1.08883);

}



TEST_F(GfxCalGrayColorSpaceTest_415, GetBlackX_ReturnsCorrectValue_415) {

    double blackX = colorSpace->getBlackX();

    // Assuming a default value for blackX is 0.0

    EXPECT_DOUBLE_EQ(blackX, 0.0);

}



TEST_F(GfxCalGrayColorSpaceTest_415, GetBlackY_ReturnsCorrectValue_415) {

    double blackY = colorSpace->getBlackY();

    // Assuming a default value for blackY is 0.0

    EXPECT_DOUBLE_EQ(blackY, 0.0);

}



TEST_F(GfxCalGrayColorSpaceTest_415, GetBlackZ_ReturnsCorrectValue_415) {

    double blackZ = colorSpace->getBlackZ();

    // Assuming a default value for blackZ is 0.0

    EXPECT_DOUBLE_EQ(blackZ, 0.0);

}



TEST_F(GfxCalGrayColorSpaceTest_415, GetGamma_ReturnsCorrectValue_415) {

    double gamma = colorSpace->getGamma();

    // Assuming a default value for gamma is 1.0

    EXPECT_DOUBLE_EQ(gamma, 1.0);

}
