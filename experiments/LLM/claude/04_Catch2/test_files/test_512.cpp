#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_reporter_registry.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/internal/catch_test_case_registry_impl.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_message.hpp"

#include <memory>
#include <string>

using namespace Catch;
using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

// Mock reporter/listener that does nothing
class MockReporter : public IEventListener {
public:
    MockReporter(IConfig const* config) : IEventListener(config) {}

    void testRunStarting(TestRunInfo const&) override {}
    void testRunEnded(TestRunStats const&) override {}
    void testCaseStarting(TestCaseInfo const&) override {}
    void testCaseEnded(TestCaseStats const&) override {}
    void testCasePartialStarting(TestCaseInfo const&, uint64_t) override {}
    void testCasePartialEnded(TestCaseStats const&, uint64_t) override {}
    void sectionStarting(SectionInfo const&) override {}
    void sectionEnded(SectionStats const&) override {}
    void assertionStarting(AssertionInfo const&) override {}
    void assertionEnded(AssertionResult const&) override {}

    void benchmarkPreparing(StringRef) override {}
    void benchmarkStarting(BenchmarkInfo const&) override {}
    void benchmarkEnded(BenchmarkStats<> const&) override {}
    void benchmarkFailed(StringRef) override {}

    void listReporters(std::vector<ReporterDescription> const&) override {}
    void listListeners(std::vector<ListenerDescription> const&) override {}
    void listTests(std::vector<TestCaseHandle> const&) override {}
    void listTags(std::vector<TagInfo> const&) override {}

    void noMatchingTestCases(StringRef) override {}
    void reportInvalidTestSpec(StringRef) override {}

    void fatalErrorEncountered(StringRef) override {}
};

class RunContextTest_512 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a valid session/config to create RunContext
        session_ = std::make_unique<Catch::Session>();
        config_ = session_->config();
    }

    std::unique_ptr<RunContext> createRunContext() {
        auto reporter = Catch::Detail::make_unique<MockReporter>(config_);
        return std::make_unique<RunContext>(config_, CATCH_MOVE(reporter));
    }

    std::unique_ptr<Catch::Session> session_;
    IConfig const* config_ = nullptr;
};

TEST_F(RunContextTest_512, LastAssertionPassedInitiallyFalse_512) {
    auto ctx = createRunContext();
    // Initially, no assertion has passed
    EXPECT_FALSE(ctx->lastAssertionPassed());
}

TEST_F(RunContextTest_512, AssertionPassedSetsLastAssertionPassedTrue_512) {
    auto ctx = createRunContext();
    ctx->assertionPassed();
    EXPECT_TRUE(ctx->lastAssertionPassed());
}

TEST_F(RunContextTest_512, LastAssertionPassedAfterMultipleCallsToAssertionPassed_512) {
    auto ctx = createRunContext();
    ctx->assertionPassed();
    EXPECT_TRUE(ctx->lastAssertionPassed());
    ctx->assertionPassed();
    EXPECT_TRUE(ctx->lastAssertionPassed());
}

TEST_F(RunContextTest_512, GetCurrentTestNameWhenNoActiveTest_512) {
    auto ctx = createRunContext();
    // When no test case is active, getCurrentTestName should return empty or some default
    std::string name = ctx->getCurrentTestName();
    // Without an active test case, the name should be empty
    EXPECT_TRUE(name.empty());
}

TEST_F(RunContextTest_512, GetLastResultWhenNoAssertions_512) {
    auto ctx = createRunContext();
    const AssertionResult* result = ctx->getLastResult();
    // Initially there should be no last result
    EXPECT_EQ(result, nullptr);
}

TEST_F(RunContextTest_512, AbortingInitiallyFalse_512) {
    auto ctx = createRunContext();
    // With default config, aborting should initially be false
    EXPECT_FALSE(ctx->aborting());
}

TEST_F(RunContextTest_512, PushAndPopScopedMessage_512) {
    auto ctx = createRunContext();
    // Create a message info
    MessageInfo msgInfo("test message", SourceLineInfo("file.cpp", 1), ResultWas::Info);
    
    // Should not throw
    EXPECT_NO_THROW(ctx->pushScopedMessage(msgInfo));
    EXPECT_NO_THROW(ctx->popScopedMessage(msgInfo));
}

