// TEST_ID: 22
// File: ./TestProjects/tinyxml2/tests/test_mempool_free_22.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

namespace {

class MemPoolTFreeTest_22 : public ::testing::Test {
protected:
    // Use a small, non-zero item size. We never assume alignment beyond what Alloc provides.
    tinyxml2::MemPoolT<16> pool;
};

TEST_F(MemPoolTFreeTest_22, FreeNullptrDoesNotChangeCurrentAllocs_22) {
    const size_t before = pool.CurrentAllocs();
    pool.Free(nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), before);
}

TEST_F(MemPoolTFreeTest_22, AllocThenFreeRestoresCurrentAllocs_22) {
    const size_t before = pool.CurrentAllocs();

    void* p = pool.Alloc();
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), before + 1);

    pool.Free(p);
    EXPECT_EQ(pool.CurrentAllocs(), before);
}

TEST_F(MemPoolTFreeTest_22, MultipleAllocsAndFreesUpdateCurrentAllocs_22) {
    const size_t before = pool.CurrentAllocs();

    void* a = pool.Alloc();
    void* b = pool.Alloc();
    void* c = pool.Alloc();
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), before + 3);

    pool.Free(b);
    EXPECT_EQ(pool.CurrentAllocs(), before + 2);

    pool.Free(a);
    EXPECT_EQ(pool.CurrentAllocs(), before + 1);

    pool.Free(c);
    EXPECT_EQ(pool.CurrentAllocs(), before);
}

TEST_F(MemPoolTFreeTest_22, FreeNullptrAfterAllocationsIsNoOp_22) {
    void* p = pool.Alloc();
    ASSERT_NE(p, nullptr);

    const size_t afterAlloc = pool.CurrentAllocs();
    pool.Free(nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), afterAlloc);

    pool.Free(p);
}

TEST_F(MemPoolTFreeTest_22, FreeThenAllocMayReuseFreedPointerAndCountsAreConsistent_22) {
    const size_t before = pool.CurrentAllocs();

    void* p = pool.Alloc();
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), before + 1);

    pool.Free(p);
    EXPECT_EQ(pool.CurrentAllocs(), before);

    void* q = pool.Alloc();
    ASSERT_NE(q, nullptr);
    EXPECT_EQ(pool.CurrentAllocs(), before + 1);

    // MemPool implementations commonly reuse freed nodes; if this pool does, this should hold.
    // If the implementation changes to not reuse immediately, this assertion may need relaxation.
    EXPECT_EQ(q, p);

    pool.Free(q);
    EXPECT_EQ(pool.CurrentAllocs(), before);
}

}  // namespace
