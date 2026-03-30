#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/splash/SplashBitmap.h"



class SplashBitmapTest_1124 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a SplashBitmap object with specific parameters for testing.

        bitmap = new SplashBitmap(10, 10, 0, splashModeRGB8, true, false, nullptr);

    }



    void TearDown() override {

        // Clean up the SplashBitmap object after each test.

        delete bitmap;

    }



    SplashBitmap* bitmap;

};



TEST_F(SplashBitmapTest_1124, GetAlphaPtr_ReturnsValidPointer_1124) {

    EXPECT_NE(bitmap->getAlphaPtr(), nullptr);

}



TEST_F(SplashBitmapTest_1124, GetWidth_ReturnsCorrectValue_1124) {

    EXPECT_EQ(bitmap->getWidth(), 10);

}



TEST_F(SplashBitmapTest_1124, GetHeight_ReturnsCorrectValue_1124) {

    EXPECT_EQ(bitmap->getHeight(), 10);

}



TEST_F(SplashBitmapTest_1124, GetRowSize_ReturnsNonNegativeValue_1124) {

    EXPECT_GE(bitmap->getRowSize(), 0);

}



TEST_F(SplashBitmapTest_1124, GetAlphaRowSize_ReturnsNonNegativeValue_1124) {

    EXPECT_GE(bitmap->getAlphaRowSize(), 0);

}



TEST_F(SplashBitmapTest_1124, GetRowPad_ReturnsCorrectValue_1124) {

    EXPECT_EQ(bitmap->getRowPad(), 0);

}



TEST_F(SplashBitmapTest_1124, GetMode_ReturnsCorrectValue_1124) {

    EXPECT_EQ(bitmap->getMode(), splashModeRGB8);

}



TEST_F(SplashBitmapTest_1124, GetDataPtr_ReturnsValidPointer_1124) {

    EXPECT_NE(bitmap->getDataPtr(), nullptr);

}



TEST_F(SplashBitmapTest_1124, GetAlpha_ReturnsValueInRange_1124) {

    for (int x = 0; x < bitmap->getWidth(); ++x) {

        for (int y = 0; y < bitmap->getHeight(); ++y) {

            EXPECT_GE(bitmap->getAlpha(x, y), 0);

            EXPECT_LE(bitmap->getAlpha(x, y), 255);

        }

    }

}



TEST_F(SplashBitmapTest_1124, GetSeparationList_ReturnsValidPointer_1124) {

    EXPECT_NE(bitmap->getSeparationList(), nullptr);

}
