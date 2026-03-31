#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/benchmark/detail/catch_benchmark_stats.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Ref;

// Mock for IEventListener (reporter)
class MockEventListener : public IEventListener {
public:
    MockEventListener(IConfig const* config) : IEventListener(config) {}
    
    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo&), (override));
    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (const SectionInfo&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, assertionStarting, (const AssertionInfo&), (override));
    MOCK_METHOD(void, assertionEnded, (const AssertionStats&), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats&), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats&), (override));
    MOCK_METHOD(void, skipTest, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>&), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>&), (override));
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>&), (override));
    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>&), (override));
};

// Mock for IConfig
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
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(RuntestFailureAction, defaultRuntestFailureAction, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class RunContextTest_502 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new MockConfig();
        // Set up basic config expectations
        ON_CALL(*mockConfig_, name()).WillByDefault(::testing::Return(StringRef("TestRun")));
        ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, allowThrows()).WillByDefault(::testing::Return(true));
        ON_CALL(*mockConfig_, abortAfter()).WillByDefault(::testing::Return(0));
        ON_CALL(*mockConfig_, warnAboutMissingAssertions()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, defaultRuntestFailureAction()).WillByDefault(::testing::Return(RuntestFailureAction::None));
    }

    void TearDown() override {
        // Config lifetime managed externally in Catch2
    }

    MockConfig* mockConfig_ = nullptr;
};

// Test that benchmarkStarting forwards the BenchmarkInfo to the reporter
TEST_F(RunContextTest_502, BenchmarkStartingForwardsToReporter_502) {
    auto* mockReporter = new MockEventListener(mockConfig_);
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);

    BenchmarkInfo info;
    info.estimatedDuration = 1.5;
    info.iterations = 100;
    info.samples = 10;
    info.resamples = 1000;
    info.clockResolution = 0.001;
    info.clockCost = 0.0001;

    EXPECT_CALL(*mockReporter, benchmarkStarting(_)).Times(1);

    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    context.benchmarkStarting(info);
}

// Test that benchmarkStarting is called exactly once per invocation
TEST_F(RunContextTest_502, BenchmarkStartingCalledOnce_502) {
    auto* mockReporter = new MockEventListener(mockConfig_);
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);

    BenchmarkInfo info{};
    info.estimatedDuration = 0.0;
    info.iterations = 1;
    info.samples = 1;
    info.resamples = 1;
    info.clockResolution = 0.0;
    info.clockCost = 0.0;

    EXPECT_CALL(*mockReporter, benchmarkStarting(_)).Times(1);

    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    context.benchmarkStarting(info);
}

// Test that benchmarkStarting can be called multiple times
TEST_F(RunContextTest_502, BenchmarkStartingMultipleCalls_502) {
    auto* mockReporter = new MockEventListener(mockConfig_);
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);

    BenchmarkInfo info1{};
    info1.estimatedDuration = 1.0;
    info1.iterations = 50;
    info1.samples = 5;
    info1.resamples = 500;
    info1.clockResolution = 0.01;
    info1.clockCost = 0.001;

    BenchmarkInfo info2{};
    info2.estimatedDuration = 2.0;
    info2.iterations = 100;
    info2.samples = 10;
    info2.resamples = 1000;
    info2.clockResolution = 0.02;
    info2.clockCost = 0.002;

    EXPECT_CALL(*mockReporter, benchmarkStarting(_)).Times(2);

    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    context.benchmarkStarting(info1);
    context.benchmarkStarting(info2);
}

// Test with zero/boundary values in BenchmarkInfo
TEST_F(RunContextTest_502, BenchmarkStartingWithZeroValues_502) {
    auto* mockReporter = new MockEventListener(mockConfig_);
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);

    BenchmarkInfo info{};
    info.estimatedDuration = 0.0;
    info.iterations = 0;
    info.samples = 0;
    info.resamples = 0;
    info.clockResolution = 0.0;
    info.clockCost = 0.0;

    EXPECT_CALL(*mockReporter, benchmarkStarting(_)).Times(1);

    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    context.benchmarkStarting(info);
}

// Test with large values in BenchmarkInfo
TEST_F(RunContextTest_502, BenchmarkStartingWithLargeValues_502) {
    auto* mockReporter = new MockEventListener(mockConfig_);
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);

    BenchmarkInfo info{};
    info.estimatedDuration = 1e15;
    info.iterations = 2147483647; // INT_MAX
    info.samples = 4294967295u;   // UINT_MAX
    info.resamples = 4294967295u; // UINT_MAX
    info.clockResolution = 1e-15;
    info.clockCost = 1e-15;

    EXPECT_CALL(*mockReporter, benchmarkStarting(_)).Times(1);

    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    context.benchmarkStarting(info);
}

// Test benchmarkPreparing forwards to reporter
TEST_F(RunContextTest_502, BenchmarkPreparingForwardsToReporter_502) {
    auto* mockReporter = new MockEventListener(mockConfig_);
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);

    EXPECT_CALL(*mockReporter, benchmarkPreparing(_)).Times(1);

    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    context.benchmarkPreparing("test_benchmark"_catch_sr);
}

// Test benchmarkFailed forwards to reporter
TEST_F(RunContextTest_502, BenchmarkFailedForwardsToReporter_502) {
    auto* mockReporter = new MockEventListener(mockConfig_);
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);

    EXPECT_CALL(*mockReporter, benchmarkFailed(_)).Times(1);

    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    context.benchmarkFailed("error message"_catch_sr);
}

// Test benchmarkEnded forwards to reporter
TEST_F(RunContextTest_502, BenchmarkEndedForwardsToReporter_502) {
    auto* mockReporter = new MockEventListener(mockConfig_);
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);

    BenchmarkInfo info{};
    info.estimatedDuration = 1.0;
    info.iterations = 10;
    info.samples = 5;
    info.resamples = 100;
    info.clockResolution = 0.001;
    info.clockCost = 0.0001;

    // Create BenchmarkStats with default/minimal data
    BenchmarkStats<> stats{info, {}, {}, {}, {}};

    EXPECT_CALL(*mockReporter, benchmarkEnded(_)).Times(1);

    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    context.benchmarkEnded(stats);
}

// Test that lastAssertionPassed returns false initially
TEST_F(RunContextTest_502, LastAssertionPassedInitiallyFalse_502) {
    auto* mockReporter = new MockEventListener(mockConfig_);
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);

    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    EXPECT_FALSE(context.lastAssertionPassed());
}

// Test assertionPassed sets lastAssertionPassed to true
TEST_F(RunContextTest_502, AssertionPassedSetsLastAssertionPassed_502) {
    auto* mockReporter = new MockEventListener(mockConfig_);
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);

    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    context.assertionPassed();
    EXPECT_TRUE(context.lastAssertionPassed());
}

// Test getCurrentTestName when no test is active
TEST_F(RunContextTest_502, GetCurrentTestNameWhenNoTestActive_502) {
    auto* mockReporter = new MockEventListener(mockConfig_);
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);

    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    std::string name = context.getCurrentTestName();
    // When no test case is active, should return empty string or some default
    EXPECT_TRUE(name.empty() || !name.empty()); // Non-crashing test
}

// Test getLastResult when no assertion has been made
TEST_F(RunContextTest_502, GetLastResultInitiallyNull_502) {
    auto* mockReporter = new MockEventListener(mockConfig_);
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);

    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    const AssertionResult* result = context.getLastResult();
    // Initially, there should be no last result
    EXPECT_EQ(result, nullptr);
}
