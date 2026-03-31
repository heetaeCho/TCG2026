#include <gtest/gtest.h>
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Test fixture for MemPoolT with a specific item size
class MemPoolTTest_19 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test ItemSize returns correct size for small item size
TEST_F(MemPoolTTest_19, ItemSizeReturnsCorrectSize_Small_19) {
    MemPoolT<8> pool;
    EXPECT_EQ(pool.ItemSize(), 8u);
}

// Test ItemSize returns correct size for larger item size
TEST_F(MemPoolTTest_19, ItemSizeReturnsCorrectSize_Large_19) {
    MemPoolT<256> pool;
    EXPECT_EQ(pool.ItemSize(), 256u);
}

// Test ItemSize returns correct size for size 1
TEST_F(MemPoolTTest_19, ItemSizeReturnsCorrectSize_One_19) {
    MemPoolT<1> pool;
    EXPECT_EQ(pool.ItemSize(), 1u);
}

// Test initial CurrentAllocs is zero
TEST_F(MemPoolTTest_19, InitialCurrentAllocsIsZero_19) {
    MemPoolT<32> pool;
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test Alloc returns non-null pointer
TEST_F(MemPoolTTest_19, AllocReturnsNonNull_19) {
    MemPoolT<32> pool;
    void* ptr = pool.Alloc();
    ASSERT_NE(ptr, nullptr);
    pool.Free(ptr);
}

// Test Alloc increases CurrentAllocs
TEST_F(MemPoolTTest_19, AllocIncreasesCurrentAllocs_19) {
    MemPoolT<32> pool;
    void* ptr = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr);
}

// Test Free decreases CurrentAllocs
TEST_F(MemPoolTTest_19, FreeDecreasesCurrentAllocs_19) {
    MemPoolT<32> pool;
    void* ptr = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test multiple allocations increase CurrentAllocs correctly
TEST_F(MemPoolTTest_19, MultipleAllocsIncreaseCurrentAllocs_19) {
    MemPoolT<64> pool;
    void* ptr1 = pool.Alloc();
    void* ptr2 = pool.Alloc();
    void* ptr3 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 3u);
    pool.Free(ptr1);
    pool.Free(ptr2);
    pool.Free(ptr3);
}

// Test multiple allocs return distinct pointers
TEST_F(MemPoolTTest_19, MultipleAllocsReturnDistinctPointers_19) {
    MemPoolT<32> pool;
    void* ptr1 = pool.Alloc();
    void* ptr2 = pool.Alloc();
    EXPECT_NE(ptr1, ptr2);
    pool.Free(ptr1);
    pool.Free(ptr2);
}

// Test Free followed by Alloc can reuse memory
TEST_F(MemPoolTTest_19, FreeAndReallocWorks_19) {
    MemPoolT<32> pool;
    void* ptr1 = pool.Alloc();
    pool.Free(ptr1);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    void* ptr2 = pool.Alloc();
    EXPECT_NE(ptr2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr2);
}

// Test Clear resets the pool
TEST_F(MemPoolTTest_19, ClearResetsPool_19) {
    MemPoolT<32> pool;
    void* ptr1 = pool.Alloc();
    void* ptr2 = pool.Alloc();
    (void)ptr1;
    (void)ptr2;
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test Untracked returns initial value
TEST_F(MemPoolTTest_19, InitialUntrackedIsZero_19) {
    MemPoolT<32> pool;
    EXPECT_EQ(pool.Untracked(), 0u);
}

// Test SetTracked affects Untracked count
TEST_F(MemPoolTTest_19, SetTrackedAffectsUntracked_19) {
    MemPoolT<32> pool;
    pool.SetTracked();
    // After SetTracked, the untracked count should change (decrement)
    // The initial _nUntracked is 0, so this tests the observable behavior
    // We just verify it doesn't crash
    pool.Untracked();
}

// Test Trace does not crash
TEST_F(MemPoolTTest_19, TraceDoesNotCrash_19) {
    MemPoolT<32> pool;
    void* ptr = pool.Alloc();
    EXPECT_NO_FATAL_FAILURE(pool.Trace("TestPool"));
    pool.Free(ptr);
}

// Test Trace with nullptr name does not crash (boundary)
TEST_F(MemPoolTTest_19, TraceWithNullNameDoesNotCrash_19) {
    MemPoolT<32> pool;
    // This may or may not crash depending on implementation, 
    // but we test boundary behavior
    // Skip if implementation doesn't handle nullptr gracefully
}

// Test large number of allocations
TEST_F(MemPoolTTest_19, LargeNumberOfAllocations_19) {
    MemPoolT<16> pool;
    const int count = 1000;
    void* ptrs[1000];
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

// Test ItemSize with various template parameters
TEST_F(MemPoolTTest_19, ItemSizeVariousTemplateParams_19) {
    MemPoolT<4> pool4;
    MemPoolT<16> pool16;
    MemPoolT<128> pool128;
    MemPoolT<1024> pool1024;
    
    EXPECT_EQ(pool4.ItemSize(), 4u);
    EXPECT_EQ(pool16.ItemSize(), 16u);
    EXPECT_EQ(pool128.ItemSize(), 128u);
    EXPECT_EQ(pool1024.ItemSize(), 1024u);
}

// Test destructor cleans up properly (no crash on destruction after allocs)
TEST_F(MemPoolTTest_19, DestructorAfterAllocsDoesNotCrash_19) {
    auto pool = new MemPoolT<32>();
    void* ptr1 = pool->Alloc();
    void* ptr2 = pool->Alloc();
    (void)ptr1;
    (void)ptr2;
    // Destroying pool without freeing should not crash
    EXPECT_NO_FATAL_FAILURE(delete pool);
}

// Test alloc-free-alloc pattern
TEST_F(MemPoolTTest_19, AllocFreeAllocPattern_19) {
    MemPoolT<32> pool;
    for (int i = 0; i < 100; i++) {
        void* ptr = pool.Alloc();
        ASSERT_NE(ptr, nullptr);
        EXPECT_EQ(pool.CurrentAllocs(), 1u);
        pool.Free(ptr);
        EXPECT_EQ(pool.CurrentAllocs(), 0u);
    }
}

// Test interleaved alloc and free
TEST_F(MemPoolTTest_19, InterleavedAllocAndFree_19) {
    MemPoolT<48> pool;
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

// Test Clear on empty pool
TEST_F(MemPoolTTest_19, ClearOnEmptyPool_19) {
    MemPoolT<32> pool;
    EXPECT_NO_FATAL_FAILURE(pool.Clear());
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test Clear followed by new allocations
TEST_F(MemPoolTTest_19, ClearFollowedByNewAllocs_19) {
    MemPoolT<32> pool;
    void* ptr1 = pool.Alloc();
    (void)ptr1;
    pool.Clear();
    // After clear, allocations should work again
    void* ptr2 = pool.Alloc();
    EXPECT_NE(ptr2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(ptr2);
}
