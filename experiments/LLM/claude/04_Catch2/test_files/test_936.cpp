#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// ============================================================
// Tests for RangeGenerator with positive step (ascending range)
// ============================================================

TEST(RangeGeneratorTest_936, ConstructWithStartEndStep_PositiveRange_936) {
    // Range [1, 5) with step 1: should yield 1, 2, 3, 4
    RangeGenerator<int> gen(1, 5, 1);
    EXPECT_EQ(gen.get(), 1);
}

TEST(RangeGeneratorTest_936, NextReturnsTrue_WhileWithinRange_936) {
    // Range [0, 3) with step 1: should yield 0, 1, 2
    RangeGenerator<int> gen(0, 3, 1);
    EXPECT_EQ(gen.get(), 0);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    // Next step would be 3, which is not < 3, so should return false
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_936, SingleElementRange_936) {
    // Range [5, 6) with step 1: should yield just 5
    RangeGenerator<int> gen(5, 6, 1);
    EXPECT_EQ(gen.get(), 5);

    // After next, current becomes 6 which is not < 6
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_936, StepGreaterThanOne_936) {
    // Range [0, 10) with step 3: should yield 0, 3, 6, 9
    RangeGenerator<int> gen(0, 10, 3);
    EXPECT_EQ(gen.get(), 0);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 9);

    // 9 + 3 = 12, which is not < 10
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_936, StepExactlyReachesEnd_936) {
    // Range [0, 6) with step 2: should yield 0, 2, 4
    RangeGenerator<int> gen(0, 6, 2);
    EXPECT_EQ(gen.get(), 0);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);

    // 4 + 2 = 6, which is not < 6
    EXPECT_FALSE(gen.next());
}

// ============================================================
// Tests for RangeGenerator with negative step (descending range)
// ============================================================

TEST(RangeGeneratorTest_936, NegativeStep_DescendingRange_936) {
    // Range [5, 1) with step -1: should yield 5, 4, 3, 2
    RangeGenerator<int> gen(5, 1, -1);
    EXPECT_EQ(gen.get(), 5);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    // 2 + (-1) = 1, which is not > 1
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_936, NegativeStep_SingleElement_936) {
    // Range [3, 2) with step -1: should yield just 3
    RangeGenerator<int> gen(3, 2, -1);
    EXPECT_EQ(gen.get(), 3);

    // 3 + (-1) = 2, which is not > 2
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_936, NegativeStep_LargerStep_936) {
    // Range [10, 0) with step -3: should yield 10, 7, 4, 1
    RangeGenerator<int> gen(10, 0, -3);
    EXPECT_EQ(gen.get(), 10);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 7);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);

    // 1 + (-3) = -2, which is not > 0
    EXPECT_FALSE(gen.next());
}

// ============================================================
// Tests for two-argument constructor (auto-step deduction)
// ============================================================

TEST(RangeGeneratorTest_936, TwoArgConstructor_AscendingAutoStep_936) {
    // start < end, so step should be +1
    RangeGenerator<int> gen(0, 3);
    EXPECT_EQ(gen.get(), 0);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_936, TwoArgConstructor_DescendingAutoStep_936) {
    // start > end, so step should be -1
    RangeGenerator<int> gen(3, 0);
    EXPECT_EQ(gen.get(), 3);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);

    EXPECT_FALSE(gen.next());
}

// ============================================================
// Tests with floating point types
// ============================================================

TEST(RangeGeneratorTest_936, FloatingPoint_PositiveStep_936) {
    RangeGenerator<double> gen(0.0, 1.0, 0.3);
    EXPECT_DOUBLE_EQ(gen.get(), 0.0);

    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 0.3);

    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 0.6);

    EXPECT_TRUE(gen.next());
    EXPECT_NEAR(gen.get(), 0.9, 1e-10);

    // 0.9 + 0.3 = 1.2 which is not < 1.0
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_936, FloatingPoint_NegativeStep_936) {
    RangeGenerator<double> gen(1.0, 0.0, -0.5);
    EXPECT_DOUBLE_EQ(gen.get(), 1.0);

    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 0.5);

    // 0.5 + (-0.5) = 0.0 which is not > 0.0
    EXPECT_FALSE(gen.next());
}

// ============================================================
// Boundary / edge cases
// ============================================================

TEST(RangeGeneratorTest_936, StartEqualsEnd_PositiveStep_936) {
    // Start == End with positive step: first get() returns start,
    // but next() should immediately return false since current + step >= end
    RangeGenerator<int> gen(5, 5, 1);
    EXPECT_EQ(gen.get(), 5);
    // 5 + 1 = 6, which is not < 5
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_936, LargeRange_936) {
    // Range [0, 1000000) with step 500000
    RangeGenerator<int> gen(0, 1000000, 500000);
    EXPECT_EQ(gen.get(), 0);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 500000);

    // 500000 + 500000 = 1000000 which is not < 1000000
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_936, GetReturnsConstReference_936) {
    RangeGenerator<int> gen(10, 20, 1);
    const int& val = gen.get();
    EXPECT_EQ(val, 10);

    gen.next();
    // After next(), get() should return the updated value
    EXPECT_EQ(gen.get(), 11);
}

TEST(RangeGeneratorTest_936, NegativeNumbers_936) {
    // Range [-5, -1) with step 1
    RangeGenerator<int> gen(-5, -1, 1);
    EXPECT_EQ(gen.get(), -5);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -4);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -3);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -2);

    // -2 + 1 = -1, which is not < -1
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_936, NegativeToPositive_936) {
    // Range [-2, 2) with step 1
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

TEST(RangeGeneratorTest_936, MultipleNextCallsAfterExhaustion_936) {
    RangeGenerator<int> gen(0, 2, 1);
    EXPECT_EQ(gen.get(), 0);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);

    EXPECT_FALSE(gen.next());

    // Calling next again after exhaustion - behavior depends on implementation
    // but we can at least verify it doesn't crash and returns false
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_936, StepLargerThanRange_936) {
    // Step is larger than the entire range, so only start is yielded
    RangeGenerator<int> gen(0, 5, 10);
    EXPECT_EQ(gen.get(), 0);

    // 0 + 10 = 10, which is not < 5
    EXPECT_FALSE(gen.next());
}

TEST(RangeGeneratorTest_936, NegativeStepLargerThanRange_936) {
    RangeGenerator<int> gen(5, 0, -10);
    EXPECT_EQ(gen.get(), 5);

    // 5 + (-10) = -5, which is not > 0
    EXPECT_FALSE(gen.next());
}
