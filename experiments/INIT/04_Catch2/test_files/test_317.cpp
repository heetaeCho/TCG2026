// File: tests/fixed_values_generator_next_317_tests.cpp
#include <gtest/gtest.h>
#include "catch2/generators/catch_generators.hpp"  // path from the prompt

using Catch::Generators::FixedValuesGenerator;

class FixedValuesGeneratorNextTest_317 : public ::testing::Test {};

// [Normal] Empty list: next() should immediately return false.
TEST_F(FixedValuesGeneratorNextTest_317, EmptyList_NextImmediatelyFalse_317) {
    FixedValuesGenerator<int> gen({});
    EXPECT_FALSE(gen.next());
}

// [Boundary] Single element: next() returns false on first call (no “next” beyond the first element).
TEST_F(FixedValuesGeneratorNextTest_317, SingleValue_NextFirstCallFalse_317) {
    FixedValuesGenerator<int> gen({42});
    EXPECT_FALSE(gen.next());
    // And remains false on subsequent calls
    EXPECT_FALSE(gen.next());
    EXPECT_FALSE(gen.next());
}

// [Normal] Two elements: first next() true, second next() false, then stays false.
TEST_F(FixedValuesGeneratorNextTest_317, TwoValues_FirstTrueThenFalse_317) {
    FixedValuesGenerator<int> gen({1, 2});
    EXPECT_TRUE(gen.next());   // move from first to second position
    EXPECT_FALSE(gen.next());  // no element after the second
    EXPECT_FALSE(gen.next());  // remains false after exhaustion
}

// [Boundary] Multiple elements: next() returns true exactly (N-1) times, then false thereafter.
TEST_F(FixedValuesGeneratorNextTest_317, ManyValues_TrueExactlyNMinusOneTimes_317) {
    constexpr int N = 5;
    FixedValuesGenerator<int> gen({0, 1, 2, 3, 4});

    for (int i = 0; i < N - 1; ++i) {
        SCOPED_TRACE(::testing::Message() << "Call #" << (i + 1));
        EXPECT_TRUE(gen.next());
    }
    EXPECT_FALSE(gen.next());  // the Nth call should be false
    EXPECT_FALSE(gen.next());  // stays false after exhaustion
}

// [Exceptional/Edge behavior via interface] After exhaustion, further calls must keep returning false.
TEST_F(FixedValuesGeneratorNextTest_317, AfterExhaustion_SubsequentNextRemainFalse_317) {
    FixedValuesGenerator<int> gen({10, 20});
    EXPECT_TRUE(gen.next());   // 1st -> true
    EXPECT_FALSE(gen.next());  // 2nd -> false (exhausted)
    // Repeatedly calling next() should never flip back to true
    for (int i = 0; i < 3; ++i) {
        SCOPED_TRACE(::testing::Message() << "Extra call #" << (i + 1));
        EXPECT_FALSE(gen.next());
    }
}
