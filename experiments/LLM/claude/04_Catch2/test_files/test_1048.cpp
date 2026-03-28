#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>

#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_message_info.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch;

namespace {

// Helper to create an AssertionResult with no message
AssertionResult createAssertionResultNoMessage() {
    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.lineInfo = SourceLineInfo("test_file.cpp", 42);
    info.resultDisposition = ResultDisposition::Normal;
    info.capturedExpression = "1 == 1"_catch_sr;

    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    // No message set

    return AssertionResult(info, CATCH_MOVE(data));
}

// Helper to create an AssertionResult with a message
AssertionResult createAssertionResultWithMessage(const std::string& msg) {
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.lineInfo = SourceLineInfo("test_file.cpp", 100);
    info.resultDisposition = ResultDisposition::Normal;
    info.capturedExpression = "a == b"_catch_sr;

    AssertionResultData data;
    data.resultType = ResultWas::ExpressionFailed;
    data.message = msg;

    return AssertionResult(info, CATCH_MOVE(data));
}

} // anonymous namespace

class AssertionStatsTest_1048 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction with no message in assertion result preserves infoMessages count
TEST_F(AssertionStatsTest_1048, ConstructWithNoMessage_InfoMessagesUnchanged_1048) {
    AssertionResult result = createAssertionResultNoMessage();
    std::vector<MessageInfo> infoMessages;
    Totals totals;

    AssertionStats stats(result, infoMessages, totals);

    // When assertionResult has no message, infoMessages should remain empty
    EXPECT_EQ(stats.infoMessages.size(), 0u);
}

// Test: Construction with a message in assertion result appends to infoMessages
TEST_F(AssertionStatsTest_1048, ConstructWithMessage_AppendsToInfoMessages_1048) {
    AssertionResult result = createAssertionResultWithMessage("some failure message");
    std::vector<MessageInfo> infoMessages;
    Totals totals;

    AssertionStats stats(result, infoMessages, totals);

    // When assertionResult has a message, one extra MessageInfo should be appended
    EXPECT_EQ(stats.infoMessages.size(), 1u);
}

// Test: Construction preserves existing infoMessages and appends when message present
TEST_F(AssertionStatsTest_1048, ConstructWithExistingInfoMessages_AppendsWhenMessagePresent_1048) {
    AssertionResult result = createAssertionResultWithMessage("failure");
    
    MessageInfo existingMsg("EXISTING_MACRO", SourceLineInfo("other.cpp", 10), ResultWas::Info);
    std::vector<MessageInfo> infoMessages;
    infoMessages.push_back(existingMsg);
    
    Totals totals;

    AssertionStats stats(result, infoMessages, totals);

    // Should have the original message plus the appended one
    EXPECT_EQ(stats.infoMessages.size(), 2u);
}

// Test: Construction preserves assertionResult
TEST_F(AssertionStatsTest_1048, ConstructPreservesAssertionResult_1048) {
    AssertionResult result = createAssertionResultNoMessage();
    std::vector<MessageInfo> infoMessages;
    Totals totals;

    AssertionStats stats(result, infoMessages, totals);

    EXPECT_EQ(stats.assertionResult.getResultType(), result.getResultType());
    EXPECT_EQ(stats.assertionResult.isOk(), result.isOk());
}

// Test: Construction preserves totals
TEST_F(AssertionStatsTest_1048, ConstructPreservesTotals_1048) {
    AssertionResult result = createAssertionResultNoMessage();
    std::vector<MessageInfo> infoMessages;
    Totals totals;
    totals.assertions.passed = 5;
    totals.assertions.failed = 3;
    totals.testCases.passed = 2;
    totals.testCases.failed = 1;

    AssertionStats stats(result, infoMessages, totals);

    EXPECT_EQ(stats.totals.assertions.passed, 5u);
    EXPECT_EQ(stats.totals.assertions.failed, 3u);
    EXPECT_EQ(stats.totals.testCases.passed, 2u);
    EXPECT_EQ(stats.totals.testCases.failed, 1u);
}

// Test: Copy construction works
TEST_F(AssertionStatsTest_1048, CopyConstruction_1048) {
    AssertionResult result = createAssertionResultNoMessage();
    std::vector<MessageInfo> infoMessages;
    Totals totals;

    AssertionStats original(result, infoMessages, totals);
    AssertionStats copy(original);

    EXPECT_EQ(copy.assertionResult.getResultType(), original.assertionResult.getResultType());
    EXPECT_EQ(copy.infoMessages.size(), original.infoMessages.size());
    EXPECT_EQ(copy.totals.assertions.passed, original.totals.assertions.passed);
}

// Test: Move construction works
TEST_F(AssertionStatsTest_1048, MoveConstruction_1048) {
    AssertionResult result = createAssertionResultNoMessage();
    std::vector<MessageInfo> infoMessages;
    Totals totals;
    totals.assertions.passed = 10;

    AssertionStats original(result, infoMessages, totals);
    AssertionStats moved(std::move(original));

    EXPECT_EQ(moved.totals.assertions.passed, 10u);
}

