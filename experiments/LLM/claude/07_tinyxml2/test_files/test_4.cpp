#include <gtest/gtest.h>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Test fixture for DynArray tests
class DynArrayTest_4 : public ::testing::Test {
protected:
    DynArray<int, 8> arr;
};

// Test that a newly constructed DynArray is empty
TEST_F(DynArrayTest_4, DefaultConstructorCreatesEmptyArray_4) {
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test that initial capacity matches INITIAL_SIZE
TEST_F(DynArrayTest_4, DefaultConstructorSetsInitialCapacity_4) {
    EXPECT_EQ(arr.Capacity(), 8u);
}

// Test Push adds an element and increases size
TEST_F(DynArrayTest_4, PushIncreasesSize_4) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.Empty());
}

// Test Push stores the correct value
TEST_F(DynArrayTest_4, PushStoresCorrectValue_4) {
    arr.Push(42);
    EXPECT_EQ(arr[0], 42);
}

// Test multiple Push operations
TEST_F(DynArrayTest_4, MultiplePushOperations_4) {
    for (int i = 0; i < 5; ++i) {
        arr.Push(i * 10);
    }
    EXPECT_EQ(arr.Size(), 5u);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], i * 10);
    }
}

// Test Pop removes and returns the last element
TEST_F(DynArrayTest_4, PopReturnsLastElement_4) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    int val = arr.Pop();
    EXPECT_EQ(val, 30);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test Pop reduces size
TEST_F(DynArrayTest_4, PopReducesSize_4) {
    arr.Push(1);
    arr.Push(2);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 1u);
}

// Test PeekTop returns the last element without removing it
TEST_F(DynArrayTest_4, PeekTopReturnsLastElement_4) {
    arr.Push(100);
    arr.Push(200);
    EXPECT_EQ(arr.PeekTop(), 200);
    EXPECT_EQ(arr.Size(), 2u); // Size should not change
}

// Test Empty returns true for empty array
TEST_F(DynArrayTest_4, EmptyReturnsTrueForEmptyArray_4) {
    EXPECT_TRUE(arr.Empty());
}

// Test Empty returns false after Push
TEST_F(DynArrayTest_4, EmptyReturnsFalseAfterPush_4) {
    arr.Push(1);
    EXPECT_FALSE(arr.Empty());
}

// Test Clear resets the array
TEST_F(DynArrayTest_4, ClearEmptiesArray_4) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test operator[] access
TEST_F(DynArrayTest_4, OperatorBracketAccess_4) {
    arr.Push(5);
    arr.Push(10);
    arr.Push(15);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 10);
    EXPECT_EQ(arr[2], 15);
}

// Test operator[] modification
TEST_F(DynArrayTest_4, OperatorBracketModification_4) {
    arr.Push(5);
    arr[0] = 99;
    EXPECT_EQ(arr[0], 99);
}

