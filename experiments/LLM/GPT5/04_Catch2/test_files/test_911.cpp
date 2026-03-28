// tests/benchmark/measure_environment_tests_911.cpp
#include <gtest/gtest.h>

// Include the amalgamated header so we only rely on public interfaces
#include "Catch2/extras/catch_amalgamated.hpp"

namespace C = Catch::Benchmark::Detail;

// Two distinct dummy clocks to force distinct template instantiations
struct TestClock_A {};
struct TestClock_B {};

// Helper: attempt to detect if Environment is equality-comparable.
// If not, tests will fall back to conservative assumptions and skip.
template <typename T, typename = void>
struct is_equality_comparable : std::false_type {};
template <typename T>
struct is_equality_comparable<T,
    std::void_t<decltype(std::declval<const T&>() == std::declval<const T&>())>
> : std::true_type {};

// Helper: attempt to detect if Environment is streamable (operator<<).
// If so, we can compare string dumps as an observable behavior.
template <typename T, typename = void>
struct is_streamable : std::false_type {};
template <typename T>
struct is_streamable<T,
    std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>
> : std::true_type {};

// A tiny printer to string when possible; otherwise returns empty string.
template <typename T>
static std::string maybeToString(const T& v) {
    if constexpr (is_streamable<T>::value) {
        std::ostringstream oss;
        oss << v;
        return oss.str();
    } else {
        return {};
    }
}

// ----------------------------------------------------------------------------
// TESTS
// ----------------------------------------------------------------------------

// TEST 1: Basic call succeeds and returns something copyable (normal operation)
TEST(MeasureEnvironment_911, ReturnsEnvironmentForClock_911) {
    // Just verify that the function is callable and returns by value
    // (copy-constructible or move-constructible is implied by return-by-value).
    auto env = C::measure_environment<TestClock_A>();
    (void)env; // silence unused if assertions below are compiled out

    // Very conservative observable checks:
    // - We can at least assert the string form is stable across two immediate calls
    //   if stream insertion is provided by Catch2 for Environment (varies by version).
    if constexpr (is_streamable<decltype(env)>::value) {
        auto env2 = C::measure_environment<TestClock_A>();
        EXPECT_EQ(maybeToString(env), maybeToString(env2))
            << "Expected the string representation to be stable on repeated calls.";
    } else {
        // If there is no operator<<, we cannot safely compare without internals.
        SUCCEED() << "Environment returned; no stream operator available to compare.";
    }
}

// TEST 2: Memoization within the same Clock instantiation (boundary / caching)
// Observable behavior we can check without mocking collaborators:
// - Calling it twice for the *same* Clock should give a stable result.
TEST(MeasureEnvironment_911, SameClockTwiceIsStable_911) {
    auto first  = C::measure_environment<TestClock_A>();
    auto second = C::measure_environment<TestClock_A>();

    if constexpr (is_equality_comparable<decltype(first)>::value) {
        EXPECT_EQ(first, second)
            << "Expected repeated calls for the same Clock to yield equal Environment.";
    } else if constexpr (is_streamable<decltype(first)>::value) {
        EXPECT_EQ(maybeToString(first), maybeToString(second))
            << "Expected repeated calls for the same Clock to yield same string form.";
    } else {
        // We cannot assert equality portably without internals or defined operators.
        GTEST_SKIP() << "Environment is neither equality-comparable nor streamable.";
    }
}

// TEST 3: Independence across different Clock instantiations (boundary behavior)
// The function template's static cache should be per-instantiation.
// We cannot assert that A != B (values could coincidentally match), but we can
// at least assert that querying B in between does not change A's result.
TEST(MeasureEnvironment_911, DifferentClockDoesNotDisturbFirst_911) {
    auto a1 = C::measure_environment<TestClock_A>();
    (void)C::measure_environment<TestClock_B>(); // this should not disturb A's cache
    auto a2 = C::measure_environment<TestClock_A>();

    if constexpr (is_equality_comparable<decltype(a1)>::value) {
        EXPECT_EQ(a1, a2)
            << "Calling with a different Clock should not alter the cached Environment of the first Clock.";
    } else if constexpr (is_streamable<decltype(a1)>::value) {
        EXPECT_EQ(maybeToString(a1), maybeToString(a2))
            << "Calling with a different Clock should not alter string form of the first Clock's Environment.";
    } else {
        GTEST_SKIP() << "Environment is neither equality-comparable nor streamable.";
    }
}

// TEST 4: Idempotence across multiple repeats (stress-ish normal operation)
// Without mocking the collaborators, the best black-box check is that multiple
// calls do not throw and remain consistent for the same Clock.
TEST(MeasureEnvironment_911, MultipleRepeatedCallsRemainConsistent_911) {
    auto baseline = C::measure_environment<TestClock_B>();

    // Call several times; ensure observed representation remains stable.
    for (int i = 0; i < 5; ++i) {
        auto now = C::measure_environment<TestClock_B>();
        if constexpr (is_equality_comparable<decltype(baseline)>::value) {
            EXPECT_EQ(baseline, now);
        } else if constexpr (is_streamable<decltype(baseline)>::value) {
            EXPECT_EQ(maybeToString(baseline), maybeToString(now));
        } else {
            // If we cannot compare at all, at least ensure calls are well-formed.
            SUCCEED();
        }
    }
}
