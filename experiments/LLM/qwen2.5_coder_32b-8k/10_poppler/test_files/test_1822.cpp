#include <gtest/gtest.h>

#include "JBIG2Stream.hh"  // Adjust the include path as necessary



using namespace std;



class JBIG2BitmapTest_1822 : public ::testing::Test {

protected:

    void SetUp() override {

        bitmap = make_unique<JBIG2Bitmap>(0, 10, 10);

    }



    unique_ptr<JBIG2Bitmap> bitmap;

};



TEST_F(JBIG2BitmapTest_1822, ConstructorWithDimensions_1822) {

    EXPECT_TRUE(bitmap->isOk());

}



TEST_F(JBIG2BitmapTest_1822, GetWidth_ReturnsCorrectValue_1822) {

    EXPECT_EQ(bitmap->getWidth(), 10);

}



TEST_F(JBIG2BitmapTest_1822, GetHeight_ReturnsCorrectValue_1822) {

    EXPECT_EQ(bitmap->getHeight(), 10);

}



TEST_F(JBIG2BitmapTest_1822, GetPixelPtr_OutOfBounds_ReturnsNullptr_1822) {

    JBIG2BitmapPtr* ptr = nullptr;

    bitmap->getPixelPtr(15, 15, &ptr);

    EXPECT_EQ(ptr, nullptr);

}



TEST_F(JBIG2BitmapTest_1822, SetAndClearPixel_ModifiesCorrectly_1822) {

    int x = 3, y = 4;

    bitmap->setPixel(x, y);

    EXPECT_NE(bitmap->getPixel(x, y), 0);



    bitmap->clearPixel(x, y);

    EXPECT_EQ(bitmap->getPixel(x, y), 0);

}



TEST_F(JBIG2BitmapTest_1822, ClearToZero_SetsAllPixelsToZero_1822) {

    bitmap->setPixel(3, 4);

    bitmap->clearToZero();

    for (int x = 0; x < bitmap->getWidth(); ++x) {

        for (int y = 0; y < bitmap->getHeight(); ++y) {

            EXPECT_EQ(bitmap->getPixel(x, y), 0);

        }

    }

}



TEST_F(JBIG2BitmapTest_1822, ClearToOne_SetsAllPixelsToOne_1822) {

    bitmap->clearToOne();

    for (int x = 0; x < bitmap->getWidth(); ++x) {

        for (int y = 0; y < bitmap->getHeight(); ++y) {

            EXPECT_NE(bitmap->getPixel(x, y), 0);

        }

    }

}



TEST_F(JBIG2BitmapTest_1822, GetSlice_OutOfBounds_ReturnsNullptr_1822) {

    auto slice = bitmap->getSlice(15, 15, 5, 5);

    EXPECT_EQ(slice.get(), nullptr);

}



TEST_F(JBIG2BitmapTest_1822, Expand_IncreasesHeightAndWidth_1822) {

    int originalHeight = bitmap->getHeight();

    int originalWidth = bitmap->getWidth();

    unsigned char pixel = 0;

    bitmap->expand(originalHeight + 5, pixel);

    EXPECT_EQ(bitmap->getHeight(), originalHeight + 5);

    // Assuming width does not change with expand

    EXPECT_EQ(bitmap->getWidth(), originalWidth);

}



TEST_F(JBIG2BitmapTest_1822, DuplicateRow_OutOfBounds_DoesNotThrow_1822) {

    bitmap->duplicateRow(15, 0);  // This should handle out-of-bounds gracefully

}



TEST_F(JBIG2BitmapTest_1822, Combine_OutOfBounds_DoesNotThrow_1822) {

    auto other = make_unique<JBIG2Bitmap>(0, 5, 5);

    bitmap->combine(*other.get(), 15, 15, 0);  // This should handle out-of-bounds gracefully

}
