#include <gtest/gtest.h>

#include "GfxState.h"



class GfxCalGrayColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxCalGrayColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxCalGrayColorSpace>();

    }

};



TEST_F(GfxCalGrayColorSpaceTest_414, GetNComps_ReturnsOne_414) {

    EXPECT_EQ(colorSpace->getNComps(), 1);

}



// Assuming GfxColor and GfxGray are properly defined elsewhere

TEST_F(GfxCalGrayColorSpaceTest_414, GetGray_DoesNotCrashWithNullPointer_414) {

    colorSpace->getGray(nullptr, nullptr);

}



TEST_F(GfxCalGrayColorSpaceTest_414, GetRGB_DoesNotCrashWithNullPointer_414) {

    colorSpace->getRGB(nullptr, nullptr);

}



TEST_F(GfxCalGrayColorSpaceTest_414, GetCMYK_DoesNotCrashWithNullPointer_414) {

    colorSpace->getCMYK(nullptr, nullptr);

}



TEST_F(GfxCalGrayColorSpaceTest_414, GetDeviceN_DoesNotCrashWithNullPointer_414) {

    colorSpace->getDeviceN(nullptr, nullptr);

}



TEST_F(GfxCalGrayColorSpaceTest_414, GetDefaultColor_DoesNotCrashWithNullPointer_414) {

    colorSpace->getDefaultColor(nullptr);

}



TEST_F(GfxCalGrayColorSpaceTest_414, GetWhiteX_ReturnsValidValue_414) {

    EXPECT_GE(colorSpace->getWhiteX(), 0.0);

    EXPECT_LE(colorSpace->getWhiteX(), 1.0);

}



TEST_F(GfxCalGrayColorSpaceTest_414, GetWhiteY_ReturnsValidValue_414) {

    EXPECT_GE(colorSpace->getWhiteY(), 0.0);

    EXPECT_LE(colorSpace->getWhiteY(), 1.0);

}



TEST_F(GfxCalGrayColorSpaceTest_414, GetWhiteZ_ReturnsValidValue_414) {

    EXPECT_GE(colorSpace->getWhiteZ(), 0.0);

    EXPECT_LE(colorSpace->getWhiteZ(), 1.0);

}



TEST_F(GfxCalGrayColorSpaceTest_414, GetBlackX_ReturnsValidValue_414) {

    EXPECT_GE(colorSpace->getBlackX(), 0.0);

    EXPECT_LE(colorSpace->getBlackX(), 1.0);

}



TEST_F(GfxCalGrayColorSpaceTest_414, GetBlackY_ReturnsValidValue_414) {

    EXPECT_GE(colorSpace->getBlackY(), 0.0);

    EXPECT_LE(colorSpace->getBlackY(), 1.0);

}



TEST_F(GfxCalGrayColorSpaceTest_414, GetBlackZ_ReturnsValidValue_414) {

    EXPECT_GE(colorSpace->getBlackZ(), 0.0);

    EXPECT_LE(colorSpace->getBlackZ(), 1.0);

}



TEST_F(GfxCalGrayColorSpaceTest_414, GetGamma_ReturnsPositiveValue_414) {

    EXPECT_GT(colorSpace->getGamma(), 0.0);

}
