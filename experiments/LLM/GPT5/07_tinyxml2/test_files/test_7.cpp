// File: ./TestProjects/tinyxml2/tests/DynArray_PushArr_test_7.cpp

#include <gtest/gtest.h>
#include <cstddef>
#include <cstdint>
#include <limits>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

using tinyxml2::DynArray;

class DynArrayPushArrTest_7 : public ::testing::Test {
protected:
    // Keep INITIAL_SIZE small to exercise capacity growth with modest counts.
    DynArray<int, 4> arr;
};

TEST_F(DynArrayPushArrTest_7, PushArrIncreasesSizeAndRangeIsWritable_7) {
    ASSERT_EQ(arr.Size(), 0u);
    const size_t oldSize = arr.Size();

    int* p = arr.PushArr(3);

    ASSERT_NE(p, nullptr);
    EXPECT_EQ(arr.Size(), oldSize + 3);

    // Write through returned pointer and verify via operator[] (observable behavior).
    p[0] = 10;
    p[1] = 20;
    p[2] = 30;

    EXPECT_EQ(arr[oldSize + 0], 10);
    EXPECT_EQ(arr[oldSize + 1], 20);
    EXPECT_EQ(arr[oldSize + 2], 30);
}

TEST_F(DynArrayPushArrTest_7, PushArrZeroCountDoesNotChangeSize_7) {
    arr.Push(1);
    arr.Push(2);

    const size_t oldSize = arr.Size();
    const int* oldMem = arr.Mem();

    int* p = arr.PushArr(0);

    EXPECT_EQ(arr.Size(), oldSize);

    // Should return a pointer to the "end" (or equivalent) of the current memory.
    // We only verify it's consistent with Mem()+oldSize as an observable property.
    ASSERT_NE(arr.Mem(), nullptr);
    EXPECT_EQ(p, arr.Mem() + oldSize);

    // No requirement that Mem() stays identical, but for zero count it should be reasonable to
    // observe that existing elements remain intact.
    (void)oldMem;
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST_F(DynArrayPushArrTest_7, PushArrAppendsAfterExistingElements_7) {
    arr.Push(7);
    arr.Push(8);
    arr.Push(9);

    const size_t oldSize = arr.Size();
    int* p = arr.PushArr(2);

    ASSERT_NE(p, nullptr);
    EXPECT_EQ(arr.Size(), oldSize + 2);

    // Ensure old elements are preserved.
    EXPECT_EQ(arr[0], 7);
    EXPECT_EQ(arr[1], 8);
    EXPECT_EQ(arr[2], 9);

    // Fill the appended range and verify indexing aligns with append semantics.
    p[0] = 100;
    p[1] = 200;

    EXPECT_EQ(arr[oldSize + 0], 100);
    EXPECT_EQ(arr[oldSize + 1], 200);
}

TEST_F(DynArrayPushArrTest_7, PushArrReturnPointerMatchesMemPlusOldSize_7) {
    arr.Push(1);
    arr.Push(2);

    const size_t oldSize = arr.Size();

    int* p = arr.PushArr(5);

    ASSERT_NE(arr.Mem(), nullptr);
    // Observable contract from the interface: PushArr returns a pointer to the newly appended block.
    EXPECT_EQ(p, arr.Mem() + oldSize);

    // Spot-check writability through pointer and visibility through operator[].
    p[0] = 11;
    p[4] = 55;
    EXPECT_EQ(arr[oldSize + 0], 11);
    EXPECT_EQ(arr[oldSize + 4], 55);
}

TEST_F(DynArrayPushArrTest_7, PushArrLargeCountCanGrowCapacityWhilePreservingContents_7) {
    // Seed with some values.
    for (int i = 0; i < 4; ++i) arr.Push(100 + i);

    const size_t oldSize = arr.Size();
    const size_t oldCap = arr.Capacity();
    const int* oldMem = arr.Mem();

    int* p = arr.PushArr(20);

    ASSERT_NE(p, nullptr);
    EXPECT_EQ(arr.Size(), oldSize + 20);

    // Capacity should be at least size; it may grow.
    EXPECT_GE(arr.Capacity(), arr.Size());
    EXPECT_GE(arr.Capacity(), oldCap);  // may stay same or increase depending on implementation.

    // Existing values remain observable and unchanged.
    for (size_t i = 0; i < oldSize; ++i) {
        EXPECT_EQ(arr[i], 100 + static_cast<int>(i));
    }

    // We avoid asserting reallocation must happen, but if it did, Mem() may change.
    (void)oldMem;

    // Write into new block and verify.
    p[0] = 999;
    p[19] = 777;
    EXPECT_EQ(arr[oldSize + 0], 999);
    EXPECT_EQ(arr[oldSize + 19], 777);
}

TEST_F(DynArrayPushArrTest_7, PushArrOverflowTriggersAssertDeath_7) {
#if GTEST_HAS_DEATH_TEST
    // Make size = 1 so that count = SIZE_MAX fails the guard: _size <= SIZE_MAX - count.
    arr.Push(123);

    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(
        {
            // The assertion should fire before attempting any allocation.
            (void)arr.PushArr(std::numeric_limits<size_t>::max());
        },
        ""
    );
#else
    GTEST_SKIP() << "Death tests are not supported on this platform/configuration.";
#endif
}

}  // namespace
