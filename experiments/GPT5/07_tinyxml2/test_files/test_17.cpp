// TEST_ID: 17
// File: mempoolt_destructor_tests_17.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace {

class MemPoolTTest_17 : public ::testing::Test {
protected:
    // Pick a small but non-trivial item size.
    static constexpr size_t kItemSize = 32;
    using Pool = tinyxml2::MemPoolT<kItemSize>;
};

TEST_F(MemPoolTTest_17, ItemSizeMatchesTemplateParameter_17) {
    Pool pool;
    EXPECT_EQ(pool.ItemSize(), kItemSize);
}

TEST_F(MemPoolTTest_17, AllocIncreasesCurrentAllocs_17) {
    Pool pool;

    const size_t before = pool.CurrentAllocs();
    void* p = pool.Alloc();

    // Observable behavior only: if allocation succeeds, CurrentAllocs should increase.
    // (If Alloc can return nullptr in some configurations, this still remains valid.)
    if (p) {
        EXPECT_EQ(pool.CurrentAllocs(), before + 1);
        pool.Free(p);
        EXPECT_EQ(pool.CurrentAllocs(), before);
    } else {
        // Allocation failed: CurrentAllocs should not spuriously increase.
        EXPECT_EQ(pool.CurrentAllocs(), before);
    }
}

TEST_F(MemPoolTTest_17, FreeNullptrDoesNotIncreaseAllocs_17) {
    Pool pool;

    const size_t before = pool.CurrentAllocs();
    // Many allocators treat Free(nullptr) as a no-op; this test only checks it is safe
    // and does not increase counts.
    pool.Free(nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), before);
}

TEST_F(MemPoolTTest_17, ClearResetsCurrentAllocsToZeroAfterAllocations_17) {
    Pool pool;

    void* a = pool.Alloc();
    void* b = pool.Alloc();
    (void)a;
    (void)b;

    // Only assert the observable contract via the public counter.
    EXPECT_GE(pool.CurrentAllocs(), static_cast<size_t>(0));

    pool.Clear();
    EXPECT_EQ(pool.CurrentAllocs(), 0u);
}

TEST_F(MemPoolTTest_17, DestructorAfterNoUseDoesNotCrash_17) {
    // Test is primarily that destruction is safe.
    auto* pool = new Pool();
    delete pool;
    SUCCEED();
}

TEST_F(MemPoolTTest_17, DestructorAfterClearDoesNotCrash_17) {
    auto* pool = new Pool();
    pool->Clear();
    delete pool;
    SUCCEED();
}

TEST_F(MemPoolTTest_17, DestructorAfterAllocationsAndFreesDoesNotCrash_17) {
    auto* pool = new Pool();

    void* p1 = pool->Alloc();
    void* p2 = pool->Alloc();

    if (p1) pool->Free(p1);
    if (p2) pool->Free(p2);

    delete pool;
    SUCCEED();
}

TEST_F(MemPoolTTest_17, DestructorCleansUpOutstandingAllocationsWithoutCrash_17) {
    // This is the closest black-box observable check for "~MemPoolT calls Clear()":
    // we allocate and intentionally do not Free() all pointers; destruction should be safe.
    auto* pool = new Pool();

    void* p1 = pool->Alloc();
    void* p2 = pool->Alloc();
    void* p3 = pool->Alloc();

    (void)p1;
    (void)p2;
    (void)p3;

    delete pool;
    SUCCEED();
}

}  // namespace
