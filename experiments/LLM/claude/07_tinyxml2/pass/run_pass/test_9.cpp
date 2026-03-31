#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class DynArrayTest_9 : public ::testing::Test {
protected:
    DynArray<int, 10> arr;
};

// Test initial state
TEST_F(DynArrayTest_9, InitiallyEmpty_9) {
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_9, InitialCapacity_9) {
    EXPECT_GE(arr.Capacity(), 10u);
}

// Test Push and Size
TEST_F(DynArrayTest_9, PushIncreasesSize_9) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.Empty());
}

TEST_F(DynArrayTest_9, PushMultipleElements_9) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    EXPECT_EQ(arr.Size(), 3u);
}

// Test operator[]
TEST_F(DynArrayTest_9, AccessElementsByIndex_9) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

// Test PeekTop
TEST_F(DynArrayTest_9, PeekTopReturnsLastPushed_9) {
    arr.Push(5);
    arr.Push(15);
    EXPECT_EQ(arr.PeekTop(), 15);
}

// Test Pop
TEST_F(DynArrayTest_9, PopReturnsLastElement_9) {
    arr.Push(100);
    arr.Push(200);
    int val = arr.Pop();
    EXPECT_EQ(val, 200);
    EXPECT_EQ(arr.Size(), 1u);
}

TEST_F(DynArrayTest_9, PopDecreasesSize_9) {
    arr.Push(1);
    arr.Push(2);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 1);
}

// Test PushArr
TEST_F(DynArrayTest_9, PushArrIncreasesSize_9) {
    int* ptr = arr.PushArr(5);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(arr.Size(), 5u);
}

TEST_F(DynArrayTest_9, PushArrReturnsWritableMemory_9) {
    int* ptr = arr.PushArr(3);
    ptr[0] = 10;
    ptr[1] = 20;
    ptr[2] = 30;
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

// Test PopArr
TEST_F(DynArrayTest_9, PopArrDecreasesSize_9) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.Push(5);
    arr.PopArr(3);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST_F(DynArrayTest_9, PopArrZeroCount_9) {
    arr.Push(1);
    arr.Push(2);
    arr.PopArr(0);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_9, PopArrEntireArray_9) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.PopArr(3);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// Test Clear
TEST_F(DynArrayTest_9, ClearMakesArrayEmpty_9) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test Empty
TEST_F(DynArrayTest_9, EmptyAfterPushAndPopAll_9) {
    arr.Push(42);
    arr.Pop();
    EXPECT_TRUE(arr.Empty());
}

// Test Mem
TEST_F(DynArrayTest_9, MemReturnsNonNull_9) {
    arr.Push(1);
    const int* mem = arr.Mem();
    EXPECT_NE(mem, nullptr);
    EXPECT_EQ(mem[0], 1);
}

TEST_F(DynArrayTest_9, MemPointsToContiguousData_9) {
    for (int i = 0; i < 5; ++i) {
        arr.Push(i * 10);
    }
    const int* mem = arr.Mem();
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(mem[i], i * 10);
    }
}

// Test SwapRemove
TEST_F(DynArrayTest_9, SwapRemoveDecreasesSize_9) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_9, SwapRemoveSwapsWithLast_9) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(0);
    // After SwapRemove(0), element at index 0 should be the former last element (30)
    EXPECT_EQ(arr[0], 30);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_9, SwapRemoveLastElement_9) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST_F(DynArrayTest_9, SwapRemoveSingleElement_9) {
    arr.Push(42);
    arr.SwapRemove(0);
    EXPECT_TRUE(arr.Empty());
}

// Test growth beyond initial capacity
TEST_F(DynArrayTest_9, GrowBeyondInitialCapacity_9) {
    for (int i = 0; i < 100; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 100u);
    EXPECT_GE(arr.Capacity(), 100u);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

// Test with different types
TEST(DynArrayCharTest_9, WorksWithCharType_9) {
    DynArray<char, 8> charArr;
    charArr.Push('a');
    charArr.Push('b');
    charArr.Push('c');
    EXPECT_EQ(charArr.Size(), 3u);
    EXPECT_EQ(charArr[0], 'a');
    EXPECT_EQ(charArr[1], 'b');
    EXPECT_EQ(charArr[2], 'c');
}

TEST(DynArrayDoubleTest_9, WorksWithDoubleType_9) {
    DynArray<double, 4> dblArr;
    dblArr.Push(1.5);
    dblArr.Push(2.5);
    EXPECT_EQ(dblArr.Size(), 2u);
    EXPECT_DOUBLE_EQ(dblArr[0], 1.5);
    EXPECT_DOUBLE_EQ(dblArr[1], 2.5);
}

// Test with small initial size
TEST(DynArraySmallInitial_9, SmallInitialSize_9) {
    DynArray<int, 1> smallArr;
    EXPECT_GE(smallArr.Capacity(), 1u);
    smallArr.Push(1);
    smallArr.Push(2);
    smallArr.Push(3);
    EXPECT_EQ(smallArr.Size(), 3u);
    EXPECT_EQ(smallArr[0], 1);
    EXPECT_EQ(smallArr[1], 2);
    EXPECT_EQ(smallArr[2], 3);
}

// Test PushArr with zero count
TEST_F(DynArrayTest_9, PushArrZeroCount_9) {
    int* ptr = arr.PushArr(0);
    EXPECT_EQ(arr.Size(), 0u);
    // ptr may or may not be null, but size should remain 0
}

// Test interleaving Push and Pop
TEST_F(DynArrayTest_9, InterleavedPushPop_9) {
    arr.Push(1);
    arr.Push(2);
    EXPECT_EQ(arr.Pop(), 2);
    arr.Push(3);
    arr.Push(4);
    EXPECT_EQ(arr.Pop(), 4);
    EXPECT_EQ(arr.Pop(), 3);
    EXPECT_EQ(arr.Pop(), 1);
    EXPECT_TRUE(arr.Empty());
}

// Test Clear and reuse
TEST_F(DynArrayTest_9, ClearAndReuse_9) {
    for (int i = 0; i < 20; ++i) {
        arr.Push(i);
    }
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    arr.Push(99);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 99);
}

// Test Capacity never less than Size
TEST_F(DynArrayTest_9, CapacityAlwaysGreaterOrEqualToSize_9) {
    for (int i = 0; i < 50; ++i) {
        arr.Push(i);
        EXPECT_GE(arr.Capacity(), arr.Size());
    }
}

// Test PeekTop after multiple operations
TEST_F(DynArrayTest_9, PeekTopAfterOperations_9) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr.PeekTop(), 30);
    arr.Pop();
    EXPECT_EQ(arr.PeekTop(), 20);
    arr.Pop();
    EXPECT_EQ(arr.PeekTop(), 10);
}
