// File: within_ulps_matcher_tests_199.cpp

#include <gtest/gtest.h>
#include <limits>
#include <cmath>

// Headers under test
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using Catch::Matchers::WithinUlpsMatcher;
using Catch::Matchers::Detail::FloatingPointKind;

class WithinUlpsMatcherTest_199 : public ::testing::Test {};

// --- Normal operation: identical values should match (for both kinds) ---
TEST_F(WithinUlpsMatcherTest_199, IdenticalValuesMatch_FloatKind_199) {
    const double target = 1.23456789;
    const uint64_t ulps = 0; // exact match tolerance
    WithinUlpsMatcher m(target, ulps, FloatingPointKind::Float);

    EXPECT_TRUE(m.match(target));
}

TEST_F(WithinUlpsMatcherTest_199, IdenticalValuesMatch_DoubleKind_199) {
    const double target = 1.23456789;
    const uint64_t ulps = 0; // exact match tolerance
    WithinUlpsMatcher m(target, ulps, FloatingPointKind::Double);

    EXPECT_TRUE(m.match(target));
}

// --- Boundary-ish condition: values that differ as doubles but collapse to the same float ---
// This checks the observable routing behavior:
//  - Float kind casts both to float, which can make them equal -> should match with ulps=0.
//  - Double kind compares doubles exactly with ulps=0 -> should not match when values differ.
TEST_F(WithinUlpsMatcherTest_199, DiffersInDoubleSameAsFloat_RoutesToExpectedBranch_199) {
    const double target = 1.0;
    // Next representable double greater than 1.0
    const double neighbor = std::nextafter(target, std::numeric_limits<double>::infinity());

    ASSERT_NE(target, neighbor); // sanity check for the test itself

    const uint64_t ulps = 0;

    // Float branch: values collapse to identical float representation => should match.
    {
        WithinUlpsMatcher m_float(target, ulps, FloatingPointKind::Float);
        EXPECT_TRUE(m_float.match(neighbor));
    }

    // Double branch: different doubles with ulps=0 (exact) => should not match.
    {
        WithinUlpsMatcher m_double(target, ulps, FloatingPointKind::Double);
        EXPECT_FALSE(m_double.match(neighbor));
    }
}

// --- Error/negative case that is observable via the interface: clearly different numbers with ulps=0 ---
TEST_F(WithinUlpsMatcherTest_199, ClearlyDifferentNumbersDoNotMatchWithZeroUlps_199) {
    const double target = 1000.0;
    const double far    = 1000.0001; // far enough apart
    const uint64_t ulps = 0;

    // For both kinds, with zero ulps tolerance, these should not match.
    {
        WithinUlpsMatcher m_float(target, ulps, FloatingPointKind::Float);
        EXPECT_FALSE(m_float.match(far));
    }
    {
        WithinUlpsMatcher m_double(target, ulps, FloatingPointKind::Double);
        EXPECT_FALSE(m_double.match(far));
    }
}

// --- General contract check: describe() returns a non-empty, human-readable message ---
TEST_F(WithinUlpsMatcherTest_199, DescribeIsNonEmpty_199) {
    WithinUlpsMatcher m(3.141592653589793, /*ulps*/ 4, FloatingPointKind::Double);
    const std::string d = m.describe();
    EXPECT_FALSE(d.empty());
}
