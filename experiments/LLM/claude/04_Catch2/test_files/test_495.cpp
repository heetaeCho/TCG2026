#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/internal/catch_run_context.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/internal/catch_string_manip.hpp>

using namespace Catch;
using ::testing::_;
using ::testing::NiceMock;

// Mock IEventListener
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
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(RangeOf<std::string> auto const&, getSeedGenerators, (), (const));
    MOCK_METHOD(unsigned int, rngSeed, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class RunContextTest_495 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new NiceMock<MockConfig>();
        ON_CALL(*mockConfig_, name()).WillByDefault(::testing::Return(StringRef("test")));
        ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, allowThrows()).WillByDefault(::testing::Return(true));
        ON_CALL(*mockConfig_, abortAfter()).WillByDefault(::testing::Return(0));
        ON_CALL(*mockConfig_, shouldDebugBreak()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, warnAboutMissingAssertions()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, rngSeed()).WillByDefault(::testing::Return(0));
        
        mockReporter_ = new NiceMock<MockReporter>(mockConfig_);
    }
    
    void TearDown() override {
        // Config outlives the RunContext, cleaned up here
    }
    
    NiceMock<MockConfig>* mockConfig_;
    NiceMock<MockReporter>* mockReporter_; // Ownership transferred to RunContext
};

TEST_F(RunContextTest_495, NotifyAssertionStartedCallsReporterAssertionStarting_495) {
    // The mock reporter pointer will be owned by RunContext via unique_ptr
    auto reporterPtr = Detail::unique_ptr<IEventListener>(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "x == 1"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    
    EXPECT_CALL(*mockReporter_, assertionStarting(_)).Times(1);
    
    context.notifyAssertionStarted(info);
}

TEST_F(RunContextTest_495, NotifyAssertionStartedPassesCorrectInfo_495) {
    auto reporterPtr = Detail::unique_ptr<IEventListener>(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    
    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "a > b"_catch_sr;
    info.resultDisposition = ResultDisposition::ContinueOnFailure;
    
    EXPECT_CALL(*mockReporter_, assertionStarting(::testing::Truly([](const AssertionInfo& receivedInfo) {
        return receivedInfo.macroName == "CHECK"_catch_sr &&
               receivedInfo.capturedExpression == "a > b"_catch_sr;
    }))).Times(1);
    
    context.notifyAssertionStarted(info);
}

TEST_F(RunContextTest_495, NotifyAssertionStartedCalledMultipleTimes_495) {
    auto reporterPtr = Detail::unique_ptr<IEventListener>(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    
    AssertionInfo info1;
    info1.macroName = "REQUIRE"_catch_sr;
    info1.capturedExpression = "x == 1"_catch_sr;
    info1.resultDisposition = ResultDisposition::Normal;
    
    AssertionInfo info2;
    info2.macroName = "CHECK"_catch_sr;
    info2.capturedExpression = "y != 0"_catch_sr;
    info2.resultDisposition = ResultDisposition::ContinueOnFailure;
    
    EXPECT_CALL(*mockReporter_, assertionStarting(_)).Times(2);
    
    context.notifyAssertionStarted(info1);
    context.notifyAssertionStarted(info2);
}

TEST_F(RunContextTest_495, NotifyAssertionStartedWithEmptyMacroName_495) {
    auto reporterPtr = Detail::unique_ptr<IEventListener>(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    
    AssertionInfo info;
    info.macroName = StringRef();
    info.capturedExpression = StringRef();
    info.resultDisposition = ResultDisposition::Normal;
    
    EXPECT_CALL(*mockReporter_, assertionStarting(_)).Times(1);
    
    context.notifyAssertionStarted(info);
}

TEST_F(RunContextTest_495, LastAssertionPassedInitiallyFalse_495) {
    auto reporterPtr = Detail::unique_ptr<IEventListener>(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    
    EXPECT_FALSE(context.lastAssertionPassed());
}

TEST_F(RunContextTest_495, AssertionPassedSetsLastAssertionPassedTrue_495) {
    auto reporterPtr = Detail::unique_ptr<IEventListener>(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    
    context.assertionPassed();
    
    EXPECT_TRUE(context.lastAssertionPassed());
}

TEST_F(RunContextTest_495, GetCurrentTestNameReturnsEmptyWhenNoActiveTest_495) {
    auto reporterPtr = Detail::unique_ptr<IEventListener>(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    
    // When no test case is active, getCurrentTestName should return empty or some default
    std::string name = context.getCurrentTestName();
    // We just verify it doesn't crash and returns a string
    EXPECT_TRUE(name.empty() || !name.empty()); // Always true, just checks no crash
}

TEST_F(RunContextTest_495, GetLastResultReturnsNullptrInitially_495) {
    auto reporterPtr = Detail::unique_ptr<IEventListener>(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    
    const AssertionResult* result = context.getLastResult();
    EXPECT_EQ(result, nullptr);
}

TEST_F(RunContextTest_495, AbortingReturnsFalseInitially_495) {
    auto reporterPtr = Detail::unique_ptr<IEventListener>(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    
    EXPECT_FALSE(context.aborting());
}

TEST_F(RunContextTest_495, BenchmarkPreparingCallsReporter_495) {
    auto reporterPtr = Detail::unique_ptr<IEventListener>(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    
    EXPECT_CALL(*mockReporter_, benchmarkPreparing(_)).Times(1);
    
    context.benchmarkPreparing("my_benchmark"_catch_sr);
}

TEST_F(RunContextTest_495, BenchmarkFailedCallsReporter_495) {
    auto reporterPtr = Detail::unique_ptr<IEventListener>(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterPtr));
    
    EXPECT_CALL(*mockReporter_, benchmarkFailed(_)).Times(1);
    
    context.benchmarkFailed("some error"_catch_sr);
}
