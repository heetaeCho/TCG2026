#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/internal/catch_message_info.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/internal/catch_noncopyable.hpp"

#include <memory>
#include <string>

namespace {

// Mock for IConfig
class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(Catch::TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
    MOCK_METHOD(Catch::OutputRedirectUsage, outputRedirectUsage, (), (const, override));
};

// Mock for IEventListener (reporter)
class MockReporter : public Catch::IEventListener {
public:
    MockReporter(Catch::IConfig const* config) : Catch::IEventListener(config) {}
    
    MOCK_METHOD(void, testRunStarting, (Catch::TestRunInfo const&), (override));
    MOCK_METHOD(void, testRunEnded, (Catch::TestRunStats const&), (override));
    MOCK_METHOD(void, testCaseStarting, (Catch::TestCaseInfo const&), (override));
    MOCK_METHOD(void, testCaseEnded, (Catch::TestCaseStats const&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (Catch::TestCaseInfo const&, uint64_t), (override));
    MOCK_METHOD(void, testCasePartialEnded, (Catch::TestCaseStats const&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (Catch::SectionInfo const&), (override));
    MOCK_METHOD(void, sectionEnded, (Catch::SectionStats const&), (override));
    MOCK_METHOD(void, assertionStarting, (Catch::AssertionInfo const&), (override));
    MOCK_METHOD(void, assertionEnded, (Catch::AssertionStats const&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (Catch::StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (Catch::BenchmarkInfo const&), (override));
    MOCK_METHOD(void, benchmarkEnded, (Catch::BenchmarkStats<> const&), (override));
    MOCK_METHOD(void, benchmarkFailed, (Catch::StringRef), (override));
    MOCK_METHOD(void, listReporters, (std::vector<Catch::ReporterDescription> const&), (override));
    MOCK_METHOD(void, listListeners, (std::vector<Catch::ListenerDescription> const&), (override));
    MOCK_METHOD(void, listTests, (std::vector<Catch::TestCaseHandle> const&), (override));
    MOCK_METHOD(void, listTags, (std::vector<Catch::TagInfo> const&), (override));
    MOCK_METHOD(void, noMatchingTestCases, (Catch::StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (Catch::StringRef), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (Catch::StringRef), (override));
};

class RunContextTest_506 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = std::make_unique<::testing::NiceMock<MockConfig>>();
        
        static const std::string testName = "TestRun";
        static const std::vector<std::string> emptyVec;
        static const Catch::TestSpec emptySpec;
        
        ON_CALL(*mockConfig_, name()).WillByDefault(::testing::Return(Catch::StringRef(testName)));
        ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, warnAboutMissingAssertions()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, allowThrows()).WillByDefault(::testing::Return(true));
        ON_CALL(*mockConfig_, abortAfter()).WillByDefault(::testing::Return(0));
        ON_CALL(*mockConfig_, showDurations()).WillByDefault(::testing::Return(Catch::ShowDurations::DefaultForReporter));
        ON_CALL(*mockConfig_, runOrder()).WillByDefault(::testing::Return(Catch::TestRunOrder::Declared));
        ON_CALL(*mockConfig_, rngSeed()).WillByDefault(::testing::Return(0));
        ON_CALL(*mockConfig_, testSpec()).WillByDefault(::testing::ReturnRef(emptySpec));
        ON_CALL(*mockConfig_, hasTestFilters()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));
        ON_CALL(*mockConfig_, verbosity()).WillByDefault(::testing::Return(Catch::Verbosity::Normal));
        ON_CALL(*mockConfig_, shouldDebugBreak()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, outputRedirectUsage()).WillByDefault(::testing::Return(Catch::OutputRedirectUsage::Default));
    }
    
    std::unique_ptr<Catch::RunContext> createRunContext() {
        auto reporter = Catch::Detail::make_unique<::testing::NiceMock<MockReporter>>(mockConfig_.get());
        return std::make_unique<Catch::RunContext>(mockConfig_.get(), std::move(reporter));
    }
    
    std::unique_ptr<::testing::NiceMock<MockConfig>> mockConfig_;
};

// Test: MessageInfo equality operator - same messages are equal
TEST_F(RunContextTest_506, MessageInfoEquality_506) {
    Catch::SourceLineInfo lineInfo("file.cpp", 10);
    Catch::MessageInfo msg1("MACRO", lineInfo, Catch::ResultWas::Info);
    Catch::MessageInfo msg2 = msg1;
    // Copy should be equal
    EXPECT_TRUE(msg1 == msg2);
}

// Test: MessageInfo inequality - different sequence numbers
TEST_F(RunContextTest_506, MessageInfoInequality_506) {
    Catch::SourceLineInfo lineInfo("file.cpp", 10);
    Catch::MessageInfo msg1("MACRO", lineInfo, Catch::ResultWas::Info);
    Catch::MessageInfo msg2("MACRO", lineInfo, Catch::ResultWas::Info);
    // Different sequence numbers, should not be equal
    EXPECT_FALSE(msg1 == msg2);
}

// Test: MessageInfo less than operator
TEST_F(RunContextTest_506, MessageInfoLessThan_506) {
    Catch::SourceLineInfo lineInfo("file.cpp", 10);
    Catch::MessageInfo msg1("MACRO", lineInfo, Catch::ResultWas::Info);
    Catch::MessageInfo msg2("MACRO", lineInfo, Catch::ResultWas::Info);
    // msg1 created first should have lower sequence
    EXPECT_TRUE(msg1 < msg2);
    EXPECT_FALSE(msg2 < msg1);
}

// Test: pushScopedMessage and popScopedMessage basic operation - no crash
TEST_F(RunContextTest_506, PushAndPopScopedMessageNoCrash_506) {
    auto context = createRunContext();
    Catch::SourceLineInfo lineInfo("test.cpp", 42);
    Catch::MessageInfo msg("INFO", lineInfo, Catch::ResultWas::Info);
    
    context->pushScopedMessage(msg);
    // Should not crash
    context->popScopedMessage(msg);
}

// Test: Pop without matching push - should not crash (removing non-existent element)
TEST_F(RunContextTest_506, PopWithoutPushNoCrash_506) {
    auto context = createRunContext();
    Catch::SourceLineInfo lineInfo("test.cpp", 42);
    Catch::MessageInfo msg("INFO", lineInfo, Catch::ResultWas::Info);
    
    // Popping a message that was never pushed should be safe
    context->popScopedMessage(msg);
}

// Test: Push multiple messages and pop them all
TEST_F(RunContextTest_506, PushMultipleAndPopAll_506) {
    auto context = createRunContext();
    Catch::SourceLineInfo lineInfo1("test.cpp", 10);
    Catch::SourceLineInfo lineInfo2("test.cpp", 20);
    Catch::SourceLineInfo lineInfo3("test.cpp", 30);
    
    Catch::MessageInfo msg1("INFO", lineInfo1, Catch::ResultWas::Info);
    Catch::MessageInfo msg2("INFO", lineInfo2, Catch::ResultWas::Info);
    Catch::MessageInfo msg3("INFO", lineInfo3, Catch::ResultWas::Info);
    
    context->pushScopedMessage(msg1);
    context->pushScopedMessage(msg2);
    context->pushScopedMessage(msg3);
    
    context->popScopedMessage(msg3);
    context->popScopedMessage(msg2);
    context->popScopedMessage(msg1);
}

// Test: Push and pop in different order (FIFO-like)
TEST_F(RunContextTest_506, PushAndPopDifferentOrder_506) {
    auto context = createRunContext();
    Catch::SourceLineInfo lineInfo1("test.cpp", 10);
    Catch::SourceLineInfo lineInfo2("test.cpp", 20);
    
    Catch::MessageInfo msg1("INFO", lineInfo1, Catch::ResultWas::Info);
    Catch::MessageInfo msg2("INFO", lineInfo2, Catch::ResultWas::Info);
    
    context->pushScopedMessage(msg1);
    context->pushScopedMessage(msg2);
    
    // Pop in a different order than pushed
    context->popScopedMessage(msg1);
    context->popScopedMessage(msg2);
}

// Test: Pop the same message twice after single push
TEST_F(RunContextTest_506, PopSameMessageTwiceAfterSinglePush_506) {
    auto context = createRunContext();
    Catch::SourceLineInfo lineInfo("test.cpp", 42);
    Catch::MessageInfo msg("INFO", lineInfo, Catch::ResultWas::Info);
    
    context->pushScopedMessage(msg);
    context->popScopedMessage(msg);
    // Second pop of same message - should be safe (no-op, element already removed)
    context->popScopedMessage(msg);
}

// Test: lastAssertionPassed returns false initially
TEST_F(RunContextTest_506, LastAssertionPassedInitiallyFalse_506) {
    auto context = createRunContext();
    EXPECT_FALSE(context->lastAssertionPassed());
}

// Test: assertionPassed sets lastAssertionPassed to true
TEST_F(RunContextTest_506, AssertionPassedSetsFlag_506) {
    auto context = createRunContext();
    context->assertionPassed();
    EXPECT_TRUE(context->lastAssertionPassed());
}

// Test: getCurrentTestName returns empty string when no test is active
TEST_F(RunContextTest_506, GetCurrentTestNameWhenNoActiveTest_506) {
    auto context = createRunContext();
    std::string name = context->getCurrentTestName();
    // When no test case is active, should return empty or some default
    EXPECT_TRUE(name.empty());
}

// Test: getLastResult returns nullptr initially
TEST_F(RunContextTest_506, GetLastResultInitiallyNull_506) {
    auto context = createRunContext();
    const Catch::AssertionResult* result = context->getLastResult();
    EXPECT_EQ(result, nullptr);
}

// Test: aborting returns false initially (abortAfter is 0 = no limit)
TEST_F(RunContextTest_506, AbortingInitiallyFalse_506) {
    auto context = createRunContext();
    EXPECT_FALSE(context->aborting());
}

}  // namespace
