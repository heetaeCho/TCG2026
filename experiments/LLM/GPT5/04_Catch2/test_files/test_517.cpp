// File: run_context_unexpected_exception_not_thrown_517_tests.cpp

#include <gtest/gtest.h>
#include <string>

// ---- Minimal surface declarations to exercise the public interface ----
namespace Catch {

// Tiny stand-in to satisfy interface usage in tests; we do not depend on internals.
struct StringRef {
    std::string s;
    StringRef() = default;
    /* implicit */ StringRef(const char* str) : s(str ? str : "") {}
};

struct ResultDisposition { enum Flags { None = 0 }; };

struct AssertionInfo {
    StringRef macroName;
    StringRef capturedExpression;
    ResultDisposition::Flags resultDisposition = ResultDisposition::None;
};

struct AssertionReaction {
    bool shouldDebugBreak = false;
    bool shouldThrow = false;
    bool shouldSkip = false;
};

namespace ResultWas {
    enum OfType {
        Unknown = -1,
        Ok = 0,
        Info = 1,
        Warning = 2,
        ExplicitSkip = 4,
        FailureBit = 16,
        ExpressionFailed = 17,
        ExplicitFailure = 18,
        Exception = 272,
        ThrewException = 273,
        DidntThrowException = 274,
        FatalErrorCondition = 528
    };
}

// Public interface under test (no reimplementation).
class RunContext {
public:
    // Implemented elsewhere (in the production TU); we only call it.
    void handleUnexpectedExceptionNotThrown(AssertionInfo const& info,
                                            AssertionReaction& reaction);

    // Collaborator called by the above; we provide a test stub below to observe calls.
    void handleNonExpr(AssertionInfo const& info,
                       ResultWas::OfType resultType,
                       AssertionReaction& reaction);
};

} // namespace Catch

// ---- Test stub & observation state for handleNonExpr ----
namespace {
int g_handleNonExpr_calls = 0;
Catch::ResultWas::OfType g_lastResultType = Catch::ResultWas::Unknown;
Catch::AssertionInfo const* g_lastInfo = nullptr;
Catch::AssertionReaction* g_lastReaction = nullptr;

void ResetObserver() {
    g_handleNonExpr_calls = 0;
    g_lastResultType = Catch::ResultWas::Unknown;
    g_lastInfo = nullptr;
    g_lastReaction = nullptr;
}
}  // namespace

// Define the collaborator so the real method can call into it.
// This does NOT reimplement any logic under test; it only records observable interactions.
void Catch::RunContext::handleNonExpr(const Catch::AssertionInfo& info,
                                      Catch::ResultWas::OfType resultType,
                                      Catch::AssertionReaction& reaction) {
    ++g_handleNonExpr_calls;
    g_lastInfo = &info;
    g_lastResultType = resultType;
    g_lastReaction = &reaction;
}

// ---- Tests ----

TEST(RunContext_517, CallsHandleNonExprWithDidntThrowException_517) {
    ResetObserver();

    Catch::RunContext ctx;
    Catch::AssertionInfo info;
    info.macroName = "REQUIRE";
    info.capturedExpression = "some_call()";

    Catch::AssertionReaction reaction; // defaults false/false/false

    // Act
    ctx.handleUnexpectedExceptionNotThrown(info, reaction);

    // Assert
    EXPECT_EQ(g_handleNonExpr_calls, 1) << "handleNonExpr should be called exactly once";
    EXPECT_EQ(g_lastResultType, Catch::ResultWas::DidntThrowException)
        << "Result type must be DidntThrowException";

    // Since our stub does not mutate reaction, its initial values should remain.
    EXPECT_FALSE(reaction.shouldDebugBreak);
    EXPECT_FALSE(reaction.shouldThrow);
    EXPECT_FALSE(reaction.shouldSkip);
}

TEST(RunContext_517, ForwardsAssertionInfoAndReaction_517) {
    ResetObserver();

    Catch::RunContext ctx;
    Catch::AssertionInfo info;
    info.macroName = "CHECK_THROWS_NOTHING";
    info.capturedExpression = "might_throw()";

    Catch::AssertionReaction reaction;

    // Act
    ctx.handleUnexpectedExceptionNotThrown(info, reaction);

    // Assert forwarding of references
    ASSERT_NE(g_lastInfo, nullptr);
    ASSERT_NE(g_lastReaction, nullptr);
    EXPECT_EQ(g_lastInfo, &info) << "AssertionInfo should be forwarded unchanged";
    EXPECT_EQ(g_lastReaction, &reaction) << "AssertionReaction should be forwarded unchanged";
}
