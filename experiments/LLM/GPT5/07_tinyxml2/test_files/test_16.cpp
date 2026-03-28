// TEST_ID: 16
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using tinyxml2::DynArray;

class DynArrayMemTest_16 : public ::testing::Test {};

// Mem() should be callable on a default-constructed DynArray and return a non-null pointer.
TEST_F(DynArrayMemTest_16, DefaultConstructedMemIsNonNull_16)
{
    DynArray<int, 4> arr;
    const int* mem = arr.Mem();
    EXPECT_NE(mem, nullptr);
}

// Values pushed through the public API should be observable consistently via Mem() and operator[].
TEST_F(DynArrayMemTest_16, MemMatchesOperatorIndexingAfterPush_16)
{
    DynArray<int, 4> arr;

    arr.Push(10);
    arr.Push(20);
    arr.Push(30);

    ASSERT_EQ(arr.Size(), 3u);

    const int* mem = arr.Mem();
    ASSERT_NE(mem, nullptr);

    for (size_t i = 0; i < arr.Size(); ++i) {
        EXPECT_EQ(mem[i], arr[i]) << "Mismatch at index " << i;
    }
}

// Writing through the pointer returned by PushArr should be observable via Mem() (and operator[]).
TEST_F(DynArrayMemTest_16, MemReflectsPushArrWrites_16)
{
    DynArray<int, 2> arr;

    // Seed with one element to ensure we exercise a non-empty state.
    arr.Push(111);

    int* block = arr.PushArr(3);
    ASSERT_NE(block, nullptr);

    block[0] = 1;
    block[1] = 2;
    block[2] = 3;

    ASSERT_EQ(arr.Size(), 4u);

    const int* mem = arr.Mem();
    ASSERT_NE(mem, nullptr);

    for (size_t i = 0; i < arr.Size(); ++i) {
        EXPECT_EQ(mem[i], arr[i]) << "Mismatch at index " << i;
    }

    // Also verify the expected logical sequence via the public accessor.
    EXPECT_EQ(arr[0], 111);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 2);
    EXPECT_EQ(arr[3], 3);
}

// Mem() should remain callable across common mutations (Clear/Pop/PopArr) and remain non-null.
TEST_F(DynArrayMemTest_16, MemCallableAfterMutations_16)
{
    DynArray<int, 4> arr;

    arr.Push(7);
    arr.Push(8);
    arr.Push(9);

    ASSERT_EQ(arr.Size(), 3u);
    EXPECT_NE(arr.Mem(), nullptr);

    // Pop one element.
    (void)arr.Pop();
    ASSERT_EQ(arr.Size(), 2u);
    EXPECT_NE(arr.Mem(), nullptr);

    // Pop remaining elements as an array.
    arr.PopArr(2);
    ASSERT_TRUE(arr.Empty());
    EXPECT_NE(arr.Mem(), nullptr);

    // Clear on already-empty should still leave Mem() callable.
    arr.Clear();
    ASSERT_TRUE(arr.Empty());
    EXPECT_NE(arr.Mem(), nullptr);

    // After reusing, Mem() should still provide a view consistent with indexing.
    arr.Push(42);
    ASSERT_EQ(arr.Size(), 1u);
    const int* mem = arr.Mem();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(mem[0], arr[0]);
    EXPECT_EQ(mem[0], 42);
}
