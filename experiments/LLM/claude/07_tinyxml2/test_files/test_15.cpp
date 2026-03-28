#include <gtest/gtest.h>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class DynArrayTest_15 : public ::testing::Test {
protected:
    DynArray<int, 8> arr;
};

// ==================== Normal Operation Tests ====================

TEST_F(DynArrayTest_15, InitiallyEmpty_15) {
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_15, PushIncreasesSize_15) {
    arr.Push(42);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.Empty());
}

TEST_F(DynArrayTest_15, PushAndAccessElement_15) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST_F(DynArrayTest_15, PopReturnsLastElement_15) {
    arr.Push(100);
    arr.Push(200);
    int val = arr.Pop();
    EXPECT_EQ(val, 200);
    EXPECT_EQ(arr.Size(), 1u);
}

TEST_F(DynArrayTest_15, PeekTopReturnsLastElement_15) {
    arr.Push(5);
    arr.Push(15);
    arr.Push(25);
    EXPECT_EQ(arr.PeekTop(), 25);
    EXPECT_EQ(arr.Size(), 3u); // PeekTop should not remove
}

TEST_F(DynArrayTest_15, ClearResetsArray_15) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST_F(DynArrayTest_15, PopArrRemovesMultipleElements_15) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.PopArr(2);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST_F(DynArrayTest_15, PushArrAllocatesSpace_15) {
    int* block = arr.PushArr(5);
    EXPECT_NE(block, nullptr);
    EXPECT_EQ(arr.Size(), 5u);
    // Write to the allocated space
    for (int i = 0; i < 5; ++i) {
        block[i] = i * 10;
    }
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], static_cast<int>(i * 10));
    }
}

TEST_F(DynArrayTest_15, MemReturnsPointerToData_15) {
    arr.Push(42);
    arr.Push(84);
    const int* mem = arr.Mem();
    EXPECT_NE(mem, nullptr);
    EXPECT_EQ(mem[0], 42);
    EXPECT_EQ(mem[1], 84);
}

TEST_F(DynArrayTest_15, CapacityAtLeastInitialSize_15) {
    EXPECT_GE(arr.Capacity(), 8u);
}

// ==================== SwapRemove Tests ====================

TEST_F(DynArrayTest_15, SwapRemoveLastElement_15) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(2); // Remove last element
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST_F(DynArrayTest_15, SwapRemoveFirstElement_15) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.SwapRemove(0); // Remove first element, replaced by last
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr[0], 30); // Last element moved to index 0
    EXPECT_EQ(arr[1], 20);
}

TEST_F(DynArrayTest_15, SwapRemoveMiddleElement_15) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);
    arr.Push(40);
    arr.SwapRemove(1); // Remove middle element, replaced by last
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 40); // Last element moved to index 1
    EXPECT_EQ(arr[2], 30);
}

TEST_F(DynArrayTest_15, SwapRemoveSingleElement_15) {
    arr.Push(99);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayTest_15, SwapRemoveAllElementsOneByOne_15) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    
    arr.SwapRemove(0); // [3, 2]
    EXPECT_EQ(arr.Size(), 2u);
    
    arr.SwapRemove(0); // [2]
    EXPECT_EQ(arr.Size(), 1u);
    
    arr.SwapRemove(0); // []
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

// ==================== Boundary / Growth Tests ====================

