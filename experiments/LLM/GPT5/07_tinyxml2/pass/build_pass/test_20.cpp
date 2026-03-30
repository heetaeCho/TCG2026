// File: ./TestProjects/tinyxml2/tests/MemPoolT_CurrentAllocs_test_20.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

namespace {

using Pool20 = tinyxml2::MemPoolT<16>;

class MemPoolTCurrentAllocsTest_20 : public ::testing::Test {
protected:
    Pool20 pool_;
};

TEST_F(MemPoolTCurrentAllocsTest_20, DefaultConstructedStartsAtZero_20) {
    EXPECT_EQ(pool_.CurrentAllocs(), static_cast<size_t>(0));
}

TEST_F(MemPoolTCurrentAllocsTest_20, AllocDoesNotDecreaseCurrentAllocs_20) {
    const size_t before = pool_.CurrentAllocs();

    void* p = pool_.Alloc();
    ASSERT_NE(p, nullptr);

    const size_t after = pool_.CurrentAllocs();
    EXPECT_GE(after, before);

    pool_.Free(p);
}

TEST_F(MemPoolTCurrentAllocsTest_20, FreeDoesNotIncreaseCurrentAllocs_20) {
    void* p = pool_.Alloc();
    ASSERT_NE(p, nullptr);

    const size_t beforeFree = pool_.CurrentAllocs();

    pool_.Free(p);

    const size_t afterFree = pool_.CurrentAllocs();
    EXPECT_LE(afterFree, beforeFree);
}

TEST_F(MemPoolTCurrentAllocsTest_20, MultipleAllocsAndFreesBehaveMonotonically_20) {
    const size_t start = pool_.CurrentAllocs();

    void* p1 = pool_.Alloc();
    ASSERT_NE(p1, nullptr);
    const size_t after1 = pool_.CurrentAllocs();
    EXPECT_GE(after1, start);

    void* p2 = pool_.Alloc();
    ASSERT_NE(p2, nullptr);
    const size_t after2 = pool_.CurrentAllocs();
    EXPECT_GE(after2, after1);

    pool_.Free(p2);
    const size_t afterFree2 = pool_.CurrentAllocs();
    EXPECT_LE(afterFree2, after2);

    pool_.Free(p1);
    const size_t afterFree1 = pool_.CurrentAllocs();
    EXPECT_LE(afterFree1, afterFree2);
}

TEST_F(MemPoolTCurrentAllocsTest_20, ClearResetsCurrentAllocsToZero_20) {
    void* p1 = pool_.Alloc();
    ASSERT_NE(p1, nullptr);
    void* p2 = pool_.Alloc();
    ASSERT_NE(p2, nullptr);

    // Clear() is part of the public interface; we only validate observable state via CurrentAllocs().
    pool_.Clear();

    EXPECT_EQ(pool_.CurrentAllocs(), static_cast<size_t>(0));
}

}  // namespace
