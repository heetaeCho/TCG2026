// File: tests/range_generator_tests_1111.cpp
#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Generators::RangeGenerator;

namespace {

// Helper: collect all generated values by repeatedly calling next()/get()
template <typename T>
std::vector<T> Collect(RangeGenerator<T>& gen) {
    std::vector<T> out;
    out.push_back(gen.get());            // initial value
    while (gen.next()) {
        out.push_back(gen.get());
    }
    return out;
}

} // namespace

// ---------- Normal operation ----------

TEST(RangeGeneratorTest_1111, PositiveRange_DefaultStep_ProducesHalfOpenSequence_1111) {
    RangeGenerator<int> gen(1, 5); // default step should move toward end
    const auto values = Collect(gen);
    // Expect [start, end) with step +1: 1,2,3,4
    std::vector<int> expected{1, 2, 3, 4};
    EXPECT_EQ(values, expected);
}

TEST(RangeGeneratorTest_1111, NegativeRange_DefaultStep_ProducesHalfOpenSequence_1111) {
    RangeGenerator<int> gen(3, 0); // default step should move toward end
    const auto values = Collect(gen);
    // Expect [start, end) with step -1: 3,2,1
    std::vector<int> expected{3, 2, 1};
    EXPECT_EQ(values, expected);
}

TEST(RangeGeneratorTest_1111, CustomPositiveStep_StopsBeforeEnd_1111) {
    RangeGenerator<int> gen(0, 7, 2); // step +2
    const auto values = Collect(gen);
    // Expect 0,2,4,6
    std::vector<int> expected{0, 2, 4, 6};
    EXPECT_EQ(values, expected);
}

TEST(RangeGeneratorTest_1111, CustomNegativeStep_StopsBeforeEnd_1111) {
    RangeGenerator<int> gen(10, 1, -3); // step -3
    const auto values = Collect(gen);
    // Expect 10,7,4
    std::vector<int> expected{10, 7, 4};
    EXPECT_EQ(values, expected);
}

// ---------- Boundary conditions ----------

TEST(RangeGeneratorTest_1111, Boundary_OneStepBeforeEnd_IncludesOnlyStart_1111) {
    RangeGenerator<int> gen(1, 2); // default step +1, only one value before end
    const auto values = Collect(gen);
    std::vector<int> expected{1};
    EXPECT_EQ(values, expected);
}

TEST(RangeGeneratorTest_1111, Boundary_OvershootStopsBeforeEnd_1111) {
    RangeGenerator<int> gen(1, 5, 3); // 1, 4 then stop (next would overshoot)
    const auto values = Collect(gen);
    std::vector<int> expected{1, 4};
    EXPECT_EQ(values, expected);
}

// ---------- Exceptional / error cases (observable via asserts -> death tests) ----------

#if !defined(NDEBUG)  // assert() must be enabled for death tests to be meaningful

TEST(RangeGeneratorTest_1111, Death_StartEqualsEnd_IsRejected_1111) {
    // start == end violates precondition; assert should fire.
    EXPECT_DEATH({ RangeGenerator<int> gen(3, 3); (void)gen; }, ".*");
}

TEST(RangeGeneratorTest_1111, Death_StepZero_IsRejected_1111) {
    // Explicit zero step violates precondition.
    EXPECT_DEATH({ RangeGenerator<int> gen(0, 5, 0); (void)gen; }, ".*");
}

TEST(RangeGeneratorTest_1111, Death_StepMovesAwayFromEnd_PositiveRangeNegativeStep_1111) {
    // For increasing range, negative step moves away from end.
    EXPECT_DEATH({ RangeGenerator<int> gen(0, 5, -1); (void)gen; }, ".*");
}

TEST(RangeGeneratorTest_1111, Death_StepMovesAwayFromEnd_NegativeRangePositiveStep_1111) {
    // For decreasing range, positive step moves away from end.
    EXPECT_DEATH({ RangeGenerator<int> gen(5, 0, 1); (void)gen; }, ".*");
}

#endif // !NDEBUG
