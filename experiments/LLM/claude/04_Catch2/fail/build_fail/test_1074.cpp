#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_test_spec.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::NiceMock;
using ::testing::Invoke;
using ::testing::AtLeast;

// Mock IConfig
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

// Mock IEventListener
class MockEventListener : public IEventListener {
public:
    explicit MockEventListener(IConfig const* config) : IEventListener(config) {}

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

class RunContextTest_1074 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new NiceMock<MockConfig>();
        
        ON_CALL(*mockConfig_, name()).WillByDefault(Return(StringRef("TestRun")));
        ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, allowThrows()).WillByDefault(Return(true));
        ON_CALL(*mockConfig_, shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, abortAfter()).WillByDefault(Return(0));
        ON_CALL(*mockConfig_, showDurations()).WillByDefault(Return(ShowDurations::Never));
        ON_CALL(*mockConfig_, verbosity()).WillByDefault(Return(Verbosity::Normal));
    }

    void TearDown() override {
        Catch::cleanUpContext();
    }

    NiceMock<MockConfig>* mockConfig_ = nullptr;

    Detail::unique_ptr<RunContext> createRunContext(MockEventListener*& outListener) {
        auto* listener = new NiceMock<MockEventListener>(mockConfig_);
        outListener = listener;
        IEventListenerPtr reporterPtr(listener);
        return Detail::unique_ptr<RunContext>(
            new RunContext(mockConfig_, CATCH_MOVE(reporterPtr))
        );
    }
};

// Test that construction calls testRunStarting on the reporter
TEST_F(RunContextTest_1074, ConstructorCallsTestRunStarting_1074) {
    auto* listener = new NiceMock<MockEventListener>(mockConfig_);
    
    EXPECT_CALL(*listener, testRunStarting(_)).Times(1);
    
    IEventListenerPtr reporterPtr(listener);
    auto runContext = Detail::unique_ptr<RunContext>(
        new RunContext(mockConfig_, CATCH_MOVE(reporterPtr))
    );
}

// Test that after construction, the result capture is set in the context
TEST_F(RunContextTest_1074, ConstructorSetsResultCapture_1074) {
    MockEventListener* listener = nullptr;
    auto runContext = createRunContext(listener);
    
    auto* resultCapture = getCurrentMutableContext().getResultCapture();
    EXPECT_NE(resultCapture, nullptr);
    EXPECT_EQ(resultCapture, runContext.get());
}

// Test that config name is used for run info
TEST_F(RunContextTest_1074, ConstructorUsesConfigName_1074) {
    EXPECT_CALL(*mockConfig_, name()).WillRepeatedly(Return(StringRef("MyTestRun")));
    
    auto* listener = new NiceMock<MockEventListener>(mockConfig_);
    
    EXPECT_CALL(*listener, testRunStarting(_)).WillOnce(Invoke([](const TestRunInfo& info) {
        EXPECT_EQ(info.name, "MyTestRun");
    }));
    
    IEventListenerPtr reporterPtr(listener);
    auto runContext = Detail::unique_ptr<RunContext>(
        new RunContext(mockConfig_, CATCH_MOVE(reporterPtr))
    );
}

// Test lastAssertionPassed returns false initially
TEST_F(RunContextTest_1074, LastAssertionPassedInitiallyFalse_1074) {
    MockEventListener* listener = nullptr;
    auto runContext = createRunContext(listener);
    
    EXPECT_FALSE(runContext->lastAssertionPassed());
}

// Test assertionPassed sets lastAssertionPassed to true
TEST_F(RunContextTest_1074, AssertionPassedSetsFlag_1074) {
    MockEventListener* listener = nullptr;
    auto runContext = createRunContext(listener);
    
    runContext->assertionPassed();
    EXPECT_TRUE(runContext->lastAssertionPassed());
}

// Test getCurrentTestName returns empty string when no test is active
TEST_F(RunContextTest_1074, GetCurrentTestNameEmptyWhenNoActiveTest_1074) {
    MockEventListener* listener = nullptr;
    auto runContext = createRunContext(listener);
    
    std::string name = runContext->getCurrentTestName();
    EXPECT_TRUE(name.empty());
}

// Test getLastResult returns nullptr when no assertions have been made
TEST_F(RunContextTest_1074, GetLastResultNullptrInitially_1074) {
    MockEventListener* listener = nullptr;
    auto runContext = createRunContext(listener);
    
    const AssertionResult* result = runContext->getLastResult();
    EXPECT_EQ(result, nullptr);
}

// Test aborting returns false initially (no abort configured)
TEST_F(RunContextTest_1074, AbortingReturnsFalseInitially_1074) {
    ON_CALL(*mockConfig_, abortAfter()).WillByDefault(Return(0));
    
    MockEventListener* listener = nullptr;
    auto runContext = createRunContext(listener);
    
    EXPECT_FALSE(runContext->aborting());
}

