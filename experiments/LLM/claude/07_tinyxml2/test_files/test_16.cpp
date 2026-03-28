#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Test fixture for DynArray with int type
class DynArrayTest_16 : public ::testing::Test {
protected:
    DynArray<int, 8> arr;
};

TEST_F(DynArrayTest_16, DefaultConstructorEmpty_16) {
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_16, DefaultConstructorCapacity_16) {
    EXPECT_GE(arr.Capacity(), 8u);
}

TEST_F(DynArrayTest_16, PushIncreasesSize_16) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.Empty());
}

TEST_F(DynArrayTest_16, PushAndAccessElement_16) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST_F(DynArrayTest_16, PopReturnsLastElement_16) {
    arr.Push(5);
    arr.Push(15);
    arr.Push(25);
    int val = arr.Pop();
    EXPECT_EQ(val, 25);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_16, PeekTopReturnsLastElement_16) {
    arr.Push(100);
    arr.Push(200);
    const int& top = arr.PeekTop();
    EXPECT_EQ(top, 200);
    EXPECT_EQ(arr.Size(), 2u); // PeekTop should not remove
}

TEST_F(DynArrayTest_16, PopArrRemovesMultipleElements_16) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.PopArr(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST_F(DynArrayTest_16, PushArrReturnsPointerAndIncreasesSize_16) {
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

TEST_F(DynArrayTest_16, ClearResetsSize_16) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_16, MemReturnsNonNull_16) {
    const int* mem = arr.Mem();
    EXPECT_NE(mem, nullptr);
}

TEST_F(DynArrayTest_16, MemPointsToElements_16) {
    arr.Push(42);
    arr.Push(84);
    const int* mem = arr.Mem();
    EXPECT_EQ(mem[0], 42);
    EXPECT_EQ(mem[1], 84);
}

TEST_F(DynArrayTest_16, EmptyReturnsTrueWhenNoElements_16) {
    EXPECT_TRUE(arr.Empty());
    arr.Push(1);
    EXPECT_FALSE(arr.Empty());
    arr.Pop();
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_16, SwapRemoveRemovesElementAtIndex_16) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.Push(40);
    arr.SwapRemove(1); // Remove element at index 1 (value 20)
    EXPECT_EQ(arr.Size(), 3u);
    // The last element (40) should have been swapped into index 1
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 40);
    EXPECT_EQ(arr[2], 30);
}

TEST_F(DynArrayTest_16, SwapRemoveLastElement_16) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(2); // Remove last element
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST_F(DynArrayTest_16, SwapRemoveFirstElement_16) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(0); // Remove first element
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 30);
    EXPECT_EQ(arr[1], 20);
}

TEST_F(DynArrayTest_16, SwapRemoveSingleElement_16) {
    arr.Push(99);
    arr.SwapRemove(0);
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_16, PushBeyondInitialCapacityGrows_16) {
    // Initial capacity is 8, push more than 8 elements
    for (int i = 0; i < 20; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 20u);
    EXPECT_GE(arr.Capacity(), 20u);
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST_F(DynArrayTest_16, PushArrBeyondInitialCapacity_16) {
    int* ptr = arr.PushArr(20);
    ASSERT_NE(ptr, nullptr);
    for (int i = 0; i < 20; ++i) {
        ptr[i] = i * 10;
    }
    EXPECT_EQ(arr.Size(), 20u);
    for (size_t i = 0; i < 20; ++i) {
        EXPECT_EQ(arr[i], static_cast<int>(i * 10));
    }
}

TEST_F(DynArrayTest_16, CapacityAtLeastInitialSize_16) {
    EXPECT_GE(arr.Capacity(), 8u);
}

TEST_F(DynArrayTest_16, ClearAfterGrowth_16) {
    for (int i = 0; i < 50; ++i) {
        arr.Push(i);
    }
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_16, MultiplePushPop_16) {
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

TEST_F(DynArrayTest_16, IndexOperatorModifiesElement_16) {
    arr.Push(10);
    arr.Push(20);
    arr[0] = 99;
    arr[1] = 88;
    EXPECT_EQ(arr[0], 99);
    EXPECT_EQ(arr[1], 88);
}

// Test with a different type (char) and different initial size
class DynArrayCharTest_16 : public ::testing::Test {
protected:
    DynArray<char, 4> arr;
};

TEST_F(DynArrayCharTest_16, PushAndAccessChars_16) {
    arr.Push('a');
    arr.Push('b');
    arr.Push('c');
    EXPECT_EQ(arr[0], 'a');
    EXPECT_EQ(arr[1], 'b');
    EXPECT_EQ(arr[2], 'c');
    EXPECT_EQ(arr.Size(), 3u);
}

TEST_F(DynArrayCharTest_16, GrowBeyondSmallInitialSize_16) {
    for (int i = 0; i < 100; ++i) {
        arr.Push(static_cast<char>(i % 128));
    }
    EXPECT_EQ(arr.Size(), 100u);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(arr[i], static_cast<char>(i % 128));
    }
}

TEST_F(DynArrayCharTest_16, MemConsistentWithSubscript_16) {
    arr.Push('x');
    arr.Push('y');
    arr.Push('z');
    const char* mem = arr.Mem();
    EXPECT_EQ(mem[0], arr[0]);
    EXPECT_EQ(mem[1], arr[1]);
    EXPECT_EQ(mem[2], arr[2]);
}

TEST_F(DynArrayTest_16, PopArrToEmpty_16) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.PopArr(3);
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_16, PushArrZeroCount_16) {
    int* ptr = arr.PushArr(0);
    // PushArr(0) should not change size
    EXPECT_EQ(arr.Size(), 0u);
    (void)ptr; // ptr may or may not be valid for 0 count
}

TEST_F(DynArrayTest_16, PopArrZeroCount_16) {
    arr.Push(1);
    arr.Push(2);
    arr.PopArr(0);
    EXPECT_EQ(arr.Size(), 2u);
}

TEST_F(DynArrayTest_16, SizeAfterPushExactlyInitialSize_16) {
    // Push exactly INITIAL_SIZE (8) elements
    for (int i = 0; i < 8; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 8u);
    EXPECT_GE(arr.Capacity(), 8u);
    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST_F(DynArrayTest_16, PushOneMoreThanInitialSize_16) {
    for (int i = 0; i < 9; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 9u);
    EXPECT_GE(arr.Capacity(), 9u);
    for (int i = 0; i < 9; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST_F(DynArrayTest_16, ClearAndReuseArray_16) {
    arr.Push(1);
    arr.Push(2);
    arr.Clear();
    arr.Push(10);
    arr.Push(20);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

// Test with a small initial size of 1
class DynArraySmallInit_16 : public ::testing::Test {
protected:
    DynArray<int, 1> arr;
};

TEST_F(DynArraySmallInit_16, InitialCapacityIsOne_16) {
    EXPECT_GE(arr.Capacity(), 1u);
}

TEST_F(DynArraySmallInit_16, GrowFromSizeOne_16) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}
