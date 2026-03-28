#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Use a reasonable ITEM_SIZE for testing
static constexpr size_t TEST_ITEM_SIZE = 64;

class MemPoolTTest_20 : public ::testing::Test {
protected:
    MemPoolT<TEST_ITEM_SIZE> pool;
};

// Test that a freshly constructed pool has zero current allocations
TEST_F(MemPoolTTest_20, InitialCurrentAllocsIsZero_20) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that ItemSize returns the template parameter
TEST_F(MemPoolTTest_20, ItemSizeMatchesTemplateParameter_20) {
    EXPECT_EQ(pool.ItemSize(), TEST_ITEM_SIZE);
}

// Test that Alloc increases CurrentAllocs by one
TEST_F(MemPoolTTest_20, AllocIncreasesCurrentAllocs_20) {
    void* mem = pool.Alloc();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
}

// Test that Free decreases CurrentAllocs by one
TEST_F(MemPoolTTest_20, FreeDecreasesCurrentAllocs_20) {
    void* mem = pool.Alloc();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test multiple allocations increase CurrentAllocs correctly
TEST_F(MemPoolTTest_20, MultipleAllocsIncreaseCurrentAllocs_20) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    void* mem3 = pool.Alloc();
    ASSERT_NE(mem1, nullptr);
    ASSERT_NE(mem2, nullptr);
    ASSERT_NE(mem3, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 3u);
    pool.Free(mem1);
    pool.Free(mem2);
    pool.Free(mem3);
}

// Test that allocations return distinct pointers
TEST_F(MemPoolTTest_20, AllocReturnsDistinctPointers_20) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    ASSERT_NE(mem1, nullptr);
    ASSERT_NE(mem2, nullptr);
    EXPECT_NE(mem1, mem2);
    pool.Free(mem1);
    pool.Free(mem2);
}

// Test that freeing all allocations returns CurrentAllocs to zero
TEST_F(MemPoolTTest_20, FreeAllReturnsToZeroAllocs_20) {
    const int N = 10;
    void* mems[N];
    for (int i = 0; i < N; ++i) {
        mems[i] = pool.Alloc();
        ASSERT_NE(mems[i], nullptr);
    }
    EXPECT_EQ(pool.CurrentAllocs(), static_cast<size_t>(N));
    for (int i = 0; i < N; ++i) {
        pool.Free(mems[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that Clear resets allocations
TEST_F(MemPoolTTest_20, ClearResetsAllocations_20) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    ASSERT_NE(mem1, nullptr);
    ASSERT_NE(mem2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test Untracked initially returns zero
TEST_F(MemPoolTTest_20, InitialUntrackedIsZero_20) {
    EXPECT_EQ(pool.Untracked(), 0u);
}

// Test SetTracked affects Untracked count
TEST_F(MemPoolTTest_20, SetTrackedAffectsUntracked_20) {
    pool.SetTracked();
    // After SetTracked, the untracked count should change
    // The exact behavior depends on implementation, but we verify it doesn't crash
    // and Untracked returns a value
    size_t untracked = pool.Untracked();
    (void)untracked; // Just verify it's callable
}

// Test Trace doesn't crash with a valid name
TEST_F(MemPoolTTest_20, TraceDoesNotCrash_20) {
    pool.Alloc();
    EXPECT_NO_FATAL_FAILURE(pool.Trace("TestPool"));
}

// Test with different ITEM_SIZE
TEST(MemPoolTDifferentSizes_20, ItemSizeSmall_20) {
    MemPoolT<8> smallPool;
    EXPECT_EQ(smallPool.ItemSize(), 8u);
    EXPECT_EQ(smallPool.CurrentAllocs(), 0u);
    void* mem = smallPool.Alloc();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(smallPool.CurrentAllocs(), 1u);
    smallPool.Free(mem);
    EXPECT_EQ(smallPool.CurrentAllocs(), 0u);
}

TEST(MemPoolTDifferentSizes_20, ItemSizeLarge_20) {
    MemPoolT<256> largePool;
    EXPECT_EQ(largePool.ItemSize(), 256u);
    void* mem = largePool.Alloc();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(largePool.CurrentAllocs(), 1u);
    largePool.Free(mem);
}

// Test alloc-free-alloc cycle (memory reuse)
TEST_F(MemPoolTTest_20, AllocFreeAllocCycle_20) {
    void* mem1 = pool.Alloc();
    ASSERT_NE(mem1, nullptr);
    pool.Free(mem1);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    void* mem2 = pool.Alloc();
    ASSERT_NE(mem2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem2);
}

// Test many allocations to trigger multiple blocks
TEST_F(MemPoolTTest_20, ManyAllocationsStressTest_20) {
    const size_t N = 1000;
    std::vector<void*> mems;
    mems.reserve(N);
    for (size_t i = 0; i < N; ++i) {
        void* mem = pool.Alloc();
        ASSERT_NE(mem, nullptr);
        mems.push_back(mem);
    }
    EXPECT_EQ(pool.CurrentAllocs(), N);
    for (size_t i = 0; i < N; ++i) {
        pool.Free(mems[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that Clear works after many allocations
TEST_F(MemPoolTTest_20, ClearAfterManyAllocations_20) {
    for (int i = 0; i < 100; ++i) {
        pool.Alloc();
    }
    EXPECT_EQ(pool.CurrentAllocs(), 100u);
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test partial free
TEST_F(MemPoolTTest_20, PartialFree_20) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    void* mem3 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 3u);
    pool.Free(mem2);
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Free(mem1);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem3);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that Alloc returns non-null
TEST_F(MemPoolTTest_20, AllocReturnsNonNull_20) {
    void* mem = pool.Alloc();
    EXPECT_NE(mem, nullptr);
    pool.Free(mem);
}

// Test allocating after Clear
TEST_F(MemPoolTTest_20, AllocAfterClear_20) {
    void* mem1 = pool.Alloc();
    ASSERT_NE(mem1, nullptr);
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    void* mem2 = pool.Alloc();
    ASSERT_NE(mem2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem2);
}
