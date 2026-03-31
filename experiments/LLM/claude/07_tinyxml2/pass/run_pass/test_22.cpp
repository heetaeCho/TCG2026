#include <gtest/gtest.h>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Use a reasonable ITEM_SIZE for testing
static constexpr size_t TEST_ITEM_SIZE = 64;

class MemPoolTTest_22 : public ::testing::Test {
protected:
    MemPoolT<TEST_ITEM_SIZE> pool;
};

// Test that a freshly constructed pool has zero current allocations
TEST_F(MemPoolTTest_22, InitialCurrentAllocsIsZero_22) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that ItemSize returns the template parameter
TEST_F(MemPoolTTest_22, ItemSizeReturnsTemplateParam_22) {
    EXPECT_EQ(pool.ItemSize(), TEST_ITEM_SIZE);
}

// Test that Alloc returns a non-null pointer
TEST_F(MemPoolTTest_22, AllocReturnsNonNull_22) {
    void* mem = pool.Alloc();
    ASSERT_NE(mem, nullptr);
    pool.Free(mem);
}

// Test that Alloc increases CurrentAllocs by 1
TEST_F(MemPoolTTest_22, AllocIncreasesCurrentAllocs_22) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    void* mem = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem);
}

// Test that Free decreases CurrentAllocs by 1
TEST_F(MemPoolTTest_22, FreeDecreasesCurrentAllocs_22) {
    void* mem = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that Free with nullptr does not change CurrentAllocs
TEST_F(MemPoolTTest_22, FreeNullptrDoesNothing_22) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    pool.Free(nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that Free with nullptr after an allocation doesn't affect the count
TEST_F(MemPoolTTest_22, FreeNullptrAfterAllocDoesNotAffectCount_22) {
    void* mem = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test multiple allocations increase CurrentAllocs correctly
TEST_F(MemPoolTTest_22, MultipleAllocsIncreaseCurrentAllocs_22) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    void* mem3 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 3u);
    pool.Free(mem1);
    pool.Free(mem2);
    pool.Free(mem3);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that allocations return distinct pointers
TEST_F(MemPoolTTest_22, AllocReturnsDistinctPointers_22) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    EXPECT_NE(mem1, mem2);
    pool.Free(mem1);
    pool.Free(mem2);
}

// Test that freed memory can be reused by subsequent Alloc
TEST_F(MemPoolTTest_22, FreedMemoryCanBeReused_22) {
    void* mem1 = pool.Alloc();
    pool.Free(mem1);
    void* mem2 = pool.Alloc();
    // After freeing, the pool may reuse the same memory
    // We just verify it's valid (non-null) and alloc count is correct
    ASSERT_NE(mem2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem2);
}

// Test alloc-free-alloc cycle maintains correct count
TEST_F(MemPoolTTest_22, AllocFreeCycleMaintainsCorrectCount_22) {
    for (int i = 0; i < 100; ++i) {
        void* mem = pool.Alloc();
        EXPECT_EQ(pool.CurrentAllocs(), 1u);
        pool.Free(mem);
        EXPECT_EQ(pool.CurrentAllocs(), 0u);
    }
}

// Test Clear resets the pool
TEST_F(MemPoolTTest_22, ClearResetsPool_22) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    (void)mem1;
    (void)mem2;
    // After Clear, CurrentAllocs should be 0
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test Untracked returns value
TEST_F(MemPoolTTest_22, UntrackedInitiallyZero_22) {
    EXPECT_EQ(pool.Untracked(), 0u);
}

// Test SetTracked can be called without crash
TEST_F(MemPoolTTest_22, SetTrackedDoesNotCrash_22) {
    pool.SetTracked();
    // Just verify no crash; SetTracked modifies internal tracking state
}

// Test Trace can be called without crash
TEST_F(MemPoolTTest_22, TraceDoesNotCrash_22) {
    pool.Alloc();
    pool.Trace("TestPool");
    pool.Clear();
    // Just verify no crash
}

// Test with a different ITEM_SIZE
TEST(MemPoolTDifferentSize_22, ItemSizeSmall_22) {
    MemPoolT<8> smallPool;
    EXPECT_EQ(smallPool.ItemSize(), 8u);
    void* mem = smallPool.Alloc();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(smallPool.CurrentAllocs(), 1u);
    smallPool.Free(mem);
    EXPECT_EQ(smallPool.CurrentAllocs(), 0u);
}

TEST(MemPoolTDifferentSize_22, ItemSizeLarge_22) {
    MemPoolT<256> largePool;
    EXPECT_EQ(largePool.ItemSize(), 256u);
    void* mem = largePool.Alloc();
    ASSERT_NE(mem, nullptr);
    EXPECT_EQ(largePool.CurrentAllocs(), 1u);
    largePool.Free(mem);
    EXPECT_EQ(largePool.CurrentAllocs(), 0u);
}

// Test many allocations to trigger multiple blocks
TEST_F(MemPoolTTest_22, ManyAllocationsWork_22) {
    const size_t N = 1000;
    std::vector<void*> ptrs;
    ptrs.reserve(N);
    for (size_t i = 0; i < N; ++i) {
        void* mem = pool.Alloc();
        ASSERT_NE(mem, nullptr);
        ptrs.push_back(mem);
    }
    EXPECT_EQ(pool.CurrentAllocs(), N);
    
    for (void* p : ptrs) {
        pool.Free(p);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test freeing in reverse order
TEST_F(MemPoolTTest_22, FreeInReverseOrder_22) {
    const size_t N = 50;
    std::vector<void*> ptrs;
    for (size_t i = 0; i < N; ++i) {
        ptrs.push_back(pool.Alloc());
    }
    EXPECT_EQ(pool.CurrentAllocs(), N);
    
    for (int i = static_cast<int>(N) - 1; i >= 0; --i) {
        pool.Free(ptrs[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test interleaved alloc and free
TEST_F(MemPoolTTest_22, InterleavedAllocAndFree_22) {
    void* a = pool.Alloc();
    void* b = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Free(a);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    void* c = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Free(b);
    pool.Free(c);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}
