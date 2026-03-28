#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Test fixture for DynArray tests
class DynArrayTest_8 : public ::testing::Test {
protected:
    DynArray<int, 4> arr;
};

// --- Normal Operation Tests ---

TEST_F(DynArrayTest_8, DefaultConstructorCreatesEmptyArray_8) {
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_8, PushIncreasesSize_8) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.Empty());
}

TEST_F(DynArrayTest_8, PushAndAccessElement_8) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST_F(DynArrayTest_8, PopReturnsLastElement_8) {
    arr.Push(100);
    arr.Push(200);
    arr.Push(300);
    int val = arr.Pop();
    EXPECT_EQ(val, 300);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_8, PopDecreasesSize_8) {
    arr.Push(1);
    arr.Push(2);
    EXPECT_EQ(arr.Size(), 2u);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 1u);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_8, PeekTopReturnsLastElement_8) {
    arr.Push(5);
    arr.Push(15);
    arr.Push(25);
    EXPECT_EQ(arr.PeekTop(), 25);
    // PeekTop should not modify size
    EXPECT_EQ(arr.Size(), 3u);
}

TEST_F(DynArrayTest_8, ClearMakesArrayEmpty_8) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_8, EmptyReturnsTrueForNewArray_8) {
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_8, EmptyReturnsFalseAfterPush_8) {
    arr.Push(42);
    EXPECT_FALSE(arr.Empty());
}

TEST_F(DynArrayTest_8, CapacityIsAtLeastInitialSize_8) {
    EXPECT_GE(arr.Capacity(), 4u);
}

TEST_F(DynArrayTest_8, MemReturnsNonNullPointer_8) {
    EXPECT_NE(arr.Mem(), nullptr);
}

TEST_F(DynArrayTest_8, MemPointsToCorrectData_8) {
    arr.Push(11);
    arr.Push(22);
    arr.Push(33);
    const int* mem = arr.Mem();
    EXPECT_EQ(mem[0], 11);
    EXPECT_EQ(mem[1], 22);
    EXPECT_EQ(mem[2], 33);
}

// --- Boundary Conditions ---

TEST_F(DynArrayTest_8, PushBeyondInitialCapacity_8) {
    // INITIAL_SIZE is 4, push more than 4 elements
    for (int i = 0; i < 10; ++i) {
        arr.Push(i * 10);
    }
    EXPECT_EQ(arr.Size(), 10u);
    EXPECT_GE(arr.Capacity(), 10u);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(arr[i], i * 10);
    }
}

TEST_F(DynArrayTest_8, PushExactlyInitialCapacity_8) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    EXPECT_EQ(arr.Size(), 4u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[3], 4);
}

TEST_F(DynArrayTest_8, PushArrAllocatesMultipleElements_8) {
    int* ptr = arr.PushArr(3);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(arr.Size(), 3u);
    // Fill the pushed array elements
    ptr[0] = 100;
    ptr[1] = 200;
    ptr[2] = 300;
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
}

TEST_F(DynArrayTest_8, PushArrBeyondInitialCapacity_8) {
    int* ptr = arr.PushArr(10);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(arr.Size(), 10u);
    EXPECT_GE(arr.Capacity(), 10u);
}

TEST_F(DynArrayTest_8, PopArrDecreasesSize_8) {
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

TEST_F(DynArrayTest_8, PopArrAllElements_8) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.PopArr(3);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_8, SwapRemoveRemovesElement_8) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.Push(40);
    arr.SwapRemove(1); // Remove element at index 1 (value 20)
    EXPECT_EQ(arr.Size(), 3u);
    // The last element should have been swapped into position 1
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 40); // Last element swapped in
    EXPECT_EQ(arr[2], 30);
}

TEST_F(DynArrayTest_8, SwapRemoveFirstElement_8) {
    arr.Push(100);
    arr.Push(200);
    arr.Push(300);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 300); // Last swapped to first
    EXPECT_EQ(arr[1], 200);
}

TEST_F(DynArrayTest_8, SwapRemoveLastElement_8) {
    arr.Push(100);
    arr.Push(200);
    arr.Push(300);
    arr.SwapRemove(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
}

TEST_F(DynArrayTest_8, SwapRemoveSingleElement_8) {
    arr.Push(42);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_8, PushAfterClear_8) {
    arr.Push(1);
    arr.Push(2);
    arr.Clear();
    arr.Push(99);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 99);
}

TEST_F(DynArrayTest_8, PushAfterPop_8) {
    arr.Push(10);
    arr.Push(20);
    arr.Pop();
    arr.Push(30);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
}

