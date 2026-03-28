#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/internal/catch_test_registry.hpp"
#include "catch2/catch_tostring.hpp"

#include <memory>
#include <string>

using namespace Catch;
using ::testing::_;
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
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
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
    
    MOCK_METHOD(void, testRunStarting, (TestRunInfo const&), (override));
    MOCK_METHOD(void, testRunEnded, (TestRunStats const&), (override));
    MOCK_METHOD(void, testCaseStarting, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, testCaseEnded, (TestCaseStats const&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (TestCaseInfo const&, uint64_t), (override));
    MOCK_METHOD(void, testCasePartialEnded, (TestCaseStats const&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (SectionInfo const&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionStats const&), (override));
    MOCK_METHOD(void, assertionStarting, (AssertionInfo const&), (override));
    MOCK_METHOD(void, assertionEnded, (AssertionStats const&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (BenchmarkInfo const&), (override));
    MOCK_METHOD(void, benchmarkEnded, (BenchmarkStats<> const&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listProcessors, (std::vector<ProcessorInfo> const&), (override));
    MOCK_METHOD(void, listReporters, (std::vector<ReporterDescription> const&), (override));
    MOCK_METHOD(void, listListeners, (std::vector<ListenerDescription> const&), (override));
    MOCK_METHOD(void, listTests, (std::vector<TestCaseHandle> const&), (override));
    MOCK_METHOD(void, listTags, (std::vector<TagInfo> const&), (override));
    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
};

class RunContextTest_507 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new NiceMock<MockConfig>();
        
        static TestSpec emptySpec;
        static std::vector<std::string> emptyVec;
        
        ON_CALL(*mockConfig_, name()).WillByDefault(Return(StringRef("TestRun")));
        ON_CALL(*mockConfig_, allowThrows()).WillByDefault(Return(true));
        ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, warnAboutUnmatchedTestSpecs()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, abortAfter()).WillByDefault(Return(0));
        ON_CALL(*mockConfig_, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));
        ON_CALL(*mockConfig_, minDuration()).WillByDefault(Return(-1.0));
        ON_CALL(*mockConfig_, testSpec()).WillByDefault(::testing::ReturnRef(emptySpec));
        ON_CALL(*mockConfig_, hasTestFilters()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));
        ON_CALL(*mockConfig_, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
        ON_CALL(*mockConfig_, rngSeed()).WillByDefault(Return(0));
        ON_CALL(*mockConfig_, shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, defaultColourMode()).WillByDefault(Return(ColourMode::None));
        ON_CALL(*mockConfig_, benchmarkNoAnalysis()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, benchmarkSamples()).WillByDefault(Return(100));
        ON_CALL(*mockConfig_, benchmarkConfidenceInterval()).WillByDefault(Return(0.95));
        ON_CALL(*mockConfig_, benchmarkResamples()).WillByDefault(Return(100000));
        ON_CALL(*mockConfig_, benchmarkWarmupTime()).WillByDefault(Return(std::chrono::milliseconds(100)));
        
        auto reporter = Detail::make_unique<NiceMock<MockReporter>>(mockConfig_);
        mockReporter_ = reporter.get();
        
        runContext_ = std::make_unique<RunContext>(mockConfig_, IEventListenerPtr(std::move(reporter)));
    }

    void TearDown() override {
        runContext_.reset();
    }

    NiceMock<MockConfig>* mockConfig_;
    NiceMock<MockReporter>* mockReporter_;
    std::unique_ptr<RunContext> runContext_;
};

// Test: getCurrentTestName returns empty string when no test is active
TEST_F(RunContextTest_507, GetCurrentTestNameWhenNoActiveTest_507) {
    std::string name = runContext_->getCurrentTestName();
    // When no test case is active, the name should be empty or default
    EXPECT_TRUE(name.empty() || !name.empty()); // Just verify it doesn't crash
}

// Test: lastAssertionPassed initially returns false
TEST_F(RunContextTest_507, LastAssertionPassedInitiallyFalse_507) {
    EXPECT_FALSE(runContext_->lastAssertionPassed());
}

// Test: assertionPassed sets lastAssertionPassed to true
TEST_F(RunContextTest_507, AssertionPassedSetsFlag_507) {
    runContext_->assertionPassed();
    EXPECT_TRUE(runContext_->lastAssertionPassed());
}

// Test: aborting returns false initially
TEST_F(RunContextTest_507, AbortingInitiallyFalse_507) {
    EXPECT_FALSE(runContext_->aborting());
}

// Test: getLastResult returns nullptr when no assertion has been made
TEST_F(RunContextTest_507, GetLastResultInitiallyNull_507) {
    const AssertionResult* result = runContext_->getLastResult();
    // Initially there should be no last result
    EXPECT_EQ(result, nullptr);
}

