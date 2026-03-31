#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/internal/catch_run_context.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/benchmark/detail/catch_benchmark_stats.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>
#include <catch2/catch_test_case_info.hpp>

#include <string>
#include <vector>

using namespace Catch;
using ::testing::_;
using ::testing::Invoke;
using ::testing::AtLeast;

// Mock for IConfig
class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(ReporterSpec const&, getReporterSpec, (size_t), (const, override));
    MOCK_METHOD(std::vector<ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(std::vector<ProcessedReporterSpec> const&, getProcessedReporterSpecs, (), (const, override));
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

// Mock for IEventListener (the reporter)
class MockReporter : public IEventListener {
public:
    MockReporter(IConfig const* config) : IEventListener(config) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (TestRunInfo const&), (override));
    MOCK_METHOD(void, testCaseStarting, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (TestCaseInfo const&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (SectionInfo const&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (BenchmarkInfo const&), (override));
    MOCK_METHOD(void, benchmarkEnded, (BenchmarkStats<> const&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, assertionStarting, (AssertionInfo const&), (override));
    MOCK_METHOD(void, assertionEnded, (AssertionStats const&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionStats const&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (TestCaseStats const&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (TestCaseStats const&), (override));
    MOCK_METHOD(void, testRunEnded, (TestRunStats const&), (override));
    MOCK_METHOD(void, skipTest, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listReporters, (std::vector<ReporterDescription> const&), (override));
    MOCK_METHOD(void, listListeners, (std::vector<ListenerDescription> const&), (override));
    MOCK_METHOD(void, listTests, (std::vector<TestCaseHandle> const&), (override));
    MOCK_METHOD(void, listTags, (std::vector<TagInfo> const&), (override));
};

class RunContextTest_503 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new MockConfig();
        
        // Set up minimal config expectations
        static std::string configName = "test";
        static std::vector<std::string> emptyVec;
        static TestSpec emptySpec;
        static std::vector<ProcessedReporterSpec> emptyProcessed;
        
        ON_CALL(*mockConfig_, name()).WillByDefault(::testing::Return(StringRef(configName)));
        ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, allowThrows()).WillByDefault(::testing::Return(true));
        ON_CALL(*mockConfig_, warnAboutMissingAssertions()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, warnAboutUnmatchedTestSpecs()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, abortAfter()).WillByDefault(::testing::Return(0));
        ON_CALL(*mockConfig_, showDurations()).WillByDefault(::testing::Return(ShowDurations::Never));
        ON_CALL(*mockConfig_, runOrder()).WillByDefault(::testing::Return(TestRunOrder::Declared));
        ON_CALL(*mockConfig_, rngSeed()).WillByDefault(::testing::Return(0));
        ON_CALL(*mockConfig_, benchmarkNoAnalysis()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, benchmarkSamples()).WillByDefault(::testing::Return(100));
        ON_CALL(*mockConfig_, benchmarkConfidenceInterval()).WillByDefault(::testing::Return(0.95));
        ON_CALL(*mockConfig_, benchmarkResamples()).WillByDefault(::testing::Return(100000));
        ON_CALL(*mockConfig_, benchmarkWarmupTime()).WillByDefault(::testing::Return(std::chrono::milliseconds(100)));
        ON_CALL(*mockConfig_, hasTestFilters()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));
        ON_CALL(*mockConfig_, getSectionsToRun()).WillByDefault(::testing::ReturnRef(emptyVec));
        ON_CALL(*mockConfig_, testSpec()).WillByDefault(::testing::ReturnRef(emptySpec));
        ON_CALL(*mockConfig_, getProcessedReporterSpecs()).WillByDefault(::testing::ReturnRef(emptyProcessed));
        ON_CALL(*mockConfig_, defaultColourMode()).WillByDefault(::testing::Return(ColourMode::None));
        
        mockReporter_ = new MockReporter(mockConfig_);
    }

    void TearDown() override {
        // mockConfig_ is not owned by RunContext, so we manage it
        // mockReporter_ is moved into RunContext and will be owned by it
    }

    MockConfig* mockConfig_;
    MockReporter* mockReporter_; // Will be moved into RunContext
};

// Test that benchmarkEnded forwards the call to the reporter
TEST_F(RunContextTest_503, BenchmarkEndedForwardsToReporter_503) {
    // Keep a raw pointer before moving
    MockReporter* reporterPtr = mockReporter_;
    
    // Expect testRunStarting to be called during construction or setup
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(AtLeast(0));
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(AtLeast(0));
    
    Detail::unique_ptr<IEventListener> reporterUptr(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterUptr));
    
    BenchmarkStats<> stats;
    stats.info.name = "TestBenchmark";
    stats.info.samples = 100;
    stats.info.iterations = 1;
    stats.info.estimatedDuration = 1.0;
    stats.outlierVariance = 0.5;
    
    EXPECT_CALL(*reporterPtr, benchmarkEnded(::testing::_)).Times(1);
    
    context.benchmarkEnded(stats);
}

