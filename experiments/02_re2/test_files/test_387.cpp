#include <gtest/gtest.h>

#include "bitmap256.h"



using namespace re2;



class Bitmap256Test_387 : public ::testing::Test {

protected:

    Bitmap256 bitmap;

};



TEST_F(Bitmap256Test_387, ClearResetsAllBits_387) {

    bitmap.Set(0);

    bitmap.Set(63);

    bitmap.Clear();

    EXPECT_FALSE(bitmap.Test(0));

    EXPECT_FALSE(bitmap.Test(63));

}



TEST_F(Bitmap256Test_387, SetAndTestSpecificBit_387) {

    bitmap.Set(10);

    EXPECT_TRUE(bitmap.Test(10));

    EXPECT_FALSE(bitmap.Test(9));

    EXPECT_FALSE(bitmap.Test(11));

}



TEST_F(Bitmap256Test_387, FindNextSetBitReturnsCorrectPosition_387) {

    bitmap.Set(5);

    bitmap.Set(10);

    bitmap.Set(15);

    EXPECT_EQ(bitmap.FindNextSetBit(0), 5);

    EXPECT_EQ(bitmap.FindNextSetBit(5), 5);

    EXPECT_EQ(bitmap.FindNextSetBit(6), 10);

    EXPECT_EQ(bitmap.FindNextSetBit(10), 10);

    EXPECT_EQ(bitmap.FindNextSetBit(11), 15);

    EXPECT_EQ(bitmap.FindNextSetBit(16), -1);

}



TEST_F(Bitmap256Test_387, FindNextSetBitBoundaryConditions_387) {

    bitmap.Set(0);

    bitmap.Set(255);

    EXPECT_EQ(bitmap.FindNextSetBit(-1), 0);

    EXPECT_EQ(bitmap.FindNextSetBit(0), 0);

    EXPECT_EQ(bitmap.FindNextSetBit(1), -1);

    EXPECT_EQ(bitmap.FindNextSetBit(254), 255);

    EXPECT_EQ(bitmap.FindNextSetBit(255), 255);

    EXPECT_EQ(bitmap.FindNextSetBit(256), -1);

}



TEST_F(Bitmap256Test_387, FindNextSetBitNoBitsSet_387) {

    EXPECT_EQ(bitmap.FindNextSetBit(0), -1);

    EXPECT_EQ(bitmap.FindNextSetBit(255), -1);

}
