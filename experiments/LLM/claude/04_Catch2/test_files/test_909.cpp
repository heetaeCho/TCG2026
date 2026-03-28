#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <chrono>
#include <cmath>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark::Detail;

// Test fixture for estimate_clock_resolution tests
class EstimateClockResolutionTest_909 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Use steady_clock as a standard clock for testing
using TestClock = std::chrono::steady_clock;

// Test that estimate_clock_resolution returns a positive mean duration
TEST_F(EstimateClockResolutionTest_909, ReturnsPositiveMeanDuration_909) {
    auto result = estimate_clock_resolution<TestClock>(10);
    // The mean clock resolution should be a positive value
    EXPECT_GT(result.mean.count(), 0.0);
}

// Test with minimal iterations (1)
TEST_F(EstimateClockResolutionTest_909, WorksWithSingleIteration_909) {
    auto result = estimate_clock_resolution<TestClock>(1);
    EXPECT_GT(result.mean.count(), 0.0);
}

// Test with larger number of iterations
TEST_F(EstimateClockResolutionTest_909, WorksWithLargerIterations_909) {
    auto result = estimate_clock_resolution<TestClock>(100);
    EXPECT_GT(result.mean.count(), 0.0);
}

// Test that the result contains a valid outlier classification
TEST_F(EstimateClockResolutionTest_909, OutlierClassificationIsValid_909) {
    auto result = estimate_clock_resolution<TestClock>(10);
    // OutlierClassification should have non-negative counts
    EXPECT_GE(result.outliers.low_severe, 0);
    EXPECT_GE(result.outliers.low_mild, 0);
    EXPECT_GE(result.outliers.high_mild, 0);
    EXPECT_GE(result.outliers.high_severe, 0);
}

// Test that the mean is within a reasonable range (not absurdly large)
// Clock resolution should be less than 1 second for any reasonable clock
TEST_F(EstimateClockResolutionTest_909, MeanIsWithinReasonableRange_909) {
    auto result = estimate_clock_resolution<TestClock>(10);
    // Clock resolution should be less than 1 second
    EXPECT_LT(result.mean.count(), 1.0);
    // And greater than 0
    EXPECT_GT(result.mean.count(), 0.0);
}

// Test that the mean is finite (not NaN or infinity)
TEST_F(EstimateClockResolutionTest_909, MeanIsFinite_909) {
    auto result = estimate_clock_resolution<TestClock>(10);
    EXPECT_TRUE(std::isfinite(result.mean.count()));
}

// Test that calling estimate_clock_resolution multiple times gives consistent results
// (both should be positive and in a similar order of magnitude)
TEST_F(EstimateClockResolutionTest_909, ConsistentAcrossMultipleCalls_909) {
    auto result1 = estimate_clock_resolution<TestClock>(10);
    auto result2 = estimate_clock_resolution<TestClock>(10);

    EXPECT_GT(result1.mean.count(), 0.0);
    EXPECT_GT(result2.mean.count(), 0.0);

    // Both results should be within a factor of 100 of each other
    // (allowing for system variability)
    double ratio = result1.mean.count() / result2.mean.count();
    EXPECT_GT(ratio, 0.01);
    EXPECT_LT(ratio, 100.0);
}

// Test with high_resolution_clock
TEST_F(EstimateClockResolutionTest_909, WorksWithHighResolutionClock_909) {
    auto result = estimate_clock_resolution<std::chrono::high_resolution_clock>(10);
    EXPECT_GT(result.mean.count(), 0.0);
    EXPECT_TRUE(std::isfinite(result.mean.count()));
}

// Test that outlier counts sum is non-negative and reasonable
TEST_F(EstimateClockResolutionTest_909, OutlierTotalSamplesNonNegative_909) {
    auto result = estimate_clock_resolution<TestClock>(10);
    int total_outliers = result.outliers.low_severe + result.outliers.low_mild +
                         result.outliers.high_mild + result.outliers.high_severe;
    EXPECT_GE(total_outliers, 0);
    // Total outliers should also have a samples_seen that is >= total_outliers
    EXPECT_GE(result.outliers.samples_seen, total_outliers);
}

// Test that the global constant clock_resolution_estimation_time is 500ms
TEST_F(EstimateClockResolutionTest_909, ClockResolutionEstimationTimeIs500ms_909) {
    EXPECT_EQ(clock_resolution_estimation_time.count(), 500);
}

// Test with a moderate iteration count
TEST_F(EstimateClockResolutionTest_909, WorksWithModerateIterations_909) {
    auto result = estimate_clock_resolution<TestClock>(50);
    EXPECT_GT(result.mean.count(), 0.0);
    EXPECT_TRUE(std::isfinite(result.mean.count()));
    EXPECT_GE(result.outliers.samples_seen, 0);
}
