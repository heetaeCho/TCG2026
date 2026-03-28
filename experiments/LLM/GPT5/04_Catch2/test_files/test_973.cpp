// File: tests/ApproxMatcher_margin_973.tests.cpp

#include <gtest/gtest.h>
#include <vector>

// Include the amalgamated Catch2 header that declares ApproxMatcher
#include "Catch2/extras/catch_amalgamated.hpp"

using std::vector;

// Convenience alias for a concrete instantiation we can exercise
using ApproxMatcherD =
    Catch::Matchers::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>;

class ApproxMatcherMarginTest_973 : public ::testing::Test {
protected:
    static vector<double> vec(std::initializer_list<double> xs) { return vector<double>(xs); }
};

// [Normal operation] margin returns *this (fluent API)
TEST_F(ApproxMatcherMarginTest_973, MarginReturnsSelf_973) {
    const vector<double> baseline = vec({1.0, 2.0});
    ApproxMatcherD matcher{baseline};

    auto* before = &matcher;
    auto& ret = matcher.margin(0.5); // should be a reference to *this
    auto* after = &ret;

    EXPECT_EQ(before, after) << "margin(T) must return *this to support fluent chaining.";
}

// [Observable behavior] With values near zero, default relative epsilon is tiny,
// so a small absolute delta should NOT match until a margin is provided.
TEST_F(ApproxMatcherMarginTest_973, NoMarginNearZeroDoesNotMatch_973) {
    const vector<double> baseline = vec({0.0});
    ApproxMatcherD matcher{baseline};

    // Candidate differs by 5e-4; without margin, expect not matching (near zero)
    EXPECT_FALSE(matcher.match(vec({0.0005})));
}

// [Observable behavior] After setting a sufficient margin, the same vector should match
TEST_F(ApproxMatcherMarginTest_973, SufficientMarginEnablesMatchNearZero_973) {
    const vector<double> baseline = vec({0.0});
    ApproxMatcherD matcher{baseline};

    matcher.margin(0.001); // larger than the absolute difference 5e-4
    EXPECT_TRUE(matcher.match(vec({0.0005})));
}

// [Boundary-ish] Margin smaller than the difference should still fail
TEST_F(ApproxMatcherMarginTest_973, InsufficientMarginDoesNotEnableMatch_973) {
    const vector<double> baseline = vec({0.0});
    ApproxMatcherD matcher{baseline};

    matcher.margin(0.0001); // smaller than 5e-4
    EXPECT_FALSE(matcher.match(vec({0.0005})));
}

// [Type constraint smoke test] margin should accept any T constructible to double (e.g., int)
TEST_F(ApproxMatcherMarginTest_973, MarginAcceptsIntegerType_973) {
    const vector<double> baseline = vec({1.0});
    ApproxMatcherD matcher{baseline};

    // Just ensure it compiles and returns self; we don't assert specific match semantics here
    auto& chained = matcher.margin(1); // int is constructible to double
    EXPECT_EQ(&chained, &matcher);
}
