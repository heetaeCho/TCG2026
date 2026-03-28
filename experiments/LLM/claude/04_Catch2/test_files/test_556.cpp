#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_assertion_handler.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Invoke;
using ::testing::AtLeast;

class MockResultCapture : public IResultCapture {
public:
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

class AssertionHandlerTest_556 : public ::testing::Test {
protected:
    void SetUp() override {
        mockCapture_ = new MockResultCapture();
        // Set the mock as the current result capture context
        // This depends on Catch2's internal context mechanism
        previousCapture_ = getCurrentContext().getResultCapture();
        getCurrentMutableContext().setResultCapture(mockCapture_);
    }

    void TearDown() override {
        getCurrentMutableContext().setResultCapture(previousCapture_);
        delete mockCapture_;
    }

    MockResultCapture* mockCapture_ = nullptr;
    IResultCapture* previousCapture_ = nullptr;
};

TEST_F(AssertionHandlerTest_556, HandleExceptionThrownAsExpected_CallsHandleNonExprWithOk_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, ResultWas::Ok, _)).Times(1);
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(0));

    AssertionHandler handler(
        "REQUIRE_THROWS"_catch_sr,
        SourceLineInfo("test_file.cpp", 42),
        "expression"_catch_sr,
        ResultDisposition::Normal
    );
    handler.handleExceptionThrownAsExpected();
    handler.complete();
}

TEST_F(AssertionHandlerTest_556, HandleExceptionNotThrownAsExpected_CallsHandleNonExpr_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, ResultWas::Ok, _)).Times(1);
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(0));

    AssertionHandler handler(
        "REQUIRE_NOTHROW"_catch_sr,
        SourceLineInfo("test_file.cpp", 50),
        "expression"_catch_sr,
        ResultDisposition::Normal
    );
    handler.handleExceptionNotThrownAsExpected();
    handler.complete();
}

TEST_F(AssertionHandlerTest_556, HandleUnexpectedExceptionNotThrown_CallsCapture_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleUnexpectedExceptionNotThrown(_, _)).Times(1);
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(0));

    AssertionHandler handler(
        "REQUIRE_THROWS"_catch_sr,
        SourceLineInfo("test_file.cpp", 60),
        "expression"_catch_sr,
        ResultDisposition::Normal
    );
    handler.handleUnexpectedExceptionNotThrown();
    handler.complete();
}

TEST_F(AssertionHandlerTest_556, HandleMessage_CallsCaptureHandleMessage_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleMessage(_, ResultWas::ExplicitFailure, _, _)).Times(1);
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(0));

    AssertionHandler handler(
        "FAIL"_catch_sr,
        SourceLineInfo("test_file.cpp", 70),
        ""_catch_sr,
        ResultDisposition::Normal
    );
    handler.handleMessage(ResultWas::ExplicitFailure, "test failure message");
    handler.complete();
}

TEST_F(AssertionHandlerTest_556, HandleThrowingCallSkipped_CallsHandleNonExpr_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(0));

    AssertionHandler handler(
        "REQUIRE_THROWS"_catch_sr,
        SourceLineInfo("test_file.cpp", 80),
        "expression"_catch_sr,
        ResultDisposition::Normal
    );
    handler.handleThrowingCallSkipped();
    handler.complete();
}

TEST_F(AssertionHandlerTest_556, HandleUnexpectedInflightException_CallsCapture_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleUnexpectedInflightException(_, _, _)).Times(1);
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(0));

    AssertionHandler handler(
        "REQUIRE"_catch_sr,
        SourceLineInfo("test_file.cpp", 90),
        "expression"_catch_sr,
        ResultDisposition::Normal
    );
    handler.handleUnexpectedInflightException();
    handler.complete();
}

TEST_F(AssertionHandlerTest_556, Complete_CalledOnce_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, ResultWas::Ok, _)).Times(1);
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(0));

    AssertionHandler handler(
        "REQUIRE_THROWS"_catch_sr,
        SourceLineInfo("test_file.cpp", 100),
        "expression"_catch_sr,
        ResultDisposition::Normal
    );
    handler.handleExceptionThrownAsExpected();
    handler.complete();
}

TEST_F(AssertionHandlerTest_556, DestructorWithoutComplete_HandlesIncomplete_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(1));

    {
        AssertionHandler handler(
            "REQUIRE"_catch_sr,
            SourceLineInfo("test_file.cpp", 110),
            "expression"_catch_sr,
            ResultDisposition::Normal
        );
        // Intentionally not calling complete() - destructor should handle incomplete
    }
}

TEST_F(AssertionHandlerTest_556, HandleMessageWithInfo_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleMessage(_, ResultWas::Info, _, _)).Times(1);
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(0));

    AssertionHandler handler(
        "INFO"_catch_sr,
        SourceLineInfo("test_file.cpp", 120),
        ""_catch_sr,
        ResultDisposition::Normal
    );
    handler.handleMessage(ResultWas::Info, "info message");
    handler.complete();
}

TEST_F(AssertionHandlerTest_556, HandleMessageWithWarning_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleMessage(_, ResultWas::Warning, _, _)).Times(1);
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(0));

    AssertionHandler handler(
        "WARN"_catch_sr,
        SourceLineInfo("test_file.cpp", 130),
        ""_catch_sr,
        ResultDisposition::Normal
    );
    handler.handleMessage(ResultWas::Warning, "warning message");
    handler.complete();
}

TEST_F(AssertionHandlerTest_556, ConstructionWithEmptyMacroName_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, ResultWas::Ok, _)).Times(1);
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(0));

    AssertionHandler handler(
        ""_catch_sr,
        SourceLineInfo("test_file.cpp", 140),
        ""_catch_sr,
        ResultDisposition::Normal
    );
    handler.handleExceptionThrownAsExpected();
    handler.complete();
}

TEST_F(AssertionHandlerTest_556, ConstructionWithNegateDisposition_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, _, _)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(0));

    AssertionHandler handler(
        "REQUIRE_FALSE"_catch_sr,
        SourceLineInfo("test_file.cpp", 150),
        "!expression"_catch_sr,
        ResultDisposition::Flags(ResultDisposition::Normal | ResultDisposition::NegateResult)
    );
    handler.handleExceptionThrownAsExpected();
    handler.complete();
}

TEST_F(AssertionHandlerTest_556, AllowThrows_ReturnsValue_556) {
    EXPECT_CALL(*mockCapture_, notifyAssertionStarted(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleIncomplete(_)).Times(AtLeast(0));
    EXPECT_CALL(*mockCapture_, handleNonExpr(_, _, _)).Times(AtLeast(0));

    AssertionHandler handler(
        "REQUIRE"_catch_sr,
        SourceLineInfo("test_file.cpp", 160),
        "expression"_catch_sr,
        ResultDisposition::Normal
    );

    // allowThrows() should return a bool value (we just verify it doesn't crash)
    bool result = handler.allowThrows();
    (void)result; // Just ensure it's callable

    handler.handleExceptionThrownAsExpected();
    handler.complete();
}
