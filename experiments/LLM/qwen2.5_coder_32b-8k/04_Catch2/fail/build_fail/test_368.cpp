#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



class BasicResultTest_368 : public ::testing::Test {

protected:

    using ResultType = Catch::Clara::Detail::ResultType;

};



TEST_F(BasicResultTest_368, DefaultConstruction_OkType_368) {

    BasicResult<int> result(ResultType::Ok, "");

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_EQ(result.type(), ResultType::Ok);

}



TEST_F(BasicResultTest_368, LogicError_Construction_ErrorTypeAndMessage_368) {

    BasicResult<int> result = BasicResult<int>::logicError("Logic error occurred");

    EXPECT_FALSE(static_cast<bool>(result));

    EXPECT_EQ(result.type(), ResultType::LogicError);

    EXPECT_EQ(result.errorMessage(), "Logic error occurred");

}



TEST_F(BasicResultTest_368, RuntimeError_Construction_ErrorTypeAndMessage_368) {

    BasicResult<int> result = BasicResult<int>::runtimeError("Runtime error occurred");

    EXPECT_FALSE(static_cast<bool>(result));

    EXPECT_EQ(result.type(), ResultType::RuntimeError);

    EXPECT_EQ(result.errorMessage(), "Runtime error occurred");

}



TEST_F(BasicResultTest_368, OkStaticMethod_NoMessage_OkType_368) {

    BasicResult<int> result = BasicResult<int>::ok();

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_EQ(result.type(), ResultType::Ok);

}



TEST_F(BasicResultTest_368, OkStaticMethod_WithMessage_OkTypeAndMessage_368) {

    BasicResult<std::string> result = BasicResult<std::string>::ok("Success");

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_EQ(result.type(), ResultType::Ok);

    EXPECT_EQ(result.errorMessage(), "");

}



TEST_F(BasicResultTest_368, CopyConstructor_PreservesState_368) {

    BasicResult<int> original = BasicResult<int>::logicError("Copy test");

    BasicResult<int> copy(original);

    EXPECT_FALSE(static_cast<bool>(copy));

    EXPECT_EQ(copy.type(), ResultType::LogicError);

    EXPECT_EQ(copy.errorMessage(), "Copy test");

}



TEST_F(BasicResultTest_368, MoveConstructor_PreservesState_368) {

    BasicResult<int> original = BasicResult<int>::runtimeError("Move test");

    BasicResult<int> moved(std::move(original));

    EXPECT_FALSE(static_cast<bool>(moved));

    EXPECT_EQ(moved.type(), ResultType::RuntimeError);

    EXPECT_EQ(moved.errorMessage(), "Move test");

}
