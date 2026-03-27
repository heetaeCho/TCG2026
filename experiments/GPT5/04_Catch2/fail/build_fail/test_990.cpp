// File: tests/benchmark_bootstrap_tests_990.cpp

#include <gtest/gtest.h>

// Use Catch2's amalgamated header so the public types and the function under test are visible.
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Benchmark::Detail::bootstrap;

// Simple external estimators to pass into `bootstrap` (collaborators, not re-impls of bootstrap).
namespace {
double MeanEstimator(const double* first, const double* last) {
    const auto n = static_cast<size_t>(last - first);
    double s = 0.0;
    for (auto p = first; p != last; ++p) s += *p;
    return n ? (s / static_cast<double>(n)) : 0.0;
}

double FirstValueEstimator(const double* first, const double* /*last*/) {
    return *first;
}
} // namespace

// Test fixture (kept minimal; no private/internal state is accessed).
class BootstrapTest_990 : public ::testing::Test {};

// [Normal] Single sample => returns (point, point, point, confidence)
TEST_F(BootstrapTest_990, SingleSampleReturnsPointTriplet_990) {
    double data[] = { 5.0 };
    // `resample` can be anything; it won't be used due to early return on n_samples == 1.
    std::vector<double> resample = { 1.0, 2.0, 3.0 };
    const double cl = 0.95;

    auto est = bootstrap(cl, /*first*/ &data[0], /*last*/ &data[1],
                         /*resample*/ resample, /*estimator*/ &MeanEstimator);

    // Observable behavior: all components equal to the estimator's point when only 1 sample.
    EXPECT_DOUBLE_EQ(est.point, 5.0);
    EXPECT_DOUBLE_EQ(est.lower, 5.0);
    EXPECT_DOUBLE_EQ(est.upper, 5.0);
    EXPECT_DOUBLE_EQ(est.confidence_level, cl);
}

// [Exceptional/degenerate] prob_n == 0 path => returns (point, point, point, confidence)
// Construct data so the point estimate is below all resample values.
TEST_F(BootstrapTest_990, ProbZeroReturnsPointTriplet_990) {
    // Two samples to avoid the early return on n_samples == 1.
    double data[] = { 1.0, 1.0 }; // MeanEstimator => point = 1.0
    // All resample values are >= point (strictly greater ensures prob_n == 0).
    std::vector<double> resample = { 2.0, 3.0, 4.0, 5.0 };
    const double cl = 0.90;

    auto est = bootstrap(cl, &data[0], &data[2], resample, &MeanEstimator);

    // Observable degenerate behavior asserted by interface: identical triplet and confidence passthrough.
    EXPECT_DOUBLE_EQ(est.point, 1.0);
    EXPECT_DOUBLE_EQ(est.lower, 1.0);
    EXPECT_DOUBLE_EQ(est.upper, 1.0);
    EXPECT_DOUBLE_EQ(est.confidence_level, cl);
}

// [Boundary] resample has size 1 => indices are clamped into [0, n-1] and both bounds equal resample[0].
// Ensure we do not take the n_samples==1 early-exit by providing 2 samples in `data`.
TEST_F(BootstrapTest_990, ResampleIndexClampingWhenNEqualsOne_990) {
    double data[] = { 10.0, 30.0 }; // MeanEstimator => point = 20.0
    // Single-element resample; regardless of computed indices, lo and hi must clamp to 0.
    std::vector<double> resample = { -100.0 };
    const double cl = 0.80;

    auto est = bootstrap(cl, &data[0], &data[2], resample, &MeanEstimator);

    EXPECT_DOUBLE_EQ(est.point, 20.0);
    // Both bounds must come from the only available resample element.
    EXPECT_DOUBLE_EQ(est.lower, resample[0]);
    EXPECT_DOUBLE_EQ(est.upper, resample[0]);
    EXPECT_DOUBLE_EQ(est.confidence_level, cl);
}

// [Normal] Non-degenerate run: validates general invariants (no exact quantile math assumptions).
// - point equals estimator(first,last)
// - lower/upper come from `resample`
// - lower <= upper (given sorted resample input it should hold; we assert membership + ordering)
TEST_F(BootstrapTest_990, ReturnsBoundsFromResampleAndKeepsPoint_990) {
    // Use a simple dataset and an estimator we control.
    double data[] = { 2.0, 4.0, 6.0 }; // MeanEstimator => point = 4.0
    // Provide a sorted resample vector to make bounds ordering meaningful.
    std::vector<double> resample = { -5.0, -1.0, 0.0, 1.0, 2.5, 4.0, 7.0, 9.0, 11.0, 13.0 };
    const double cl = 0.95;

    auto est = bootstrap(cl, &data[0], &data[3], resample, &MeanEstimator);

    // Point must equal the estimator's result (observable via return value).
    EXPECT_DOUBLE_EQ(est.point, 4.0);

    // Bounds must come from the provided resample (observable via equality to some element).
    auto in_resample = [&](double v) {
        return std::find(resample.begin(), resample.end(), v) != resample.end();
    };
    EXPECT_TRUE(in_resample(est.lower));
    EXPECT_TRUE(in_resample(est.upper));

    // Confidence level is passed through.
    EXPECT_DOUBLE_EQ(est.confidence_level, cl);

    // For a sorted resample, we expect lower <= upper.
    EXPECT_LE(est.lower, est.upper);
}

// [Normal] Different estimator collaborator is honored (verifies external interaction via returned point).
TEST_F(BootstrapTest_990, UsesProvidedEstimatorCollaborator_990) {
    // Craft data where the first value differs from the mean.
    double data[] = { 100.0, 0.0, 0.0 }; // Mean would be ~33.333..., first value is 100.
    // Make resample benign; we don't assert its exact quantiles here.
    std::vector<double> resample = { -10.0, 0.0, 10.0, 20.0, 30.0 };
    const double cl = 0.90;

    auto est_first = bootstrap(cl, &data[0], &data[3], resample, &FirstValueEstimator);
    auto est_mean  = bootstrap(cl, &data[0], &data[3], resample, &MeanEstimator);

    // Observable difference proves `bootstrap` invoked the given estimator (external collaborator).
    EXPECT_DOUBLE_EQ(est_first.point, 100.0);
    EXPECT_NE(est_first.point, est_mean.point);

    // Sanity on confidence passthrough.
    EXPECT_DOUBLE_EQ(est_first.confidence_level, cl);
    EXPECT_DOUBLE_EQ(est_mean.confidence_level, cl);
}
