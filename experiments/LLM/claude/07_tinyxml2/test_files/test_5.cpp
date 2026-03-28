#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class DynArrayTest_5 : public ::testing::Test {
protected:
    DynArray<int, 8> arr;
};

// --- Construction Tests ---

TEST_F(DynArrayTest_5, DefaultConstructorCreatesEmptyArray_5) {
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_5, DefaultConstructorHasInitialCapacity_5) {
    EXPECT_GE(arr.Capacity(), 8u);
}

// --- Push Tests ---

TEST_F(DynArrayTest_5, PushIncreasesSize_5) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.Empty());
}

TEST_F(DynArrayTest_5, PushMultipleElements_5) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    EXPECT_EQ(arr.Size(), 3u);
}

TEST_F(DynArrayTest_5, PushAndAccessByIndex_5) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST_F(DynArrayTest_5, PushBeyondInitialCapacity_5) {
    for (int i = 0; i < 20; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 20u);
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

// --- PushArr Tests ---

TEST_F(DynArrayTest_5, PushArrReturnsPointerAndIncreasesSize_5) {
    int* ptr = arr.PushArr(5);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(arr.Size(), 5u);
}

TEST_F(DynArrayTest_5, PushArrWritableMemory_5) {
    int* ptr = arr.PushArr(3);
    ptr[0] = 100;
    ptr[1] = 200;
    ptr[2] = 300;
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
}

TEST_F(DynArrayTest_5, PushArrBeyondInitialCapacity_5) {
    int* ptr = arr.PushArr(20);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(arr.Size(), 20u);
    EXPECT_GE(arr.Capacity(), 20u);
}

// --- Pop Tests ---

TEST_F(DynArrayTest_5, PopReturnsLastElement_5) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    int val = arr.Pop();
    EXPECT_EQ(val, 30);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_5, PopDecreasesSize_5) {
    arr.Push(1);
    arr.Push(2);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 1u);
}

TEST_F(DynArrayTest_5, PopAllElements_5) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Pop();
    arr.Pop();
    arr.Pop();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// --- PopArr Tests ---

TEST_F(DynArrayTest_5, PopArrDecreasesSize_5) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.Push(5);
    arr.PopArr(3);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_5, PopArrAllElements_5) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.PopArr(3);
    EXPECT_TRUE(arr.Empty());
}

// --- Empty Tests ---

TEST_F(DynArrayTest_5, EmptyReturnsTrueForNewArray_5) {
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_5, EmptyReturnsFalseAfterPush_5) {
    arr.Push(1);
    EXPECT_FALSE(arr.Empty());
}

TEST_F(DynArrayTest_5, EmptyReturnsTrueAfterClear_5) {
    arr.Push(1);
    arr.Push(2);
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
}

// --- Clear Tests ---

TEST_F(DynArrayTest_5, ClearResetsSize_5) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_5, ClearOnEmptyArray_5) {
    arr.Clear();
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_5, ClearThenPushWorks_5) {
    arr.Push(1);
    arr.Push(2);
    arr.Clear();
    arr.Push(99);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 99);
}

// --- PeekTop Tests ---

TEST_F(DynArrayTest_5, PeekTopReturnsLastElement_5) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr.PeekTop(), 30);
}

TEST_F(DynArrayTest_5, PeekTopDoesNotRemoveElement_5) {
    arr.Push(42);
    EXPECT_EQ(arr.PeekTop(), 42);
    EXPECT_EQ(arr.Size(), 1u);
}

// --- Size Tests ---

TEST_F(DynArrayTest_5, SizeReflectsPushAndPop_5) {
    EXPECT_EQ(arr.Size(), 0u);
    arr.Push(1);
    EXPECT_EQ(arr.Size(), 1u);
    arr.Push(2);
    EXPECT_EQ(arr.Size(), 2u);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 1u);
}

// --- Capacity Tests ---

TEST_F(DynArrayTest_5, CapacityAtLeastInitialSize_5) {
    EXPECT_GE(arr.Capacity(), 8u);
}

TEST_F(DynArrayTest_5, CapacityGrowsWhenNeeded_5) {
    for (int i = 0; i < 20; ++i) {
        arr.Push(i);
    }
    EXPECT_GE(arr.Capacity(), 20u);
}

// --- Operator[] Tests ---

TEST_F(DynArrayTest_5, OperatorBracketAccessAndModify_5) {
    arr.Push(10);
    arr.Push(20);
    arr[0] = 100;
    arr[1] = 200;
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
}

// --- SwapRemove Tests ---

