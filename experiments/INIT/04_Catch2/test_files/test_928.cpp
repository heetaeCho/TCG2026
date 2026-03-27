// File: tests/RepeatGenerator_repeat_tests_928.cpp

#include <gtest/gtest.h>

// The prompt points us to the amalgamated header path below.
// If your project includes Catch2 differently, adjust the include accordingly.
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Generators::GeneratorWrapper;

namespace {

template <typename T>
static std::vector<T> Drain(GeneratorWrapper<T>& gen) {
    std::vector<T> out;
    // Initial current value
    out.push_back(gen.get());
    // Advance until exhaustion
    while (gen.next()) {
        out.push_back(gen.get());
    }
    return out;
}

} // namespace

// ============== Normal operation ==============

TEST(RepeatGeneratorTest_928, RepeatTwoTimes_RepeatsUnderlyingSequence_928) {
    // Underlying generator yields {1, 2, 3}; repeating 2x => {1,2,3, 1,2,3}
    auto base = Catch::Generators::values({1, 2, 3});
    auto gen  = Catch::Generators::repeat(2, std::move(base));

    const auto got = Drain(gen);
    const std::vector<int> expected{1, 2, 3, 1, 2, 3};
    EXPECT_EQ(got, expected);
}

TEST(RepeatGeneratorTest_928, RepeatOnce_EqualsUnderlyingSequence_928) {
    // repeat(1, …) should behave like the underlying generator (no extra copies)
    auto base = Catch::Generators::values({10, 20});
    auto gen  = Catch::Generators::repeat(1, std::move(base));

    const auto got = Drain(gen);
    const std::vector<int> expected{10, 20};
    EXPECT_EQ(got, expected);
}

// ============== Boundary conditions ==============

TEST(RepeatGeneratorTest_928, SingleValueManyRepeats_928) {
    // Single value repeated n times should produce exactly n outputs of the same value
    auto base = Catch::Generators::value(42);
    auto gen  = Catch::Generators::repeat(5, std::move(base));

    const auto got = Drain(gen);
    const std::vector<int> expected{42, 42, 42, 42, 42};
    EXPECT_EQ(got, expected);
}

TEST(RepeatGeneratorTest_928, WorksWithNonTrivialType_Strings_928) {
    // Verify it also repeats sequences of non-trivial types (e.g., std::string)
    auto base = Catch::Generators::values<std::string>({"a", "bb"});
    auto gen  = Catch::Generators::repeat(3, std::move(base));

    const auto got = Drain(gen);
    const std::vector<std::string> expected{
        "a","bb", "a","bb", "a","bb"
    };
    EXPECT_EQ(got, expected);
}

// ============== Exceptional / error cases observable via interface ==============

#if GTEST_HAS_DEATH_TEST
TEST(RepeatGeneratorTest_928, ZeroRepeats_TriggersDebugAssertion_928) {
    // Construction with repeats == 0 is guarded by an assertion inside Catch2's RepeatGenerator.
    // We validate this via a death test (only meaningful with assertions enabled).
    EXPECT_DEATH_IF_SUPPORTED(
        []{
            auto base = Catch::Generators::values({1});
            // The assert should fire during construction inside repeat(...)
            auto gen  = Catch::Generators::repeat(0, std::move(base));
            (void)gen; // suppress unused warning
        }(),
        "Repeat generator must repeat at least once"
    );
}
#endif

// Note:
// - Using bool with repeat(...) is ill-formed due to a static_assert in Catch2;
//   this cannot be tested at runtime without an intentional compile failure,
//   so we do not include such a test in this suite.
// - Generators created from empty ranges (e.g., from_range on empty) throw before
//   reaching repeat(...); that behavior belongs to the underlying generator and
//   is covered elsewhere, so we do not exercise it here.
