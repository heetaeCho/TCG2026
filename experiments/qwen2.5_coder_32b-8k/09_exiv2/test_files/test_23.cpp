#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"

#include <vector>



using namespace Exiv2;

using ::testing::ElementsAre;



class SliceTest_23 : public ::testing::Test {

protected:

    std::vector<int> vec = {1, 2, 3, 4, 5};

};



TEST_F(SliceTest_23, MakeSliceFrom_ReturnsCorrectSize_23) {

    auto slice = makeSliceFrom(vec, 0);

    EXPECT_EQ(slice.size(), 5);

}



TEST_F(SliceTest_23, MakeSliceFrom_StartsAtBeginIndex_23) {

    auto slice = makeSliceFrom(vec, 2);

    EXPECT_EQ(slice[0], 3);

}



TEST_F(SliceTest_23, MakeSliceFrom_CorrectElementsStartingFromBegin_23) {

    auto slice = makeSliceFrom(vec, 1);

    EXPECT_THAT(slice, ElementsAre(2, 3, 4, 5));

}



TEST_F(SliceTest_23, MakeSliceFrom_BoundaryCondition_ZeroBegin_23) {

    auto slice = makeSliceFrom(vec, 0);

    EXPECT_EQ(slice[0], 1);

}



TEST_F(SliceTest_23, MakeSliceFrom_BoundaryCondition_LastElement_23) {

    auto slice = makeSliceFrom(vec, 4);

    EXPECT_EQ(slice.size(), 1);

    EXPECT_EQ(slice[0], 5);

}



TEST_F(SliceTest_23, MakeSliceFrom_OutOfBoundsBegin_ReturnsEmpty_23) {

    auto slice = makeSliceFrom(vec, 5);

    EXPECT_TRUE(slice.empty());

}



TEST_F(SliceTest_23, MakeSliceFrom_GreaterThanSizeBegin_ReturnsEmpty_23) {

    auto slice = makeSliceFrom(vec, 6);

    EXPECT_TRUE(slice.empty());

}
