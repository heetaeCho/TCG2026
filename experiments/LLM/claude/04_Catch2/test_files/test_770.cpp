#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/benchmark/detail/catch_benchmark_stats.hpp>
#include <catch2/benchmark/catch_estimate.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/catch_reporter_registrars.hpp>

#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace Catch;
using namespace Catch::Benchmark;

namespace {

// Helper to create a BenchmarkStats with given values
BenchmarkStats<> makeBenchmarkStats(double meanPoint, double meanLow, double meanHigh,
                                     double sdPoint, double sdLow, double sdHigh) {
    BenchmarkStats<> stats;
    stats.info.name = "test_benchmark";
    stats.info.samples = 100;
    stats.info.resamples = 100000;
    stats.info.iterations = 1;
    stats.info.estimatedDuration = 0.0;

    stats.mean.point = FDuration(meanPoint);
    stats.mean.lower_bound = FDuration(meanLow);
    stats.mean.upper_bound = FDuration(meanHigh);
    stats.mean.confidence_interval = 0.95;

    stats.standardDeviation.point = FDuration(sdPoint);
    stats.standardDeviation.lower_bound = FDuration(sdLow);
    stats.standardDeviation.upper_bound = FDuration(sdHigh);
    stats.standardDeviation.confidence_interval = 0.95;

    stats.outliers.samples_seen = 100;
    stats.outliers.low_mild = 0;
    stats.outliers.low_severe = 0;
    stats.outliers.high_mild = 0;
    stats.outliers.high_severe = 0;
    stats.outliers.total() ;

    stats.outlierVariance = 0.0;

    return stats;
}

// Helper to build a ConsoleReporter with specific config
class ConsoleReporterTest_770 : public ::testing::Test {
protected:
    std::stringstream stream;

    std::unique_ptr<ConsoleReporter> makeReporter(bool noAnalysis) {
        // Build argv for Config
        std::vector<std::string> args = {"test"};
        if (noAnalysis) {
            args.push_back("--benchmark-no-analysis");
        }

        // We need to create a proper Catch2 config
        // Use Catch's own configuration mechanisms
        char const* argv_cstr[10];
        for (size_t i = 0; i < args.size(); ++i) {
            argv_cstr[i] = args[i].c_str();
        }

        Catch::ConfigData configData;
        configData.benchmarkNoAnalysis = noAnalysis;

        auto config = Catch::Detail::make_unique<Catch::Config>(configData);

        auto reporterConfig = ReporterConfig(config.get(), stream, ColourMode::None, {});

        auto reporter = Catch::Detail::make_unique<ConsoleReporter>(CATCH_MOVE(reporterConfig));

        // Store config so it outlives reporter
        m_config = CATCH_MOVE(config);

        return reporter;
    }

    Catch::Detail::unique_ptr<Catch::Config> m_config;
};

} // anonymous namespace

