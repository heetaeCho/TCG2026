// File: sparse_array_empty_test_71.cc
#include <gtest/gtest.h>
#include "re2/sparse_array.h"

using re2::SparseArray;

// Suite: SparseArrayEmptyTest_71
// Notes:
// - We only assert on observable behavior from public APIs (e.g., empty(), set(), clear(), resize()).
// - Since empty() returns an int, we compare against 0/non-zero rather than assuming bool.

TEST(SparseArrayEmptyTest_71, InitiallyEmptyWithCapacity_71) {
    SparseArray<int> sa(8);
    EXPECT_NE(0, sa.empty());  // true (non-zero) means empty
}

TEST(SparseArrayEmptyTest_71, ZeroCapacity_IsEmpty_71) {
    SparseArray<int> sa(0);
    EXPECT_NE(0, sa.empty());
}

TEST(SparseArrayEmptyTest_71, SetMakesNonEmpty_71) {
    SparseArray<int> sa(8);
    EXPECT_NE(0, sa.empty());
    sa.set(3, 42);
    EXPECT_EQ(0, sa.empty());  // false (0) means not empty
}

TEST(SparseArrayEmptyTest_71, ClearMakesEmpty_71) {
    SparseArray<int> sa(8);
    sa.set(2, 7);
    ASSERT_EQ(0, sa.empty());  // confirm non-empty first
    sa.clear();
    EXPECT_NE(0, sa.empty());
}

TEST(SparseArrayEmptyTest_71, ResizePreservesEmptiness_WhenEmpty_71) {
    SparseArray<int> sa(4);
    ASSERT_NE(0, sa.empty());
    sa.resize(16);
    EXPECT_NE(0, sa.empty());
}

TEST(SparseArrayEmptyTest_71, ResizePreservesEmptiness_WhenNonEmpty_71) {
    SparseArray<int> sa(4);
    sa.set(1, 10);
    ASSERT_EQ(0, sa.empty());
    sa.resize(16);
    EXPECT_EQ(0, sa.empty());
}

TEST(SparseArrayEmptyTest_71, CopyConstruction_PreservesEmptiness_71) {
    SparseArray<int> sa(5);
    sa.set(0, 1);
    ASSERT_EQ(0, sa.empty());

    SparseArray<int> copy(sa);
    EXPECT_EQ(0, copy.empty());
}

TEST(SparseArrayEmptyTest_71, MoveConstruction_PreservesEmptinessOfTarget_71) {
    SparseArray<int> src(5);
    src.set(4, 99);
    ASSERT_EQ(0, src.empty());

    SparseArray<int> moved(std::move(src));
    // We only assert on the moved-to object; moved-from state is unspecified.
    EXPECT_EQ(0, moved.empty());
}

TEST(SparseArrayEmptyTest_71, SetAtBoundaryIndex_MakesNonEmpty_71) {
    SparseArray<int> sa(5);
    // Boundary: last valid index (capacity-dependent; here explicitly constructed as 5).
    sa.set(4, 123);
    EXPECT_EQ(0, sa.empty());
}