TEST_F(RunContextTest_512, NotifyAssertionStartedDoesNotThrow_512) {
    auto ctx = createRunContext();
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.lineInfo = SourceLineInfo("test.cpp", 10);
    info.capturedExpression = "x == 1"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    EXPECT_NO_THROW(ctx->notifyAssertionStarted(info));
}

TEST_F(RunContextTest_512, ExceptionEarlyReportedDoesNotThrow_512) {
    auto ctx = createRunContext();
    EXPECT_NO_THROW(ctx->exceptionEarlyReported());
}

TEST_F(RunContextTest_512, AssertionPassedThenCheckLastAssertionPassed_512) {
    auto ctx = createRunContext();
    
    // Before any assertion
    EXPECT_FALSE(ctx->lastAssertionPassed());
    
    // Mark assertion as passed
    ctx->assertionPassed();
    EXPECT_TRUE(ctx->lastAssertionPassed());
}

TEST_F(RunContextTest_512, BenchmarkPreparingDoesNotThrow_512) {
    auto ctx = createRunContext();
    EXPECT_NO_THROW(ctx->benchmarkPreparing("test_benchmark"_catch_sr));
}

TEST_F(RunContextTest_512, BenchmarkFailedDoesNotThrow_512) {
    auto ctx = createRunContext();
    EXPECT_NO_THROW(ctx->benchmarkFailed("some error"_catch_sr));
}

TEST_F(RunContextTest_512, EmplaceUnscopedMessageDoesNotThrow_512) {
    auto ctx = createRunContext();
    MessageBuilder builder("INFO"_catch_sr, SourceLineInfo("file.cpp", 42), ResultWas::Info);
    builder << "test unscoped message";
    EXPECT_NO_THROW(ctx->emplaceUnscopedMessage(CATCH_MOVE(builder)));
}

TEST_F(RunContextTest_512, HandleNonExprDoesNotCrash_512) {
    auto ctx = createRunContext();
    AssertionInfo info;
    info.macroName = "SUCCEED"_catch_sr;
    info.lineInfo = SourceLineInfo("test.cpp", 20);
    info.capturedExpression = ""_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    // This should handle without crashing
    EXPECT_NO_THROW(ctx->handleNonExpr(info, ResultWas::Ok, reaction));
}

TEST_F(RunContextTest_512, HandleNonExprSetsLastAssertionPassed_512) {
    auto ctx = createRunContext();
    AssertionInfo info;
    info.macroName = "SUCCEED"_catch_sr;
    info.lineInfo = SourceLineInfo("test.cpp", 25);
    info.capturedExpression = ""_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    ctx->handleNonExpr(info, ResultWas::Ok, reaction);
    
    // After a successful non-expr assertion, lastAssertionPassed should be true
    EXPECT_TRUE(ctx->lastAssertionPassed());
}

TEST_F(RunContextTest_512, HandleMessageDoesNotCrash_512) {
    auto ctx = createRunContext();
    AssertionInfo info;
    info.macroName = "INFO"_catch_sr;
    info.lineInfo = SourceLineInfo("test.cpp", 30);
    info.capturedExpression = ""_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    EXPECT_NO_THROW(ctx->handleMessage(info, ResultWas::Info, "test info message", reaction));
}

TEST_F(RunContextTest_512, HandleUnexpectedExceptionNotThrownSetsReaction_512) {
    auto ctx = createRunContext();
    AssertionInfo info;
    info.macroName = "REQUIRE_THROWS"_catch_sr;
    info.lineInfo = SourceLineInfo("test.cpp", 35);
    info.capturedExpression = "func()"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    ctx->handleUnexpectedExceptionNotThrown(info, reaction);
    
    // After an unexpected missing exception, lastAssertionPassed should be false
    EXPECT_FALSE(ctx->lastAssertionPassed());
}

TEST_F(RunContextTest_512, HandleUnexpectedInflightExceptionSetsReaction_512) {
    auto ctx = createRunContext();
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.lineInfo = SourceLineInfo("test.cpp", 40);
    info.capturedExpression = "x == 1"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    ctx->handleUnexpectedInflightException(info, "unexpected exception", reaction);
    
    // After an unexpected inflight exception, lastAssertionPassed should be false
    EXPECT_FALSE(ctx->lastAssertionPassed());
}
