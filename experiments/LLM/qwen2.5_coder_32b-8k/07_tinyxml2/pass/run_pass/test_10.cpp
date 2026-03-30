#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_10 : public ::testing::Test {

protected:

    DynArray<int, 5> dynArray;

};



TEST_F(DynArrayTest_10, Empty_ReturnsTrueForNewInstance_10) {

    EXPECT_TRUE(dynArray.Empty());

}



TEST_F(DynArrayTest_10, Push_IncreasesSize_10) {

    dynArray.Push(42);

    EXPECT_FALSE(dynArray.Empty());

}



TEST_F(DynArrayTest_10, PushArr_ReturnsPointerToNewElements_10) {

    int* ptr = dynArray.PushArr(3);

    for (int i = 0; i < 3; ++i) {

        ptr[i] = i;

    }

    EXPECT_EQ(dynArray.Size(), 3u);

}



TEST_F(DynArrayTest_10, Pop_DecreasesSize_10) {

    dynArray.Push(42);

    dynArray.Pop();

    EXPECT_TRUE(dynArray.Empty());

}



TEST_F(DynArrayTest_10, PopArr_DecreasesSizeByCount_10) {

    dynArray.PushArr(5);

    dynArray.PopArr(3);

    EXPECT_EQ(dynArray.Size(), 2u);

}



TEST_F(DynArrayTest_10, Size_ReturnsCorrectSizeAfterPush_10) {

    dynArray.Push(42);

    EXPECT_EQ(dynArray.Size(), 1u);

}



TEST_F(DynArrayTest_10, Capacity_ReturnsInitialCapacity_10) {

    EXPECT_EQ(dynArray.Capacity(), 5u);

}



TEST_F(DynArrayTest_10, OperatorBracket_AccessesElementsCorrectly_10) {

    dynArray.Push(42);

    dynArray.Push(84);

    EXPECT_EQ(dynArray[0], 42);

    EXPECT_EQ(dynArray[1], 84);

}



TEST_F(DynArrayTest_10, PeekTop_ReturnsLastElement_10) {

    dynArray.Push(42);

    dynArray.Push(84);

    EXPECT_EQ(dynArray.PeekTop(), 84);

}



TEST_F(DynArrayTest_10, SwapRemove_RemovesAndSwapsCorrectly_10) {

    for (int i = 0; i < 3; ++i) {

        dynArray.Push(i);

    }

    dynArray.SwapRemove(0); // Remove element 0, swap with last element

    EXPECT_EQ(dynArray.Size(), 2u);

    EXPECT_EQ(dynArray[0], 2);

}



TEST_F(DynArrayTest_10, Mem_ReturnsPointerToData_10) {

    dynArray.Push(42);

    const int* data = dynArray.Mem();

    EXPECT_EQ(*data, 42);

}



TEST_F(DynArrayTest_10, Clear_ResetsSize_10) {

    dynArray.PushArr(5);

    dynArray.Clear();

    EXPECT_TRUE(dynArray.Empty());

}
