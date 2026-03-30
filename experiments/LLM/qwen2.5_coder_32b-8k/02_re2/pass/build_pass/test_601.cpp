#include <gtest/gtest.h>

#include "bitmap256.h"



namespace re2 {

class Bitmap256Test_601 : public ::testing::Test {

protected:

    Bitmap256 bitmap_;

};



TEST_F(Bitmap256Test_601, ClearInitializesAllBitsToZero_601) {

    for (int i = 0; i < 256; ++i) {

        EXPECT_FALSE(bitmap_.Test(i));

    }

}



TEST_F(Bitmap256Test_601, SetAndTestBit_601) {

    bitmap_.Set(42);

    EXPECT_TRUE(bitmap_.Test(42));

    EXPECT_FALSE(bitmap_.Test(0));

}



TEST_F(Bitmap256Test_601, SetMultipleBits_601) {

    bitmap_.Set(0);

    bitmap_.Set(32);

    bitmap_.Set(255);



    EXPECT_TRUE(bitmap_.Test(0));

    EXPECT_TRUE(bitmap_.Test(32));

    EXPECT_TRUE(bitmap_.Test(255));



    for (int i = 1; i < 256; ++i) {

        if (i != 32 && i != 255) {

            EXPECT_FALSE(bitmap_.Test(i));

        }

    }

}



TEST_F(Bitmap256Test_601, FindNextSetBitOnEmptyBitmap_601) {

    EXPECT_EQ(bitmap_.FindNextSetBit(0), -1);

}



TEST_F(Bitmap256Test_601, FindNextSetBitAfterSettingSingleBit_601) {

    bitmap_.Set(42);

    EXPECT_EQ(bitmap_.FindNextSetBit(0), 42);

    EXPECT_EQ(bitmap_.FindNextSetBit(42), 42);

    EXPECT_EQ(bitmap_.FindNextSetBit(43), -1);

}



TEST_F(Bitmap256Test_601, FindNextSetBitAfterSettingMultipleBits_601) {

    bitmap_.Set(10);

    bitmap_.Set(20);

    bitmap_.Set(30);



    EXPECT_EQ(bitmap_.FindNextSetBit(0), 10);

    EXPECT_EQ(bitmap_.FindNextSetBit(11), 20);

    EXPECT_EQ(bitmap_.FindNextSetBit(21), 30);

    EXPECT_EQ(bitmap_.FindNextSetBit(31), -1);

}



TEST_F(Bitmap256Test_601, FindNextSetBitOnBoundaryConditions_601) {

    bitmap_.Set(0);

    bitmap_.Set(255);



    EXPECT_EQ(bitmap_.FindNextSetBit(0), 0);

    EXPECT_EQ(bitmap_.FindNextSetBit(1), -1);

    EXPECT_EQ(bitmap_.FindNextSetBit(254), 255);

    EXPECT_EQ(bitmap_.FindNextSetBit(256), -1);

}



TEST_F(Bitmap256Test_601, FindNextSetBitAcrossWordBoundary_601) {

    bitmap_.Set(63);

    bitmap_.Set(64);



    EXPECT_EQ(bitmap_.FindNextSetBit(63), 63);

    EXPECT_EQ(bitmap_.FindNextSetBit(64), 64);

}



TEST_F(Bitmap256Test_601, FindNextSetBitAfterClearingAllBits_601) {

    bitmap_.Set(10);

    bitmap_.Set(20);

    bitmap_.Clear();



    EXPECT_EQ(bitmap_.FindNextSetBit(0), -1);

}

}  // namespace re2
