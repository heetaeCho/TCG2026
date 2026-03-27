#include <gtest/gtest.h>

#include "SplashBitmap.h"

#include <vector>



class SplashBitmapTest : public ::testing::Test {

protected:

    SplashBitmap* bitmap;



    void SetUp() override {

        // Create a sample SplashBitmap instance for testing

        const std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;

        bitmap = new SplashBitmap(10, 5, 2, static_cast<SplashColorMode>(0), true, false, &separationList);

    }



    void TearDown() override {

        // Clean up the SplashBitmap instance

        delete bitmap;

    }

};



TEST_F(SplashBitmapTest_1120, GetAlphaRowSize_ReturnsWidth_1120) {

    EXPECT_EQ(bitmap->getAlphaRowSize(), 10);

}



TEST_F(SplashBitmapTest_1120, GetWidth_ReturnsCorrectValue_1120) {

    EXPECT_EQ(bitmap->getWidth(), 10);

}



TEST_F(SplashBitmapTest_1120, GetHeight_ReturnsCorrectValue_1120) {

    EXPECT_EQ(bitmap->getHeight(), 5);

}



TEST_F(SplashBitmapTest_1120, GetRowSize_ReturnsExpectedValue_1120) {

    // Assuming rowSize is calculated as width + rowPad

    EXPECT_EQ(bitmap->getRowSize(), 12); 

}



TEST_F(SplashBitmapTest_1120, GetRowPad_ReturnsCorrectValue_1120) {

    EXPECT_EQ(bitmap->getRowPad(), 2);

}



TEST_F(SplashBitmapTest_1120, GetMode_ReturnsCorrectValue_1120) {

    EXPECT_EQ(static_cast<int>(bitmap->getMode()), 0);

}



// Assuming getAlphaPtr returns a valid pointer if alpha is enabled

TEST_F(SplashBitmapTest_1120, GetAlphaPtr_IsNotNull_1120) {

    EXPECT_NE(bitmap->getAlphaPtr(), nullptr);

}



// Assuming getDataPtr returns a valid pointer

TEST_F(SplashBitmapTest_1120, GetDataPtr_IsNotNull_1120) {

    EXPECT_NE(bitmap->getDataPtr(), nullptr);

}



// Assuming getSeparationList returns the same list passed in constructor

TEST_F(SplashBitmapTest_1120, GetSeparationList_ReturnsSamePointer_1120) {

    const std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;

    EXPECT_EQ(bitmap->getSeparationList(), &separationList);

}
