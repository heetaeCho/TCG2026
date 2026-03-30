// File: ./TestProjects/tinyxml2/tests/test_dynarray_swapremove_15.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

namespace {

class DynArraySwapRemoveTest_15 : public ::testing::Test {
protected:
    using Array = tinyxml2::DynArray<int, 4>;

    static Array MakeWithFour() {
        Array a;
        a.Push(10);
        a.Push(20);
        a.Push(30);
        a.Push(40);
        return a;
    }
};

TEST_F(DynArraySwapRemoveTest_15, SwapRemoveMiddleSwapsInLastAndDecrementsSize_15) {
    auto a = MakeWithFour();
    ASSERT_EQ(a.Size(), 4u);

    a.SwapRemove(1);

    EXPECT_EQ(a.Size(), 3u);
    // Index 1 should now contain the previous last element.
    EXPECT_EQ(a[0], 10);
    EXPECT_EQ(a[1], 40);
    EXPECT_EQ(a[2], 30);
}

TEST_F(DynArraySwapRemoveTest_15, SwapRemoveFirstSwapsInLastAndDecrementsSize_15) {
    auto a = MakeWithFour();
    ASSERT_EQ(a.Size(), 4u);

    a.SwapRemove(0);

    EXPECT_EQ(a.Size(), 3u);
    EXPECT_EQ(a[0], 40);
    EXPECT_EQ(a[1], 20);
    EXPECT_EQ(a[2], 30);
}

TEST_F(DynArraySwapRemoveTest_15, SwapRemoveLastJustDecrementsSizeAndKeepsPrefix_15) {
    auto a = MakeWithFour();
    ASSERT_EQ(a.Size(), 4u);

    a.SwapRemove(3);

    EXPECT_EQ(a.Size(), 3u);
    EXPECT_EQ(a[0], 10);
    EXPECT_EQ(a[1], 20);
    EXPECT_EQ(a[2], 30);
}

TEST_F(DynArraySwapRemoveTest_15, SwapRemoveOnlyElementBecomesEmpty_15) {
    Array a;
    EXPECT_TRUE(a.Empty());

    a.Push(123);
    ASSERT_FALSE(a.Empty());
    ASSERT_EQ(a.Size(), 1u);

    a.SwapRemove(0);

    EXPECT_EQ(a.Size(), 0u);
    EXPECT_TRUE(a.Empty());
}

#if GTEST_HAS_DEATH_TEST
#ifndef NDEBUG
TEST_F(DynArraySwapRemoveTest_15, SwapRemoveOnEmptyDiesInDebug_15) {
    Array a;
    ASSERT_TRUE(a.Empty());
    EXPECT_DEATH({ a.SwapRemove(0); }, "");
}

TEST_F(DynArraySwapRemoveTest_15, SwapRemoveOutOfRangeIndexDiesInDebug_15) {
    auto a = MakeWithFour();
    ASSERT_EQ(a.Size(), 4u);
    EXPECT_DEATH({ a.SwapRemove(4); }, "");  // i must be < Size()
}
#endif  // !NDEBUG
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace
