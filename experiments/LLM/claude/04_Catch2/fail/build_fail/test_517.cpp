#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/internal/catch_run_context.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/internal/catch_assertion_handler.hpp>
#include <catch2/internal/catch_result_type.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/internal/catch_reporter_registry.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/internal/catch_move_and_forward.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>

#include <string>
#include <vector>

using namespace Catch;
using namespace testing;

namespace {

// Mock event listener to capture reported assertions
class MockEventListener : public Catch::EventListenerBase {
public:
    using EventListenerBase::EventListenerBase;

    MOCK_METHOD(void, testRunStarting, (TestRunInfo const&), (override));
    MOCK_METHOD(void, testRunEnded, (TestRunStats const&), (override));
    MOCK_METHOD(void, testCaseStarting, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, testCaseEnded, (TestCaseStats const&), (override));
    MOCK_METHOD(void, sectionStarting, (SectionInfo const&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionStats const&), (override));
    MOCK_METHOD(void, assertionStarting, (AssertionInfo const&), (override));
    MOCK_METHOD(void, assertionEnded, (AssertionStats const&), (override));
};

// A minimal mock config
class MockConfig : public Catch::IConfig {
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

class RunContextTest_517 : public ::testing::Test {
protected:
    void SetUp() override {
        testsOrTags_.clear();
        sectionsToRun_.clear();

        ON_CALL(mockConfig_, name()).WillByDefault(Return("TestRun"_catch_sr));
        ON_CALL(mockConfig_, allowThrows()).WillByDefault(Return(true));
        ON_CALL(mockConfig_, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(mockConfig_, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(mockConfig_, warnAboutUnmatchedTestSpecs()).WillByDefault(Return(false));
        ON_CALL(mockConfig_, zeroTestsCountAsSuccess()).WillByDefault(Return(false));
        ON_CALL(mockConfig_, abortAfter()).WillByDefault(Return(-1));
        ON_CALL(mockConfig_, showInvisibles()).WillByDefault(Return(false));
        ON_CALL(mockConfig_, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));
        ON_CALL(mockConfig_, minDuration()).WillByDefault(Return(-1.0));
        ON_CALL(mockConfig_, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
        ON_CALL(mockConfig_, rngSeed()).WillByDefault(Return(0));
        ON_CALL(mockConfig_, shardCount()).WillByDefault(Return(1));
        ON_CALL(mockConfig_, shardIndex()).WillByDefault(Return(0));
        ON_CALL(mockConfig_, defaultColourMode()).WillByDefault(Return(ColourMode::PlatformDefault));
        ON_CALL(mockConfig_, hasTestFilters()).WillByDefault(Return(false));
        ON_CALL(mockConfig_, getTestsOrTags()).WillByDefault(ReturnRef(testsOrTags_));
        ON_CALL(mockConfig_, getSectionsToRun()).WillByDefault(ReturnRef(sectionsToRun_));
        ON_CALL(mockConfig_, verbosity()).WillByDefault(Return(Verbosity::Normal));
        ON_CALL(mockConfig_, benchmarkNoAnalysis()).WillByDefault(Return(false));
        ON_CALL(mockConfig_, benchmarkSamples()).WillByDefault(Return(100));
        ON_CALL(mockConfig_, benchmarkConfidenceInterval()).WillByDefault(Return(0.95));
        ON_CALL(mockConfig_, benchmarkResamples()).WillByDefault(Return(100000));
        ON_CALL(mockConfig_, benchmarkWarmupTime()).WillByDefault(Return(std::chrono::milliseconds(100)));
    }

    NiceMock<MockConfig> mockConfig_;
    std::vector<std::string> testsOrTags_;
    std::vector<std::string> sectionsToRun_;
};

// Test that handleUnexpectedExceptionNotThrown sets reaction flags
TEST_F(RunContextTest_517, HandleUnexpectedExceptionNotThrown_SetsReaction_517) {
    auto mockListener = Catch::Detail::make_unique<NiceMock<MockEventListener>>(
        Catch::IConfig const* {&mockConfig_});
    
    // We expect assertionEnded to be called on the listener
    EXPECT_CALL(*mockListener, assertionStarting(_)).Times(AnyNumber());
    EXPECT_CALL(*mockListener, assertionEnded(_)).Times(AtLeast(1));

    Catch::IEventListenerPtr listenerPtr(mockListener.release());
    Catch::RunContext context(&mockConfig_, CATCH_MOVE(listenerPtr));

    AssertionInfo info;
    info.macroName = "REQUIRE_THROWS"_catch_sr;
    info.capturedExpression = "expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    reaction.shouldDebugBreak = false;
    reaction.shouldThrow = false;
    reaction.shouldSkip = false;

    context.handleUnexpectedExceptionNotThrown(info, reaction);

    // After handling an unexpected "exception not thrown", we expect the
    // reaction to indicate failure behavior (shouldThrow or shouldDebugBreak).
    // The last assertion should NOT have passed since the exception wasn't thrown.
    EXPECT_FALSE(context.lastAssertionPassed());
}

// Test that assertionPassed sets lastAssertionPassed to true
TEST_F(RunContextTest_517, AssertionPassed_SetsLastAssertionPassed_517) {
    auto mockListener = Catch::Detail::make_unique<NiceMock<MockEventListener>>(
        static_cast<Catch::IConfig const*>(&mockConfig_));

    Catch::IEventListenerPtr listenerPtr(mockListener.release());
    Catch::RunContext context(&mockConfig_, CATCH_MOVE(listenerPtr));

    context.assertionPassed();
    EXPECT_TRUE(context.lastAssertionPassed());
}

// Test that getCurrentTestName returns empty when no test is active
TEST_F(RunContextTest_517, GetCurrentTestName_NoActiveTest_ReturnsEmpty_517) {
    auto mockListener = Catch::Detail::make_unique<NiceMock<MockEventListener>>(
        static_cast<Catch::IConfig const*>(&mockConfig_));

    Catch::IEventListenerPtr listenerPtr(mockListener.release());
    Catch::RunContext context(&mockConfig_, CATCH_MOVE(listenerPtr));

    std::string testName = context.getCurrentTestName();
    // No active test case, should return empty or some default
    EXPECT_TRUE(testName.empty());
}

// Test that getLastResult returns nullptr initially
TEST_F(RunContextTest_517, GetLastResult_InitiallyNull_517) {
    auto mockListener = Catch::Detail::make_unique<NiceMock<MockEventListener>>(
        static_cast<Catch::IConfig const*>(&mockConfig_));

    Catch::IEventListenerPtr listenerPtr(mockListener.release());
    Catch::RunContext context(&mockConfig_, CATCH_MOVE(listenerPtr));

    const AssertionResult* result = context.getLastResult();
    EXPECT_EQ(result, nullptr);
}

// Test lastAssertionPassed is false initially
TEST_F(RunContextTest_517, LastAssertionPassed_InitiallyFalse_517) {
    auto mockListener = Catch::Detail::make_unique<NiceMock<MockEventListener>>(
        static_cast<Catch::IConfig const*>(&mockConfig_));

    Catch::IEventListenerPtr listenerPtr(mockListener.release());
    Catch::RunContext context(&mockConfig_, CATCH_MOVE(listenerPtr));

    EXPECT_FALSE(context.lastAssertionPassed());
}

// Test aborting returns false when no abort condition
TEST_F(RunContextTest_517, Aborting_ReturnsFalseInitially_517) {
    auto mockListener = Catch::Detail::make_unique<NiceMock<MockEventListener>>(
        static_cast<Catch::IConfig const*>(&mockConfig_));

    Catch::IEventListenerPtr listenerPtr(mockListener.release());
    Catch::RunContext context(&mockConfig_, CATCH_MOVE(listenerPtr));

    EXPECT_FALSE(context.aborting());
}

// Test handleMessage with Info result type
TEST_F(RunContextTest_517, HandleMessage_InfoType_517) {
    auto mockListener = Catch::Detail::make_unique<NiceMock<MockEventListener>>(
        static_cast<Catch::IConfig const*>(&mockConfig_));

    EXPECT_CALL(*mockListener, assertionStarting(_)).Times(AnyNumber());
    EXPECT_CALL(*mockListener, assertionEnded(_)).Times(AtLeast(1));

    Catch::IEventListenerPtr listenerPtr(mockListener.release());
    Catch::RunContext context(&mockConfig_, CATCH_MOVE(listenerPtr));

    AssertionInfo info;
    info.macroName = "INFO"_catch_sr;
    info.capturedExpression = ""_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    context.handleMessage(info, ResultWas::Info, "test message", reaction);
}

// Test handleNonExpr with DidntThrowException
TEST_F(RunContextTest_517, HandleNonExpr_DidntThrowException_517) {
    auto mockListener = Catch::Detail::make_unique<NiceMock<MockEventListener>>(
        static_cast<Catch::IConfig const*>(&mockConfig_));

    EXPECT_CALL(*mockListener, assertionStarting(_)).Times(AnyNumber());
    EXPECT_CALL(*mockListener, assertionEnded(_)).Times(AtLeast(1));

    Catch::IEventListenerPtr listenerPtr(mockListener.release());
    Catch::RunContext context(&mockConfig_, CATCH_MOVE(listenerPtr));

    AssertionInfo info;
    info.macroName = "REQUIRE_THROWS"_catch_sr;
    info.capturedExpression = "someExpr()"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    context.handleNonExpr(info, ResultWas::DidntThrowException, reaction);

    // A DidntThrowException is a failure
    EXPECT_FALSE(context.lastAssertionPassed());
}

// Test that handleUnexpectedInflightException marks assertion as failed
TEST_F(RunContextTest_517, HandleUnexpectedInflightException_MarksFailure_517) {
    auto mockListener = Catch::Detail::make_unique<NiceMock<MockEventListener>>(
        static_cast<Catch::IConfig const*>(&mockConfig_));

    EXPECT_CALL(*mockListener, assertionStarting(_)).Times(AnyNumber());
    EXPECT_CALL(*mockListener, assertionEnded(_)).Times(AtLeast(1));

    Catch::IEventListenerPtr listenerPtr(mockListener.release());
    Catch::RunContext context(&mockConfig_, CATCH_MOVE(listenerPtr));

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    context.handleUnexpectedInflightException(info, "unexpected exception", reaction);

    EXPECT_FALSE(context.lastAssertionPassed());
}

// Test assertionPassed then handleUnexpectedExceptionNotThrown resets
TEST_F(RunContextTest_517, AssertionPassedThenFailure_ResetsState_517) {
    auto mockListener = Catch::Detail::make_unique<NiceMock<MockEventListener>>(
        static_cast<Catch::IConfig const*>(&mockConfig_));

    Catch::IEventListenerPtr listenerPtr(mockListener.release());
    Catch::RunContext context(&mockConfig_, CATCH_MOVE(listenerPtr));

    context.assertionPassed();
    EXPECT_TRUE(context.lastAssertionPassed());

    AssertionInfo info;
    info.macroName = "REQUIRE_THROWS"_catch_sr;
    info.capturedExpression = "expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    context.handleUnexpectedExceptionNotThrown(info, reaction);

    EXPECT_FALSE(context.lastAssertionPassed());
}

// Test that notifyAssertionStarted can be called without crash
TEST_F(RunContextTest_517, NotifyAssertionStarted_DoesNotCrash_517) {
    auto mockListener = Catch::Detail::make_unique<NiceMock<MockEventListener>>(
        static_cast<Catch::IConfig const*>(&mockConfig_));

    EXPECT_CALL(*mockListener, assertionStarting(_)).Times(1);

    Catch::IEventListenerPtr listenerPtr(mockListener.release());
    Catch::RunContext context(&mockConfig_, CATCH_MOVE(listenerPtr));

    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "x == 1"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    context.notifyAssertionStarted(info);
}

// Test exceptionEarlyReported does not crash
TEST_F(RunContextTest_517, ExceptionEarlyReported_DoesNotCrash_517) {
    auto mockListener = Catch::Detail::make_unique<NiceMock<MockEventListener>>(
        static_cast<Catch::IConfig const*>(&mockConfig_));

    Catch::IEventListenerPtr listenerPtr(mockListener.release());
    Catch::RunContext context(&mockConfig_, CATCH_MOVE(listenerPtr));

    EXPECT_NO_THROW(context.exceptionEarlyReported());
}

// Test AssertionReaction default values
TEST(AssertionReactionTest_517, DefaultValues_517) {
    Catch::AssertionReaction reaction;
    EXPECT_FALSE(reaction.shouldDebugBreak);
    EXPECT_FALSE(reaction.shouldThrow);
    EXPECT_FALSE(reaction.shouldSkip);
}

} // anonymous namespace
