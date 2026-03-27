#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JBIG2Bitmap.h"



class JBIG2BitmapTest_1819 : public ::testing::Test {

protected:

    JBIG2Bitmap* bitmap;

    unsigned int width = 10;

    unsigned int height = 10;



    void SetUp() override {

        bitmap = new JBIG2Bitmap(width, height);

    }



    void TearDown() override {

        delete bitmap;

    }

};



TEST_F(JBIG2BitmapTest_1819, SetAndClearPixel_NormalOperation_1819) {

    int x = 5;

    int y = 5;

    bitmap->setPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, y), 1);



    bitmap->clearPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, y), 0);

}



TEST_F(JBIG2BitmapTest_1819, SetAndClearPixel_BoundaryConditions_1819) {

    // Upper boundary

    int x = width - 1;

    int y = height - 1;

    bitmap->setPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, y), 1);



    bitmap->clearPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, y), 0);



    // Lower boundary

    x = 0;

    y = 0;

    bitmap->setPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, y), 1);



    bitmap->clearPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, y), 0);

}



TEST_F(JBIG2BitmapTest_1819, SetAndClearPixel_OutOfBounds_NoEffect_1819) {

    int x = width;

    int y = height;



    bitmap->setPixel(x, y); // Out of bounds

    EXPECT_EQ(bitmap->getPixel(width - 1, height - 1), 0);



    bitmap->clearPixel(x, y); // Out of bounds

    EXPECT_EQ(bitmap->getPixel(width - 1, height - 1), 0);

}



TEST_F(JBIG2BitmapTest_1819, GetWidth_NormalOperation_1819) {

    EXPECT_EQ(bitmap->getWidth(), width);

}



TEST_F(JBIG2BitmapTest_1819, GetHeight_NormalOperation_1819) {

    EXPECT_EQ(bitmap->getHeight(), height);

}



TEST_F(JBIG2BitmapTest_1819, GetDataSize_NormalOperation_1819) {

    int expectedDataSize = (width + 7) / 8 * height;

    EXPECT_EQ(bitmap->getDataSize(), expectedDataSize);

}



TEST_F(JBIG2BitmapTest_1819, ClearToZero_AllZeros_1819) {

    bitmap->clearToZero();

    for (int y = 0; y < height; ++y) {

        for (int x = 0; x < width; ++x) {

            EXPECT_EQ(bitmap->getPixel(x, y), 0);

        }

    }

}



TEST_F(JBIG2BitmapTest_1819, ClearToOne_AllOnes_1819) {

    bitmap->clearToOne();

    for (int y = 0; y < height; ++y) {

        for (int x = 0; x < width; ++x) {

            EXPECT_EQ(bitmap->getPixel(x, y), 1);

        }

    }

}
