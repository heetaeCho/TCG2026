#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"

#include <vector>



using namespace Exiv2::Internal;



struct MockStorage {

    std::vector<int> data_;

    MockStorage(std::vector<int>& data, size_t begin, size_t end) : data_(data.begin() + begin, data.begin() + end) {}

};



using TestSlice = ConstSliceBase<MockStorage, int>;



class SliceTest_6 : public ::testing::Test {

protected:

    std::vector<int> data_{1, 2, 3, 4, 5};

    TestSlice slice_;

    

    SliceTest_6() : slice_(data_, 0, data_.size()) {}

};



TEST_F(SliceTest_6, SubSliceNormalOperation_6) {

    auto subslice = slice_.subSlice(1, 4);

    EXPECT_EQ(subslice.cbegin(), slice_.cbegin() + 1);

    EXPECT_EQ(subslice.cend(), slice_.cend() - 1);

}



TEST_F(SliceTest_6, SubSliceBoundaryConditionsStart_6) {

    auto subslice = slice_.subSlice(0, 1);

    EXPECT_EQ(subslice.cbegin(), slice_.cbegin());

    EXPECT_EQ(subslice.cend(), slice_.cbegin() + 1);

}



TEST_F(SliceTest_6, SubSliceBoundaryConditionsEnd_6) {

    auto subslice = slice_.subSlice(data_.size() - 1, data_.size());

    EXPECT_EQ(subslice.cbegin(), slice_.cend() - 1);

    EXPECT_EQ(subslice.cend(), slice_.cend());

}



TEST_F(SliceTest_6, SubSliceFullRange_6) {

    auto subslice = slice_.subSlice(0, data_.size());

    EXPECT_EQ(subslice.cbegin(), slice_.cbegin());

    EXPECT_EQ(subslice.cend(), slice_.cend());

}



TEST_F(SliceTest_6, SubSliceOutOfLowerBound_6) {

    EXPECT_THROW(slice_.subSlice(-1, 3), std::out_of_range);

}



TEST_F(SliceTest_6, SubSliceOutOfUpperBound_6) {

    EXPECT_THROW(slice_.subSlice(0, data_.size() + 1), std::out_of_range);

}



TEST_F(SliceTest_6, SubSliceInvalidRange_6) {

    EXPECT_THROW(slice_.subSlice(3, 2), std::out_of_range);

}
