#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>

namespace {

using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

// Test fixture for BasicResult<int>
class BasicResultIntTest_364 : public ::testing::Test {};

// Test fixture for BasicResult<std::string>
class BasicResultStringTest_364 : public ::testing::Test {};

// Test fixture for BasicResult<void> (no value)
class BasicResultVoidTest_364 : public ::testing::Test {};

// ==================== ok() with value tests ====================

TEST_F(BasicResultIntTest_364, OkWithIntValue_364) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultIntTest_364, OkWithZeroValue_364) {
    auto result = BasicResult<int>::ok(0);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultIntTest_364, OkWithNegativeValue_364) {
    auto result = BasicResult<int>::ok(-1);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultStringTest_364, OkWithStringValue_364) {
    auto result = BasicResult<std::string>::ok(std::string("hello"));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultStringTest_364, OkWithEmptyStringValue_364) {
    auto result = BasicResult<std::string>::ok(std::string(""));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

// ==================== ok() without value tests ====================

TEST_F(BasicResultVoidTest_364, OkWithoutValue_364) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(result.errorMessage().empty());
}

// ==================== logicError() tests ====================

TEST_F(BasicResultIntTest_364, LogicErrorReturnsFailedResult_364) {
    auto result = BasicResult<int>::logicError(std::string("some logic error"));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), "some logic error");
}

TEST_F(BasicResultVoidTest_364, LogicErrorVoidResult_364) {
    auto result = BasicResult<void>::logicError(std::string("logic error"));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), "logic error");
}

TEST_F(BasicResultIntTest_364, LogicErrorWithEmptyMessage_364) {
    auto result = BasicResult<int>::logicError(std::string(""));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), "");
}

// ==================== runtimeError() tests ====================

TEST_F(BasicResultIntTest_364, RuntimeErrorReturnsFailedResult_364) {
    auto result = BasicResult<int>::runtimeError(std::string("some runtime error"));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), "some runtime error");
}

TEST_F(BasicResultVoidTest_364, RuntimeErrorVoidResult_364) {
    auto result = BasicResult<void>::runtimeError(std::string("runtime error"));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), "runtime error");
}

TEST_F(BasicResultIntTest_364, RuntimeErrorWithEmptyMessage_364) {
    auto result = BasicResult<int>::runtimeError(std::string(""));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), "");
}

// ==================== operator bool() tests ====================

TEST_F(BasicResultIntTest_364, BoolOperatorTrueForOk_364) {
    auto result = BasicResult<int>::ok(10);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultIntTest_364, BoolOperatorFalseForLogicError_364) {
    auto result = BasicResult<int>::logicError(std::string("err"));
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultIntTest_364, BoolOperatorFalseForRuntimeError_364) {
    auto result = BasicResult<int>::runtimeError(std::string("err"));
    EXPECT_FALSE(static_cast<bool>(result));
}

// ==================== type() tests ====================

TEST_F(BasicResultIntTest_364, TypeIsOkForOkResult_364) {
    auto result = BasicResult<int>::ok(5);
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultIntTest_364, TypeIsLogicErrorForLogicErrorResult_364) {
    auto result = BasicResult<int>::logicError(std::string("test"));
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

TEST_F(BasicResultIntTest_364, TypeIsRuntimeErrorForRuntimeErrorResult_364) {
    auto result = BasicResult<int>::runtimeError(std::string("test"));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

// ==================== errorMessage() tests ====================

TEST_F(BasicResultIntTest_364, ErrorMessageEmptyForOk_364) {
    auto result = BasicResult<int>::ok(100);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultIntTest_364, ErrorMessagePreservedForLogicError_364) {
    std::string msg = "a detailed logic error message";
    auto result = BasicResult<int>::logicError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

TEST_F(BasicResultIntTest_364, ErrorMessagePreservedForRuntimeError_364) {
    std::string msg = "a detailed runtime error message";
    auto result = BasicResult<int>::runtimeError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

// ==================== Copy construction from other BasicResult type ====================

TEST_F(BasicResultIntTest_364, CopyConstructFromOtherType_364) {
    auto original = BasicResult<int>::logicError(std::string("copy test"));
    BasicResult<int> copied(original);
    EXPECT_FALSE(static_cast<bool>(copied));
    EXPECT_EQ(copied.type(), ResultType::LogicError);
    EXPECT_EQ(copied.errorMessage(), "copy test");
}

// ==================== Boundary: long error messages ====================

TEST_F(BasicResultIntTest_364, LongErrorMessage_364) {
    std::string longMsg(10000, 'x');
    auto result = BasicResult<int>::runtimeError(std::string(longMsg));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), longMsg);
    EXPECT_EQ(result.errorMessage().size(), 10000u);
}

// ==================== Different value types ====================

TEST_F(BasicResultIntTest_364, OkWithDoubleValue_364) {
    auto result = BasicResult<double>::ok(3.14);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultIntTest_364, OkWithBoolValue_364) {
    auto result = BasicResult<bool>::ok(true);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

// ==================== ResultType enum values ====================

TEST(ResultTypeTest_364, EnumValues_364) {
    EXPECT_EQ(static_cast<int>(ResultType::Ok), 0);
    EXPECT_EQ(static_cast<int>(ResultType::LogicError), 1);
    EXPECT_EQ(static_cast<int>(ResultType::RuntimeError), 2);
}

}  // namespace
