// File: predicate_matcher_predicate_tests_215.cpp

#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include just the public header that declares the function under test.
// Adjust the include path if your project structure differs.
#include "catch2/matchers/catch_matchers_predicate.hpp"

namespace {

using Catch::Matchers::Predicate;

// A simple helper to assert that a matcher-like object supports
// match(T) and describe() without relying on internal state.
template <typename MatcherT, typename T>
void ExpectMatchResult(const MatcherT& m, const T& value, bool expected) {
    // Observable behavior: match returns a bool result based on the provided predicate.
    EXPECT_EQ(m.match(value), expected);
}

} // namespace

// ------------------------------------------------------------
// Normal operation: lambda predicate + explicit description.
// Verifies that the created matcher uses the given predicate and
// that the description is propagated.
// ------------------------------------------------------------
TEST(PredicateFunctionTest_215, LambdaEvenPredicateWithDescription_215) {
    auto is_even = [](int v) { return v % 2 == 0; };
    auto m = Predicate<int>(is_even, "is even");

    ExpectMatchResult(m, 4, true);
    ExpectMatchResult(m, 3, false);

    // Observable via interface: description text is what we passed in.
    EXPECT_EQ(m.describe(), "is even");
}

// ------------------------------------------------------------
// Normal operation: default description argument.
// Verifies that the defaulted description observable via describe()
// is an empty string (since default parameter is "").
// ------------------------------------------------------------
TEST(PredicateFunctionTest_215, DefaultDescriptionIsEmptyString_215) {
    auto always_true = [](int) { return true; };
    auto m = Predicate<int>(always_true);

    ExpectMatchResult(m, 123, true);
    EXPECT_EQ(m.describe(), "");
}

// ------------------------------------------------------------
// Works across types: double predicate.
// Checks matching for positive numbers through observable behavior.
// ------------------------------------------------------------
TEST(PredicateFunctionTest_215, WorksForDifferentValueTypes_Double_215) {
    auto positive = [](double x) { return x > 0.0; };
    auto m = Predicate<double>(positive, "is positive");

    const double a = 1.25;
    const double b = -0.1;

    ExpectMatchResult(m, a, true);
    ExpectMatchResult(m, b, false);
    EXPECT_EQ(m.describe(), "is positive");
}

// ------------------------------------------------------------
// Boundary-ish check for integers: zero case.
// Ensures predicate is applied exactly as supplied.
// ------------------------------------------------------------
TEST(PredicateFunctionTest_215, IntegerZeroBoundary_215) {
    auto nonzero = [](int v) { return v != 0; };
    auto m = Predicate<int>(nonzero, "non-zero");

    ExpectMatchResult(m, 0, false);
    ExpectMatchResult(m, 1, true);
    ExpectMatchResult(m, -1, true);
    EXPECT_EQ(m.describe(), "non-zero");
}

// ------------------------------------------------------------
// Perfect-forwarding / move-only predicate:
// Passing a move-only functor should work via forwarding.
// This does NOT inspect internal storage—only observable behavior.
// ------------------------------------------------------------
struct MoveOnlyEquals {
    std::unique_ptr<int> target;
    // Callable with int; returns bool (as required by interface).
    bool operator()(int v) const { return target && v == *target; }

    // Move-only semantics
    MoveOnlyEquals(std::unique_ptr<int> t) : target(std::move(t)) {}
    MoveOnlyEquals(MoveOnlyEquals&&) noexcept = default;
    MoveOnlyEquals& operator=(MoveOnlyEquals&&) noexcept = default;

    MoveOnlyEquals(const MoveOnlyEquals&) = delete;
    MoveOnlyEquals& operator=(const MoveOnlyEquals&) = delete;
};

TEST(PredicateFunctionTest_215, AcceptsMoveOnlyPredicate_215) {
    MoveOnlyEquals pred{std::make_unique<int>(7)};
    auto m = Predicate<int>(std::move(pred), "equals 7");

    ExpectMatchResult(m, 7, true);
    ExpectMatchResult(m, 6, false);
    EXPECT_EQ(m.describe(), "equals 7");
}

// ------------------------------------------------------------
// Description string with non-ASCII (robustness of description forwarding).
// ------------------------------------------------------------
TEST(PredicateFunctionTest_215, UnicodeDescriptionForwarding_215) {
    auto is42 = [](int v) { return v == 42; };
    std::string desc = u8"정확히 42";
    auto m = Predicate<int>(is42, desc);

    ExpectMatchResult(m, 42, true);
    ExpectMatchResult(m, 41, false);
    EXPECT_EQ(m.describe(), desc);
}
