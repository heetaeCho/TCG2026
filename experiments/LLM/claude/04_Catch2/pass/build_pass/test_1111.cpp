#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// ============================================================
// Normal Operation Tests
// ============================================================

TEST(RangeGeneratorTest_1111, ConstructWithPositiveStep_1111) {
    RangeGenerator<int> gen(1, 10, 2);
    EXPECT_EQ(gen.get(), 1);
}

TEST(RangeGeneratorTest_1111, ConstructWithNegativeStep_1111) {
    RangeGenerator<int> gen(10, 1, -2);
    EXPECT_EQ(gen.get(), 10);
}

TEST(RangeGeneratorTest_1111, DefaultStepAscending_1111) {
    RangeGenerator<int> gen(1, 5);
    EXPECT_EQ(gen.get(), 1);
}

TEST(RangeGeneratorTest_1111, DefaultStepDescending_1111) {
    RangeGenerator<int> gen(5, 1);
    EXPECT_EQ(gen.get(), 5);
}

TEST(RangeGeneratorTest_1111, NextAdvancesValue_1111) {
    RangeGenerator<int> gen(1, 5, 1);
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
}

TEST(RangeGeneratorTest_1111, IterateThroughEntireRangeStepOne_1111) {
    RangeGenerator<int> gen(1, 4, 1);
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_1111, IterateThroughEntireRangeStepTwo_1111) {
    RangeGenerator<int> gen(0, 6, 2);
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_1111, NegativeStepIteration_1111) {
    RangeGenerator<int> gen(6, 0, -2);
    EXPECT_EQ(gen.get(), 6);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_1111, SingleElementRange_1111) {
    // Range from 1 to 2 with step 1 should yield only value 1
    RangeGenerator<int> gen(1, 2, 1);
    EXPECT_EQ(gen.get(), 1);
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_1111, FloatingPointRange_1111) {
    RangeGenerator<double> gen(0.0, 1.0, 0.5);
    EXPECT_DOUBLE_EQ(gen.get(), 0.0);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 0.5);
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_1111, NegativeToPositiveRange_1111) {
    RangeGenerator<int> gen(-2, 2, 1);
    EXPECT_EQ(gen.get(), -2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_1111, PositiveToNegativeRange_1111) {
    RangeGenerator<int> gen(2, -2, -1);
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -1);
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_1111, DefaultStepAscendingIteration_1111) {
    RangeGenerator<int> gen(3, 6);
    EXPECT_EQ(gen.get(), 3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_1111, DefaultStepDescendingIteration_1111) {
    RangeGenerator<int> gen(6, 3);
    EXPECT_EQ(gen.get(), 6);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_FALSE(gen.next());
}

// ============================================================
// Boundary Condition Tests
// ============================================================

TEST(RangeGeneratorTest_1111, StepExactlyReachesEnd_1111) {
    // 2 to 8 step 3: values 2, 5 (next would be 8 which equals end, so stops)
    RangeGenerator<int> gen(2, 8, 3);
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_1111, StepOvershotsEnd_1111) {
    // 0 to 5 step 3: values 0, 3 (next would be 6 > 5, so stops)
    RangeGenerator<int> gen(0, 5, 3);
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_1111, LargeStep_1111) {
    // Step larger than range: only start value
    RangeGenerator<int> gen(0, 3, 10);
    EXPECT_EQ(gen.get(), 0);
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_1111, AdjacentValues_1111) {
    RangeGenerator<int> gen(5, 6, 1);
    EXPECT_EQ(gen.get(), 5);
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_1111, NegativeAdjacentValues_1111) {
    RangeGenerator<int> gen(-1, -2, -1);
    EXPECT_EQ(gen.get(), -1);
    EXPECT_FALSE(gen.next());
}

// ============================================================
// Exceptional / Error Cases (assertion failures)
// ============================================================

TEST(RangeGeneratorTest_1111, StartEqualsEndAssertionDeath_1111) {
    EXPECT_DEATH(RangeGenerator<int>(5, 5, 1), "");
}

TEST(RangeGeneratorTest_1111, ZeroStepAssertionDeath_1111) {
    EXPECT_DEATH(RangeGenerator<int>(1, 10, 0), "");
}

TEST(RangeGeneratorTest_1111, PositiveStepWithDescendingRangeAssertionDeath_1111) {
    EXPECT_DEATH(RangeGenerator<int>(10, 1, 1), "");
}

TEST(RangeGeneratorTest_1111, NegativeStepWithAscendingRangeAssertionDeath_1111) {
    EXPECT_DEATH(RangeGenerator<int>(1, 10, -1), "");
}

// ============================================================
// get() const correctness test
// ============================================================

TEST(RangeGeneratorTest_1111, GetReturnsCurrentValueConsistently_1111) {
    RangeGenerator<int> gen(10, 15, 2);
    // Calling get() multiple times without next() should return the same value
    EXPECT_EQ(gen.get(), 10);
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 12);
    EXPECT_EQ(gen.get(), 12);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 14);
    EXPECT_EQ(gen.get(), 14);
    EXPECT_FALSE(gen.next());
}

// ============================================================
// Long type test
// ============================================================

TEST(RangeGeneratorTest_1111, LongTypeRange_1111) {
    RangeGenerator<long long> gen(0LL, 1000000000LL, 500000000LL);
    EXPECT_EQ(gen.get(), 0LL);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 500000000LL);
    EXPECT_FALSE(gen.next());
}

// ============================================================
// Float descending range
// ============================================================

TEST(RangeGeneratorTest_1111, FloatingPointDescendingRange_1111) {
    RangeGenerator<double> gen(1.0, 0.0, -0.5);
    EXPECT_DOUBLE_EQ(gen.get(), 1.0);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 0.5);
    EXPECT_FALSE(gen.next());
}
