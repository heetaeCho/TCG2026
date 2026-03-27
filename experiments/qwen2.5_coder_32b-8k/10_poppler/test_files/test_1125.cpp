#include <gtest/gtest.h>

#include "SplashBitmap.h"

#include <vector>

#include <memory>



class SplashBitmapTest : public ::testing::Test {

protected:

    std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;

    SplashBitmap* bitmap;



    void SetUp() override {

        // Assuming a default constructor or setup for simplicity

        bitmap = new SplashBitmap(10, 10, 1, SplashScreenModeRGB8, false, true, &separationList);

    }



    void TearDown() override {

        delete bitmap;

    }

};



TEST_F(SplashBitmapTest_1125, GetSeparationList_ReturnsCorrectPointer_1125) {

    EXPECT_EQ(bitmap->getSeparationList(), &separationList);

}



TEST_F(SplashBitmapTest_1125, GetWidth_ReturnsPositiveValue_1125) {

    EXPECT_GT(bitmap->getWidth(), 0);

}



TEST_F(SplashBitmapTest_1125, GetHeight_ReturnsPositiveValue_1125) {

    EXPECT_GT(bitmap->getHeight(), 0);

}



TEST_F(SplashBitmapTest_1125, GetRowSize_ReturnsNonNegativeValue_1125) {

    EXPECT_GE(bitmap->getRowSize(), 0);

}



TEST_F(SplashBitmapTest_1125, GetAlphaRowSize_ReturnsNonNegativeValue_1125) {

    EXPECT_GE(bitmap->getAlphaRowSize(), 0);

}



TEST_F(SplashBitmapTest_1125, GetRowPad_ReturnsNonNegativeValue_1125) {

    EXPECT_GE(bitmap->getRowPad(), 0);

}



TEST_F(SplashBitmapTest_1125, GetMode_ReturnsValidSplashColorMode_1125) {

    SplashColorMode mode = bitmap->getMode();

    EXPECT_TRUE(mode == SplashScreenModeRGB8 || mode == SplashScreenModeMono8 || mode == SplashScreenModeCMYK8);

}



TEST_F(SplashBitmapTest_1125, GetDataPtr_ReturnsNonNullPointer_1125) {

    EXPECT_NE(bitmap->getDataPtr(), nullptr);

}



TEST_F(SplashBitmapTest_1125, GetAlphaPtr_ReturnsNullPointerWhenNoAlpha_1125) {

    EXPECT_EQ(bitmap->getAlphaPtr(), nullptr);

}