// Test includeSuccessfulResults when config says true
TEST_F(RunContextTest_1074, IncludeSuccessfulResultsFromConfig_1074) {
    ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(Return(true));
    
    auto* listener = new NiceMock<MockEventListener>(mockConfig_);
    EXPECT_CALL(*listener, testRunStarting(_)).Times(1);
    
    IEventListenerPtr reporterPtr(listener);
    // Should not crash; just testing construction with different config
    auto runContext = Detail::unique_ptr<RunContext>(
        new RunContext(mockConfig_, CATCH_MOVE(reporterPtr))
    );
    EXPECT_NE(runContext.get(), nullptr);
}

// Test that notifyAssertionStarted can be called without crash
TEST_F(RunContextTest_1074, NotifyAssertionStartedDoesNotCrash_1074) {
    MockEventListener* listener = nullptr;
    auto runContext = createRunContext(listener);
    
    EXPECT_CALL(*listener, assertionStarting(_)).Times(1);
    
    AssertionInfo info{"test macro", SourceLineInfo("file.cpp", 42), "expression", ResultDisposition::Normal};
    runContext->notifyAssertionStarted(info);
}

// Test construction with empty name
TEST_F(RunContextTest_1074, ConstructorWithEmptyName_1074) {
    EXPECT_CALL(*mockConfig_, name()).WillRepeatedly(Return(StringRef("")));
    
    auto* listener = new NiceMock<MockEventListener>(mockConfig_);
    
    EXPECT_CALL(*listener, testRunStarting(_)).WillOnce(Invoke([](const TestRunInfo& info) {
        EXPECT_TRUE(info.name.empty());
    }));
    
    IEventListenerPtr reporterPtr(listener);
    auto runContext = Detail::unique_ptr<RunContext>(
        new RunContext(mockConfig_, CATCH_MOVE(reporterPtr))
    );
}

// Test benchmarkPreparing forwards to reporter
TEST_F(RunContextTest_1074, BenchmarkPreparingForwardsToReporter_1074) {
    MockEventListener* listener = nullptr;
    auto runContext = createRunContext(listener);
    
    EXPECT_CALL(*listener, benchmarkPreparing(_)).Times(1);
    
    runContext->benchmarkPreparing("my_benchmark");
}

// Test benchmarkFailed forwards to reporter
TEST_F(RunContextTest_1074, BenchmarkFailedForwardsToReporter_1074) {
    MockEventListener* listener = nullptr;
    auto runContext = createRunContext(listener);
    
    EXPECT_CALL(*listener, benchmarkFailed(_)).Times(1);
    
    runContext->benchmarkFailed("benchmark error");
}

// Test exceptionEarlyReported does not crash
TEST_F(RunContextTest_1074, ExceptionEarlyReportedDoesNotCrash_1074) {
    MockEventListener* listener = nullptr;
    auto runContext = createRunContext(listener);
    
    EXPECT_NO_FATAL_FAILURE(runContext->exceptionEarlyReported());
}

// Test that assertionPassed then lastAssertionPassed works correctly
TEST_F(RunContextTest_1074, AssertionPassedThenLastAssertionPassed_1074) {
    MockEventListener* listener = nullptr;
    auto runContext = createRunContext(listener);
    
    EXPECT_FALSE(runContext->lastAssertionPassed());
    runContext->assertionPassed();
    EXPECT_TRUE(runContext->lastAssertionPassed());
}

// Test that the reporter preferences affect shouldRedirectStdOut behavior
TEST_F(RunContextTest_1074, ReporterPreferencesRespected_1074) {
    auto* listener = new NiceMock<MockEventListener>(mockConfig_);
    // Default preferences: shouldRedirectStdOut = false, shouldReportAllAssertions = false
    
    EXPECT_CALL(*listener, testRunStarting(_)).Times(1);
    
    IEventListenerPtr reporterPtr(listener);
    auto runContext = Detail::unique_ptr<RunContext>(
        new RunContext(mockConfig_, CATCH_MOVE(reporterPtr))
    );
    
    EXPECT_NE(runContext.get(), nullptr);
}

// Test construction with includeSuccessfulResults false and reporter not requesting all assertions
TEST_F(RunContextTest_1074, NoIncludeSuccessfulResultsNoReportAll_1074) {
    ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(Return(false));
    
    auto* listener = new NiceMock<MockEventListener>(mockConfig_);
    // Default m_preferences.shouldReportAllAssertions is false
    
    EXPECT_CALL(*listener, testRunStarting(_)).Times(1);
    
    IEventListenerPtr reporterPtr(listener);
    auto runContext = Detail::unique_ptr<RunContext>(
        new RunContext(mockConfig_, CATCH_MOVE(reporterPtr))
    );
    
    EXPECT_NE(runContext.get(), nullptr);
}
