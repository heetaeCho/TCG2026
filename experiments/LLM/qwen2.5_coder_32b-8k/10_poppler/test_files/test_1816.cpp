#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JBIG2Stream.h"



using namespace testing;



class JBIG2BitmapTest_1816 : public Test {

protected:

    std::unique_ptr<JBIG2Bitmap> bitmap;



    void SetUp() override {

        bitmap = std::make_unique<JBIG2Bitmap>(1, 100, 100); // Example setup with a 100x100 bitmap

    }

};



TEST_F(JBIG2BitmapTest_1816, GetLineSize_ReturnsCorrectValue_1816) {

    int lineSize = bitmap->getLineSize();

    EXPECT_EQ(lineSize, 1); // Assuming the line size is correctly initialized to 1 in the constructor

}



TEST_F(JBIG2BitmapTest_1816, GetWidth_ReturnsCorrectValue_1816) {

    int width = bitmap->getWidth();

    EXPECT_EQ(width, 100);

}



TEST_F(JBIG2BitmapTest_1816, GetHeight_ReturnsCorrectValue_1816) {

    int height = bitmap->getHeight();

    EXPECT_EQ(height, 100);

}



TEST_F(JBIG2BitmapTest_1816, GetDataSize_ReturnsNonNegativeValue_1816) {

    int dataSize = bitmap->getDataSize();

    EXPECT_GE(dataSize, 0);

}



TEST_F(JBIG2BitmapTest_1816, IsOk_ReturnsTrueInitially_1816) {

    bool isOk = bitmap->isOk();

    EXPECT_TRUE(isOk);

}



TEST_F(JBIG2BitmapTest_1816, GetPixel_OutOfBounds_ReturnsZero_1816) {

    int pixelValue = bitmap->getPixel(150, 150); // Out of bounds access

    EXPECT_EQ(pixelValue, 0);

}



TEST_F(JBIG2BitmapTest_1816, SetPixelAndGetPixel_NormalOperation_1816) {

    bitmap->setPixel(10, 10);

    int pixelValue = bitmap->getPixel(10, 10);

    EXPECT_EQ(pixelValue, 1);

}



TEST_F(JBIG2BitmapTest_1816, ClearPixelAndGetPixel_NormalOperation_1816) {

    bitmap->setPixel(10, 10);

    bitmap->clearPixel(10, 10);

    int pixelValue = bitmap->getPixel(10, 10);

    EXPECT_EQ(pixelValue, 0);

}



TEST_F(JBIG2BitmapTest_1816, ClearToZero_AllPixelsSetToOne_1816) {

    for (int x = 0; x < 100; ++x) {

        for (int y = 0; y < 100; ++y) {

            bitmap->setPixel(x, y);

        }

    }

    bitmap->clearToZero();

    for (int x = 0; x < 100; ++x) {

        for (int y = 0; y < 100; ++y) {

            EXPECT_EQ(bitmap->getPixel(x, y), 0);

        }

    }

}



TEST_F(JBIG2BitmapTest_1816, ClearToOne_AllPixelsSetToZero_1816) {

    bitmap->clearToOne();

    for (int x = 0; x < 100; ++x) {

        for (int y = 0; y < 100; ++y) {

            EXPECT_EQ(bitmap->getPixel(x, y), 1);

        }

    }

}



TEST_F(JBIG2BitmapTest_1816, Expand_HeightIncreased_PixelValuePreserved_1816) {

    bitmap->setPixel(10, 10);

    int originalHeight = bitmap->getHeight();

    bitmap->expand(originalHeight + 50, 0); // Expanding height by 50 pixels

    EXPECT_EQ(bitmap->getHeight(), originalHeight + 50);

    EXPECT_EQ(bitmap->getPixel(10, 10), 1); // Original pixel value should be preserved

}



TEST_F(JBIG2BitmapTest_1816, GetSlice_OutOfBounds_ReturnsNullptr_1816) {

    auto slice = bitmap->getSlice(150, 150, 10, 10); // Out of bounds access

    EXPECT_EQ(slice.get(), nullptr);

}



TEST_F(JBIG2BitmapTest_1816, GetSlice_NormalOperation_ReturnsValidBitmap_1816) {

    auto slice = bitmap->getSlice(10, 10, 50, 50); // Valid slice within bounds

    EXPECT_NE(slice.get(), nullptr);

    EXPECT_EQ(slice->getWidth(), 50);

    EXPECT_EQ(slice->getHeight(), 50);

}
