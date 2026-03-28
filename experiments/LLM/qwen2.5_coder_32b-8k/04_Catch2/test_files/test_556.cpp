#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_assertion_handler.hpp"

#include "catch2/interfaces/catch_interfaces_capture.hpp"

#include "catch2/internal/catch_result_type.hpp"



using namespace Catch;



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

    MOCK_METHOD(void, handleMessage, (const AssertionInfo& info, struct ResultWas::OfType resultType, std::string&& message, AssertionReaction& reaction), (override));

    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo& info, AssertionReaction& reaction), (override));

    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo& info, std::string&& message, AssertionReaction& reaction), (override));

    MOCK_METHOD(void, handleIncomplete, (const AssertionInfo& info), (override));

    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo& info, struct ResultWas::OfType resultType, AssertionReaction& reaction), (override));

    MOCK_METHOD(bool, lastAssertionPassed, (), (override));

    MOCK_METHOD(void, assertionPassed, (), (override));

    MOCK_METHOD(const std::string&, getCurrentTestName, (), (override));

    MOCK_METHOD(const const AssertionResult*, getLastResult, (), (override));

    MOCK_METHOD(void, exceptionEarlyReported, (), (override));

};



class AssertionHandlerTest : public ::testing::Test {

protected:

    MockResultCapture mockResultCapture;

    SourceLineInfo lineInfo{"filename.cpp", 42};

    StringRef macroName = "CATCH_CHECK";

    StringRef capturedExpression = "a == b";

    ResultDisposition::Flags resultDisposition = ResultDisposition::Normal;



    AssertionHandler handler{macroName, lineInfo, capturedExpression, resultDisposition};



    AssertionInfo assertionInfo{macroName, lineInfo, capturedExpression};

    AssertionReaction reaction;

};



TEST_F(AssertionHandlerTest_556, HandleExceptionThrownAsExpected_NormalOperation_556) {

    EXPECT_CALL(mockResultCapture, handleNonExpr(assertionInfo, ResultWas::Ok, testing::_));



    handler.handleExceptionThrownAsExpected();

}



// Boundary condition tests

TEST_F(AssertionHandlerTest_556, HandleExceptionThrownAsExpected_NoAssertions_556) {

    EXPECT_CALL(mockResultCapture, handleNonExpr(assertionInfo, ResultWas::Ok, testing::_))

        .Times(1);



    handler.handleExceptionThrownAsExpected();

}



// Exceptional or error cases

TEST_F(AssertionHandlerTest_556, HandleUnexpectedInflightException_ExceptionHandling_556) {

    std::string message = "An unexpected exception occurred";

    EXPECT_CALL(mockResultCapture, handleUnexpectedInflightException(assertionInfo, testing::Eq(message), testing::_));



    handler.handleUnexpectedInflightException();

}



// Verification of external interactions

TEST_F(AssertionHandlerTest_556, HandleExpr_VerifyExternalInteraction_556) {

    MockTransientExpression mockExpr;

    EXPECT_CALL(mockResultCapture, handleExpr(assertionInfo, testing::Ref(mockExpr), testing::_));



    handler.handleExpr(mockExpr);

}



class MockTransientExpression : public ITransientExpression {

public:

    MOCK_METHOD(bool, evaluate, (), (const override));

    MOCK_METHOD(std::string, getOp, (), (const override));

    MOCK_METHOD(std::string, lhsAsStr, (), (const override));

    MOCK_METHOD(std::string, rhsAsStr, (), (const override));

};



TEST_F(AssertionHandlerTest_556, HandleMessage_VerifyExternalInteraction_556) {

    std::string message = "Custom message";

    EXPECT_CALL(mockResultCapture, handleMessage(assertionInfo, ResultWas::Warning, testing::Eq(message), testing::_));



    handler.handleMessage(ResultWas::Warning, std::move(message));

}
