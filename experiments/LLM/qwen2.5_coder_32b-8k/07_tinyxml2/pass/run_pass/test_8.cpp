#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_8 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed

    }



    void TearDown() override {

        // Teardown code, if needed

    }



    DynArray<int, 10> dynArray;

};



TEST_F(DynArrayTest_8, PushAndPop_SingleElement_8) {

    dynArray.Push(42);

    EXPECT_EQ(dynArray.Pop(), 42);

}



TEST_F(DynArrayTest_8, Pop_EmptyArray_8) {

    EXPECT_DEATH(dynArray.Pop(), "TIXMLASSERT.*");

}



TEST_F(DynArrayTest_8, PushAndPop_MultipleElements_8) {

    dynArray.Push(1);

    dynArray.Push(2);

    dynArray.Push(3);



    EXPECT_EQ(dynArray.Pop(), 3);

    EXPECT_EQ(dynArray.Pop(), 2);

    EXPECT_EQ(dynArray.Pop(), 1);

}



TEST_F(DynArrayTest_8, PushArr_ReturnsPointerToFirstElement_8) {

    int* ptr = dynArray.PushArr(3);

    for (int i = 0; i < 3; ++i) {

        ptr[i] = i;

    }

    EXPECT_EQ(ptr[0], 0);

    EXPECT_EQ(ptr[1], 1);

    EXPECT_EQ(ptr[2], 2);



    // Verify that the elements are in the array

    for (int i = 0; i < 3; ++i) {

        EXPECT_EQ(dynArray.Pop(), 2 - i);

    }

}



TEST_F(DynArrayTest_8, PushArr_PopArr_MultipleElements_8) {

    dynArray.PushArr(5);

    dynArray.PopArr(3);



    // After popping 3 elements, 2 should remain

    EXPECT_EQ(dynArray.Size(), 2);

}



TEST_F(DynArrayTest_8, Clear_RemovesAllElements_8) {

    dynArray.Push(1);

    dynArray.Push(2);

    dynArray.Clear();

    EXPECT_TRUE(dynArray.Empty());

}



TEST_F(DynArrayTest_8, Empty_ReturnsTrueForEmptyArray_8) {

    EXPECT_TRUE(dynArray.Empty());

}



TEST_F(DynArrayTest_8, Empty_ReturnsFalseForNonEmptyArray_8) {

    dynArray.Push(1);

    EXPECT_FALSE(dynArray.Empty());

}



TEST_F(DynArrayTest_8, Size_ReturnsCorrectSize_8) {

    dynArray.Push(1);

    dynArray.Push(2);

    EXPECT_EQ(dynArray.Size(), 2);



    dynArray.Pop();

    EXPECT_EQ(dynArray.Size(), 1);

}



TEST_F(DynArrayTest_8, Capacity_ReturnsInitialCapacity_8) {

    EXPECT_EQ(dynArray.Capacity(), 10);

}



TEST_F(DynArrayTest_8, PeekTop_ReturnsLastElement_8) {

    dynArray.Push(42);

    EXPECT_EQ(dynArray.PeekTop(), 42);



    dynArray.Push(13);

    EXPECT_EQ(dynArray.PeekTop(), 13);

}



TEST_F(DynArrayTest_8, SubscriptOperator_ReturnsCorrectElements_8) {

    dynArray.Push(1);

    dynArray.Push(2);

    dynArray.Push(3);



    EXPECT_EQ(dynArray[0], 1);

    EXPECT_EQ(dynArray[1], 2);

    EXPECT_EQ(dynArray[2], 3);

}



TEST_F(DynArrayTest_8, Mem_ReturnsPointerToMemory_8) {

    const int* mem = dynArray.Mem();

    EXPECT_TRUE(mem != nullptr);



    dynArray.Push(42);

    EXPECT_EQ(*mem, 42);

}



TEST_F(DynArrayTest_8, SwapRemove_MovesLastElementToFront_8) {

    dynArray.Push(1);

    dynArray.Push(2);

    dynArray.Push(3);



    dynArray.SwapRemove(0); // Remove first element

    EXPECT_EQ(dynArray[0], 3);



    dynArray.SwapRemove(1); // Remove last element (now second element)

    EXPECT_EQ(dynArray.Size(), 1);

}
