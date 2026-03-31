#include <gtest/gtest.h>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Use a concrete instantiation of DynArray with a small initial size for testing
using TestDynArray = DynArray<int, 4>;

class DynArrayTest_7 : public ::testing::Test {
protected:
    TestDynArray arr;
};

// ==================== Construction Tests ====================

TEST_F(DynArrayTest_7, DefaultConstructorCreatesEmptyArray_7) {
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_7, DefaultConstructorHasInitialCapacity_7) {
    EXPECT_GE(arr.Capacity(), 4u);
}

// ==================== Push Tests ====================

TEST_F(DynArrayTest_7, PushIncreasesSize_7) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.Empty());
}

TEST_F(DynArrayTest_7, PushMultipleElements_7) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    EXPECT_EQ(arr.Size(), 3u);
}

TEST_F(DynArrayTest_7, PushAndAccessByIndex_7) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST_F(DynArrayTest_7, PushBeyondInitialCapacity_7) {
    // Initial capacity is 4, push more than that
    for (int i = 0; i < 10; ++i) {
        arr.Push(i * 10);
    }
    EXPECT_EQ(arr.Size(), 10u);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(arr[i], i * 10);
    }
}

// ==================== PushArr Tests ====================

TEST_F(DynArrayTest_7, PushArrReturnsPointerToNewElements_7) {
    int* ptr = arr.PushArr(3);
    ASSERT_NE(ptr, nullptr);
    ptr[0] = 100;
    ptr[1] = 200;
    ptr[2] = 300;
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
}

TEST_F(DynArrayTest_7, PushArrWithZeroCount_7) {
    arr.Push(5);
    int* ptr = arr.PushArr(0);
    EXPECT_EQ(arr.Size(), 1u);
    // ptr should still be valid (pointing at end)
    ASSERT_NE(ptr, nullptr);
}

TEST_F(DynArrayTest_7, PushArrBeyondInitialCapacity_7) {
    int* ptr = arr.PushArr(10);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(arr.Size(), 10u);
    EXPECT_GE(arr.Capacity(), 10u);
    for (size_t i = 0; i < 10; ++i) {
        ptr[i] = static_cast<int>(i);
    }
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(arr[i], static_cast<int>(i));
    }
}

TEST_F(DynArrayTest_7, PushArrAfterPush_7) {
    arr.Push(1);
    arr.Push(2);
    int* ptr = arr.PushArr(3);
    ptr[0] = 10;
    ptr[1] = 20;
    ptr[2] = 30;
    EXPECT_EQ(arr.Size(), 5u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 10);
    EXPECT_EQ(arr[3], 20);
    EXPECT_EQ(arr[4], 30);
}

// ==================== Pop Tests ====================

TEST_F(DynArrayTest_7, PopReturnsMostRecentElement_7) {
    arr.Push(42);
    arr.Push(99);
    int val = arr.Pop();
    EXPECT_EQ(val, 99);
    EXPECT_EQ(arr.Size(), 1u);
}

TEST_F(DynArrayTest_7, PopDecreasesSize_7) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 2u);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 1u);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// ==================== PopArr Tests ====================

TEST_F(DynArrayTest_7, PopArrDecreasesSize_7) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.PopArr(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST_F(DynArrayTest_7, PopArrAllElements_7) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.PopArr(3);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_7, PopArrZeroElements_7) {
    arr.Push(1);
    arr.Push(2);
    arr.PopArr(0);
    EXPECT_EQ(arr.Size(), 2u);
}

// ==================== Empty Tests ====================

TEST_F(DynArrayTest_7, EmptyOnNewArray_7) {
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_7, NotEmptyAfterPush_7) {
    arr.Push(1);
    EXPECT_FALSE(arr.Empty());
}

TEST_F(DynArrayTest_7, EmptyAfterPushAndPop_7) {
    arr.Push(1);
    arr.Pop();
    EXPECT_TRUE(arr.Empty());
}

// ==================== PeekTop Tests ====================

TEST_F(DynArrayTest_7, PeekTopReturnsLastElement_7) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr.PeekTop(), 30);
}

TEST_F(DynArrayTest_7, PeekTopDoesNotModifyArray_7) {
    arr.Push(5);
    arr.Push(10);
    const int& top = arr.PeekTop();
    EXPECT_EQ(top, 10);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_7, PeekTopAfterPop_7) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Pop();
    EXPECT_EQ(arr.PeekTop(), 2);
}

// ==================== Size and Capacity Tests ====================

TEST_F(DynArrayTest_7, SizeReflectsElementCount_7) {
    EXPECT_EQ(arr.Size(), 0u);
    arr.Push(1);
    EXPECT_EQ(arr.Size(), 1u);
    arr.Push(2);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_7, CapacityGrowsAsNeeded_7) {
    size_t initialCap = arr.Capacity();
    EXPECT_GE(initialCap, 4u);
    // Push more than initial capacity
    for (int i = 0; i < 20; ++i) {
        arr.Push(i);
    }
    EXPECT_GE(arr.Capacity(), 20u);
}

// ==================== Clear Tests ====================

TEST_F(DynArrayTest_7, ClearMakesArrayEmpty_7) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_7, ClearOnEmptyArray_7) {
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_7, PushAfterClear_7) {
    arr.Push(1);
    arr.Push(2);
    arr.Clear();
    arr.Push(99);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 99);
}

// ==================== Operator[] Tests ====================