// Test PushArr allocates space for multiple elements
TEST_F(DynArrayTest_4, PushArrAllocatesSpace_4) {
    int* ptr = arr.PushArr(3);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(arr.Size(), 3u);
    // Fill in values through returned pointer
    ptr[0] = 10;
    ptr[1] = 20;
    ptr[2] = 30;
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

// Test PopArr removes multiple elements
TEST_F(DynArrayTest_4, PopArrRemovesMultipleElements_4) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.PopArr(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

// Test SwapRemove removes element by swapping with last
TEST_F(DynArrayTest_4, SwapRemoveRemovesElement_4) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(0); // Remove first element, swap with last
    EXPECT_EQ(arr.Size(), 2u);
    // The element at index 0 should now be the former last element
    EXPECT_EQ(arr[0], 30);
    EXPECT_EQ(arr[1], 20);
}

// Test SwapRemove on last element
TEST_F(DynArrayTest_4, SwapRemoveLastElement_4) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(2); // Remove last element
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

// Test SwapRemove on single element array
TEST_F(DynArrayTest_4, SwapRemoveSingleElement_4) {
    arr.Push(42);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// Test Mem returns pointer to internal memory
TEST_F(DynArrayTest_4, MemReturnsPointer_4) {
    arr.Push(1);
    arr.Push(2);
    const int* mem = arr.Mem();
    EXPECT_NE(mem, nullptr);
    EXPECT_EQ(mem[0], 1);
    EXPECT_EQ(mem[1], 2);
}

// Test Mem on empty array
TEST_F(DynArrayTest_4, MemOnEmptyArray_4) {
    const int* mem = arr.Mem();
    EXPECT_NE(mem, nullptr); // Should point to the pool
}

// Test pushing beyond initial capacity triggers reallocation
TEST_F(DynArrayTest_4, PushBeyondInitialCapacityGrows_4) {
    for (int i = 0; i < 20; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 20u);
    EXPECT_GE(arr.Capacity(), 20u);
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

// Test capacity grows when needed
TEST_F(DynArrayTest_4, CapacityGrowsWhenExceedingInitialSize_4) {
    for (int i = 0; i < 9; ++i) {
        arr.Push(i);
    }
    EXPECT_GE(arr.Capacity(), 9u);
}

// Test Clear then Push again
TEST_F(DynArrayTest_4, ClearThenPushAgain_4) {
    arr.Push(1);
    arr.Push(2);
    arr.Clear();
    arr.Push(99);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 99);
}

// Test PushArr with count 0
TEST_F(DynArrayTest_4, PushArrZeroCount_4) {
    arr.Push(5);
    int* ptr = arr.PushArr(0);
    EXPECT_EQ(arr.Size(), 1u);
    (void)ptr; // Just ensure it doesn't crash
}

// Test PopArr with count 0
TEST_F(DynArrayTest_4, PopArrZeroCount_4) {
    arr.Push(1);
    arr.Push(2);
    arr.PopArr(0);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test with different template types - char
TEST(DynArrayCharTest_4, WorksWithChar_4) {
    DynArray<char, 4> charArr;
    charArr.Push('a');
    charArr.Push('b');
    charArr.Push('c');
    EXPECT_EQ(charArr.Size(), 3u);
    EXPECT_EQ(charArr[0], 'a');
    EXPECT_EQ(charArr[1], 'b');
    EXPECT_EQ(charArr[2], 'c');
}

// Test with different template types - double
TEST(DynArrayDoubleTest_4, WorksWithDouble_4) {
    DynArray<double, 2> dblArr;
    dblArr.Push(1.5);
    dblArr.Push(2.5);
    dblArr.Push(3.5); // Beyond initial size
    EXPECT_EQ(dblArr.Size(), 3u);
    EXPECT_DOUBLE_EQ(dblArr[0], 1.5);
    EXPECT_DOUBLE_EQ(dblArr[1], 2.5);
    EXPECT_DOUBLE_EQ(dblArr[2], 3.5);
}

// Test with INITIAL_SIZE of 1
TEST(DynArraySmallInitialSize_4, InitialSizeOne_4) {
    DynArray<int, 1> smallArr;
    EXPECT_EQ(smallArr.Capacity(), 1u);
    smallArr.Push(10);
    EXPECT_EQ(smallArr.Size(), 1u);
    smallArr.Push(20); // Should trigger growth
    EXPECT_EQ(smallArr.Size(), 2u);
    EXPECT_GE(smallArr.Capacity(), 2u);
    EXPECT_EQ(smallArr[0], 10);
    EXPECT_EQ(smallArr[1], 20);
}

// Test Pop after Push restores empty state
TEST_F(DynArrayTest_4, PushThenPopRestoresEmpty_4) {
    arr.Push(42);
    arr.Pop();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test PeekTop after multiple operations
TEST_F(DynArrayTest_4, PeekTopAfterMultipleOperations_4) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Pop();
    EXPECT_EQ(arr.PeekTop(), 2);
}

// Test large number of elements
TEST_F(DynArrayTest_4, LargeNumberOfElements_4) {
    const size_t count = 1000;
    for (size_t i = 0; i < count; ++i) {
        arr.Push(static_cast<int>(i));
    }
    EXPECT_EQ(arr.Size(), count);
    EXPECT_GE(arr.Capacity(), count);
    for (size_t i = 0; i < count; ++i) {
        EXPECT_EQ(arr[i], static_cast<int>(i));
    }
}

// Test PushArr then access through Mem
TEST_F(DynArrayTest_4, PushArrThenAccessMem_4) {
    int* ptr = arr.PushArr(5);
    for (int i = 0; i < 5; ++i) {
        ptr[i] = i * 100;
    }
    const int* mem = arr.Mem();
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(mem[i], i * 100);
    }
}

// Test SwapRemove middle element
TEST_F(DynArrayTest_4, SwapRemoveMiddleElement_4) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.Push(40);
    arr.Push(50);
    arr.SwapRemove(2); // Remove 30, replace with 50
    EXPECT_EQ(arr.Size(), 4u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 50);
    EXPECT_EQ(arr[3], 40);
}

// Test Size after various operations
TEST_F(DynArrayTest_4, SizeAfterVariousOperations_4) {
    EXPECT_EQ(arr.Size(), 0u);
    arr.Push(1);
    EXPECT_EQ(arr.Size(), 1u);
    arr.Push(2);
    EXPECT_EQ(arr.Size(), 2u);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 1u);
    arr.PushArr(3);
    EXPECT_EQ(arr.Size(), 4u);
    arr.PopArr(2);
    EXPECT_EQ(arr.Size(), 2u);
    arr.Clear();
    EXPECT_EQ(arr.Size(), 0u);
}

// Test that Capacity is at least Size
TEST_F(DynArrayTest_4, CapacityAtLeastSize_4) {
    for (int i = 0; i < 50; ++i) {
        arr.Push(i);
        EXPECT_GE(arr.Capacity(), arr.Size());
    }
}

// Test with pointers as stored type
TEST(DynArrayPointerTest_4, WorksWithPointers_4) {
    DynArray<int*, 4> ptrArr;
    int a = 1, b = 2, c = 3;
    ptrArr.Push(&a);
    ptrArr.Push(&b);
    ptrArr.Push(&c);
    EXPECT_EQ(ptrArr.Size(), 3u);
    EXPECT_EQ(*ptrArr[0], 1);
    EXPECT_EQ(*ptrArr[1], 2);
    EXPECT_EQ(*ptrArr[2], 3);
}
