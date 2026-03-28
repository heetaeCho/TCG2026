// File: test_analyse_no_analysis_982.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include Catch2 amalgamated header so FDuration, SampleAnalysis, IConfig, etc. are defined
#include "Catch2/extras/catch_amalgamated.hpp"

using ::testing::NiceMock;
using ::testing::Return;

namespace {

/// GoogleMock for Catch::IConfig.
/// We provide overrides for the interface. Only methods used in these tests
/// are given explicit ON_CALL/EXPECT_CALL behaviors; the rest are left with
/// default gMock behaviors (they are not invoked by the code paths we test).
class MockConfig_982 : public Catch::IConfig {
public:
    // Destructor
    ~MockConfig_982() override = default;

    // The long list of virtual methods (matching Catch2's IConfig).
    // We mark them const & override; return values are dummies unless explicitly set.
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const Catch::TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD((const std::vector<std::string>&), getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD((const std::vector<std::string>&), getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

using FD = Catch::Benchmark::FDuration;  // duration type used by Catch2 benchmarks
using Catch::Benchmark::Detail::analyse;

struct AnalyseNoAnalysisTest_982 : public ::testing::Test {
    // Helper to compare two FDurations as doubles (by .count()).
    static void ExpectDurationEq(const FD& a, const FD& b) {
        EXPECT_DOUBLE_EQ(a.count(), b.count());
    }
};

} // namespace

// -----------------------------------------------------------------------------
// Normal operation: multiple samples, analysis disabled.
// Verifies that outputs mirror inputs and that statistics are set as specified
// by the observable "no analysis" branch behavior.
// -----------------------------------------------------------------------------
TEST_F(AnalyseNoAnalysisTest_982, MultipleSamples_NoAnalysis_ReturnsMeanAndZeroStdDev_982) {
    NiceMock<MockConfig_982> cfg;

    // External interaction: analyse should query benchmarkNoAnalysis() and take the "no analysis" path.
    EXPECT_CALL(cfg, benchmarkNoAnalysis())
        .Times(1)
        .WillOnce(Return(true));

    // Prepare a few sample durations
    std::vector<FD> input{
        FD(1.0), FD(3.0), FD(5.0), FD(7.0)
    };
    const double expected_mean =
        (1.0 + 3.0 + 5.0 + 7.0) / static_cast<double>(input.size());

    // Execute
    auto result = analyse(cfg, &input.front(), &input.front() + input.size());

    // Observable behavior checks:

    // 1) Samples are preserved in order and by value
    ASSERT_EQ(result.samples.size(), input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        ExpectDurationEq(result.samples[i], input[i]);
    }

    // 2) Mean estimate has point == lower == upper == arithmetic mean
    EXPECT_DOUBLE_EQ(result.mean.point.count(), expected_mean);
    EXPECT_DOUBLE_EQ(result.mean.lower_bound.count(), expected_mean);
    EXPECT_DOUBLE_EQ(result.mean.upper_bound.count(), expected_mean);
    EXPECT_DOUBLE_EQ(result.mean.confidence_interval, 0.0);

    // 3) Standard deviation estimate is all zeros in "no analysis" mode
    EXPECT_DOUBLE_EQ(result.standard_deviation.point.count(), 0.0);
    EXPECT_DOUBLE_EQ(result.standard_deviation.lower_bound.count(), 0.0);
    EXPECT_DOUBLE_EQ(result.standard_deviation.upper_bound.count(), 0.0);
    EXPECT_DOUBLE_EQ(result.standard_deviation.confidence_interval, 0.0);

    // 4) Outlier classification is default-constructed with zeros
    EXPECT_EQ(result.outliers.samples_seen, 0);
    EXPECT_EQ(result.outliers.low_severe, 0);
    EXPECT_EQ(result.outliers.low_mild, 0);
    EXPECT_EQ(result.outliers.high_mild, 0);
    EXPECT_EQ(result.outliers.high_severe, 0);

    // 5) Outlier variance is 0.0
    EXPECT_DOUBLE_EQ(result.outlier_variance, 0.0);
}

// -----------------------------------------------------------------------------
// Boundary condition: single sample, analysis disabled.
// Mean should equal that single value; stddev stays zero.
// -----------------------------------------------------------------------------
TEST_F(AnalyseNoAnalysisTest_982, SingleSample_NoAnalysis_MeanEqualsValue_982) {
    NiceMock<MockConfig_982> cfg;

    EXPECT_CALL(cfg, benchmarkNoAnalysis())
        .Times(1)
        .WillOnce(Return(true));

    std::vector<FD> input{ FD(42.5) };

    auto result = analyse(cfg, &input.front(), &input.front() + input.size());

    ASSERT_EQ(result.samples.size(), 1u);
    ExpectDurationEq(result.samples[0], FD(42.5));

    EXPECT_DOUBLE_EQ(result.mean.point.count(), 42.5);
    EXPECT_DOUBLE_EQ(result.mean.lower_bound.count(), 42.5);
    EXPECT_DOUBLE_EQ(result.mean.upper_bound.count(), 42.5);
    EXPECT_DOUBLE_EQ(result.mean.confidence_interval, 0.0);

    EXPECT_DOUBLE_EQ(result.standard_deviation.point.count(), 0.0);
    EXPECT_DOUBLE_EQ(result.standard_deviation.lower_bound.count(), 0.0);
    EXPECT_DOUBLE_EQ(result.standard_deviation.upper_bound.count(), 0.0);
    EXPECT_DOUBLE_EQ(result.standard_deviation.confidence_interval, 0.0);

    EXPECT_EQ(result.outliers.samples_seen, 0);
    EXPECT_EQ(result.outliers.low_severe, 0);
    EXPECT_EQ(result.outliers.low_mild, 0);
    EXPECT_EQ(result.outliers.high_mild, 0);
    EXPECT_EQ(result.outliers.high_severe, 0);

    EXPECT_DOUBLE_EQ(result.outlier_variance, 0.0);
}

// -----------------------------------------------------------------------------
// (Intentionally omitted): empty range behavior.
// The provided code divides by the number of elements; with an empty range, the
// behavior would be undefined/erroneous and is not exercised here to avoid
// relying on internal checks or UB that is not specified by the interface.
// -----------------------------------------------------------------------------