// Test that benchmarkEnded passes the correct stats to the reporter
TEST_F(RunContextTest_503, BenchmarkEndedPassesCorrectStats_503) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(AtLeast(0));
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(AtLeast(0));
    
    Detail::unique_ptr<IEventListener> reporterUptr(mockReporter_);
    RunContext context(mockConfig_, CATCH_MOVE(reporterUptr));
    
    BenchmarkStats<> stats;
    stats.info.name = "SpecificBenchmark";
    stats.info.samples = 200;
    stats.info.iterations = 5;
    stats.info.estimatedDuration = 2.5;
    stats.outlierVariance = 0.1;
    
    EXPECT_CALL(*reporterPtr, benchmarkEnded(::testing::_))
        .Times(1)
        .WillOnce(Invoke([](BenchmarkStats<> const& receivedStats) {
            EXPECT_EQ(receivedStats.info.name, "SpecificBenchmark");
            EXPECT_EQ(receivedStats.info.samples, 200u);
            EXPECT_EQ(receivedStats.info.iterations, 5u);
            EXPECT_DOUBLE_EQ(receivedStats.outlierVariance, 0.1);
        }));
    
    context.benchmarkEnded(stats);
}

// Test that benchmarkPreparing forwards to reporter
TEST_F(RunContextTest_503, BenchmarkPreparingForwardsToReporter_503) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(AtLeast(0));
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(AtLeast(0));
    
    Detail::unique_ptr<IEventListener> reporterUptr(mockReporter_);
    RunContext context(mockConfig_, CATCH_MOVE(reporterUptr));
    
    EXPECT_CALL(*reporterPtr, benchmarkPreparing(::testing::_)).Times(1);
    
    context.benchmarkPreparing("TestBenchmarkPrep"_catch_sr);
}

// Test that benchmarkStarting forwards to reporter
TEST_F(RunContextTest_503, BenchmarkStartingForwardsToReporter_503) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(AtLeast(0));
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(AtLeast(0));
    
    Detail::unique_ptr<IEventListener> reporterUptr(mockReporter_);
    RunContext context(mockConfig_, CATCH_MOVE(reporterUptr));
    
    BenchmarkInfo info{"BenchmarkName", 100.0, 50, 10};
    
    EXPECT_CALL(*reporterPtr, benchmarkStarting(::testing::_)).Times(1);
    
    context.benchmarkStarting(info);
}

// Test that benchmarkFailed forwards to reporter
TEST_F(RunContextTest_503, BenchmarkFailedForwardsToReporter_503) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(AtLeast(0));
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(AtLeast(0));
    
    Detail::unique_ptr<IEventListener> reporterUptr(mockReporter_);
    RunContext context(mockConfig_, CATCH_MOVE(reporterUptr));
    
    EXPECT_CALL(*reporterPtr, benchmarkFailed(::testing::_)).Times(1);
    
    context.benchmarkFailed("benchmark error"_catch_sr);
}

