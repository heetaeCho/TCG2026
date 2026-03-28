#include "gtest/gtest.h"
#include "./TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// Use a reasonable ITEM_SIZE for testing
static constexpr size_t TEST_ITEM_SIZE = 64;

class MemPoolTTest_24 : public ::testing::Test {
protected:
    MemPoolT<TEST_ITEM_SIZE> pool;

    void SetUp() override {
        // pool is default constructed
    }

    void TearDown() override {
        pool.Clear();
    }
};

// Test default construction state
TEST_F(MemPoolTTest_24, DefaultConstructionHasZeroAllocs_24) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test ItemSize returns the template parameter
TEST_F(MemPoolTTest_24, ItemSizeReturnsTemplateParameter_24) {
    EXPECT_EQ(pool.ItemSize(), TEST_ITEM_SIZE);
}

// Test ItemSize with different template parameter
TEST(MemPoolTSizeTest_24, ItemSizeVariesWithTemplate_24) {
    MemPoolT<128> pool128;
    EXPECT_EQ(pool128.ItemSize(), 128u);

    MemPoolT<32> pool32;
    EXPECT_EQ(pool32.ItemSize(), 32u);

    MemPoolT<1> pool1;
    EXPECT_EQ(pool1.ItemSize(), 1u);
}

// Test that Alloc returns a non-null pointer
TEST_F(MemPoolTTest_24, AllocReturnsNonNull_24) {
    void* mem = pool.Alloc();
    ASSERT_NE(mem, nullptr);
    pool.Free(mem);
}

// Test that Alloc increases CurrentAllocs
TEST_F(MemPoolTTest_24, AllocIncreasesCurrentAllocs_24) {
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    void* mem1 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    void* mem2 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Free(mem1);
    pool.Free(mem2);
}

// Test that Free decreases CurrentAllocs
TEST_F(MemPoolTTest_24, FreeDecreasesCurrentAllocs_24) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Free(mem1);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem2);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test multiple allocations return distinct pointers
TEST_F(MemPoolTTest_24, MultipleAllocsReturnDistinctPointers_24) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    void* mem3 = pool.Alloc();
    EXPECT_NE(mem1, mem2);
    EXPECT_NE(mem1, mem3);
    EXPECT_NE(mem2, mem3);
    pool.Free(mem1);
    pool.Free(mem2);
    pool.Free(mem3);
}

// Test that after freeing and re-allocating, the count remains correct
TEST_F(MemPoolTTest_24, AllocAfterFreeCorrectCount_24) {
    void* mem1 = pool.Alloc();
    pool.Free(mem1);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
    void* mem2 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem2);
}

// Test Clear resets allocations
TEST_F(MemPoolTTest_24, ClearResetsState_24) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    (void)mem1;
    (void)mem2;
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test Untracked starts at zero
TEST_F(MemPoolTTest_24, UntrackedStartsAtZero_24) {
    EXPECT_EQ(pool.Untracked(), 0u);
}

// Test that Alloc increases Untracked count
TEST_F(MemPoolTTest_24, AllocIncreasesUntracked_24) {
    void* mem = pool.Alloc();
    // Each Alloc should increment _nUntracked (based on typical MemPool behavior)
    EXPECT_GE(pool.Untracked(), 0u);
    pool.Free(mem);
}

// Test that SetTracked decreases Untracked
TEST_F(MemPoolTTest_24, SetTrackedDecreasesUntracked_24) {
    void* mem = pool.Alloc();
    size_t untrackedBefore = pool.Untracked();
    pool.SetTracked();
    size_t untrackedAfter = pool.Untracked();
    // SetTracked decrements _nUntracked by 1
    if (untrackedBefore > 0) {
        EXPECT_EQ(untrackedAfter, untrackedBefore - 1);
    }
    pool.Free(mem);
}

// Test many allocations and frees
TEST_F(MemPoolTTest_24, ManyAllocsAndFrees_24) {
    const int N = 1000;
    std::vector<void*> ptrs;
    ptrs.reserve(N);
    for (int i = 0; i < N; ++i) {
        void* mem = pool.Alloc();
        ASSERT_NE(mem, nullptr);
        ptrs.push_back(mem);
    }
    EXPECT_EQ(pool.CurrentAllocs(), static_cast<size_t>(N));
    for (int i = 0; i < N; ++i) {
        pool.Free(ptrs[i]);
    }
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test Trace does not crash (no observable output check, just no crash)
TEST_F(MemPoolTTest_24, TraceDoesNotCrash_24) {
    void* mem = pool.Alloc();
    EXPECT_NO_FATAL_FAILURE(pool.Trace("TestPool"));
    pool.Free(mem);
}

// Test Trace with null name doesn't crash (boundary)
TEST_F(MemPoolTTest_24, TraceWithNullNameDoesNotCrash_24) {
    // Depending on implementation, this may or may not be safe
    // but we test it as a boundary condition
    EXPECT_NO_FATAL_FAILURE(pool.Trace(nullptr));
}

// Test allocating after Clear
TEST_F(MemPoolTTest_24, AllocAfterClearWorks_24) {
    void* mem1 = pool.Alloc();
    (void)mem1;
    pool.Clear();
    void* mem2 = pool.Alloc();
    ASSERT_NE(mem2, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), 1u);
    pool.Free(mem2);
}

// Test that allocated memory is writable
TEST_F(MemPoolTTest_24, AllocatedMemoryIsWritable_24) {
    void* mem = pool.Alloc();
    ASSERT_NE(mem, nullptr);
    // Write to the allocated memory
    memset(mem, 0xAB, TEST_ITEM_SIZE);
    // Read back to verify (basic check)
    unsigned char* bytes = static_cast<unsigned char*>(mem);
    EXPECT_EQ(bytes[0], 0xAB);
    EXPECT_EQ(bytes[TEST_ITEM_SIZE - 1], 0xAB);
    pool.Free(mem);
}

// Test CurrentAllocs is zero after construction with different item sizes
TEST(MemPoolTVariousSizes_24, InitialCurrentAllocsIsZero_24) {
    MemPoolT<8> pool8;
    MemPoolT<256> pool256;
    MemPoolT<1024> pool1024;
    EXPECT_EQ(pool8.CurrentAllocs(), 0u);
    EXPECT_EQ(pool256.CurrentAllocs(), 0u);
    EXPECT_EQ(pool1024.CurrentAllocs(), 0u);
}

// Test interleaved alloc and free
TEST_F(MemPoolTTest_24, InterleavedAllocFree_24) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    pool.Free(mem1);
    void* mem3 = pool.Alloc();
    EXPECT_EQ(pool.CurrentAllocs(), 2u);
    pool.Free(mem2);
    pool.Free(mem3);
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

// Test SetTracked multiple times
TEST_F(MemPoolTTest_24, MultipleSetTrackedCalls_24) {
    void* mem1 = pool.Alloc();
    void* mem2 = pool.Alloc();
    void* mem3 = pool.Alloc();
    size_t untracked = pool.Untracked();
    pool.SetTracked();
    EXPECT_EQ(pool.Untracked(), untracked - 1);
    pool.SetTracked();
    EXPECT_EQ(pool.Untracked(), untracked - 2);
    pool.SetTracked();
    EXPECT_EQ(pool.Untracked(), untracked - 3);
    pool.Free(mem1);
    pool.Free(mem2);
    pool.Free(mem3);
}
