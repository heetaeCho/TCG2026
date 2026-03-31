#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

// We need to include the Catch2 amalgamated header to access the bootstrap function
// and related types
#include "catch_amalgamated.hpp"

using namespace Catch::Benchmark::Detail;

// Helper estimator functions
static double mean_estimator(double const* first, double const* last) {
    if (first == last) return 0.0;
    double sum = 0.0;
    auto n = last - first;
    for (auto it = first; it != last; ++it) {
        sum += *it;
    }
    return sum / static_cast<double>(n);
}

static double median_estimator(double const* first, double const* last) {
    auto n = last - first;
    if (n == 0) return 0.0;
    std::vector<double> sorted(first, last);
    std::sort(sorted.begin(), sorted.end());
    if (n % 2 == 0) {
        return (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
    }
    return sorted[n / 2];
}

static double constant_estimator(double const* first, double const* /*last*/) {
    return *first;
}

class BootstrapTest_990 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Single sample should return point estimate for all fields
TEST_F(BootstrapTest_990, SingleSampleReturnsPointForAll_990) {
    double data[] = {42.0};
    std::vector<double> resample = {42.0, 42.0, 42.0, 42.0, 42.0};
    double confidence = 0.95;

    auto result = bootstrap(confidence, data, data + 1, resample, mean_estimator);

    EXPECT_DOUBLE_EQ(result.point, 42.0);
    EXPECT_DOUBLE_EQ(result.lower_bound, 42.0);
    EXPECT_DOUBLE_EQ(result.upper_bound, 42.0);
    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
}

// Test: Normal operation with multiple samples
TEST_F(BootstrapTest_990, MultipleSamplesNormalOperation_990) {
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    // Create a sorted resample
    std::vector<double> resample;
    for (int i = 0; i < 1000; ++i) {
        resample.push_back(1.0 + 4.0 * static_cast<double>(i) / 999.0);
    }
    std::sort(resample.begin(), resample.end());
    double confidence = 0.95;

    auto result = bootstrap(confidence, data, data + 5, resample, mean_estimator);

    EXPECT_DOUBLE_EQ(result.point, 3.0);
    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
    // Lower bound should be <= point, upper bound should be >= point (or at least within resample range)
    EXPECT_LE(result.lower_bound, result.upper_bound);
}

// Test: Confidence level is preserved in the result
TEST_F(BootstrapTest_990, ConfidenceLevelIsPreserved_990) {
    double data[] = {10.0, 20.0, 30.0};
    std::vector<double> resample;
    for (int i = 0; i < 500; ++i) {
        resample.push_back(10.0 + 20.0 * static_cast<double>(i) / 499.0);
    }
    std::sort(resample.begin(), resample.end());

    double confidence = 0.99;
    auto result = bootstrap(confidence, data, data + 3, resample, mean_estimator);

    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
}

// Test: All identical data should return point for all bounds
TEST_F(BootstrapTest_990, AllIdenticalDataPointReturned_990) {
    double data[] = {5.0, 5.0, 5.0, 5.0, 5.0};
    // All resample values are below the point (none are < 5.0 if all equal 5.0)
    // prob_n = 0 case
    std::vector<double> resample(100, 5.0);

    double confidence = 0.95;
    auto result = bootstrap(confidence, data, data + 5, resample, mean_estimator);

    EXPECT_DOUBLE_EQ(result.point, 5.0);
    // When prob_n == 0, all bounds equal point
    EXPECT_DOUBLE_EQ(result.lower_bound, 5.0);
    EXPECT_DOUBLE_EQ(result.upper_bound, 5.0);
    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
}

// Test: Two samples
TEST_F(BootstrapTest_990, TwoSamplesOperation_990) {
    double data[] = {1.0, 3.0};
    std::vector<double> resample;
    for (int i = 0; i < 200; ++i) {
        resample.push_back(1.0 + 2.0 * static_cast<double>(i) / 199.0);
    }
    std::sort(resample.begin(), resample.end());

    double confidence = 0.95;
    auto result = bootstrap(confidence, data, data + 2, resample, mean_estimator);

    EXPECT_DOUBLE_EQ(result.point, 2.0);
    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
}

// Test: Different estimator (median)
TEST_F(BootstrapTest_990, MedianEstimator_990) {
    double data[] = {1.0, 2.0, 3.0, 4.0, 100.0};
    std::vector<double> resample;
    for (int i = 0; i < 500; ++i) {
        resample.push_back(1.0 + 99.0 * static_cast<double>(i) / 499.0);
    }
    std::sort(resample.begin(), resample.end());

    double confidence = 0.95;
    auto result = bootstrap(confidence, data, data + 5, resample, median_estimator);

    EXPECT_DOUBLE_EQ(result.point, 3.0);
    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
}

// Test: Low confidence level
TEST_F(BootstrapTest_990, LowConfidenceLevel_990) {
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> resample;
    for (int i = 0; i < 1000; ++i) {
        resample.push_back(1.0 + 4.0 * static_cast<double>(i) / 999.0);
    }
    std::sort(resample.begin(), resample.end());

    double confidence = 0.50;
    auto result = bootstrap(confidence, data, data + 5, resample, mean_estimator);

    EXPECT_DOUBLE_EQ(result.point, 3.0);
    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
    // With lower confidence, the interval should be narrower
    EXPECT_LE(result.lower_bound, result.upper_bound);
}

// Test: Resample all below point triggers prob_n = 1.0
TEST_F(BootstrapTest_990, ResampleAllBelowPoint_990) {
    double data[] = {10.0, 20.0, 30.0};
    // Mean is 20. All resample values below 20
    std::vector<double> resample(100, 19.0);
    std::sort(resample.begin(), resample.end());

    double confidence = 0.95;
    auto result = bootstrap(confidence, data, data + 3, resample, mean_estimator);

    EXPECT_DOUBLE_EQ(result.point, 20.0);
    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
}

// Test: Resample with no values below point (prob_n == 0)
TEST_F(BootstrapTest_990, ResampleNoBelowPoint_990) {
    double data[] = {10.0, 20.0, 30.0};
    // Mean is 20. All resample values >= 20
    std::vector<double> resample(100, 25.0);

    double confidence = 0.95;
    auto result = bootstrap(confidence, data, data + 3, resample, mean_estimator);

    // prob_n == 0 triggers early return
    EXPECT_DOUBLE_EQ(result.point, 20.0);
    EXPECT_DOUBLE_EQ(result.lower_bound, 20.0);
    EXPECT_DOUBLE_EQ(result.upper_bound, 20.0);
    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
}

// Test: Large dataset
TEST_F(BootstrapTest_990, LargeDataset_990) {
    std::vector<double> data(100);
    std::iota(data.begin(), data.end(), 1.0); // 1, 2, ..., 100

    std::vector<double> resample;
    for (int i = 0; i < 5000; ++i) {
        resample.push_back(1.0 + 99.0 * static_cast<double>(i) / 4999.0);
    }
    std::sort(resample.begin(), resample.end());

    double confidence = 0.95;
    auto result = bootstrap(confidence, data.data(), data.data() + data.size(), resample, mean_estimator);

    EXPECT_DOUBLE_EQ(result.point, 50.5);
    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
    EXPECT_LE(result.lower_bound, result.upper_bound);
}

// Test: Resample half below, half above
TEST_F(BootstrapTest_990, ResampleHalfAndHalf_990) {
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double point = 3.0; // mean
    std::vector<double> resample;
    // 50 below, 50 at or above
    for (int i = 0; i < 50; ++i) {
        resample.push_back(2.0);
    }
    for (int i = 0; i < 50; ++i) {
        resample.push_back(4.0);
    }
    std::sort(resample.begin(), resample.end());

    double confidence = 0.95;
    auto result = bootstrap(confidence, data, data + 5, resample, mean_estimator);

    EXPECT_DOUBLE_EQ(result.point, 3.0);
    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
}

// Test: Verify bounds are within resample range for normal case
TEST_F(BootstrapTest_990, BoundsWithinResampleRange_990) {
    double data[] = {2.0, 4.0, 6.0, 8.0, 10.0};
    std::vector<double> resample;
    for (int i = 0; i < 1000; ++i) {
        resample.push_back(2.0 + 8.0 * static_cast<double>(i) / 999.0);
    }
    std::sort(resample.begin(), resample.end());

    double confidence = 0.95;
    auto result = bootstrap(confidence, data, data + 5, resample, mean_estimator);

    EXPECT_GE(result.lower_bound, resample.front());
    EXPECT_LE(result.upper_bound, resample.back());
}

// Test: Negative values in data
TEST_F(BootstrapTest_990, NegativeValues_990) {
    double data[] = {-5.0, -3.0, -1.0, 1.0, 3.0};
    std::vector<double> resample;
    for (int i = 0; i < 500; ++i) {
        resample.push_back(-5.0 + 8.0 * static_cast<double>(i) / 499.0);
    }
    std::sort(resample.begin(), resample.end());

    double confidence = 0.95;
    auto result = bootstrap(confidence, data, data + 5, resample, mean_estimator);

    EXPECT_DOUBLE_EQ(result.point, -1.0);
    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
}

// Test: Single sample with different confidence level
TEST_F(BootstrapTest_990, SingleSampleDifferentConfidence_990) {
    double data[] = {7.5};
    std::vector<double> resample = {7.5, 7.5, 7.5};
    double confidence = 0.80;

    auto result = bootstrap(confidence, data, data + 1, resample, mean_estimator);

    EXPECT_DOUBLE_EQ(result.point, 7.5);
    EXPECT_DOUBLE_EQ(result.lower_bound, 7.5);
    EXPECT_DOUBLE_EQ(result.upper_bound, 7.5);
    EXPECT_DOUBLE_EQ(result.confidence_interval, confidence);
}
