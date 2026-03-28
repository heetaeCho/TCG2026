#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_run_context.hpp>
#include <catch2/internal/catch_decomposer.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/internal/catch_assertion_handler.hpp>
#include <catch2/internal/catch_result_type.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/internal/catch_move_and_forward.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <sstream>

using namespace Catch;

// Concrete ITransientExpression for testing
class TestExpression : public ITransientExpression {
public:
    TestExpression(bool isBinary, bool result)
        : ITransientExpression(isBinary, result) {}

    void streamReconstructedExpression(std::ostream& os) const override {
        os << "test_expr";
    }
};

// Mock event listener that captures calls
class MockEventListener : public Catch::EventListenerBase {
public:
    using EventListenerBase::EventListenerBase;

    void assertionEnded(Catch::AssertionStats const& stats) override {
        lastAssertionResult = stats.assertionResult;
        assertionEndedCallCount++;
    }

    void testCaseStarting(Catch::TestCaseInfo const& info) override {}
    void testCaseEnded(Catch::TestCaseStats const& stats) override {}

    std::optional<Catch::AssertionResult> lastAssertionResult;
    int assertionEndedCallCount = 0;
};

class RunContextHandleExprTest_515 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need actual Catch2 config and reporter to construct RunContext
    }
};

// Since RunContext is deeply coupled to Catch2 internals, we test through
// observable behavior: reaction state and lastAssertionPassed

// Helper to create a minimal config
static Catch::Detail::unique_ptr<Catch::IConfig const> makeConfig(bool includeSuccessful = false) {
    // Use default config
    auto cfg = Catch::ConfigData{};
    cfg.showSuccessfulTests = includeSuccessful;
    return Catch::Detail::make_unique<Catch::Config>(cfg);
}

static Catch::IEventListenerPtr makeListener(Catch::IConfig const* config) {
    return Catch::Detail::make_unique<MockEventListener>(
        Catch::ReporterConfig{config, Catch::Detail::make_unique<std::ostream>(std::cout.rdbuf()), Catch::ColourMode::None}
    );
}

TEST(HandleExprPassingTest_515, PassingExpressionSetsLastAssertionPassed_515) {
    // A passing expression (getResult() == true, not negated) should mark assertion as passed
    auto config = makeConfig(false);
    auto listener = makeListener(config.get());
    RunContext context(config.get(), CATCH_MOVE(listener));

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "true"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    TestExpression expr(false, true); // result = true
    AssertionReaction reaction;

    context.handleExpr(info, expr, reaction);

    EXPECT_TRUE(context.lastAssertionPassed());
    EXPECT_FALSE(reaction.shouldDebugBreak);
    EXPECT_FALSE(reaction.shouldThrow);
}

TEST(HandleExprFailingTest_515, FailingExpressionPopulatesReaction_515) {
    auto config = makeConfig(false);
    auto listener = makeListener(config.get());
    RunContext context(config.get(), CATCH_MOVE(listener));

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "false"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    TestExpression expr(false, false); // result = false
    AssertionReaction reaction;

    context.handleExpr(info, expr, reaction);

    // On failure, populateReaction should set shouldThrow or shouldDebugBreak
    EXPECT_FALSE(context.lastAssertionPassed());
    // At least one of the reaction flags should be set for REQUIRE
    EXPECT_TRUE(reaction.shouldThrow || reaction.shouldDebugBreak || reaction.shouldSkip);
}

TEST(HandleExprNegatedPassTest_515, NegatedExprWithFalseResultPasses_515) {
    // When resultDisposition includes FalseTest, negated=true
    // result = expr.getResult() != negated = false != true = true -> passes
    auto config = makeConfig(false);
    auto listener = makeListener(config.get());
    RunContext context(config.get(), CATCH_MOVE(listener));

    AssertionInfo info;
    info.macroName = "REQUIRE_FALSE"_catch_sr;
    info.capturedExpression = "!false"_catch_sr;
    info.resultDisposition = static_cast<ResultDisposition::Flags>(
        ResultDisposition::Normal | ResultDisposition::FalseTest);

    TestExpression expr(false, false); // getResult() = false, negated = true => result = true
    AssertionReaction reaction;

    context.handleExpr(info, expr, reaction);

    EXPECT_TRUE(context.lastAssertionPassed());
    EXPECT_FALSE(reaction.shouldThrow);
}

TEST(HandleExprNegatedFailTest_515, NegatedExprWithTrueResultFails_515) {
    // negated=true, expr.getResult()=true => result = true != true = false -> fails
    auto config = makeConfig(false);
    auto listener = makeListener(config.get());
    RunContext context(config.get(), CATCH_MOVE(listener));

    AssertionInfo info;
    info.macroName = "REQUIRE_FALSE"_catch_sr;
    info.capturedExpression = "!true"_catch_sr;
    info.resultDisposition = static_cast<ResultDisposition::Flags>(
        ResultDisposition::Normal | ResultDisposition::FalseTest);

    TestExpression expr(false, true); // getResult() = true, negated = true => result = false
    AssertionReaction reaction;

    context.handleExpr(info, expr, reaction);

    EXPECT_FALSE(context.lastAssertionPassed());
    EXPECT_TRUE(reaction.shouldThrow || reaction.shouldDebugBreak || reaction.shouldSkip);
}

