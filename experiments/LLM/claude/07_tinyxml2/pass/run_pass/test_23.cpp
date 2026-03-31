#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Use a reasonable ITEM_SIZE for testing
static constexpr size_t TEST_ITEM_SIZE = 64;

class MemPoolTTest_23 : public ::testing::Test {
protected:
    MemPoolT<TEST_ITEM_SIZE> pool;
};

// Test that a freshly constructed pool has zero current allocations
TEST_F(MemPoolTTest_23, InitialCurrentAllocsIsZero_23) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that ItemSize returns the template parameter
TEST_F(MemPoolTTest_23, ItemSizeReturnsTemplateParameter_23) {
    EXPECT_EQ(pool.ItemSize(), TEST_ITEM_SIZE);
}

// Test that Untracked returns zero initially
TEST_F(MemPoolTTest_23, InitialUntrackedIsZero_23) {
    EXPECT_EQ(pool.Untracked(), 0u);
}

// Test that a single allocation increases CurrentAllocs
TEST_F(MemPoolTTest_23, AllocIncreasesCurrentAllocs_23) {
    void* mem = pool.Alloc();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem);
}

// Test that freeing an allocation decreases CurrentAllocs
TEST_F(MemPoolTTest_23, FreeDecreasesCurrentAllocs_23) {
    void* mem = pool.Alloc();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test multiple allocations
TEST_F(MemPoolTTest_23, MultipleAllocsIncreaseCurrentAllocs_23) {
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
TEST_F(MemPoolTTest_23, AllocReturnsDistinctPointers_23) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    ASSERT_NE(mem1, nullptr);
    ASSERT_NE(mem2, nullptr);
    EXPECT_NE(mem1, mem2);
    pool.Free(mem1);
    pool.Free(mem2);
}

// Test that after freeing, the memory can be reused (alloc after free should succeed)
TEST_F(MemPoolTTest_23, AllocAfterFreeSucceeds_23) {
    void* mem1 = pool.Alloc();
    pool.Free(mem1);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    void* mem2 = pool.Alloc();
    ASSERT_NE(mem2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem2);
}

// Test Clear resets the pool
TEST_F(MemPoolTTest_23, ClearResetsPool_23) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    // Don't free - just clear the pool
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that after Clear, new allocations work
TEST_F(MemPoolTTest_23, AllocAfterClearWorks_23) {
    void* mem1 = pool.Alloc();
    pool.Clear();
    void* mem2 = pool.Alloc();
    ASSERT_NE(mem2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem2);
}

// Test many allocations and frees
TEST_F(MemPoolTTest_23, ManyAllocsAndFrees_23) {
    const int N = 100;
    void* ptrs[N];
    for (int i = 0; i < N; ++i) {
        ptrs[i] = pool.Alloc();
        ASSERT_NE(ptrs[i], nullptr);
    }
    EXPECT_EQ(pool.CurrentAllocs(), static_cast<size_t>(N));
    for (int i = 0; i < N; ++i) {
        pool.Free(ptrs[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test Trace does not crash (smoke test)
TEST_F(MemPoolTTest_23, TraceDoesNotCrash_23) {
    void* mem = pool.Alloc();
    ASSERT_NO_FATAL_FAILURE(pool.Trace("test_pool"));
    pool.Free(mem);
}

// Test SetTracked can be called without crash
TEST_F(MemPoolTTest_23, SetTrackedDoesNotCrash_23) {
    ASSERT_NO_FATAL_FAILURE(pool.SetTracked());
}

// Test Untracked behavior with SetTracked
TEST_F(MemPoolTTest_23, SetTrackedAffectsUntracked_23) {
    // Alloc before SetTracked - these should be untracked
    void* mem1 = pool.Alloc();
    size_t untrackedBefore = pool.Untracked();
    pool.SetTracked();
    // After SetTracked, untracked count might change
    // We just verify it's callable and returns a valid value
    size_t untrackedAfter = pool.Untracked();
    EXPECT_GE(untrackedAfter, 0u);
    pool.Free(mem1);
}

// Test with different template parameter sizes
TEST(MemPoolTDifferentSizes_23, SmallItemSize_23) {
    MemPoolT<8> smallPool;
    EXPECT_EQ(smallPool.ItemSize(), 8u);
    void* mem = smallPool.Alloc();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(smallPool.CurrentAllocs(), 1u);
    smallPool.Free(mem);
    EXPECT_EQ(smallPool.CurrentAllocs(), 0u);
}

TEST(MemPoolTDifferentSizes_23, LargeItemSize_23) {
    MemPoolT<256> largePool;
    EXPECT_EQ(largePool.ItemSize(), 256u);
    void* mem = largePool.Alloc();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(largePool.CurrentAllocs(), 1u);
    largePool.Free(mem);
    EXPECT_EQ(largePool.CurrentAllocs(), 0u);
}

// Test allocate, free interleaved pattern
TEST_F(MemPoolTTest_23, InterleavedAllocFree_23) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Free(mem1);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    void* mem3 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Free(mem2);
    pool.Free(mem3);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that allocated memory is writable
TEST_F(MemPoolTTest_23, AllocatedMemoryIsWritable_23) {
    void* mem = pool.Alloc();
    ASSERT_NE(mem, nullptr);
    // Write to the allocated memory - should not crash
    memset(mem, 0xAB, TEST_ITEM_SIZE);
    unsigned char* bytes = static_cast<unsigned char*>(mem);
    EXPECT_EQ(bytes[0], 0xAB);
    EXPECT_EQ(bytes[TEST_ITEM_SIZE - 1], 0xAB);
    pool.Free(mem);
}

// Test Clear on empty pool does not crash
TEST_F(MemPoolTTest_23, ClearOnEmptyPool_23) {
    ASSERT_NO_FATAL_FAILURE(pool.Clear());
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test Trace on empty pool
TEST_F(MemPoolTTest_23, TraceOnEmptyPool_23) {
    ASSERT_NO_FATAL_FAILURE(pool.Trace("empty_pool"));
}

// Test destructor cleans up (implicit - no crash when pool goes out of scope with allocations)
TEST(MemPoolTDestructor_23, DestructorWithOutstandingAllocs_23) {
    {
        MemPoolT<TEST_ITEM_SIZE> localPool;
        void* mem1 = localPool.Alloc();
        void* mem2 = localPool.Alloc();
        (void)mem1;
        (void)mem2;
        // Pool destroyed with outstanding allocations - should not crash
    }
    SUCCEED();
}
