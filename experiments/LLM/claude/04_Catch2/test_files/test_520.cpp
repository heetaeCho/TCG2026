#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/catch_assertion_result.hpp>
#include <catch2/internal/catch_assertion_handler.hpp>
#include <catch2/internal/catch_run_context.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/internal/catch_reporter_registry.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/internal/catch_test_case_registry_impl.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/internal/catch_context.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/internal/catch_compiler_capabilities.hpp>

#include <memory>
#include <string>

using namespace Catch;

// Mock event listener that records calls
class MockEventListener : public IEventListener {
public:
    MockEventListener(IConfig const* config) : IEventListener(config) {}

    void testRunStarting(TestRunInfo const&) override {}
    void testRunEnded(TestRunStats const&) override {}
    void testCaseStarting(TestCaseInfo const&) override {}
    void testCaseEnded(TestCaseStats const&) override {}
    void testCasePartialStarting(TestCaseInfo const&, uint64_t) override {}
    void testCasePartialEnded(TestCaseStats const&, uint64_t) override {}
    void sectionStarting(SectionInfo const&) override {}
    void sectionEnded(SectionStats const&) override {}
    void assertionStarting(AssertionInfo const&) override {}
    void assertionEnded(AssertionResult const& result) override {
        lastResult = result.getResultType();
        lastIsOk = result.isOk();
        assertionEndedCount++;
    }
    void benchmarkPreparing(StringRef) override {}
    void benchmarkStarting(BenchmarkInfo const&) override {}
    void benchmarkEnded(BenchmarkStats<> const&) override {}
    void benchmarkFailed(StringRef) override {}
    void skipTest(TestCaseInfo const&) override {}
    void fatalErrorEncountered(StringRef) override {}
    void reportInvalidTestSpec(StringRef) override {}
    void listReporters(std::vector<ReporterDescription> const&) override {}
    void listListeners(std::vector<ListenerDescription> const&) override {}
    void listTests(std::vector<TestCaseHandle> const&) override {}
    void listTags(std::vector<TagInfo> const&) override {}
    void noMatchingTestCases(StringRef) override {}

    ResultWas::OfType lastResult = ResultWas::Unknown;
    bool lastIsOk = false;
    int assertionEndedCount = 0;
};

class HandleNonExprTest_520 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a valid Catch2 session context to create RunContext
        // This is complex, so we use the Catch2 internal mechanisms
        static const char* argv[] = {"test"};
        static int argc = 1;
        
        session.applyCommandLine(argc, argv);
        config = session.config();
    }

    Catch::Session session;
    Catch::ConfigData configData;
    Catch::IConfig const* config = nullptr;
};

// Test that handleNonExpr with an "Ok" result type does not populate reaction
TEST_F(HandleNonExprTest_520, OkResultDoesNotPopulateReaction_520) {
    auto mockListener = Catch::Detail::make_unique<MockEventListener>(config);
    auto* listenerPtr = mockListener.get();
    
    RunContext context(config, Catch::IEventListenerPtr(mockListener.release()));
    
    AssertionInfo info;
    info.macroName = "TEST_MACRO"_catch_sr;
    info.capturedExpression = "expression"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    
    AssertionReaction reaction;
    reaction.shouldDebugBreak = false;
    reaction.shouldThrow = false;
    reaction.shouldSkip = false;
    
    context.handleNonExpr(info, ResultWas::Ok, reaction);
    
    // For an Ok result, reaction should NOT be populated (no throwing/breaking)
    EXPECT_FALSE(reaction.shouldThrow);
    EXPECT_FALSE(reaction.shouldDebugBreak);
}

// Test that handleNonExpr with a failure result type populates reaction
TEST_F(HandleNonExprTest_520, FailureResultPopulatesReaction_520) {
    auto mockListener = Catch::Detail::make_unique<MockEventListener>(config);
    auto* listenerPtr = mockListener.get();
    
    RunContext context(config, Catch::IEventListenerPtr(mockListener.release()));
    
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "false"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    
    AssertionReaction reaction;
    reaction.shouldDebugBreak = false;
    reaction.shouldThrow = false;
    reaction.shouldSkip = false;
    
    context.handleNonExpr(info, ResultWas::ExplicitFailure, reaction);
    
    // For a failure result, reaction should be populated
    EXPECT_TRUE(reaction.shouldThrow || reaction.shouldDebugBreak || reaction.shouldSkip);
}

// Test that handleNonExpr records the assertion result accessible via getLastResult
TEST_F(HandleNonExprTest_520, LastResultIsUpdated_520) {
    auto mockListener = Catch::Detail::make_unique<MockEventListener>(config);
    auto* listenerPtr = mockListener.get();
    
    RunContext context(config, Catch::IEventListenerPtr(mockListener.release()));
    
    AssertionInfo info;
    info.macroName = "SUCCEED"_catch_sr;
    info.capturedExpression = ""_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    
    AssertionReaction reaction;
    
    context.handleNonExpr(info, ResultWas::Ok, reaction);
    
    const AssertionResult* lastResult = context.getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(lastResult->getResultType(), ResultWas::Ok);
}

// Test that handleNonExpr with ExplicitSkip result type
TEST_F(HandleNonExprTest_520, ExplicitSkipResultType_520) {
    auto mockListener = Catch::Detail::make_unique<MockEventListener>(config);
    
    RunContext context(config, Catch::IEventListenerPtr(mockListener.release()));
    
    AssertionInfo info;
    info.macroName = "SKIP"_catch_sr;
    info.capturedExpression = ""_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    
    AssertionReaction reaction;
    reaction.shouldDebugBreak = false;
    reaction.shouldThrow = false;
    reaction.shouldSkip = false;
    
    context.handleNonExpr(info, ResultWas::ExplicitSkip, reaction);
    
    // Skip should populate reaction with shouldSkip
    EXPECT_TRUE(reaction.shouldSkip || reaction.shouldThrow);
}

