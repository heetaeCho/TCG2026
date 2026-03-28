#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Use a concrete instantiation with a known INITIAL_SIZE
// Based on the template: DynArray<T, INITIAL_SIZE>
// We'll test with int and a small initial size

class DynArrayTest_14 : public ::testing::Test {
protected:
    DynArray<int, 8> arr;
};

// Test that a newly constructed DynArray is empty
TEST_F(DynArrayTest_14, DefaultConstructorEmpty_14) {
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test that initial capacity is at least INITIAL_SIZE
TEST_F(DynArrayTest_14, InitialCapacity_14) {
    EXPECT_GE(arr.Capacity(), 8u);
}

// Test Push and Size
TEST_F(DynArrayTest_14, PushIncreasesSize_14) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.Empty());
}

// Test Push and element access via operator[]
TEST_F(DynArrayTest_14, PushAndAccess_14) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

// Test Pop returns the last element and decreases size
TEST_F(DynArrayTest_14, PopReturnsLastElement_14) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    int val = arr.Pop();
    EXPECT_EQ(val, 3);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test PeekTop returns last element without removing it
TEST_F(DynArrayTest_14, PeekTopReturnsLastElement_14) {
    arr.Push(100);
    arr.Push(200);
    const int& top = arr.PeekTop();
    EXPECT_EQ(top, 200);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test Clear empties the array
TEST_F(DynArrayTest_14, ClearEmptiesArray_14) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test PushArr allocates space for multiple elements
TEST_F(DynArrayTest_14, PushArrAllocatesSpace_14) {
    int* block = arr.PushArr(5);
    ASSERT_NE(block, nullptr);
    // Fill the allocated block
    for (int i = 0; i < 5; i++) {
        block[i] = i * 10;
    }
    EXPECT_EQ(arr.Size(), 5u);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 10);
    EXPECT_EQ(arr[4], 40);
}

// Test PopArr removes multiple elements
TEST_F(DynArrayTest_14, PopArrRemovesMultiple_14) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.PopArr(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

// Test Mem returns pointer to underlying data
TEST_F(DynArrayTest_14, MemReturnsData_14) {
    arr.Push(7);
    arr.Push(8);
    const int* mem = arr.Mem();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(mem[0], 7);
    EXPECT_EQ(mem[1], 8);
}

// Test SwapRemove removes element by swapping with last
TEST_F(DynArrayTest_14, SwapRemoveRemovesElement_14) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.Push(40);
    arr.SwapRemove(1); // Remove element at index 1 (value 20), swap with last (40)
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 40); // swapped from end
    EXPECT_EQ(arr[2], 30);
}

// Test SwapRemove on last element
TEST_F(DynArrayTest_14, SwapRemoveLastElement_14) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(2); // Remove last element
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

// Test SwapRemove on first element of single-element array
TEST_F(DynArrayTest_14, SwapRemoveSingleElement_14) {
    arr.Push(99);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// Test capacity grows when pushing beyond INITIAL_SIZE
TEST_F(DynArrayTest_14, CapacityGrowsBeyondInitial_14) {
    for (int i = 0; i < 20; i++) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 20u);
    EXPECT_GE(arr.Capacity(), 20u);
    // Verify all elements are correct
    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(arr[i], i);
    }
}

// Test Empty on non-empty array
TEST_F(DynArrayTest_14, EmptyReturnsFalseWhenNotEmpty_14) {
    arr.Push(1);
    EXPECT_FALSE(arr.Empty());
}

// Test multiple Push and Pop operations
TEST_F(DynArrayTest_14, MultiplePushPop_14) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    EXPECT_EQ(arr.Pop(), 3);
    arr.Push(4);
    EXPECT_EQ(arr.Pop(), 4);
    EXPECT_EQ(arr.Pop(), 2);
    EXPECT_EQ(arr.Pop(), 1);
    EXPECT_TRUE(arr.Empty());
}

// Test operator[] for writing
TEST_F(DynArrayTest_14, OperatorBracketWrite_14) {
    arr.Push(0);
    arr.Push(0);
    arr[0] = 55;
    arr[1] = 66;
    EXPECT_EQ(arr[0], 55);
    EXPECT_EQ(arr[1], 66);
}

// Test with char type
TEST(DynArrayCharTest_14, CharArray_14) {
    DynArray<char, 4> charArr;
    charArr.Push('a');
    charArr.Push('b');
    charArr.Push('c');
    EXPECT_EQ(charArr.Size(), 3u);
    EXPECT_EQ(charArr[0], 'a');
    EXPECT_EQ(charArr[1], 'b');
    EXPECT_EQ(charArr[2], 'c');
}

// Test PushArr with zero count
TEST_F(DynArrayTest_14, PushArrZeroCount_14) {
    size_t sizeBefore = arr.Size();
    arr.PushArr(0);
    EXPECT_EQ(arr.Size(), sizeBefore);
}

// Test PopArr with zero count
TEST_F(DynArrayTest_14, PopArrZeroCount_14) {
    arr.Push(1);
    arr.Push(2);
    arr.PopArr(0);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test Clear on already empty array
TEST_F(DynArrayTest_14, ClearOnEmptyArray_14) {
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test large number of pushes to verify dynamic growth
TEST_F(DynArrayTest_14, LargeNumberOfPushes_14) {
    for (int i = 0; i < 1000; i++) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 1000u);
    EXPECT_GE(arr.Capacity(), 1000u);
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(arr[i], i);
    }
}

// Test Capacity after Clear
TEST_F(DynArrayTest_14, CapacityAfterClear_14) {
    for (int i = 0; i < 100; i++) {
        arr.Push(i);
    }
    size_t capBefore = arr.Capacity();
    arr.Clear();
    // Capacity should be at least INITIAL_SIZE after clear
    EXPECT_GE(arr.Capacity(), 8u);
    // After clear, we can push again
    arr.Push(42);
    EXPECT_EQ(arr[0], 42);
    EXPECT_EQ(arr.Size(), 1u);
}

// Test Mem on empty array
TEST_F(DynArrayTest_14, MemOnEmptyArray_14) {
    const int* mem = arr.Mem();
    EXPECT_NE(mem, nullptr); // Should point to internal pool
}

// Test boundary: Push exactly INITIAL_SIZE elements
TEST_F(DynArrayTest_14, PushExactlyInitialSize_14) {
    for (int i = 0; i < 8; i++) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 8u);
    EXPECT_GE(arr.Capacity(), 8u);
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(arr[i], i);
    }
}

// Test boundary: Push one more than INITIAL_SIZE
TEST_F(DynArrayTest_14, PushOneMoreThanInitialSize_14) {
    for (int i = 0; i < 9; i++) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 9u);
    EXPECT_GE(arr.Capacity(), 9u);
    for (int i = 0; i < 9; i++) {
        EXPECT_EQ(arr[i], i);
    }
}
