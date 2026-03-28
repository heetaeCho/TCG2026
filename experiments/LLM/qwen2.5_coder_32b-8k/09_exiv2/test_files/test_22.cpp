#include <gtest/gtest.h>

#include "exiv2/slice.hpp"

#include <vector>

#include <string>



using namespace Exiv2;



// Test fixture for Slice class tests

class SliceTest_22 : public ::testing::Test {

protected:

    std::vector<int> vec = {1, 2, 3, 4, 5};

    std::string str = "hello";

};



// Test normal operation with a vector

TEST_F(SliceTest_22, VectorSliceCreation_22) {

    auto slice = makeSlice(vec);

    EXPECT_EQ(slice.start(), 0);

    EXPECT_EQ(slice.end(), vec.size());

}



// Test normal operation with a string

TEST_F(SliceTest_22, StringSliceCreation_22) {

    auto slice = makeSlice(str);

    EXPECT_EQ(slice.start(), 0);

    EXPECT_EQ(slice.end(), str.size());

}



// Test boundary condition with an empty vector

TEST_F(SliceTest_22, EmptyVectorSliceCreation_22) {

    std::vector<int> emptyVec;

    auto slice = makeSlice(emptyVec);

    EXPECT_EQ(slice.start(), 0);

    EXPECT_EQ(slice.end(), 0);

}



// Test boundary condition with an empty string

TEST_F(SliceTest_22, EmptyStringSliceCreation_22) {

    std::string emptyStr;

    auto slice = makeSlice(emptyStr);

    EXPECT_EQ(slice.start(), 0);

    EXPECT_EQ(slice.end(), 0);

}
