#include <gtest/gtest.h>

#include "GfxState.h"



class GfxCalRGBColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxCalRGBColorSpace>();

    }

};



TEST_F(GfxCalRGBColorSpaceTest_435, GetBlackX_ReturnsCorrectValue_435) {

    double blackX = colorSpace->getBlackX();

    EXPECT_DOUBLE_EQ(blackX, 0.0); // Assuming default value is 0.0, as not specified otherwise

}



TEST_F(GfxCalRGBColorSpaceTest_435, GetWhiteX_ReturnsCorrectValue_435) {

    double whiteX = colorSpace->getWhiteX();

    EXPECT_DOUBLE_EQ(whiteX, 1.0); // Assuming default value is 1.0, as not specified otherwise

}



TEST_F(GfxCalRGBColorSpaceTest_435, GetBlackY_ReturnsCorrectValue_435) {

    double blackY = colorSpace->getBlackY();

    EXPECT_DOUBLE_EQ(blackY, 0.0); // Assuming default value is 0.0, as not specified otherwise

}



TEST_F(GfxCalRGBColorSpaceTest_435, GetWhiteY_ReturnsCorrectValue_435) {

    double whiteY = colorSpace->getWhiteY();

    EXPECT_DOUBLE_EQ(whiteY, 1.0); // Assuming default value is 1.0, as not specified otherwise

}



TEST_F(GfxCalRGBColorSpaceTest_435, GetBlackZ_ReturnsCorrectValue_435) {

    double blackZ = colorSpace->getBlackZ();

    EXPECT_DOUBLE_EQ(blackZ, 0.0); // Assuming default value is 0.0, as not specified otherwise

}



TEST_F(GfxCalRGBColorSpaceTest_435, GetWhiteZ_ReturnsCorrectValue_435) {

    double whiteZ = colorSpace->getWhiteZ();

    EXPECT_DOUBLE_EQ(whiteZ, 1.0); // Assuming default value is 1.0, as not specified otherwise

}



TEST_F(GfxCalRGBColorSpaceTest_435, GetGammaR_ReturnsCorrectValue_435) {

    double gammaR = colorSpace->getGammaR();

    EXPECT_DOUBLE_EQ(gammaR, 1.0); // Assuming default value is 1.0, as not specified otherwise

}



TEST_F(GfxCalRGBColorSpaceTest_435, GetGammaG_ReturnsCorrectValue_435) {

    double gammaG = colorSpace->getGammaG();

    EXPECT_DOUBLE_EQ(gammaG, 1.0); // Assuming default value is 1.0, as not specified otherwise

}



TEST_F(GfxCalRGBColorSpaceTest_435, GetGammaB_ReturnsCorrectValue_435) {

    double gammaB = colorSpace->getGammaB();

    EXPECT_DOUBLE_EQ(gammaB, 1.0); // Assuming default value is 1.0, as not specified otherwise

}



TEST_F(GfxCalRGBColorSpaceTest_435, GetMatrix_ReturnsCorrectValue_435) {

    const std::array<double, 9>& matrix = colorSpace->getMatrix();

    for (const auto& value : matrix) {

        EXPECT_DOUBLE_EQ(value, 0.0); // Assuming default values are 0.0, as not specified otherwise

    }

}
