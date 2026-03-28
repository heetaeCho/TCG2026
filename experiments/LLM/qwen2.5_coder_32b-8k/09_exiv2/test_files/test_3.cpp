#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"



namespace {



using namespace Exiv2::Internal;



class ConstSliceBaseTest_3 : public ::testing::Test {

protected:

    std::vector<int> data = {10, 20, 30, 40, 50};

    ConstSliceBase<std::vector, int> sliceBase;



    ConstSliceBaseTest_3() : sliceBase(data, 1, 4) {}

};



TEST_F(ConstSliceBaseTest_3, At_ReturnsCorrectElement_3) {

    EXPECT_EQ(sliceBase.at(0), 20);

    EXPECT_EQ(sliceBase.at(1), 30);

    EXPECT_EQ(sliceBase.at(2), 40);

}



TEST_F(ConstSliceBaseTest_3, At_OutOfRangeThrows_3) {

    EXPECT_THROW(sliceBase.at(3), std::out_of_range);

    EXPECT_THROW(sliceBase.at(-1), std::out_of_range);

}



TEST_F(ConstSliceBaseTest_3, Size_ReturnsCorrectSize_3) {

    EXPECT_EQ(sliceBase.size(), 3);

}



TEST_F(ConstSliceBaseTest_3, SubSlice_ReturnsCorrectSubslice_3) {

    auto subslice = sliceBase.subSlice(1, 2);

    EXPECT_EQ(subslice.at(0), 30);

    EXPECT_EQ(subslice.size(), 1);

}



TEST_F(ConstSliceBaseTest_3, CbeginCend_IterateOverElements_3) {

    auto it = sliceBase.cbegin();

    auto end = sliceBase.cend();

    std::vector<int> expected = {20, 30, 40};

    int index = 0;

    for (; it != end; ++it, ++index) {

        EXPECT_EQ(*it, expected[index]);

    }

}



TEST_F(ConstSliceBaseTest_3, SubSlice_OutOfRangeThrows_3) {

    EXPECT_THROW(sliceBase.subSlice(2, 5), std::out_of_range);

    EXPECT_THROW(sliceBase.subSlice(-1, 2), std::out_of_range);

}



} // namespace
