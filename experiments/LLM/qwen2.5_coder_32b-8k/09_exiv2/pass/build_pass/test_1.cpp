#include <gtest/gtest.h>

#include "exiv2/slice.hpp"



using namespace Exiv2::Internal;



class SliceBaseTest_1 : public ::testing::Test {

protected:

    SliceBase slice_;



    SliceBaseTest_1() : slice_(0, 10) {}

};



TEST_F(SliceBaseTest_1, SizeReturnsCorrectValue_1) {

    EXPECT_EQ(slice_.size(), 10);

}



TEST_F(SliceBaseTest_1, ZeroSizeSlice_1) {

    SliceBase zeroSizeSlice(5, 5);

    EXPECT_EQ(zeroSizeSlice.size(), 0);

}



TEST_F(SliceBaseTest_1, LargeRangeSlice_1) {

    SliceBase largeRangeSlice(0, 1000000);

    EXPECT_EQ(largeRangeSlice.size(), 1000000);

}
