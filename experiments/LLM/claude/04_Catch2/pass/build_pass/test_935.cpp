#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// ============================================================
// Tests for RangeGenerator with int type
// ============================================================

class RangeGeneratorTest_935 : public ::testing::Test {
protected:
};

// Normal operation: ascending range with default step
TEST_F(RangeGeneratorTest_935, AscendingRangeDefaultStep_935) {
    RangeGenerator<int> gen(1, 5);
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_FALSE(gen.next());
}

// Normal operation: descending range with default step
TEST_F(RangeGeneratorTest_935, DescendingRangeDefaultStep_935) {
    RangeGenerator<int> gen(5, 1);
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);
    EXPECT_FALSE(gen.next());
}

// Normal operation: ascending range with explicit step
TEST_F(RangeGeneratorTest_935, AscendingRangeWithStep_935) {
    RangeGenerator<int> gen(0, 10, 3);
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 9);
    EXPECT_FALSE(gen.next());
}

// Normal operation: descending range with explicit negative step
TEST_F(RangeGeneratorTest_935, DescendingRangeWithNegativeStep_935) {
    RangeGenerator<int> gen(10, 0, -3);
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 7);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);
    EXPECT_FALSE(gen.next());
}

// Boundary condition: start equals end (single element range)
TEST_F(RangeGeneratorTest_935, StartEqualsEnd_935) {
    RangeGenerator<int> gen(5, 5);
    EXPECT_EQ(gen.get(), 5);
    EXPECT_FALSE(gen.next());
}

// Boundary condition: step of 1 with range of size 1
TEST_F(RangeGeneratorTest_935, SingleStepRange_935) {
    RangeGenerator<int> gen(3, 4);
    EXPECT_EQ(gen.get(), 3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_FALSE(gen.next());
}

// Get returns consistent value without next
TEST_F(RangeGeneratorTest_935, GetReturnsConsistentValue_935) {
    RangeGenerator<int> gen(7, 10);
    EXPECT_EQ(gen.get(), 7);
    EXPECT_EQ(gen.get(), 7);  // calling get multiple times should return same value
}

// Normal operation: step of 2 ascending
TEST_F(RangeGeneratorTest_935, AscendingStepOf2_935) {
    RangeGenerator<int> gen(0, 6, 2);
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);
    EXPECT_FALSE(gen.next());
}

// Boundary: step exactly reaches end
TEST_F(RangeGeneratorTest_935, StepExactlyReachesEnd_935) {
    RangeGenerator<int> gen(0, 9, 3);
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 9);
    EXPECT_FALSE(gen.next());
}

// Boundary: step overshoots end
TEST_F(RangeGeneratorTest_935, StepOvershootsEnd_935) {
    RangeGenerator<int> gen(0, 5, 3);
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    // Next step would be 6, which is > 5, so should stop
    EXPECT_FALSE(gen.next());
}

// Negative numbers: ascending through negative range
TEST_F(RangeGeneratorTest_935, NegativeNumbersAscending_935) {
    RangeGenerator<int> gen(-5, -1);
    EXPECT_EQ(gen.get(), -5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -4);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -1);
    EXPECT_FALSE(gen.next());
}

// Negative numbers: descending through negative range
TEST_F(RangeGeneratorTest_935, NegativeNumbersDescending_935) {
    RangeGenerator<int> gen(-1, -5);
    EXPECT_EQ(gen.get(), -1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -4);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -5);
    EXPECT_FALSE(gen.next());
}

// Crossing zero: ascending from negative to positive
TEST_F(RangeGeneratorTest_935, CrossingZeroAscending_935) {
    RangeGenerator<int> gen(-2, 2);
    EXPECT_EQ(gen.get(), -2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_FALSE(gen.next());
}

// Float type: ascending range
TEST_F(RangeGeneratorTest_935, FloatAscendingRange_935) {
    RangeGenerator<double> gen(0.0, 1.0, 0.5);
    EXPECT_DOUBLE_EQ(gen.get(), 0.0);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 0.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 1.0);
    EXPECT_FALSE(gen.next());
}

// Float type: descending range
TEST_F(RangeGeneratorTest_935, FloatDescendingRange_935) {
    RangeGenerator<double> gen(1.0, 0.0, -0.5);
    EXPECT_DOUBLE_EQ(gen.get(), 1.0);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 0.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 0.0);
    EXPECT_FALSE(gen.next());
}

// Large step: step larger than range
TEST_F(RangeGeneratorTest_935, LargeStepLargerThanRange_935) {
    RangeGenerator<int> gen(0, 3, 10);
    EXPECT_EQ(gen.get(), 0);
    // The next step would go to 10, which is past 3
    EXPECT_FALSE(gen.next());
}

// Large step descending: step magnitude larger than range
TEST_F(RangeGeneratorTest_935, LargeStepDescendingLargerThanRange_935) {
    RangeGenerator<int> gen(3, 0, -10);
    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}

// Verify next returns false after exhaustion and stays false
TEST_F(RangeGeneratorTest_935, NextReturnsFalseAfterExhaustion_935) {
    RangeGenerator<int> gen(1, 2);
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_FALSE(gen.next());
    // Calling next again should still return false
    EXPECT_FALSE(gen.next());
}

// Zero start and end
TEST_F(RangeGeneratorTest_935, ZeroStartAndEnd_935) {
    RangeGenerator<int> gen(0, 0);
    EXPECT_EQ(gen.get(), 0);
    EXPECT_FALSE(gen.next());
}

// Get returns reference to current value
TEST_F(RangeGeneratorTest_935, GetReturnsReference_935) {
    RangeGenerator<int> gen(1, 3);
    const int& ref1 = gen.get();
    EXPECT_EQ(ref1, 1);
    gen.next();
    const int& ref2 = gen.get();
    EXPECT_EQ(ref2, 2);
}

// Step of 1 explicit matches default for ascending
TEST_F(RangeGeneratorTest_935, ExplicitStep1MatchesDefault_935) {
    RangeGenerator<int> gen1(1, 3, 1);
    RangeGenerator<int> gen2(1, 3);
    
    EXPECT_EQ(gen1.get(), gen2.get());
    while (gen1.next()) {
        EXPECT_TRUE(gen2.next());
        EXPECT_EQ(gen1.get(), gen2.get());
    }
    EXPECT_FALSE(gen2.next());
}

// Step of -1 explicit matches default for descending
TEST_F(RangeGeneratorTest_935, ExplicitStepMinus1MatchesDefault_935) {
    RangeGenerator<int> gen1(3, 1, -1);
    RangeGenerator<int> gen2(3, 1);
    
    EXPECT_EQ(gen1.get(), gen2.get());
    while (gen1.next()) {
        EXPECT_TRUE(gen2.next());
        EXPECT_EQ(gen1.get(), gen2.get());
    }
    EXPECT_FALSE(gen2.next());
}
