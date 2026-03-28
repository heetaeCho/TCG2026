#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"



namespace {



using namespace Exiv2::Internal;



class MutableSliceBaseTest_10 : public ::testing::Test {

protected:

    using StorageType = std::vector<int>;

    using DataType = int;

    using SliceType = MutableSliceBase<StorageType, DataType>;



    SliceType slice_;

};



TEST_F(MutableSliceBaseTest_10, ToConstBase_ConvertsCorrectly_10) {

    StorageType storage = {1, 2, 3, 4, 5};

    size_t begin = 1;

    size_t end = 4;

    SliceType slice(storage, begin, end);

    

    ConstSliceBase<StorageType, const DataType> const_base = slice.to_const_base();

    

    EXPECT_EQ(const_base.data(), storage.data());

    EXPECT_EQ(const_base.begin(), begin);

    EXPECT_EQ(const_base.end(), end);

}



TEST_F(MutableSliceBaseTest_10, At_ReturnsCorrectElement_10) {

    StorageType storage = {10, 20, 30, 40, 50};

    SliceType slice(storage, 0, 5);

    

    EXPECT_EQ(slice.at(0), 10);

    EXPECT_EQ(slice.at(2), 30);

    EXPECT_EQ(slice.at(4), 50);

}



TEST_F(MutableSliceBaseTest_10, At_OutOfBounds_ThrowsException_10) {

    StorageType storage = {10, 20, 30};

    SliceType slice(storage, 0, 3);



    EXPECT_THROW(slice.at(3), std::out_of_range);

    EXPECT_THROW(slice.at(-1), std::out_of_range);

}



TEST_F(MutableSliceBaseTest_10, Begin_ReturnsCorrectIterator_10) {

    StorageType storage = {1, 2, 3};

    SliceType slice(storage, 0, 3);



    EXPECT_EQ(*slice.begin(), 1);

}



TEST_F(MutableSliceBaseTest_10, End_ReturnsCorrectIterator_10) {

    StorageType storage = {1, 2, 3};

    SliceType slice(storage, 0, 3);



    EXPECT_EQ(slice.end(), storage.data() + 3);

}



TEST_F(MutableSliceBaseTest_10, SubSlice_CreatesValidSubslice_10) {

    StorageType storage = {1, 2, 3, 4, 5};

    SliceType slice(storage, 0, 5);



    auto subslice = slice.subSlice(1, 4);

    EXPECT_EQ(subslice.begin(), 1);

    EXPECT_EQ(subslice.end(), 4);

}



TEST_F(MutableSliceBaseTest_10, SubSlice_OutOfBounds_CreatesEmptySubslice_10) {

    StorageType storage = {1, 2, 3};

    SliceType slice(storage, 0, 3);



    auto subslice = slice.subSlice(3, 5);

    EXPECT_EQ(subslice.begin(), 3);

    EXPECT_EQ(subslice.end(), 3);

}



TEST_F(MutableSliceBaseTest_10, SubSlice_BoundaryConditions_CreatesValidSubslices_10) {

    StorageType storage = {1, 2, 3};

    SliceType slice(storage, 0, 3);



    auto subslice_begin = slice.subSlice(0, 1);

    EXPECT_EQ(subslice_begin.begin(), 0);

    EXPECT_EQ(subslice_begin.end(), 1);



    auto subslice_end = slice.subSlice(2, 3);

    EXPECT_EQ(subslice_end.begin(), 2);

    EXPECT_EQ(subslice_end.end(), 3);

}



} // namespace
