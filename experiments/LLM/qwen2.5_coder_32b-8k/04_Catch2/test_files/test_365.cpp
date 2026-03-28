#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_clara.hpp"



using namespace Catch::Clara::Detail;



class BasicResultTest_365 : public ::testing::Test {};



TEST_F(BasicResultTest_365, OkConstructor_ReturnsTrue_365) {

    BasicResult<void> result = BasicResult<void>::ok();

    EXPECT_TRUE(static_cast<bool>(result));

}



TEST_F(BasicResultTest_365, LogicErrorConstructor_ReturnsFalse_365) {

    BasicResult<void> result = BasicResult<void>::logicError("Logic error message");

    EXPECT_FALSE(static_cast<bool>(result));

}



TEST_F(BasicResultTest_365, RuntimeErrorConstructor_ReturnsFalse_365) {

    BasicResult<void> result = BasicResult<void>::runtimeError("Runtime error message");

    EXPECT_FALSE(static_cast<bool>(result));

}



TEST_F(BasicResultTest_365, OkType_ReturnsOk_365) {

    BasicResult<void> result = BasicResult<void>::ok();

    EXPECT_EQ(result.type(), ResultType::Ok);

}



TEST_F(BasicResultTest_365, LogicErrorType_ReturnsLogicError_365) {

    BasicResult<void> result = BasicResult<void>::logicError("Logic error message");

    EXPECT_EQ(result.type(), ResultType::LogicError);

}



TEST_F(BasicResultTest_365, RuntimeErrorType_ReturnsRuntimeError_365) {

    BasicResult<void> result = BasicResult<void>::runtimeError("Runtime error message");

    EXPECT_EQ(result.type(), ResultType::RuntimeError);

}



TEST_F(BasicResultTest_365, OkErrorMessage_ReturnsEmptyString_365) {

    BasicResult<void> result = BasicResult<void>::ok();

    EXPECT_TRUE(result.errorMessage().empty());

}



TEST_F(BasicResultTest_365, LogicErrorMessage_ReturnsCorrectMessage_365) {

    std::string message = "Logic error message";

    BasicResult<void> result = BasicResult<void>::logicError(message);

    EXPECT_EQ(result.errorMessage(), message);

}



TEST_F(BasicResultTest_365, RuntimeErrorErrorMessage_ReturnsCorrectMessage_365) {

    std::string message = "Runtime error message";

    BasicResult<void> result = BasicResult<void>::runtimeError(message);

    EXPECT_EQ(result.errorMessage(), message);

}
