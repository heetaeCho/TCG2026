#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>

// Include the necessary headers from the Catch2 project
// We need the declarations for analyse_samples, bootstrap_analysis, Estimate, etc.

// Forward declarations based on the partial code provided
namespace Catch {
namespace Benchmark {

template <typename Type>
struct Estimate {
    Type point;
    Type lower_bound;
    Type upper_bound;
    double confidence_interval;
};

struct bootstrap_analysis {
    Estimate<double> mean;
    Estimate<double> standard_deviation;
    double outlier_variance;
};

namespace Detail {
    bootstrap_analysis analyse_samples(double confidence_level,
                                        unsigned int n_resamples,
                                        double* first,
                                        double* last);
    double mean(double const* first, double const* last);
    double standard_deviation(double const* first, double const* last);
}
}
}

// If the above forward declarations conflict with the actual headers, 
// include the real headers instead:
// #include "catch_amalgamated.hpp"

class AnalyseSamplesTest_991 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Normal operation with a simple uniform dataset
TEST_F(AnalyseSamplesTest_991, NormalOperationUniformData_991) {
    std::vector<double> samples = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 100, samples.data(), samples.data() + samples.size());
    
    // The mean estimate point should be close to 5.5
    EXPECT_NEAR(result.mean.point, 5.5, 0.01);
    
    // Mean lower_bound should be <= point and upper_bound >= point
    EXPECT_LE(result.mean.lower_bound, result.mean.point);
    EXPECT_GE(result.mean.upper_bound, result.mean.point);
    
    // Standard deviation should be positive
    EXPECT_GT(result.standard_deviation.point, 0.0);
    EXPECT_LE(result.standard_deviation.lower_bound, result.standard_deviation.point);
    EXPECT_GE(result.standard_deviation.upper_bound, result.standard_deviation.point);
    
    // Outlier variance should be between 0 and 1 (or at least non-negative)
    EXPECT_GE(result.outlier_variance, 0.0);
    EXPECT_LE(result.outlier_variance, 1.0);
    
    // Confidence interval should match what was requested
    EXPECT_DOUBLE_EQ(result.mean.confidence_interval, 0.95);
    EXPECT_DOUBLE_EQ(result.standard_deviation.confidence_interval, 0.95);
}

// Test: All identical values (zero standard deviation case)
TEST_F(AnalyseSamplesTest_991, AllIdenticalValues_991) {
    std::vector<double> samples = {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0};
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 100, samples.data(), samples.data() + samples.size());
    
    // Mean should be exactly 5.0
    EXPECT_DOUBLE_EQ(result.mean.point, 5.0);
    
    // Standard deviation should be 0 or very close to 0
    EXPECT_NEAR(result.standard_deviation.point, 0.0, 1e-10);
}

// Test: Two elements (minimum meaningful dataset)
TEST_F(AnalyseSamplesTest_991, TwoElements_991) {
    std::vector<double> samples = {1.0, 3.0};
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 100, samples.data(), samples.data() + samples.size());
    
    // Mean should be 2.0
    EXPECT_NEAR(result.mean.point, 2.0, 0.01);
    
    // Standard deviation should be positive
    EXPECT_GT(result.standard_deviation.point, 0.0);
}

// Test: Single element
TEST_F(AnalyseSamplesTest_991, SingleElement_991) {
    std::vector<double> samples = {42.0};
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 100, samples.data(), samples.data() + samples.size());
    
    // Mean should be 42.0
    EXPECT_DOUBLE_EQ(result.mean.point, 42.0);
    
    // Standard deviation should be 0 for a single element
    EXPECT_NEAR(result.standard_deviation.point, 0.0, 1e-10);
}

// Test: Large dataset
TEST_F(AnalyseSamplesTest_991, LargeDataset_991) {
    std::vector<double> samples(1000);
    for (int i = 0; i < 1000; ++i) {
        samples[i] = static_cast<double>(i + 1);
    }
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 200, samples.data(), samples.data() + samples.size());
    
    // Mean should be close to 500.5
    EXPECT_NEAR(result.mean.point, 500.5, 0.01);
    
    // Standard deviation should be positive and reasonable
    EXPECT_GT(result.standard_deviation.point, 0.0);
    
    // Bounds should make sense
    EXPECT_LE(result.mean.lower_bound, result.mean.upper_bound);
    EXPECT_LE(result.standard_deviation.lower_bound, result.standard_deviation.upper_bound);
}

// Test: Different confidence levels
TEST_F(AnalyseSamplesTest_991, DifferentConfidenceLevel_991) {
    std::vector<double> samples = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    
    auto result_90 = Catch::Benchmark::Detail::analyse_samples(
        0.90, 100, samples.data(), samples.data() + samples.size());
    
    auto result_99 = Catch::Benchmark::Detail::analyse_samples(
        0.99, 100, samples.data(), samples.data() + samples.size());
    
    // Both should have the same point estimate for mean
    EXPECT_DOUBLE_EQ(result_90.mean.point, result_99.mean.point);
    
    // Confidence intervals should reflect the requested level
    EXPECT_DOUBLE_EQ(result_90.mean.confidence_interval, 0.90);
    EXPECT_DOUBLE_EQ(result_99.mean.confidence_interval, 0.99);
}

