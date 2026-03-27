// File: test_dynarray_capacity_14.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

using tinyxml2::DynArray;

class DynArrayCapacityTest_14 : public ::testing::Test {};

TEST_F(DynArrayCapacityTest_14, CapacityInitiallyEqualsInitialSize_14) {
    DynArray<int, 4> a;
    EXPECT_EQ(a.Capacity(), static_cast<size_t>(4));
}

TEST_F(DynArrayCapacityTest_14, CapacityCallableOnConstObject_14) {
    const DynArray<int, 8> a;
    EXPECT_EQ(a.Capacity(), static_cast<size_t>(8));
}

TEST_F(DynArrayCapacityTest_14, CapacityNeverLessThanInitialSizeAfterMutations_14) {
    constexpr size_t kInitial = 4;
    DynArray<int, kInitial> a;

    // Mutate via Push and Clear; regardless of internal growth strategy, capacity should
    // never drop below the template INITIAL_SIZE (Capacity() has an internal assert for it).
    a.Push(1);
    a.Push(2);
    a.Clear();

    EXPECT_GE(a.Capacity(), kInitial);
}

TEST_F(DynArrayCapacityTest_14, CapacityAtLeastSizeAfterGrowingBeyondInitial_14) {
    constexpr size_t kInitial = 4;
    DynArray<int, kInitial> a;

    // Add more than INITIAL_SIZE elements; do not assume exact capacity growth policy.
    const size_t targetSize = kInitial + 1;
    for (size_t i = 0; i < targetSize; ++i) {
        a.Push(static_cast<int>(i));
    }

    EXPECT_EQ(a.Size(), targetSize);
    EXPECT_GE(a.Capacity(), a.Size());
    EXPECT_GE(a.Capacity(), kInitial);
}

}  // namespace
