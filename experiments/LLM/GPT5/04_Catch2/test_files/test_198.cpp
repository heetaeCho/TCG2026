// File: within_abs_matcher_describe_tests_198.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"

using ::testing::HasSubstr;

namespace {

using Catch::Matchers::WithinAbsMatcher;

// These tests verify only the *observable string* produced by describe(),
// without making any assumptions about internal state or implementation details.

TEST(WithinAbsMatcherDescribeTest_198, IncludesKeywords_198) {
    // Normal case: check that the fixed keywords appear as specified.
    WithinAbsMatcher matcher(/*target=*/10.0, /*margin=*/1.5);

    const std::string d = matcher.describe();

    EXPECT_THAT(d, HasSubstr("is within"));
    EXPECT_THAT(d, HasSubstr(" of "));
}

TEST(WithinAbsMatcherDescribeTest_198, FormatsMarginAndTarget_198) {
    // Normal case: verify that provided margin and target values appear in the description.
    // Choose values that stringify in a straightforward, non-scientific format.
    const double target = -42.75;
    const double margin = 0.125;
    WithinAbsMatcher matcher(target, margin);

    const std::string d = matcher.describe();

    // We don't assert full equality to avoid coupling to exact spacing/precision choices,
    // but we do check that both numbers are present somewhere in the string.
    EXPECT_THAT(d, HasSubstr("0.125"));
    EXPECT_THAT(d, HasSubstr("-42.75"));
}

TEST(WithinAbsMatcherDescribeTest_198, HandlesZeroAndNegativeMarginPrinting_198) {
    // Boundary/edge observables: description should still include the raw values.
    {
        // Zero margin
        WithinAbsMatcher m_zero(/*target=*/0.0, /*margin=*/0.0);
        const std::string d0 = m_zero.describe();
        EXPECT_THAT(d0, HasSubstr("0"));     // appears at least once
        EXPECT_THAT(d0, HasSubstr("is within"));
        EXPECT_THAT(d0, HasSubstr(" of "));
    }
    {
        // Negative margin (if constructible): description should reflect the value verbatim.
        // We are *not* judging validity here—only the observable string output.
        WithinAbsMatcher m_neg(/*target=*/3.25, /*margin=*/-1.0);
        const std::string d1 = m_neg.describe();
        EXPECT_THAT(d1, HasSubstr("-1"));
        EXPECT_THAT(d1, HasSubstr("3.25"));
    }
}

} // namespace