// Test benchmarkEnded with empty samples
TEST_F(RunContextTest_503, BenchmarkEndedWithEmptySamples_503) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(AtLeast(0));
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(AtLeast(0));
    
    Detail::unique_ptr<IEventListener> reporterUptr(mockReporter_);
    RunContext context(mockConfig_, CATCH_MOVE(reporterUptr));
    
    BenchmarkStats<> stats;
    stats.info.name = "EmptyBenchmark";
    stats.info.samples = 0;
    stats.info.iterations = 0;
    stats.info.estimatedDuration = 0.0;
    stats.samples.clear();
    stats.outlierVariance = 0.0;
    
    EXPECT_CALL(*reporterPtr, benchmarkEnded(::testing::_))
        .Times(1)
        .WillOnce(Invoke([](BenchmarkStats<> const& receivedStats) {
            EXPECT_TRUE(receivedStats.samples.empty());
            EXPECT_EQ(receivedStats.info.name, "EmptyBenchmark");
        }));
    
    context.benchmarkEnded(stats);
}

// Test benchmarkEnded called multiple times
TEST_F(RunContextTest_503, BenchmarkEndedCalledMultipleTimes_503) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(AtLeast(0));
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(AtLeast(0));
    
    Detail::unique_ptr<IEventListener> reporterUptr(mockReporter_);
    RunContext context(mockConfig_, CATCH_MOVE(reporterUptr));
    
    BenchmarkStats<> stats1;
    stats1.info.name = "Benchmark1";
    stats1.info.samples = 10;
    stats1.info.iterations = 1;
    stats1.info.estimatedDuration = 1.0;
    stats1.outlierVariance = 0.0;
    
    BenchmarkStats<> stats2;
    stats2.info.name = "Benchmark2";
    stats2.info.samples = 20;
    stats2.info.iterations = 2;
    stats2.info.estimatedDuration = 2.0;
    stats2.outlierVariance = 0.5;
    
    EXPECT_CALL(*reporterPtr, benchmarkEnded(::testing::_)).Times(2);
    
    context.benchmarkEnded(stats1);
    context.benchmarkEnded(stats2);
}

// Test that lastAssertionPassed returns false initially
TEST_F(RunContextTest_503, LastAssertionPassedInitiallyFalse_503) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(AtLeast(0));
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(AtLeast(0));
    
    Detail::unique_ptr<IEventListener> reporterUptr(mockReporter_);
    RunContext context(mockConfig_, CATCH_MOVE(reporterUptr));
    
    EXPECT_FALSE(context.lastAssertionPassed());
}

// Test assertionPassed sets last assertion to passed
TEST_F(RunContextTest_503, AssertionPassedSetsFlag_503) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(AtLeast(0));
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(AtLeast(0));
    
    Detail::unique_ptr<IEventListener> reporterUptr(mockReporter_);
    RunContext context(mockConfig_, CATCH_MOVE(reporterUptr));
    
    context.assertionPassed();
    EXPECT_TRUE(context.lastAssertionPassed());
}

// Test getCurrentTestName when no test is active
TEST_F(RunContextTest_503, GetCurrentTestNameWhenNoTestActive_503) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(AtLeast(0));
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(AtLeast(0));
    
    Detail::unique_ptr<IEventListener> reporterUptr(mockReporter_);
    RunContext context(mockConfig_, CATCH_MOVE(reporterUptr));
    
    // When no test case is active, getCurrentTestName should return empty or some default
    std::string name = context.getCurrentTestName();
    EXPECT_TRUE(name.empty());
}

// Test benchmarkEnded with large outlier variance
TEST_F(RunContextTest_503, BenchmarkEndedWithLargeOutlierVariance_503) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(AtLeast(0));
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(AtLeast(0));
    
    Detail::unique_ptr<IEventListener> reporterUptr(mockReporter_);
    RunContext context(mockConfig_, CATCH_MOVE(reporterUptr));
    
    BenchmarkStats<> stats;
    stats.info.name = "HighVarianceBenchmark";
    stats.info.samples = 1000;
    stats.info.iterations = 100;
    stats.info.estimatedDuration = 100.0;
    stats.outlierVariance = 0.99;
    
    EXPECT_CALL(*reporterPtr, benchmarkEnded(::testing::_))
        .Times(1)
        .WillOnce(Invoke([](BenchmarkStats<> const& receivedStats) {
            EXPECT_DOUBLE_EQ(receivedStats.outlierVariance, 0.99);
            EXPECT_EQ(receivedStats.info.name, "HighVarianceBenchmark");
        }));
    
    context.benchmarkEnded(stats);
}
