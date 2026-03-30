#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_12 : public ::testing::Test {

protected:

    DynArray<int, 5> dynArray;

};



TEST_F(DynArrayTest_12, PushIncreasesCount_12) {

    EXPECT_EQ(dynArray.Size(), 0);

    dynArray.Push(42);

    EXPECT_EQ(dynArray.Size(), 1);

}



TEST_F(DynArrayTest_12, PopDecreasesCount_12) {

    dynArray.Push(42);

    EXPECT_EQ(dynArray.Size(), 1);

    dynArray.Pop();

    EXPECT_EQ(dynArray.Size(), 0);

}



TEST_F(DynArrayTest_12, PeekTopReturnsLastElement_12) {

    dynArray.Push(42);

    EXPECT_EQ(dynArray.PeekTop(), 42);

    dynArray.Push(54);

    EXPECT_EQ(dynArray.PeekTop(), 54);

}



TEST_F(DynArrayTest_12, PopArrReducesCount_12) {

    dynArray.Push(1);

    dynArray.Push(2);

    dynArray.Push(3);

    dynArray.PopArr(2);

    EXPECT_EQ(dynArray.Size(), 1);

}



TEST_F(DynArrayTest_12, ClearResetsSize_12) {

    dynArray.Push(42);

    dynArray.Clear();

    EXPECT_EQ(dynArray.Size(), 0);

}



TEST_F(DynArrayTest_12, EmptyReturnsTrueWhenNoElements_12) {

    EXPECT_TRUE(dynArray.Empty());

    dynArray.Push(42);

    EXPECT_FALSE(dynArray.Empty());

}



TEST_F(DynArrayTest_12, PushArrIncreasesSizeByCount_12) {

    int* arr = dynArray.PushArr(3);

    for (size_t i = 0; i < 3; ++i) {

        arr[i] = static_cast<int>(i);

    }

    EXPECT_EQ(dynArray.Size(), 3);

}



TEST_F(DynArrayTest_12, CapacityReturnsInitialCapacity_12) {

    EXPECT_EQ(dynArray.Capacity(), 5);

}



TEST_F(DynArrayTest_12, SwapRemoveReplacesElementWithLast_12) {

    dynArray.Push(10);

    dynArray.Push(20);

    dynArray.Push(30);

    dynArray.SwapRemove(1); // Should replace 20 with 30

    EXPECT_EQ(dynArray.Size(), 2);

    EXPECT_TRUE(dynArray[0] == 10 && dynArray[1] == 30);

}



TEST_F(DynArrayTest_12, ArrayAccessOperatorReturnsCorrectElement_12) {

    dynArray.Push(42);

    EXPECT_EQ(dynArray[0], 42);

    dynArray.Push(54);

    EXPECT_EQ(dynArray[1], 54);

}
