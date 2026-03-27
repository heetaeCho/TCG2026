#include <gtest/gtest.h>

#include "JBIG2Stream.cc"



class JBIG2BitmapTest_1815 : public ::testing::Test {

protected:

    void SetUp() override {

        bitmap = std::make_unique<JBIG2Bitmap>(10, 10);

    }



    std::unique_ptr<JBIG2Bitmap> bitmap;

};



TEST_F(JBIG2BitmapTest_1815, GetHeight_ReturnsCorrectHeight_1815) {

    EXPECT_EQ(bitmap->getHeight(), 10);

}



TEST_F(JBIG2BitmapTest_1815, GetWidth_ReturnsCorrectWidth_1815) {

    EXPECT_EQ(bitmap->getWidth(), 10);

}



TEST_F(JBIG2BitmapTest_1815, IsOk_ReturnsTrueInitially_1815) {

    EXPECT_TRUE(bitmap->isOk());

}



TEST_F(JBIG2BitmapTest_1815, GetLineSize_ReturnsCorrectSize_1815) {

    // Assuming each line is 1 byte per pixel and no padding

    EXPECT_EQ(bitmap->getLineSize(), 10);

}



TEST_F(JBIG2BitmapTest_1815, SetAndGetPixel_WorksAsExpected_1815) {

    bitmap->setPixel(3, 4);

    EXPECT_EQ(bitmap->getPixel(3, 4), 1);



    bitmap->clearPixel(3, 4);

    EXPECT_EQ(bitmap->getPixel(3, 4), 0);

}



TEST_F(JBIG2BitmapTest_1815, ClearToZero_SetsAllPixelsToZero_1815) {

    bitmap->setPixel(1, 1);

    bitmap->clearToZero();

    EXPECT_EQ(bitmap->getPixel(1, 1), 0);

}



TEST_F(JBIG2BitmapTest_1815, ClearToOne_SetsAllPixelsToOne_1815) {

    bitmap->clearToOne();

    EXPECT_EQ(bitmap->getPixel(9, 9), 1);

}



TEST_F(JBIG2BitmapTest_1815, GetSlice_ReturnsCorrectSize_1815) {

    auto slice = bitmap->getSlice(0, 0, 5, 5);

    EXPECT_EQ(slice->getWidth(), 5);

    EXPECT_EQ(slice->getHeight(), 5);

}



TEST_F(JBIG2BitmapTest_1815, GetPixelPtr_ReturnsValidPointer_1815) {

    JBIG2BitmapPtr ptr;

    bitmap->getPixelPtr(0, 0, &ptr);

    EXPECT_NE(ptr.p, nullptr);

}



TEST_F(JBIG2BitmapTest_1815, NextPixel_IncrementsPointerCorrectly_1815) {

    JBIG2BitmapPtr ptr;

    bitmap->getPixelPtr(0, 0, &ptr);

    int pixel = bitmap->nextPixel(&ptr);

    EXPECT_EQ(pixel, 0); // Assuming initial pixels are zero

}



TEST_F(JBIG2BitmapTest_1815, DuplicateRow_DuplicatesCorrectly_1815) {

    bitmap->setPixel(3, 4);

    bitmap->duplicateRow(5, 4);

    EXPECT_EQ(bitmap->getPixel(3, 5), 1);

}



TEST_F(JBIG2BitmapTest_1815, Combine_SetsPixelsAccordingToCombOp_1815) {

    auto other = std::make_unique<JBIG2Bitmap>(10, 10);

    other->setPixel(3, 4);



    bitmap->combine(*other, 0, 0, 0); // Assuming combOp 0 is OR operation

    EXPECT_EQ(bitmap->getPixel(3, 4), 1);

}



TEST_F(JBIG2BitmapTest_1815, GetDataPtr_ReturnsValidPointer_1815) {

    unsigned char* data = bitmap->getDataPtr();

    EXPECT_NE(data, nullptr);

}



TEST_F(JBIG2BitmapTest_1815, GetDataSize_ReturnsCorrectSize_1815) {

    EXPECT_EQ(bitmap->getDataSize(), 10 * 1); // Assuming 1 byte per row

}
