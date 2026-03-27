#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_assertion_handler.hpp"

#include "catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch;

using ::testing::MockFunction;



class MockIResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, notifyAssertionStarted, (const AssertionInfo & info), (override));

    MOCK_METHOD(bool, sectionStarted, (StringRef sectionName, const SourceLineInfo & sectionLineInfo, Counts & assertions), (override));

    MOCK_METHOD(void, sectionEnded, (SectionEndInfo && endInfo), (override));

    MOCK_METHOD(void, sectionEndedEarly, (SectionEndInfo && endInfo), (override));

    MOCK_METHOD(IGeneratorTracker *, acquireGeneratorTracker, (StringRef generatorName, const SourceLineInfo & lineInfo), (override));

    MOCK_METHOD(IGeneratorTracker *, createGeneratorTracker, (StringRef generatorName, SourceLineInfo lineInfo, Generators::GeneratorBasePtr && generator), (override));

    MOCK_METHOD(void, benchmarkPreparing, (StringRef name), (override));

    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo & info), (override));

    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<> & stats), (override));

    MOCK_METHOD(void, benchmarkFailed, (StringRef error), (override));

    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo & message), (override));

    MOCK_METHOD(void, popScopedMessage, (const MessageInfo & message), (override));

    MOCK_METHOD(void, emplaceUnscopedMessage, (MessageBuilder && builder), (override));

    MOCK_METHOD(void, handleFatalErrorCondition, (StringRef message), (override));

    MOCK_METHOD(void, handleExpr, (const AssertionInfo & info, const ITransientExpression & expr, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, handleMessage, (const AssertionInfo & info, struct ResultWas::OfType resultType, std::string && message, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo & info, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo & info, std::string && message, AssertionReaction & reaction), (override));

    MOCK_METHOD(void, handleIncomplete, (const AssertionInfo & info), (override));

    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo & info, struct ResultWas::OfType resultType, AssertionReaction & reaction), (override));

    MOCK_METHOD(bool, lastAssertionPassed, (), (override));

    MOCK_METHOD(void, assertionPassed, (), (override));

    MOCK_METHOD(const std::string &, getCurrentTestName, (), (const, override));

    MOCK_METHOD(const AssertionResult *, getLastResult, (), (const, override));

    MOCK_METHOD(void, exceptionEarlyReported, (), (override));

};



class AssertionHandlerTest_131 : public ::testing::Test {

protected:

    MockIResultCapture mock_result_capture;

    SourceLineInfo line_info{"file.cpp", 42};

    AssertionInfo assertion_info{"MACRO_NAME", line_info, "capturedExpression", ResultDisposition::Flags::None()};

};



TEST_F(AssertionHandlerTest_131, ConstructorAndDestructorIncomplete_131) {

    EXPECT_CALL(mock_result_capture, handleIncomplete(::testing::_)).Times(1);

    {

        AssertionHandler handler("MACRO_NAME", line_info, "capturedExpression", ResultDisposition::Flags::None());

    }

}



TEST_F(AssertionHandlerTest_131, CompleteSetsCompletedToTrue_131) {

    AssertionHandler handler("MACRO_NAME", line_info, "capturedExpression", ResultDisposition::Flags::None());

    EXPECT_CALL(mock_result_capture, handleIncomplete(::testing::_)).Times(0);

    handler.complete();

}



TEST_F(AssertionHandlerTest_131, HandleExprCallsHandleExprOnMock_131) {

    AssertionHandler handler("MACRO_NAME", line_info, "capturedExpression", ResultDisposition::Flags::None());

    MockFunction<void(const AssertionInfo &, const ITransientExpression &, AssertionReaction &)> mock_expr_handler;

    EXPECT_CALL(mock_result_capture, handleExpr(::testing::_, ::testing::_, ::testing::_)).Times(1);

    handler.handleExpr(ITransientExpression{});

}



TEST_F(AssertionHandlerTest_131, HandleMessageCallsHandleMessageOnMock_131) {

    AssertionHandler handler("MACRO_NAME", line_info, "capturedExpression", ResultDisposition::Flags::None());

    EXPECT_CALL(mock_result_capture, handleMessage(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);

    handler.handleMessage(ResultWas::OfType{}, "message");

}



TEST_F(AssertionHandlerTest_131, HandleExceptionThrownAsExpectedDoesNotCrash_131) {

    AssertionHandler handler("MACRO_NAME", line_info, "capturedExpression", ResultDisposition::Flags::None());

    handler.handleExceptionThrownAsExpected();

}



TEST_F(AssertionHandlerTest_131, HandleUnexpectedExceptionNotThrownCallsHandleUnexpectedExceptionNotThrownOnMock_131) {

    AssertionHandler handler("MACRO_NAME", line_info, "capturedExpression", ResultDisposition::Flags::None());

    EXPECT_CALL(mock_result_capture, handleUnexpectedExceptionNotThrown(::testing::_, ::testing::_)).Times(1);

    handler.handleUnexpectedExceptionNotThrown();

}



TEST_F(AssertionHandlerTest_131, HandleExceptionNotThrownAsExpectedDoesNotCrash_131) {

    AssertionHandler handler("MACRO_NAME", line_info, "capturedExpression", ResultDisposition::Flags::None());

    handler.handleExceptionNotThrownAsExpected();

}



TEST_F(AssertionHandlerTest_131, HandleThrowingCallSkippedDoesNotCrash_131) {

    AssertionHandler handler("MACRO_NAME", line_info, "capturedExpression", ResultDisposition::Flags::None());

    handler.handleThrowingCallSkipped();

}



TEST_F(AssertionHandlerTest_131, HandleUnexpectedInflightExceptionCallsHandleUnexpectedInflightExceptionOnMock_131) {

    AssertionHandler handler("MACRO_NAME", line_info, "capturedExpression", ResultDisposition::Flags::None());

    EXPECT_CALL(mock_result_capture, handleUnexpectedInflightException(::testing::_, ::testing::_)).Times(1);

    handler.handleUnexpectedInflightException();

}



TEST_F(AssertionHandlerTest_131, AllowThrowsReturnsFalseByDefault_131) {

    AssertionHandler handler("MACRO_NAME", line_info, "capturedExpression", ResultDisposition::Flags::None());

    EXPECT_FALSE(handler.allowThrows());

}
