#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>

// We need to work with the actual types from the Clara namespace.
// Based on the interface, we'll test BasicResult through its public static factories and methods.

namespace {

using namespace Catch::Clara::Detail;

// We'll use a concrete instantiation. Based on the interface, BasicResult<void> and BasicResult<int> should work.

class BasicResultTest_370 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that ok() creates a result that converts to true (success)
TEST_F(BasicResultTest_370, OkResultIsTruthy_370) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that ok() result has an empty error message
TEST_F(BasicResultTest_370, OkResultHasEmptyErrorMessage_370) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test that logicError creates a result that converts to false (failure)
TEST_F(BasicResultTest_370, LogicErrorResultIsFalsy_370) {
    auto result = BasicResult<void>::logicError("some logic error");
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test that logicError stores the correct error message
TEST_F(BasicResultTest_370, LogicErrorHasCorrectMessage_370) {
    std::string msg = "test logic error message";
    auto result = BasicResult<void>::logicError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

// Test that runtimeError creates a result that converts to false (failure)
TEST_F(BasicResultTest_370, RuntimeErrorResultIsFalsy_370) {
    auto result = BasicResult<void>::runtimeError("some runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test that runtimeError stores the correct error message
TEST_F(BasicResultTest_370, RuntimeErrorHasCorrectMessage_370) {
    std::string msg = "test runtime error message";
    auto result = BasicResult<void>::runtimeError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

// Test with empty error message for logicError
TEST_F(BasicResultTest_370, LogicErrorWithEmptyMessage_370) {
    auto result = BasicResult<void>::logicError(std::string(""));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test with empty error message for runtimeError
TEST_F(BasicResultTest_370, RuntimeErrorWithEmptyMessage_370) {
    auto result = BasicResult<void>::runtimeError(std::string(""));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test ok with a value (typed result)
TEST_F(BasicResultTest_370, OkWithValueIsTruthy_370) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test ok with value has empty error message
TEST_F(BasicResultTest_370, OkWithValueHasEmptyErrorMessage_370) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test logicError for typed result
TEST_F(BasicResultTest_370, TypedLogicErrorIsFalsy_370) {
    auto result = BasicResult<int>::logicError("typed logic error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "typed logic error");
}

// Test runtimeError for typed result
TEST_F(BasicResultTest_370, TypedRuntimeErrorIsFalsy_370) {
    auto result = BasicResult<int>::runtimeError("typed runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "typed runtime error");
}

// Test copy construction from one type to another (e.g., BasicResult<void> from BasicResult<int> error)
TEST_F(BasicResultTest_370, CopyConstructFromDifferentType_370) {
    auto intResult = BasicResult<int>::logicError("cross-type error");
    BasicResult<void> voidResult(intResult);
    EXPECT_FALSE(static_cast<bool>(voidResult));
    EXPECT_EQ(voidResult.errorMessage(), "cross-type error");
}

// Test copy construction preserves ok status
TEST_F(BasicResultTest_370, CopyConstructPreservesOk_370) {
    auto okResult = BasicResult<int>::ok(100);
    BasicResult<void> voidResult(okResult);
    EXPECT_TRUE(static_cast<bool>(voidResult));
    EXPECT_TRUE(voidResult.errorMessage().empty());
}

// Test with a long error message
TEST_F(BasicResultTest_370, LongErrorMessage_370) {
    std::string longMsg(10000, 'x');
    auto result = BasicResult<void>::runtimeError(std::string(longMsg));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), longMsg);
    EXPECT_EQ(result.errorMessage().size(), 10000u);
}

// Test error message with special characters
TEST_F(BasicResultTest_370, ErrorMessageWithSpecialCharacters_370) {
    std::string specialMsg = "error: \n\t\r\0 special chars!@#$%^&*()";
    auto result = BasicResult<void>::logicError(std::string(specialMsg));
    EXPECT_EQ(result.errorMessage(), specialMsg);
}

// Test that ok with string value works
TEST_F(BasicResultTest_370, OkWithStringValue_370) {
    auto result = BasicResult<std::string>::ok(std::string("hello"));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test runtimeError for string-typed result
TEST_F(BasicResultTest_370, StringTypedRuntimeError_370) {
    auto result = BasicResult<std::string>::runtimeError("string runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "string runtime error");
}

} // anonymous namespace
