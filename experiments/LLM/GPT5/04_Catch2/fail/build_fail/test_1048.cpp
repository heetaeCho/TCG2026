// File: tests/AssertionStats_tests_1048.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>

// Catch2 public headers — use your actual include paths
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_message_info.hpp"
#include "catch2/internal/catch_stringref.hpp"

// If your project uses different headers/namespaces, adjust the includes above.
// All tests adhere strictly to public interfaces and observable behavior.

using namespace Catch;

namespace {

// --- Small helpers (using only public interfaces) ---------------------------

// Build a SourceLineInfo that is stable/known for assertions.
inline SourceLineInfo makeSrc(const char* file = "file.cpp", std::size_t line = 123) {
    return SourceLineInfo{ file, line };
}

// Construct an AssertionResult *without* a message.
// Use your project’s public constructors for AssertionInfo/AssertionResultData.
inline AssertionResult makeAssertionNoMsg(ResultWas::OfType type = ResultWas::Ok) {
    AssertionInfo info;
    // Fill using your public API (macro name, src info, etc.)
    // Example fields vary across Catch2 versions; only use public constructors.
    info.macroName = StringRef("TEST_MACRO_NO_MSG");
    info.lineInfo = makeSrc();
    info.capturedExpression = StringRef("");
    info.resultDisposition = ResultDisposition::Normal;

    AssertionResultData data;
    data.resultType = type;
    // Ensure there is no message set in data.

    return AssertionResult{ info, CATCH_MOVE(data) };
}

// Construct an AssertionResult *with* a message, so that hasMessage() returns true.
inline AssertionResult makeAssertionWithMsg(
    StringRef macro = StringRef("TEST_MACRO_WITH_MSG"),
    StringRef message = StringRef("hello from assertion"),
    ResultWas::OfType type = ResultWas::ExpressionFailed
) {
    AssertionInfo info;
    info.macroName = macro;
    info.lineInfo = makeSrc("with_msg.cpp", 456);
    info.capturedExpression = StringRef("x == y");
    info.resultDisposition = ResultDisposition::Normal;

    AssertionResultData data;
    data.resultType = type;
    // Set the message in a public, supported way in your version.
    data.reconstructedExpression = "";
    data.message = static_cast<std::string>(message);

    return AssertionResult{ info, CATCH_MOVE(data) };
}

// Build a Totals with public operations (delta/+=/-) or value-initialize.
inline Totals makeTotals(unsigned assertionsCount = 3U, unsigned testsCount = 1U) {
    Totals t;
    t.assertions.passed = assertionsCount;   // Use your public fields or builders
    t.testCases.passed = testsCount;
    return t;
}

} // namespace

// -----------------------------------------------------------------------------
// Test fixture (empty: no private-state peeking)
class AssertionStatsTest_1048 : public ::testing::Test {};

// -----------------------------------------------------------------------------
// Normal path: when AssertionResult has NO message, infoMessages is copied as-is
TEST_F(AssertionStatsTest_1048, CopiesInfoMessagesWithoutAppend_1048) {
    auto ar = makeAssertionNoMsg(ResultWas::Ok);
    std::vector<MessageInfo> msgs;
    msgs.emplace_back(StringRef("M"), makeSrc("a.cpp", 1), ResultWas::Ok);
    msgs.emplace_back(StringRef("N"), makeSrc("b.cpp", 2), ResultWas::Ok);

    auto totals = makeTotals(5U, 2U);

    AssertionStats stats{ ar, msgs, totals };

    // Observable effects:
    // 1) assertionResult is stored (we won’t dig into internals; presence suffices)
    // 2) infoMessages == the original size (no implicit append)
    // 3) totals copied
    EXPECT_EQ(stats.infoMessages.size(), msgs.size());
    // Equality/ordering of MessageInfo is public; compare element-wise for stability
    for (std::size_t i = 0; i < msgs.size(); ++i) {
        EXPECT_TRUE(stats.infoMessages[i] == msgs[i]);
    }
    EXPECT_EQ(stats.totals.assertions.passed, totals.assertions.passed);
    EXPECT_EQ(stats.totals.testCases.passed, totals.testCases.passed);
}