TEST(HandleExprWithSuccessfulResults_515, PassingExprWithIncludeSuccessfulResults_515) {
    // When m_includeSuccessfulResults is true, reportExpr should be called with Ok
    auto config = makeConfig(true); // includeSuccessful = true
    auto listener = makeListener(config.get());
    RunContext context(config.get(), CATCH_MOVE(listener));

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "true"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    TestExpression expr(false, true);
    AssertionReaction reaction;

    context.handleExpr(info, expr, reaction);

    EXPECT_TRUE(context.lastAssertionPassed());
    EXPECT_FALSE(reaction.shouldThrow);
    EXPECT_FALSE(reaction.shouldDebugBreak);
}

TEST(HandleExprBinaryExpression_515, BinaryExpressionPassing_515) {
    auto config = makeConfig(false);
    auto listener = makeListener(config.get());
    RunContext context(config.get(), CATCH_MOVE(listener));

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "1 == 1"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    TestExpression expr(true, true); // binary expression, passing
    AssertionReaction reaction;

    context.handleExpr(info, expr, reaction);

    EXPECT_TRUE(context.lastAssertionPassed());
    EXPECT_FALSE(reaction.shouldThrow);
}

TEST(HandleExprBinaryExpressionFail_515, BinaryExpressionFailing_515) {
    auto config = makeConfig(false);
    auto listener = makeListener(config.get());
    RunContext context(config.get(), CATCH_MOVE(listener));

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "1 == 2"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    TestExpression expr(true, false); // binary expression, failing
    AssertionReaction reaction;

    context.handleExpr(info, expr, reaction);

    EXPECT_FALSE(context.lastAssertionPassed());
    EXPECT_TRUE(reaction.shouldThrow || reaction.shouldDebugBreak || reaction.shouldSkip);
}

TEST(HandleExprReactionInitialState_515, ReactionUnchangedOnPass_515) {
    // When expression passes, reaction should not be populated
    auto config = makeConfig(false);
    auto listener = makeListener(config.get());
    RunContext context(config.get(), CATCH_MOVE(listener));

    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "true"_catch_sr;
    info.resultDisposition = ResultDisposition::ContinueOnFailure;

    TestExpression expr(false, true);
    AssertionReaction reaction;
    reaction.shouldDebugBreak = false;
    reaction.shouldThrow = false;
    reaction.shouldSkip = false;

    context.handleExpr(info, expr, reaction);

    EXPECT_FALSE(reaction.shouldDebugBreak);
    EXPECT_FALSE(reaction.shouldThrow);
    EXPECT_FALSE(reaction.shouldSkip);
}

TEST(HandleExprContinueOnFailure_515, FailWithContinueDisposition_515) {
    // CHECK-style: ContinueOnFailure - should fail but might not set shouldThrow
    auto config = makeConfig(false);
    auto listener = makeListener(config.get());
    RunContext context(config.get(), CATCH_MOVE(listener));

    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "false"_catch_sr;
    info.resultDisposition = ResultDisposition::ContinueOnFailure;

    TestExpression expr(false, false);
    AssertionReaction reaction;

    context.handleExpr(info, expr, reaction);

    EXPECT_FALSE(context.lastAssertionPassed());
    // With ContinueOnFailure, shouldThrow should be false (CHECK vs REQUIRE behavior)
}

TEST(HandleExprMultipleCalls_515, ConsecutiveCallsResetState_515) {
    auto config = makeConfig(false);
    auto listener = makeListener(config.get());
    RunContext context(config.get(), CATCH_MOVE(listener));

    // First call: passing
    {
        AssertionInfo info;
        info.macroName = "REQUIRE"_catch_sr;
        info.capturedExpression = "true"_catch_sr;
        info.resultDisposition = ResultDisposition::Normal;

        TestExpression expr(false, true);
        AssertionReaction reaction;
        context.handleExpr(info, expr, reaction);
        EXPECT_TRUE(context.lastAssertionPassed());
    }

    // Second call: failing (with ContinueOnFailure to avoid throw)
    {
        AssertionInfo info;
        info.macroName = "CHECK"_catch_sr;
        info.capturedExpression = "false"_catch_sr;
        info.resultDisposition = ResultDisposition::ContinueOnFailure;

        TestExpression expr(false, false);
        AssertionReaction reaction;
        context.handleExpr(info, expr, reaction);
        EXPECT_FALSE(context.lastAssertionPassed());
    }
}
