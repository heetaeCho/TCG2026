#include <gtest/gtest.h>

#include "JBIG2Stream.h"



class JBIG2BitmapTest_1817 : public ::testing::Test {

protected:

    JBIG2Bitmap* bitmap;



    void SetUp() override {

        bitmap = new JBIG2Bitmap(3, 3); // Create a 3x3 bitmap for testing

        bitmap->clearToZero();

    }



    void TearDown() override {

        delete bitmap;

    }

};



TEST_F(JBIG2BitmapTest_1817, GetPixel_DefaultValueIsZero_1817) {

    EXPECT_EQ(bitmap->getPixel(0, 0), 0);

}



TEST_F(JBIG2BitmapTest_1817, SetAndClearPixel_TogglesCorrectly_1817) {

    bitmap->setPixel(0, 0);

    EXPECT_EQ(bitmap->getPixel(0, 0), 1);



    bitmap->clearPixel(0, 0);

    EXPECT_EQ(bitmap->getPixel(0, 0), 0);

}



TEST_F(JBIG2BitmapTest_1817, GetPixel_OutOfBoundsReturnsZero_1817) {

    EXPECT_EQ(bitmap->getPixel(-1, 0), 0);

    EXPECT_EQ(bitmap->getPixel(0, -1), 0);

    EXPECT_EQ(bitmap->getPixel(3, 0), 0);

    EXPECT_EQ(bitmap->getPixel(0, 3), 0);

}



TEST_F(JBIG2BitmapTest_1817, ClearToZero_SetsAllPixelsToZero_1817) {

    bitmap->setPixel(0, 0);

    bitmap->clearToZero();

    for (int x = 0; x < 3; ++x) {

        for (int y = 0; y < 3; ++y) {

            EXPECT_EQ(bitmap->getPixel(x, y), 0);

        }

    }

}



TEST_F(JBIG2BitmapTest_1817, ClearToOne_SetsAllPixelsToOne_1817) {

    bitmap->clearToOne();

    for (int x = 0; x < 3; ++x) {

        for (int y = 0; y < 3; ++y) {

            EXPECT_EQ(bitmap->getPixel(x, y), 1);

        }

    }

}
