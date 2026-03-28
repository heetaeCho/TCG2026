#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>

namespace {

using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

// Use the void specialization or a simple type for testing
// Based on the interface, BasicResult is a template. We'll test with common types.

class BasicResultTest_367 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test ok() with no value (void-like)
TEST_F(BasicResultTest_367, OkReturnsSuccessResult_367) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test ok(value) with an int
TEST_F(BasicResultTest_367, OkWithValueReturnsSuccessResult_367) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test ok(value) with a string
TEST_F(BasicResultTest_367, OkWithStringValueReturnsSuccessResult_367) {
    auto result = BasicResult<std::string>::ok(std::string("hello"));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test runtimeError returns a result that evaluates to false
TEST_F(BasicResultTest_367, RuntimeErrorReturnsFalseResult_367) {
    auto result = BasicResult<void>::runtimeError("something went wrong");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

// Test runtimeError message is preserved
TEST_F(BasicResultTest_367, RuntimeErrorPreservesMessage_367) {
    std::string msg = "a runtime error occurred";
    auto result = BasicResult<void>::runtimeError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

// Test logicError returns a result that evaluates to false
TEST_F(BasicResultTest_367, LogicErrorReturnsFalseResult_367) {
    auto result = BasicResult<void>::logicError("logic error happened");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

// Test logicError message is preserved
TEST_F(BasicResultTest_367, LogicErrorPreservesMessage_367) {
    std::string msg = "a logic error occurred";
    auto result = BasicResult<void>::logicError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

// Test runtimeError with empty message
TEST_F(BasicResultTest_367, RuntimeErrorWithEmptyMessage_367) {
    auto result = BasicResult<void>::runtimeError("");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test logicError with empty message
TEST_F(BasicResultTest_367, LogicErrorWithEmptyMessage_367) {
    auto result = BasicResult<void>::logicError("");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test runtimeError with a very long message
TEST_F(BasicResultTest_367, RuntimeErrorWithLongMessage_367) {
    std::string longMsg(10000, 'x');
    auto result = BasicResult<void>::runtimeError(std::string(longMsg));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), longMsg);
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

// Test runtimeError with int template parameter
TEST_F(BasicResultTest_367, RuntimeErrorWithIntType_367) {
    auto result = BasicResult<int>::runtimeError("int runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), "int runtime error");
}

// Test logicError with int template parameter
TEST_F(BasicResultTest_367, LogicErrorWithIntType_367) {
    auto result = BasicResult<int>::logicError("int logic error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), "int logic error");
}

// Test ok result has empty error message
TEST_F(BasicResultTest_367, OkResultHasEmptyErrorMessage_367) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test copy construction from one BasicResult type to another
TEST_F(BasicResultTest_367, CopyConstructFromOtherType_367) {
    auto original = BasicResult<void>::runtimeError("cross-type error");
    BasicResult<void> copy(original);
    EXPECT_FALSE(static_cast<bool>(copy));
    EXPECT_EQ(copy.type(), ResultType::RuntimeError);
    EXPECT_EQ(copy.errorMessage(), "cross-type error");
}

// Test that ok result type is Ok
TEST_F(BasicResultTest_367, OkResultTypeIsOk_367) {
    auto result = BasicResult<void>::ok();
    EXPECT_EQ(result.type(), ResultType::Ok);
}

// Test runtimeError with special characters in message
TEST_F(BasicResultTest_367, RuntimeErrorWithSpecialCharacters_367) {
    std::string msg = "error: file not found\n\tat line 42\ttab\0embedded";
    auto result = BasicResult<void>::runtimeError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

// Test multiple sequential error results are independent
TEST_F(BasicResultTest_367, MultipleErrorResultsAreIndependent_367) {
    auto result1 = BasicResult<void>::runtimeError("error1");
    auto result2 = BasicResult<void>::runtimeError("error2");
    auto result3 = BasicResult<void>::logicError("error3");

    EXPECT_EQ(result1.errorMessage(), "error1");
    EXPECT_EQ(result2.errorMessage(), "error2");
    EXPECT_EQ(result3.errorMessage(), "error3");

    EXPECT_EQ(result1.type(), ResultType::RuntimeError);
    EXPECT_EQ(result2.type(), ResultType::RuntimeError);
    EXPECT_EQ(result3.type(), ResultType::LogicError);
}

// Test that ok with value and error results differ in bool conversion
TEST_F(BasicResultTest_367, OkAndErrorDifferInBoolConversion_367) {
    auto okResult = BasicResult<int>::ok(100);
    auto errResult = BasicResult<int>::runtimeError("fail");

    EXPECT_TRUE(static_cast<bool>(okResult));
    EXPECT_FALSE(static_cast<bool>(errResult));
}

} // namespace
