#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_assertion_handler.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/internal/catch_run_context.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_result_type.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Eq;
using ::testing::An;

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

class AssertionHandlerTest_557 : public ::testing::Test {
protected:
    void SetUp() override {
        mockCapture_ = std::make_unique<MockResultCapture>();
        // We need to set the mock as the current result capture in Catch2's context
        originalCapture_ = Catch::getResultCapture();
        Catch::setResultCapture(mockCapture_.get());
    }

    void TearDown() override {
        Catch::setResultCapture(originalCapture_);
    }

    std::unique_ptr<MockResultCapture> mockCapture_;
    IResultCapture* originalCapture_ = nullptr;
};

TEST_F(AssertionHandlerTest_557, HandleExceptionNotThrownAsExpected_CallsHandleNonExprWithOk_557) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(1);
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, Eq(ResultWas::Ok), _)).Times(1);

    AssertionHandler handler(
        "REQUIRE_NOTHROW"_catch_sr,
        SourceLineInfo("test_file.cpp", 42),
        "someExpression"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleExceptionNotThrownAsExpected();
    handler.complete();
}

TEST_F(AssertionHandlerTest_557, HandleExceptionThrownAsExpected_CallsHandleNonExpr_557) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(1);
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, _, _)).Times(1);

    AssertionHandler handler(
        "REQUIRE_THROWS"_catch_sr,
        SourceLineInfo("test_file.cpp", 10),
        "throwingExpr"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleExceptionThrownAsExpected();
    handler.complete();
}

TEST_F(AssertionHandlerTest_557, HandleUnexpectedExceptionNotThrown_CallsCapture_557) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(1);
    EXPECT_CALL(*mockCapture_, handleUnexpectedExceptionNotThrown(_, _)).Times(1);

    AssertionHandler handler(
        "REQUIRE_THROWS"_catch_sr,
        SourceLineInfo("test_file.cpp", 20),
        "noThrowExpr"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleUnexpectedExceptionNotThrown();
    handler.complete();
}

TEST_F(AssertionHandlerTest_557, HandleUnexpectedInflightException_CallsCapture_557) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(1);
    EXPECT_CALL(*mockCapture_, handleUnexpectedInflightException(_, _, _)).Times(1);

    AssertionHandler handler(
        "REQUIRE"_catch_sr,
        SourceLineInfo("test_file.cpp", 30),
        "expr"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleUnexpectedInflightException();
    handler.complete();
}

TEST_F(AssertionHandlerTest_557, HandleMessage_CallsCaptureHandleMessage_557) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(1);
    EXPECT_CALL(*mockCapture_, handleMessage(_, Eq(ResultWas::ExplicitFailure), _, _)).Times(1);

    AssertionHandler handler(
        "FAIL"_catch_sr,
        SourceLineInfo("test_file.cpp", 50),
        ""_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleMessage(ResultWas::ExplicitFailure, "failure message");
    handler.complete();
}

TEST_F(AssertionHandlerTest_557, HandleThrowingCallSkipped_CallsHandleNonExpr_557) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(1);
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, _, _)).Times(1);

    AssertionHandler handler(
        "REQUIRE_NOTHROW"_catch_sr,
        SourceLineInfo("test_file.cpp", 60),
        "skippedExpr"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleThrowingCallSkipped();
    handler.complete();
}

TEST_F(AssertionHandlerTest_557, Complete_CanBeCalledAfterHandling_557) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(1);
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, Eq(ResultWas::Ok), _)).Times(1);

    AssertionHandler handler(
        "REQUIRE_NOTHROW"_catch_sr,
        SourceLineInfo("test_file.cpp", 70),
        "expr"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleExceptionNotThrownAsExpected();
    handler.complete();
    // No crash or double-handling expected
}

TEST_F(AssertionHandlerTest_557, ConstructorNotifiesAssertionStarted_557) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(1);

    AssertionHandler handler(
        "CHECK"_catch_sr,
        SourceLineInfo("test_file.cpp", 80),
        "expression"_catch_sr,
        ResultDisposition::ContinueOnFailure
    );

    // Need to complete to avoid assertion in destructor
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, _, _)).Times(1);
    handler.handleExceptionNotThrownAsExpected();
    handler.complete();
}

TEST_F(AssertionHandlerTest_557, HandleExceptionNotThrownAsExpected_ResultWasOk_557) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(1);
    
    // Verify specifically that ResultWas::Ok is passed
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, Eq(ResultWas::Ok), _))
        .Times(1);

    AssertionHandler handler(
        "REQUIRE_NOTHROW"_catch_sr,
        SourceLineInfo("verify.cpp", 100),
        "noThrow()"_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleExceptionNotThrownAsExpected();
    handler.complete();
}

TEST_F(AssertionHandlerTest_557, DifferentMacroNames_557) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(1);
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, Eq(ResultWas::Ok), _)).Times(1);

    AssertionHandler handler(
        "CHECK_NOTHROW"_catch_sr,
        SourceLineInfo("different.cpp", 200),
        "differentExpr()"_catch_sr,
        ResultDisposition::ContinueOnFailure
    );

    handler.handleExceptionNotThrownAsExpected();
    handler.complete();
}

TEST_F(AssertionHandlerTest_557, HandleMessageWithInfo_557) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(1);
    EXPECT_CALL(*mockCapture_, handleMessage(_, Eq(ResultWas::Info), _, _)).Times(1);

    AssertionHandler handler(
        "INFO"_catch_sr,
        SourceLineInfo("info.cpp", 300),
        ""_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleMessage(ResultWas::Info, "info message");
    handler.complete();
}

TEST_F(AssertionHandlerTest_557, HandleMessageWithWarning_557) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(1);
    EXPECT_CALL(*mockCapture_, handleMessage(_, Eq(ResultWas::Warning), _, _)).Times(1);

    AssertionHandler handler(
        "WARN"_catch_sr,
        SourceLineInfo("warn.cpp", 400),
        ""_catch_sr,
        ResultDisposition::Normal
    );

    handler.handleMessage(ResultWas::Warning, "warning message");
    handler.complete();
}
