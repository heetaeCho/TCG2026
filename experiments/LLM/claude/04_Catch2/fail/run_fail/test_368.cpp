#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>

namespace {

using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

// Test fixture
class BasicResultTest_368 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== ok() static factory tests ====================

TEST_F(BasicResultTest_368, OkResultWithValueIsTruthy_368) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_368, OkResultWithoutValueIsTruthy_368) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_368, OkResultTypeIsOk_368) {
    auto result = BasicResult<int>::ok(10);
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultTest_368, OkVoidResultTypeIsOk_368) {
    auto result = BasicResult<void>::ok();
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultTest_368, OkResultHasEmptyErrorMessage_368) {
    auto result = BasicResult<int>::ok(10);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultTest_368, OkVoidResultHasEmptyErrorMessage_368) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(result.errorMessage().empty());
}

// ==================== logicError() static factory tests ====================

TEST_F(BasicResultTest_368, LogicErrorResultIsFalsy_368) {
    auto result = BasicResult<int>::logicError("some logic error");
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_368, LogicErrorResultTypeIsLogicError_368) {
    auto result = BasicResult<int>::logicError("some logic error");
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

TEST_F(BasicResultTest_368, LogicErrorResultHasCorrectMessage_368) {
    std::string msg = "test logic error message";
    auto result = BasicResult<int>::logicError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

TEST_F(BasicResultTest_368, LogicErrorVoidResultIsFalsy_368) {
    auto result = BasicResult<void>::logicError("logic error");
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_368, LogicErrorVoidResultTypeIsLogicError_368) {
    auto result = BasicResult<void>::logicError("logic error");
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

TEST_F(BasicResultTest_368, LogicErrorVoidResultHasCorrectMessage_368) {
    std::string msg = "void logic error";
    auto result = BasicResult<void>::logicError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

// ==================== runtimeError() static factory tests ====================

TEST_F(BasicResultTest_368, RuntimeErrorResultIsFalsy_368) {
    auto result = BasicResult<int>::runtimeError("some runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_368, RuntimeErrorResultTypeIsRuntimeError_368) {
    auto result = BasicResult<int>::runtimeError("some runtime error");
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultTest_368, RuntimeErrorResultHasCorrectMessage_368) {
    std::string msg = "test runtime error message";
    auto result = BasicResult<int>::runtimeError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

TEST_F(BasicResultTest_368, RuntimeErrorVoidResultIsFalsy_368) {
    auto result = BasicResult<void>::runtimeError("runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_368, RuntimeErrorVoidResultTypeIsRuntimeError_368) {
    auto result = BasicResult<void>::runtimeError("runtime error");
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultTest_368, RuntimeErrorVoidResultHasCorrectMessage_368) {
    std::string msg = "void runtime error";
    auto result = BasicResult<void>::runtimeError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

// ==================== Copy construction from different type ====================

TEST_F(BasicResultTest_368, CopyConstructFromVoidLogicErrorToIntResult_368) {
    auto voidResult = BasicResult<void>::logicError("cross-type error");
    BasicResult<int> intResult(voidResult);
    EXPECT_FALSE(static_cast<bool>(intResult));
    EXPECT_EQ(intResult.type(), ResultType::LogicError);
    EXPECT_EQ(intResult.errorMessage(), "cross-type error");
}

TEST_F(BasicResultTest_368, CopyConstructFromVoidRuntimeErrorToIntResult_368) {
    auto voidResult = BasicResult<void>::runtimeError("cross-type runtime");
    BasicResult<int> intResult(voidResult);
    EXPECT_FALSE(static_cast<bool>(intResult));
    EXPECT_EQ(intResult.type(), ResultType::RuntimeError);
    EXPECT_EQ(intResult.errorMessage(), "cross-type runtime");
}

// ==================== Boundary / edge cases ====================

TEST_F(BasicResultTest_368, LogicErrorWithEmptyMessage_368) {
    auto result = BasicResult<void>::logicError(std::string(""));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultTest_368, RuntimeErrorWithEmptyMessage_368) {
    auto result = BasicResult<void>::runtimeError(std::string(""));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultTest_368, LogicErrorWithLongMessage_368) {
    std::string longMsg(10000, 'x');
    auto result = BasicResult<void>::logicError(std::string(longMsg));
    EXPECT_EQ(result.errorMessage(), longMsg);
    EXPECT_EQ(result.errorMessage().size(), 10000u);
}

TEST_F(BasicResultTest_368, OkWithStringValue_368) {
    auto result = BasicResult<std::string>::ok(std::string("hello"));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultTest_368, OkWithZeroValue_368) {
    auto result = BasicResult<int>::ok(0);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultTest_368, OkWithNegativeValue_368) {
    auto result = BasicResult<int>::ok(-1);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

// ==================== Distinguishing error types ====================

TEST_F(BasicResultTest_368, LogicAndRuntimeErrorsAreDifferentTypes_368) {
    auto logicErr = BasicResult<void>::logicError("err");
    auto runtimeErr = BasicResult<void>::runtimeError("err");
    EXPECT_NE(logicErr.type(), runtimeErr.type());
    EXPECT_FALSE(static_cast<bool>(logicErr));
    EXPECT_FALSE(static_cast<bool>(runtimeErr));
}

TEST_F(BasicResultTest_368, OkAndErrorAreDifferentBoolValues_368) {
    auto ok = BasicResult<void>::ok();
    auto err = BasicResult<void>::logicError("err");
    EXPECT_TRUE(static_cast<bool>(ok));
    EXPECT_FALSE(static_cast<bool>(err));
}

// ==================== ResultType enum values ====================

TEST_F(BasicResultTest_368, ResultTypeEnumValues_368) {
    EXPECT_EQ(static_cast<int>(ResultType::Ok), 0);
    EXPECT_EQ(static_cast<int>(ResultType::LogicError), 1);
    EXPECT_EQ(static_cast<int>(ResultType::RuntimeError), 2);
}

} // anonymous namespace
