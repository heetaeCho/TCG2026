// TEST_ID: 25
#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace {

class MemPoolTUntrackedTest_25 : public ::testing::Test {
protected:
    // Use a small, typical item size.
    tinyxml2::MemPoolT<16> pool_;
};

TEST_F(MemPoolTUntrackedTest_25, DefaultConstructor_UntrackedIsZero_25) {
    // Observable behavior: Untracked() returns a count; after default construction it should be 0.
    EXPECT_EQ(pool_.Untracked(), static_cast<size_t>(0));
}

TEST_F(MemPoolTUntrackedTest_25, Untracked_IsStableAcrossRepeatedCalls_25) {
    const size_t first = pool_.Untracked();
    const size_t second = pool_.Untracked();
    EXPECT_EQ(first, second);
}

TEST_F(MemPoolTUntrackedTest_25, SetTracked_DoesNotBreakUntrackedQuery_25) {
    // We don't infer what SetTracked() should do to the count; we only verify the call is safe
    // and Untracked() remains a valid, stable query afterward.
    const size_t before = pool_.Untracked();

    ASSERT_NO_FATAL_FAILURE(pool_.SetTracked());

    const size_t after1 = pool_.Untracked();
    const size_t after2 = pool_.Untracked();

    EXPECT_EQ(after1, after2);
    // Not asserting after1 == before, because that would infer internal semantics.
    (void)before;
}

TEST_F(MemPoolTUntrackedTest_25, AllocAndFree_NormalUsage_DoesNotBreakUntrackedQuery_25) {
    // Normal operation: allocate then free if allocation succeeds.
    void* mem = nullptr;
    ASSERT_NO_FATAL_FAILURE(mem = pool_.Alloc());

    // Regardless of whether allocation returns nullptr in some edge condition,
    // Untracked() must remain callable and stable.
    const size_t mid1 = pool_.Untracked();
    const size_t mid2 = pool_.Untracked();
    EXPECT_EQ(mid1, mid2);

    if (mem) {
        ASSERT_NO_FATAL_FAILURE(pool_.Free(mem));
    }

    const size_t after1 = pool_.Untracked();
    const size_t after2 = pool_.Untracked();
    EXPECT_EQ(after1, after2);
}

TEST_F(MemPoolTUntrackedTest_25, Clear_Boundary_DoesNotBreakUntrackedQuery_25) {
    // Boundary-style check: after Clear(), the query should still be valid and stable.
    ASSERT_NO_FATAL_FAILURE(pool_.Clear());

    const size_t v1 = pool_.Untracked();
    const size_t v2 = pool_.Untracked();
    EXPECT_EQ(v1, v2);
}

}  // namespace
