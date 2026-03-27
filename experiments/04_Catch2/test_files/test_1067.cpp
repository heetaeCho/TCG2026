#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



class BasicResultTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if any

    }



    void TearDown() override {

        // Teardown code, if any

    }

};



TEST_F(BasicResultTest_1067, ConstructorWithErrorMessage_1067) {

    BasicResult<int> result(ResultType::LogicError, "Test error message");

    EXPECT_EQ(result.type(), ResultType::LogicError);

    EXPECT_EQ(result.errorMessage(), "Test error message");

}



TEST_F(BasicResultTest_1067, StaticOkWithValue_1067) {

    auto result = BasicResult<int>::ok(42);

    EXPECT_EQ(result.type(), ResultType::Ok);

    EXPECT_TRUE(static_cast<bool>(result));

}



TEST_F(BasicResultTest_1067, StaticOkWithoutValue_1067) {

    auto result = BasicResult<void>::ok();

    EXPECT_EQ(result.type(), ResultType::Ok);

    EXPECT_TRUE(static_cast<bool>(result));

}



TEST_F(BasicResultTest_1067, StaticLogicError_1067) {

    auto result = BasicResult<int>::logicError("Logic error message");

    EXPECT_EQ(result.type(), ResultType::LogicError);

    EXPECT_FALSE(static_cast<bool>(result));

    EXPECT_EQ(result.errorMessage(), "Logic error message");

}



TEST_F(BasicResultTest_1067, StaticRuntimeError_1067) {

    auto result = BasicResult<int>::runtimeError("Runtime error message");

    EXPECT_EQ(result.type(), ResultType::RuntimeError);

    EXPECT_FALSE(static_cast<bool>(result));

    EXPECT_EQ(result.errorMessage(), "Runtime error message");

}



TEST_F(BasicResultTest_1067, TypeMethodReturnsCorrectValue_1067) {

    BasicResult<int> logicError = BasicResult<int>::logicError("Logic error message");

    BasicResult<int> runtimeError = BasicResult<int>::runtimeError("Runtime error message");



    EXPECT_EQ(logicError.type(), ResultType::LogicError);

    EXPECT_EQ(runtimeError.type(), ResultType::RuntimeError);

}



TEST_F(BasicResultTest_1067, ErrorMessageMethodReturnsCorrectValue_1067) {

    BasicResult<int> logicError = BasicResult<int>::logicError("Logic error message");

    BasicResult<int> runtimeError = BasicResult<int>::runtimeError("Runtime error message");



    EXPECT_EQ(logicError.errorMessage(), "Logic error message");

    EXPECT_EQ(runtimeError.errorMessage(), "Runtime error message");

}



TEST_F(BasicResultTest_1067, BoolConversionOperator_1067) {

    BasicResult<int> okResult = BasicResult<int>::ok(42);

    BasicResult<int> logicError = BasicResult<int>::logicError("Logic error message");



    EXPECT_TRUE(static_cast<bool>(okResult));

    EXPECT_FALSE(static_cast<bool>(logicError));

}
