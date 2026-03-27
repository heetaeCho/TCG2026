#include <gtest/gtest.h>

#include "catch_clara.hpp"



using namespace Catch::Clara::Detail;



class BasicResultTest_367 : public ::testing::Test {

protected:

    BasicResult<int> okResult;

    BasicResult<int> logicErrorResult;

    BasicResult<int> runtimeErrorResult;



    BasicResultTest_367() 

        : okResult(BasicResult<int>::ok(42)),

          logicErrorResult(BasicResult<int>::logicError("Logic error message")),

          runtimeErrorResult(BasicResult<int>::runtimeError("Runtime error message")) {}

};



TEST_F(BasicResultTest_367, OkResultIsTrue_367) {

    EXPECT_TRUE(static_cast<bool>(okResult));

}



TEST_F(BasicResultTest_367, LogicErrorResultIsFalse_367) {

    EXPECT_FALSE(static_cast<bool>(logicErrorResult));

}



TEST_F(BasicResultTest_367, RuntimeErrorResultIsFalse_367) {

    EXPECT_FALSE(static_cast<bool>(runtimeErrorResult));

}



TEST_F(BasicResultTest_367, OkResultTypeIsOk_367) {

    EXPECT_EQ(okResult.type(), ResultType::Ok);

}



TEST_F(BasicResultTest_367, LogicErrorResultTypeIsLogicError_367) {

    EXPECT_EQ(logicErrorResult.type(), ResultType::LogicError);

}



TEST_F(BasicResultTest_367, RuntimeErrorResultTypeIsRuntimeError_367) {

    EXPECT_EQ(runtimeErrorResult.type(), ResultType::RuntimeError);

}



TEST_F(BasicResultTest_367, OkResultErrorMessageIsEmpty_367) {

    EXPECT_TRUE(okResult.errorMessage().empty());

}



TEST_F(BasicResultTest_367, LogicErrorResultErrorMessageIsCorrect_367) {

    EXPECT_EQ(logicErrorResult.errorMessage(), "Logic error message");

}



TEST_F(BasicResultTest_367, RuntimeErrorResultErrorMessageIsCorrect_367) {

    EXPECT_EQ(runtimeErrorResult.errorMessage(), "Runtime error message");

}
