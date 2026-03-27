#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"



namespace {



using namespace Exiv2::Internal;



class MockSliceBase : public SliceBase {

public:

    MockSliceBase(size_t begin, size_t end) : SliceBase(begin, end) {}

    MOCK_CONST_METHOD0(size, size_t());

};



class SliceBaseTest_2 : public ::testing::Test {

protected:

    MockSliceBase mockSliceBase;

    SliceBaseTest_2() : mockSliceBase(0, 10) {} // Example range from 0 to 9

};



TEST_F(SliceBaseTest_2, RangeCheckWithinBounds_2) {

    EXPECT_CALL(mockSliceBase, size()).WillOnce(::testing::Return(10));

    ASSERT_NO_THROW(mockSliceBase.rangeCheck(5)); // Index within bounds

}



TEST_F(SliceBaseTest_2, RangeCheckOnBoundaryLower_2) {

    EXPECT_CALL(mockSliceBase, size()).WillOnce(::testing::Return(10));

    ASSERT_NO_THROW(mockSliceBase.rangeCheck(0)); // Lower boundary index

}



TEST_F(SliceBaseTest_2, RangeCheckOnBoundaryUpper_2) {

    EXPECT_CALL(mockSliceBase, size()).WillOnce(::testing::Return(10));

    ASSERT_NO_THROW(mockSliceBase.rangeCheck(9)); // Upper boundary index

}



TEST_F(SliceBaseTest_2, RangeCheckOutsideBoundsLower_2) {

    EXPECT_CALL(mockSliceBase, size()).WillOnce(::testing::Return(10));

    EXPECT_THROW(mockSliceBase.rangeCheck(-1), std::out_of_range); // Index below lower bound

}



TEST_F(SliceBaseTest_2, RangeCheckOutsideBoundsUpper_2) {

    EXPECT_CALL(mockSliceBase, size()).WillOnce(::testing::Return(10));

    EXPECT_THROW(mockSliceBase.rangeCheck(10), std::out_of_range); // Index above upper bound

}



}  // namespace
