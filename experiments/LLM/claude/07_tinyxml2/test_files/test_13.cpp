#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Use a concrete instantiation with a reasonable INITIAL_SIZE
using IntDynArray = DynArray<int, 8>;
using CharDynArray = DynArray<char, 4>;

class DynArrayTest_13 : public ::testing::Test {
protected:
    IntDynArray arr;
    CharDynArray charArr;
};

// --- Size tests ---

TEST_F(DynArrayTest_13, InitialSizeIsZero_13) {
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_13, SizeAfterPush_13) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
}

TEST_F(DynArrayTest_13, SizeAfterMultiplePushes_13) {
    for (int i = 0; i < 10; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 10u);
}

// --- Empty tests ---

TEST_F(DynArrayTest_13, EmptyOnConstruction_13) {
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_13, NotEmptyAfterPush_13) {
    arr.Push(1);
    EXPECT_FALSE(arr.Empty());
}

TEST_F(DynArrayTest_13, EmptyAfterPushAndPop_13) {
    arr.Push(1);
    arr.Pop();
    EXPECT_TRUE(arr.Empty());
}

// --- Push and Pop tests ---

TEST_F(DynArrayTest_13, PushAndPopReturnsCorrectValue_13) {
    arr.Push(99);
    EXPECT_EQ(arr.Pop(), 99);
}

TEST_F(DynArrayTest_13, PushMultipleAndPopInLIFOOrder_13) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    EXPECT_EQ(arr.Pop(), 3);
    EXPECT_EQ(arr.Pop(), 2);
    EXPECT_EQ(arr.Pop(), 1);
}

TEST_F(DynArrayTest_13, PopDecreasesSize_13) {
    arr.Push(10);
    arr.Push(20);
    EXPECT_EQ(arr.Size(), 2u);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 1u);
}

// --- PushArr tests ---

TEST_F(DynArrayTest_13, PushArrIncreasesSize_13) {
    int* ptr = arr.PushArr(5);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(arr.Size(), 5u);
}

TEST_F(DynArrayTest_13, PushArrReturnsWritableMemory_13) {
    int* ptr = arr.PushArr(3);
    ptr[0] = 10;
    ptr[1] = 20;
    ptr[2] = 30;
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST_F(DynArrayTest_13, PushArrZeroElements_13) {
    arr.PushArr(0);
    EXPECT_EQ(arr.Size(), 0u);
}

// --- PopArr tests ---

TEST_F(DynArrayTest_13, PopArrDecreasesSize_13) {
    for (int i = 0; i < 5; ++i) {
        arr.Push(i);
    }
    arr.PopArr(3);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_13, PopArrAllElements_13) {
    arr.Push(1);
    arr.Push(2);
    arr.PopArr(2);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// --- operator[] tests ---

TEST_F(DynArrayTest_13, OperatorIndexAccess_13) {
    arr.Push(100);
    arr.Push(200);
    arr.Push(300);
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
}

TEST_F(DynArrayTest_13, OperatorIndexModify_13) {
    arr.Push(10);
    arr[0] = 999;
    EXPECT_EQ(arr[0], 999);
}

// --- PeekTop tests ---

TEST_F(DynArrayTest_13, PeekTopReturnsLastElement_13) {
    arr.Push(5);
    arr.Push(10);
    EXPECT_EQ(arr.PeekTop(), 10);
}

TEST_F(DynArrayTest_13, PeekTopDoesNotRemoveElement_13) {
    arr.Push(42);
    arr.PeekTop();
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr.PeekTop(), 42);
}

// --- Clear tests ---

TEST_F(DynArrayTest_13, ClearMakesEmpty_13) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_13, ClearOnEmptyArray_13) {
    arr.Clear();
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_13, PushAfterClear_13) {
    arr.Push(1);
    arr.Push(2);
    arr.Clear();
    arr.Push(99);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 99);
}

// --- Capacity tests ---

TEST_F(DynArrayTest_13, InitialCapacity_13) {
    EXPECT_GE(arr.Capacity(), 8u);
}

TEST_F(DynArrayTest_13, CapacityGrowsWhenExceedingInitialSize_13) {
    for (int i = 0; i < 20; ++i) {
        arr.Push(i);
    }
    EXPECT_GE(arr.Capacity(), 20u);
    EXPECT_EQ(arr.Size(), 20u);
}

// --- Mem tests ---

