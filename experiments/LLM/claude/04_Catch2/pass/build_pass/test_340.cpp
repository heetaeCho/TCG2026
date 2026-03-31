#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <cstdint>

// Include the header under test
#include "catch2/internal/catch_random_floating_point_helpers.hpp"

// DistanceType is typically an unsigned integer type matching the float size
// We need to understand the interface: count_equidistant_floats(a, b, distance)
// counts how many equidistant floats (multiples of distance) fit in [a, b].

using Catch::Detail::count_equidistant_floats;

// =============================================================================
// Tests for double
// =============================================================================

class CountEquidistantFloatsDoubleTest_340 : public ::testing::Test {};

TEST_F(CountEquidistantFloatsDoubleTest_340, SamePointReturnsOneOrZero_340) {
    // When a == b, the interval is a single point.
    // If a is a multiple of distance, there's 1 point; otherwise could be 0 or 1.
    auto result = count_equidistant_floats(0.0, 0.0, 1.0);
    // 0.0 is a multiple of 1.0, so ceil(0) = 0, and err check applies
    // The exact result depends on the implementation
    EXPECT_GE(result, 0u);
    EXPECT_LE(result, 1u);
}

TEST_F(CountEquidistantFloatsDoubleTest_340, UnitIntervalUnitDistance_340) {
    // [0, 1] with distance 1: points at 0 and 1 => expect 1 (since bg - ag = 1, ceil(1) = 1)
    auto result = count_equidistant_floats(0.0, 1.0, 1.0);
    EXPECT_GE(result, 1u);
    EXPECT_LE(result, 2u);
}

TEST_F(CountEquidistantFloatsDoubleTest_340, SimpleIntegerInterval_340) {
    // [0, 10] with distance 1.0: points at 0,1,2,...,10 => 10 intervals, ceil(10) = 10
    auto result = count_equidistant_floats(0.0, 10.0, 1.0);
    EXPECT_GE(result, 10u);
    EXPECT_LE(result, 11u);
}

TEST_F(CountEquidistantFloatsDoubleTest_340, HalfDistanceInUnitInterval_340) {
    // [0, 1] with distance 0.5: points at 0, 0.5, 1.0 => 2 intervals
    auto result = count_equidistant_floats(0.0, 1.0, 0.5);
    EXPECT_GE(result, 2u);
    EXPECT_LE(result, 3u);
}

TEST_F(CountEquidistantFloatsDoubleTest_340, DistanceLargerThanInterval_340) {
    // [0, 0.5] with distance 1.0: only 0.0 fits (or none beyond start)
    auto result = count_equidistant_floats(0.0, 0.5, 1.0);
    EXPECT_GE(result, 0u);
    EXPECT_LE(result, 1u);
}

TEST_F(CountEquidistantFloatsDoubleTest_340, NegativeToPositiveInterval_340) {
    // [-5, 5] with distance 1.0: points -5,-4,...,0,...,4,5 => 10 intervals
    auto result = count_equidistant_floats(-5.0, 5.0, 1.0);
    EXPECT_GE(result, 10u);
    EXPECT_LE(result, 11u);
}

TEST_F(CountEquidistantFloatsDoubleTest_340, NegativeInterval_340) {
    // [-10, -1] with distance 1.0: 9 intervals
    auto result = count_equidistant_floats(-10.0, -1.0, 1.0);
    EXPECT_GE(result, 9u);
    EXPECT_LE(result, 10u);
}

TEST_F(CountEquidistantFloatsDoubleTest_340, SmallDistanceInSmallInterval_340) {
    // [0, 1] with distance 0.1
    auto result = count_equidistant_floats(0.0, 1.0, 0.1);
    EXPECT_GE(result, 9u);
    EXPECT_LE(result, 11u);
}

TEST_F(CountEquidistantFloatsDoubleTest_340, VerySmallInterval_340) {
    // [1.0, 1.0 + 1e-10] with distance 1e-11
    double a = 1.0;
    double b = 1.0 + 1e-10;
    double distance = 1e-11;
    auto result = count_equidistant_floats(a, b, distance);
    EXPECT_GE(result, 9u);
    EXPECT_LE(result, 11u);
}

TEST_F(CountEquidistantFloatsDoubleTest_340, LargeInterval_340) {
    // [0, 1000000] with distance 1.0
    auto result = count_equidistant_floats(0.0, 1000000.0, 1.0);
    EXPECT_EQ(result, 1000000u);
}

TEST_F(CountEquidistantFloatsDoubleTest_340, DistanceEqualsIntervalLength_340) {
    // [0, 5] with distance 5.0: exactly one step
    auto result = count_equidistant_floats(0.0, 5.0, 5.0);
    EXPECT_GE(result, 1u);
    EXPECT_LE(result, 2u);
}

TEST_F(CountEquidistantFloatsDoubleTest_340, NonAlignedBoundaries_340) {
    // [0.3, 0.7] with distance 0.25: 0.25 < 0.3, 0.5 in range, 0.75 > 0.7 => ~1 point in interior
    auto result = count_equidistant_floats(0.3, 0.7, 0.25);
    EXPECT_GE(result, 1u);
    EXPECT_LE(result, 2u);
}

