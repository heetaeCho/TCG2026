// File: within_ulps_matcher_describe_test_200.cpp
#include <gtest/gtest.h>
#include <string>

// Include the matcher headers from your project
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using Catch::Matchers::WithinUlpsMatcher;
using Catch::Matchers::Detail::FloatingPointKind;

namespace {

// Helper: create a matcher and return its description (black-box usage)
static std::string Describe(double target, uint64_t ulps, FloatingPointKind kind) {
    WithinUlpsMatcher m(target, ulps, kind);
    return m.describe();
}

} // namespace

// Verifies the prefix "is within <ulps> ULPs of " appears and the float target gets an 'f' suffix.
TEST(WithinUlpsMatcherDescribeTest_200, FloatSuffixAndUlpsPrefix_200) {
    const std::string desc = Describe(1.5, /*ulps*/4, FloatingPointKind::Float);

    // Observable keywords/patterns
    EXPECT_NE(desc.find("is within 4 ULPs of "), std::string::npos)
        << "Description must contain the ULP count prefix";
    EXPECT_NE(desc.find("1.5f"), std::string::npos)
        << "Float target should be rendered with an 'f' suffix";
}

// Verifies that for double base type there is no 'f' suffix for the target.
TEST(WithinUlpsMatcherDescribeTest_200, DoubleHasNoFloatSuffix_200) {
    const std::string desc = Describe(1.5, /*ulps*/4, FloatingPointKind::Double);

    EXPECT_NE(desc.find("is within 4 ULPs of "), std::string::npos);
    EXPECT_EQ(desc.find("1.5f"), std::string::npos)
        << "Double target must not include 'f' suffix";
    // Still should include the target value in some double form.
    EXPECT_NE(desc.find("1.5"), std::string::npos)
        << "Double target value should appear without 'f' suffix";
}

// Verifies the presence of a bracketed range skeleton: " ([" <lower> ", " <upper> "])"
TEST(WithinUlpsMatcherDescribeTest_200, ContainsBracketedRangeSkeleton_200) {
    const std::string desc = Describe(1.5, /*ulps*/4, FloatingPointKind::Double);

    EXPECT_NE(desc.find(" (["), std::string::npos)
        << "Description should include opening range marker";
    EXPECT_NE(desc.find(", "), std::string::npos)
        << "Description should separate lower/upper bounds with a comma+space";
    EXPECT_NE(desc.find("])"), std::string::npos)
        << "Description should include closing range marker";
}

// Boundary check: when ulps == 0, description should still be well-formed and reflect '0 ULPs'
TEST(WithinUlpsMatcherDescribeTest_200, ZeroUlpsBoundary_200) {
    const std::string desc_float  = Describe(1.5, /*ulps*/0, FloatingPointKind::Float);
    const std::string desc_double = Describe(1.5, /*ulps*/0, FloatingPointKind::Double);

    for (const auto& d : {desc_float, desc_double}) {
        EXPECT_NE(d.find("is within 0 ULPs of "), std::string::npos)
            << "ULPs count should be shown as 0";
        EXPECT_NE(d.find(" (["), std::string::npos)
            << "Range should still be present even for 0 ULPs";
        EXPECT_NE(d.find(", "), std::string::npos);
        EXPECT_NE(d.find("])"), std::string::npos);
    }

    // Float should carry 'f' after the target; double should not.
    EXPECT_NE(desc_float.find("1.5f"), std::string::npos);
    EXPECT_EQ(desc_double.find("1.5f"), std::string::npos);
}

// Sanity: descriptions for the same target/ulps must differ between Float and Double (due to suffix and range formatting path)
TEST(WithinUlpsMatcherDescribeTest_200, FloatVsDoubleDescriptionsDiffer_200) {
    const std::string desc_float  = Describe(1.5, /*ulps*/8, FloatingPointKind::Float);
    const std::string desc_double = Describe(1.5, /*ulps*/8, FloatingPointKind::Double);

    // Black-box expectation: float path adds 'f' to the target and uses float stepping;
    // double path omits 'f' and uses double stepping => descriptions should not be identical.
    EXPECT_NE(desc_float, desc_double)
        << "Descriptions should differ between Float and Double base types";
}

