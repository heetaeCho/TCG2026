// TEST_ID: 13
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class DynArraySizeTest_13 : public ::testing::Test {
protected:
    using Arr = tinyxml2::DynArray<int, 2>;
};

TEST_F(DynArraySizeTest_13, DefaultConstructedSizeIsZero_13) {
    Arr a;
    EXPECT_EQ(a.Size(), 0u);
    EXPECT_TRUE(a.Empty());
}

TEST_F(DynArraySizeTest_13, SizeIsCallableOnConstObject_13) {
    Arr a;
    a.Push(1);
    a.Push(2);

    const Arr& ca = a;
    EXPECT_EQ(ca.Size(), 2u);
}

TEST_F(DynArraySizeTest_13, PushIncreasesSizeByOneEachTime_13) {
    Arr a;
    EXPECT_EQ(a.Size(), 0u);

    a.Push(10);
    EXPECT_EQ(a.Size(), 1u);

    a.Push(20);
    EXPECT_EQ(a.Size(), 2u);

    a.Push(30);
    EXPECT_EQ(a.Size(), 3u);
}

TEST_F(DynArraySizeTest_13, ClearResetsSizeToZero_13) {
    Arr a;
    a.Push(1);
    a.Push(2);
    a.Push(3);
    ASSERT_EQ(a.Size(), 3u);

    a.Clear();
    EXPECT_EQ(a.Size(), 0u);
    EXPECT_TRUE(a.Empty());

    // Clearing an already-empty array should keep it empty.
    a.Clear();
    EXPECT_EQ(a.Size(), 0u);
    EXPECT_TRUE(a.Empty());
}

TEST_F(DynArraySizeTest_13, PushArrIncreasesSizeByCount_13) {
    Arr a;

    int* p = a.PushArr(3);
    (void)p; // Avoid assuming anything about pointer value beyond successful call.
    EXPECT_EQ(a.Size(), 3u);

    // Add more via PushArr
    a.PushArr(2);
    EXPECT_EQ(a.Size(), 5u);
}

TEST_F(DynArraySizeTest_13, PushArrElementsAccessibleViaOperatorIndex_13) {
    Arr a;

    int* p = a.PushArr(4);
    ASSERT_NE(p, nullptr); // If PushArr succeeds, returned storage should be usable.

    // Fill returned storage and verify observable access through operator[].
    for (size_t i = 0; i < 4; ++i) {
        p[i] = static_cast<int>(100 + i);
    }

    EXPECT_EQ(a.Size(), 4u);
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(a[i], static_cast<int>(100 + i));
    }
}

TEST_F(DynArraySizeTest_13, PopDecreasesSizeByOne_13) {
    Arr a;
    a.Push(1);
    a.Push(2);
    a.Push(3);
    ASSERT_EQ(a.Size(), 3u);

    (void)a.Pop();
    EXPECT_EQ(a.Size(), 2u);

    (void)a.Pop();
    EXPECT_EQ(a.Size(), 1u);

    (void)a.Pop();
    EXPECT_EQ(a.Size(), 0u);
    EXPECT_TRUE(a.Empty());
}

TEST_F(DynArraySizeTest_13, PopArrDecreasesSizeByCount_13) {
    Arr a;
    a.PushArr(6);
    ASSERT_EQ(a.Size(), 6u);

    a.PopArr(2);
    EXPECT_EQ(a.Size(), 4u);

    a.PopArr(4);
    EXPECT_EQ(a.Size(), 0u);
    EXPECT_TRUE(a.Empty());
}

TEST_F(DynArraySizeTest_13, SwapRemoveDecreasesSizeByOneWhenIndexValid_13) {
    Arr a;
    a.Push(10);
    a.Push(20);
    a.Push(30);
    a.Push(40);
    ASSERT_EQ(a.Size(), 4u);

    a.SwapRemove(1);
    EXPECT_EQ(a.Size(), 3u);

    a.SwapRemove(0);
    EXPECT_EQ(a.Size(), 2u);
}

TEST_F(DynArraySizeTest_13, SizeUnaffectedByMemOrCapacityQueries_13) {
    Arr a;
    a.Push(7);
    a.Push(8);
    ASSERT_EQ(a.Size(), 2u);

    // These calls should not mutate size (observable behavior).
    (void)a.Mem();
    (void)a.Capacity();
    EXPECT_EQ(a.Size(), 2u);

    const Arr& ca = a;
    (void)ca.Mem();
    (void)ca.Capacity();
    EXPECT_EQ(ca.Size(), 2u);
}

}  // namespace
