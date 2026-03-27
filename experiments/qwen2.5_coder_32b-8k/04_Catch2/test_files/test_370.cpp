#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_clara.hpp"



using namespace Catch::Clara::Detail;



class BasicResultTest_370 : public ::testing::Test {

protected:

    using ResultType = typename BasicResult<int>::ResultType;

};



TEST_F(BasicResultTest_370, ErrorMessageReturnsEmptyStringWhenOk_370) {

    BasicResult<int> result = BasicResult<int>::ok(42);

    EXPECT_EQ(result.errorMessage(), "");

}



TEST_F(BasicResultTest_370, ErrorMessageReturnsProvidedMessageForLogicError_370) {

    std::string errorMessage = "Logical Error";

    BasicResult<int> result = BasicResult<int>::logicError(errorMessage);

    EXPECT_EQ(result.errorMessage(), errorMessage);

}



TEST_F(BasicResultTest_370, ErrorMessageReturnsProvidedMessageForRuntimeError_370) {

    std::string errorMessage = "Runtime Error";

    BasicResult<int> result = BasicResult<int>::runtimeError(errorMessage);

    EXPECT_EQ(result.errorMessage(), errorMessage);

}



TEST_F(BasicResultTest_370, BoolOperatorReturnsTrueWhenOk_370) {

    BasicResult<int> result = BasicResult<int>::ok(42);

    EXPECT_TRUE(static_cast<bool>(result));

}



TEST_F(BasicResultTest_370, BoolOperatorReturnsFalseWhenLogicError_370) {

    BasicResult<int> result = BasicResult<int>::logicError("Logical Error");

    EXPECT_FALSE(static_cast<bool>(result));

}



TEST_F(BasicResultTest_370, BoolOperatorReturnsFalseWhenRuntimeError_370) {

    BasicResult<int> result = BasicResult<int>::runtimeError("Runtime Error");

    EXPECT_FALSE(static_cast<bool>(result));

}
