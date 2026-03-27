#include <gtest/gtest.h>

#include "exiv2/slice.hpp"



using namespace Exiv2;



class SliceTest_16 : public ::testing::Test {

protected:

    std::vector<int> data = {1, 2, 3, 4, 5};

    Slice<std::vector<int>> slice;

    

    void SetUp() override {

        slice = Slice<std::vector<int>>(data.data(), 0, data.size());

    }

};



TEST_F(SliceTest_16, SubSliceNormalOperation_16) {

    auto subSlice = slice.subSlice(1, 4);

    EXPECT_EQ(subSlice.begin(), 1u);

    EXPECT_EQ(subSlice.end(), 4u);

}



TEST_F(SliceTest_16, SubSliceBoundaryStart_16) {

    auto subSlice = slice.subSlice(0, 3);

    EXPECT_EQ(subSlice.begin(), 0u);

    EXPECT_EQ(subSlice.end(), 3u);

}



TEST_F(SliceTest_16, SubSliceBoundaryEnd_16) {

    auto subSlice = slice.subSlice(2, 5);

    EXPECT_EQ(subSlice.begin(), 2u);

    EXPECT_EQ(subSlice.end(), 5u);

}



TEST_F(SliceTest_16, SubSliceFullRange_16) {

    auto subSlice = slice.subSlice(0, data.size());

    EXPECT_EQ(subSlice.begin(), 0u);

    EXPECT_EQ(subSlice.end(), data.size());

}



TEST_F(SliceTest_16, SubSliceEmptySlice_16) {

    auto subSlice = slice.subSlice(2, 2);

    EXPECT_EQ(subSlice.begin(), 2u);

    EXPECT_EQ(subSlice.end(), 2u);

}



TEST_F(SliceTest_16, SubSliceInvalidRange_16) {

    EXPECT_THROW(slice.subSlice(3, 2), std::invalid_argument);

}



TEST_F(SliceTest_16, SubSliceOutofBoundsStart_16) {

    EXPECT_THROW(slice.subSlice(data.size() + 1, data.size() + 2), std::out_of_range);

}



TEST_F(SliceTest_16, SubSliceOutofBoundsEnd_16) {

    EXPECT_THROW(slice.subSlice(0, data.size() + 1), std::out_of_range);

}