TEST_F(DynArrayTest_5, SwapRemoveRemovesElementAndDecreaseSize_5) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.Push(40);
    arr.SwapRemove(1); // Remove element at index 1 (value 20), replaced by last element (40)
    EXPECT_EQ(arr.Size(), 3u);
}

TEST_F(DynArrayTest_5, SwapRemoveFirstElement_5) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 2u);
    // The last element (30) should have been swapped into position 0
    EXPECT_EQ(arr[0], 30);
    EXPECT_EQ(arr[1], 20);
}

TEST_F(DynArrayTest_5, SwapRemoveLastElement_5) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST_F(DynArrayTest_5, SwapRemoveOnlyElement_5) {
    arr.Push(42);
    arr.SwapRemove(0);
    EXPECT_TRUE(arr.Empty());
}

// --- Mem Tests ---

TEST_F(DynArrayTest_5, MemReturnsPointerToData_5) {
    arr.Push(5);
    arr.Push(10);
    const int* mem = arr.Mem();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(mem[0], 5);
    EXPECT_EQ(mem[1], 10);
}

TEST_F(DynArrayTest_5, MemOnEmptyArrayNotNull_5) {
    const int* mem = arr.Mem();
    EXPECT_NE(mem, nullptr);
}

// --- Different Template Parameters ---

TEST(DynArrayDifferentTypes_5, WorksWithChar_5) {
    DynArray<char, 4> charArr;
    charArr.Push('a');
    charArr.Push('b');
    charArr.Push('c');
    EXPECT_EQ(charArr.Size(), 3u);
    EXPECT_EQ(charArr[0], 'a');
    EXPECT_EQ(charArr[1], 'b');
    EXPECT_EQ(charArr[2], 'c');
}

TEST(DynArrayDifferentTypes_5, WorksWithDouble_5) {
    DynArray<double, 2> dblArr;
    dblArr.Push(1.5);
    dblArr.Push(2.5);
    dblArr.Push(3.5); // exceeds initial size of 2
    EXPECT_EQ(dblArr.Size(), 3u);
    EXPECT_DOUBLE_EQ(dblArr[0], 1.5);
    EXPECT_DOUBLE_EQ(dblArr[1], 2.5);
    EXPECT_DOUBLE_EQ(dblArr[2], 3.5);
}

TEST(DynArrayDifferentTypes_5, SmallInitialSize_5) {
    DynArray<int, 1> smallArr;
    smallArr.Push(1);
    smallArr.Push(2);
    smallArr.Push(3);
    EXPECT_EQ(smallArr.Size(), 3u);
    EXPECT_GE(smallArr.Capacity(), 3u);
}

// --- Complex Interaction Tests ---

TEST_F(DynArrayTest_5, PushClearPushSequence_5) {
    for (int i = 0; i < 10; ++i) {
        arr.Push(i);
    }
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    
    for (int i = 100; i < 105; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 5u);
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[4], 104);
}

TEST_F(DynArrayTest_5, PushPopPushSequence_5) {
    arr.Push(1);
    arr.Push(2);
    arr.Pop();
    arr.Push(3);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST_F(DynArrayTest_5, PeekTopAfterPop_5) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.Pop();
    EXPECT_EQ(arr.PeekTop(), 20);
}

TEST_F(DynArrayTest_5, PushArrFollowedByPush_5) {
    int* ptr = arr.PushArr(3);
    ptr[0] = 1;
    ptr[1] = 2;
    ptr[2] = 3;
    arr.Push(4);
    EXPECT_EQ(arr.Size(), 4u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
}

TEST_F(DynArrayTest_5, PopArrFollowedByPeekTop_5) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.Push(5);
    arr.PopArr(2);
    EXPECT_EQ(arr.PeekTop(), 3);
}

TEST_F(DynArrayTest_5, LargeNumberOfElements_5) {
    const int N = 1000;
    for (int i = 0; i < N; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), static_cast<size_t>(N));
    EXPECT_GE(arr.Capacity(), static_cast<size_t>(N));
    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST_F(DynArrayTest_5, SwapRemoveMiddleElementVerifyContent_5) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.Push(40);
    arr.Push(50);
    arr.SwapRemove(2); // Remove 30, replaced by 50
    EXPECT_EQ(arr.Size(), 4u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 50);
    EXPECT_EQ(arr[3], 40);
}

TEST_F(DynArrayTest_5, MemConsistencyAfterMultipleOperations_5) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Pop();
    arr.Push(4);
    
    const int* mem = arr.Mem();
    EXPECT_EQ(mem[0], 1);
    EXPECT_EQ(mem[1], 2);
    EXPECT_EQ(mem[2], 4);
}