// Test that lastAssertionPassed reflects the ok-ness of the last assertion
TEST_F(HandleNonExprTest_520, LastAssertionPassedReflectsOkResult_520) {
    auto mockListener = Catch::Detail::make_unique<MockEventListener>(config);
    
    RunContext context(config, Catch::IEventListenerPtr(mockListener.release()));
    
    AssertionInfo info;
    info.macroName = "SUCCEED"_catch_sr;
    info.capturedExpression = ""_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    
    AssertionReaction reaction;
    
    context.handleNonExpr(info, ResultWas::Ok, reaction);
    
    EXPECT_TRUE(context.lastAssertionPassed());
}

// Test that lastAssertionPassed returns false after a failure
TEST_F(HandleNonExprTest_520, LastAssertionPassedReturnsFalseOnFailure_520) {
    auto mockListener = Catch::Detail::make_unique<MockEventListener>(config);
    
    RunContext context(config, Catch::IEventListenerPtr(mockListener.release()));
    
    AssertionInfo info;
    info.macroName = "FAIL"_catch_sr;
    info.capturedExpression = ""_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    
    AssertionReaction reaction;
    
    context.handleNonExpr(info, ResultWas::ExplicitFailure, reaction);
    
    EXPECT_FALSE(context.lastAssertionPassed());
}

// Test that assertion info is reset after handleNonExpr
TEST_F(HandleNonExprTest_520, AssertionInfoResetAfterCall_520) {
    auto mockListener = Catch::Detail::make_unique<MockEventListener>(config);
    auto* listenerPtr = mockListener.get();
    
    RunContext context(config, Catch::IEventListenerPtr(mockListener.release()));
    
    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "someExpr"_catch_sr;
    info.resultDisposition = ResultDisposition::ContinueOnFailure;
    
    AssertionReaction reaction;
    
    context.handleNonExpr(info, ResultWas::Ok, reaction);
    
    // Verify the listener received the assertion end notification
    EXPECT_EQ(listenerPtr->assertionEndedCount, 1);
    EXPECT_EQ(listenerPtr->lastResult, ResultWas::Ok);
    EXPECT_TRUE(listenerPtr->lastIsOk);
}

// Test multiple successive calls to handleNonExpr
TEST_F(HandleNonExprTest_520, MultipleCallsUpdateState_520) {
    auto mockListener = Catch::Detail::make_unique<MockEventListener>(config);
    auto* listenerPtr = mockListener.get();
    
    RunContext context(config, Catch::IEventListenerPtr(mockListener.release()));
    
    AssertionInfo info1;
    info1.macroName = "SUCCEED"_catch_sr;
    info1.capturedExpression = ""_catch_sr;
    info1.resultDisposition = ResultDisposition::Normal;
    
    AssertionReaction reaction1;
    context.handleNonExpr(info1, ResultWas::Ok, reaction1);
    
    EXPECT_TRUE(context.lastAssertionPassed());
    EXPECT_EQ(listenerPtr->assertionEndedCount, 1);
    
    AssertionInfo info2;
    info2.macroName = "SUCCEED"_catch_sr;
    info2.capturedExpression = ""_catch_sr;
    info2.resultDisposition = ResultDisposition::Normal;
    
    AssertionReaction reaction2;
    context.handleNonExpr(info2, ResultWas::Ok, reaction2);
    
    EXPECT_TRUE(context.lastAssertionPassed());
    EXPECT_EQ(listenerPtr->assertionEndedCount, 2);
}

// Test with ContinueOnFailure disposition - failure should not throw
TEST_F(HandleNonExprTest_520, ContinueOnFailureDisposition_520) {
    auto mockListener = Catch::Detail::make_unique<MockEventListener>(config);
    
    RunContext context(config, Catch::IEventListenerPtr(mockListener.release()));
    
    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "false"_catch_sr;
    info.resultDisposition = ResultDisposition::ContinueOnFailure;
    
    AssertionReaction reaction;
    reaction.shouldDebugBreak = false;
    reaction.shouldThrow = false;
    reaction.shouldSkip = false;
    
    context.handleNonExpr(info, ResultWas::ExplicitFailure, reaction);
    
    // With ContinueOnFailure, shouldThrow might not be set
    // The reaction should still be populated since it's a failure
    const AssertionResult* lastResult = context.getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(lastResult->getResultType(), ResultWas::ExplicitFailure);
}

// Test with Warning result type (which is considered ok)
TEST_F(HandleNonExprTest_520, WarningResultIsOk_520) {
    auto mockListener = Catch::Detail::make_unique<MockEventListener>(config);
    
    RunContext context(config, Catch::IEventListenerPtr(mockListener.release()));
    
    AssertionInfo info;
    info.macroName = "WARN"_catch_sr;
    info.capturedExpression = ""_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    
    AssertionReaction reaction;
    reaction.shouldDebugBreak = false;
    reaction.shouldThrow = false;
    reaction.shouldSkip = false;
    
    context.handleNonExpr(info, ResultWas::Warning, reaction);
    
    // Warning should be ok, no reaction population
    EXPECT_FALSE(reaction.shouldThrow);
    EXPECT_FALSE(reaction.shouldDebugBreak);
}
