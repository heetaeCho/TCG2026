// FixedValuesGenerator_test_316.cpp

#include <gtest/gtest.h>
#include "catch2/generators/catch_generators.hpp"

using Catch::Generators::FixedValuesGenerator;

// Normal operation: iterates through all provided integer values in order
TEST(FixedValuesGeneratorTest_316, IteratesThroughAllValues_316) {
    FixedValuesGenerator<int> gen({1, 2, 3});

    // Initial position yields the first value
    EXPECT_EQ(gen.get(), 1);

    // Advance to second
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    // Advance to third
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);

    // End reached: further advance reports no more elements
    EXPECT_FALSE(gen.next());
}

// Boundary: single element sequence
TEST(FixedValuesGeneratorTest_316, SingleElementSequence_316) {
    FixedValuesGenerator<int> gen({42});

    // Only element available initially
    EXPECT_EQ(gen.get(), 42);

    // No second element
    EXPECT_FALSE(gen.next());
}

// Stability: repeated get() without advancing returns the same current value
TEST(FixedValuesGeneratorTest_316, RepeatedGetWithoutNextReturnsSameValue_316) {
    FixedValuesGenerator<int> gen({7, 8});

    const int first_read = gen.get();
    const int second_read = gen.get();
    EXPECT_EQ(first_read, 7);
    EXPECT_EQ(second_read, 7);

    // After advancing once, get() reflects the new current value
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 8);
}

// Type coverage: works with non-integer types (e.g., std::string)
TEST(FixedValuesGeneratorTest_316, WorksWithStrings_316) {
    FixedValuesGenerator<std::string> gen({"alpha", "beta"});

    EXPECT_EQ(gen.get(), "alpha");
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "beta");
    EXPECT_FALSE(gen.next());
}

// Error/edge behavior (observable): once exhausted, next() continues to return false
TEST(FixedValuesGeneratorTest_316, NextStaysFalseAfterExhaustion_316) {
    FixedValuesGenerator<int> gen({10});

    // Consume the only value
    EXPECT_EQ(gen.get(), 10);
    EXPECT_FALSE(gen.next());

    // Subsequent calls remain false (no undefined behavior assumed from get())
    EXPECT_FALSE(gen.next());
}
