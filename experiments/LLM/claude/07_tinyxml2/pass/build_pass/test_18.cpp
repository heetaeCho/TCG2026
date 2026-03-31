#include <gtest/gtest.h>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Use a reasonable ITEM_SIZE for testing
static constexpr size_t TEST_ITEM_SIZE = 32;

class MemPoolTTest_18 : public ::testing::Test {
protected:
    MemPoolT<TEST_ITEM_SIZE> pool;
};

// Test that a freshly constructed pool has zero current allocations
TEST_F(MemPoolTTest_18, InitialCurrentAllocsIsZero_18) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that ItemSize returns the template parameter
TEST_F(MemPoolTTest_18, ItemSizeReturnsCorrectSize_18) {
    EXPECT_EQ(pool.ItemSize(), TEST_ITEM_SIZE);
}

// Test that Alloc returns a non-null pointer
TEST_F(MemPoolTTest_18, AllocReturnsNonNull_18) {
    void* ptr = pool.Alloc();
    ASSERT_NE(ptr, nullptr);
    pool.Free(ptr);
}

// Test that after one Alloc, CurrentAllocs is 1
TEST_F(MemPoolTTest_18, AllocIncreasesCurrentAllocs_18) {
    void* ptr = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr);
}

// Test that after Alloc and Free, CurrentAllocs returns to 0
TEST_F(MemPoolTTest_18, FreeDecreasesCurrentAllocs_18) {
    void* ptr = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test multiple allocations increase CurrentAllocs correctly
TEST_F(MemPoolTTest_18, MultipleAllocsIncreaseCurrentAllocs_18) {
    void* ptrs[10];
    for (int i = 0; i < 10; ++i) {
        ptrs[i] = pool.Alloc();
        EXPECT_NE(ptrs[i], nullptr);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 10u);
    for (int i = 0; i < 10; ++i) {
        pool.Free(ptrs[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that Clear resets allocations to zero
TEST_F(MemPoolTTest_18, ClearResetsCurrentAllocsToZero_18) {
    void* ptr1 = pool.Alloc();
    void* ptr2 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test Clear on an empty pool does not cause issues
TEST_F(MemPoolTTest_18, ClearOnEmptyPoolIsNoOp_18) {
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that calling Clear multiple times is safe
TEST_F(MemPoolTTest_18, MultipleClearsAreSafe_18) {
    void* ptr = pool.Alloc();
    pool.Clear();
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that Alloc works after Clear
TEST_F(MemPoolTTest_18, AllocAfterClearWorks_18) {
    void* ptr1 = pool.Alloc();
    pool.Clear();
    void* ptr2 = pool.Alloc();
    ASSERT_NE(ptr2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr2);
}

// Test that each Alloc returns a distinct pointer
TEST_F(MemPoolTTest_18, AllocReturnsDistinctPointers_18) {
    void* ptr1 = pool.Alloc();
    void* ptr2 = pool.Alloc();
    EXPECT_NE(ptr1, ptr2);
    pool.Free(ptr1);
    pool.Free(ptr2);
}

// Test Untracked initially returns zero
TEST_F(MemPoolTTest_18, InitialUntrackedIsZero_18) {
    EXPECT_EQ(pool.Untracked(), 0u);
}

// Test SetTracked can be called (no crash)
TEST_F(MemPoolTTest_18, SetTrackedDoesNotCrash_18) {
    pool.SetTracked();
    // If SetTracked affects Untracked count, we can observe it
    // But mainly we verify it doesn't crash
}

// Test with a different ITEM_SIZE
TEST(MemPoolTDifferentSize_18, ItemSizeMatchesTemplateParam_18) {
    MemPoolT<64> pool64;
    EXPECT_EQ(pool64.ItemSize(), 64u);

    MemPoolT<128> pool128;
    EXPECT_EQ(pool128.ItemSize(), 128u);

    MemPoolT<8> pool8;
    EXPECT_EQ(pool8.ItemSize(), 8u);
}

// Test allocating and freeing in reverse order
TEST_F(MemPoolTTest_18, AllocAndFreeInReverseOrder_18) {
    void* ptrs[5];
    for (int i = 0; i < 5; ++i) {
        ptrs[i] = pool.Alloc();
    }
    EXPECT_EQ(pool.CurrentAllocs(), 5u);
    for (int i = 4; i >= 0; --i) {
        pool.Free(ptrs[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test that freed memory can be reused (alloc after free)
TEST_F(MemPoolTTest_18, FreedMemoryCanBeReused_18) {
    void* ptr1 = pool.Alloc();
    pool.Free(ptr1);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    void* ptr2 = pool.Alloc();
    EXPECT_NE(ptr2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr2);
}

// Test large number of allocations
TEST_F(MemPoolTTest_18, LargeNumberOfAllocations_18) {
    const int N = 1000;
    std::vector<void*> ptrs(N);
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

// Test Trace does not crash (basic smoke test)
TEST_F(MemPoolTTest_18, TraceDoesNotCrash_18) {
    pool.Alloc();
    pool.Trace("TestPool");
    pool.Clear();
}

// Test destructor cleans up properly (no leak or crash)
TEST(MemPoolTDestructor_18, DestructorAfterAllocDoesNotCrash_18) {
    {
        MemPoolT<TEST_ITEM_SIZE> localPool;
        void* ptr1 = localPool.Alloc();
        void* ptr2 = localPool.Alloc();
        // Destructor called here without explicit Free
    }
    // If we get here without crash, destructor handled cleanup
    SUCCEED();
}

// Test interleaved alloc and free
TEST_F(MemPoolTTest_18, InterleavedAllocAndFree_18) {
    void* p1 = pool.Alloc();
    void* p2 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Free(p1);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    void* p3 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Free(p2);
    pool.Free(p3);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}