TEST_F(DynArrayTest_8, MultiplePopOperations_8) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    EXPECT_EQ(arr.Pop(), 3);
    EXPECT_EQ(arr.Pop(), 2);
    EXPECT_EQ(arr.Pop(), 1);
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_8, LargeNumberOfElements_8) {
    const int count = 1000;
    for (int i = 0; i < count; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), static_cast<size_t>(count));
    EXPECT_GE(arr.Capacity(), static_cast<size_t>(count));
    for (int i = 0; i < count; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST_F(DynArrayTest_8, OperatorBracketModifiesElement_8) {
    arr.Push(10);
    arr.Push(20);
    arr[0] = 99;
    arr[1] = 88;
    EXPECT_EQ(arr[0], 99);
    EXPECT_EQ(arr[1], 88);
}

TEST_F(DynArrayTest_8, PushArrZeroCount_8) {
    int* ptr = arr.PushArr(0);
    // Pushing 0 should not change size
    EXPECT_EQ(arr.Size(), 0u);
    (void)ptr; // ptr may or may not be meaningful
}

TEST_F(DynArrayTest_8, PopArrZeroCount_8) {
    arr.Push(1);
    arr.Push(2);
    arr.PopArr(0);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test with a different type
class DynArrayCharTest_8 : public ::testing::Test {
protected:
    DynArray<char, 8> arr;
};

TEST_F(DynArrayCharTest_8, PushAndPopChars_8) {
    arr.Push('a');
    arr.Push('b');
    arr.Push('c');
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr.Pop(), 'c');
    EXPECT_EQ(arr.Pop(), 'b');
    EXPECT_EQ(arr.Pop(), 'a');
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayCharTest_8, PeekTopChar_8) {
    arr.Push('x');
    arr.Push('y');
    EXPECT_EQ(arr.PeekTop(), 'y');
    EXPECT_EQ(arr.Size(), 2u);
}

// Test with pointer type
class DynArrayPointerTest_8 : public ::testing::Test {
protected:
    DynArray<int*, 2> arr;
};

TEST_F(DynArrayPointerTest_8, PushAndAccessPointers_8) {
    int a = 10, b = 20;
    arr.Push(&a);
    arr.Push(&b);
    EXPECT_EQ(arr[0], &a);
    EXPECT_EQ(arr[1], &b);
    EXPECT_EQ(*arr[0], 10);
    EXPECT_EQ(*arr[1], 20);
}

TEST_F(DynArrayPointerTest_8, PushBeyondInitialCapacityPointers_8) {
    int vals[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        arr.Push(&vals[i]);
    }
    EXPECT_EQ(arr.Size(), 5u);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(*arr[i], vals[i]);
    }
}

// Test capacity grows
TEST_F(DynArrayTest_8, CapacityGrowsWhenNeeded_8) {
    size_t initialCap = arr.Capacity();
    // Push more than initial capacity
    for (size_t i = 0; i < initialCap + 5; ++i) {
        arr.Push(static_cast<int>(i));
    }
    EXPECT_GT(arr.Capacity(), initialCap);
}

// Test that Mem() returns data consistent with operator[]
TEST_F(DynArrayTest_8, MemConsistentWithBracketOperator_8) {
    arr.Push(7);
    arr.Push(14);
    arr.Push(21);
    const int* mem = arr.Mem();
    for (size_t i = 0; i < arr.Size(); ++i) {
        EXPECT_EQ(mem[i], arr[i]);
    }
}

// Test PushArr followed by regular Push
TEST_F(DynArrayTest_8, PushArrThenPush_8) {
    int* ptr = arr.PushArr(2);
    ptr[0] = 50;
    ptr[1] = 60;
    arr.Push(70);
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 50);
    EXPECT_EQ(arr[1], 60);
    EXPECT_EQ(arr[2], 70);
}

// Test Clear then verify capacity is still valid
TEST_F(DynArrayTest_8, ClearDoesNotInvalidateCapacity_8) {
    for (int i = 0; i < 20; ++i) {
        arr.Push(i);
    }
    size_t capBefore = arr.Capacity();
    arr.Clear();
    EXPECT_EQ(arr.Size(), 0u);
    // Capacity should still be valid (>= 0)
    EXPECT_GE(arr.Capacity(), 0u);
    // Should be able to push again
    arr.Push(999);
    EXPECT_EQ(arr[0], 999);
}

// Test with INITIAL_SIZE of 1
class DynArraySmallInitial_8 : public ::testing::Test {
protected:
    DynArray<int, 1> arr;
};

TEST_F(DynArraySmallInitial_8, SmallInitialCapacityGrows_8) {
    EXPECT_GE(arr.Capacity(), 1u);
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_GE(arr.Capacity(), 3u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}