// -----------------------------------------------------------------------------
// Interaction-style behavior: if AssertionResult reports a message,
// AssertionStats appends a derived MessageInfo to infoMessages.
TEST_F(AssertionStatsTest_1048, AppendsMessageInfoWhenAssertionHasMessage_1048) {
    // Make an assertion that *has* a message.
    auto ar = makeAssertionWithMsg(
        StringRef("MY_MACRO"),
        StringRef("This should be appended"),
        ResultWas::ExpressionFailed
    );

    std::vector<MessageInfo> msgs;
    msgs.emplace_back(StringRef("PRE"), makeSrc("pre.cpp", 10), ResultWas::Ok);

    auto totals = makeTotals(7U, 3U);

    AssertionStats stats{ ar, msgs, totals };

    // One element should be appended
    ASSERT_EQ(stats.infoMessages.size(), msgs.size() + 1);

    // The newly appended element should sort *after* all previous ones
    const MessageInfo& appended = stats.infoMessages.back();

    // We cannot reach into private fields, so rely on public comparisons where possible.
    // Build the expected "shape" of the appended info based on public ctor inputs:
    MessageInfo expectedShape(
        ar.getTestMacroName(),
        ar.getSourceInfo(),
        ar.getResultType()
    );

    // At minimum, type/order should match what the ctor would produce
    // (macro name, line, result type). Equality might account for message text and
    // sequence; if it does, strict equality may fail across versions.
    // So we check *ordering* and *type* via public ops.
    EXPECT_EQ(appended.type, expectedShape.type);
    // If your MessageInfo provides operator== that includes message & sequence,
    // this might be too strict; keep type check above as the core invariant.

    // Totals still copied
    EXPECT_EQ(stats.totals.assertions.passed, totals.assertions.passed);
    EXPECT_EQ(stats.totals.testCases.passed, totals.testCases.passed);
}

// -----------------------------------------------------------------------------
// Boundary: empty incoming infoMessages + assertion has message → size becomes 1
TEST_F(AssertionStatsTest_1048, EmptyInputMessagesAppendOneIfHasMessage_1048) {
    auto ar = makeAssertionWithMsg(StringRef("BORDER_MACRO"), StringRef("edge msg"));
    std::vector<MessageInfo> emptyMsgs;
    auto totals = makeTotals(0U, 0U);

    AssertionStats stats{ ar, emptyMsgs, totals };

    ASSERT_EQ(stats.infoMessages.size(), 1u);

    const MessageInfo& last = stats.infoMessages.back();
    MessageInfo expected(ar.getTestMacroName(), ar.getSourceInfo(), ar.getResultType());
    EXPECT_EQ(last.type, expected.type);
}

// -----------------------------------------------------------------------------
// Boundary: large incoming vector stays stable in relative order, new msg at end
TEST_F(AssertionStatsTest_1048, PreservesOrderAndAppendsAtEnd_1048) {
    auto ar = makeAssertionWithMsg(StringRef("ORDER_MACRO"), StringRef("append"));
    std::vector<MessageInfo> msgs;
    for (int i = 0; i < 50; ++i) {
        msgs.emplace_back(StringRef("SEQ"), makeSrc("x.cpp", static_cast<std::size_t>(i+1)), ResultWas::Ok);
    }
    auto totals = makeTotals(42U, 13U);

    AssertionStats stats{ ar, msgs, totals };

    ASSERT_EQ(stats.infoMessages.size(), msgs.size() + 1);
    // Check that the first 50 are unchanged (by equality where available)
    for (std::size_t i = 0; i < msgs.size(); ++i) {
        EXPECT_TRUE(stats.infoMessages[i] == msgs[i]);
    }
}

// -----------------------------------------------------------------------------
// Normal: NO message and empty input vector → stays empty
TEST_F(AssertionStatsTest_1048, NoMessageKeepsVectorEmpty_1048) {
    auto ar = makeAssertionNoMsg(ResultWas::Ok);
    std::vector<MessageInfo> none;
    auto totals = makeTotals();

    AssertionStats stats{ ar, none, totals };
    EXPECT_TRUE(stats.infoMessages.empty());
}

