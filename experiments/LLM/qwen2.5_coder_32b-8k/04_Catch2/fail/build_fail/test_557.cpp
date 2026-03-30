#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_assertion_handler.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Ref;



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

    AssertionInfo assertionInfo{"macro", SourceLineInfo{"file.cpp", 10}, "expression"};

    AssertionReaction reaction{AssertionReaction::Normal};

    AssertionHandler handler{"macro", SourceLineInfo{"file.cpp", 10}, "expression", ResultDisposition::None()};

};



TEST_F(AssertionHandlerTest, HandleExceptionNotThrownAsExpected_CallsHandleNonExprWithOk_557) {

    EXPECT_CALL(mockResultCapture, handleNonExpr(Ref(assertionInfo), ResultWas::Ok, Ref(reaction)));

    handler.handleExceptionNotThrownAsExpected();

}



TEST_F(AssertionHandlerTest, HandleUnexpectedInflightException_DoesNothing_557) {

    EXPECT_CALL(mockResultCapture, handleUnexpectedInflightException(_, _, _)).Times(0);

    handler.handleUnexpectedInflightException();

}



TEST_F(AssertionHandlerTest, HandleThrowingCallSkipped_DoesNothing_557) {

    EXPECT_CALL(mockResultCapture, handleExpr(_, _, _)).Times(0);

    handler.handleThrowingCallSkipped();

}
