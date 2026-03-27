#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_assertion_handler.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class MockAssertionHandler : public AssertionHandler {

public:

    MOCK_METHOD(void, handleExpr, (const ITransientExpression & expr), (override));

    MOCK_METHOD(void, handleMessage, (struct ResultWas::OfType resultType, std::string&& message), (override));

    MOCK_METHOD(void, handleExceptionThrownAsExpected, (), (override));

    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (), (override));

    MOCK_METHOD(void, handleExceptionNotThrownAsExpected, (), (override));

    MOCK_METHOD(void, handleThrowingCallSkipped, (), (override));

    MOCK_METHOD(void, handleUnexpectedInflightException, (), (override));

    MOCK_METHOD(bool, allowThrows, (), (const, override));

    MOCK_METHOD(void, complete, (), (override));



    MockAssertionHandler(StringRef macroName, const SourceLineInfo & lineInfo, StringRef capturedExpression, struct ResultDisposition::Flags resultDisposition)

        : AssertionHandler(macroName, lineInfo, capturedExpression, resultDisposition) {}

};



TEST_F(MockAssertionHandlerTest_560, HandleExpr_CallsHandleExpr_560) {

    MockAssertionHandler handler("macro", SourceLineInfo(), "expr", ResultDisposition::Normal);

    EXPECT_CALL(handler, handleExpr(_));

    handler.handleExpr(ITransientExpression{});

}



TEST_F(MockAssertionHandlerTest_560, HandleMessage_CallsHandleMessage_560) {

    MockAssertionHandler handler("macro", SourceLineInfo(), "expr", ResultDisposition::Normal);

    EXPECT_CALL(handler, handleMessage(ResultWas::OfType{}, _));

    handler.handleMessage(ResultWas::OfType{}, "");

}



TEST_F(MockAssertionHandlerTest_560, HandleExceptionThrownAsExpected_CallsHandleExceptionThrownAsExpected_560) {

    MockAssertionHandler handler("macro", SourceLineInfo(), "expr", ResultDisposition::Normal);

    EXPECT_CALL(handler, handleExceptionThrownAsExpected());

    handler.handleExceptionThrownAsExpected();

}



TEST_F(MockAssertionHandlerTest_560, HandleUnexpectedExceptionNotThrown_CallsHandleUnexpectedExceptionNotThrown_560) {

    MockAssertionHandler handler("macro", SourceLineInfo(), "expr", ResultDisposition::Normal);

    EXPECT_CALL(handler, handleUnexpectedExceptionNotThrown());

    handler.handleUnexpectedExceptionNotThrown();

}



TEST_F(MockAssertionHandlerTest_560, HandleExceptionNotThrownAsExpected_CallsHandleExceptionNotThrownAsExpected_560) {

    MockAssertionHandler handler("macro", SourceLineInfo(), "expr", ResultDisposition::Normal);

    EXPECT_CALL(handler, handleExceptionNotThrownAsExpected());

    handler.handleExceptionNotThrownAsExpected();

}



TEST_F(MockAssertionHandlerTest_560, HandleThrowingCallSkipped_CallsHandleThrowingCallSkipped_560) {

    MockAssertionHandler handler("macro", SourceLineInfo(), "expr", ResultDisposition::Normal);

    EXPECT_CALL(handler, handleThrowingCallSkipped());

    handler.handleThrowingCallSkipped();

}



TEST_F(MockAssertionHandlerTest_560, HandleUnexpectedInflightException_CallsHandleUnexpectedInflightException_560) {

    MockAssertionHandler handler("macro", SourceLineInfo(), "expr", ResultDisposition::Normal);

    EXPECT_CALL(handler, handleUnexpectedInflightException());

    handler.handleUnexpectedInflightException();

}



TEST_F(MockAssertionHandlerTest_560, AllowThrows_ReturnsBool_560) {

    MockAssertionHandler handler("macro", SourceLineInfo(), "expr", ResultDisposition::Normal);

    EXPECT_CALL(handler, allowThrows()).WillOnce(InvokeWithoutArgs([]{ return true; }));

    bool result = handler.allowThrows();

    EXPECT_EQ(result, true);

}



TEST_F(MockAssertionHandlerTest_560, Complete_CallsComplete_560) {

    MockAssertionHandler handler("macro", SourceLineInfo(), "expr", ResultDisposition::Normal);

    EXPECT_CALL(handler, complete());

    handler.complete();

}
