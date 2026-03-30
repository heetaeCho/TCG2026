#include <gtest/gtest.h>

#include "catch_clara.hpp"



using namespace Catch::Clara::Detail;



class BasicResultTest_1066 : public ::testing::Test {

protected:

    BasicResult<int> okResult;

    BasicResult<int> logicErrorResult;

    BasicResult<int> runtimeErrorResult;



    BasicResultTest_1066()

        : okResult(BasicResult<int>::ok(42)),

          logicErrorResult(BasicResult<int>::logicError("Logic error occurred")),

          runtimeErrorResult(BasicResult<int>::runtimeError("Runtime error occurred")) {}

};



TEST_F(BasicResultTest_1066, OkConstructorSetsTypeAndValue_1066) {

    EXPECT_TRUE(okResult);

    EXPECT_EQ(okResult.type(), ResultType::Ok);

}



TEST_F(BasicResultTest_1066, LogicErrorConstructorSetsTypeAndMessage_1066) {

    EXPECT_FALSE(logicErrorResult);

    EXPECT_EQ(logicErrorResult.type(), ResultType::LogicError);

    EXPECT_EQ(logicErrorResult.errorMessage(), "Logic error occurred");

}



TEST_F(BasicResultTest_1066, RuntimeErrorConstructorSetsTypeAndMessage_1066) {

    EXPECT_FALSE(runtimeErrorResult);

    EXPECT_EQ(runtimeErrorResult.type(), ResultType::RuntimeError);

    EXPECT_EQ(runtimeErrorResult.errorMessage(), "Runtime error occurred");

}



TEST_F(BasicResultTest_1066, CopyConstructorTransfersState_1066) {

    BasicResult<int> copyOk(okResult);

    BasicResult<int> copyLogic(logicErrorResult);

    BasicResult<int> copyRuntime(runtimeErrorResult);



    EXPECT_TRUE(copyOk);

    EXPECT_EQ(copyOk.type(), ResultType::Ok);



    EXPECT_FALSE(copyLogic);

    EXPECT_EQ(copyLogic.type(), ResultType::LogicError);

    EXPECT_EQ(copyLogic.errorMessage(), "Logic error occurred");



    EXPECT_FALSE(copyRuntime);

    EXPECT_EQ(copyRuntime.type(), ResultType::RuntimeError);

    EXPECT_EQ(copyRuntime.errorMessage(), "Runtime error occurred");

}



TEST_F(BasicResultTest_1066, OkStaticMethodCreatesOkResult_1066) {

    auto ok = BasicResult<int>::ok();

    EXPECT_TRUE(ok);

    EXPECT_EQ(ok.type(), ResultType::Ok);

}



TEST_F(BasicResultTest_1066, LogicErrorStaticMethodCreatesLogicErrorResult_1066) {

    auto logicError = BasicResult<int>::logicError("Another logic error");

    EXPECT_FALSE(logicError);

    EXPECT_EQ(logicError.type(), ResultType::LogicError);

    EXPECT_EQ(logicError.errorMessage(), "Another logic error");

}



TEST_F(BasicResultTest_1066, RuntimeErrorStaticMethodCreatesRuntimeErrorResult_1066) {

    auto runtimeError = BasicResult<int>::runtimeError("Another runtime error");

    EXPECT_FALSE(runtimeError);

    EXPECT_EQ(runtimeError.type(), ResultType::RuntimeError);

    EXPECT_EQ(runtimeError.errorMessage(), "Another runtime error");

}
