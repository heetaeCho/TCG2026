#include <gtest/gtest.h>

#include "exiv2/slice.hpp"



using namespace Exiv2;



// Test Fixture for Slice class

class SliceTest_25 : public ::testing::Test {

protected:

    // Common setup and teardown can be done here if needed

};



TEST_F(SliceTest_25, MakeSliceUntil_ValidPointerAndSize_25) {

    int data[] = {1, 2, 3, 4, 5};

    size_t end = 3;

    Slice<int*> slice = makeSliceUntil(data, end);



    EXPECT_EQ(slice.begin(), data);

    EXPECT_EQ(slice.end(), data + end);

}



TEST_F(SliceTest_25, MakeSliceUntil_ZeroSize_25) {

    int data[] = {1, 2, 3, 4, 5};

    size_t end = 0;

    Slice<int*> slice = makeSliceUntil(data, end);



    EXPECT_EQ(slice.begin(), data);

    EXPECT_EQ(slice.end(), data + end);

}



TEST_F(SliceTest_25, MakeSliceUntil_FullSize_25) {

    int data[] = {1, 2, 3, 4, 5};

    size_t end = sizeof(data) / sizeof(data[0]);

    Slice<int*> slice = makeSliceUntil(data, end);



    EXPECT_EQ(slice.begin(), data);

    EXPECT_EQ(slice.end(), data + end);

}



TEST_F(SliceTest_25, MakeSliceUntil_NullPointer_25) {

    int* data = nullptr;

    size_t end = 3;

    Slice<int*> slice = makeSliceUntil(data, end);



    EXPECT_EQ(slice.begin(), data);

    EXPECT_EQ(slice.end(), data + end);

}



TEST_F(SliceTest_25, MakeSliceUntil_LargeSize_25) {

    int data[] = {1, 2, 3, 4, 5};

    size_t end = 10; // Larger than the actual array size

    Slice<int*> slice = makeSliceUntil(data, end);



    EXPECT_EQ(slice.begin(), data);

    EXPECT_EQ(slice.end(), data + end);

}
