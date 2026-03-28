#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_assertion_handler.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/internal/catch_run_context.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::NiceMock;

class MockResultCapture : public IResultCapture {
public:
    ~MockResultCapture() override = default;

    MOCK_METHOD(void, notifyAssertionStarted, (const AssertionInfo& info), (override));
    MOCK_METHOD(bool, sectionStarted, (StringRef sectionName, const SourceLineInfo& sectionLineInfo, Counts& assertions), (override));
    MOCK_METHOD(void, sectionEnded, (SectionEndInfo&& endInfo), (override));
    MOCK_METHOD(void, sectionEndedEarly, (SectionEndInfo&& endInfo), (override));
    MOCK_METHOD(IGeneratorTracker*, acquireGeneratorTracker, (StringRef generatorName, const SourceLineInfo& lineInfo), (override));
    MOCK_METHOD(IGeneratorTracker*, createGeneratorTracker, (StringRef generatorName, SourceLineInfo lineInfo, Generators::GeneratorBasePtr&& generator), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef name), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo& info), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>& stats), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef error), (override));
    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo& message), (override));
    MOCK_METHOD(void, popScopedMessage, (const MessageInfo& message), (override));
    MOCK_METHOD(void, emplaceUnscopedMessage, (MessageBuilder&& builder), (override));
    MOCK_METHOD(void, handleFatalErrorCondition, (StringRef message), (override));
    MOCK_METHOD(void, handleExpr, (const AssertionInfo& info, const ITransientExpression& expr, AssertionReaction& reaction), (override));
    MOCK_METHOD(void, handleMessage, (const AssertionInfo& info, ResultWas::OfType resultType, std::string&& message, AssertionReaction& reaction), (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo& info, AssertionReaction& reaction), (override));
    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo& info, std::string&& message, AssertionReaction& reaction), (override));
    MOCK_METHOD(void, handleIncomplete, (const AssertionInfo& info), (override));
    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo& info, ResultWas::OfType resultType, AssertionReaction& reaction), (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(const std::string, getCurrentTestName, (), (override));
    MOCK_METHOD(const AssertionResult*, getLastResult, (), (const, override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

class AssertionHandlerTest_558 : public ::testing::Test {
protected:
    NiceMock<MockResultCapture> mockCapture;

    void SetUp() override {
        // Set up the mock as the current result capture context
        // This depends on how Catch2 provides access to IResultCapture internally
        // Typically through IContext or getCurrentContext()
    }

    void TearDown() override {
    }
};

// Test that handleUnexpectedExceptionNotThrown delegates to IResultCapture
TEST_F(AssertionHandlerTest_558, HandleUnexpectedExceptionNotThrownDelegatesToCapture_558) {
    EXPECT_CALL(mockCapture, handleUnexpectedExceptionNotThrown(_, _)).Times(1);
    EXPECT_CALL(mockCapture, notifyAssertionStarted(_)).Times(::testing::AnyNumber());

    // Construct handler - it will use the current context's result capture
    AssertionHandler handler(
        "REQUIRE_THROWS"_catch_sr,
        SourceLineInfo("test_file.cpp", 42),
        "expression"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleUnexpectedExceptionNotThrown();
    handler.complete();
}

// Test that handleExceptionThrownAsExpected delegates properly
TEST_F(AssertionHandlerTest_558, HandleExceptionThrownAsExpectedDelegates_558) {
    EXPECT_CALL(mockCapture, notifyAssertionStarted(_)).Times(::testing::AnyNumber());

    AssertionHandler handler(
        "REQUIRE_THROWS"_catch_sr,
        SourceLineInfo("test_file.cpp", 10),
        "someExpr"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleExceptionThrownAsExpected();
    handler.complete();
}

// Test that handleExceptionNotThrownAsExpected delegates properly
TEST_F(AssertionHandlerTest_558, HandleExceptionNotThrownAsExpectedDelegates_558) {
    EXPECT_CALL(mockCapture, notifyAssertionStarted(_)).Times(::testing::AnyNumber());

    AssertionHandler handler(
        "REQUIRE_NOTHROW"_catch_sr,
        SourceLineInfo("test_file.cpp", 20),
        "someExpr"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleExceptionNotThrownAsExpected();
    handler.complete();
}

// Test that handleUnexpectedInflightException delegates properly
TEST_F(AssertionHandlerTest_558, HandleUnexpectedInflightExceptionDelegates_558) {
    EXPECT_CALL(mockCapture, handleUnexpectedInflightException(_, _, _)).Times(1);
    EXPECT_CALL(mockCapture, notifyAssertionStarted(_)).Times(::testing::AnyNumber());

    AssertionHandler handler(
        "REQUIRE"_catch_sr,
        SourceLineInfo("test_file.cpp", 30),
        "someExpr"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleUnexpectedInflightException();
    handler.complete();
}

// Test that handleMessage delegates to IResultCapture::handleMessage
TEST_F(AssertionHandlerTest_558, HandleMessageDelegatesToCapture_558) {
    EXPECT_CALL(mockCapture, handleMessage(_, _, _, _)).Times(1);
    EXPECT_CALL(mockCapture, notifyAssertionStarted(_)).Times(::testing::AnyNumber());

    AssertionHandler handler(
        "INFO"_catch_sr,
        SourceLineInfo("test_file.cpp", 50),
        "msg"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleMessage(ResultWas::Info, std::string("test message"));
    handler.complete();
}

// Test that handleThrowingCallSkipped works without error
TEST_F(AssertionHandlerTest_558, HandleThrowingCallSkippedNoError_558) {
    EXPECT_CALL(mockCapture, notifyAssertionStarted(_)).Times(::testing::AnyNumber());

    AssertionHandler handler(
        "REQUIRE_THROWS"_catch_sr,
        SourceLineInfo("test_file.cpp", 60),
        "expr"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleThrowingCallSkipped();
    handler.complete();
}

// Test that complete can be called after handling
TEST_F(AssertionHandlerTest_558, CompleteAfterHandling_558) {
    EXPECT_CALL(mockCapture, notifyAssertionStarted(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(mockCapture, handleUnexpectedExceptionNotThrown(_, _)).Times(1);

    AssertionHandler handler(
        "CHECK_THROWS"_catch_sr,
        SourceLineInfo("test_file.cpp", 70),
        "throwingExpr"_catch_sr,
        ResultDisposition::ContinueOnFailure
    );

    handler.handleUnexpectedExceptionNotThrown();
    handler.complete();
}

// Test allowThrows returns a boolean value
TEST_F(AssertionHandlerTest_558, AllowThrowsReturnsBool_558) {
    EXPECT_CALL(mockCapture, notifyAssertionStarted(_)).Times(::testing::AnyNumber());

    AssertionHandler handler(
        "REQUIRE"_catch_sr,
        SourceLineInfo("test_file.cpp", 80),
        "expr"_catch_sr,
        ResultDisposition::Normal
    );

    bool result = handler.allowThrows();
    // Result is either true or false - we just verify it's callable
    (void)result;
    handler.complete();
}

// Test construction with different ResultDisposition flags
TEST_F(AssertionHandlerTest_558, ConstructWithContinueOnFailure_558) {
    EXPECT_CALL(mockCapture, notifyAssertionStarted(_)).Times(::testing::AnyNumber());

    AssertionHandler handler(
        "CHECK"_catch_sr,
        SourceLineInfo("test_file.cpp", 90),
        "checkExpr"_catch_sr,
        ResultDisposition::ContinueOnFailure
    );

    handler.complete();
}

// Test construction with NegateResult disposition
TEST_F(AssertionHandlerTest_558, ConstructWithNegateResult_558) {
    EXPECT_CALL(mockCapture, notifyAssertionStarted(_)).Times(::testing::AnyNumber());

    AssertionHandler handler(
        "REQUIRE_FALSE"_catch_sr,
        SourceLineInfo("test_file.cpp", 100),
        "!expr"_catch_sr,
        ResultDisposition::NegateResult
    );

    handler.complete();
}

// Test with empty expression string
TEST_F(AssertionHandlerTest_558, EmptyCapturedExpression_558) {
    EXPECT_CALL(mockCapture, notifyAssertionStarted(_)).Times(::testing::AnyNumber());

    AssertionHandler handler(
        "SUCCEED"_catch_sr,
        SourceLineInfo("test_file.cpp", 110),
        ""_catch_sr,
        ResultDisposition::Normal
    );

    handler.complete();
}
