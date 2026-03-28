// TEST_ID: 18
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class MemPoolTTest_18 : public ::testing::Test {
protected:
    // Pick a reasonably sized item to avoid edge cases with very small ITEM_SIZE.
    tinyxml2::MemPoolT<64> pool;
};

TEST_F(MemPoolTTest_18, ClearOnFreshPoolKeepsCountsAtZero_18) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    EXPECT_EQ(pool.Untracked(), 0u);

    pool.Clear();

    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    EXPECT_EQ(pool.Untracked(), 0u);

    // Idempotent / safe to call repeatedly.
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    EXPECT_EQ(pool.Untracked(), 0u);
}

TEST_F(MemPoolTTest_18, ClearAfterAllocationsResetsCurrentAllocsToZero_18) {
    void* p1 = pool.Alloc();
    void* p2 = pool.Alloc();
    void* p3 = pool.Alloc();

    ASSERT_NE(p1, nullptr);
    ASSERT_NE(p2, nullptr);
    ASSERT_NE(p3, nullptr);

    EXPECT_GT(pool.CurrentAllocs(), 0u);

    pool.Clear();

    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

TEST_F(MemPoolTTest_18, ClearResetsUntrackedToZero_18) {
    // We don't assume how Untracked changes during normal use, only that Clear resets it.
    (void)pool.Alloc();
    (void)pool.Alloc();

    pool.Clear();

    EXPECT_EQ(pool.Untracked(), 0u);
}

TEST_F(MemPoolTTest_18, ClearAllowsPoolToBeUsedAgain_18) {
    void* before = pool.Alloc();
    ASSERT_NE(before, nullptr);
    EXPECT_GT(pool.CurrentAllocs(), 0u);

    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);

    void* after = pool.Alloc();
    EXPECT_NE(after, nullptr);
    EXPECT_GT(pool.CurrentAllocs(), 0u);

    // Cleanup (not strictly necessary for the test, but keeps usage well-formed).
    pool.Free(after);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

}  // namespace
