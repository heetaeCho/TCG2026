#include <gtest/gtest.h>

#include "JBIG2Stream.h"



class JBIG2BitmapTest_1818 : public ::testing::Test {

protected:

    void SetUp() override {

        bitmap = std::make_unique<JBIG2Bitmap>(10, 10); // Example dimensions

    }



    std::unique_ptr<JBIG2Bitmap> bitmap;

};



TEST_F(JBIG2BitmapTest_1818, SetPixelAndGetPixel_NormalOperation_1818) {

    int x = 3;

    int y = 4;

    bitmap->setPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, y), 1);

}



TEST_F(JBIG2BitmapTest_1818, SetPixelBoundary_TopLeftCorner_1818) {

    int x = 0;

    int y = 0;

    bitmap->setPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, y), 1);

}



TEST_F(JBIG2BitmapTest_1818, SetPixelBoundary_BottomRightCorner_1818) {

    int x = 9;

    int y = 9;

    bitmap->setPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, y), 1);

}



TEST_F(JBIG2BitmapTest_1818, SetPixel_OutOfBounds_XNegative_1818) {

    int x = -1;

    int y = 5;

    bitmap->setPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(0, y), 0); // Ensure no change at boundary

}



TEST_F(JBIG2BitmapTest_1818, SetPixel_OutOfBounds_XTooLarge_1818) {

    int x = 10;

    int y = 5;

    bitmap->setPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(9, y), 0); // Ensure no change at boundary

}



TEST_F(JBIG2BitmapTest_1818, SetPixel_OutOfBounds_YNegative_1818) {

    int x = 5;

    int y = -1;

    bitmap->setPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, 0), 0); // Ensure no change at boundary

}



TEST_F(JBIG2BitmapTest_1818, SetPixel_OutOfBounds_YTooLarge_1818) {

    int x = 5;

    int y = 10;

    bitmap->setPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, 9), 0); // Ensure no change at boundary

}



TEST_F(JBIG2BitmapTest_1818, ClearPixelAndGetPixel_NormalOperation_1818) {

    int x = 3;

    int y = 4;

    bitmap->setPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, y), 1);

    bitmap->clearPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, y), 0);

}



TEST_F(JBIG2BitmapTest_1818, GetWidth_NormalOperation_1818) {

    EXPECT_EQ(bitmap->getWidth(), 10);

}



TEST_F(JBIG2BitmapTest_1818, GetHeight_NormalOperation_1818) {

    EXPECT_EQ(bitmap->getHeight(), 10);

}



TEST_F(JBIG2BitmapTest_1818, IsOk_NormalOperation_1818) {

    EXPECT_TRUE(bitmap->isOk());

}
