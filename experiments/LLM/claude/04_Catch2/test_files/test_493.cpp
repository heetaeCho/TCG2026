#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_test_run_info.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/benchmark/catch_benchmark_stats.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::NiceMock;

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
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

// Mock for IEventListener (reporter)
class MockReporter : public IEventListener {
public:
    MockReporter(IConfig const* config) : IEventListener(config) {}

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

class RunContextTest_493 : public ::testing::Test {
protected:
    void SetUp() override {
        config_ = new NiceMock<MockConfig>();
        ON_CALL(*config_, name()).WillByDefault(Return(StringRef("TestRun")));
        ON_CALL(*config_, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(*config_, abortAfter()).WillByDefault(Return(0));
        ON_CALL(*config_, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(*config_, allowThrows()).WillByDefault(Return(true));
        
        std::vector<std::string> empty;
        ON_CALL(*config_, getSectionsToRun()).WillByDefault(::testing::ReturnRef(emptyStrVec_));
    }

    void TearDown() override {
        // config_ is not owned by us if passed to RunContext, but since RunContext
        // takes a raw pointer, we manage it here
    }

    std::unique_ptr<RunContext> createRunContext(MockReporter*& reporterRawPtr) {
        auto reporter = Detail::unique_ptr<IEventListener>(
            new NiceMock<MockReporter>(config_));
        reporterRawPtr = static_cast<MockReporter*>(reporter.get());
        return std::make_unique<RunContext>(config_, CATCH_MOVE(reporter));
    }

    NiceMock<MockConfig>* config_ = nullptr;
    std::vector<std::string> emptyStrVec_;
};

// Test: Destructor calls testRunEnded on reporter
TEST_F(RunContextTest_493, DestructorCallsTestRunEnded_493) {
    MockReporter* reporterPtr = nullptr;
    {
        auto reporter = Detail::unique_ptr<IEventListener>(
            new NiceMock<MockReporter>(config_));
        reporterPtr = static_cast<MockReporter*>(reporter.get());

        EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(AtLeast(0));
        EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);

        RunContext ctx(config_, CATCH_MOVE(reporter));
        // Destructor should call testRunEnded
    }
}

// Test: getCurrentTestName returns empty string when no test is running
TEST_F(RunContextTest_493, GetCurrentTestNameNoActiveTest_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);

    RunContext ctx(config_, CATCH_MOVE(reporter));
    std::string name = ctx.getCurrentTestName();
    // With no active test case, the name should be empty
    EXPECT_TRUE(name.empty());
}

// Test: lastAssertionPassed initially returns false
TEST_F(RunContextTest_493, LastAssertionPassedInitiallyFalse_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);

    RunContext ctx(config_, CATCH_MOVE(reporter));
    EXPECT_FALSE(ctx.lastAssertionPassed());
}

// Test: assertionPassed sets lastAssertionPassed to true
TEST_F(RunContextTest_493, AssertionPassedSetsFlag_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);

    RunContext ctx(config_, CATCH_MOVE(reporter));
    ctx.assertionPassed();
    EXPECT_TRUE(ctx.lastAssertionPassed());
}

// Test: getLastResult returns nullptr initially
TEST_F(RunContextTest_493, GetLastResultInitiallyNull_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);

    RunContext ctx(config_, CATCH_MOVE(reporter));
    const AssertionResult* result = ctx.getLastResult();
    EXPECT_EQ(result, nullptr);
}

// Test: aborting returns false initially (abortAfter is 0 meaning no abort limit)
TEST_F(RunContextTest_493, AbortingReturnsFalseInitially_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);

    RunContext ctx(config_, CATCH_MOVE(reporter));
    EXPECT_FALSE(ctx.aborting());
}

// Test: notifyAssertionStarted calls reporter's assertionStarting
TEST_F(RunContextTest_493, NotifyAssertionStartedCallsReporter_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);
    EXPECT_CALL(*reporterPtr, assertionStarting(_)).Times(1);

    RunContext ctx(config_, CATCH_MOVE(reporter));
    
    AssertionInfo info{"test", SourceLineInfo("file.cpp", 1), StringRef(), ResultDisposition::Normal};
    ctx.notifyAssertionStarted(info);
}

// Test: benchmarkPreparing calls reporter's benchmarkPreparing
TEST_F(RunContextTest_493, BenchmarkPreparingCallsReporter_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);
    EXPECT_CALL(*reporterPtr, benchmarkPreparing(_)).Times(1);

    RunContext ctx(config_, CATCH_MOVE(reporter));
    ctx.benchmarkPreparing("bench1");
}

// Test: benchmarkStarting calls reporter's benchmarkStarting
TEST_F(RunContextTest_493, BenchmarkStartingCallsReporter_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);
    EXPECT_CALL(*reporterPtr, benchmarkStarting(_)).Times(1);

    RunContext ctx(config_, CATCH_MOVE(reporter));
    BenchmarkInfo benchInfo{"bench1", 1.0, 100, 1, 1, 1};
    ctx.benchmarkStarting(benchInfo);
}

// Test: benchmarkFailed calls reporter's benchmarkFailed
TEST_F(RunContextTest_493, BenchmarkFailedCallsReporter_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);
    EXPECT_CALL(*reporterPtr, benchmarkFailed(_)).Times(1);

    RunContext ctx(config_, CATCH_MOVE(reporter));
    ctx.benchmarkFailed("error message");
}

// Test: exceptionEarlyReported does not crash
TEST_F(RunContextTest_493, ExceptionEarlyReportedDoesNotCrash_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);

    RunContext ctx(config_, CATCH_MOVE(reporter));
    EXPECT_NO_THROW(ctx.exceptionEarlyReported());
}

// Test: Multiple assertionPassed calls keep the flag true
TEST_F(RunContextTest_493, MultipleAssertionPassedKeepsFlagTrue_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);

    RunContext ctx(config_, CATCH_MOVE(reporter));
    ctx.assertionPassed();
    ctx.assertionPassed();
    ctx.assertionPassed();
    EXPECT_TRUE(ctx.lastAssertionPassed());
}

// Test: testRunEnded receives correct run info name
TEST_F(RunContextTest_493, TestRunEndedReceivesCorrectRunName_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(::testing::_))
        .WillOnce([](const TestRunStats& stats) {
            EXPECT_EQ(stats.runInfo.name, "TestRun");
        });

    {
        RunContext ctx(config_, CATCH_MOVE(reporter));
    }
}

// Test: Config with abortAfter(0) means not aborting
TEST_F(RunContextTest_493, AbortAfterZeroMeansNotAborting_493) {
    ON_CALL(*config_, abortAfter()).WillByDefault(Return(0));

    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);

    RunContext ctx(config_, CATCH_MOVE(reporter));
    EXPECT_FALSE(ctx.aborting());
}

// Test: Copy constructor is deleted (compile-time check - this is a static assertion test)
// We verify this indirectly: the class declares copy constructor as deleted.
// We just verify the object can be constructed and destroyed properly.
TEST_F(RunContextTest_493, ConstructionAndDestruction_493) {
    MockReporter* reporterPtr = nullptr;
    auto reporter = Detail::unique_ptr<IEventListener>(
        new NiceMock<MockReporter>(config_));
    reporterPtr = static_cast<MockReporter*>(reporter.get());

    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(1);

    EXPECT_NO_THROW({
        RunContext ctx(config_, CATCH_MOVE(reporter));
    });
}
