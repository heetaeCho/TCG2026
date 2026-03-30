#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_14 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary variables before each test.

        dynArray.Clear();

    }



    void TearDown() override {

        // Clean up after each test if necessary.

        dynArray.Clear();

    }



    DynArray<int, 5> dynArray;  // Assuming int type and initial size of 5 for testing purposes

};



TEST_F(DynArrayTest_14, InitialCapacity_14) {

    EXPECT_EQ(dynArray.Capacity(), 5);

}



TEST_F(DynArrayTest_14, PushIncreasesSize_14) {

    dynArray.Push(10);

    EXPECT_EQ(dynArray.Size(), 1);

}



TEST_F(DynArrayTest_14, PopDecreasesSize_14) {

    dynArray.Push(10);

    dynArray.Pop();

    EXPECT_EQ(dynArray.Size(), 0);

}



TEST_F(DynArrayTest_14, PushArrIncreasesCapacityAndSize_14) {

    int* arr = dynArray.PushArr(3);

    EXPECT_NE(arr, nullptr);

    EXPECT_EQ(dynArray.Capacity(), 5);  // EnsureCapacity not triggered

    EXPECT_EQ(dynArray.Size(), 3);



    arr = dynArray.PushArr(3);

    EXPECT_NE(arr, nullptr);

    EXPECT_GE(dynArray.Capacity(), 8);  // EnsureCapacity triggered

    EXPECT_EQ(dynArray.Size(), 6);

}



TEST_F(DynArrayTest_14, PopArrDecreasesSize_14) {

    dynArray.PushArr(3);

    dynArray.PopArr(2);

    EXPECT_EQ(dynArray.Size(), 1);



    dynArray.PopArr(1);

    EXPECT_EQ(dynArray.Size(), 0);

}



TEST_F(DynArrayTest_14, EmptyCheck_14) {

    EXPECT_TRUE(dynArray.Empty());

    dynArray.Push(10);

    EXPECT_FALSE(dynArray.Empty());

}



TEST_F(DynArrayTest_14, IndexOperator_14) {

    dynArray.Push(10);

    dynArray.Push(20);



    EXPECT_EQ(dynArray[0], 10);

    EXPECT_EQ(dynArray[1], 20);

}



TEST_F(DynArrayTest_14, PeekTopAfterPush_14) {

    dynArray.Push(30);

    EXPECT_EQ(dynArray.PeekTop(), 30);



    dynArray.Push(40);

    EXPECT_EQ(dynArray.PeekTop(), 40);

}



TEST_F(DynArrayTest_14, SwapRemovePreservesOrder_14) {

    dynArray.Push(10);

    dynArray.Push(20);

    dynArray.Push(30);



    dynArray.SwapRemove(1);  // Remove element at index 1 (value 20)

    EXPECT_EQ(dynArray[0], 10);

    EXPECT_EQ(dynArray[1], 30);

    EXPECT_EQ(dynArray.Size(), 2);

}



TEST_F(DynArrayTest_14, MemPointerNotNull_14) {

    EXPECT_NE(dynArray.Mem(), nullptr);

}



TEST_F(DynArrayTest_14, BoundaryConditionPushPop_14) {

    // Push up to initial capacity

    for (int i = 0; i < 5; ++i) {

        dynArray.Push(i);

    }

    EXPECT_EQ(dynArray.Size(), 5);



    // Pop all elements

    for (int i = 0; i < 5; ++i) {

        dynArray.Pop();

    }

    EXPECT_EQ(dynArray.Size(), 0);

}