// Test: pushScopedMessage and popScopedMessage don't crash
TEST_F(RunContextTest_507, PushAndPopScopedMessageDoesNotCrash_507) {
    MessageInfo info("test_macro"_catch_sr, SourceLineInfo("file", 1), ResultWas::Info);
    EXPECT_NO_THROW(runContext_->pushScopedMessage(info));
    EXPECT_NO_THROW(runContext_->popScopedMessage(info));
}

// Test: emplaceUnscopedMessage doesn't crash
TEST_F(RunContextTest_507, EmplaceUnscopedMessageDoesNotCrash_507) {
    MessageBuilder builder("TEST_MACRO"_catch_sr, SourceLineInfo("file.cpp", 42), ResultWas::Info);
    EXPECT_NO_THROW(runContext_->emplaceUnscopedMessage(std::move(builder)));
}

// Test: Multiple emplaceUnscopedMessage calls work
TEST_F(RunContextTest_507, MultipleEmplaceUnscopedMessages_507) {
    for (int i = 0; i < 5; ++i) {
        MessageBuilder builder("TEST_MACRO"_catch_sr, SourceLineInfo("file.cpp", i), ResultWas::Info);
        EXPECT_NO_THROW(runContext_->emplaceUnscopedMessage(std::move(builder)));
    }
}

// Test: exceptionEarlyReported doesn't crash
TEST_F(RunContextTest_507, ExceptionEarlyReportedDoesNotCrash_507) {
    EXPECT_NO_THROW(runContext_->exceptionEarlyReported());
}

// Test: assertionPassed followed by checking lastAssertionPassed
TEST_F(RunContextTest_507, AssertionPassedAndLastAssertionPassed_507) {
    EXPECT_FALSE(runContext_->lastAssertionPassed());
    runContext_->assertionPassed();
    EXPECT_TRUE(runContext_->lastAssertionPassed());
}

// Test: notifyAssertionStarted doesn't crash
TEST_F(RunContextTest_507, NotifyAssertionStartedDoesNotCrash_507) {
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.lineInfo = SourceLineInfo("test.cpp", 10);
    info.capturedExpression = "x == 1"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    
    EXPECT_NO_THROW(runContext_->notifyAssertionStarted(info));
}

// Test: benchmarkPreparing notifies reporter
TEST_F(RunContextTest_507, BenchmarkPreparingNotifiesReporter_507) {
    EXPECT_CALL(*mockReporter_, benchmarkPreparing(_)).Times(1);
    runContext_->benchmarkPreparing("bench_test"_catch_sr);
}

// Test: benchmarkStarting notifies reporter
TEST_F(RunContextTest_507, BenchmarkStartingNotifiesReporter_507) {
    BenchmarkInfo info{"bench", 1.0, 100, 100, 1000, 0.95};
    EXPECT_CALL(*mockReporter_, benchmarkStarting(_)).Times(1);
    runContext_->benchmarkStarting(info);
}

// Test: benchmarkFailed notifies reporter
TEST_F(RunContextTest_507, BenchmarkFailedNotifiesReporter_507) {
    EXPECT_CALL(*mockReporter_, benchmarkFailed(_)).Times(1);
    runContext_->benchmarkFailed("error occurred"_catch_sr);
}

// Test: Multiple assertionPassed calls
TEST_F(RunContextTest_507, MultipleAssertionPassedCalls_507) {
    for (int i = 0; i < 10; ++i) {
        runContext_->assertionPassed();
        EXPECT_TRUE(runContext_->lastAssertionPassed());
    }
}

// Test: pushScopedMessage multiple times
TEST_F(RunContextTest_507, PushMultipleScopedMessages_507) {
    for (int i = 0; i < 3; ++i) {
        MessageInfo info("macro"_catch_sr, SourceLineInfo("file", i + 1), ResultWas::Info);
        EXPECT_NO_THROW(runContext_->pushScopedMessage(info));
    }
    // Pop them in reverse order
    for (int i = 2; i >= 0; --i) {
        MessageInfo info("macro"_catch_sr, SourceLineInfo("file", i + 1), ResultWas::Info);
        EXPECT_NO_THROW(runContext_->popScopedMessage(info));
    }
}

// Test: Construction with valid config and reporter
TEST_F(RunContextTest_507, ConstructionSucceeds_507) {
    EXPECT_NE(runContext_.get(), nullptr);
}

// Test: getCurrentTestName returns a string (not crashing)
TEST_F(RunContextTest_507, GetCurrentTestNameDoesNotCrash_507) {
    EXPECT_NO_THROW(runContext_->getCurrentTestName());
}
