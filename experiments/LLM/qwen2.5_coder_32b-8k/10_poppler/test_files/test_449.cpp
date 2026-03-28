#include <gtest/gtest.h>

#include "GfxState.h"



class GfxLabColorSpaceTest_449 : public ::testing::Test {

protected:

    std::unique_ptr<GfxLabColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxLabColorSpace>();

    }

};



TEST_F(GfxLabColorSpaceTest_449, GetWhiteX_ReturnsValidValue_449) {

    double whiteX = colorSpace->getWhiteX();

    EXPECT_GE(whiteX, 0.0);

    EXPECT_LE(whiteX, 1.0);

}



TEST_F(GfxLabColorSpaceTest_449, GetWhiteY_ReturnsValidValue_449) {

    double whiteY = colorSpace->getWhiteY();

    EXPECT_GE(whiteY, 0.0);

    EXPECT_LE(whiteY, 1.0);

}



TEST_F(GfxLabColorSpaceTest_449, GetWhiteZ_ReturnsValidValue_449) {

    double whiteZ = colorSpace->getWhiteZ();

    EXPECT_GE(whiteZ, 0.0);

    EXPECT_LE(whiteZ, 1.0);

}



TEST_F(GfxLabColorSpaceTest_449, GetBlackX_ReturnsValidValue_449) {

    double blackX = colorSpace->getBlackX();

    EXPECT_GE(blackX, 0.0);

    EXPECT_LE(blackX, 1.0);

}



TEST_F(GfxLabColorSpaceTest_449, GetBlackY_ReturnsValidValue_449) {

    double blackY = colorSpace->getBlackY();

    EXPECT_GE(blackY, 0.0);

    EXPECT_LE(blackY, 1.0);

}



TEST_F(GfxLabColorSpaceTest_449, GetBlackZ_ReturnsValidValue_449) {

    double blackZ = colorSpace->getBlackZ();

    EXPECT_GE(blackZ, 0.0);

    EXPECT_LE(blackZ, 1.0);

}



TEST_F(GfxLabColorSpaceTest_449, GetAMin_ReturnsValidValue_449) {

    double aMin = colorSpace->getAMin();

    EXPECT_TRUE(std::isfinite(aMin));

}



TEST_F(GfxLabColorSpaceTest_449, GetAMax_ReturnsValidValue_449) {

    double aMax = colorSpace->getAMax();

    EXPECT_TRUE(std::isfinite(aMax));

}



TEST_F(GfxLabColorSpaceTest_449, GetBMin_ReturnsValidValue_449) {

    double bMin = colorSpace->getBMin();

    EXPECT_TRUE(std::isfinite(bMin));

}



TEST_F(GfxLabColorSpaceTest_449, GetBMax_ReturnsValidValue_449) {

    double bMax = colorSpace->getBMax();

    EXPECT_TRUE(std::isfinite(bMax));

}
