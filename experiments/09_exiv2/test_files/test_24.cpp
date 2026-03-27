#include <gtest/gtest.h>

#include "exiv2/slice.hpp"

#include <vector>

#include <string>



using namespace Exiv2;



// Fixture for Slice tests

class SliceTest_24 : public ::testing::Test {

protected:

    std::vector<int> testVector;

    std::string testString;



    void SetUp() override {

        testVector = {1, 2, 3, 4, 5};

        testString = "hello";

    }

};



// Test normal operation with a vector

TEST_F(SliceTest_24, MakeSliceUntil_NormalOperation_Vector_24) {

    auto slice = makeSliceUntil(testVector, 3);

    EXPECT_EQ(slice.size(), 3);

    EXPECT_EQ(slice[0], 1);

    EXPECT_EQ(slice[1], 2);

    EXPECT_EQ(slice[2], 3);

}



// Test normal operation with a string

TEST_F(SliceTest_24, MakeSliceUntil_NormalOperation_String_24) {

    auto slice = makeSliceUntil(testString, 3);

    EXPECT_EQ(slice.size(), 3);

    EXPECT_EQ(slice[0], 'h');

    EXPECT_EQ(slice[1], 'e');

    EXPECT_EQ(slice[2], 'l');

}



// Test boundary condition: end is zero

TEST_F(SliceTest_24, MakeSliceUntil_EndIsZero_24) {

    auto slice = makeSliceUntil(testVector, 0);

    EXPECT_EQ(slice.size(), 0);

}



// Test boundary condition: end is equal to container size

TEST_F(SliceTest_24, MakeSliceUntil_EndEqualToSize_24) {

    auto slice = makeSliceUntil(testVector, testVector.size());

    EXPECT_EQ(slice.size(), testVector.size());

    for (size_t i = 0; i < testVector.size(); ++i) {

        EXPECT_EQ(slice[i], testVector[i]);

    }

}



// Test boundary condition: end is greater than container size

TEST_F(SliceTest_24, MakeSliceUntil_EndGreaterThanSize_24) {

    auto slice = makeSliceUntil(testVector, testVector.size() + 1);

    EXPECT_EQ(slice.size(), testVector.size());

    for (size_t i = 0; i < testVector.size(); ++i) {

        EXPECT_EQ(slice[i], testVector[i]);

    }

}
