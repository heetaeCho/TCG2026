#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <chrono>
#include <vector>
#include <string>

// Include necessary Catch2 headers
#include "catch_amalgamated.hpp"

using namespace Catch::Benchmark;
using namespace Catch::Benchmark::Detail;
using FDuration = Catch::Benchmark::FDuration;

// Mock IConfig
class MockConfig : public Catch::IConfig {
public:
    ~MockConfig() override = default;

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
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class AnalyseTest_982 : public ::testing::Test {
protected:
    MockConfig config;

    void SetupForNoAnalysis() {
        ON_CALL(config, benchmarkNoAnalysis()).WillByDefault(::testing::Return(true));
    }

    void SetupForAnalysis() {
        ON_CALL(config, benchmarkNoAnalysis()).WillByDefault(::testing::Return(false));
        ON_CALL(config, benchmarkConfidenceInterval()).WillByDefault(::testing::Return(0.95));
        ON_CALL(config, benchmarkResamples()).WillByDefault(::testing::Return(100));
    }
};

// ==================== No Analysis Mode Tests ====================

TEST_F(AnalyseTest_982, NoAnalysis_SingleSample_982) {
    SetupForNoAnalysis();

    std::vector<FDuration> durations = { FDuration(5.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    ASSERT_EQ(result.samples.size(), 1u);
    EXPECT_DOUBLE_EQ(result.samples[0].count(), 5.0);

    // Mean should be 5.0
    EXPECT_DOUBLE_EQ(result.mean.point.count(), 5.0);
    EXPECT_DOUBLE_EQ(result.mean.lower_bound.count(), 5.0);
    EXPECT_DOUBLE_EQ(result.mean.upper_bound.count(), 5.0);
    EXPECT_DOUBLE_EQ(result.mean.confidence_interval, 0.0);

    // Standard deviation should be 0
    EXPECT_DOUBLE_EQ(result.standard_deviation.point.count(), 0.0);
    EXPECT_DOUBLE_EQ(result.standard_deviation.lower_bound.count(), 0.0);
    EXPECT_DOUBLE_EQ(result.standard_deviation.upper_bound.count(), 0.0);
    EXPECT_DOUBLE_EQ(result.standard_deviation.confidence_interval, 0.0);

    // Outlier variance should be 0
    EXPECT_DOUBLE_EQ(result.outlier_variance, 0.0);
}

TEST_F(AnalyseTest_982, NoAnalysis_MultipleSamples_MeanCalculation_982) {
    SetupForNoAnalysis();

    std::vector<FDuration> durations = { FDuration(2.0), FDuration(4.0), FDuration(6.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    ASSERT_EQ(result.samples.size(), 3u);
    EXPECT_DOUBLE_EQ(result.samples[0].count(), 2.0);
    EXPECT_DOUBLE_EQ(result.samples[1].count(), 4.0);
    EXPECT_DOUBLE_EQ(result.samples[2].count(), 6.0);

    // Mean should be (2+4+6)/3 = 4.0
    EXPECT_DOUBLE_EQ(result.mean.point.count(), 4.0);
    EXPECT_DOUBLE_EQ(result.mean.lower_bound.count(), 4.0);
    EXPECT_DOUBLE_EQ(result.mean.upper_bound.count(), 4.0);
    EXPECT_DOUBLE_EQ(result.mean.confidence_interval, 0.0);
}

TEST_F(AnalyseTest_982, NoAnalysis_IdenticalSamples_982) {
    SetupForNoAnalysis();

    std::vector<FDuration> durations = { FDuration(3.0), FDuration(3.0), FDuration(3.0), FDuration(3.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    ASSERT_EQ(result.samples.size(), 4u);
    EXPECT_DOUBLE_EQ(result.mean.point.count(), 3.0);
}

TEST_F(AnalyseTest_982, NoAnalysis_StandardDeviationIsZero_982) {
    SetupForNoAnalysis();

    std::vector<FDuration> durations = { FDuration(1.0), FDuration(2.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    EXPECT_DOUBLE_EQ(result.standard_deviation.point.count(), 0.0);
    EXPECT_DOUBLE_EQ(result.standard_deviation.lower_bound.count(), 0.0);
    EXPECT_DOUBLE_EQ(result.standard_deviation.upper_bound.count(), 0.0);
    EXPECT_DOUBLE_EQ(result.standard_deviation.confidence_interval, 0.0);
}

TEST_F(AnalyseTest_982, NoAnalysis_OutlierClassificationDefault_982) {
    SetupForNoAnalysis();

    std::vector<FDuration> durations = { FDuration(1.0), FDuration(2.0), FDuration(3.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    EXPECT_EQ(result.outliers.samples_seen, 0);
    EXPECT_EQ(result.outliers.low_severe, 0);
    EXPECT_EQ(result.outliers.low_mild, 0);
    EXPECT_EQ(result.outliers.high_mild, 0);
    EXPECT_EQ(result.outliers.high_severe, 0);
}

TEST_F(AnalyseTest_982, NoAnalysis_OutlierVarianceIsZero_982) {
    SetupForNoAnalysis();

    std::vector<FDuration> durations = { FDuration(10.0), FDuration(20.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    EXPECT_DOUBLE_EQ(result.outlier_variance, 0.0);
}

TEST_F(AnalyseTest_982, NoAnalysis_TwoSamples_MeanCalculation_982) {
    SetupForNoAnalysis();

    std::vector<FDuration> durations = { FDuration(10.0), FDuration(20.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    EXPECT_DOUBLE_EQ(result.mean.point.count(), 15.0);
}

TEST_F(AnalyseTest_982, NoAnalysis_PreservesSampleOrder_982) {
    SetupForNoAnalysis();

    std::vector<FDuration> durations = { FDuration(5.0), FDuration(1.0), FDuration(3.0), FDuration(7.0), FDuration(2.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    ASSERT_EQ(result.samples.size(), 5u);
    EXPECT_DOUBLE_EQ(result.samples[0].count(), 5.0);
    EXPECT_DOUBLE_EQ(result.samples[1].count(), 1.0);
    EXPECT_DOUBLE_EQ(result.samples[2].count(), 3.0);
    EXPECT_DOUBLE_EQ(result.samples[3].count(), 7.0);
    EXPECT_DOUBLE_EQ(result.samples[4].count(), 2.0);
}

TEST_F(AnalyseTest_982, NoAnalysis_ZeroDurations_982) {
    SetupForNoAnalysis();

    std::vector<FDuration> durations = { FDuration(0.0), FDuration(0.0), FDuration(0.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    EXPECT_DOUBLE_EQ(result.mean.point.count(), 0.0);
    EXPECT_EQ(result.samples.size(), 3u);
}

// ==================== With Analysis Mode Tests ====================

TEST_F(AnalyseTest_982, WithAnalysis_SingleSample_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations = { FDuration(5.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    ASSERT_EQ(result.samples.size(), 1u);
    EXPECT_DOUBLE_EQ(result.samples[0].count(), 5.0);
}

TEST_F(AnalyseTest_982, WithAnalysis_MultipleSamples_ReturnsSameSizeAsSamples_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations = { FDuration(1.0), FDuration(2.0), FDuration(3.0), FDuration(4.0), FDuration(5.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    ASSERT_EQ(result.samples.size(), 5u);
}

TEST_F(AnalyseTest_982, WithAnalysis_SamplesPreservedAsDouble_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations = { FDuration(1.5), FDuration(2.5), FDuration(3.5) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    ASSERT_EQ(result.samples.size(), 3u);
    EXPECT_DOUBLE_EQ(result.samples[0].count(), 1.5);
    EXPECT_DOUBLE_EQ(result.samples[1].count(), 2.5);
    EXPECT_DOUBLE_EQ(result.samples[2].count(), 3.5);
}

TEST_F(AnalyseTest_982, WithAnalysis_MeanEstimateHasValidConfidenceInterval_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations;
    for (int i = 0; i < 20; ++i) {
        durations.push_back(FDuration(static_cast<double>(i + 1)));
    }
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    // The mean point should be somewhere reasonable
    EXPECT_GT(result.mean.point.count(), 0.0);

    // Lower bound should be <= point <= upper bound
    EXPECT_LE(result.mean.lower_bound.count(), result.mean.point.count());
    EXPECT_GE(result.mean.upper_bound.count(), result.mean.point.count());
}

TEST_F(AnalyseTest_982, WithAnalysis_StandardDeviationEstimateNonNegative_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations;
    for (int i = 0; i < 20; ++i) {
        durations.push_back(FDuration(static_cast<double>(i + 1)));
    }
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    EXPECT_GE(result.standard_deviation.point.count(), 0.0);
    EXPECT_GE(result.standard_deviation.lower_bound.count(), 0.0);
    EXPECT_GE(result.standard_deviation.upper_bound.count(), 0.0);
}

TEST_F(AnalyseTest_982, WithAnalysis_IdenticalSamples_LowVariance_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations;
    for (int i = 0; i < 20; ++i) {
        durations.push_back(FDuration(5.0));
    }
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    // All identical samples means std dev should be 0 or very near 0
    EXPECT_NEAR(result.standard_deviation.point.count(), 0.0, 1e-10);
}

TEST_F(AnalyseTest_982, WithAnalysis_OutliersClassification_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations;
    for (int i = 0; i < 20; ++i) {
        durations.push_back(FDuration(static_cast<double>(i + 1)));
    }
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    // Outliers samples_seen should equal number of samples
    EXPECT_EQ(result.outliers.samples_seen, 20);
    // Total outliers should be non-negative
    EXPECT_GE(result.outliers.total(), 0);
}

TEST_F(AnalyseTest_982, WithAnalysis_ConfigCalledWithCorrectParameters_982) {
    EXPECT_CALL(config, benchmarkNoAnalysis()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(config, benchmarkConfidenceInterval()).WillRepeatedly(::testing::Return(0.95));
    EXPECT_CALL(config, benchmarkResamples()).WillRepeatedly(::testing::Return(100));

    std::vector<FDuration> durations = { FDuration(1.0), FDuration(2.0), FDuration(3.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    // Just verify the calls were made - the EXPECT_CALL above will verify
    EXPECT_EQ(result.samples.size(), 3u);
}

TEST_F(AnalyseTest_982, WithAnalysis_LargeNumberOfSamples_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations;
    for (int i = 0; i < 100; ++i) {
        durations.push_back(FDuration(static_cast<double>(i)));
    }
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    ASSERT_EQ(result.samples.size(), 100u);
    EXPECT_GT(result.mean.point.count(), 0.0);
    EXPECT_GE(result.standard_deviation.point.count(), 0.0);
}

TEST_F(AnalyseTest_982, WithAnalysis_OutlierVarianceNonNegative_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations;
    for (int i = 0; i < 20; ++i) {
        durations.push_back(FDuration(static_cast<double>(i + 1)));
    }
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    EXPECT_GE(result.outlier_variance, 0.0);
}

TEST_F(AnalyseTest_982, WithAnalysis_MeanEstimateConfidenceInterval_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations;
    for (int i = 0; i < 30; ++i) {
        durations.push_back(FDuration(static_cast<double>(i + 1)));
    }
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    // Confidence interval should be between 0 and 1 (inclusive)
    EXPECT_GE(result.mean.confidence_interval, 0.0);
    EXPECT_LE(result.mean.confidence_interval, 1.0);
}

TEST_F(AnalyseTest_982, WithAnalysis_StdDevEstimateConfidenceInterval_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations;
    for (int i = 0; i < 30; ++i) {
        durations.push_back(FDuration(static_cast<double>(i + 1)));
    }
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    EXPECT_GE(result.standard_deviation.confidence_interval, 0.0);
    EXPECT_LE(result.standard_deviation.confidence_interval, 1.0);
}

TEST_F(AnalyseTest_982, WithAnalysis_WithExtremeOutlier_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations;
    for (int i = 0; i < 19; ++i) {
        durations.push_back(FDuration(10.0));
    }
    // Add one extreme outlier
    durations.push_back(FDuration(10000.0));

    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    ASSERT_EQ(result.samples.size(), 20u);
    // With an extreme outlier, we should see some outlier classification
    EXPECT_EQ(result.outliers.samples_seen, 20);
    // The outlier variance should be positive with such a clear outlier
    EXPECT_GE(result.outlier_variance, 0.0);
}

TEST_F(AnalyseTest_982, NoAnalysis_LargeNumberOfSamples_982) {
    SetupForNoAnalysis();

    std::vector<FDuration> durations;
    double sum = 0.0;
    for (int i = 1; i <= 100; ++i) {
        durations.push_back(FDuration(static_cast<double>(i)));
        sum += i;
    }
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    double expectedMean = sum / 100.0;
    EXPECT_DOUBLE_EQ(result.mean.point.count(), expectedMean);
    EXPECT_EQ(result.samples.size(), 100u);
}

TEST_F(AnalyseTest_982, NoAnalysis_FractionalDurations_982) {
    SetupForNoAnalysis();

    std::vector<FDuration> durations = { FDuration(0.1), FDuration(0.2), FDuration(0.3) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    double expectedMean = (0.1 + 0.2 + 0.3) / 3.0;
    EXPECT_NEAR(result.mean.point.count(), expectedMean, 1e-12);
}

TEST_F(AnalyseTest_982, WithAnalysis_DifferentConfidenceInterval_982) {
    ON_CALL(config, benchmarkNoAnalysis()).WillByDefault(::testing::Return(false));
    ON_CALL(config, benchmarkConfidenceInterval()).WillByDefault(::testing::Return(0.99));
    ON_CALL(config, benchmarkResamples()).WillByDefault(::testing::Return(200));

    std::vector<FDuration> durations;
    for (int i = 0; i < 20; ++i) {
        durations.push_back(FDuration(static_cast<double>(i + 1)));
    }
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    ASSERT_EQ(result.samples.size(), 20u);
    EXPECT_GT(result.mean.point.count(), 0.0);
}

TEST_F(AnalyseTest_982, WithAnalysis_TwoSamples_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations = { FDuration(10.0), FDuration(20.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    ASSERT_EQ(result.samples.size(), 2u);
    EXPECT_DOUBLE_EQ(result.samples[0].count(), 10.0);
    EXPECT_DOUBLE_EQ(result.samples[1].count(), 20.0);
}

TEST_F(AnalyseTest_982, NoAnalysis_MeanBoundsEqualPoint_982) {
    SetupForNoAnalysis();

    std::vector<FDuration> durations = { FDuration(1.0), FDuration(2.0), FDuration(3.0), FDuration(4.0) };
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    EXPECT_DOUBLE_EQ(result.mean.point.count(), result.mean.lower_bound.count());
    EXPECT_DOUBLE_EQ(result.mean.point.count(), result.mean.upper_bound.count());
}

TEST_F(AnalyseTest_982, WithAnalysis_StdDevBoundsOrdering_982) {
    SetupForAnalysis();

    std::vector<FDuration> durations;
    for (int i = 0; i < 30; ++i) {
        durations.push_back(FDuration(static_cast<double>(i * i)));
    }
    auto result = analyse(config, durations.data(), durations.data() + durations.size());

    EXPECT_LE(result.standard_deviation.lower_bound.count(), result.standard_deviation.point.count());
    EXPECT_GE(result.standard_deviation.upper_bound.count(), result.standard_deviation.point.count());
}
