#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Using a reasonable ITEM_SIZE for testing
static constexpr size_t TEST_ITEM_SIZE = 64;

class MemPoolTTest_25 : public ::testing::Test {
protected:
    MemPoolT<TEST_ITEM_SIZE> pool;
};

// Test that a freshly constructed pool has zero untracked count
TEST_F(MemPoolTTest_25, InitialUntrackedIsZero_25) {
    EXPECT_EQ(pool.Untracked(), 0u);
}

// Test that a freshly constructed pool has zero current allocations
TEST_F(MemPoolTTest_25, InitialCurrentAllocsIsZero_25) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that ItemSize returns the template parameter
TEST_F(MemPoolTTest_25, ItemSizeReturnsTemplateParam_25) {
    EXPECT_EQ(pool.ItemSize(), TEST_ITEM_SIZE);
}

// Test that ItemSize works with different template parameters
TEST(MemPoolTItemSizeTest_25, DifferentItemSizes_25) {
    MemPoolT<16> pool16;
    EXPECT_EQ(pool16.ItemSize(), 16u);

    MemPoolT<128> pool128;
    EXPECT_EQ(pool128.ItemSize(), 128u);

    MemPoolT<256> pool256;
    EXPECT_EQ(pool256.ItemSize(), 256u);
}

// Test that Alloc returns a non-null pointer
TEST_F(MemPoolTTest_25, AllocReturnsNonNull_25) {
    void* ptr = pool.Alloc();
    ASSERT_NE(ptr, nullptr);
    pool.Free(ptr);
}

// Test that CurrentAllocs increases after Alloc
TEST_F(MemPoolTTest_25, AllocIncreasesCurrentAllocs_25) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    void* ptr = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr);
}

// Test that Free decreases CurrentAllocs
TEST_F(MemPoolTTest_25, FreeDecreasesCurrentAllocs_25) {
    void* ptr = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test multiple allocations
TEST_F(MemPoolTTest_25, MultipleAllocations_25) {
    void* ptrs[10];
    for (int i = 0; i < 10; i++) {
        ptrs[i] = pool.Alloc();
        ASSERT_NE(ptrs[i], nullptr);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 10u);

    for (int i = 0; i < 10; i++) {
        pool.Free(ptrs[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that each allocation returns a different pointer
TEST_F(MemPoolTTest_25, AllocReturnsDifferentPointers_25) {
    void* ptr1 = pool.Alloc();
    void* ptr2 = pool.Alloc();
    EXPECT_NE(ptr1, ptr2);
    pool.Free(ptr1);
    pool.Free(ptr2);
}

// Test that Untracked increases when allocating without SetTracked
TEST_F(MemPoolTTest_25, UntrackedIncreasesOnAlloc_25) {
    size_t initialUntracked = pool.Untracked();
    void* ptr = pool.Alloc();
    EXPECT_EQ(pool.Untracked(), initialUntracked + 1);
    pool.Free(ptr);
}

// Test SetTracked resets tracking
TEST_F(MemPoolTTest_25, SetTrackedResetsUntracked_25) {
    void* ptr = pool.Alloc();
    EXPECT_GT(pool.Untracked(), 0u);
    pool.SetTracked();
    EXPECT_EQ(pool.Untracked(), 0u);
    pool.Free(ptr);
}

// Test Clear resets the pool
TEST_F(MemPoolTTest_25, ClearResetsPool_25) {
    void* ptr1 = pool.Alloc();
    void* ptr2 = pool.Alloc();
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test alloc-free-alloc cycle can reuse memory
TEST_F(MemPoolTTest_25, AllocFreeCycle_25) {
    void* ptr1 = pool.Alloc();
    pool.Free(ptr1);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);

    void* ptr2 = pool.Alloc();
    ASSERT_NE(ptr2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr2);
}

// Test many allocations to trigger multiple block allocations
TEST_F(MemPoolTTest_25, ManyAllocations_25) {
    const int count = 1000;
    void* ptrs[count];
    for (int i = 0; i < count; i++) {
        ptrs[i] = pool.Alloc();
        ASSERT_NE(ptrs[i], nullptr);
    }
    EXPECT_EQ(pool.CurrentAllocs(), static_cast<size_t>(count));

    for (int i = 0; i < count; i++) {
        pool.Free(ptrs[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test Trace doesn't crash (we can't verify output, but it shouldn't segfault)
TEST_F(MemPoolTTest_25, TraceDoesNotCrash_25) {
    void* ptr = pool.Alloc();
    EXPECT_NO_FATAL_FAILURE(pool.Trace("test_pool"));
    pool.Free(ptr);
}

// Test Trace with empty pool
TEST_F(MemPoolTTest_25, TraceEmptyPoolDoesNotCrash_25) {
    EXPECT_NO_FATAL_FAILURE(pool.Trace("empty_pool"));
}

// Test multiple SetTracked calls
TEST_F(MemPoolTTest_25, MultipleSetTracked_25) {
    void* ptr1 = pool.Alloc();
    pool.SetTracked();
    EXPECT_EQ(pool.Untracked(), 0u);

    void* ptr2 = pool.Alloc();
    EXPECT_EQ(pool.Untracked(), 1u);
    pool.SetTracked();
    EXPECT_EQ(pool.Untracked(), 0u);

    pool.Free(ptr1);
    pool.Free(ptr2);
}

// Test with smallest reasonable item size
TEST(MemPoolTSmallItemTest_25, SmallItemSize_25) {
    MemPoolT<8> smallPool;
    EXPECT_EQ(smallPool.ItemSize(), 8u);
    void* ptr = smallPool.Alloc();
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(smallPool.CurrentAllocs(), 1u);
    smallPool.Free(ptr);
    EXPECT_EQ(smallPool.CurrentAllocs(), 0u);
}

// Test with larger item size
TEST(MemPoolTLargeItemTest_25, LargeItemSize_25) {
    MemPoolT<1024> largePool;
    EXPECT_EQ(largePool.ItemSize(), 1024u);
    void* ptr = largePool.Alloc();
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(largePool.CurrentAllocs(), 1u);
    largePool.Free(ptr);
    EXPECT_EQ(largePool.CurrentAllocs(), 0u);
}

// Test that freeing in reverse order works
TEST_F(MemPoolTTest_25, FreeInReverseOrder_25) {
    void* ptrs[5];
    for (int i = 0; i < 5; i++) {
        ptrs[i] = pool.Alloc();
    }
    for (int i = 4; i >= 0; i--) {
        pool.Free(ptrs[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that freeing in random order works
TEST_F(MemPoolTTest_25, FreeInRandomOrder_25) {
    void* ptrs[5];
    for (int i = 0; i < 5; i++) {
        ptrs[i] = pool.Alloc();
    }
    pool.Free(ptrs[2]);
    pool.Free(ptrs[0]);
    pool.Free(ptrs[4]);
    pool.Free(ptrs[1]);
    pool.Free(ptrs[3]);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test interleaved alloc and free
TEST_F(MemPoolTTest_25, InterleavedAllocFree_25) {
    void* ptr1 = pool.Alloc();
    void* ptr2 = pool.Alloc();
    pool.Free(ptr1);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    void* ptr3 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Free(ptr2);
    pool.Free(ptr3);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}
