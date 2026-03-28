// File: within_rel_matcher_test_201.cpp

#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include only the public interface
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using Catch::Matchers::WithinRelMatcher;

namespace {

// Helper to avoid accidental NaNs in tests
inline double rel_diff(double a, double b) {
    return std::fabs(a - b) / (std::max)(std::fabs(a), std::fabs(b));
}

} // namespace

// Normal operation: exact equality should match regardless of epsilon
TEST(WithinRelMatcherTest_201, MatchesExactEquality_201) {
    const double target = 123.456;
    const double eps = 1e-9; // any non-negative epsilon
    WithinRelMatcher m(target, eps);
    EXPECT_TRUE(m.match(target));
}

// Normal operation: value within relative margin (above target)
TEST(WithinRelMatcherTest_201, MatchesWithinRelativeMarginAbove_201) {
    const double target = 100.0;
    const double eps = 0.01; // 1%
    const double matchee = 100.5; // 0.5% away -> should match
    ASSERT_LT(rel_diff(matchee, target), eps);
    WithinRelMatcher m(target, eps);
    EXPECT_TRUE(m.match(matchee));
}

// Normal operation: value within relative margin (below target)
TEST(WithinRelMatcherTest_201, MatchesWithinRelativeMarginBelow_201) {
    const double target = 200.0;
    const double eps = 0.02; // 2%
    const double matchee = 196.5; // 1.75% away -> should match
    ASSERT_LT(rel_diff(matchee, target), eps);
    WithinRelMatcher m(target, eps);
    EXPECT_TRUE(m.match(matchee));
}

// Boundary: just outside the relative margin should not match
TEST(WithinRelMatcherTest_201, FailsOutsideRelativeMargin_201) {
    const double target = 100.0;
    const double eps = 0.01; // 1%
    const double matchee = 102.0; // diff = 2; margin = 0.01 * max(100,102)=1.02 -> should fail
    ASSERT_GT(std::fabs(matchee - target), eps * (std::max)(std::fabs(matchee), std::fabs(target)));
    WithinRelMatcher m(target, eps);
    EXPECT_FALSE(m.match(matchee));
}

// Boundary: negative values should be handled symmetrically
TEST(WithinRelMatcherTest_201, MatchesNegativeValuesWithinMargin_201) {
    const double target = -50.0;
    const double eps = 0.01; // 1%
    const double matchee = -49.6; // diff = 0.4; margin = 0.5 -> should match
    ASSERT_LT(std::fabs(matchee - target), eps * (std::max)(std::fabs(matchee), std::fabs(target)));
    WithinRelMatcher m(target, eps);
    EXPECT_TRUE(m.match(matchee));
}

// Boundary: epsilon = 0 means only exact matches should pass
TEST(WithinRelMatcherTest_201, EpsilonZeroOnlyExactMatches_201) {
    const double target = 42.0;
    WithinRelMatcher m(target, 0.0);

    EXPECT_TRUE(m.match(target)) << "Exact equality should pass when epsilon == 0";

    const double matchee = 42.0 + std::numeric_limits<double>::epsilon();
    EXPECT_FALSE(m.match(matchee)) << "Any difference should fail when epsilon == 0";
}

// Behavior around zero target: nonzero matchee requires epsilon >= 1 to pass
TEST(WithinRelMatcherTest_201, ZeroTargetRequiresLargeEpsilonForNonzero_201) {
    {
        // epsilon < 1: should fail for nonzero matchee
        WithinRelMatcher m(0.0, 0.5);
        EXPECT_FALSE(m.match(1.0));
    }
    {
        // epsilon >= 1: should pass for nonzero matchee
        WithinRelMatcher m(0.0, 1.1);
        EXPECT_TRUE(m.match(1.0));
    }
    {
        // matchee == 0 always matches (diff == 0)
        WithinRelMatcher m(0.0, 0.0);
        EXPECT_TRUE(m.match(0.0));
    }
}

// Asymmetry guard: using max(|a|,|b|) makes comparison symmetric with respect to swapping
// (This is an observable property we can check via the public API by constructing two matchers.)
TEST(WithinRelMatcherTest_201, SymmetricWithRespectToSwap_201) {
    const double a = 1e6;
    const double b = a * 1.0005; // 0.05% apart
    const double eps = 0.001;    // 0.1% -> should match either way

    WithinRelMatcher m_ab(a, eps);
    WithinRelMatcher m_ba(b, eps);

    EXPECT_TRUE(m_ab.match(b));
    EXPECT_TRUE(m_ba.match(a));
}

// Large magnitude values should still compare using relative margin
TEST(WithinRelMatcherTest_201, LargeMagnitudesWithinMargin_201) {
    const double target = 1e12;
    const double eps = 1e-6; // 1 ppm
    const double matchee = target * (1.0 + 5e-7); // 0.5 ppm away -> should match
    ASSERT_LT(rel_diff(matchee, target), eps);

    WithinRelMatcher m(target, eps);
    EXPECT_TRUE(m.match(matchee));
}

