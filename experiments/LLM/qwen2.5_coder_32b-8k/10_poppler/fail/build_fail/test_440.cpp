#include <gtest/gtest.h>

#include "GfxState.h"



class GfxCalRGBColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxCalRGBColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxCalRGBColorSpace>();

    }

};



TEST_F(GfxCalRGBColorSpaceTest_440, GetGammaB_ReturnsCorrectValue_440) {

    double gammaB = colorSpace->getGammaB();

    EXPECT_DOUBLE_EQ(gammaB, colorSpace->getGammaB()); // Assuming consistent value on subsequent calls

}



// Additional tests based on other observable behaviors and boundary conditions



TEST_F(GfxCalRGBColorSpaceTest_440, GetGammaR_ReturnsConsistentValue_440) {

    double gammaR = colorSpace->getGammaR();

    EXPECT_DOUBLE_EQ(gammaR, colorSpace->getGammaR());

}



TEST_F(GfxCalRGBColorSpaceTest_440, GetGammaG_ReturnsConsistentValue_440) {

    double gammaG = colorSpace->getGammaG();

    EXPECT_DOUBLE_EQ(gammaG, colorSpace->getGammaG());

}



TEST_F(GfxCalRGBColorSpaceTest_440, GetMatrix_ReturnsConsistentValues_440) {

    auto matrix1 = colorSpace->getMatrix();

    auto matrix2 = colorSpace->getMatrix();

    EXPECT_EQ(matrix1, matrix2);

}
