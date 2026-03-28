#include <gtest/gtest.h>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Test fixture for DynArray with int type
class DynArrayTest_11 : public ::testing::Test {
protected:
    DynArray<int, 4> arr;
};

// Test that a newly constructed DynArray is empty
TEST_F(DynArrayTest_11, DefaultConstructorIsEmpty_11) {
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test that initial capacity matches INITIAL_SIZE
TEST_F(DynArrayTest_11, DefaultConstructorCapacity_11) {
    EXPECT_EQ(arr.Capacity(), 4u);
}

// Test Push increases size
TEST_F(DynArrayTest_11, PushIncreasesSize_11) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.Empty());
}

// Test Push stores correct value retrievable via operator[]
TEST_F(DynArrayTest_11, PushAndAccessElement_11) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

// Test Pop returns the last pushed element
TEST_F(DynArrayTest_11, PopReturnsLastElement_11) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    int val = arr.Pop();
    EXPECT_EQ(val, 3);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test Pop reduces size correctly
TEST_F(DynArrayTest_11, PopReducesSize_11) {
    arr.Push(5);
    arr.Push(10);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 1u);
}

// Test PeekTop returns last element without removing
TEST_F(DynArrayTest_11, PeekTopReturnsLastElement_11) {
    arr.Push(100);
    arr.Push(200);
    const int& top = arr.PeekTop();
    EXPECT_EQ(top, 200);
    EXPECT_EQ(arr.Size(), 2u);
}

// Test Empty returns true when array has no elements
TEST_F(DynArrayTest_11, EmptyReturnsTrueWhenEmpty_11) {
    EXPECT_TRUE(arr.Empty());
    arr.Push(1);
    arr.Pop();
    EXPECT_TRUE(arr.Empty());
}

// Test Empty returns false when array has elements
TEST_F(DynArrayTest_11, EmptyReturnsFalseWhenNonEmpty_11) {
    arr.Push(1);
    EXPECT_FALSE(arr.Empty());
}

// Test Clear empties the array
TEST_F(DynArrayTest_11, ClearEmptiesArray_11) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

// Test Size returns correct count
TEST_F(DynArrayTest_11, SizeReturnsCorrectCount_11) {
    EXPECT_EQ(arr.Size(), 0u);
    arr.Push(1);
    EXPECT_EQ(arr.Size(), 1u);
    arr.Push(2);
    EXPECT_EQ(arr.Size(), 2u);
    arr.Pop();
    EXPECT_EQ(arr.Size(), 1u);
}

// Test PushArr allocates space for multiple elements
TEST_F(DynArrayTest_11, PushArrAllocatesMultipleElements_11) {
    int* block = arr.PushArr(3);
    EXPECT_NE(block, nullptr);
    EXPECT_EQ(arr.Size(), 3u);
    // Write to the allocated space
    block[0] = 10;
    block[1] = 20;
    block[2] = 30;
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

// Test PopArr reduces size by count
TEST_F(DynArrayTest_11, PopArrReducesSizeByCount_11) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.PopArr(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

// Test growing beyond INITIAL_SIZE (heap allocation)
TEST_F(DynArrayTest_11, GrowBeyondInitialSize_11) {
    for (int i = 0; i < 10; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 10u);
    EXPECT_GE(arr.Capacity(), 10u);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

// Test Mem returns pointer to internal memory
TEST_F(DynArrayTest_11, MemReturnsValidPointer_11) {
    arr.Push(42);
    arr.Push(43);
    const int* mem = arr.Mem();
    EXPECT_NE(mem, nullptr);
    EXPECT_EQ(mem[0], 42);
    EXPECT_EQ(mem[1], 43);
}

// Test SwapRemove removes element and swaps with last
TEST_F(DynArrayTest_11, SwapRemoveRemovesElement_11) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.Push(40);
    arr.SwapRemove(1); // Remove element at index 1 (value 20), replaced by last (40)
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 40); // Last element moved to index 1
    EXPECT_EQ(arr[2], 30);
}

// Test SwapRemove on last element
TEST_F(DynArrayTest_11, SwapRemoveLastElement_11) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(2); // Remove last element
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

// Test SwapRemove on first element
TEST_F(DynArrayTest_11, SwapRemoveFirstElement_11) {
    arr.Push(10);
    arr.Push(20);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 20);
}