// Test: Empty infoMessages with no message result stays empty
TEST_F(AssertionStatsTest_1048, EmptyInfoMessagesNoMessageStaysEmpty_1048) {
    AssertionResult result = createAssertionResultNoMessage();
    std::vector<MessageInfo> emptyMessages;
    Totals totals;

    AssertionStats stats(result, emptyMessages, totals);

    EXPECT_TRUE(stats.infoMessages.empty());
}

// Test: The appended message info contains the assertion's message content
TEST_F(AssertionStatsTest_1048, AppendedMessageContainsCorrectContent_1048) {
    std::string expectedMessage = "test failure message";
    AssertionResult result = createAssertionResultWithMessage(expectedMessage);
    std::vector<MessageInfo> infoMessages;
    Totals totals;

    AssertionStats stats(result, infoMessages, totals);

    ASSERT_EQ(stats.infoMessages.size(), 1u);
    EXPECT_EQ(stats.infoMessages.back().message, expectedMessage);
}

// Test: The appended message info uses the macro name from the assertion result
TEST_F(AssertionStatsTest_1048, AppendedMessageUsesMacroName_1048) {
    AssertionResult result = createAssertionResultWithMessage("msg");
    std::vector<MessageInfo> infoMessages;
    Totals totals;

    AssertionStats stats(result, infoMessages, totals);

    ASSERT_EQ(stats.infoMessages.size(), 1u);
    EXPECT_EQ(stats.infoMessages.back().macroName, result.getTestMacroName());
}

// Test: The appended message info uses the source info from the assertion result
TEST_F(AssertionStatsTest_1048, AppendedMessageUsesSourceInfo_1048) {
    AssertionResult result = createAssertionResultWithMessage("msg");
    std::vector<MessageInfo> infoMessages;
    Totals totals;

    AssertionStats stats(result, infoMessages, totals);

    ASSERT_EQ(stats.infoMessages.size(), 1u);
    EXPECT_EQ(stats.infoMessages.back().lineInfo.line, result.getSourceInfo().line);
}

// Test: Multiple existing info messages are preserved and new one appended
TEST_F(AssertionStatsTest_1048, MultipleExistingInfoMessagesPreserved_1048) {
    AssertionResult result = createAssertionResultWithMessage("failure");
    
    std::vector<MessageInfo> infoMessages;
    infoMessages.push_back(MessageInfo("M1", SourceLineInfo("a.cpp", 1), ResultWas::Info));
    infoMessages.push_back(MessageInfo("M2", SourceLineInfo("b.cpp", 2), ResultWas::Info));
    infoMessages.push_back(MessageInfo("M3", SourceLineInfo("c.cpp", 3), ResultWas::Info));
    
    Totals totals;

    AssertionStats stats(result, infoMessages, totals);

    // 3 existing + 1 appended
    EXPECT_EQ(stats.infoMessages.size(), 4u);
}

// Test: Multiple existing info messages are preserved when no message
TEST_F(AssertionStatsTest_1048, MultipleExistingInfoMessagesPreservedNoAppend_1048) {
    AssertionResult result = createAssertionResultNoMessage();
    
    std::vector<MessageInfo> infoMessages;
    infoMessages.push_back(MessageInfo("M1", SourceLineInfo("a.cpp", 1), ResultWas::Info));
    infoMessages.push_back(MessageInfo("M2", SourceLineInfo("b.cpp", 2), ResultWas::Info));
    
    Totals totals;

    AssertionStats stats(result, infoMessages, totals);

    // Only the 2 existing, nothing appended
    EXPECT_EQ(stats.infoMessages.size(), 2u);
}

// Test: Default Totals are preserved correctly
TEST_F(AssertionStatsTest_1048, DefaultTotalsPreserved_1048) {
    AssertionResult result = createAssertionResultNoMessage();
    std::vector<MessageInfo> infoMessages;
    Totals totals; // default-initialized

    AssertionStats stats(result, infoMessages, totals);

    EXPECT_EQ(stats.totals.assertions.passed, 0u);
    EXPECT_EQ(stats.totals.assertions.failed, 0u);
    EXPECT_EQ(stats.totals.testCases.passed, 0u);
    EXPECT_EQ(stats.totals.testCases.failed, 0u);
}

// Test: The appended message's result type matches the assertion result type
TEST_F(AssertionStatsTest_1048, AppendedMessageResultTypeMatches_1048) {
    AssertionResult result = createAssertionResultWithMessage("error");
    std::vector<MessageInfo> infoMessages;
    Totals totals;

    AssertionStats stats(result, infoMessages, totals);

    ASSERT_EQ(stats.infoMessages.size(), 1u);
    EXPECT_EQ(stats.infoMessages.back().type, result.getResultType());
}
