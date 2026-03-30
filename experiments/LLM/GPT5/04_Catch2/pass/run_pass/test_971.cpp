// TEST_ID: 971
// File: tests/approx_matcher_describe_971.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the provided amalgamated header that contains ApproxMatcher
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {

template <typename T>
using VecApproxMatcher =
    Catch::Matchers::ApproxMatcher<T, std::allocator<T>, std::allocator<T>>;

} // namespace

// ---- Normal operation ----

TEST(ApproxMatcherDescribeTest_971, DescribeMatchesStringifyForInts_971) {
    std::vector<int> cmp{1, 2, 3};
    VecApproxMatcher<int> m{cmp};

    const std::string expected =
        std::string("is approx: ") + ::Catch::Detail::stringify(cmp);

    EXPECT_EQ(m.describe(), expected);
}

TEST(ApproxMatcherDescribeTest_971, DescribeMatchesStringifyForDoubles_971) {
    std::vector<double> cmp{1.0, 2.5, -3.0};
    VecApproxMatcher<double> m{cmp};

    const std::string expected =
        std::string("is approx: ") + ::Catch::Detail::stringify(cmp);

    EXPECT_EQ(m.describe(), expected);
}

// ---- Boundary conditions ----

TEST(ApproxMatcherDescribeTest_971, DescribeWithEmptyVector_971) {
    std::vector<int> cmp{};
    VecApproxMatcher<int> m{cmp};

    const std::string expected =
        std::string("is approx: ") + ::Catch::Detail::stringify(cmp);

    EXPECT_EQ(m.describe(), expected);
}

TEST(ApproxMatcherDescribeTest_971, DescribeWithSingleElement_971) {
    std::vector<int> cmp{42};
    VecApproxMatcher<int> m{cmp};

    const std::string expected =
        std::string("is approx: ") + ::Catch::Detail::stringify(cmp);

    EXPECT_EQ(m.describe(), expected);
}

// ---- Interaction with fluent configuration (observable via describe only) ----
// We verify that describe() remains purely a description of the comparator
// sequence and is not changed by epsilon/margin/scale adjustments.

TEST(ApproxMatcherDescribeTest_971, DescribeUnaffectedByEpsilonMarginScale_971) {
    std::vector<double> cmp{10.0, -20.0, 30.0};
    VecApproxMatcher<double> m{cmp};

    const std::string before =
        std::string("is approx: ") + ::Catch::Detail::stringify(cmp);

    // Chain fluent configuration calls (public API, observable side-effect via match only;
    // describe() should continue to reflect comparator content).
    auto& chained = m.epsilon(0.001).margin(0.1).scale(2.0);

    // The fluent API returns a reference to the matcher (publicly observable via type)
    EXPECT_EQ(&chained, &m);

    const std::string after = m.describe();
    EXPECT_EQ(after, before);
}

// ---- Mixed-type values that stringify clearly (another normal check) ----

TEST(ApproxMatcherDescribeTest_971, DescribeWithNegativeAndPositiveInts_971) {
    std::vector<int> cmp{-5, 0, 7, 12};
    VecApproxMatcher<int> m{cmp};

    const std::string expected =
        std::string("is approx: ") + ::Catch::Detail::stringify(cmp);

    EXPECT_EQ(m.describe(), expected);
}
