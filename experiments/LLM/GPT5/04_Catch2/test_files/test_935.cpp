// File: tests/RangeGenerator_935_Test.cpp

#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Generators::RangeGenerator;

// A tiny helper that consumes a generator strictly through its public API.
// It never peeks into internals and never infers implementation logic.
template <typename T>
static std::vector<T> Drain(RangeGenerator<T>& gen) {
    std::vector<T> out;
    for (;;) {
        out.push_back(gen.get());
        if (!gen.next()) break;
    }
    return out;
}

class RangeGeneratorTest_935 : public ::testing::Test {};

// [Normal] Increasing range with default step (2-arg ctor infers +1)
TEST_F(RangeGeneratorTest_935, IncreasingDefaultStep_935) {
    RangeGenerator<int> gen(1, 5);  // expect monotonic increasing values starting at 1
    // Observable sequence should stop before hitting the end bound.
    // We assert a concrete expected sequence based on public behavior.
    // (start, end) with default step is commonly used as half-open [start, end).
    auto seq = Drain(gen);
    std::vector<int> expected{1, 2, 3, 4};
    EXPECT_EQ(seq, expected);
}

// [Normal] Decreasing range with default step (2-arg ctor infers -1)
TEST_F(RangeGeneratorTest_935, DecreasingDefaultStep_935) {
    RangeGenerator<int> gen(5, 1);  // expect monotonic decreasing values starting at 5
    auto seq = Drain(gen);
    std::vector<int> expected{5, 4, 3, 2};
    EXPECT_EQ(seq, expected);
}

// [Normal] Custom positive step
TEST_F(RangeGeneratorTest_935, CustomPositiveStep_935) {
    RangeGenerator<int> gen(0, 10, 3);  // expect 0, 3, 6, 9
    auto seq = Drain(gen);
    std::vector<int> expected{0, 3, 6, 9};
    EXPECT_EQ(seq, expected);
}

// [Normal] Custom negative step
TEST_F(RangeGeneratorTest_935, CustomNegativeStep_935) {
    RangeGenerator<int> gen(10, -1, -4);  // expect 10, 6, 2, -2 would cross end; stop before crossing -> 10, 6, 2
    auto seq = Drain(gen);
    std::vector<int> expected{10, 6, 2};
    EXPECT_EQ(seq, expected);
}

// [Boundary] Stops strictly before the end (exclusive upper/lower bound)
TEST_F(RangeGeneratorTest_935, StopsBeforeEnd_ExclusiveUpperBound_935) {
    {
        RangeGenerator<int> gen(2, 6, 2);   // 2, 4 (stop before 6)
        auto seq = Drain(gen);
        std::vector<int> expected{2, 4};
        EXPECT_EQ(seq, expected);
    }
    {
        RangeGenerator<int> gen(6, 2, -2);  // 6, 4 (stop before 2)
        auto seq = Drain(gen);
        std::vector<int> expected{6, 4};
        EXPECT_EQ(seq, expected);
    }
}

// [Behavior] get() reflects the current element and does not advance on its own
TEST_F(RangeGeneratorTest_935, GetReturnsCurrent_WithoutAdvancing_935) {
    RangeGenerator<int> gen(3, 7); // default +1 step
    // Calling get() repeatedly without next() should keep returning the same current value.
    EXPECT_EQ(gen.get(), 3);
    EXPECT_EQ(gen.get(), 3);

    // After advancing once, get() should reflect the next current value.
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);

    // Drain the rest to ensure it still terminates as expected.
    auto seq_rest = Drain(gen); // This includes current(4) already captured, so adapt:
    // Since Drain starts by pushing current, and we already consumed one next(),
    // the full remaining sequence produced by Drain should start at 4.
    std::vector<int> expected{4, 5, 6};
    EXPECT_EQ(seq_rest, expected);
}
