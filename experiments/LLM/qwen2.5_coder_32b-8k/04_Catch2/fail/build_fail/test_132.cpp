#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_assertion_handler.hpp"



using namespace Catch;



// Mock class for ITransientExpression

class MockITransientExpression : public ITransientExpression {

public:

    MOCK_CONST_METHOD0(eval, bool());

};



// Mock class for SourceLineInfo

class MockSourceLineInfo : public SourceLineInfo {

public:

    MockSourceLineInfo(const std::string& file = "", int line = 0)

        : SourceLineInfo(file, line) {}

};



TEST_F(AssertionHandlerTest_132, HandleExpr_SuccessfulExpression_132) {

    MockITransientExpression mockExpr;

    EXPECT_CALL(mockExpr, eval()).WillOnce(::testing::Return(true));



    AssertionHandler handler("CHECK", MockSourceLineInfo(__FILE__, __LINE__), "true", ResultDisposition::None());

    handler.handleExpr(mockExpr);

}



TEST_F(AssertionHandlerTest_132, HandleExpr_UnsuccessfulExpression_132) {

    MockITransientExpression mockExpr;

    EXPECT_CALL(mockExpr, eval()).WillOnce(::testing::Return(false));



    AssertionHandler handler("CHECK", MockSourceLineInfo(__FILE__, __LINE__), "false", ResultDisposition::None());

    handler.handleExpr(mockExpr);

}



TEST_F(AssertionHandlerTest_132, HandleMessage_WithEmptyMessage_132) {

    AssertionHandler handler("CHECK", MockSourceLineInfo(__FILE__, __LINE__), "true", ResultDisposition::None());

    EXPECT_NO_THROW(handler.handleMessage(ResultWas::Ok, ""));

}



TEST_F(AssertionHandlerTest_132, HandleMessage_WithNonEmptyMessage_132) {

    AssertionHandler handler("CHECK", MockSourceLineInfo(__FILE__, __LINE__), "true", ResultDisposition::None());

    EXPECT_NO_THROW(handler.handleMessage(ResultWas::Ok, "This is a test message"));

}



TEST_F(AssertionHandlerTest_132, HandleExceptionThrownAsExpected_CalledOnce_132) {

    AssertionHandler handler("CHECK_THROWS", MockSourceLineInfo(__FILE__, __LINE__), "throw std::runtime_error()", ResultDisposition::None());

    EXPECT_NO_THROW(handler.handleExceptionThrownAsExpected());

}



TEST_F(AssertionHandlerTest_132, HandleUnexpectedExceptionNotThrown_CalledOnce_132) {

    AssertionHandler handler("CHECK_THROWS", MockSourceLineInfo(__FILE__, __LINE__), "no_throw()", ResultDisposition::None());

    EXPECT_NO_THROW(handler.handleUnexpectedExceptionNotThrown());

}



TEST_F(AssertionHandlerTest_132, HandleExceptionNotThrownAsExpected_CalledOnce_132) {

    AssertionHandler handler("CHECK_NOTHROW", MockSourceLineInfo(__FILE__, __LINE__), "throw std::runtime_error()", ResultDisposition::None());

    EXPECT_NO_THROW(handler.handleExceptionNotThrownAsExpected());

}



TEST_F(AssertionHandlerTest_132, HandleUnexpectedInflightException_CalledOnce_132) {

    AssertionHandler handler("CHECK", MockSourceLineInfo(__FILE__, __LINE__), "true", ResultDisposition::None());

    EXPECT_NO_THROW(handler.handleUnexpectedInflightException());

}



TEST_F(AssertionHandlerTest_132, Complete_CallTwice_132) {

    AssertionHandler handler("CHECK", MockSourceLineInfo(__FILE__, __LINE__), "true", ResultDisposition::None());

    handler.complete();

    handler.complete(); // Should not throw

}



TEST_F(AssertionHandlerTest_132, AllowThrows_DefaultValue_132) {

    AssertionHandler handler("CHECK_THROWS", MockSourceLineInfo(__FILE__, __LINE__), "throw std::runtime_error()", ResultDisposition::None());

    EXPECT_TRUE(handler.allowThrows());

}
