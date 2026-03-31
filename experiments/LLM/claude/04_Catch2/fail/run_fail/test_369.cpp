#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>

namespace {

using namespace Catch::Clara::Detail;

// Use BasicResult<void> and BasicResult<int> as concrete instantiations

class BasicResultVoidTest_369 : public ::testing::Test {};
class BasicResultIntTest_369 : public ::testing::Test {};

// ==================== BasicResult<void> Tests ====================

TEST_F(BasicResultVoidTest_369, OkReturnsOkType_369) {
    auto result = BasicResult<void>::ok();
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultVoidTest_369, OkResultIsTrueWhenConvertedToBool_369) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultVoidTest_369, LogicErrorReturnsLogicErrorType_369) {
    auto result = BasicResult<void>::logicError(std::string("logic error message"));
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

TEST_F(BasicResultVoidTest_369, LogicErrorIsFalseWhenConvertedToBool_369) {
    auto result = BasicResult<void>::logicError(std::string("some logic error"));
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultVoidTest_369, LogicErrorMessageIsPreserved_369) {
    std::string msg = "this is a logic error";
    auto result = BasicResult<void>::logicError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

TEST_F(BasicResultVoidTest_369, RuntimeErrorReturnsRuntimeErrorType_369) {
    auto result = BasicResult<void>::runtimeError(std::string("runtime error message"));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultVoidTest_369, RuntimeErrorIsFalseWhenConvertedToBool_369) {
    auto result = BasicResult<void>::runtimeError(std::string("some runtime error"));
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultVoidTest_369, RuntimeErrorMessageIsPreserved_369) {
    std::string msg = "this is a runtime error";
    auto result = BasicResult<void>::runtimeError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

TEST_F(BasicResultVoidTest_369, OkResultHasEmptyErrorMessage_369) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultVoidTest_369, EmptyLogicErrorMessage_369) {
    auto result = BasicResult<void>::logicError(std::string(""));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultVoidTest_369, EmptyRuntimeErrorMessage_369) {
    auto result = BasicResult<void>::runtimeError(std::string(""));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_TRUE(result.errorMessage().empty());
}

// ==================== BasicResult<int> Tests ====================

TEST_F(BasicResultIntTest_369, OkWithValueReturnsOkType_369) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultIntTest_369, OkWithValueIsTrueWhenConvertedToBool_369) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultIntTest_369, OkWithValuePreservesValue_369) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_EQ(result.value(), 42);
}

TEST_F(BasicResultIntTest_369, OkWithZeroValue_369) {
    auto result = BasicResult<int>::ok(0);
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_EQ(result.value(), 0);
}

TEST_F(BasicResultIntTest_369, OkWithNegativeValue_369) {
    auto result = BasicResult<int>::ok(-100);
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_EQ(result.value(), -100);
}

TEST_F(BasicResultIntTest_369, LogicErrorReturnsLogicErrorType_369) {
    auto result = BasicResult<int>::logicError(std::string("int logic error"));
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

TEST_F(BasicResultIntTest_369, LogicErrorIsFalseWhenConvertedToBool_369) {
    auto result = BasicResult<int>::logicError(std::string("int logic error"));
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultIntTest_369, LogicErrorMessageIsPreserved_369) {
    std::string msg = "int logic error message";
    auto result = BasicResult<int>::logicError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

TEST_F(BasicResultIntTest_369, RuntimeErrorReturnsRuntimeErrorType_369) {
    auto result = BasicResult<int>::runtimeError(std::string("int runtime error"));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultIntTest_369, RuntimeErrorIsFalseWhenConvertedToBool_369) {
    auto result = BasicResult<int>::runtimeError(std::string("int runtime error"));
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultIntTest_369, RuntimeErrorMessageIsPreserved_369) {
    std::string msg = "int runtime error message";
    auto result = BasicResult<int>::runtimeError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

TEST_F(BasicResultIntTest_369, OkResultHasEmptyErrorMessage_369) {
    auto result = BasicResult<int>::ok(10);
    EXPECT_TRUE(result.errorMessage().empty());
}

// ==================== Copy Construction Tests ====================

TEST_F(BasicResultVoidTest_369, CopyConstructFromVoidOk_369) {
    auto original = BasicResult<void>::ok();
    BasicResult<void> copy(original);
    EXPECT_EQ(copy.type(), ResultType::Ok);
    EXPECT_TRUE(static_cast<bool>(copy));
}

TEST_F(BasicResultVoidTest_369, CopyConstructFromVoidError_369) {
    auto original = BasicResult<void>::logicError(std::string("copy test error"));
    BasicResult<void> copy(original);
    EXPECT_EQ(copy.type(), ResultType::LogicError);
    EXPECT_EQ(copy.errorMessage(), "copy test error");
    EXPECT_FALSE(static_cast<bool>(copy));
}

// ==================== Long Error Message Tests ====================

TEST_F(BasicResultVoidTest_369, LongErrorMessage_369) {
    std::string longMsg(10000, 'x');
    auto result = BasicResult<void>::runtimeError(std::string(longMsg));
    EXPECT_EQ(result.errorMessage(), longMsg);
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

// ==================== BasicResult<std::string> Tests ====================

class BasicResultStringTest_369 : public ::testing::Test {};

TEST_F(BasicResultStringTest_369, OkWithStringValue_369) {
    auto result = BasicResult<std::string>::ok(std::string("hello"));
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.value(), "hello");
}

TEST_F(BasicResultStringTest_369, OkWithEmptyStringValue_369) {
    auto result = BasicResult<std::string>::ok(std::string(""));
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.value(), "");
}

TEST_F(BasicResultStringTest_369, LogicErrorForStringResult_369) {
    auto result = BasicResult<std::string>::logicError(std::string("string logic error"));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "string logic error");
}

} // anonymous namespace
