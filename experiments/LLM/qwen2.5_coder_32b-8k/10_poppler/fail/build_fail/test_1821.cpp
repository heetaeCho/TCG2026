#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JBIG2Stream.cc"



using namespace testing;



class JBIG2BitmapTest_1821 : public ::testing::Test {

protected:

    JBIG2Bitmap* bitmap;

    const int width = 32;

    const int height = 32;

    const int lineSize = 4; // Assuming a byte per row



    void SetUp() override {

        bitmap = new JBIG2Bitmap(width, height);

    }



    void TearDown() override {

        delete bitmap;

    }

};



TEST_F(JBIG2BitmapTest_1821, GetDataSize_ReturnsCorrectSize_1821) {

    EXPECT_EQ(bitmap->getDataSize(), width * lineSize);

}



TEST_F(JBIG2BitmapTest_1821, GetWidth_ReturnsInitializedWidth_1821) {

    EXPECT_EQ(bitmap->getWidth(), width);

}



TEST_F(JBIG2BitmapTest_1821, GetHeight_ReturnsInitializedHeight_1821) {

    EXPECT_EQ(bitmap->getHeight(), height);

}



TEST_F(JBIG2BitmapTest_1821, GetLineSize_ReturnsCorrectLineSize_1821) {

    EXPECT_EQ(bitmap->getLineSize(), lineSize);

}



TEST_F(JBIG2BitmapTest_1821, IsOk_ReturnsTrueInitially_1821) {

    EXPECT_TRUE(bitmap->isOk());

}



TEST_F(JBIG2BitmapTest_1821, GetPixel_ReturnsZeroForUnsetPixel_1821) {

    EXPECT_EQ(bitmap->getPixel(0, 0), 0);

}



TEST_F(JBIG2BitmapTest_1821, SetAndClearPixel_OperatesCorrectly_1821) {

    bitmap->setPixel(0, 0);

    EXPECT_EQ(bitmap->getPixel(0, 0), 1);



    bitmap->clearPixel(0, 0);

    EXPECT_EQ(bitmap->getPixel(0, 0), 0);

}



TEST_F(JBIG2BitmapTest_1821, GetPixel_OutOfBounds_ReturnsZero_1821) {

    EXPECT_EQ(bitmap->getPixel(width, height), 0);

    EXPECT_EQ(bitmap->getPixel(-1, -1), 0);

}



TEST_F(JBIG2BitmapTest_1821, GetDataPtr_ReturnsNonNullPointer_1821) {

    EXPECT_NE(bitmap->getDataPtr(), nullptr);

}



TEST_F(JBIG2BitmapTest_1821, ClearToZero_SetsAllPixelsToZero_1821) {

    bitmap->setPixel(0, 0);

    bitmap->clearToZero();

    EXPECT_EQ(bitmap->getPixel(0, 0), 0);

}



TEST_F(JBIG2BitmapTest_1821, ClearToOne_SetsAllPixelsToOne_1821) {

    bitmap->clearToOne();

    EXPECT_EQ(bitmap->getPixel(0, 0), 1);

}



TEST_F(JBIG2BitmapTest_1821, GetSlice_ReturnsValidBitmap_1821) {

    auto slice = bitmap->getSlice(0, 0, width/2, height/2);

    EXPECT_NE(slice.get(), nullptr);

    EXPECT_EQ(slice->getWidth(), width/2);

    EXPECT_EQ(slice->getHeight(), height/2);

}



TEST_F(JBIG2BitmapTest_1821, GetSlice_OutOfBounds_ReturnsNullptr_1821) {

    auto slice = bitmap->getSlice(width, height, 0, 0);

    EXPECT_EQ(slice.get(), nullptr);

}
