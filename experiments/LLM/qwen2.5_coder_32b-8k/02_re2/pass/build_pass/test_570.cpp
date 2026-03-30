#include <gtest/gtest.h>

#include "bitmap256.h"



using namespace re2;



class Bitmap256Test_570 : public ::testing::Test {

protected:

    Bitmap256 bitmap;

};



TEST_F(Bitmap256Test_570, FindNextSetBit_ReturnsCorrectIndex_570) {

    bitmap.Set(5);

    EXPECT_EQ(bitmap.FindNextSetBit(0), 5);

}



TEST_F(Bitmap256Test_570, FindNextSetBit_SkipsUnsetBits_570) {

    bitmap.Set(10);

    EXPECT_EQ(bitmap.FindNextSetBit(9), 10);

}



TEST_F(Bitmap256Test_570, FindNextSetBit_ReturnsNegativeOneIfNoBitsSet_570) {

    EXPECT_EQ(bitmap.FindNextSetBit(0), -1);

}



TEST_F(Bitmap256Test_570, FindNextSetBit_BoundaryCondition_StartOfRange_570) {

    bitmap.Set(0);

    EXPECT_EQ(bitmap.FindNextSetBit(0), 0);

}



TEST_F(Bitmap256Test_570, FindNextSetBit_BoundaryCondition_EndOfRange_570) {

    bitmap.Set(255);

    EXPECT_EQ(bitmap.FindNextSetBit(254), 255);

}



TEST_F(Bitmap256Test_570, FindNextSetBit_MultipleBitsSet_570) {

    bitmap.Set(10);

    bitmap.Set(20);

    bitmap.Set(30);

    EXPECT_EQ(bitmap.FindNextSetBit(11), 20);

}



TEST_F(Bitmap256Test_570, FindNextSetBit_SecondWord_570) {

    bitmap.Set(70); // Bit in the second word

    EXPECT_EQ(bitmap.FindNextSetBit(64), 70);

}



TEST_F(Bitmap256Test_570, FindNextSetBit_ThirdWord_570) {

    bitmap.Set(130); // Bit in the third word

    EXPECT_EQ(bitmap.FindNextSetBit(128), 130);

}



TEST_F(Bitmap256Test_570, FindNextSetBit_FourthWord_570) {

    bitmap.Set(200); // Bit in the fourth word

    EXPECT_EQ(bitmap.FindNextSetBit(192), 200);

}
