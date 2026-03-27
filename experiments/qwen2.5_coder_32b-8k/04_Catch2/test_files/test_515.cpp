#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_run_context.hpp"

#include "catch_assertion_info.hpp"

#include "catch_decomposer.hpp"

#include "catch_assertion_handler.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::MockFunction;



class MockITransientExpression : public ITransientExpression {

public:

    MOCK_CONST_METHOD0(getResult, bool());

};



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD4(reportAssertion, void(AssertionInfo const&, ResultWas::OfType, ITransientExpression const*, bool));

    MOCK_METHOD1(debugBreak, void(bool shouldDebugBreak));

    MOCK_METHOD1(throwException, void(bool shouldThrow));

    MOCK_METHOD1(skipTest, void(bool shouldSkip));

};



class RunContextTest : public ::testing::Test {

protected:

    MockIEventListener mockReporter;

    std::unique_ptr<RunContext> runContext;



    AssertionInfo assertionInfo;

    MockITransientExpression transientExpr;

    AssertionReaction reaction;



    virtual void SetUp() override {

        runContext = std::make_unique<RunContext>(nullptr, IEventListenerPtr(&mockReporter));

        reaction = {};

    }

};



TEST_F(RunContextTest_515, HandleExpr_SuccessfulAssertionNotIncluded_515) {

    EXPECT_CALL(mockReporter, reportAssertion(_, _, _, _)).Times(0);

    EXPECT_CALL(mockReporter, debugBreak(_)).Times(0);

    EXPECT_CALL(mockReporter, throwException(_)).Times(0);



    transientExpr.getResult().WillOnce(::testing::Return(true));

    runContext->m_includeSuccessfulResults = false;



    runContext->handleExpr(assertionInfo, transientExpr, reaction);

}



TEST_F(RunContextTest_515, HandleExpr_SuccessfulAssertionIncluded_515) {

    EXPECT_CALL(mockReporter, reportAssertion(_, ResultWas::Ok, &transientExpr, false));



    transientExpr.getResult().WillOnce(::testing::Return(true));

    runContext->m_includeSuccessfulResults = true;



    runContext->handleExpr(assertionInfo, transientExpr, reaction);

}



TEST_F(RunContextTest_515, HandleExpr_FailedAssertion_NegatedFalse_515) {

    EXPECT_CALL(mockReporter, reportAssertion(_, ResultWas::ExpressionFailed, &transientExpr, false));



    transientExpr.getResult().WillOnce(::testing::Return(false));

    runContext->m_includeSuccessfulResults = true;



    runContext->handleExpr(assertionInfo, transientExpr, reaction);

}



TEST_F(RunContextTest_515, HandleExpr_FailedAssertion_NegatedTrue_515) {

    EXPECT_CALL(mockReporter, reportAssertion(_, ResultWas::ExpressionFailed, &transientExpr, true));



    assertionInfo.resultDisposition = ResultDisposition::Flags::NegateResult;

    transientExpr.getResult().WillOnce(::testing::Return(true));

    runContext->m_includeSuccessfulResults = true;



    runContext->handleExpr(assertionInfo, transientExpr, reaction);

}



TEST_F(RunContextTest_515, HandleExpr_PopulateReactionForFailure_515) {

    EXPECT_CALL(mockReporter, reportAssertion(_, ResultWas::ExpressionFailed, &transientExpr, false));



    MockFunction<void(AssertionReaction&)> populateReactionMock;

    auto originalPopulateReaction = runContext->populateReaction;

    runContext->populateReaction = [&](AssertionReaction& reaction) { 

        populateReactionMock.Call(reaction);

        originalPopulateReaction(reaction);

    };



    transientExpr.getResult().WillOnce(::testing::Return(false));

    runContext->m_includeSuccessfulResults = true;



    EXPECT_CALL(populateReactionMock, Call(_)).Times(1);



    runContext->handleExpr(assertionInfo, transientExpr, reaction);

}



TEST_F(RunContextTest_515, HandleExpr_ResetAssertionInfo_AfterHandling_515) {

    MockFunction<void()> resetAssertionInfoMock;

    auto originalResetAssertionInfo = runContext->resetAssertionInfo;

    runContext->resetAssertionInfo = [&]() { 

        resetAssertionInfoMock.Call();

        originalResetAssertionInfo(); 

    };



    transientExpr.getResult().WillOnce(::testing::Return(false));

    runContext->m_includeSuccessfulResults = true;



    EXPECT_CALL(resetAssertionInfoMock, Call()).Times(1);



    runContext->handleExpr(assertionInfo, transientExpr, reaction);

}
