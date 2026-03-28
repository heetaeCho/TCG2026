// File: tests/AnalyseSamples_991_Test.cpp

#include <gtest/gtest.h>
#include <cmath>
#include <vector>

// Keep usage constrained strictly to the public interface.
// We assume the function is available through the project's normal includes.
// If your build exposes the amalgamated interface header, prefer that here.
#include <catch2/catch_all.hpp>  // or the appropriate header that declares analyse_samples

// If your project uses non-amalgamated headers, the function lives in:
// Catch::Benchmark::Detail::analyse_samples

namespace {

using Catch::Benchmark::Estimate;

TEST(AnalyseSamplesTest_991, BasicFiniteEstimates_991) {
    // Normal operation: small sample range, typical confidence level & resamples.
    std::vector<double> data{1.0, 2.0, 3.0, 4.0, 5.0};
    const double confidence = 0.95;
    const unsigned int resamples = 100; // avoid excessive runtime while enabling bootstrap

    auto result = Catch::Benchmark::Detail::analyse_samples(
        confidence, resamples, data.data(), data.data() + data.size()
    );

    // Observable behavior checks only. We do NOT assert internal algorithmic results.
    // We only check properties any valid bootstrap analysis should satisfy.
    // Mean estimate should be finite.
    EXPECT_TRUE(std::isfinite(result.mean.point));
    EXPECT_TRUE(std::isfinite(result.mean.lower_bound));
    EXPECT_TRUE(std::isfinite(result.mean.upper_bound));
    EXPECT_TRUE(std::isfinite(result.mean.confidence_interval));

    // Stddev estimate should be finite.
    EXPECT_TRUE(std::isfinite(result.standard_deviation.point));
    EXPECT_TRUE(std::isfinite(result.standard_deviation.lower_bound));
    EXPECT_TRUE(std::isfinite(result.standard_deviation.upper_bound));
    EXPECT_TRUE(std::isfinite(result.standard_deviation.confidence_interval));

    // Confidence intervals should be within [0, 1].
    EXPECT_GE(result.mean.confidence_interval, 0.0);
    EXPECT_LE(result.mean.confidence_interval, 1.0);
    EXPECT_GE(result.standard_deviation.confidence_interval, 0.0);
    EXPECT_LE(result.standard_deviation.confidence_interval, 1.0);

    // Outlier variance should be finite (no assumption on sign/magnitude).
    EXPECT_TRUE(std::isfinite(result.outlier_variance));
}

TEST(AnalyseSamplesTest_991, SingleElementSample_StddevNearZero_991) {
    // Boundary condition: single-element sample. The standard deviation
    // should be ~0 by definition. We avoid assuming exact algorithm details
    // and only check closeness to 0 for the point estimate.
    double value = 42.0;
    std::vector<double> data{value};

    const double confidence = 0.90;
    const unsigned int resamples = 64;

    auto result = Catch::Benchmark::Detail::analyse_samples(
        confidence, resamples, data.data(), data.data() + data.size()
    );

    // Mean point should be close to the single value (observable behavior).
    // Tolerance chosen conservatively to avoid assuming internals.
    EXPECT_NEAR(result.mean.point, value, 1e-9);

    // Standard deviation point should be ~0 for a single repeated value.
    EXPECT_NEAR(result.standard_deviation.point, 0.0, 1e-12);

    // Finite checks for the rest.
    EXPECT_TRUE(std::isfinite(result.mean.lower_bound));
    EXPECT_TRUE(std::isfinite(result.mean.upper_bound));
    EXPECT_TRUE(std::isfinite(result.standard_deviation.lower_bound));
    EXPECT_TRUE(std::isfinite(result.standard_deviation.upper_bound));
    EXPECT_TRUE(std::isfinite(result.outlier_variance));

    // Confidence intervals within [0, 1].
    EXPECT_GE(result.mean.confidence_interval, 0.0);
    EXPECT_LE(result.mean.confidence_interval, 1.0);
    EXPECT_GE(result.standard_deviation.confidence_interval, 0.0);
    EXPECT_LE(result.standard_deviation.confidence_interval, 1.0);
}

TEST(AnalyseSamplesTest_991, MinimalResamples_DoesNotThrow_991) {
    // Boundary condition: minimal bootstrapping. We avoid asserting exact numbers
    // and check that the function completes and returns finite values.
    std::vector<double> data{10.0, 20.0, 30.0};
    const double confidence = 0.80;
    const unsigned int resamples = 1; // minimal non-zero

    auto result = Catch::Benchmark::Detail::analyse_samples(
        confidence, resamples, data.data(), data.data() + data.size()
    );

    EXPECT_TRUE(std::isfinite(result.mean.point));
    EXPECT_TRUE(std::isfinite(result.standard_deviation.point));
    EXPECT_TRUE(std::isfinite(result.outlier_variance));

    EXPECT_GE(result.mean.confidence_interval, 0.0);
    EXPECT_LE(result.mean.confidence_interval, 1.0);
    EXPECT_GE(result.standard_deviation.confidence_interval, 0.0);
    EXPECT_LE(result.standard_deviation.confidence_interval, 1.0);
}

TEST(AnalyseSamplesTest_991, LargerResamples_StillFinite_991) {
    // Stress-ish boundary (within reason for unit tests): more resamples.
    // This should not change correctness guarantees (still finite values).
    std::vector<double> data{3.0, 3.5, 4.0, 5.0, 100.0}; // include an outlier
    const double confidence = 0.99;
    const unsigned int resamples = 1000; // larger bootstrap count

    auto result = Catch::Benchmark::Detail::analyse_samples(
        confidence, resamples, data.data(), data.data() + data.size()
    );

    // Again, assert only observable, non-internal properties.
    EXPECT_TRUE(std::isfinite(result.mean.point));
    EXPECT_TRUE(std::isfinite(result.mean.lower_bound));
    EXPECT_TRUE(std::isfinite(result.mean.upper_bound));

    EXPECT_TRUE(std::isfinite(result.standard_deviation.point));
    EXPECT_TRUE(std::isfinite(result.standard_deviation.lower_bound));
    EXPECT_TRUE(std::isfinite(result.standard_deviation.upper_bound));

    EXPECT_TRUE(std::isfinite(result.outlier_variance));

    EXPECT_GE(result.mean.confidence_interval, 0.0);
    EXPECT_LE(result.mean.confidence_interval, 1.0);
    EXPECT_GE(result.standard_deviation.confidence_interval, 0.0);
    EXPECT_LE(result.standard_deviation.confidence_interval, 1.0);
}

} // namespace
