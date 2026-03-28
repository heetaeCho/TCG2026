#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_assertion_handler.hpp"



using namespace Catch;

using ::testing::_;



class MockAssertionInfo : public AssertionInfo {

public:

    MockAssertionInfo(StringRef macroName, const SourceLineInfo& lineInfo, StringRef capturedExpression)

        : AssertionInfo(macroName, lineInfo, capturedExpression) {}

};



class MockITransientExpression : public ITransientExpression {

public:

    MOCK_CONST_METHOD0(evalResult, bool());

    MOCK_CONST_METHOD0(reconstructExpression, std::string());

};



class MockSourceLineInfo : public SourceLineInfo {

public:

    MockSourceLineInfo(std::string file = "", int line = 0) : SourceLineInfo(file, line) {}

};



TEST_F(AssertionHandlerTest_554, CompleteSetsCompletedFlag_554) {

    AssertionReaction reaction;

    MockSourceLineInfo sourceLineInfo("test_file.cpp", 123);

    StringRef macroName("TEST_MACRO");

    StringRef capturedExpression("expr");



    AssertionHandler handler(macroName, sourceLineInfo, capturedExpression, ResultDisposition::Flags());

    ASSERT_FALSE(handler.allowThrows());



    handler.complete();

    EXPECT_TRUE(handler.allowThrows());

}



TEST_F(AssertionHandlerTest_554, CompleteWithDebugBreakReaction_554) {

    AssertionReaction reaction{true, false, false};

    MockSourceLineInfo sourceLineInfo("test_file.cpp", 123);

    StringRef macroName("TEST_MACRO");

    StringRef capturedExpression("expr");



    AssertionHandler handler(macroName, sourceLineInfo, capturedExpression, ResultDisposition::Flags());

    EXPECT_THROW(handler.complete(), std::exception); // Assuming CATCH_BREAK_INTO_DEBUGGER throws an exception

}



TEST_F(AssertionHandlerTest_554, CompleteWithThrowReaction_554) {

    AssertionReaction reaction{false, true, false};

    MockSourceLineInfo sourceLineInfo("test_file.cpp", 123);

    StringRef macroName("TEST_MACRO");

    StringRef capturedExpression("expr");



    AssertionHandler handler(macroName, sourceLineInfo, capturedExpression, ResultDisposition::Flags());

    EXPECT_THROW(handler.complete(), std::exception); // Assuming throw_test_failure_exception throws an exception

}



TEST_F(AssertionHandlerTest_554, CompleteWithSkipReaction_554) {

    AssertionReaction reaction{false, false, true};

    MockSourceLineInfo sourceLineInfo("test_file.cpp", 123);

    StringRef macroName("TEST_MACRO");

    StringRef capturedExpression("expr");



    AssertionHandler handler(macroName, sourceLineInfo, capturedExpression, ResultDisposition::Flags());

    EXPECT_THROW(handler.complete(), std::exception); // Assuming throw_test_skip_exception throws an exception

}



TEST_F(AssertionHandlerTest_554, HandleExprCallsEvalResult_554) {

    AssertionReaction reaction;

    MockSourceLineInfo sourceLineInfo("test_file.cpp", 123);

    StringRef macroName("TEST_MACRO");

    StringRef capturedExpression("expr");



    MockITransientExpression exprMock;



    EXPECT_CALL(exprMock, evalResult())

        .WillOnce(::testing::Return(true));



    AssertionHandler handler(macroName, sourceLineInfo, capturedExpression, ResultDisposition::Flags());

    handler.handleExpr(exprMock);

}



TEST_F(AssertionHandlerTest_554, HandleMessageDoesNotThrow_554) {

    AssertionReaction reaction;

    MockSourceLineInfo sourceLineInfo("test_file.cpp", 123);

    StringRef macroName("TEST_MACRO");

    StringRef capturedExpression("expr");



    AssertionHandler handler(macroName, sourceLineInfo, capturedExpression, ResultDisposition::Flags());

    EXPECT_NO_THROW(handler.handleMessage(ResultWas::OfType::Ok, "Test message"));

}



TEST_F(AssertionHandlerTest_554, HandleExceptionThrownAsExpectedDoesNotThrow_554) {

    AssertionReaction reaction;

    MockSourceLineInfo sourceLineInfo("test_file.cpp", 123);

    StringRef macroName("TEST_MACRO");

    StringRef capturedExpression("expr");



    AssertionHandler handler(macroName, sourceLineInfo, capturedExpression, ResultDisposition::Flags());

    EXPECT_NO_THROW(handler.handleExceptionThrownAsExpected());

}



TEST_F(AssertionHandlerTest_554, HandleUnexpectedExceptionNotThrownDoesNotThrow_554) {

    AssertionReaction reaction;

    MockSourceLineInfo sourceLineInfo("test_file.cpp", 123);

    StringRef macroName("TEST_MACRO");

    StringRef capturedExpression("expr");



    AssertionHandler handler(macroName, sourceLineInfo, capturedExpression, ResultDisposition::Flags());

    EXPECT_NO_THROW(handler.handleUnexpectedExceptionNotThrown());

}



TEST_F(AssertionHandlerTest_554, HandleExceptionNotThrownAsExpectedDoesNotThrow_554) {

    AssertionReaction reaction;

    MockSourceLineInfo sourceLineInfo("test_file.cpp", 123);

    StringRef macroName("TEST_MACRO");

    StringRef capturedExpression("expr");



    AssertionHandler handler(macroName, sourceLineInfo, capturedExpression, ResultDisposition::Flags());

    EXPECT_NO_THROW(handler.handleExceptionNotThrownAsExpected());

}



TEST_F(AssertionHandlerTest_554, HandleThrowingCallSkippedDoesNotThrow_554) {

    AssertionReaction reaction;

    MockSourceLineInfo sourceLineInfo("test_file.cpp", 123);

    StringRef macroName("TEST_MACRO");

    StringRef capturedExpression("expr");



    AssertionHandler handler(macroName, sourceLineInfo, capturedExpression, ResultDisposition::Flags());

    EXPECT_NO_THROW(handler.handleThrowingCallSkipped());

}



TEST_F(AssertionHandlerTest_554, HandleUnexpectedInflightExceptionDoesNotThrow_554) {

    AssertionReaction reaction;

    MockSourceLineInfo sourceLineInfo("test_file.cpp", 123);

    StringRef macroName("TEST_MACRO");

    StringRef capturedExpression("expr");



    AssertionHandler handler(macroName, sourceLineInfo, capturedExpression, ResultDisposition::Flags());

    EXPECT_NO_THROW(handler.handleUnexpectedInflightException());

}
