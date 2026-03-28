// File: tests/range_generator_range_tests_938.cpp

#include <gtest/gtest.h>
#include <limits>
#include "Catch2/extras/catch_amalgamated.hpp"

namespace CG = Catch::Generators;

class RangeGeneratorRangeTest_938 : public ::testing::Test {};

// [Normal operation] Verify iteration from start to just before end (observable via get()/next()).
TEST_F(RangeGeneratorRangeTest_938, RangeYieldsIncreasingIntegers_938) {
    auto gen = CG::range<int>(1, 4); // expected sequence: 1, 2, 3

    // First value should be available immediately via get()
    EXPECT_EQ(gen.get(), 1);

    // Advance and check subsequent values
    ASSERT_TRUE(gen.next()); // move to 2
    EXPECT_EQ(gen.get(), 2);

    ASSERT_TRUE(gen.next()); // move to 3
    EXPECT_EQ(gen.get(), 3);

    // No more values
    EXPECT_FALSE(gen.next());
}

// [Boundary] start == end should yield no values (no observable element).
// We must not call get() if there are no elements; we check next() first.
TEST_F(RangeGeneratorRangeTest_938, EmptyRangeHasNoValues_938) {
    auto gen = CG::range<int>(5, 5); // empty

    // No elements to observe/advance to
    EXPECT_FALSE(gen.next());
}

// [Boundary] Negative to zero; ensures it works with negative integers
TEST_F(RangeGeneratorRangeTest_938, NegativeToZeroRange_938) {
    auto gen = CG::range<int>(-2, 1); // expected sequence: -2, -1, 0

    EXPECT_EQ(gen.get(), -2);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -1);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0);

    EXPECT_FALSE(gen.next());
}

// [Boundary] Upper bound near INT_MAX to surface potential overflow/edge handling (observable sequence only)
TEST_F(RangeGeneratorRangeTest_938, UpperBoundNearIntMax_938) {
    const int end = std::numeric_limits<int>::max();
    const int start = end - 2; // two values before INT_MAX
    auto gen = CG::range<int>(start, end); // expected sequence: end-2, end-1

    EXPECT_EQ(gen.get(), start);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), start + 1);

    // Should be out after reaching end-1
    EXPECT_FALSE(gen.next());
}
