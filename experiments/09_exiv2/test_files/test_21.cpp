#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"



namespace {



using namespace Exiv2;



TEST(SliceTest_21, MakeSlice_ValidRange_21) {

    int data[] = {1, 2, 3, 4, 5};

    auto slice = makeSlice(data, 1, 4);

    EXPECT_EQ(slice.begin(), &data[1]);

    EXPECT_EQ(slice.end(), &data[4]);

}



TEST(SliceTest_21, MakeSlice_FullRange_21) {

    int data[] = {1, 2, 3, 4, 5};

    auto slice = makeSlice(data, 0, 5);

    EXPECT_EQ(slice.begin(), &data[0]);

    EXPECT_EQ(slice.end(), &data[5]);

}



TEST(SliceTest_21, MakeSlice_EmptyRange_21) {

    int data[] = {1, 2, 3, 4, 5};

    auto slice = makeSlice(data, 2, 2);

    EXPECT_EQ(slice.begin(), &data[2]);

    EXPECT_EQ(slice.end(), &data[2]);

}



TEST(SliceTest_21, MakeSlice_OutOfBoundsEnd_21) {

    int data[] = {1, 2, 3, 4, 5};

    auto slice = makeSlice(data, 0, 6);

    EXPECT_EQ(slice.begin(), &data[0]);

    EXPECT_EQ(slice.end(), &data[5]); // end should clamp to the last valid element

}



TEST(SliceTest_21, MakeSlice_OutOfBoundsBegin_21) {

    int data[] = {1, 2, 3, 4, 5};

    auto slice = makeSlice(data, 6, 7);

    EXPECT_EQ(slice.begin(), &data[5]); // begin should clamp to the last valid element

    EXPECT_EQ(slice.end(), &data[5]);

}



TEST(SliceTest_21, MakeSlice_BeginGreaterThanEnd_21) {

    int data[] = {1, 2, 3, 4, 5};

    auto slice = makeSlice(data, 4, 2);

    EXPECT_EQ(slice.begin(), &data[4]);

    EXPECT_EQ(slice.end(), &data[4]); // end should be adjusted to match begin

}



}  // namespace
