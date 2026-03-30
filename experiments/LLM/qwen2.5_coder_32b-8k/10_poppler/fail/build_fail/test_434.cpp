#include <gtest/gtest.h>

#include "GfxState.h"



class GfxCalRGBColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxCalRGBColorSpace>();

    }

};



TEST_F(GfxCalRGBColorSpaceTest_434, GetWhiteZ_ReturnsExpectedValue_434) {

    double expectedWhiteZ = 1.0; // Assuming default value for whiteZ is 1.0

    EXPECT_EQ(colorSpace->getWhiteZ(), expectedWhiteZ);

}



// Boundary conditions and exceptional cases are not directly observable from the given interface.

// However, we can test other getter methods similarly.



TEST_F(GfxCalRGBColorSpaceTest_434, GetWhiteX_ReturnsExpectedValue_434) {

    double expectedWhiteX = 1.0; // Assuming default value for whiteX is 1.0

    EXPECT_EQ(colorSpace->getWhiteX(), expectedWhiteX);

}



TEST_F(GfxCalRGBColorSpaceTest_434, GetWhiteY_ReturnsExpectedValue_434) {

    double expectedWhiteY = 1.0; // Assuming default value for whiteY is 1.0

    EXPECT_EQ(colorSpace->getWhiteY(), expectedWhiteY);

}



TEST_F(GfxCalRGBColorSpaceTest_434, GetBlackX_ReturnsExpectedValue_434) {

    double expectedBlackX = 0.0; // Assuming default value for blackX is 0.0

    EXPECT_EQ(colorSpace->getBlackX(), expectedBlackX);

}



TEST_F(GfxCalRGBColorSpaceTest_434, GetBlackY_ReturnsExpectedValue_434) {

    double expectedBlackY = 0.0; // Assuming default value for blackY is 0.0

    EXPECT_EQ(colorSpace->getBlackY(), expectedBlackY);

}



TEST_F(GfxCalRGBColorSpaceTest_434, GetBlackZ_ReturnsExpectedValue_434) {

    double expectedBlackZ = 0.0; // Assuming default value for blackZ is 0.0

    EXPECT_EQ(colorSpace->getBlackZ(), expectedBlackZ);

}



TEST_F(GfxCalRGBColorSpaceTest_434, GetGammaR_ReturnsExpectedValue_434) {

    double expectedGammaR = 1.0; // Assuming default value for gammaR is 1.0

    EXPECT_EQ(colorSpace->getGammaR(), expectedGammaR);

}



TEST_F(GfxCalRGBColorSpaceTest_434, GetGammaG_ReturnsExpectedValue_434) {

    double expectedGammaG = 1.0; // Assuming default value for gammaG is 1.0

    EXPECT_EQ(colorSpace->getGammaG(), expectedGammaG);

}



TEST_F(GfxCalRGBColorSpaceTest_434, GetGammaB_ReturnsExpectedValue_434) {

    double expectedGammaB = 1.0; // Assuming default value for gammaB is 1.0

    EXPECT_EQ(colorSpace->getGammaB(), expectedGammaB);

}



TEST_F(GfxCalRGBColorSpaceTest_434, GetMatrix_ReturnsExpectedValue_434) {

    std::array<double, 9> expectedMatrix = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}; // Assuming default identity matrix

    EXPECT_EQ(colorSpace->getMatrix(), expectedMatrix);

}
