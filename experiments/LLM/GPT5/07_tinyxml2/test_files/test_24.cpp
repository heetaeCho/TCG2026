// File: ./TestProjects/tinyxml2/tests/MemPoolT_SetTracked_test_24.cpp

#include <gtest/gtest.h>

#include <limits>
#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class MemPoolT_SetTrackedTest_24 : public ::testing::Test {
protected:
    // ITEM_SIZE can be any valid size_t; pick a small one.
    tinyxml2::MemPoolT<8> pool;
};

TEST_F(MemPoolT_SetTrackedTest_24, SetTrackedDecrementsUntrackedByOne_24) {
    const size_t before = pool.Untracked();

    pool.SetTracked();

    const size_t after = pool.Untracked();
    EXPECT_EQ(after, static_cast<size_t>(before - 1));
}

TEST_F(MemPoolT_SetTrackedTest_24, SetTrackedMultipleCallsDecrementEachTime_24) {
    const size_t before = pool.Untracked();

    pool.SetTracked();
    pool.SetTracked();
    pool.SetTracked();

    const size_t after = pool.Untracked();
    EXPECT_EQ(after, static_cast<size_t>(before - 3));
}

TEST_F(MemPoolT_SetTrackedTest_24, SetTrackedFromZeroWrapsToMaxSizeT_24) {
    // Constructor in the provided header initializes _nUntracked to 0.
    ASSERT_EQ(pool.Untracked(), static_cast<size_t>(0));

    pool.SetTracked();

    EXPECT_EQ(pool.Untracked(), std::numeric_limits<size_t>::max());
}

} // namespace