TEST_F(DynArrayTest_13, MemReturnsNonNull_13) {
    arr.Push(1);
    EXPECT_NE(arr.Mem(), nullptr);
}

TEST_F(DynArrayTest_13, MemPointsToCorrectData_13) {
    arr.Push(10);
    arr.Push(20);
    const int* mem = arr.Mem();
    EXPECT_EQ(mem[0], 10);
    EXPECT_EQ(mem[1], 20);
}

// --- SwapRemove tests ---

TEST_F(DynArrayTest_13, SwapRemoveDecreasesSize_13) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_13, SwapRemoveLastElement_13) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST_F(DynArrayTest_13, SwapRemoveFirstElementSwapsWithLast_13) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 2u);
    // The last element (30) should have replaced the first element
    EXPECT_EQ(arr[0], 30);
    EXPECT_EQ(arr[1], 20);
}

TEST_F(DynArrayTest_13, SwapRemoveMiddleElement_13) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.SwapRemove(1);
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 1);
    // Element at index 1 should now be what was the last element (4)
    EXPECT_EQ(arr[1], 4);
    EXPECT_EQ(arr[2], 3);
}

TEST_F(DynArrayTest_13, SwapRemoveSingleElement_13) {
    arr.Push(42);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// --- Growth beyond initial pool tests ---

TEST_F(DynArrayTest_13, GrowBeyondInitialPool_13) {
    // Initial size is 8, push more than that
    for (int i = 0; i < 100; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 100u);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

// --- Char array tests ---

TEST_F(DynArrayTest_13, CharArrayPushAndAccess_13) {
    charArr.Push('a');
    charArr.Push('b');
    charArr.Push('c');
    EXPECT_EQ(charArr.Size(), 3u);
    EXPECT_EQ(charArr[0], 'a');
    EXPECT_EQ(charArr[1], 'b');
    EXPECT_EQ(charArr[2], 'c');
}

TEST_F(DynArrayTest_13, CharArrayGrowBeyondPool_13) {
    // Pool size is 4
    for (char c = 'a'; c <= 'z'; ++c) {
        charArr.Push(c);
    }
    EXPECT_EQ(charArr.Size(), 26u);
    for (int i = 0; i < 26; ++i) {
        EXPECT_EQ(charArr[i], 'a' + i);
    }
}

// --- Boundary: push exactly INITIAL_SIZE elements ---

TEST_F(DynArrayTest_13, PushExactlyInitialSizeElements_13) {
    for (int i = 0; i < 8; ++i) {
        arr.Push(i * 10);
    }
    EXPECT_EQ(arr.Size(), 8u);
    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(arr[i], i * 10);
    }
}

TEST_F(DynArrayTest_13, PushOneMoreThanInitialSize_13) {
    for (int i = 0; i < 9; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 9u);
    for (int i = 0; i < 9; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

// --- Destructor / scope tests ---

TEST_F(DynArrayTest_13, ArrayCanBeDestroyedAfterGrowth_13) {
    // This test verifies no crash on destruction after dynamic allocation
    IntDynArray* dynArr = new IntDynArray();
    for (int i = 0; i < 50; ++i) {
        dynArr->Push(i);
    }
    EXPECT_EQ(dynArr->Size(), 50u);
    delete dynArr; // Should not crash
}

// --- Mixed operations ---

TEST_F(DynArrayTest_13, MixedPushPopPeekOperations_13) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    EXPECT_EQ(arr.PeekTop(), 3);
    EXPECT_EQ(arr.Pop(), 3);
    EXPECT_EQ(arr.PeekTop(), 2);
    arr.Push(4);
    EXPECT_EQ(arr.PeekTop(), 4);
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 4);
}

TEST_F(DynArrayTest_13, ClearAndRegrow_13) {
    for (int i = 0; i < 20; ++i) {
        arr.Push(i);
    }
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    for (int i = 100; i < 110; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 10u);
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[9], 109);
}

TEST_F(DynArrayTest_13, PopArrZeroElements_13) {
    arr.Push(1);
    arr.Push(2);
    arr.PopArr(0);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_13, MemOnEmptyArray_13) {
    // Mem should still return a valid pointer (pointing to the pool)
    const int* mem = arr.Mem();
    EXPECT_NE(mem, nullptr);
}

TEST_F(DynArrayTest_13, CapacityNeverLessThanSize_13) {
    for (int i = 0; i < 50; ++i) {
        arr.Push(i);
        EXPECT_GE(arr.Capacity(), arr.Size());
    }
}
