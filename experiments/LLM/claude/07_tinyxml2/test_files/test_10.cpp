#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class DynArrayTest_10 : public ::testing::Test {
protected:
    DynArray<int, 8> arr;
};

// Test that a newly constructed DynArray is empty
TEST_F(DynArrayTest_10, DefaultConstructorIsEmpty_10) {
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test that initial capacity matches INITIAL_SIZE
TEST_F(DynArrayTest_10, DefaultCapacity_10) {
    EXPECT_EQ(arr.Capacity(), 8u);
}

// Test Push adds an element and array is no longer empty
TEST_F(DynArrayTest_10, PushMakesNonEmpty_10) {
    arr.Push(42);
    EXPECT_FALSE(arr.Empty());
    EXPECT_EQ(arr.Size(), 1u);
}

// Test Push and access via operator[]
TEST_F(DynArrayTest_10, PushAndAccess_10) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr.Size(), 3u);
}

// Test Pop returns the last pushed element
TEST_F(DynArrayTest_10, PopReturnsLastElement_10) {
    arr.Push(5);
    arr.Push(15);
    arr.Push(25);
    int val = arr.Pop();
    EXPECT_EQ(val, 25);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test Pop until empty
TEST_F(DynArrayTest_10, PopUntilEmpty_10) {
    arr.Push(1);
    arr.Push(2);
    arr.Pop();
    arr.Pop();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test PeekTop returns last element without removing
TEST_F(DynArrayTest_10, PeekTopReturnsLast_10) {
    arr.Push(100);
    arr.Push(200);
    EXPECT_EQ(arr.PeekTop(), 200);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test Clear empties the array
TEST_F(DynArrayTest_10, ClearMakesEmpty_10) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test PushArr allocates space for multiple elements
TEST_F(DynArrayTest_10, PushArrAllocatesSpace_10) {
    int* ptr = arr.PushArr(5);
    ASSERT_NE(ptr, nullptr);
    for (int i = 0; i < 5; ++i) {
        ptr[i] = i * 10;
    }
    EXPECT_EQ(arr.Size(), 5u);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 10);
    EXPECT_EQ(arr[2], 20);
    EXPECT_EQ(arr[3], 30);
    EXPECT_EQ(arr[4], 40);
}

// Test PopArr removes multiple elements
TEST_F(DynArrayTest_10, PopArrRemovesMultiple_10) {
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

// Test growth beyond INITIAL_SIZE
TEST_F(DynArrayTest_10, GrowBeyondInitialSize_10) {
    for (int i = 0; i < 20; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 20u);
    EXPECT_GE(arr.Capacity(), 20u);
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

// Test Mem returns a valid pointer
TEST_F(DynArrayTest_10, MemReturnsValidPointer_10) {
    arr.Push(7);
    arr.Push(8);
    const int* mem = arr.Mem();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(mem[0], 7);
    EXPECT_EQ(mem[1], 8);
}

// Test SwapRemove removes element by swapping with last
TEST_F(DynArrayTest_10, SwapRemoveReducesSize_10) {
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
TEST_F(DynArrayTest_10, SwapRemoveLastElement_10) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(2); // Remove last element
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

// Test SwapRemove on first element
TEST_F(DynArrayTest_10, SwapRemoveFirstElement_10) {
    arr.Push(100);
    arr.Push(200);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 200);
}

// Test operator[] modification
TEST_F(DynArrayTest_10, OperatorBracketModification_10) {
    arr.Push(0);
    arr[0] = 999;
    EXPECT_EQ(arr[0], 999);
}

// Test with a single element
TEST_F(DynArrayTest_10, SingleElementOperations_10) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.Empty());
    EXPECT_EQ(arr.PeekTop(), 42);
    EXPECT_EQ(arr[0], 42);
    int val = arr.Pop();
    EXPECT_EQ(val, 42);
    EXPECT_TRUE(arr.Empty());
}

// Test PushArr with 0 count
TEST_F(DynArrayTest_10, PushArrZeroCount_10) {
    arr.Push(1);
    int* ptr = arr.PushArr(0);
    EXPECT_EQ(arr.Size(), 1u);
    // ptr may or may not be null, but size should not change beyond the 0 added
}

// Test PopArr with 0 count
TEST_F(DynArrayTest_10, PopArrZeroCount_10) {
    arr.Push(1);
    arr.Push(2);
    arr.PopArr(0);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test large number of pushes and pops
TEST_F(DynArrayTest_10, LargeNumberOfPushesAndPops_10) {
    const size_t N = 1000;
    for (size_t i = 0; i < N; ++i) {
        arr.Push(static_cast<int>(i));
    }
    EXPECT_EQ(arr.Size(), N);
    EXPECT_GE(arr.Capacity(), N);

    for (size_t i = 0; i < N; ++i) {
        EXPECT_EQ(arr[i], static_cast<int>(i));
    }

    for (size_t i = 0; i < N; ++i) {
        int val = arr.Pop();
        EXPECT_EQ(val, static_cast<int>(N - 1 - i));
    }
    EXPECT_TRUE(arr.Empty());
}

// Test Clear followed by Push
TEST_F(DynArrayTest_10, ClearThenPush_10) {
    arr.Push(1);
    arr.Push(2);
    arr.Clear();
    arr.Push(99);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 99);
}

// Test with a different type (char)
TEST(DynArrayCharTest_10, CharType_10) {
    DynArray<char, 4> charArr;
    EXPECT_TRUE(charArr.Empty());
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

// Test with small INITIAL_SIZE to trigger reallocation
TEST(DynArraySmallInitial_10, GrowthFromSmallInitial_10) {
    DynArray<int, 2> smallArr;
    EXPECT_EQ(smallArr.Capacity(), 2u);
    smallArr.Push(1);
    smallArr.Push(2);
    smallArr.Push(3); // Should trigger reallocation
    EXPECT_EQ(smallArr.Size(), 3u);
    EXPECT_GE(smallArr.Capacity(), 3u);
    EXPECT_EQ(smallArr[0], 1);
    EXPECT_EQ(smallArr[1], 2);
    EXPECT_EQ(smallArr[2], 3);
}

// Test Mem on empty array
TEST_F(DynArrayTest_10, MemOnEmptyArray_10) {
    const int* mem = arr.Mem();
    // Should return a valid pointer (to the internal pool), not null
    ASSERT_NE(mem, nullptr);
}

// Test SwapRemove on single element array
TEST_F(DynArrayTest_10, SwapRemoveSingleElement_10) {
    arr.Push(42);
    arr.SwapRemove(0);
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test multiple PushArr calls
TEST_F(DynArrayTest_10, MultiplePushArrCalls_10) {
    int* p1 = arr.PushArr(3);
    p1[0] = 1; p1[1] = 2; p1[2] = 3;
    int* p2 = arr.PushArr(2);
    p2[0] = 4; p2[1] = 5;
    EXPECT_EQ(arr.Size(), 5u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    EXPECT_EQ(arr[4], 5);
}

// Test that capacity never decreases
TEST_F(DynArrayTest_10, CapacityNeverDecreases_10) {
    for (int i = 0; i < 50; ++i) {
        arr.Push(i);
    }
    size_t capBefore = arr.Capacity();
    for (int i = 0; i < 40; ++i) {
        arr.Pop();
    }
    EXPECT_GE(arr.Capacity(), capBefore);
}
