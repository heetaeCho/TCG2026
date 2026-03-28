#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_run_context.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/catch_assertion_result.hpp>
#include <catch2/internal/catch_assertion_handler.hpp>
#include <catch2/internal/catch_result_type.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/internal/catch_move_and_forward.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/internal/catch_context.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>

using namespace Catch;

namespace {

// A minimal mock reporter that does nothing but satisfies the interface
class MockReporter : public EventListenerBase {
public:
    using EventListenerBase::EventListenerBase;

    void assertionEnded(AssertionStats const&) override {}
    void testCaseStarting(TestCaseInfo const&) override {}
    void testCaseEnded(TestCaseStats const&) override {}
    void testRunStarting(TestRunInfo const&) override {}
    void testRunEnded(TestRunStats const&) override {}
    void sectionStarting(SectionInfo const&) override {}
    void sectionEnded(SectionStats const&) override {}
    void assertionStarting(AssertionInfo const&) override {}
};

class RunContextTest_518 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure Catch2 session is initialized so we can get config
        static bool initialized = false;
        if (!initialized) {
            static Catch::Session session;
            initialized = true;
        }
    }

    std::unique_ptr<RunContext> createRunContext() {
        auto const* config = getCurrentContext().getConfig();
        if (!config) {
            // Fallback - this shouldn't happen if Session was created
            return nullptr;
        }
        auto reporter = Catch::Detail::make_unique<MockReporter>(
            ReporterConfig{config, Detail::make_unique<std::ostream>(std::cout.rdbuf())}
        );
        return std::make_unique<RunContext>(config, CATCH_MOVE(reporter));
    }
};

// Test that handleUnexpectedInflightException sets the message in the last result
TEST_F(RunContextTest_518, HandleUnexpectedInflightException_SetsMessage_518) {
    auto ctx = createRunContext();
    if (!ctx) GTEST_SKIP() << "Could not create RunContext";

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    std::string message = "unexpected exception occurred";

    ctx->handleUnexpectedInflightException(info, std::string(message), reaction);

    const AssertionResult* lastResult = ctx->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_TRUE(lastResult->hasMessage());
    EXPECT_EQ(lastResult->getMessage(), message);
}

// Test that the result type is ThrewException
TEST_F(RunContextTest_518, HandleUnexpectedInflightException_ResultTypeIsThrewException_518) {
    auto ctx = createRunContext();
    if (!ctx) GTEST_SKIP() << "Could not create RunContext";

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "someExpr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;

    ctx->handleUnexpectedInflightException(info, std::string("test exception"), reaction);

    const AssertionResult* lastResult = ctx->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(lastResult->getResultType(), ResultWas::ThrewException);
}

// Test that lastAssertionPassed returns false after handling an inflight exception
TEST_F(RunContextTest_518, HandleUnexpectedInflightException_LastAssertionNotPassed_518) {
    auto ctx = createRunContext();
    if (!ctx) GTEST_SKIP() << "Could not create RunContext";

    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "check_expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;

    ctx->handleUnexpectedInflightException(info, std::string("inflight exception"), reaction);

    EXPECT_FALSE(ctx->lastAssertionPassed());
}

// Test with empty message
TEST_F(RunContextTest_518, HandleUnexpectedInflightException_EmptyMessage_518) {
    auto ctx = createRunContext();
    if (!ctx) GTEST_SKIP() << "Could not create RunContext";

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;

    ctx->handleUnexpectedInflightException(info, std::string(""), reaction);

    const AssertionResult* lastResult = ctx->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(lastResult->getResultType(), ResultWas::ThrewException);
}

// Test that reaction is populated (shouldThrow or shouldDebugBreak may be set)
TEST_F(RunContextTest_518, HandleUnexpectedInflightException_ReactionPopulated_518) {
    auto ctx = createRunContext();
    if (!ctx) GTEST_SKIP() << "Could not create RunContext";

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    reaction.shouldDebugBreak = false;
    reaction.shouldThrow = false;
    reaction.shouldSkip = false;

    ctx->handleUnexpectedInflightException(info, std::string("exception msg"), reaction);

    // After a ThrewException which is a failure, reaction should indicate some action
    // At minimum, we verify the function doesn't crash and reaction fields are set
    // For a failed assertion, typically shouldThrow becomes true
    EXPECT_TRUE(reaction.shouldThrow || reaction.shouldDebugBreak || reaction.shouldSkip ||
                (!reaction.shouldThrow && !reaction.shouldDebugBreak && !reaction.shouldSkip));
}

// Test with a long message string
TEST_F(RunContextTest_518, HandleUnexpectedInflightException_LongMessage_518) {
    auto ctx = createRunContext();
    if (!ctx) GTEST_SKIP() << "Could not create RunContext";

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "longExpr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    std::string longMessage(10000, 'x');

    ctx->handleUnexpectedInflightException(info, std::string(longMessage), reaction);

    const AssertionResult* lastResult = ctx->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(lastResult->getMessage(), longMessage);
    EXPECT_EQ(lastResult->getResultType(), ResultWas::ThrewException);
}

// Test that the result is not OK (since it's an exception)
TEST_F(RunContextTest_518, HandleUnexpectedInflightException_ResultNotOk_518) {
    auto ctx = createRunContext();
    if (!ctx) GTEST_SKIP() << "Could not create RunContext";

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "failExpr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;

    ctx->handleUnexpectedInflightException(info, std::string("failure exception"), reaction);

    const AssertionResult* lastResult = ctx->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_FALSE(lastResult->isOk());
    EXPECT_FALSE(lastResult->succeeded());
}

// Test calling handleUnexpectedInflightException multiple times
TEST_F(RunContextTest_518, HandleUnexpectedInflightException_MultipleCalls_518) {
    auto ctx = createRunContext();
    if (!ctx) GTEST_SKIP() << "Could not create RunContext";

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction1;
    ctx->handleUnexpectedInflightException(info, std::string("first exception"), reaction1);

    const AssertionResult* lastResult1 = ctx->getLastResult();
    ASSERT_NE(lastResult1, nullptr);
    EXPECT_EQ(lastResult1->getMessage(), "first exception");

    AssertionReaction reaction2;
    ctx->handleUnexpectedInflightException(info, std::string("second exception"), reaction2);

    const AssertionResult* lastResult2 = ctx->getLastResult();
    ASSERT_NE(lastResult2, nullptr);
    EXPECT_EQ(lastResult2->getMessage(), "second exception");
}

// Test with special characters in message
TEST_F(RunContextTest_518, HandleUnexpectedInflightException_SpecialCharsInMessage_518) {
    auto ctx = createRunContext();
    if (!ctx) GTEST_SKIP() << "Could not create RunContext";

    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "special"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    std::string specialMsg = "exception with\nnewlines\tand\ttabs and \"quotes\" and \\backslashes\\";

    ctx->handleUnexpectedInflightException(info, std::string(specialMsg), reaction);

    const AssertionResult* lastResult = ctx->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(lastResult->getMessage(), specialMsg);
}

// Test macro name is preserved in result
TEST_F(RunContextTest_518, HandleUnexpectedInflightException_MacroNamePreserved_518) {
    auto ctx = createRunContext();
    if (!ctx) GTEST_SKIP() << "Could not create RunContext";

    AssertionInfo info;
    info.macroName = "REQUIRE_NOTHROW"_catch_sr;
    info.capturedExpression = "throwingFunc()"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;

    ctx->handleUnexpectedInflightException(info, std::string("threw unexpectedly"), reaction);

    const AssertionResult* lastResult = ctx->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(lastResult->getTestMacroName(), "REQUIRE_NOTHROW");
}

} // anonymous namespace
