#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/splash/SplashBitmap.h"



class SplashBitmapTest_1122 : public ::testing::Test {

protected:

    static constexpr int width = 10;

    static constexpr int height = 10;

    static constexpr int rowPad = 1;

    static constexpr bool alphaA = false;

    static constexpr bool topDown = true;



    SplashBitmap* splashBitmap;



    void SetUp() override {

        splashBitmap = new SplashBitmap(width, height, rowPad, SplashColorModeRGB8, alphaA, topDown, nullptr);

    }



    void TearDown() override {

        delete splashBitmap;

    }

};



TEST_F(SplashBitmapTest_1122, GetModeReturnsCorrectValue_1122) {

    EXPECT_EQ(splashBitmap->getMode(), SplashColorModeRGB8);

}



TEST_F(SplashBitmapTest_1122, GetWidthReturnsCorrectValue_1122) {

    EXPECT_EQ(splashBitmap->getWidth(), width);

}



TEST_F(SplashBitmapTest_1122, GetHeightReturnsCorrectValue_1122) {

    EXPECT_EQ(splashBitmap->getHeight(), height);

}



TEST_F(SplashBitmapTest_1122, GetRowPadReturnsCorrectValue_1122) {

    EXPECT_EQ(splashBitmap->getRowPad(), rowPad);

}



TEST_F(SplashBitmapTest_1122, GetDataPtrDoesNotReturnNull_1122) {

    EXPECT_NE(splashBitmap->getDataPtr(), nullptr);

}



TEST_F(SplashBitmapTest_1122, GetAlphaPtrReturnsNullWhenNoAlpha_1122) {

    EXPECT_EQ(splashBitmap->getAlphaPtr(), nullptr);

}



TEST_F(SplashBitmapTest_1122, CopyFunctionCreatesNewInstanceWithSameMode_1122) {

    auto copy = SplashBitmap::copy(splashBitmap);

    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(copy->getMode(), splashBitmap->getMode());

    delete copy;

}



TEST_F(SplashBitmapTest_1122, CopyFunctionCreatesNewInstanceWithSameWidth_1122) {

    auto copy = SplashBitmap::copy(splashBitmap);

    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(copy->getWidth(), splashBitmap->getWidth());

    delete copy;

}



TEST_F(SplashBitmapTest_1122, CopyFunctionCreatesNewInstanceWithSameHeight_1122) {

    auto copy = SplashBitmap::copy(splashBitmap);

    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(copy->getHeight(), splashBitmap->getHeight());

    delete copy;

}
