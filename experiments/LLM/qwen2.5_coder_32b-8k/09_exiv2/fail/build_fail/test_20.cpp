#include <gtest/gtest.h>

#include "exiv2/slice.hpp"

#include <vector>



namespace {



template <typename T>

class SliceTest_20 : public ::testing::Test {

protected:

    using ContainerType = std::vector<T>;

    using SliceType = Exiv2::Slice<T>;



    SliceTest_20() : container_{1, 2, 3, 4, 5}, slice_{Exiv2::makeSlice(container_, 1, 4)} {}



    ContainerType container_;

    SliceType slice_;

};



using IntSliceTest_20 = SliceTest_20<int>;



TEST_F(IntSliceTest_20, AccessElementsCorrectly_20) {

    EXPECT_EQ(slice_[0], 2);

    EXPECT_EQ(slice_[1], 3);

    EXPECT_EQ(slice_[2], 4);

}



TEST_F(IntSliceTest_20, SizeReturnsCorrectValue_20) {

    EXPECT_EQ(slice_.size(), 3);

}



TEST_F(IntSliceTest_20, EmptySliceHasZeroSize_20) {

    SliceType emptySlice = Exiv2::makeSlice(container_, 1, 1);

    EXPECT_EQ(emptySlice.size(), 0);

}



TEST_F(IntSliceTest_20, FullContainerSliceMatchesOriginal_20) {

    SliceType fullSlice = Exiv2::makeSlice(container_, 0, container_.size());

    for (size_t i = 0; i < container_.size(); ++i) {

        EXPECT_EQ(fullSlice[i], container_[i]);

    }

}



TEST_F(IntSliceTest_20, OutOfBoundsAccessThrowsException_20) {

    EXPECT_THROW(slice_[3], std::out_of_range);

    EXPECT_THROW(slice_[-1], std::out_of_range);

}



}  // namespace
