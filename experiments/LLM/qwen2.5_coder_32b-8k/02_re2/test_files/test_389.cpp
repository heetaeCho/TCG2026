#include <gtest/gtest.h>

#include "re2/bitmap256.h"



namespace {



class Bitmap256Test_389 : public ::testing::Test {

protected:

    re2::Bitmap256 bitmap_;

};



TEST_F(Bitmap256Test_389, SetAndGetNormalOperation_389) {

    bitmap_.Set(0);

    EXPECT_TRUE(bitmap_.Test(0));

    

    bitmap_.Set(255);

    EXPECT_TRUE(bitmap_.Test(255));

}



TEST_F(Bitmap256Test_389, SetBoundaryConditions_389) {

    bitmap_.Set(0);

    EXPECT_TRUE(bitmap_.Test(0));



    bitmap_.Set(255);

    EXPECT_TRUE(bitmap_.Test(255));

}



TEST_F(Bitmap256Test_389, FindNextSetBitNormalOperation_389) {

    bitmap_.Set(10);

    EXPECT_EQ(bitmap_.FindNextSetBit(0), 10);



    bitmap_.Set(50);

    EXPECT_EQ(bitmap_.FindNextSetBit(10), 50);

}



TEST_F(Bitmap256Test_389, FindNextSetBitBoundaryConditions_389) {

    bitmap_.Set(0);

    EXPECT_EQ(bitmap_.FindNextSetBit(0), 0);



    bitmap_.Clear();

    EXPECT_EQ(bitmap_.FindNextSetBit(0), -1);



    bitmap_.Set(255);

    EXPECT_EQ(bitmap_.FindNextSetBit(254), 255);

}



TEST_F(Bitmap256Test_389, ClearOperation_389) {

    bitmap_.Set(50);

    EXPECT_TRUE(bitmap_.Test(50));



    bitmap_.Clear();

    EXPECT_FALSE(bitmap_.Test(50));

}



}  // namespace