// Test SwapRemove on single element array
TEST_F(DynArrayTest_11, SwapRemoveSingleElement_11) {
    arr.Push(99);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// Test operator[] modifies element in place
TEST_F(DynArrayTest_11, OperatorBracketModifiesElement_11) {
    arr.Push(1);
    arr.Push(2);
    arr[0] = 100;
    arr[1] = 200;
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
}

// Test Capacity grows as needed
TEST_F(DynArrayTest_11, CapacityGrowsAsNeeded_11) {
    size_t initialCap = arr.Capacity();
    for (size_t i = 0; i < initialCap + 1; ++i) {
        arr.Push(static_cast<int>(i));
    }
    EXPECT_GT(arr.Capacity(), initialCap);
}

// Test PushArr with zero count
TEST_F(DynArrayTest_11, PushArrZeroCount_11) {
    arr.Push(1);
    int* block = arr.PushArr(0);
    EXPECT_EQ(arr.Size(), 1u);
    // block may or may not be null, but size should not change meaningfully
    (void)block;
}

// Test multiple Push and Pop cycles
TEST_F(DynArrayTest_11, MultiplePushPopCycles_11) {
    for (int cycle = 0; cycle < 5; ++cycle) {
        for (int i = 0; i < 10; ++i) {
            arr.Push(cycle * 10 + i);
        }
        for (int i = 9; i >= 0; --i) {
            int val = arr.Pop();
            EXPECT_EQ(val, cycle * 10 + i);
        }
        EXPECT_TRUE(arr.Empty());
    }
}

// Test Clear and reuse
TEST_F(DynArrayTest_11, ClearAndReuse_11) {
    arr.Push(1);
    arr.Push(2);
    arr.Clear();
    arr.Push(10);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 10);
}

// Test with larger INITIAL_SIZE
TEST(DynArrayLargeInitial_11, LargeInitialSize_11) {
    DynArray<int, 64> largeArr;
    EXPECT_EQ(largeArr.Capacity(), 64u);
    EXPECT_TRUE(largeArr.Empty());
    for (int i = 0; i < 100; ++i) {
        largeArr.Push(i);
    }
    EXPECT_EQ(largeArr.Size(), 100u);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(largeArr[i], i);
    }
}

// Test with INITIAL_SIZE of 1
TEST(DynArrayMinInitial_11, MinimalInitialSize_11) {
    DynArray<int, 1> minArr;
    EXPECT_EQ(minArr.Capacity(), 1u);
    minArr.Push(42);
    EXPECT_EQ(minArr.Size(), 1u);
    EXPECT_EQ(minArr[0], 42);
    // Force growth
    minArr.Push(43);
    EXPECT_EQ(minArr.Size(), 2u);
    EXPECT_GE(minArr.Capacity(), 2u);
    EXPECT_EQ(minArr[0], 42);
    EXPECT_EQ(minArr[1], 43);
}

// Test with non-int type (char)
TEST(DynArrayCharType_11, CharTypeOperations_11) {
    DynArray<char, 4> charArr;
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

// Test PopArr removing all elements
TEST_F(DynArrayTest_11, PopArrRemovesAll_11) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.PopArr(3);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// Test Mem on empty array
TEST_F(DynArrayTest_11, MemOnEmptyArray_11) {
    const int* mem = arr.Mem();
    // Should return a valid pointer (to the pool), even when empty
    EXPECT_NE(mem, nullptr);
}

// Test large number of elements to stress heap allocation
TEST_F(DynArrayTest_11, StressTest_11) {
    const int count = 1000;
    for (int i = 0; i < count; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), static_cast<size_t>(count));
    for (int i = 0; i < count; ++i) {
        EXPECT_EQ(arr[i], i);
    }
    // Pop all
    for (int i = count - 1; i >= 0; --i) {
        int val = arr.Pop();
        EXPECT_EQ(val, i);
    }
    EXPECT_TRUE(arr.Empty());
}

// Test PushArr returns writable memory
TEST_F(DynArrayTest_11, PushArrReturnsWritableMemory_11) {
    arr.Push(1);
    int* block = arr.PushArr(4);
    EXPECT_EQ(arr.Size(), 5u);
    for (int i = 0; i < 4; ++i) {
        block[i] = (i + 1) * 100;
    }
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 100);
    EXPECT_EQ(arr[2], 200);
    EXPECT_EQ(arr[3], 300);
    EXPECT_EQ(arr[4], 400);
}

// Test destructor doesn't leak (implicit - just create and destroy)
TEST(DynArrayDestructor_11, DestructorNoLeak_11) {
    DynArray<int, 4>* arr = new DynArray<int, 4>();
    for (int i = 0; i < 100; ++i) {
        arr->Push(i);
    }
    delete arr; // Should not leak
}
