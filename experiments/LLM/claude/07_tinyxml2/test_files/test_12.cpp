#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Test fixture for DynArray
class DynArrayTest_12 : public ::testing::Test {
protected:
    DynArray<int, 4> arr;
};

// Test that a newly constructed DynArray is empty
TEST_F(DynArrayTest_12, DefaultConstructorCreatesEmptyArray_12) {
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test that initial capacity matches INITIAL_SIZE
TEST_F(DynArrayTest_12, InitialCapacityMatchesTemplateParam_12) {
    EXPECT_GE(arr.Capacity(), 4u);
}

// Test Push increases size
TEST_F(DynArrayTest_12, PushIncreasesSize_12) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.Empty());
}

// Test PeekTop returns the last pushed element
TEST_F(DynArrayTest_12, PeekTopReturnsLastPushed_12) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr.PeekTop(), 30);
}

// Test PeekTop with a single element
TEST_F(DynArrayTest_12, PeekTopWithSingleElement_12) {
    arr.Push(99);
    EXPECT_EQ(arr.PeekTop(), 99);
}

// Test Pop returns the last pushed element and decreases size
TEST_F(DynArrayTest_12, PopReturnsLastPushedAndDecreasesSize_12) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    EXPECT_EQ(arr.Pop(), 3);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr.Pop(), 2);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr.Pop(), 1);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// Test operator[] for index access
TEST_F(DynArrayTest_12, OperatorBracketAccessesCorrectElement_12) {
    arr.Push(100);
    arr.Push(200);
    arr.Push(300);
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
}

// Test operator[] can modify elements
TEST_F(DynArrayTest_12, OperatorBracketCanModifyElement_12) {
    arr.Push(5);
    arr[0] = 50;
    EXPECT_EQ(arr[0], 50);
}

// Test Clear resets the array
TEST_F(DynArrayTest_12, ClearResetsArray_12) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test PushArr allocates space for multiple elements
TEST_F(DynArrayTest_12, PushArrAllocatesMultipleElements_12) {
    int* ptr = arr.PushArr(3);
    ASSERT_NE(ptr, nullptr);
    ptr[0] = 10;
    ptr[1] = 20;
    ptr[2] = 30;
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

// Test PopArr removes multiple elements
TEST_F(DynArrayTest_12, PopArrRemovesMultipleElements_12) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.PopArr(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

// Test that pushing beyond initial size triggers capacity growth
TEST_F(DynArrayTest_12, PushBeyondInitialSizeGrowsCapacity_12) {
    for (int i = 0; i < 10; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 10u);
    EXPECT_GE(arr.Capacity(), 10u);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

// Test PeekTop after push and pop operations
TEST_F(DynArrayTest_12, PeekTopAfterPushAndPop_12) {
    arr.Push(5);
    arr.Push(10);
    arr.Pop();
    EXPECT_EQ(arr.PeekTop(), 5);
}

// Test Mem returns a pointer to the data
TEST_F(DynArrayTest_12, MemReturnsPointerToData_12) {
    arr.Push(42);
    arr.Push(43);
    const int* mem = arr.Mem();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(mem[0], 42);
    EXPECT_EQ(mem[1], 43);
}

// Test Empty returns true for empty array, false otherwise
TEST_F(DynArrayTest_12, EmptyReturnsTrueWhenEmptyFalseOtherwise_12) {
    EXPECT_TRUE(arr.Empty());
    arr.Push(1);
    EXPECT_FALSE(arr.Empty());
    arr.Pop();
    EXPECT_TRUE(arr.Empty());
}

// Test SwapRemove removes element and swaps with last
TEST_F(DynArrayTest_12, SwapRemoveSwapsWithLastAndRemoves_12) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.Push(40);
    arr.SwapRemove(1); // Remove element at index 1 (value 20), swap with last (40)
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 40); // 40 was swapped into position 1
    EXPECT_EQ(arr[2], 30);
}

// Test SwapRemove on last element
TEST_F(DynArrayTest_12, SwapRemoveLastElement_12) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(2); // Remove last element
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

// Test SwapRemove on single element array
TEST_F(DynArrayTest_12, SwapRemoveSingleElement_12) {
    arr.Push(42);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// Test SwapRemove on first element
TEST_F(DynArrayTest_12, SwapRemoveFirstElement_12) {
    arr.Push(1);
    arr.Push(2);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 2);
}

// Test PushArr with zero count
TEST_F(DynArrayTest_12, PushArrZeroCount_12) {
    size_t sizeBefore = arr.Size();
    arr.PushArr(0);
    EXPECT_EQ(arr.Size(), sizeBefore);
}

// Test large number of pushes to stress capacity growth
TEST_F(DynArrayTest_12, LargePushStressTest_12) {
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

// Test PeekTop is const-correct
TEST_F(DynArrayTest_12, PeekTopConstCorrectness_12) {
    arr.Push(7);
    const DynArray<int, 4>& constRef = arr;
    EXPECT_EQ(constRef.PeekTop(), 7);
}

// Test with different type (double)
TEST(DynArrayTypeTest_12, WorksWithDouble_12) {
    DynArray<double, 2> darr;
    darr.Push(1.5);
    darr.Push(2.5);
    darr.Push(3.5);
    EXPECT_DOUBLE_EQ(darr.PeekTop(), 3.5);
    EXPECT_EQ(darr.Size(), 3u);
    EXPECT_DOUBLE_EQ(darr.Pop(), 3.5);
    EXPECT_EQ(darr.Size(), 2u);
}

// Test with char type
TEST(DynArrayTypeTest_12, WorksWithChar_12) {
    DynArray<char, 8> carr;
    carr.Push('a');
    carr.Push('b');
    carr.Push('c');
    EXPECT_EQ(carr.PeekTop(), 'c');
    EXPECT_EQ(carr[0], 'a');
    EXPECT_EQ(carr[1], 'b');
    EXPECT_EQ(carr.Size(), 3u);
}

// Test Clear followed by Push
TEST_F(DynArrayTest_12, ClearThenPush_12) {
    arr.Push(1);
    arr.Push(2);
    arr.Clear();
    arr.Push(99);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 99);
    EXPECT_EQ(arr.PeekTop(), 99);
}

// Test PopArr all elements
TEST_F(DynArrayTest_12, PopArrAllElements_12) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.PopArr(3);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// Test that capacity is at least as large as size after many pushes
TEST_F(DynArrayTest_12, CapacityAlwaysAtLeastSize_12) {
    for (int i = 0; i < 50; ++i) {
        arr.Push(i);
        EXPECT_GE(arr.Capacity(), arr.Size());
    }
}

// Test Size returns correct count through multiple operations
TEST_F(DynArrayTest_12, SizeTracksThroughOperations_12) {
    EXPECT_EQ(arr.Size(), 0u);
    arr.Push(1);
    EXPECT_EQ(arr.Size(), 1u);
    arr.Push(2);
    EXPECT_EQ(arr.Size(), 2u);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 1u);
    arr.PushArr(5);
    EXPECT_EQ(arr.Size(), 6u);
    arr.PopArr(3);
    EXPECT_EQ(arr.Size(), 3u);
    arr.Clear();
    EXPECT_EQ(arr.Size(), 0u);
}
