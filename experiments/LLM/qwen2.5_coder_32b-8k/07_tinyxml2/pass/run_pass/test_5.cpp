#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_5 : public ::testing::Test {

protected:

    DynArray<int, 10> dynArray;

};



TEST_F(DynArrayTest_5, ClearEmptiesArray_5) {

    dynArray.Push(42);

    EXPECT_FALSE(dynArray.Empty());

    dynArray.Clear();

    EXPECT_TRUE(dynArray.Empty());

}



TEST_F(DynArrayTest_5, PushIncreasesSize_5) {

    size_t initialSize = dynArray.Size();

    dynArray.Push(42);

    EXPECT_EQ(dynArray.Size(), initialSize + 1);

}



TEST_F(DynArrayTest_5, PopDecreasesSize_5) {

    dynArray.Push(42);

    size_t initialSize = dynArray.Size();

    dynArray.Pop();

    EXPECT_EQ(dynArray.Size(), initialSize - 1);

}



TEST_F(DynArrayTest_5, PushArrIncreasesCapacityAndSize_5) {

    size_t count = 3;

    size_t initialSize = dynArray.Size();

    size_t initialCapacity = dynArray.Capacity();

    int* ptr = dynArray.PushArr(count);

    EXPECT_EQ(dynArray.Size(), initialSize + count);

    EXPECT_GE(dynArray.Capacity(), initialCapacity + count); // Capacity might increase more due to internal logic

}



TEST_F(DynArrayTest_5, PopArrDecreasesSize_5) {

    size_t count = 3;

    dynArray.Push(1);

    dynArray.Push(2);

    dynArray.Push(3);

    size_t initialSize = dynArray.Size();

    dynArray.PopArr(count);

    EXPECT_EQ(dynArray.Size(), initialSize - count);

}



TEST_F(DynArrayTest_5, PeekTopReturnsLastElement_5) {

    int value = 42;

    dynArray.Push(value);

    EXPECT_EQ(dynArray.PeekTop(), value);

}



TEST_F(DynArrayTest_5, OperatorBracketAccessesCorrectElement_5) {

    int value1 = 10;

    int value2 = 20;

    dynArray.Push(value1);

    dynArray.Push(value2);

    EXPECT_EQ(dynArray[0], value1);

    EXPECT_EQ(dynArray[1], value2);

}



TEST_F(DynArrayTest_5, SwapRemoveMaintainsSizeAndOrder_5) {

    int values[] = {1, 2, 3, 4, 5};

    for (int val : values) {

        dynArray.Push(val);

    }

    size_t indexToRemove = 2;

    int expectedValuesAfterRemoval[] = {1, 2, 5, 4}; // Element at index 2 is removed

    dynArray.SwapRemove(indexToRemove);

    for (size_t i = 0; i < dynArray.Size(); ++i) {

        EXPECT_EQ(dynArray[i], expectedValuesAfterRemoval[i]);

    }

}



TEST_F(DynArrayTest_5, CapacityGrowsWithPushArrBeyondInitialSize_5) {

    size_t initialCapacity = dynArray.Capacity();

    size_t count = initialCapacity + 1;

    dynArray.PushArr(count);

    EXPECT_GT(dynArray.Capacity(), initialCapacity);

}



TEST_F(DynArrayTest_5, MemReturnsPointerToInternalMemory_5) {

    int* memPtr = const_cast<int*>(dynArray.Mem());

    EXPECT_EQ(memPtr, &dynArray[0]);

}
