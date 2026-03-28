#include <gtest/gtest.h>

#include "catch_clara.hpp"



using namespace Catch::Clara::Detail;



class BasicResultTest_371 : public ::testing::Test {

protected:

    BasicResult<int> okResult;

    BasicResult<int> logicErrorResult;

    BasicResult<int> runtimeErrorResult;



    BasicResultTest_371()

        : okResult(BasicResult<int>::ok(42)),

          logicErrorResult(BasicResult<int>::logicError("Logic Error")),

          runtimeErrorResult(BasicResult<int>::runtimeError("Runtime Error")) {}

};



TEST_F(BasicResultTest_371, OkType_ReturnsTrue_371) {

    EXPECT_TRUE(static_cast<bool>(okResult));

}



TEST_F(BasicResultTest_371, LogicErrorType_ReturnsFalse_371) {

    EXPECT_FALSE(static_cast<bool>(logicErrorResult));

}



TEST_F(BasicResultTest_371, RuntimeErrorType_ReturnsFalse_371) {

    EXPECT_FALSE(static_cast<bool>(runtimeErrorResult));

}



TEST_F(BasicResultTest_371, OkResult_TypeIsOk_371) {

    EXPECT_EQ(okResult.type(), ResultType::Ok);

}



TEST_F(BasicResultTest_371, LogicErrorResult_TypeIsLogicError_371) {

    EXPECT_EQ(logicErrorResult.type(), ResultType::LogicError);

}



TEST_F(BasicResultTest_371, RuntimeErrorResult_TypeIsRuntimeError_371) {

    EXPECT_EQ(runtimeErrorResult.type(), ResultType::RuntimeError);

}



TEST_F(BasicResultTest_371, OkResult_HasNoErrorMessage_371) {

    EXPECT_TRUE(okResult.errorMessage().empty());

}



TEST_F(BasicResultTest_371, LogicErrorResult_HasCorrectErrorMessage_371) {

    EXPECT_EQ(logicErrorResult.errorMessage(), "Logic Error");

}



TEST_F(BasicResultTest_371, RuntimeErrorResult_HasCorrectErrorMessage_371) {

    EXPECT_EQ(runtimeErrorResult.errorMessage(), "Runtime Error");

}



TEST_F(BasicResultTest_371, EnforceOk_OnOk_DoesNotAbort_371) {

    // This test assumes that the program does not abort if enforceOk is called on an Ok result.

    okResult.enforceOk();

}



TEST_F(BasicResultTest_371, EnforceOk_OnLogicError_Aborts_371) {

    EXPECT_DEATH(logicErrorResult.enforceOk(), "");

}



TEST_F(BasicResultTest_371, EnforceOk_OnRuntimeError_Aborts_371) {

    EXPECT_DEATH(runtimeErrorResult.enforceOk(), "");

}
