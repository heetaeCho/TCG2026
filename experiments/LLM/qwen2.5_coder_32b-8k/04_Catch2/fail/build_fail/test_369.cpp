#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



class BasicResultTest_369 : public ::testing::Test {

protected:

    using Result = BasicResult<int>;

};



TEST_F(BasicResultTest_369, Type_ReturnsCorrectTypeForOk_369) {

    auto result = Result::ok(42);

    EXPECT_EQ(result.type(), ResultType::Ok);

}



TEST_F(BasicResultTest_369, Type_ReturnsCorrectTypeForLogicError_369) {

    auto result = Result::logicError("Logic error message");

    EXPECT_EQ(result.type(), ResultType::LogicError);

}



TEST_F(BasicResultTest_369, Type_ReturnsCorrectTypeForRuntimeError_369) {

    auto result = Result::runtimeError("Runtime error message");

    EXPECT_EQ(result.type(), ResultType::RuntimeError);

}



TEST_F(BasicResultTest_369, ErrorMessage_ReturnsEmptyStringForOk_369) {

    auto result = Result::ok(42);

    EXPECT_TRUE(result.errorMessage().empty());

}



TEST_F(BasicResultTest_369, ErrorMessage_ReturnsCorrectMessageForLogicError_369) {

    std::string message = "Logic error message";

    auto result = Result::logicError(message);

    EXPECT_EQ(result.errorMessage(), message);

}



TEST_F(BasicResultTest_369, ErrorMessage_ReturnsCorrectMessageForRuntimeError_369) {

    std::string message = "Runtime error message";

    auto result = Result::runtimeError(message);

    EXPECT_EQ(result.errorMessage(), message);

}



TEST_F(BasicResultTest_369, BoolConversion_ReturnsTrueForOk_369) {

    auto result = Result::ok(42);

    EXPECT_TRUE(static_cast<bool>(result));

}



TEST_F(BasicResultTest_369, BoolConversion_ReturnsFalseForLogicError_369) {

    auto result = Result::logicError("Logic error message");

    EXPECT_FALSE(static_cast<bool>(result));

}



TEST_F(BasicResultTest_369, BoolConversion_ReturnsFalseForRuntimeError_369) {

    auto result = Result::runtimeError("Runtime error message");

    EXPECT_FALSE(static_cast<bool>(result));

}
