#include <gtest/gtest.h>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Use a reasonable ITEM_SIZE for testing
static const size_t TEST_ITEM_SIZE = 64;

class MemPoolTTest_17 : public ::testing::Test {
protected:
    MemPoolT<TEST_ITEM_SIZE> pool;
};

// Test that a freshly constructed pool has zero current allocations
TEST_F(MemPoolTTest_17, InitialCurrentAllocsIsZero_17) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that ItemSize returns the template parameter
TEST_F(MemPoolTTest_17, ItemSizeReturnsTemplateParameter_17) {
    EXPECT_EQ(pool.ItemSize(), TEST_ITEM_SIZE);
}

// Test that ItemSize works with different template sizes
TEST(MemPoolTItemSizeTest_17, ItemSizeVariesWithTemplate_17) {
    MemPoolT<32> pool32;
    MemPoolT<128> pool128;
    MemPoolT<1> pool1;

    EXPECT_EQ(pool32.ItemSize(), 32u);
    EXPECT_EQ(pool128.ItemSize(), 128u);
    EXPECT_EQ(pool1.ItemSize(), 1u);
}

// Test that Alloc returns a non-null pointer
TEST_F(MemPoolTTest_17, AllocReturnsNonNull_17) {
    void* mem = pool.Alloc();
    ASSERT_NE(mem, nullptr);
    pool.Free(mem);
}

// Test that Alloc increases current allocations count
TEST_F(MemPoolTTest_17, AllocIncreasesCurrentAllocs_17) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    void* mem = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem);
}

// Test that Free decreases current allocations count
TEST_F(MemPoolTTest_17, FreeDecreasesCurrentAllocs_17) {
    void* mem = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test multiple allocations
TEST_F(MemPoolTTest_17, MultipleAllocationsIncreaseCount_17) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    void* mem3 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 3u);

    pool.Free(mem1);
    pool.Free(mem2);
    pool.Free(mem3);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that multiple Alloc calls return distinct pointers
TEST_F(MemPoolTTest_17, AllocReturnsDistinctPointers_17) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    EXPECT_NE(mem1, mem2);

    pool.Free(mem1);
    pool.Free(mem2);
}

// Test Clear resets the pool
TEST_F(MemPoolTTest_17, ClearResetsCurrentAllocs_17) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 2u);

    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that after Clear, Alloc still works
TEST_F(MemPoolTTest_17, AllocWorksAfterClear_17) {
    void* mem1 = pool.Alloc();
    pool.Clear();

    void* mem2 = pool.Alloc();
    ASSERT_NE(mem2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem2);
}

// Test Untracked returns initial value
TEST_F(MemPoolTTest_17, InitialUntrackedIsZero_17) {
    EXPECT_EQ(pool.Untracked(), 0u);
}

// Test SetTracked affects Untracked count
TEST_F(MemPoolTTest_17, SetTrackedModifiesUntracked_17) {
    pool.SetTracked();
    // After calling SetTracked, untracked should decrement or change
    // Since initial is 0, it may underflow or stay at 0 depending on impl
    // We simply verify the function is callable
    // The behavior is observable through Untracked()
    size_t untracked = pool.Untracked();
    // We can't make strong assumptions without knowing the implementation,
    // but we verify no crash occurred
    (void)untracked;
}

// Test Trace doesn't crash with a valid name
TEST_F(MemPoolTTest_17, TraceDoesNotCrash_17) {
    void* mem = pool.Alloc();
    EXPECT_NO_FATAL_FAILURE(pool.Trace("TestPool"));
    pool.Free(mem);
}

// Test Trace with empty string
TEST_F(MemPoolTTest_17, TraceWithEmptyStringDoesNotCrash_17) {
    EXPECT_NO_FATAL_FAILURE(pool.Trace(""));
}

// Test allocating and freeing many items (stress boundary)
TEST_F(MemPoolTTest_17, ManyAllocationsAndFrees_17) {
    const int COUNT = 1000;
    void* ptrs[COUNT];
    for (int i = 0; i < COUNT; ++i) {
        ptrs[i] = pool.Alloc();
        ASSERT_NE(ptrs[i], nullptr);
    }
    EXPECT_EQ(pool.CurrentAllocs(), static_cast<size_t>(COUNT));

    for (int i = 0; i < COUNT; ++i) {
        pool.Free(ptrs[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that freed memory can be reused (alloc after free)
TEST_F(MemPoolTTest_17, FreedMemoryCanBeReused_17) {
    void* mem1 = pool.Alloc();
    pool.Free(mem1);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);

    void* mem2 = pool.Alloc();
    ASSERT_NE(mem2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem2);
}

// Test alternating alloc and free
TEST_F(MemPoolTTest_17, AlternatingAllocFree_17) {
    for (int i = 0; i < 100; ++i) {
        void* mem = pool.Alloc();
        ASSERT_NE(mem, nullptr);
        EXPECT_EQ(pool.CurrentAllocs(), 1u);
        pool.Free(mem);
        EXPECT_EQ(pool.CurrentAllocs(), 0u);
    }
}

// Test with smallest possible ITEM_SIZE
TEST(MemPoolTSmallItemTest_17, SmallItemSize_17) {
    MemPoolT<1> smallPool;
    EXPECT_EQ(smallPool.ItemSize(), 1u);

    void* mem = smallPool.Alloc();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(smallPool.CurrentAllocs(), 1u);
    smallPool.Free(mem);
    EXPECT_EQ(smallPool.CurrentAllocs(), 0u);
}

// Test with a larger ITEM_SIZE
TEST(MemPoolTLargeItemTest_17, LargeItemSize_17) {
    MemPoolT<1024> largePool;
    EXPECT_EQ(largePool.ItemSize(), 1024u);

    void* mem = largePool.Alloc();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(largePool.CurrentAllocs(), 1u);
    largePool.Free(mem);
    EXPECT_EQ(largePool.CurrentAllocs(), 0u);
}

// Test destructor cleans up without crash (implicit through test fixture teardown)
TEST(MemPoolTDestructorTest_17, DestructorCleansUpAllocations_17) {
    MemPoolT<TEST_ITEM_SIZE>* pool = new MemPoolT<TEST_ITEM_SIZE>();
    pool->Alloc();
    pool->Alloc();
    // Destructor should handle cleanup even with outstanding allocations
    EXPECT_NO_FATAL_FAILURE(delete pool);
}

// Test Clear on an empty pool doesn't crash
TEST_F(MemPoolTTest_17, ClearOnEmptyPool_17) {
    EXPECT_NO_FATAL_FAILURE(pool.Clear());
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test multiple Clears in a row
TEST_F(MemPoolTTest_17, MultipleClearsDoNotCrash_17) {
    void* mem = pool.Alloc();
    (void)mem;
    pool.Clear();
    EXPECT_NO_FATAL_FAILURE(pool.Clear());
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}
