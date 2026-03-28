#include <gtest/gtest.h>

#include "catch_clara.hpp"



using namespace Catch::Clara::Detail;



class BasicResultTest_364 : public ::testing::Test {

protected:

    using Result = BasicResult<int>;

};



TEST_F(BasicResultTest_364, OkWithIntValue_ReturnsTrueAndCorrectType_364) {

    auto result = BasicResult<int>::ok(42);

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_EQ(result.type(), ResultType::Ok);

}



TEST_F(BasicResultTest_364, OkWithoutValue_ReturnsTrueAndCorrectType_364) {

    auto result = BasicResult<void>::ok();

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_EQ(result.type(), ResultType::Ok);

}



TEST_F(BasicResultTest_364, LogicError_ReturnsFalseAndCorrectType_364) {

    auto result = BasicResult<int>::logicError("Logic error message");

    EXPECT_FALSE(static_cast<bool>(result));

    EXPECT_EQ(result.type(), ResultType::LogicError);

    EXPECT_EQ(result.errorMessage(), "Logic error message");

}



TEST_F(BasicResultTest_364, RuntimeError_ReturnsFalseAndCorrectType_364) {

    auto result = BasicResult<int>::runtimeError("Runtime error message");

    EXPECT_FALSE(static_cast<bool>(result));

    EXPECT_EQ(result.type(), ResultType::RuntimeError);

    EXPECT_EQ(result.errorMessage(), "Runtime error message");

}



TEST_F(BasicResultTest_364, CopyConstructorPreservesState_364) {

    auto original = BasicResult<int>::logicError("Original error");

    auto copy = BasicResult<int>(original);



    EXPECT_FALSE(static_cast<bool>(copy));

    EXPECT_EQ(copy.type(), ResultType::LogicError);

    EXPECT_EQ(copy.errorMessage(), "Original error");

}



TEST_F(BasicResultTest_364, TypeComparison_ReturnsCorrectValues_364) {

    auto okResult = BasicResult<int>::ok(10);

    auto logicResult = BasicResult<int>::logicError("Logic error");

    auto runtimeResult = BasicResult<int>::runtimeError("Runtime error");



    EXPECT_EQ(okResult.type(), ResultType::Ok);

    EXPECT_EQ(logicResult.type(), ResultType::LogicError);

    EXPECT_EQ(runtimeResult.type(), ResultType::RuntimeError);

}
