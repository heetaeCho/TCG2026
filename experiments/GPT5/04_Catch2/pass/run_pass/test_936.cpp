// File: tests/range_generator_tests_936.cpp
#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Generators::RangeGenerator;

namespace {

// Suite name includes TEST_ID per your convention.
class RangeGeneratorTest_936 : public ::testing::Test {};

} // namespace

// Normal operation: increasing range with default step (end is exclusive).
TEST_F(RangeGeneratorTest_936, Increasing_DefaultStep_ExclusiveEnd_936) {
    RangeGenerator<int> gen(1, 5); // expected sequence: 1,2,3,4

    // initial value
    EXPECT_EQ(gen.get(), 1);

    // step to 2
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    // step to 3
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);

    // step to 4
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);

    // the next step would pass the end (exclusive), so it should return false
    EXPECT_FALSE(gen.next());
    // Do not call get() after next() returned false (treat as undefined).
}

// Normal operation: decreasing range with default step (end is exclusive).
TEST_F(RangeGeneratorTest_936, Decreasing_DefaultStep_ExclusiveEnd_936) {
    RangeGenerator<int> gen(5, 1); // expected sequence: 5,4,3,2

    EXPECT_EQ(gen.get(), 5);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    EXPECT_FALSE(gen.next());
}

// Custom positive step that does not land exactly on end.
TEST_F(RangeGeneratorTest_936, CustomPositiveStep_ExclusiveEnd_936) {
    RangeGenerator<int> gen(0, 10, 3); // expected sequence: 0,3,6,9

    EXPECT_EQ(gen.get(), 0);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 9);

    EXPECT_FALSE(gen.next());
}

// Custom negative step that does not land exactly on end.
TEST_F(RangeGeneratorTest_936, CustomNegativeStep_ExclusiveEnd_936) {
    RangeGenerator<int> gen(10, 0, -4); // expected sequence: 10,6,2

    EXPECT_EQ(gen.get(), 10);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    EXPECT_FALSE(gen.next());
}

// Boundary behavior: one step before the end; next() becomes false after last valid value.
TEST_F(RangeGeneratorTest_936, Boundary_StopsBeforeExclusiveEnd_936) {
    RangeGenerator<int> gen(0, 5, 2); // expected sequence: 0,2,4

    EXPECT_EQ(gen.get(), 0);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);

    // next would move past the exclusive end -> should return false
    EXPECT_FALSE(gen.next());
}
