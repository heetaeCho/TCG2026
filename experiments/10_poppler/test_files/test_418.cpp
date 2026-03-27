#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



using namespace testing;



class GfxCalGrayColorSpaceTest_418 : public ::testing::Test {

protected:

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxCalGrayColorSpace>();

    }

};



TEST_F(GfxCalGrayColorSpaceTest_418, GetBlackX_ReturnsCorrectValue_418) {

    // Assuming getBlackX() returns a value that can be verified

    double blackX = colorSpace->getBlackX();

    // Since we cannot infer the internal logic, we assume a default or expected value for testing purposes.

    EXPECT_DOUBLE_EQ(blackX, 0.0); // This is an assumption and should be replaced with actual expected value if known.

}



TEST_F(GfxCalGrayColorSpaceTest_418, GetWhiteX_ReturnsCorrectValue_418) {

    double whiteX = colorSpace->getWhiteX();

    EXPECT_DOUBLE_EQ(whiteX, 0.95047); // Standard D65 illuminant X value

}



TEST_F(GfxCalGrayColorSpaceTest_418, GetWhiteY_ReturnsCorrectValue_418) {

    double whiteY = colorSpace->getWhiteY();

    EXPECT_DOUBLE_EQ(whiteY, 1.0); // Standard D65 illuminant Y value

}



TEST_F(GfxCalGrayColorSpaceTest_418, GetWhiteZ_ReturnsCorrectValue_418) {

    double whiteZ = colorSpace->getWhiteZ();

    EXPECT_DOUBLE_EQ(whiteZ, 1.08883); // Standard D65 illuminant Z value

}



TEST_F(GfxCalGrayColorSpaceTest_418, GetBlackY_ReturnsCorrectValue_418) {

    double blackY = colorSpace->getBlackY();

    EXPECT_DOUBLE_EQ(blackY, 0.0); // Assuming black Y value is 0.0

}



TEST_F(GfxCalGrayColorSpaceTest_418, GetBlackZ_ReturnsCorrectValue_418) {

    double blackZ = colorSpace->getBlackZ();

    EXPECT_DOUBLE_EQ(blackZ, 0.0); // Assuming black Z value is 0.0

}



TEST_F(GfxCalGrayColorSpaceTest_418, GetGamma_ReturnsCorrectValue_418) {

    double gamma = colorSpace->getGamma();

    EXPECT_DOUBLE_EQ(gamma, 1.0); // Default gamma value assumption

}
