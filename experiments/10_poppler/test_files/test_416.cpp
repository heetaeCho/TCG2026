#include <gtest/gtest.h>

#include "GfxState.h"



class GfxCalGrayColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxCalGrayColorSpace>();

    }

};



TEST_F(GfxCalGrayColorSpaceTest_416, GetWhiteY_ReturnsCorrectValue_416) {

    double whiteY = colorSpace->getWhiteY();

    EXPECT_DOUBLE_EQ(whiteY, 1.0); // Assuming default value for testing

}



// Additional test cases



TEST_F(GfxCalGrayColorSpaceTest_416, GetWhiteX_ReturnsCorrectValue_416) {

    double whiteX = colorSpace->getWhiteX();

    EXPECT_DOUBLE_EQ(whiteX, 0.95047); // Assuming default value for testing

}



TEST_F(GfxCalGrayColorSpaceTest_416, GetWhiteZ_ReturnsCorrectValue_416) {

    double whiteZ = colorSpace->getWhiteZ();

    EXPECT_DOUBLE_EQ(whiteZ, 1.08883); // Assuming default value for testing

}



TEST_F(GfxCalGrayColorSpaceTest_416, GetBlackX_ReturnsCorrectValue_416) {

    double blackX = colorSpace->getBlackX();

    EXPECT_DOUBLE_EQ(blackX, 0.0); // Assuming default value for testing

}



TEST_F(GfxCalGrayColorSpaceTest_416, GetBlackY_ReturnsCorrectValue_416) {

    double blackY = colorSpace->getBlackY();

    EXPECT_DOUBLE_EQ(blackY, 0.0); // Assuming default value for testing

}



TEST_F(GfxCalGrayColorSpaceTest_416, GetBlackZ_ReturnsCorrectValue_416) {

    double blackZ = colorSpace->getBlackZ();

    EXPECT_DOUBLE_EQ(blackZ, 0.0); // Assuming default value for testing

}



TEST_F(GfxCalGrayColorSpaceTest_416, GetGamma_ReturnsCorrectValue_416) {

    double gamma = colorSpace->getGamma();

    EXPECT_DOUBLE_EQ(gamma, 1.0); // Assuming default value for testing

}
