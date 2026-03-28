// File: test_direct_compare_608.cpp

#include <gtest/gtest.h>
#include <limits>
#include <cmath>

namespace Catch { namespace Detail { bool directCompare(float lhs, float rhs); } }

using Catch::Detail::directCompare;

// Normal operation: exactly equal finite values
TEST(DirectCompareTest_608, ReturnsTrueForExactlyEqualFiniteValues_608) {
    EXPECT_TRUE(directCompare(1.0f, 1.0f));
    EXPECT_TRUE(directCompare(-123.75f, -123.75f));
    EXPECT_TRUE(directCompare(0.0f, 0.0f));
}

// Normal operation: clearly different finite values
TEST(DirectCompareTest_608, ReturnsFalseForDifferentFiniteValues_608) {
    EXPECT_FALSE(directCompare(1.0f, 2.0f));
    EXPECT_FALSE(directCompare(-5.0f, -5.0001f));
}

// Boundary: adjacent representable floats (ULP difference of 1) are not equal
TEST(DirectCompareTest_608, ReturnsFalseForAdjacentFloats_608) {
    float a = 1.0f;
    float b = std::nextafterf(a, 2.0f); // next representable float greater than 1.0
    ASSERT_NE(a, b); // sanity check for test setup
    EXPECT_FALSE(directCompare(a, b));
    EXPECT_FALSE(directCompare(b, a)); // symmetry
}

// Boundary: +0.0 and -0.0 compare equal with operator==
TEST(DirectCompareTest_608, ReturnsTrueForPositiveAndNegativeZero_608) {
    float pz = 0.0f;
    float nz = -0.0f;
    // Verify behavior observable via public comparison
    EXPECT_TRUE(directCompare(pz, nz));
    EXPECT_TRUE(directCompare(nz, pz));
}

// Boundary: infinities — same sign equal, opposite sign not equal
TEST(DirectCompareTest_608, HandlesInfinities_608) {
    float inf  = std::numeric_limits<float>::infinity();
    float ninf = -std::numeric_limits<float>::infinity();

    EXPECT_TRUE(directCompare(inf, inf));
    EXPECT_TRUE(directCompare(ninf, ninf));

    EXPECT_FALSE(directCompare(inf, ninf));
    EXPECT_FALSE(directCompare(ninf, inf));
}

// Exceptional/edge: NaN comparisons are always false with operator==
TEST(DirectCompareTest_608, ReturnsFalseWhenEitherSideIsNaN_608) {
    float nan = std::numeric_limits<float>::quiet_NaN();

    EXPECT_FALSE(directCompare(nan, nan));     // NaN vs NaN
    EXPECT_FALSE(directCompare(nan, 1.0f));    // NaN vs finite
    EXPECT_FALSE(directCompare(1.0f, nan));    // finite vs NaN
    EXPECT_FALSE(directCompare(nan, std::numeric_limits<float>::infinity())); // NaN vs inf
}
