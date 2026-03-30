#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class DynArrayTest_11 : public ::testing::Test {

protected:

    using TestType = DynArray<int, 5>;

    TestType dynArray;

};



TEST_F(DynArrayTest_11, InitialState_11) {

    EXPECT_EQ(dynArray.Size(), 0);

    EXPECT_EQ(dynArray.Capacity(), 5);

}



TEST_F(DynArrayTest_11, PushIncreasesSize_11) {

    dynArray.Push(42);

    EXPECT_EQ(dynArray.Size(), 1);

    EXPECT_EQ(dynArray[0], 42);

}



TEST_F(DynArrayTest_11, PopDecreasesSize_11) {

    dynArray.Push(42);

    dynArray.Pop();

    EXPECT_EQ(dynArray.Size(), 0);

}



TEST_F(DynArrayTest_11, PushArrIncreasesSizeCorrectly_11) {

    int* arr = dynArray.PushArr(3);

    for (int i = 0; i < 3; ++i) {

        arr[i] = i;

    }

    EXPECT_EQ(dynArray.Size(), 3);

    EXPECT_EQ(dynArray[2], 2);

}



TEST_F(DynArrayTest_11, PopArrDecreasesSizeCorrectly_11) {

    dynArray.Push(42);

    dynArray.Push(43);

    dynArray.PopArr(1);

    EXPECT_EQ(dynArray.Size(), 1);

}



TEST_F(DynArrayTest_11, PeekTopReturnsLastElement_11) {

    dynArray.Push(42);

    dynArray.Push(43);

    EXPECT_EQ(dynArray.PeekTop(), 43);

}



TEST_F(DynArrayTest_11, EmptyReturnsTrueWhenEmpty_11) {

    EXPECT_TRUE(dynArray.Empty());

}



TEST_F(DynArrayTest_11, EmptyReturnsFalseWhenNotEmpty_11) {

    dynArray.Push(42);

    EXPECT_FALSE(dynArray.Empty());

}



TEST_F(DynArrayTest_11, SwapRemoveMaintainsSizeAndOrder_11) {

    for (int i = 0; i < 5; ++i) {

        dynArray.Push(i);

    }

    dynArray.SwapRemove(2); // Remove element '2'

    EXPECT_EQ(dynArray.Size(), 4);

    EXPECT_EQ(dynArray[2], 4); // Last element is swapped to the removed position

}



TEST_F(DynArrayTest_11, AccessOperatorBoundsCheck_11) {

    dynArray.Push(42);

    EXPECT_THROW({ dynArray[1]; }, std::exception);

}