// Test: Negative values in samples
TEST_F(AnalyseSamplesTest_991, NegativeValues_991) {
    std::vector<double> samples = {-5.0, -3.0, -1.0, 1.0, 3.0, 5.0};
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 100, samples.data(), samples.data() + samples.size());
    
    // Mean should be close to 0
    EXPECT_NEAR(result.mean.point, 0.0, 0.01);
    
    // Standard deviation should be positive
    EXPECT_GT(result.standard_deviation.point, 0.0);
}

// Test: Very small values (near zero)
TEST_F(AnalyseSamplesTest_991, VerySmallValues_991) {
    std::vector<double> samples = {1e-10, 2e-10, 3e-10, 4e-10, 5e-10};
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 100, samples.data(), samples.data() + samples.size());
    
    EXPECT_NEAR(result.mean.point, 3e-10, 1e-12);
    EXPECT_GT(result.standard_deviation.point, 0.0);
}

// Test: Very large values
TEST_F(AnalyseSamplesTest_991, VeryLargeValues_991) {
    std::vector<double> samples = {1e10, 2e10, 3e10, 4e10, 5e10};
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 100, samples.data(), samples.data() + samples.size());
    
    EXPECT_NEAR(result.mean.point, 3e10, 1e7);
    EXPECT_GT(result.standard_deviation.point, 0.0);
}

// Test: Number of resamples = 1 (edge case)
TEST_F(AnalyseSamplesTest_991, MinimumResamples_991) {
    std::vector<double> samples = {1.0, 2.0, 3.0, 4.0, 5.0};
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 1, samples.data(), samples.data() + samples.size());
    
    // Mean point estimate should still be correct
    EXPECT_NEAR(result.mean.point, 3.0, 0.01);
}

// Test: High number of resamples
TEST_F(AnalyseSamplesTest_991, HighResamples_991) {
    std::vector<double> samples = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 10000, samples.data(), samples.data() + samples.size());
    
    // Mean should still be accurate
    EXPECT_NEAR(result.mean.point, 5.5, 0.01);
    
    // With more resamples, confidence intervals should be well-formed
    EXPECT_LE(result.mean.lower_bound, result.mean.point);
    EXPECT_GE(result.mean.upper_bound, result.mean.point);
}

// Test: Result structure completeness
TEST_F(AnalyseSamplesTest_991, ResultStructureCompleteness_991) {
    std::vector<double> samples = {2.0, 4.0, 6.0, 8.0, 10.0};
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 100, samples.data(), samples.data() + samples.size());
    
    // Verify all fields of the result are populated with finite values
    EXPECT_TRUE(std::isfinite(result.mean.point));
    EXPECT_TRUE(std::isfinite(result.mean.lower_bound));
    EXPECT_TRUE(std::isfinite(result.mean.upper_bound));
    EXPECT_TRUE(std::isfinite(result.mean.confidence_interval));
    
    EXPECT_TRUE(std::isfinite(result.standard_deviation.point));
    EXPECT_TRUE(std::isfinite(result.standard_deviation.lower_bound));
    EXPECT_TRUE(std::isfinite(result.standard_deviation.upper_bound));
    EXPECT_TRUE(std::isfinite(result.standard_deviation.confidence_interval));
    
    EXPECT_TRUE(std::isfinite(result.outlier_variance));
}

// Test: Samples with outliers
TEST_F(AnalyseSamplesTest_991, SamplesWithOutliers_991) {
    std::vector<double> samples = {1.0, 1.1, 1.0, 0.9, 1.0, 1.1, 0.9, 1.0, 100.0, 1.0};
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 100, samples.data(), samples.data() + samples.size());
    
    // The outlier variance should reflect the presence of outliers
    // It should be non-negative
    EXPECT_GE(result.outlier_variance, 0.0);
    
    // Mean should be pulled toward the outlier
    double expected_mean = std::accumulate(samples.begin(), samples.end(), 0.0) / samples.size();
    EXPECT_NEAR(result.mean.point, expected_mean, 0.01);
}

// Test: Monotonically increasing samples
TEST_F(AnalyseSamplesTest_991, MonotonicallyIncreasingValues_991) {
    std::vector<double> samples;
    for (int i = 1; i <= 20; ++i) {
        samples.push_back(static_cast<double>(i));
    }
    
    auto result = Catch::Benchmark::Detail::analyse_samples(
        0.95, 500, samples.data(), samples.data() + samples.size());
    
    EXPECT_NEAR(result.mean.point, 10.5, 0.01);
    EXPECT_GT(result.standard_deviation.point, 0.0);
    EXPECT_LE(result.mean.lower_bound, result.mean.upper_bound);
}

// Test: Consistency - running twice with same data should give same point estimates
TEST_F(AnalyseSamplesTest_991, ConsistentPointEstimates_991) {
    std::vector<double> samples = {3.0, 5.0, 7.0, 9.0, 11.0};
    
    auto result1 = Catch::Benchmark::Detail::analyse_samples(
        0.95, 100, samples.data(), samples.data() + samples.size());
    
    auto result2 = Catch::Benchmark::Detail::analyse_samples(
        0.95, 100, samples.data(), samples.data() + samples.size());
    
    // Point estimates should be deterministic (same data -> same point estimate)
    EXPECT_DOUBLE_EQ(result1.mean.point, result2.mean.point);
    EXPECT_DOUBLE_EQ(result1.standard_deviation.point, result2.standard_deviation.point);
}
