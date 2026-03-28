#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JBIG2Stream.h"



class JBIG2BitmapTest : public ::testing::Test {

protected:

    std::unique_ptr<JBIG2Bitmap> bitmap;



    void SetUp() override {

        bitmap = std::make_unique<JBIG2Bitmap>(10, 10);

    }

};



TEST_F(JBIG2BitmapTest_1813, GetTypeReturnsJBIG2SegBitmap_1813) {

    EXPECT_EQ(bitmap->getType(), jbig2SegBitmap);

}



TEST_F(JBIG2BitmapTest_1813, GetWidthAndHeightReturnCorrectValues_1813) {

    EXPECT_EQ(bitmap->getWidth(), 10);

    EXPECT_EQ(bitmap->getHeight(), 10);

}



TEST_F(JBIG2BitmapTest_1813, ClearToZeroSetsAllPixelsToZero_1813) {

    bitmap->setPixel(5, 5);

    bitmap->clearToZero();

    EXPECT_EQ(bitmap->getPixel(5, 5), 0);

}



TEST_F(JBIG2BitmapTest_1813, ClearToOneSetsAllPixelsToOne_1813) {

    bitmap->clearToOne();

    EXPECT_EQ(bitmap->getPixel(5, 5), 1);

}



TEST_F(JBIG2BitmapTest_1813, SetAndClearPixelWorkCorrectly_1813) {

    bitmap->setPixel(5, 5);

    EXPECT_EQ(bitmap->getPixel(5, 5), 1);



    bitmap->clearPixel(5, 5);

    EXPECT_EQ(bitmap->getPixel(5, 5), 0);

}



TEST_F(JBIG2BitmapTest_1813, GetSliceReturnsCorrectSizeBitmap_1813) {

    auto slice = bitmap->getSlice(2, 2, 4, 4);

    EXPECT_EQ(slice->getWidth(), 4);

    EXPECT_EQ(slice->getHeight(), 4);

}



TEST_F(JBIG2BitmapTest_1813, ExpandIncreasesHeightAndFillsWithPixelValue_1813) {

    bitmap->expand(15, 0xFF);

    EXPECT_EQ(bitmap->getHeight(), 15);

    // Assuming expand fills new rows with the pixel value

    for (int y = 10; y < 15; ++y) {

        for (int x = 0; x < 10; ++x) {

            EXPECT_EQ(bitmap->getPixel(x, y), 1);

        }

    }

}



TEST_F(JBIG2BitmapTest_1813, DuplicateRowDuplicatesCorrectly_1813) {

    bitmap->setPixel(5, 3);

    bitmap->duplicateRow(4, 3);

    EXPECT_EQ(bitmap->getPixel(5, 4), 1);

}



TEST_F(JBIG2BitmapTest_1813, CombineSetsPixelsAccordingToCombOp_1813) {

    auto other = std::make_unique<JBIG2Bitmap>(10, 10);

    other->setPixel(5, 5);



    bitmap->combine(*other, 0, 0, 0); // Assuming combOp 0 is OR

    EXPECT_EQ(bitmap->getPixel(5, 5), 1);



    other->clearToZero();

    other->setPixel(5, 6);

    bitmap->combine(*other, 0, 0, 2); // Assuming combOp 2 is AND

    EXPECT_EQ(bitmap->getPixel(5, 6), 0);

}



TEST_F(JBIG2BitmapTest_1813, IsOkReturnsTrueForValidBitmap_1813) {

    EXPECT_TRUE(bitmap->isOk());

}
