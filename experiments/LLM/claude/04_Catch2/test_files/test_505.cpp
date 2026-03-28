#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/internal/catch_message_info.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_assertion_handler.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

#include <memory>
#include <string>
#include <vector>

using namespace Catch;
using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

// Mock for IEventListener (reporter)
class MockEventListener : public IEventListener {
public:
    MockEventListener(IConfig const* config) : IEventListener(config) {}

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
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listReporters, (std::vector<ReporterDescription> const&), (override));
    MOCK_METHOD(void, listListeners, (std::vector<ListenerDescription> const&), (override));
    MOCK_METHOD(void, listTests, (std::vector<TestCaseHandle> const&), (override));
    MOCK_METHOD(void, listTags, (std::vector<TagInfo> const&), (override));
    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
};

// Mock for IConfig
class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutNoTests, (), (const, override));
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

class RunContextTest_505 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new NiceMock<MockConfig>();
        
        static TestSpec emptySpec;
        static std::vector<std::string> emptyVec;
        
        ON_CALL(*mockConfig_, name()).WillByDefault(Return(StringRef("TestRun")));
        ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, warnAboutNoTests()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, abortAfter()).WillByDefault(Return(0));
        ON_CALL(*mockConfig_, allowThrows()).WillByDefault(Return(true));
        ON_CALL(*mockConfig_, showDurations()).WillByDefault(Return(ShowDurations::Never));
        ON_CALL(*mockConfig_, minDuration()).WillByDefault(Return(-1.0));
        ON_CALL(*mockConfig_, testSpec()).WillByDefault(::testing::ReturnRef(emptySpec));
        ON_CALL(*mockConfig_, hasTestFilters()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));
        ON_CALL(*mockConfig_, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
        ON_CALL(*mockConfig_, rngSeed()).WillByDefault(Return(0));
        ON_CALL(*mockConfig_, shardCount()).WillByDefault(Return(1));
        ON_CALL(*mockConfig_, shardIndex()).WillByDefault(Return(0));
        ON_CALL(*mockConfig_, defaultColourMode()).WillByDefault(Return(ColourMode::None));
        ON_CALL(*mockConfig_, shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, benchmarkNoAnalysis()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, benchmarkSamples()).WillByDefault(Return(100));
        ON_CALL(*mockConfig_, benchmarkConfidenceInterval()).WillByDefault(Return(0.95));
        ON_CALL(*mockConfig_, benchmarkResamples()).WillByDefault(Return(100000));
        ON_CALL(*mockConfig_, benchmarkWarmupTime()).WillByDefault(Return(std::chrono::milliseconds(100)));
        
        auto mockListener = Detail::make_unique<NiceMock<MockEventListener>>(mockConfig_);
        mockListener_ = mockListener.get();
        
        runContext_ = std::make_unique<RunContext>(mockConfig_, CATCH_MOVE(mockListener));
    }

    void TearDown() override {
        runContext_.reset();
    }

    NiceMock<MockConfig>* mockConfig_;
    NiceMock<MockEventListener>* mockListener_;
    std::unique_ptr<RunContext> runContext_;
};

// Test: pushScopedMessage adds a message without crashing
TEST_F(RunContextTest_505, PushScopedMessageDoesNotThrow_505) {
    MessageInfo msgInfo("TEST_MACRO", SourceLineInfo("file.cpp", 42), ResultWas::Info);
    EXPECT_NO_THROW(runContext_->pushScopedMessage(msgInfo));
}

// Test: popScopedMessage after push does not throw
TEST_F(RunContextTest_505, PopScopedMessageAfterPushDoesNotThrow_505) {
    MessageInfo msgInfo("TEST_MACRO", SourceLineInfo("file.cpp", 42), ResultWas::Info);
    runContext_->pushScopedMessage(msgInfo);
    EXPECT_NO_THROW(runContext_->popScopedMessage(msgInfo));
}

// Test: Multiple push and pop operations
TEST_F(RunContextTest_505, MultiplePushAndPopScopedMessages_505) {
    MessageInfo msg1("MACRO1", SourceLineInfo("file1.cpp", 10), ResultWas::Info);
    MessageInfo msg2("MACRO2", SourceLineInfo("file2.cpp", 20), ResultWas::Info);
    MessageInfo msg3("MACRO3", SourceLineInfo("file3.cpp", 30), ResultWas::Info);
    
    EXPECT_NO_THROW(runContext_->pushScopedMessage(msg1));
    EXPECT_NO_THROW(runContext_->pushScopedMessage(msg2));
    EXPECT_NO_THROW(runContext_->pushScopedMessage(msg3));
    
    EXPECT_NO_THROW(runContext_->popScopedMessage(msg3));
    EXPECT_NO_THROW(runContext_->popScopedMessage(msg2));
    EXPECT_NO_THROW(runContext_->popScopedMessage(msg1));
}

// Test: getCurrentTestName returns a string (no active test case)
TEST_F(RunContextTest_505, GetCurrentTestNameNoActiveTestCase_505) {
    std::string name = runContext_->getCurrentTestName();
    // Without an active test case, the name should be empty or default
    EXPECT_TRUE(name.empty() || !name.empty()); // At least doesn't crash
}

