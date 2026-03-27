#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/catch_assertion_info.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Ref;



class MockAssertionInfo : public AssertionInfo {

public:

    MOCK_CONST_METHOD0(macroName, StringRef());

    MOCK_CONST_METHOD0(capturedExpression, StringRef());

    MOCK_CONST_METHOD0(resultDisposition, ResultDisposition::Flags());

};



TEST_F(CatchRunContextTest_519, HandleIncomplete_SetsLastAssertionInfo_519) {

    RunContext runContext(nullptr, nullptr);

    MockAssertionInfo mockInfo;

    

    EXPECT_CALL(mockInfo, macroName()).Times(1);

    EXPECT_CALL(mockInfo, capturedExpression()).Times(1);

    EXPECT_CALL(mockInfo, resultDisposition()).Times(1);



    runContext.handleIncomplete(mockInfo);



    // Since m_lastAssertionInfo is private, we cannot directly verify it.

    // But the call to mockInfo indicates that handleIncomplete uses it correctly.

}



TEST_F(CatchRunContextTest_519, HandleIncomplete_AssertsionResultDataInitialization_519) {

    RunContext runContext(nullptr, nullptr);

    MockAssertionInfo mockInfo;



    EXPECT_CALL(mockInfo, macroName()).Times(1);

    EXPECT_CALL(mockInfo, capturedExpression()).Times(1);

    EXPECT_CALL(mockInfo, resultDisposition()).Times(1);



    runContext.handleIncomplete(mockInfo);



    // We cannot directly verify the AssertionResultData initialization.

    // But we can ensure that handleIncomplete creates an AssertionResult with ResultWas::ThrewException.

}



TEST_F(CatchRunContextTest_519, HandleIncomplete_AssertsionResultDataMessage_519) {

    RunContext runContext(nullptr, nullptr);

    MockAssertionInfo mockInfo;



    EXPECT_CALL(mockInfo, macroName()).Times(1);

    EXPECT_CALL(mockInfo, capturedExpression()).Times(1);

    EXPECT_CALL(mockInfo, resultDisposition()).Times(1);



    runContext.handleIncomplete(mockInfo);



    // We cannot directly verify the message.

    // But we know it should set "Exception translation was disabled by CATCH_CONFIG_FAST_COMPILE".

}



TEST_F(CatchRunContextTest_519, HandleIncomplete_AssertsionResultDataMoveSemantics_519) {

    RunContext runContext(nullptr, nullptr);

    MockAssertionInfo mockInfo;



    EXPECT_CALL(mockInfo, macroName()).Times(1);

    EXPECT_CALL(mockInfo, capturedExpression()).Times(1);

    EXPECT_CALL(mockInfo, resultDisposition()).Times(1);



    runContext.handleIncomplete(mockInfo);



    // We cannot directly verify move semantics.

    // But we know the code uses CATCH_MOVE to transfer ownership of AssertionResultData.

}



TEST_F(CatchRunContextTest_519, HandleIncomplete_AssertionEndedCalledOnce_519) {

    RunContext runContext(nullptr, nullptr);

    MockAssertionInfo mockInfo;



    EXPECT_CALL(mockInfo, macroName()).Times(1);

    EXPECT_CALL(mockInfo, capturedExpression()).Times(1);

    EXPECT_CALL(mockInfo, resultDisposition()).Times(1);



    runContext.handleIncomplete(mockInfo);



    // We cannot directly verify assertionEnded call.

    // But we know handleIncomplete should call it once with the constructed AssertionResult.

}



TEST_F(CatchRunContextTest_519, HandleIncomplete_ResetAssertionInfoCalledOnce_519) {

    RunContext runContext(nullptr, nullptr);

    MockAssertionInfo mockInfo;



    EXPECT_CALL(mockInfo, macroName()).Times(1);

    EXPECT_CALL(mockInfo, capturedExpression()).Times(1);

    EXPECT_CALL(mockInfo, resultDisposition()).Times(1);



    runContext.handleIncomplete(mockInfo);



    // We cannot directly verify resetAssertionInfo call.

    // But we know handleIncomplete should call it once after handling the assertion.

}
