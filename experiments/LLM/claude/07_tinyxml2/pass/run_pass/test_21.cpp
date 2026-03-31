#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Use a reasonable ITEM_SIZE for testing
static constexpr size_t TEST_ITEM_SIZE = 32;

class MemPoolTTest_21 : public ::testing::Test {
protected:
    MemPoolT<TEST_ITEM_SIZE> pool;
};

// Test that a freshly constructed pool has zero current allocations
TEST_F(MemPoolTTest_21, InitialCurrentAllocsIsZero_21) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that ItemSize returns the template parameter
TEST_F(MemPoolTTest_21, ItemSizeReturnsCorrectSize_21) {
    EXPECT_EQ(pool.ItemSize(), TEST_ITEM_SIZE);
}

// Test that Alloc returns a non-null pointer
TEST_F(MemPoolTTest_21, AllocReturnsNonNull_21) {
    void* ptr = pool.Alloc();
    ASSERT_NE(ptr, nullptr);
    pool.Free(ptr);
}

// Test that after one Alloc, CurrentAllocs is 1
TEST_F(MemPoolTTest_21, SingleAllocIncreasesCurrentAllocs_21) {
    void* ptr = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr);
}

// Test that after Alloc and Free, CurrentAllocs returns to 0
TEST_F(MemPoolTTest_21, FreeDecreasesCurrentAllocs_21) {
    void* ptr = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test multiple allocations increase CurrentAllocs correctly
TEST_F(MemPoolTTest_21, MultipleAllocsIncreaseCurrentAllocs_21) {
    const size_t count = 10;
    void* ptrs[count];
    for (size_t i = 0; i < count; ++i) {
        ptrs[i] = pool.Alloc();
        ASSERT_NE(ptrs[i], nullptr);
    }
    EXPECT_EQ(pool.CurrentAllocs(), count);
    for (size_t i = 0; i < count; ++i) {
        pool.Free(ptrs[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that each Alloc returns a unique pointer
TEST_F(MemPoolTTest_21, AllocReturnsUniquePointers_21) {
    void* ptr1 = pool.Alloc();
    void* ptr2 = pool.Alloc();
    EXPECT_NE(ptr1, ptr2);
    pool.Free(ptr1);
    pool.Free(ptr2);
}

// Test that a freed pointer can be reused by subsequent Alloc
TEST_F(MemPoolTTest_21, FreedMemoryCanBeReused_21) {
    void* ptr1 = pool.Alloc();
    pool.Free(ptr1);
    void* ptr2 = pool.Alloc();
    // The freed item should be reused (returned again)
    EXPECT_EQ(ptr1, ptr2);
    pool.Free(ptr2);
}

// Test that Clear resets the pool
TEST_F(MemPoolTTest_21, ClearResetsPool_21) {
    void* ptr1 = pool.Alloc();
    void* ptr2 = pool.Alloc();
    (void)ptr1;
    (void)ptr2;
    // After clear, CurrentAllocs should be 0
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that allocating many items (more than one block) works
TEST_F(MemPoolTTest_21, AllocAcrossMultipleBlocks_21) {
    const size_t count = 1000;
    void* ptrs[count];
    for (size_t i = 0; i < count; ++i) {
        ptrs[i] = pool.Alloc();
        ASSERT_NE(ptrs[i], nullptr);
    }
    EXPECT_EQ(pool.CurrentAllocs(), count);
    for (size_t i = 0; i < count; ++i) {
        pool.Free(ptrs[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test Untracked count increases with allocations
TEST_F(MemPoolTTest_21, UntrackedIncreasesWithAlloc_21) {
    size_t initialUntracked = pool.Untracked();
    void* ptr = pool.Alloc();
    EXPECT_EQ(pool.Untracked(), initialUntracked + 1);
    pool.Free(ptr);
}

// Test SetTracked resets untracked count
TEST_F(MemPoolTTest_21, SetTrackedResetsUntracked_21) {
    void* ptr = pool.Alloc();
    EXPECT_GT(pool.Untracked(), 0u);
    pool.SetTracked();
    EXPECT_EQ(pool.Untracked(), 0u);
    pool.Free(ptr);
}

// Test with different ITEM_SIZE template parameter
TEST(MemPoolTDifferentSize_21, ItemSizeMatchesTemplateParam_21) {
    MemPoolT<64> pool64;
    EXPECT_EQ(pool64.ItemSize(), 64u);

    MemPoolT<128> pool128;
    EXPECT_EQ(pool128.ItemSize(), 128u);

    MemPoolT<8> pool8;
    EXPECT_EQ(pool8.ItemSize(), 8u);
}

// Test alternating alloc and free
TEST_F(MemPoolTTest_21, AlternatingAllocFree_21) {
    for (int i = 0; i < 100; ++i) {
        void* ptr = pool.Alloc();
        ASSERT_NE(ptr, nullptr);
        EXPECT_EQ(pool.CurrentAllocs(), 1u);
        pool.Free(ptr);
        EXPECT_EQ(pool.CurrentAllocs(), 0u);
    }
}

// Test that Trace doesn't crash (smoke test)
TEST_F(MemPoolTTest_21, TraceDoesNotCrash_21) {
    void* ptr = pool.Alloc();
    EXPECT_NO_FATAL_FAILURE(pool.Trace("TestPool"));
    pool.Free(ptr);
}

// Test alloc-free-alloc pattern with multiple pointers
TEST_F(MemPoolTTest_21, PartialFreeAndRealloc_21) {
    void* ptr1 = pool.Alloc();
    void* ptr2 = pool.Alloc();
    void* ptr3 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 3u);

    pool.Free(ptr2);
    EXPECT_EQ(pool.CurrentAllocs(), 2u);

    // Allocate again; should reuse ptr2's memory
    void* ptr4 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 3u);
    EXPECT_EQ(ptr4, ptr2);

    pool.Free(ptr1);
    pool.Free(ptr3);
    pool.Free(ptr4);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test destructor after allocations (no crash / leak detection)
TEST(MemPoolTDestructor_21, DestructorAfterAllocs_21) {
    {
        MemPoolT<TEST_ITEM_SIZE> pool;
        pool.Alloc();
        pool.Alloc();
        pool.Alloc();
        // Pool goes out of scope - destructor should handle cleanup
    }
    SUCCEED();
}

// Test Clear followed by new allocations
TEST_F(MemPoolTTest_21, ClearThenReallocate_21) {
    void* ptr1 = pool.Alloc();
    void* ptr2 = pool.Alloc();
    (void)ptr1;
    (void)ptr2;
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);

    // Should be able to allocate again after clear
    void* ptr3 = pool.Alloc();
    ASSERT_NE(ptr3, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr3);
}