TEST_F(DynArrayTest_15, PushBeyondInitialCapacity_15) {
    // INITIAL_SIZE is 8, push more than that to trigger reallocation
    for (int i = 0; i < 20; ++i) {
        arr.Push(i);
    }
    EXPECT_EQ(arr.Size(), 20u);
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST_F(DynArrayTest_15, CapacityGrowsWithPush_15) {
    size_t initialCapacity = arr.Capacity();
    for (size_t i = 0; i < initialCapacity + 10; ++i) {
        arr.Push(static_cast<int>(i));
    }
    EXPECT_GE(arr.Capacity(), initialCapacity + 10);
}

TEST_F(DynArrayTest_15, SwapRemoveAfterReallocation_15) {
    for (int i = 0; i < 20; ++i) {
        arr.Push(i * 5);
    }
    arr.SwapRemove(5); // Remove element at index 5, replace with last (19*5=95)
    EXPECT_EQ(arr.Size(), 19u);
    EXPECT_EQ(arr[5], 95);
}

TEST_F(DynArrayTest_15, PushArrBeyondInitialCapacity_15) {
    int* block = arr.PushArr(20);
    EXPECT_NE(block, nullptr);
    EXPECT_EQ(arr.Size(), 20u);
    EXPECT_GE(arr.Capacity(), 20u);
}

TEST_F(DynArrayTest_15, MultiplePushAndPopCycles_15) {
    for (int cycle = 0; cycle < 5; ++cycle) {
        for (int i = 0; i < 10; ++i) {
            arr.Push(cycle * 10 + i);
        }
        for (int i = 0; i < 10; ++i) {
            arr.Pop();
        }
        EXPECT_EQ(arr.Size(), 0u);
    }
}

TEST_F(DynArrayTest_15, ClearAfterGrowth_15) {
    for (int i = 0; i < 50; ++i) {
        arr.Push(i);
    }
    arr.Clear();
    EXPECT_TRUE(arr.Empty());
    EXPECT_EQ(arr.Size(), 0u);
    // Should still be able to push after clear
    arr.Push(999);
    EXPECT_EQ(arr[0], 999);
    EXPECT_EQ(arr.Size(), 1u);
}

// ==================== Different Type Tests ====================

TEST(DynArrayCharTest_15, WorksWithCharType_15) {
    DynArray<char, 4> charArr;
    charArr.Push('a');
    charArr.Push('b');
    charArr.Push('c');
    EXPECT_EQ(charArr.Size(), 3u);
    EXPECT_EQ(charArr[0], 'a');
    EXPECT_EQ(charArr[1], 'b');
    EXPECT_EQ(charArr[2], 'c');
    
    charArr.SwapRemove(0);
    EXPECT_EQ(charArr.Size(), 2u);
    EXPECT_EQ(charArr[0], 'c');
}

TEST(DynArrayDoubleTest_15, WorksWithDoubleType_15) {
    DynArray<double, 4> dArr;
    dArr.Push(1.5);
    dArr.Push(2.5);
    dArr.Push(3.5);
    
    dArr.SwapRemove(1);
    EXPECT_EQ(dArr.Size(), 2u);
    EXPECT_DOUBLE_EQ(dArr[0], 1.5);
    EXPECT_DOUBLE_EQ(dArr[1], 3.5);
}

// ==================== Operator[] Tests ====================

TEST_F(DynArrayTest_15, OperatorBracketModifiesValue_15) {
    arr.Push(10);
    arr.Push(20);
    arr[0] = 100;
    arr[1] = 200;
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
}

// ==================== Pop and PeekTop interaction ====================

TEST_F(DynArrayTest_15, PeekTopAfterPop_15) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Pop();
    EXPECT_EQ(arr.PeekTop(), 2);
}

TEST_F(DynArrayTest_15, PopAllElements_15) {
    arr.Push(10);
    arr.Push(20);
    EXPECT_EQ(arr.Pop(), 20);
    EXPECT_EQ(arr.Pop(), 10);
    EXPECT_TRUE(arr.Empty());
}

// ==================== SwapRemove with two elements ====================

TEST_F(DynArrayTest_15, SwapRemoveWithTwoElements_15) {
    arr.Push(100);
    arr.Push(200);
    arr.SwapRemove(0);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 200);
}

TEST_F(DynArrayTest_15, SwapRemoveSecondOfTwoElements_15) {
    arr.Push(100);
    arr.Push(200);
    arr.SwapRemove(1);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_EQ(arr[0], 100);
}

// ==================== Small initial size ====================

TEST(DynArraySmallInitial_15, InitialSizeOne_15) {
    DynArray<int, 1> smallArr;
    smallArr.Push(42);
    EXPECT_EQ(smallArr.Size(), 1u);
    EXPECT_EQ(smallArr[0], 42);
    
    // Force growth
    smallArr.Push(84);
    EXPECT_EQ(smallArr.Size(), 2u);
    EXPECT_EQ(smallArr[0], 42);
    EXPECT_EQ(smallArr[1], 84);
    
    smallArr.SwapRemove(0);
    EXPECT_EQ(smallArr.Size(), 1u);
    EXPECT_EQ(smallArr[0], 84);
}
