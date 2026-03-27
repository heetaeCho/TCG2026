#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "catch_clara.hpp"



using namespace Catch::Clara::Detail;



class BasicResultTest_366 : public ::testing::Test {

protected:

    using Result = BasicResult<void>;

};



TEST_F(BasicResultTest_366, LogicErrorSetsCorrectTypeAndMessage_366) {

    std::string expectedMessage = "Logic error occurred";

    auto result = BasicResult<void>::logicError(std::move(expectedMessage));

    

    EXPECT_EQ(result.type(), ResultType::LogicError);

    EXPECT_EQ(result.errorMessage(), "Logic error occurred");

}



TEST_F(BasicResultTest_366, RuntimeErrorSetsCorrectTypeAndMessage_366) {

    std::string expectedMessage = "Runtime error occurred";

    auto result = BasicResult<void>::runtimeError(std::move(expectedMessage));

    

    EXPECT_EQ(result.type(), ResultType::RuntimeError);

    EXPECT_EQ(result.errorMessage(), "Runtime error occurred");

}



TEST_F(BasicResultTest_366, OkSetsCorrectTypeAndEmptyMessage_366) {

    auto result = BasicResult<void>::ok();

    

    EXPECT_EQ(result.type(), ResultType::Ok);

    EXPECT_EQ(result.errorMessage(), "");

}



TEST_F(BasicResultTest_366, BoolOperatorReturnsTrueForOk_366) {

    auto result = BasicResult<void>::ok();

    

    EXPECT_TRUE(static_cast<bool>(result));

}



TEST_F(BasicResultTest_366, BoolOperatorReturnsFalseForLogicError_366) {

    auto result = BasicResult<void>::logicError("Logic error occurred");

    

    EXPECT_FALSE(static_cast<bool>(result));

}



TEST_F(BasicResultTest_366, BoolOperatorReturnsFalseForRuntimeError_366) {

    auto result = BasicResult<void>::runtimeError("Runtime error occurred");

    

    EXPECT_FALSE(static_cast<bool>(result));

}
