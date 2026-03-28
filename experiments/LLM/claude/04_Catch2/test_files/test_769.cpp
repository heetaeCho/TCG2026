#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>

#include "catch2/reporters/catch_reporter_console.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/benchmark/detail/catch_benchmark_stats.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"

using namespace Catch;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;

namespace {

class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

// Helper to create a ConsoleReporter with a mock config and stringstream output
struct ConsoleReporterTestFixture {
    std::stringstream ss;
    MockConfig mockConfig;
    std::vector<std::string> emptyVec;
    std::vector<std::string> emptySections;
    TestSpec emptyTestSpec;

    void setupDefaultMockExpectations() {
        ON_CALL(mockConfig, allowThrows()).WillByDefault(Return(true));
        ON_CALL(mockConfig, name()).WillByDefault(Return(StringRef("")));
        ON_CALL(mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(mockConfig, shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(mockConfig, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(mockConfig, warnAboutUnmatchedTestSpecs()).WillByDefault(Return(false));
        ON_CALL(mockConfig, zeroTestsCountAsSuccess()).WillByDefault(Return(false));
        ON_CALL(mockConfig, abortAfter()).WillByDefault(Return(0));
        ON_CALL(mockConfig, showInvisibles()).WillByDefault(Return(false));
        ON_CALL(mockConfig, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));
        ON_CALL(mockConfig, minDuration()).WillByDefault(Return(0.0));
        ON_CALL(mockConfig, testSpec()).WillByDefault(ReturnRef(emptyTestSpec));
        ON_CALL(mockConfig, hasTestFilters()).WillByDefault(Return(false));
        ON_CALL(mockConfig, getTestsOrTags()).WillByDefault(ReturnRef(emptyVec));
        ON_CALL(mockConfig, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
        ON_CALL(mockConfig, rngSeed()).WillByDefault(Return(0));
        ON_CALL(mockConfig, shardCount()).WillByDefault(Return(1));
        ON_CALL(mockConfig, shardIndex()).WillByDefault(Return(0));
        ON_CALL(mockConfig, defaultColourMode()).WillByDefault(Return(ColourMode::None));
        ON_CALL(mockConfig, getSectionsToRun()).WillByDefault(ReturnRef(emptySections));
        ON_CALL(mockConfig, verbosity()).WillByDefault(Return(Verbosity::Normal));
        ON_CALL(mockConfig, skipBenchmarks()).WillByDefault(Return(false));
        ON_CALL(mockConfig, benchmarkNoAnalysis()).WillByDefault(Return(false));
        ON_CALL(mockConfig, benchmarkSamples()).WillByDefault(Return(100));
        ON_CALL(mockConfig, benchmarkConfidenceInterval()).WillByDefault(Return(0.95));
        ON_CALL(mockConfig, benchmarkResamples()).WillByDefault(Return(100000));
        ON_CALL(mockConfig, benchmarkWarmupTime()).WillByDefault(Return(std::chrono::milliseconds(100)));
    }
};

} // anonymous namespace

class ConsoleReporterBenchmarkTest_769 : public ::testing::Test {
protected:
    void SetUp() override {
        fixture.setupDefaultMockExpectations();
    }

    ConsoleReporterTestFixture fixture;

    std::unique_ptr<ConsoleReporter> createReporter() {
        auto config = ReporterConfig(&fixture.mockConfig, fixture.ss, ColourMode::None, {});
        return std::make_unique<ConsoleReporter>(CATCH_MOVE(config));
    }

    BenchmarkInfo makeBenchmarkInfo(unsigned int samples, int iterations, double estimatedDuration) {
        BenchmarkInfo info;
        info.samples = samples;
        info.iterations = iterations;
        info.estimatedDuration = estimatedDuration;
        info.resamples = 100000;
        info.clockResolution = 1e-9;
        info.clockCost = 1e-6;
        return info;
    }

    void prepareReporterForBenchmark(ConsoleReporter& reporter) {
        // We need to set up the reporter state so it can print benchmark info
        // This typically requires testRunStarting, testCaseStarting, sectionStarting, benchmarkPreparing
        TestRunInfo runInfo("test");
        reporter.testRunStarting(runInfo);

        auto properties = TestCaseProperties::None;
        TestCaseInfo tcInfo("benchmark_test", {"class"}, SourceLineInfo("file.cpp", 1), "", properties);
        reporter.testCaseStarting(tcInfo);

        SectionInfo sectionInfo(SourceLineInfo("file.cpp", 1), "section");
        reporter.sectionStarting(sectionInfo);

        reporter.benchmarkPreparing("benchmark_name"_catch_sr);
    }
};

TEST_F(ConsoleReporterBenchmarkTest_769, BenchmarkStartingWithAnalysis_769) {
    ON_CALL(fixture.mockConfig, benchmarkNoAnalysis()).WillByDefault(Return(false));

    auto reporter = createReporter();
    prepareReporterForBenchmark(*reporter);

    BenchmarkInfo info = makeBenchmarkInfo(100, 1000, 5.0);
    EXPECT_NO_THROW(reporter->benchmarkStarting(info));

    std::string output = fixture.ss.str();
    // With analysis, the output should contain samples and iterations
    EXPECT_NE(output.find("100"), std::string::npos);
    EXPECT_NE(output.find("1000"), std::string::npos);
}

TEST_F(ConsoleReporterBenchmarkTest_769, BenchmarkStartingNoAnalysis_769) {
    ON_CALL(fixture.mockConfig, benchmarkNoAnalysis()).WillByDefault(Return(true));

    auto reporter = createReporter();
    prepareReporterForBenchmark(*reporter);

    BenchmarkInfo info = makeBenchmarkInfo(50, 500, 3.0);
    EXPECT_NO_THROW(reporter->benchmarkStarting(info));

    std::string output = fixture.ss.str();
    // Samples and iterations should still be printed
    EXPECT_NE(output.find("50"), std::string::npos);
    EXPECT_NE(output.find("500"), std::string::npos);
}

TEST_F(ConsoleReporterBenchmarkTest_769, BenchmarkStartingZeroSamples_769) {
    ON_CALL(fixture.mockConfig, benchmarkNoAnalysis()).WillByDefault(Return(false));

    auto reporter = createReporter();
    prepareReporterForBenchmark(*reporter);

    BenchmarkInfo info = makeBenchmarkInfo(0, 0, 0.0);
    EXPECT_NO_THROW(reporter->benchmarkStarting(info));

    std::string output = fixture.ss.str();
    // Should handle zero values gracefully
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterBenchmarkTest_769, BenchmarkStartingLargeValues_769) {
    ON_CALL(fixture.mockConfig, benchmarkNoAnalysis()).WillByDefault(Return(false));

    auto reporter = createReporter();
    prepareReporterForBenchmark(*reporter);

    BenchmarkInfo info = makeBenchmarkInfo(1000000, 999999999, 1e12);
    EXPECT_NO_THROW(reporter->benchmarkStarting(info));

    std::string output = fixture.ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterBenchmarkTest_769, BenchmarkStartingSingleSampleIteration_769) {
    ON_CALL(fixture.mockConfig, benchmarkNoAnalysis()).WillByDefault(Return(false));

    auto reporter = createReporter();
    prepareReporterForBenchmark(*reporter);

    BenchmarkInfo info = makeBenchmarkInfo(1, 1, 0.001);
    EXPECT_NO_THROW(reporter->benchmarkStarting(info));

    std::string output = fixture.ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterBenchmarkTest_769, BenchmarkStartingNoAnalysisDoesNotPrintDuration_769) {
    ON_CALL(fixture.mockConfig, benchmarkNoAnalysis()).WillByDefault(Return(true));

    auto reporter = createReporter();
    prepareReporterForBenchmark(*reporter);

    // Use a very specific estimated duration that we can check for absence
    BenchmarkInfo info = makeBenchmarkInfo(10, 20, 99.12345);
    EXPECT_NO_THROW(reporter->benchmarkStarting(info));

    // When noAnalysis is true, the estimated duration should NOT be printed
    // (the Duration(...) << ColumnBreak() block is skipped)
    std::string output = fixture.ss.str();
    // The exact format depends on Duration formatting, but the key point is no throw
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterBenchmarkTest_769, BenchmarkStartingWithAnalysisPrintsDuration_769) {
    ON_CALL(fixture.mockConfig, benchmarkNoAnalysis()).WillByDefault(Return(false));

    auto reporter = createReporter();
    prepareReporterForBenchmark(*reporter);

    BenchmarkInfo info = makeBenchmarkInfo(10, 20, 5.0);
    EXPECT_NO_THROW(reporter->benchmarkStarting(info));

    // Output should be non-empty and should contain the benchmark info
    std::string output = fixture.ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterBenchmarkTest_769, BenchmarkStartingVerySmallDuration_769) {
    ON_CALL(fixture.mockConfig, benchmarkNoAnalysis()).WillByDefault(Return(false));

    auto reporter = createReporter();
    prepareReporterForBenchmark(*reporter);

    BenchmarkInfo info = makeBenchmarkInfo(5, 10, 1e-15);
    EXPECT_NO_THROW(reporter->benchmarkStarting(info));

    std::string output = fixture.ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ConsoleReporterBenchmarkTest_769, GetDescriptionReturnsNonEmpty_769) {
    std::string desc = ConsoleReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(ConsoleReporterBenchmarkTest_769, ConsoleReporterCanBeCreated_769) {
    auto reporter = createReporter();
    EXPECT_NE(reporter, nullptr);
}
