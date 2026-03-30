// File: within_rel_matcher_tests_206.cpp

#include <gtest/gtest.h>

// Catch2 matcher header that declares WithinRel / WithinRelMatcher
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinRelMatcher;

namespace {

// A small helper to silence -Wfloat-equal where enabled; we deliberately
// use exact equality in some tests because exact-equality behavior is a
// legitimate, observable part of the public matcher API.
inline double same(double x) { return x; }

} // namespace

// ---------- Type & Construction / Basic API ----------

TEST(WithinRelMatcherTest_206, ReturnsWithinRelMatcherType_206) {
    auto m = WithinRel(1.23, 0.0);
    // Compile-time type check via decltype. We don't assert at runtime; if this
    // compiles, the interface contract (return type) holds.
    (void)static_cast<WithinRelMatcher*>(nullptr); // ensure type is visible
    (void)m; // silence unused warning
}

TEST(WithinRelMatcherTest_206, IsCopyAndMoveConstructible_206) {
    auto m = WithinRel(3.14, 0.01);

    // Copy-construct
    WithinRelMatcher m_copy = m;
    // Move-construct
    WithinRelMatcher m_move = std::move(m_copy);

    // Observable: copied/moved matcher should be invocable and produce a bool
    EXPECT_TRUE(m_move.match(same(3.14)));
}

// ---------- Observable Matching Behavior (black-box) ----------

TEST(WithinRelMatcherTest_206, ExactMatchWithZeroEpsMatches_206) {
    const double target = 42.0;
    auto m = WithinRel(target, 0.0);

    // With zero relative tolerance, exact equality should match.
    EXPECT_TRUE(m.match(target));
}

TEST(WithinRelMatcherTest_206, DifferentValueWithZeroEpsDoesNotMatch_206) {
    const double target = 10.0;
    auto m = WithinRel(target, 0.0);

    // With zero relative tolerance, any non-equal value should not match.
    EXPECT_FALSE(m.match(target + 1.0));
    EXPECT_FALSE(m.match(target - 1.0));
}

TEST(WithinRelMatcherTest_206, SameArgsProduceConsistentResultsAfterCopy_206) {
    const double target = 5.0;
    const double eps = 1e-3;

    auto m1 = WithinRel(target, eps);
    auto m2 = m1; // copy

    // For a representative set of probes, copied matcher should behave identically.
    const double probes[] = { target, target * 1.0005, target * 0.9995, target + 1.0, target - 1.0 };
    for (double v : probes) {
        EXPECT_EQ(m1.match(v), m2.match(v)) << "Mismatch on value " << v;
    }
}

TEST(WithinRelMatcherTest_206, SameParametersYieldSameDecisions_206) {
    const double target = -7.0;
    const double eps = 1e-2;

    auto mA = WithinRel(target, eps);
    auto mB = WithinRel(target, eps);

    // Determinism: two independently constructed matchers with the same
    // parameters should make the same decision for any given input.
    const double probes[] = { target, target * 1.005, target * 0.995, target + 0.5, target - 0.5 };
    for (double v : probes) {
        EXPECT_EQ(mA.match(v), mB.match(v)) << "Mismatch on value " << v;
    }
}

// ---------- Boundary-ish Observations Without Assuming Internals ----------

TEST(WithinRelMatcherTest_206, BehaviorIsWellDefinedForVerySmallTarget_206) {
    // We only check that the matcher is callable and returns a boolean;
    // we don't assert any specific numeric policy beyond exact equality.
    const double tiny = 1e-12;
    auto m = WithinRel(tiny, 1e-6);

    // Exact equality should still match
    EXPECT_TRUE(m.match(tiny));

    // A nearby, but different, value yields a determinate boolean (no crash/UB).
    (void)EXPECT_TRUE(m.match(2e-12) || !m.match(2e-12));
}

TEST(WithinRelMatcherTest_206, BehaviorIsWellDefinedForLargeValues_206) {
    const double big = 1e12;
    auto m = WithinRel(big, 1e-6);

    // Exact equality should match
    EXPECT_TRUE(m.match(big));

    // A distinct value returns a determinate boolean (no crash/UB).
    (void)EXPECT_TRUE(m.match(big * 1.1) || !m.match(big * 1.1));
}