TEST_F(CountEquidistantFloatsDoubleTest_340, SymmetricAroundZero_340) {
    // [-1, 1] with distance 0.5: points at -1, -0.5, 0, 0.5, 1 => 4 intervals
    auto result = count_equidistant_floats(-1.0, 1.0, 0.5);
    EXPECT_GE(result, 3u);
    EXPECT_LE(result, 5u);
}

// =============================================================================
// Tests for float
// =============================================================================

class CountEquidistantFloatsFloatTest_340 : public ::testing::Test {};

TEST_F(CountEquidistantFloatsFloatTest_340, UnitIntervalUnitDistance_340) {
    auto result = count_equidistant_floats(0.0f, 1.0f, 1.0f);
    EXPECT_GE(result, 1u);
    EXPECT_LE(result, 2u);
}

TEST_F(CountEquidistantFloatsFloatTest_340, SimpleIntegerInterval_340) {
    auto result = count_equidistant_floats(0.0f, 10.0f, 1.0f);
    EXPECT_GE(result, 10u);
    EXPECT_LE(result, 11u);
}

TEST_F(CountEquidistantFloatsFloatTest_340, HalfDistance_340) {
    auto result = count_equidistant_floats(0.0f, 1.0f, 0.5f);
    EXPECT_GE(result, 2u);
    EXPECT_LE(result, 3u);
}

TEST_F(CountEquidistantFloatsFloatTest_340, NegativeToPositive_340) {
    auto result = count_equidistant_floats(-5.0f, 5.0f, 1.0f);
    EXPECT_GE(result, 10u);
    EXPECT_LE(result, 11u);
}

TEST_F(CountEquidistantFloatsFloatTest_340, SamePoint_340) {
    auto result = count_equidistant_floats(0.0f, 0.0f, 1.0f);
    EXPECT_GE(result, 0u);
    EXPECT_LE(result, 1u);
}

TEST_F(CountEquidistantFloatsFloatTest_340, LargeDistanceSmallInterval_340) {
    auto result = count_equidistant_floats(0.0f, 0.1f, 1.0f);
    EXPECT_GE(result, 0u);
    EXPECT_LE(result, 1u);
}

// =============================================================================
// Boundary / edge case tests
// =============================================================================

class CountEquidistantFloatsBoundaryTest_340 : public ::testing::Test {};

TEST_F(CountEquidistantFloatsBoundaryTest_340, VeryLargeValues_340) {
    // Large but finite values
    double a = 1e15;
    double b = 1e15 + 1e6;
    double distance = 1.0;
    auto result = count_equidistant_floats(a, b, distance);
    // Due to floating point precision at large values, result may vary
    EXPECT_GT(result, 0u);
}

TEST_F(CountEquidistantFloatsBoundaryTest_340, VerySmallDistance_340) {
    double a = 0.0;
    double b = 1e-5;
    double distance = 1e-6;
    auto result = count_equidistant_floats(a, b, distance);
    EXPECT_GE(result, 9u);
    EXPECT_LE(result, 11u);
}

TEST_F(CountEquidistantFloatsBoundaryTest_340, ExactMultiples_340) {
    // [0, 6] with distance 2.0: points at 0, 2, 4, 6 => 3 intervals
    auto result = count_equidistant_floats(0.0, 6.0, 2.0);
    EXPECT_GE(result, 3u);
    EXPECT_LE(result, 4u);
}

TEST_F(CountEquidistantFloatsBoundaryTest_340, PowerOfTwoDistance_340) {
    // [0, 8] with distance 0.25: 32 intervals
    auto result = count_equidistant_floats(0.0, 8.0, 0.25);
    EXPECT_EQ(result, 32u);
}

TEST_F(CountEquidistantFloatsBoundaryTest_340, NearZeroCrossing_340) {
    // [-1e-15, 1e-15] with distance 1e-16
    auto result = count_equidistant_floats(-1e-15, 1e-15, 1e-16);
    EXPECT_GE(result, 19u);
    EXPECT_LE(result, 21u);
}

TEST_F(CountEquidistantFloatsBoundaryTest_340, IntervalIsExactlyOneStep_340) {
    // [2.0, 2.5] with distance 0.5
    auto result = count_equidistant_floats(2.0, 2.5, 0.5);
    EXPECT_GE(result, 1u);
    EXPECT_LE(result, 2u);
}

TEST_F(CountEquidistantFloatsBoundaryTest_340, TwoSteps_340) {
    // [0, 2] with distance 1.0: steps 0->1->2, 2 steps
    auto result = count_equidistant_floats(0.0, 2.0, 1.0);
    EXPECT_EQ(result, 2u);
}

TEST_F(CountEquidistantFloatsBoundaryTest_340, ThreeStepsPowerOfTwo_340) {
    // [0, 3] with distance 1.0: steps 0->1->2->3, 3 steps
    auto result = count_equidistant_floats(0.0, 3.0, 1.0);
    EXPECT_EQ(result, 3u);
}

TEST_F(CountEquidistantFloatsBoundaryTest_340, FractionsThatDontDivideEvenly_340) {
    // [0, 1] with distance 0.3: 0, 0.3, 0.6, 0.9 fit, 1.2 doesn't => ceil(1/0.3) = ceil(3.33) = 4
    auto result = count_equidistant_floats(0.0, 1.0, 0.3);
    EXPECT_GE(result, 3u);
    EXPECT_LE(result, 4u);
}
