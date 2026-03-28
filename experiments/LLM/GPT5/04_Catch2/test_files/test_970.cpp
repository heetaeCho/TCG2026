// File: tests/ApproxMatcher_970_tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::ApproxMatcher;

namespace {

using Vec = std::vector<double>;

} // namespace

// Normal operation: identical vectors (same size, same values) should match.
TEST(ApproxMatcherTest_970, ExactMatchSameSize_970) {
    Vec comp{1.0, 2.0, 3.0};
    Vec v   {1.0, 2.0, 3.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> m(comp);
    EXPECT_TRUE(m.match(v));
}

// Boundary: both empty vectors should match.
TEST(ApproxMatcherTest_970, EmptyVectorsMatch_970) {
    Vec comp{};
    Vec v{};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> m(comp);
    EXPECT_TRUE(m.match(v));
}

// Boundary: size mismatch should fail regardless of values.
TEST(ApproxMatcherTest_970, FailsOnSizeMismatch_970) {
    Vec comp{1.0, 2.0, 3.0};
    Vec v   {1.0, 2.0}; // shorter

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> m(comp);
    EXPECT_FALSE(m.match(v));
}

// Normal operation: values within an absolute margin should match.
TEST(ApproxMatcherTest_970, MatchesWithinMargin_970) {
    Vec comp{1.0, 2.0, 3.0};
    // Each element differs by at most 0.005
    Vec v   {1.005, 1.995, 3.000};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> m(comp);
    // Use explicit absolute margin to avoid assumptions about defaults.
    m.margin(0.01);
    EXPECT_TRUE(m.match(v));
}

// Error/strict case: tightening tolerance (zero margin & very small epsilon) should fail on slight differences.
TEST(ApproxMatcherTest_970, FailsWhenMarginTooTight_970) {
    Vec comp{10.0, 20.0};
    Vec v   {10.0005, 19.9995}; // tiny deltas

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> m(comp);
    // Make tolerances very strict to force a failure on non-identical values.
    m.margin(0.0).epsilon(0.0);
    EXPECT_FALSE(m.match(v));
}

// API behavior: chaining modifiers returns self; equal vectors still match after chaining (smoke test for scale/epsilon/margin).
TEST(ApproxMatcherTest_970, ChainingReturnsSelfAndStillMatches_970) {
    Vec comp{3.14, 2.71};
    Vec v   {3.14, 2.71};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> m(comp);
    auto& ref = m.epsilon(1e-9).margin(0.0).scale(1.0);
    // Verify fluent API returns the same object (observable via address).
    EXPECT_EQ(&ref, &m);
    // With identical inputs, it must match regardless of tolerance settings.
    EXPECT_TRUE(m.match(v));
}

// describe(): should provide a non-empty human-readable description (format is not asserted).
TEST(ApproxMatcherTest_970, DescribeIsNonEmpty_970) {
    Vec comp{1.0};
    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> m(comp);
    const std::string desc = m.describe();
    EXPECT_FALSE(desc.empty());
    // Do not assert specific text; treat implementation as a black box.
}
