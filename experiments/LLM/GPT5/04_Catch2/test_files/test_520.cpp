// run_context_handle_nonexpr_520_test.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the headers from the prompt (paths as provided)
#include "Catch2/src/catch2/internal/catch_run_context.hpp"
#include "Catch2/src/catch2/internal/catch_assertion_handler.hpp"
#include "Catch2/src/catch2/catch_assertion_info.hpp"
#include "Catch2/src/catch2/catch_assertion_result.hpp"

using ::testing::Bool;
using ::testing::Eq;

namespace {

// --------- Test seams for interaction verification (no logic reimplementation) ---------
struct InteractionRecorder {
    int assertionEndedCalls = 0;
    int populateReactionCalls = 0;
    bool lastIsOk = false;
} g_rec;

// Provide minimal constructor/destructor so we can instantiate RunContext.
// They do not perform any production logic.
} // namespace

namespace Catch {

// Provide empty IEventListenerPtr-compatible arg in ctor signature.
// We do not need real reporter nor config for these tests.
RunContext::RunContext(IConfig const* /*_config*/, IEventListenerPtr&& /*reporter*/) {}
RunContext::~RunContext() {}

// Record that assertionEnded was called and whether the result is ok.
void RunContext::assertionEnded(AssertionResult&& result) {
    ++g_rec.assertionEndedCalls;
    g_rec.lastIsOk = result.isOk();
}

// Do not alter any state; just satisfy linkage.
void RunContext::resetAssertionInfo() {}

// Record that populateReaction was called. For determinism in tests, toggle a flag.
void RunContext::populateReaction(AssertionReaction& reaction) {
    ++g_rec.populateReactionCalls;
    // Deterministic observable tweak so tests can assert a change on failure path
    reaction.shouldThrow = true;
}

} // namespace Catch


// ---------------------------- Test Fixture ----------------------------
class RunContextHandleNonExprTest_520 : public ::testing::Test {
protected:
    void SetUp() override {
        g_rec = InteractionRecorder{}; // reset counters
    }
    // Helper to create a default AssertionInfo
    static Catch::AssertionInfo DefaultInfo() {
        // Aggregate-init with empty StringRefs and zero flags is fine for interface-level testing
        Catch::AssertionInfo info{};
        return info;
    }
};


// ---------------------------- Tests ----------------------------

// Normal: OK result should NOT call populateReaction and should call assertionEnded once.
TEST_F(RunContextHandleNonExprTest_520, OkResult_DoesNotPopulateReaction_520) {
    Catch::RunContext ctx{/*_config*/nullptr, /*reporter*/{}};

    Catch::AssertionInfo info = DefaultInfo();
    Catch::AssertionReaction reaction{}; // defaults to all false

    ctx.handleNonExpr(info, Catch::ResultWas::Ok, reaction);

    EXPECT_EQ(g_rec.assertionEndedCalls, 1);
    EXPECT_TRUE(g_rec.lastIsOk);                  // assertionEnded saw an OK result
    EXPECT_EQ(g_rec.populateReactionCalls, 0);    // no population for OK
    // Reaction should remain unchanged
    EXPECT_FALSE(reaction.shouldDebugBreak);
    EXPECT_FALSE(reaction.shouldThrow);
    EXPECT_FALSE(reaction.shouldSkip);
}

// Failure: non-OK result should call populateReaction and assertionEnded once.
TEST_F(RunContextHandleNonExprTest_520, FailureResult_PopulatesReaction_AndCallsAssertionEnded_520) {
    Catch::RunContext ctx{/*_config*/nullptr, /*reporter*/{}};

    Catch::AssertionInfo info = DefaultInfo();
    Catch::AssertionReaction reaction{}; // defaults false

    // Use a clearly non-OK result type; ExplicitFailure is representative
    ctx.handleNonExpr(info, Catch::ResultWas::ExplicitFailure, reaction);

    EXPECT_EQ(g_rec.assertionEndedCalls, 1);
    EXPECT_FALSE(g_rec.lastIsOk);                // assertionEnded saw a non-OK result
    EXPECT_EQ(g_rec.populateReactionCalls, 1);   // reaction populated for failure

    // Our seam flips shouldThrow=true to provide an observable effect
    EXPECT_TRUE(reaction.shouldThrow);
    EXPECT_FALSE(reaction.shouldDebugBreak);
    EXPECT_FALSE(reaction.shouldSkip);
}

// Idempotence on reaction: When already set, OK result should not overwrite reaction.
TEST_F(RunContextHandleNonExprTest_520, OkResult_DoesNotOverwriteExistingReaction_520) {
    Catch::RunContext ctx{/*_config*/nullptr, /*reporter*/{}};

    Catch::AssertionInfo info = DefaultInfo();
    Catch::AssertionReaction reaction{};
    // Pre-set some flags to ensure the function does not touch them on success
    reaction.shouldDebugBreak = true;
    reaction.shouldSkip = true;

    ctx.handleNonExpr(info, Catch::ResultWas::Ok, reaction);

    EXPECT_EQ(g_rec.assertionEndedCalls, 1);
    EXPECT_TRUE(g_rec.lastIsOk);
    EXPECT_EQ(g_rec.populateReactionCalls, 0);

    // Verify reaction stayed as-is
    EXPECT_TRUE(reaction.shouldDebugBreak);
    EXPECT_TRUE(reaction.shouldSkip);
    EXPECT_FALSE(reaction.shouldThrow);
}

// Robustness: Empty/neutral AssertionInfo should still proceed via the same paths.
TEST_F(RunContextHandleNonExprTest_520, HandlesEmptyAssertionInfo_AndFailureFlow_520) {
    Catch::RunContext ctx{/*_config*/nullptr, /*reporter*/{}};

    Catch::AssertionInfo info{}; // empty/neutral
    Catch::AssertionReaction reaction{};

    ctx.handleNonExpr(info, Catch::ResultWas::ExplicitFailure, reaction);

    EXPECT_EQ(g_rec.assertionEndedCalls, 1);
    EXPECT_FALSE(g_rec.lastIsOk);
    EXPECT_EQ(g_rec.populateReactionCalls, 1);
    EXPECT_TRUE(reaction.shouldThrow); // observable effect from our seam
}

