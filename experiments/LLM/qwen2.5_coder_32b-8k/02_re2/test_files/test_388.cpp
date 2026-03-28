#include <gtest/gtest.h>

#include "bitmap256.h"



namespace re2 {



class Bitmap256Test : public ::testing::Test {

protected:

    Bitmap256 bitmap;

};



TEST_F(Bitmap256Test_388, TestBitInitiallyFalse_388) {

    EXPECT_FALSE(bitmap.Test(0));

}



TEST_F(Bitmap256Test_388, SetAndTestBit_388) {

    bitmap.Set(0);

    EXPECT_TRUE(bitmap.Test(0));

}



TEST_F(Bitmap256Test_388, ClearAfterSet_388) {

    bitmap.Set(0);

    bitmap.Clear();

    EXPECT_FALSE(bitmap.Test(0));

}



TEST_F(Bitmap256Test_388, TestBoundaryValues_388) {

    EXPECT_FALSE(bitmap.Test(0));

    EXPECT_FALSE(bitmap.Test(255));



    bitmap.Set(0);

    bitmap.Set(255);



    EXPECT_TRUE(bitmap.Test(0));

    EXPECT_TRUE(bitmap.Test(255));

}



TEST_F(Bitmap256Test_388, TestNonSetBits_388) {

    for (int i = 1; i < 256; ++i) {

        EXPECT_FALSE(bitmap.Test(i)) << "Failed at bit position: " << i;

    }

}



TEST_F(Bitmap256Test_388, SetAndTestMultipleBits_388) {

    bitmap.Set(10);

    bitmap.Set(20);

    bitmap.Set(30);



    EXPECT_TRUE(bitmap.Test(10));

    EXPECT_TRUE(bitmap.Test(20));

    EXPECT_TRUE(bitmap.Test(30));

}



TEST_F(Bitmap256Test_388, ClearAfterSettingMultipleBits_388) {

    bitmap.Set(10);

    bitmap.Set(20);

    bitmap.Set(30);



    bitmap.Clear();



    EXPECT_FALSE(bitmap.Test(10));

    EXPECT_FALSE(bitmap.Test(20));

    EXPECT_FALSE(bitmap.Test(30));

}



TEST_F(Bitmap256Test_388, FindNextSetBitInitiallyNegative_388) {

    EXPECT_EQ(-1, bitmap.FindNextSetBit(0));

}



TEST_F(Bitmap256Test_388, FindNextSetBitAfterSettingBits_388) {

    bitmap.Set(5);

    EXPECT_EQ(5, bitmap.FindNextSetBit(0));



    bitmap.Set(15);

    EXPECT_EQ(5, bitmap.FindNextSetBit(0));

    EXPECT_EQ(15, bitmap.FindNextSetBit(6));



    bitmap.Clear();

    EXPECT_EQ(-1, bitmap.FindNextSetBit(0));

}



TEST_F(Bitmap256Test_388, FindNextSetBitAtBoundary_388) {

    bitmap.Set(255);

    EXPECT_EQ(255, bitmap.FindNextSetBit(255));

}



}  // namespace re2
