#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_13 : public ::testing::Test {

protected:

    DynArray<int, 5> dynArray;

};



TEST_F(DynArrayTest_13, InitialSizeIsZero_13) {

    EXPECT_EQ(dynArray.Size(), 0);

}



TEST_F(DynArrayTest_13, PushIncreasesCount_13) {

    dynArray.Push(42);

    EXPECT_EQ(dynArray.Size(), 1);

}



TEST_F(DynArrayTest_13, PopDecreasesCount_13) {

    dynArray.Push(42);

    dynArray.Pop();

    EXPECT_EQ(dynArray.Size(), 0);

}



TEST_F(DynArrayTest_13, PushArrIncreasesCount_13) {

    auto arr = dynArray.PushArr(3);

    for (size_t i = 0; i < 3; ++i) {

        arr[i] = static_cast<int>(i);

    }

    EXPECT_EQ(dynArray.Size(), 3);

}



TEST_F(DynArrayTest_13, PopArrDecreasesCount_13) {

    auto arr = dynArray.PushArr(3);

    for (size_t i = 0; i < 3; ++i) {

        arr[i] = static_cast<int>(i);

    }

    dynArray.PopArr(2);

    EXPECT_EQ(dynArray.Size(), 1);

}



TEST_F(DynArrayTest_13, ClearSetsCountToZero_13) {

    dynArray.Push(42);

    dynArray.Clear();

    EXPECT_EQ(dynArray.Size(), 0);

}



TEST_F(DynArrayTest_13, EmptyReturnsTrueWhenNoElements_13) {

    EXPECT_TRUE(dynArray.Empty());

}



TEST_F(DynArrayTest_13, EmptyReturnsFalseWhenElementsPresent_13) {

    dynArray.Push(42);

    EXPECT_FALSE(dynArray.Empty());

}



TEST_F(DynArrayTest_13, OperatorBracketAccessesElement_13) {

    dynArray.Push(42);

    EXPECT_EQ(dynArray[0], 42);

}



TEST_F(DynArrayTest_13, PeekTopReturnsLastElement_13) {

    dynArray.Push(42);

    EXPECT_EQ(dynArray.PeekTop(), 42);

}



TEST_F(DynArrayTest_13, CapacityIsInitiallyCorrect_13) {

    EXPECT_EQ(dynArray.Capacity(), 5);

}
