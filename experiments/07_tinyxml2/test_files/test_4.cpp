#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_4 : public ::testing::Test {

protected:

    DynArray<int, 5> dynArray;

};



TEST_F(DynArrayTest_4, PushIncreasesSize_4) {

    EXPECT_EQ(dynArray.Size(), 0);

    dynArray.Push(1);

    EXPECT_EQ(dynArray.Size(), 1);

}



TEST_F(DynArrayTest_4, PushArrIncreasesSizeCorrectly_4) {

    EXPECT_EQ(dynArray.Size(), 0);

    int* arr = dynArray.PushArr(3);

    for (int i = 0; i < 3; ++i) {

        arr[i] = i;

    }

    EXPECT_EQ(dynArray.Size(), 3);

}



TEST_F(DynArrayTest_4, PopDecreasesSize_4) {

    dynArray.Push(1);

    dynArray.Push(2);

    EXPECT_EQ(dynArray.Size(), 2);

    dynArray.Pop();

    EXPECT_EQ(dynArray.Size(), 1);

}



TEST_F(DynArrayTest_4, PopArrDecreasesSizeCorrectly_4) {

    int* arr = dynArray.PushArr(3);

    for (int i = 0; i < 3; ++i) {

        arr[i] = i;

    }

    EXPECT_EQ(dynArray.Size(), 3);

    dynArray.PopArr(2);

    EXPECT_EQ(dynArray.Size(), 1);

}



TEST_F(DynArrayTest_4, EmptyReturnsTrueWhenEmpty_4) {

    EXPECT_TRUE(dynArray.Empty());

}



TEST_F(DynArrayTest_4, EmptyReturnsFalseWhenNotEmpty_4) {

    dynArray.Push(1);

    EXPECT_FALSE(dynArray.Empty());

}



TEST_F(DynArrayTest_4, OperatorBracketAccessesCorrectElement_4) {

    int* arr = dynArray.PushArr(3);

    for (int i = 0; i < 3; ++i) {

        arr[i] = i + 1;

    }

    EXPECT_EQ(dynArray[0], 1);

    EXPECT_EQ(dynArray[1], 2);

    EXPECT_EQ(dynArray[2], 3);

}



TEST_F(DynArrayTest_4, PeekTopReturnsLastElement_4) {

    dynArray.Push(1);

    dynArray.Push(2);

    EXPECT_EQ(dynArray.PeekTop(), 2);

}



TEST_F(DynArrayTest_4, SizeReturnsCorrectSize_4) {

    EXPECT_EQ(dynArray.Size(), 0);

    dynArray.Push(1);

    EXPECT_EQ(dynArray.Size(), 1);

    dynArray.PushArr(3);

    EXPECT_EQ(dynArray.Size(), 4);

}



TEST_F(DynArrayTest_4, CapacityReturnsCorrectCapacity_4) {

    EXPECT_EQ(dynArray.Capacity(), 5);

    dynArray.PushArr(6); // This should cause a capacity increase

    EXPECT_GT(dynArray.Capacity(), 5);

}



TEST_F(DynArrayTest_4, SwapRemoveRemovesElementAndPreservesOrder_4) {

    int* arr = dynArray.PushArr(3);

    for (int i = 0; i < 3; ++i) {

        arr[i] = i + 1;

    }

    dynArray.SwapRemove(1); // Remove element at index 1

    EXPECT_EQ(dynArray.Size(), 2);

    EXPECT_EQ(dynArray[0], 1);

    EXPECT_EQ(dynArray[1], 3);

}



TEST_F(DynArrayTest_4, MemReturnsPointerToData_4) {

    int* arr = dynArray.PushArr(3);

    for (int i = 0; i < 3; ++i) {

        arr[i] = i + 1;

    }

    const int* mem = dynArray.Mem();

    EXPECT_EQ(mem[0], 1);

    EXPECT_EQ(mem[1], 2);

    EXPECT_EQ(mem[2], 3);

}



TEST_F(DynArrayTest_4, ClearResetsSizeToZero_4) {

    dynArray.Push(1);

    dynArray.Push(2);

    dynArray.Clear();

    EXPECT_EQ(dynArray.Size(), 0);

}
