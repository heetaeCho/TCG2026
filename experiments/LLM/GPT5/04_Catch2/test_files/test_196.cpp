// File: ulp_distance_test_196.cpp
#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <cstdint>

// Include the header under test
#include "catch2/internal/catch_floating_point_helpers.hpp"

using Catch::ulpDistance;

namespace {

class ULPDistanceTest_196 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(ULPDistanceTest_196, EqualNumbersReturnZero_196) {
    const double x = 123.456;
    EXPECT_EQ(ulpDistance(x, x), 0u);
}

TEST_F(ULPDistanceTest_196, AdjacentPositivesHaveDistanceOne_196) {
    const double x = 1.0;
    const double y = std::nextafter(x, std::numeric_limits<double>::infinity());
    ASSERT_NE(x, y); // sanity
    EXPECT_EQ(ulpDistance(x, y), 1u);
    EXPECT_EQ(ulpDistance(y, x), 1u); // symmetry on magnitude
}

TEST_F(ULPDistanceTest_196, AdjacentNegativesHaveDistanceOne_196) {
    const double x = -1.0;
    const double y = std::nextafter(x, -std::numeric_limits<double>::infinity());
    ASSERT_NE(x, y); // sanity
    EXPECT_EQ(ulpDistance(x, y), 1u);
    EXPECT_EQ(ulpDistance(y, x), 1u);
}

TEST_F(ULPDistanceTest_196, PositiveAndNegativeZeroHaveDistanceZero_196) {
    const double pz = +0.0;
    const double nz = -0.0;
    ASSERT_EQ(pz, nz); // IEEE-754: +0 == -0
    EXPECT_EQ(ulpDistance(pz, nz), 0u);
    EXPECT_EQ(ulpDistance(nz, pz), 0u);
}

// --- Boundary conditions ---

TEST_F(ULPDistanceTest_196, SmallestPositiveSubnormalAndZeroHaveDistanceOne_196) {
    const double dm = std::numeric_limits<double>::denorm_min();
    ASSERT_GT(dm, 0.0);
    EXPECT_EQ(ulpDistance(dm, 0.0), 1u);
    EXPECT_EQ(ulpDistance(0.0, dm), 1u);
}

TEST_F(ULPDistanceTest_196, DBLMaxAndPreviousRepresentableAreOneUlpApart_196) {
    const double max = std::numeric_limits<double>::max();
    const double prev = std::nextafter(max, 0.0); // the next representable towards zero
    ASSERT_LT(prev, max);
    EXPECT_EQ(ulpDistance(max, prev), 1u);
    EXPECT_EQ(ulpDistance(prev, max), 1u);
}

// --- Cross-sign behavior (observable via public API spec) ---

TEST_F(ULPDistanceTest_196, CrossSignDistanceEqualsSumOfDistancesToZero_196) {
    const double a = 1.0;
    // Property derived from the public behavior:
    // ulpDistance(a, -a) == ulpDistance(|a|, 0) + ulpDistance(|a|, 0)
    const uint64_t to_zero = ulpDistance(std::fabs(a), 0.0);
    const uint64_t cross   = ulpDistance(a, -a);
    EXPECT_EQ(cross, to_zero + to_zero);
}

TEST_F(ULPDistanceTest_196, CrossSignForTinySubnormalTwiceDistanceToZero_196) {
    const double a = std::numeric_limits<double>::denorm_min();
    const uint64_t to_zero = ulpDistance(a, 0.0);   // expected 1
    const uint64_t cross   = ulpDistance(a, -a);    // expected 2
    EXPECT_EQ(to_zero, 1u);
    EXPECT_EQ(cross, 2u);
}

// --- Exceptional / error cases observable via interface (assertions) ---

#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
TEST_F(ULPDistanceTest_196, DiesOnNaNInput_196) {
    const double x = std::numeric_limits<double>::quiet_NaN();
    // The function asserts that distance with NaN is "not meaningful".
    EXPECT_DEATH({ (void)ulpDistance(x, 0.0); }, "");
    EXPECT_DEATH({ (void)ulpDistance(0.0, x); }, "");
}
#endif

} // namespace
