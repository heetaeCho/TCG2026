#include <gtest/gtest.h>

#include "JBIG2Stream.cc"



class JBIG2BitmapTest : public ::testing::Test {

protected:

    std::unique_ptr<JBIG2Bitmap> bitmap;



    void SetUp() override {

        bitmap = std::make_unique<JBIG2Bitmap>(10, 15);

    }

};



TEST_F(JBIG2BitmapTest_1814, GetWidth_ReturnsCorrectValue_1814) {

    EXPECT_EQ(bitmap->getWidth(), 10);

}



TEST_F(JBIG2BitmapTest_1814, GetHeight_ReturnsCorrectValue_1814) {

    EXPECT_EQ(bitmap->getHeight(), 15);

}



TEST_F(JBIG2BitmapTest_1814, GetDataSize_ReturnsPositiveValue_1814) {

    EXPECT_GT(bitmap->getDataSize(), 0);

}



TEST_F(JBIG2BitmapTest_1814, IsOk_ReturnsTrueForValidBitmap_1814) {

    EXPECT_TRUE(bitmap->isOk());

}



TEST_F(JBIG2BitmapTest_1814, GetPixelPtr_SetsPointerCorrectly_1814) {

    JBIG2BitmapPtr ptr;

    bitmap->getPixelPtr(0, 0, &ptr);

    EXPECT_NE(ptr, nullptr);

}



TEST_F(JBIG2BitmapTest_1814, NextPixel_ReturnsValidValue_1814) {

    JBIG2BitmapPtr ptr;

    bitmap->getPixelPtr(0, 0, &ptr);

    int pixel = bitmap->nextPixel(&ptr);

    EXPECT_NE(pixel, jbig2HuffmanOOB);

    EXPECT_NE(pixel, jbig2HuffmanLOW);

    EXPECT_NE(pixel, jbig2HuffmanEOT);

}



TEST_F(JBIG2BitmapTest_1814, SetAndClearPixel_ModifiesPixelCorrectly_1814) {

    bitmap->setPixel(0, 0);

    EXPECT_EQ(bitmap->getPixel(0, 0), 1);



    bitmap->clearPixel(0, 0);

    EXPECT_EQ(bitmap->getPixel(0, 0), 0);

}



TEST_F(JBIG2BitmapTest_1814, ClearToZero_SetsAllPixelsToZero_1814) {

    bitmap->setPixel(0, 0);

    bitmap->clearToZero();

    EXPECT_EQ(bitmap->getPixel(0, 0), 0);

}



TEST_F(JBIG2BitmapTest_1814, ClearToOne_SetsAllPixelsToOne_1814) {

    bitmap->clearToOne();

    EXPECT_EQ(bitmap->getPixel(0, 0), 1);

}



TEST_F(JBIG2BitmapTest_1814, GetSlice_ReturnsValidBitmap_1814) {

    auto slice = bitmap->getSlice(0, 0, 5, 5);

    EXPECT_NE(slice, nullptr);

    EXPECT_EQ(slice->getWidth(), 5);

    EXPECT_EQ(slice->getHeight(), 5);

}



TEST_F(JBIG2BitmapTest_1814, Expand_IncreasesHeight_1814) {

    int originalHeight = bitmap->getHeight();

    bitmap->expand(20, 0);

    EXPECT_GT(bitmap->getHeight(), originalHeight);

}



TEST_F(JBIG2BitmapTest_1814, DuplicateRow_CopiesRowCorrectly_1814) {

    bitmap->setPixel(5, 0);

    bitmap->duplicateRow(1, 0);

    EXPECT_EQ(bitmap->getPixel(5, 1), 1);

}



TEST_F(JBIG2BitmapTest_1814, Combine_MergesBitmapsCorrectly_1814) {

    auto otherBitmap = std::make_unique<JBIG2Bitmap>(10, 15);

    otherBitmap->setPixel(5, 5);



    bitmap->combine(*otherBitmap, 0, 0, 0);

    EXPECT_EQ(bitmap->getPixel(5, 5), 1);

}



TEST_F(JBIG2BitmapTest_1814, GetLineSize_ReturnsPositiveValue_1814) {

    EXPECT_GT(bitmap->getLineSize(), 0);

}
