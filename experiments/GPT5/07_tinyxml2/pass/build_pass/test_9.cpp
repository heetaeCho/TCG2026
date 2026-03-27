// File: ./TestProjects/tinyxml2/tests/DynArray_PopArr_test_9.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace tinyxml2 {

class DynArrayPopArrTest_9 : public ::testing::Test {
protected:
    DynArray<int, 4> arr;
};

TEST_F(DynArrayPopArrTest_9, PopArrReducesSizeAndUpdatesTop_9) {
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.Push(5);

    ASSERT_EQ(arr.Size(), 5u);
    ASSERT_FALSE(arr.Empty());
    ASSERT_EQ(arr.PeekTop(), 5);

    arr.PopArr(2);

    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_FALSE(arr.Empty());
    EXPECT_EQ(arr.PeekTop(), 3);
}

TEST_F(DynArrayPopArrTest_9, PopArrZeroDoesNothing_9) {
    arr.Push(10);
    arr.Push(20);
    arr.Push(30);

    const size_t beforeSize = arr.Size();
    const int beforeTop = arr.PeekTop();

    arr.PopArr(0);

    EXPECT_EQ(arr.Size(), beforeSize);
    EXPECT_FALSE(arr.Empty());
    EXPECT_EQ(arr.PeekTop(), beforeTop);
}

TEST_F(DynArrayPopArrTest_9, PopArrAllElementsBecomesEmpty_9) {
    arr.Push(7);
    arr.Push(8);
    arr.Push(9);

    ASSERT_EQ(arr.Size(), 3u);
    ASSERT_FALSE(arr.Empty());

    arr.PopArr(3);

    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

TEST_F(DynArrayPopArrTest_9, PopArrInMultipleSteps_9) {
    for (int i = 1; i <= 6; ++i) {
        arr.Push(i);
    }
    ASSERT_EQ(arr.Size(), 6u);
    ASSERT_EQ(arr.PeekTop(), 6);

    arr.PopArr(1);
    EXPECT_EQ(arr.Size(), 5u);
    EXPECT_EQ(arr.PeekTop(), 5);

    arr.PopArr(3);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr.PeekTop(), 2);

    arr.PopArr(2);
    EXPECT_EQ(arr.Size(), 0u);
    EXPECT_TRUE(arr.Empty());
}

#if !defined(NDEBUG)
// In debug builds, TIXMLASSERT typically triggers a process-terminating assert on invalid usage.
TEST_F(DynArrayPopArrTest_9, PopArrMoreThanSizeTriggersAssert_9) {
    arr.Push(1);
    ASSERT_EQ(arr.Size(), 1u);

    EXPECT_DEATH(arr.PopArr(2), ".*");
}
#endif

}  // namespace tinyxml2
