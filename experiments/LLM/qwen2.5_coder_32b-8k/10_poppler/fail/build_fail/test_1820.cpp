#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JBIG2Stream.h"



class JBIG2BitmapTest_1820 : public ::testing::Test {

protected:

    JBIG2Bitmap* bitmap;



    void SetUp() override {

        bitmap = new JBIG2Bitmap(1, 10, 10); // segNumA, wA, hA

    }



    void TearDown() override {

        delete bitmap;

    }

};



TEST_F(JBIG2BitmapTest_1820, GetDataPtr_ReturnsValidPointer_1820) {

    EXPECT_NE(bitmap->getDataPtr(), nullptr);

}



TEST_F(JBIG2BitmapTest_1820, GetWidth_ReturnsCorrectValue_1820) {

    EXPECT_EQ(bitmap->getWidth(), 10);

}



TEST_F(JBIG2BitmapTest_1820, GetHeight_ReturnsCorrectValue_1820) {

    EXPECT_EQ(bitmap->getHeight(), 10);

}



TEST_F(JBIG2BitmapTest_1820, GetDataSize_ReturnsCorrectValue_1820) {

    EXPECT_EQ(bitmap->getDataSize(), ((10 + 7) / 8) * 10); // line size * height

}



TEST_F(JBIG2BitmapTest_1820, IsOk_ReturnsTrueInitially_1820) {

    EXPECT_TRUE(bitmap->isOk());

}



TEST_F(JBIG2BitmapTest_1820, SetAndClearPixel_ModifyBitmapCorrectly_1820) {

    bitmap->clearToZero();

    bitmap->setPixel(3, 4);

    EXPECT_EQ(bitmap->getPixel(3, 4), 1);



    bitmap->clearPixel(3, 4);

    EXPECT_EQ(bitmap->getPixel(3, 4), 0);

}



TEST_F(JBIG2BitmapTest_1820, ClearToZero_SetsAllPixelsToZero_1820) {

    bitmap->setPixel(5, 5);

    bitmap->clearToZero();

    for (int x = 0; x < bitmap->getWidth(); ++x) {

        for (int y = 0; y < bitmap->getHeight(); ++y) {

            EXPECT_EQ(bitmap->getPixel(x, y), 0);

        }

    }

}



TEST_F(JBIG2BitmapTest_1820, ClearToOne_SetsAllPixelsToOne_1820) {

    bitmap->clearToOne();

    for (int x = 0; x < bitmap->getWidth(); ++x) {

        for (int y = 0; y < bitmap->getHeight(); ++y) {

            EXPECT_EQ(bitmap->getPixel(x, y), 1);

        }

    }

}



TEST_F(JBIG2BitmapTest_1820, GetSlice_ReturnsValidPointer_1820) {

    auto slice = bitmap->getSlice(0, 0, 5, 5);

    EXPECT_NE(slice.get(), nullptr);

    EXPECT_EQ(slice->getWidth(), 5);

    EXPECT_EQ(slice->getHeight(), 5);

}



TEST_F(JBIG2BitmapTest_1820, GetSlice_OutOfBounds_ReturnsEmptyPointer_1820) {

    auto slice = bitmap->getSlice(9, 9, 2, 2); // Out of bounds

    EXPECT_EQ(slice.get(), nullptr);

}



TEST_F(JBIG2BitmapTest_1820, Expand_IncreasesHeightCorrectly_1820) {

    int originalHeight = bitmap->getHeight();

    bitmap->expand(originalHeight + 5, 0);

    EXPECT_EQ(bitmap->getHeight(), originalHeight + 5);

}



TEST_F(JBIG2BitmapTest_1820, DuplicateRow_DuplicatesCorrectly_1820) {

    bitmap->setPixel(3, 4);

    bitmap->duplicateRow(5, 4);

    EXPECT_EQ(bitmap->getPixel(3, 4), bitmap->getPixel(3, 5));

}



TEST_F(JBIG2BitmapTest_1820, Combine_MergesBitmapsCorrectly_1820) {

    JBIG2Bitmap otherBitmap(1, 10, 10);

    otherBitmap.setPixel(3, 4);



    bitmap->combine(otherBitmap, 0, 0, 0); // Assuming combOp = 0 (or operator)

    EXPECT_EQ(bitmap->getPixel(3, 4), 1);

}
