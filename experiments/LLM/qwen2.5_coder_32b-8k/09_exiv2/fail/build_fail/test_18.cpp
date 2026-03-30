#include <gtest/gtest.h>

#include "exiv2/slice.hpp"



using namespace Exiv2;



class SliceTest_18 : public ::testing::Test {

protected:

    static const size_t dataSize = 5;

    int data[dataSize] = {0, 1, 2, 3, 4};

    Slice<int*> slice;

    

    void SetUp() override {

        slice = Slice<int*>(data, 0, dataSize);

    }

};



TEST_F(SliceTest_18, SubSliceNormalOperation_18) {

    auto sub = slice.subSlice(1, 3);

    EXPECT_EQ(sub.size(), 2);

    EXPECT_EQ(sub[0], 1);

    EXPECT_EQ(sub[1], 2);

}



TEST_F(SliceTest_18, SubSliceBoundaryStart_18) {

    auto sub = slice.subSlice(0, 2);

    EXPECT_EQ(sub.size(), 2);

    EXPECT_EQ(sub[0], 0);

    EXPECT_EQ(sub[1], 1);

}



TEST_F(SliceTest_18, SubSliceBoundaryEnd_18) {

    auto sub = slice.subSlice(3, dataSize);

    EXPECT_EQ(sub.size(), 2);

    EXPECT_EQ(sub[0], 3);

    EXPECT_EQ(sub[1], 4);

}



TEST_F(SliceTest_18, SubSliceEntireRange_18) {

    auto sub = slice.subSlice(0, dataSize);

    EXPECT_EQ(sub.size(), dataSize);

    for (size_t i = 0; i < dataSize; ++i) {

        EXPECT_EQ(sub[i], data[i]);

    }

}



TEST_F(SliceTest_18, SubSliceEmptyRange_18) {

    auto sub = slice.subSlice(2, 2);

    EXPECT_EQ(sub.size(), 0);

}



TEST_F(SliceTest_18, SubSliceInvalidRangeStartGreaterEnd_18) {

    EXPECT_THROW(slice.subSlice(3, 2), std::out_of_range);

}



TEST_F(SliceTest_18, SubSliceInvalidRangeStartOutOfBounds_18) {

    EXPECT_THROW(slice.subSlice(dataSize + 1, dataSize + 2), std::out_of_range);

}



TEST_F(SliceTest_18, SubSliceInvalidRangeEndOutOfBounds_18) {

    EXPECT_THROW(slice.subSlice(0, dataSize + 1), std::out_of_range);

}
