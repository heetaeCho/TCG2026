#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"



using namespace Exiv2::Internal;



class ConstSliceBaseTest_5 : public ::testing::Test {

protected:

    std::vector<int> data = {1, 2, 3, 4, 5};

    ConstSliceBase<std::vector, int> slice;



    ConstSliceBaseTest_5() : slice(data, 1, 4) {}

};



TEST_F(ConstSliceBaseTest_5, SizeReturnsCorrectSize_5) {

    EXPECT_EQ(slice.size(), 3);

}



TEST_F(ConstSliceBaseTest_5, AtAccessesCorrectElement_5) {

    EXPECT_EQ(slice.at(0), 2);

    EXPECT_EQ(slice.at(1), 3);

    EXPECT_EQ(slice.at(2), 4);

}



TEST_F(ConstSliceBaseTest_5, CbeginReturnsIteratorToStart_5) {

    auto it = slice.cbegin();

    EXPECT_EQ(*it, 2);

}



TEST_F(ConstSliceBaseTest_5, CendReturnsIteratorToEnd_5) {

    auto it = slice.cend();

    EXPECT_EQ(it, slice.storage_.unsafeGetIteratorAt(4));

}



TEST_F(ConstSliceBaseTest_5, SubSliceCreatesCorrectSubslice_5) {

    auto subslice = slice.subSlice<int>(1, 2);

    EXPECT_EQ(subslice.size(), 1);

    EXPECT_EQ(subslice.at(0), 3);

}



TEST_F(ConstSliceBaseTest_5, BoundaryConditionAtStart_5) {

    EXPECT_EQ(slice.at(0), 2);

}



TEST_F(ConstSliceBaseTest_5, BoundaryConditionAtEnd_5) {

    EXPECT_EQ(slice.at(2), 4);

}



TEST_F(ConstSliceBaseTest_5, OutOfBoundsAccessThrowsException_5) {

    EXPECT_THROW(slice.at(3), std::out_of_range);

    EXPECT_THROW(slice.at(-1), std::out_of_range);

}
