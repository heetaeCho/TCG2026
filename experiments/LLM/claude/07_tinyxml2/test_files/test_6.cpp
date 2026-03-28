#include <gtest/gtest.h>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Test fixture for DynArray with int type and default-ish initial size
class DynArrayTest_6 : public ::testing::Test {
protected:
    DynArray<int, 10> arr;
};

// Test that a newly constructed DynArray is empty
TEST_F(DynArrayTest_6, DefaultConstructorIsEmpty_6) {
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test that initial capacity matches INITIAL_SIZE
TEST_F(DynArrayTest_6, DefaultConstructorCapacity_6) {
    EXPECT_EQ(arr.Capacity(), 10u);
}

// Test Push increases size
TEST_F(DynArrayTest_6, PushIncreasesSize_6) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.Empty());
}

// Test Push stores the correct value
TEST_F(DynArrayTest_6, PushStoresCorrectValue_6) {
    arr.Push(42);
    EXPECT_EQ(arr[0], 42);
}

// Test multiple pushes
TEST_F(DynArrayTest_6, MultiplePushes_6) {
    for (int i = 0; i < 5; ++i) {
        arr.Push(i * 10);
    }
    EXPECT_EQ(arr.Size(), 5u);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], i * 10);
    }
}

// Test Push beyond initial capacity triggers growth
TEST_F(DynArrayTest_6, PushBeyondInitialCapacity_6) {
    for (int i = 0; i < 15; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 15u);
    EXPECT_GE(arr.Capacity(), 15u);
    for (int i = 0; i < 15; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

// Test Pop returns the last element
TEST_F(DynArrayTest_6, PopReturnsLastElement_6) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    int val = arr.Pop();
    EXPECT_EQ(val, 30);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test Pop reduces size
TEST_F(DynArrayTest_6, PopReducesSize_6) {
    arr.Push(1);
    arr.Push(2);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 1u);
}

// Test PeekTop returns last element without removing
TEST_F(DynArrayTest_6, PeekTopReturnsLastElement_6) {
    arr.Push(100);
    arr.Push(200);
    EXPECT_EQ(arr.PeekTop(), 200);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test Empty returns true for empty array
TEST_F(DynArrayTest_6, EmptyOnEmptyArray_6) {
    EXPECT_TRUE(arr.Empty());
}

// Test Empty returns false after push
TEST_F(DynArrayTest_6, EmptyReturnsFalseAfterPush_6) {
    arr.Push(1);
    EXPECT_FALSE(arr.Empty());
}

// Test Clear resets the array
TEST_F(DynArrayTest_6, ClearResetsArray_6) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test operator[] access
TEST_F(DynArrayTest_6, OperatorBracketAccess_6) {
    arr.Push(5);
    arr.Push(15);
    arr.Push(25);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 15);
    EXPECT_EQ(arr[2], 25);
}

// Test operator[] modification
TEST_F(DynArrayTest_6, OperatorBracketModification_6) {
    arr.Push(5);
    arr[0] = 99;
    EXPECT_EQ(arr[0], 99);
}

// Test PushArr allocates space and returns pointer
TEST_F(DynArrayTest_6, PushArrAllocatesSpace_6) {
    int* ptr = arr.PushArr(5);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(arr.Size(), 5u);
    // Fill the allocated space
    for (int i = 0; i < 5; ++i) {
        ptr[i] = i + 1;
    }
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], i + 1);
    }
}

// Test PopArr removes multiple elements
TEST_F(DynArrayTest_6, PopArrRemovesElements_6) {
    for (int i = 0; i < 10; ++i) {
        arr.Push(i);
    }
    arr.PopArr(3);
    EXPECT_EQ(arr.Size(), 7u);
    EXPECT_EQ(arr.PeekTop(), 6);
}

// Test SwapRemove removes element and replaces with last
TEST_F(DynArrayTest_6, SwapRemoveMiddleElement_6) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.Push(40);
    arr.SwapRemove(1); // Remove element at index 1 (value 20), replace with last (40)
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 40);
    EXPECT_EQ(arr[2], 30);
}

// Test SwapRemove on last element
TEST_F(DynArrayTest_6, SwapRemoveLastElement_6) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