TEST_F(DynArrayTest_7, OperatorIndexAccess_7) {
    arr.Push(10);
    arr.Push(20);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST_F(DynArrayTest_7, OperatorIndexModification_7) {
    arr.Push(10);
    arr.Push(20);
    arr[0] = 99;
    EXPECT_EQ(arr[0], 99);
    EXPECT_EQ(arr[1], 20);
}

// ==================== SwapRemove Tests ====================

TEST_F(DynArrayTest_7, SwapRemoveFromMiddle_7) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.SwapRemove(1); // Remove element at index 1 (value 2), swap with last (4)
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 1);
    // The element at index 1 should now be 4 (the last element)
    EXPECT_EQ(arr[1], 4);
    EXPECT_EQ(arr[2], 3);
}

TEST_F(DynArrayTest_7, SwapRemoveLastElement_7) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.SwapRemove(2); // Remove last element
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST_F(DynArrayTest_7, SwapRemoveFirstElement_7) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 2u);
    // First element should be replaced by the last
    EXPECT_EQ(arr[0], 30);
    EXPECT_EQ(arr[1], 20);
}

TEST_F(DynArrayTest_7, SwapRemoveSingleElement_7) {
    arr.Push(42);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// ==================== Mem Tests ====================

TEST_F(DynArrayTest_7, MemReturnsNonNullPointer_7) {
    EXPECT_NE(arr.Mem(), nullptr);
}

TEST_F(DynArrayTest_7, MemPointsToElements_7) {
    arr.Push(11);
    arr.Push(22);
    arr.Push(33);
    const int* mem = arr.Mem();
    EXPECT_EQ(mem[0], 11);
    EXPECT_EQ(mem[1], 22);
    EXPECT_EQ(mem[2], 33);
}

// ==================== Stress / Boundary Tests ====================

TEST_F(DynArrayTest_7, LargeNumberOfElements_7) {
    const int N = 1000;
    for (int i = 0; i < N; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), static_cast<size_t>(N));
    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST_F(DynArrayTest_7, PushArrLargeCount_7) {
    const size_t count = 500;
    int* ptr = arr.PushArr(count);
    ASSERT_NE(ptr, nullptr);
    for (size_t i = 0; i < count; ++i) {
        ptr[i] = static_cast<int>(i * 2);
    }
    EXPECT_EQ(arr.Size(), count);
    for (size_t i = 0; i < count; ++i) {
        EXPECT_EQ(arr[i], static_cast<int>(i * 2));
    }
}

TEST_F(DynArrayTest_7, AlternatePushAndPop_7) {
    for (int i = 0; i < 100; ++i) {
        arr.Push(i);
        EXPECT_EQ(arr.PeekTop(), i);
        int val = arr.Pop();
        EXPECT_EQ(val, i);
        EXPECT_TRUE(arr.Empty());
    }
}

TEST_F(DynArrayTest_7, ClearAndReuseMultipleTimes_7) {
    for (int cycle = 0; cycle < 5; ++cycle) {
        for (int i = 0; i < 20; ++i) {
            arr.Push(cycle * 100 + i);
        }
        EXPECT_EQ(arr.Size(), 20u);
        arr.Clear();
        EXPECT_TRUE(arr.Empty());
    }
}

// ==================== Different Type Tests ====================

TEST(DynArrayCharTest_7, WorksWithCharType_7) {
    DynArray<char, 8> charArr;
    charArr.Push('a');
    charArr.Push('b');
    charArr.Push('c');
    EXPECT_EQ(charArr.Size(), 3u);
    EXPECT_EQ(charArr[0], 'a');
    EXPECT_EQ(charArr[1], 'b');
    EXPECT_EQ(charArr[2], 'c');
    EXPECT_EQ(charArr.PeekTop(), 'c');
    char val = charArr.Pop();
    EXPECT_EQ(val, 'c');
    EXPECT_EQ(charArr.Size(), 2u);
}

TEST(DynArrayDoubleTest_7, WorksWithDoubleType_7) {
    DynArray<double, 2> dblArr;
    dblArr.Push(1.5);
    dblArr.Push(2.5);
    dblArr.Push(3.5); // beyond initial capacity
    dblArr.Push(4.5);
    EXPECT_EQ(dblArr.Size(), 4u);
    EXPECT_DOUBLE_EQ(dblArr[0], 1.5);
    EXPECT_DOUBLE_EQ(dblArr[1], 2.5);
    EXPECT_DOUBLE_EQ(dblArr[2], 3.5);
    EXPECT_DOUBLE_EQ(dblArr[3], 4.5);
}

TEST(DynArraySmallInitialSize_7, InitialSizeOne_7) {
    DynArray<int, 1> smallArr;
    EXPECT_GE(smallArr.Capacity(), 1u);
    smallArr.Push(10);
    smallArr.Push(20); // triggers growth
    EXPECT_EQ(smallArr.Size(), 2u);
    EXPECT_EQ(smallArr[0], 10);
    EXPECT_EQ(smallArr[1], 20);
}

// ==================== PushArr followed by Push ====================

TEST_F(DynArrayTest_7, PushArrFollowedByPush_7) {
    int* ptr = arr.PushArr(2);
    ptr[0] = 100;
    ptr[1] = 200;
    arr.Push(300);
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
}

// ==================== Mem consistency after growth ====================

TEST_F(DynArrayTest_7, MemConsistentAfterGrowth_7) {
    for (int i = 0; i < 50; ++i) {
        arr.Push(i);
    }
    const int* mem = arr.Mem();
    for (size_t i = 0; i < arr.Size(); ++i) {
        EXPECT_EQ(mem[i], static_cast<int>(i));
    }
}