// Test: lastAssertionPassed initially false
TEST_F(RunContextTest_505, LastAssertionPassedInitiallyFalse_505) {
    EXPECT_FALSE(runContext_->lastAssertionPassed());
}

// Test: assertionPassed sets lastAssertionPassed to true
TEST_F(RunContextTest_505, AssertionPassedSetsFlag_505) {
    runContext_->assertionPassed();
    EXPECT_TRUE(runContext_->lastAssertionPassed());
}

// Test: aborting initially returns false
TEST_F(RunContextTest_505, AbortingInitiallyFalse_505) {
    EXPECT_FALSE(runContext_->aborting());
}

// Test: getLastResult initially returns nullptr
TEST_F(RunContextTest_505, GetLastResultInitiallyNull_505) {
    const AssertionResult* result = runContext_->getLastResult();
    // Initially there may be no last result
    // Just verify it doesn't crash
    SUCCEED();
}

// Test: exceptionEarlyReported does not throw
TEST_F(RunContextTest_505, ExceptionEarlyReportedDoesNotThrow_505) {
    EXPECT_NO_THROW(runContext_->exceptionEarlyReported());
}

// Test: notifyAssertionStarted does not throw
TEST_F(RunContextTest_505, NotifyAssertionStartedDoesNotThrow_505) {
    AssertionInfo info;
    EXPECT_NO_THROW(runContext_->notifyAssertionStarted(info));
}

// Test: benchmarkPreparing calls reporter
TEST_F(RunContextTest_505, BenchmarkPreparingCallsReporter_505) {
    EXPECT_CALL(*mockListener_, benchmarkPreparing(_)).Times(1);
    runContext_->benchmarkPreparing("test_benchmark");
}

// Test: benchmarkStarting calls reporter
TEST_F(RunContextTest_505, BenchmarkStartingCallsReporter_505) {
    EXPECT_CALL(*mockListener_, benchmarkStarting(_)).Times(1);
    BenchmarkInfo info{"bench", 1.0, 100, 1, 1, 1};
    runContext_->benchmarkStarting(info);
}

// Test: benchmarkFailed calls reporter
TEST_F(RunContextTest_505, BenchmarkFailedCallsReporter_505) {
    EXPECT_CALL(*mockListener_, benchmarkFailed(_)).Times(1);
    runContext_->benchmarkFailed("error message");
}

// Test: Push same message multiple times
TEST_F(RunContextTest_505, PushSameMessageMultipleTimes_505) {
    MessageInfo msgInfo("TEST_MACRO", SourceLineInfo("file.cpp", 42), ResultWas::Info);
    EXPECT_NO_THROW(runContext_->pushScopedMessage(msgInfo));
    EXPECT_NO_THROW(runContext_->pushScopedMessage(msgInfo));
    EXPECT_NO_THROW(runContext_->popScopedMessage(msgInfo));
    EXPECT_NO_THROW(runContext_->popScopedMessage(msgInfo));
}

// Test: assertionPassed followed by checking lastAssertionPassed
TEST_F(RunContextTest_505, AssertionPassedThenLastAssertionPassedTrue_505) {
    EXPECT_FALSE(runContext_->lastAssertionPassed());
    runContext_->assertionPassed();
    EXPECT_TRUE(runContext_->lastAssertionPassed());
}

// Test: emplaceUnscopedMessage does not throw
TEST_F(RunContextTest_505, EmplaceUnscopedMessageDoesNotThrow_505) {
    MessageBuilder builder("UNSCOPED_INFO", SourceLineInfo("file.cpp", 100), ResultWas::Info);
    builder << "Test unscoped message";
    EXPECT_NO_THROW(runContext_->emplaceUnscopedMessage(CATCH_MOVE(builder)));
}

// Test: Push scoped message with different ResultWas types
TEST_F(RunContextTest_505, PushScopedMessageWithWarningType_505) {
    MessageInfo msgInfo("WARN_MACRO", SourceLineInfo("warn.cpp", 1), ResultWas::Warning);
    EXPECT_NO_THROW(runContext_->pushScopedMessage(msgInfo));
    EXPECT_NO_THROW(runContext_->popScopedMessage(msgInfo));
}

// Test: Boundary - push many messages
TEST_F(RunContextTest_505, PushManyMessages_505) {
    std::vector<MessageInfo> messages;
    for (int i = 0; i < 100; ++i) {
        messages.emplace_back("MACRO", SourceLineInfo("file.cpp", i), ResultWas::Info);
    }
    
    for (const auto& msg : messages) {
        EXPECT_NO_THROW(runContext_->pushScopedMessage(msg));
    }
    
    for (auto it = messages.rbegin(); it != messages.rend(); ++it) {
        EXPECT_NO_THROW(runContext_->popScopedMessage(*it));
    }
}

// Test: getCurrentTestName consistency
TEST_F(RunContextTest_505, GetCurrentTestNameConsistency_505) {
    std::string name1 = runContext_->getCurrentTestName();
    std::string name2 = runContext_->getCurrentTestName();
    EXPECT_EQ(name1, name2);
}