// Test SwapRemove on first element
TEST_F(DynArrayTest_6, SwapRemoveFirstElement_6) {
    arr.Push(10);
    arr.Push(20);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 20);
}

// Test SwapRemove on single element array
TEST_F(DynArrayTest_6, SwapRemoveSingleElement_6) {
    arr.Push(99);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// Test Mem returns pointer to memory
TEST_F(DynArrayTest_6, MemReturnsPointer_6) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    const int* mem = arr.Mem();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(mem[0], 1);
    EXPECT_EQ(mem[1], 2);
    EXPECT_EQ(mem[2], 3);
}

// Test Mem on empty array is non-null (pool memory)
TEST_F(DynArrayTest_6, MemOnEmptyArrayNonNull_6) {
    const int* mem = arr.Mem();
    EXPECT_NE(mem, nullptr);
}

// Test Size returns 0 on empty
TEST_F(DynArrayTest_6, SizeReturnsZeroOnEmpty_6) {
    EXPECT_EQ(arr.Size(), 0u);
}

// Test capacity grows when pushing beyond initial size
TEST_F(DynArrayTest_6, CapacityGrowsOnDemand_6) {
    size_t initial_cap = arr.Capacity();
    for (size_t i = 0; i <= initial_cap; ++i) {
        arr.Push(static_cast<int>(i));
    }
    EXPECT_GT(arr.Capacity(), initial_cap);
}

// Test with small initial size (1)
class DynArraySmallTest_6 : public ::testing::Test {
protected:
    DynArray<int, 1> arr;
};

TEST_F(DynArraySmallTest_6, SmallInitialSizeGrows_6) {
    EXPECT_EQ(arr.Capacity(), 1u);
    arr.Push(1);
    arr.Push(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_GE(arr.Capacity(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

// Test push and pop sequence
TEST_F(DynArrayTest_6, PushPopSequence_6) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    EXPECT_EQ(arr.Pop(), 3);
    EXPECT_EQ(arr.Pop(), 2);
    arr.Push(4);
    EXPECT_EQ(arr.Pop(), 4);
    EXPECT_EQ(arr.Pop(), 1);
    EXPECT_TRUE(arr.Empty());
}

// Test Clear and reuse
TEST_F(DynArrayTest_6, ClearAndReuse_6) {
    for (int i = 0; i < 20; ++i) {
        arr.Push(i);
    }
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    arr.Push(999);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 999);
}

// Test PushArr followed by Push
TEST_F(DynArrayTest_6, PushArrThenPush_6) {
    int* ptr = arr.PushArr(3);
    ptr[0] = 10;
    ptr[1] = 20;
    ptr[2] = 30;
    arr.Push(40);
    EXPECT_EQ(arr.Size(), 4u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr[3], 40);
}

// Test with char type
class DynArrayCharTest_6 : public ::testing::Test {
protected:
    DynArray<char, 8> arr;
};

TEST_F(DynArrayCharTest_6, PushAndAccessChars_6) {
    arr.Push('a');
    arr.Push('b');
    arr.Push('c');
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 'a');
    EXPECT_EQ(arr[1], 'b');
    EXPECT_EQ(arr[2], 'c');
}

// Test PopArr to empty
TEST_F(DynArrayTest_6, PopArrToEmpty_6) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.PopArr(3);
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test PushArr with zero count
TEST_F(DynArrayTest_6, PushArrZeroCount_6) {
    int* ptr = arr.PushArr(0);
    EXPECT_EQ(arr.Size(), 0u);
    (void)ptr; // Just ensure no crash
}

// Test large number of elements
TEST_F(DynArrayTest_6, LargeNumberOfElements_6) {
    const int N = 1000;
    for (int i = 0; i < N; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), static_cast<size_t>(N));
    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

// Test PeekTop after modifications
TEST_F(DynArrayTest_6, PeekTopAfterModifications_6) {
    arr.Push(10);
    EXPECT_EQ(arr.PeekTop(), 10);
    arr.Push(20);
    EXPECT_EQ(arr.PeekTop(), 20);
    arr.Pop();
    EXPECT_EQ(arr.PeekTop(), 10);
}
