// File: ./TestProjects/tinyxml2/tests/MemPoolT_Alloc_tests_21.cpp

#include "gtest/gtest.h"
#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class MemPoolTAllocTest_21 : public ::testing::Test {
protected:
    // Use a small-but-reasonable item size for the template parameter.
    tinyxml2::MemPoolT<8> pool_;
};

TEST_F(MemPoolTAllocTest_21, AllocReturnsNonNullAndIncrementsCounters_21) {
    const size_t prevCurrent = pool_.CurrentAllocs();
    const size_t prevUntracked = pool_.Untracked();

    void* p = nullptr;
    ASSERT_NO_THROW(p = pool_.Alloc());
    ASSERT_NE(p, nullptr);

    EXPECT_EQ(pool_.CurrentAllocs(), prevCurrent + 1u);
    EXPECT_EQ(pool_.Untracked(), prevUntracked + 1u);

    // Clean up (observable behavior: CurrentAllocs should go back down).
    ASSERT_NO_THROW(pool_.Free(p));
    EXPECT_EQ(pool_.CurrentAllocs(), prevCurrent);
}

TEST_F(MemPoolTAllocTest_21, MultipleAllocationsAccumulateCounts_21) {
    const size_t prevCurrent = pool_.CurrentAllocs();
    const size_t prevUntracked = pool_.Untracked();

    constexpr int kAllocs = 5;
    void* ptrs[kAllocs] = {nullptr, nullptr, nullptr, nullptr, nullptr};

    for (int i = 0; i < kAllocs; ++i) {
        ASSERT_NO_THROW(ptrs[i] = pool_.Alloc());
        ASSERT_NE(ptrs[i], nullptr);
    }

    EXPECT_EQ(pool_.CurrentAllocs(), prevCurrent + static_cast<size_t>(kAllocs));
    EXPECT_EQ(pool_.Untracked(), prevUntracked + static_cast<size_t>(kAllocs));

    for (int i = 0; i < kAllocs; ++i) {
        ASSERT_NO_THROW(pool_.Free(ptrs[i]));
    }
    EXPECT_EQ(pool_.CurrentAllocs(), prevCurrent);
}

TEST_F(MemPoolTAllocTest_21, FreeAfterAllocRestoresCurrentAllocs_21) {
    const size_t prevCurrent = pool_.CurrentAllocs();

    void* p = pool_.Alloc();
    ASSERT_NE(p, nullptr);
    ASSERT_EQ(pool_.CurrentAllocs(), prevCurrent + 1u);

    pool_.Free(p);
    EXPECT_EQ(pool_.CurrentAllocs(), prevCurrent);
}

TEST_F(MemPoolTAllocTest_21, AllocWorksAfterClear_21) {
    void* p1 = pool_.Alloc();
    ASSERT_NE(p1, nullptr);
    pool_.Free(p1);

    ASSERT_NO_THROW(pool_.Clear());

    void* p2 = nullptr;
    ASSERT_NO_THROW(p2 = pool_.Alloc());
    ASSERT_NE(p2, nullptr);

    pool_.Free(p2);
}

}  // namespace