TEST_F(ConsoleReporterTest_770, BenchmarkEndedWithNoAnalysis_770) {
    auto reporter = makeReporter(true);

    // We need to set up the reporter state so benchmarkEnded can work
    // Start a test run and test case first
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        "", {"test_case", "[benchmark]"}, {"file.cpp", 1});
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo("file.cpp", 1, "test_case");
    reporter->sectionStarting(sectionInfo);

    BenchmarkInfo benchInfo{"bench1", 1.0, 100, 100, 100000};
    reporter->benchmarkPreparing("bench1");
    reporter->benchmarkStarting(benchInfo);

    auto stats = makeBenchmarkStats(100.0, 90.0, 110.0, 5.0, 3.0, 7.0);

    // Should not throw
    ASSERT_NO_THROW(reporter->benchmarkEnded(stats));

    std::string output = stream.str();
    // With noAnalysis, output should contain mean but likely not standard deviation columns
    // We just verify it doesn't crash and produces some output
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterTest_770, BenchmarkEndedWithAnalysis_770) {
    auto reporter = makeReporter(false);

    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        "", {"test_case", "[benchmark]"}, {"file.cpp", 1});
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo("file.cpp", 1, "test_case");
    reporter->sectionStarting(sectionInfo);

    BenchmarkInfo benchInfo{"bench1", 1.0, 100, 100, 100000};
    reporter->benchmarkPreparing("bench1");
    reporter->benchmarkStarting(benchInfo);

    auto stats = makeBenchmarkStats(100.0, 90.0, 110.0, 5.0, 3.0, 7.0);

    ASSERT_NO_THROW(reporter->benchmarkEnded(stats));

    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterTest_770, BenchmarkEndedZeroValues_770) {
    auto reporter = makeReporter(false);

    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        "", {"test_case", "[benchmark]"}, {"file.cpp", 1});
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo("file.cpp", 1, "test_case");
    reporter->sectionStarting(sectionInfo);

    BenchmarkInfo benchInfo{"bench_zero", 1.0, 100, 100, 100000};
    reporter->benchmarkPreparing("bench_zero");
    reporter->benchmarkStarting(benchInfo);

    auto stats = makeBenchmarkStats(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    ASSERT_NO_THROW(reporter->benchmarkEnded(stats));

    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterTest_770, BenchmarkEndedZeroValuesNoAnalysis_770) {
    auto reporter = makeReporter(true);

    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        "", {"test_case", "[benchmark]"}, {"file.cpp", 1});
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo("file.cpp", 1, "test_case");
    reporter->sectionStarting(sectionInfo);

    BenchmarkInfo benchInfo{"bench_zero_na", 1.0, 100, 100, 100000};
    reporter->benchmarkPreparing("bench_zero_na");
    reporter->benchmarkStarting(benchInfo);

    auto stats = makeBenchmarkStats(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    ASSERT_NO_THROW(reporter->benchmarkEnded(stats));

    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterTest_770, BenchmarkEndedLargeValues_770) {
    auto reporter = makeReporter(false);

    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        "", {"test_case", "[benchmark]"}, {"file.cpp", 1});
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo("file.cpp", 1, "test_case");
    reporter->sectionStarting(sectionInfo);

    BenchmarkInfo benchInfo{"bench_large", 1.0, 100, 100, 100000};
    reporter->benchmarkPreparing("bench_large");
    reporter->benchmarkStarting(benchInfo);

    auto stats = makeBenchmarkStats(1e12, 9e11, 1.1e12, 1e10, 9e9, 1.1e10);

    ASSERT_NO_THROW(reporter->benchmarkEnded(stats));

    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterTest_770, BenchmarkEndedVerySmallValues_770) {
    auto reporter = makeReporter(false);

    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        "", {"test_case", "[benchmark]"}, {"file.cpp", 1});
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo("file.cpp", 1, "test_case");
    reporter->sectionStarting(sectionInfo);

    BenchmarkInfo benchInfo{"bench_tiny", 1.0, 100, 100, 100000};
    reporter->benchmarkPreparing("bench_tiny");
    reporter->benchmarkStarting(benchInfo);

    auto stats = makeBenchmarkStats(1e-12, 9e-13, 1.1e-12, 1e-13, 9e-14, 1.1e-13);

    ASSERT_NO_THROW(reporter->benchmarkEnded(stats));

    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterTest_770, BenchmarkEndedNegativeValues_770) {
    auto reporter = makeReporter(false);

    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        "", {"test_case", "[benchmark]"}, {"file.cpp", 1});
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo("file.cpp", 1, "test_case");
    reporter->sectionStarting(sectionInfo);

    BenchmarkInfo benchInfo{"bench_neg", 1.0, 100, 100, 100000};
    reporter->benchmarkPreparing("bench_neg");
    reporter->benchmarkStarting(benchInfo);

    // Negative durations are unusual but should not crash
    auto stats = makeBenchmarkStats(-1.0, -2.0, -0.5, -0.1, -0.2, -0.05);

    ASSERT_NO_THROW(reporter->benchmarkEnded(stats));
}

TEST_F(ConsoleReporterTest_770, BenchmarkEndedMultipleBenchmarks_770) {
    auto reporter = makeReporter(false);

    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        "", {"test_case", "[benchmark]"}, {"file.cpp", 1});
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo("file.cpp", 1, "test_case");
    reporter->sectionStarting(sectionInfo);

    // First benchmark
    BenchmarkInfo benchInfo1{"bench1", 1.0, 100, 100, 100000};
    reporter->benchmarkPreparing("bench1");
    reporter->benchmarkStarting(benchInfo1);
    auto stats1 = makeBenchmarkStats(100.0, 90.0, 110.0, 5.0, 3.0, 7.0);
    ASSERT_NO_THROW(reporter->benchmarkEnded(stats1));

    // Second benchmark
    BenchmarkInfo benchInfo2{"bench2", 1.0, 100, 100, 100000};
    reporter->benchmarkPreparing("bench2");
    reporter->benchmarkStarting(benchInfo2);
    auto stats2 = makeBenchmarkStats(200.0, 180.0, 220.0, 10.0, 8.0, 12.0);
    ASSERT_NO_THROW(reporter->benchmarkEnded(stats2));

    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterTest_770, GetDescription_770) {
    std::string desc = ConsoleReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(ConsoleReporterTest_770, BenchmarkFailed_770) {
    auto reporter = makeReporter(false);

    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        "", {"test_case", "[benchmark]"}, {"file.cpp", 1});
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo("file.cpp", 1, "test_case");
    reporter->sectionStarting(sectionInfo);

    reporter->benchmarkPreparing("failing_bench");
    BenchmarkInfo benchInfo{"failing_bench", 1.0, 100, 100, 100000};
    reporter->benchmarkStarting(benchInfo);

    ASSERT_NO_THROW(reporter->benchmarkFailed("some error"));

    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterTest_770, NoMatchingTestCases_770) {
    auto reporter = makeReporter(false);

    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    ASSERT_NO_THROW(reporter->noMatchingTestCases("nonexistent_spec"));

    std::string output = stream.str();
    // Should output something about no matching test cases
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterTest_770, BenchmarkEndedNoAnalysisLargeValues_770) {
    auto reporter = makeReporter(true);

    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        "", {"test_case", "[benchmark]"}, {"file.cpp", 1});
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo("file.cpp", 1, "test_case");
    reporter->sectionStarting(sectionInfo);

    BenchmarkInfo benchInfo{"bench_large_na", 1.0, 100, 100, 100000};
    reporter->benchmarkPreparing("bench_large_na");
    reporter->benchmarkStarting(benchInfo);

    auto stats = makeBenchmarkStats(1e9, 9e8, 1.1e9, 1e7, 9e6, 1.1e7);

    ASSERT_NO_THROW(reporter->benchmarkEnded(stats));

    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
}
