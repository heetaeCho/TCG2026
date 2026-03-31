#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>

namespace {

using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

// Test fixture
class BasicResultTest_365 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== ok() static factory ====================

TEST_F(BasicResultTest_365, OkReturnsSuccessResult_365) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_365, OkResultHasOkType_365) {
    auto result = BasicResult<void>::ok();
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultTest_365, OkResultHasEmptyErrorMessage_365) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(result.errorMessage().empty());
}

// ==================== ok(value) static factory ====================

TEST_F(BasicResultTest_365, OkWithValueReturnsSuccessResult_365) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_365, OkWithValueHasOkType_365) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultTest_365, OkWithValueHasEmptyErrorMessage_365) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultTest_365, OkWithStringValue_365) {
    auto result = BasicResult<std::string>::ok(std::string("hello"));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

// ==================== logicError() static factory ====================

TEST_F(BasicResultTest_365, LogicErrorReturnsFalse_365) {
    auto result = BasicResult<void>::logicError("some logic error");
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_365, LogicErrorHasLogicErrorType_365) {
    auto result = BasicResult<void>::logicError("some logic error");
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

TEST_F(BasicResultTest_365, LogicErrorHasCorrectMessage_365) {
    auto result = BasicResult<void>::logicError("some logic error");
    EXPECT_EQ(result.errorMessage(), "some logic error");
}

TEST_F(BasicResultTest_365, LogicErrorWithEmptyMessage_365) {
    auto result = BasicResult<void>::logicError("");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultTest_365, LogicErrorWithTypedResult_365) {
    auto result = BasicResult<int>::logicError("typed logic error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), "typed logic error");
}

// ==================== runtimeError() static factory ====================

TEST_F(BasicResultTest_365, RuntimeErrorReturnsFalse_365) {
    auto result = BasicResult<void>::runtimeError("some runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_365, RuntimeErrorHasRuntimeErrorType_365) {
    auto result = BasicResult<void>::runtimeError("some runtime error");
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultTest_365, RuntimeErrorHasCorrectMessage_365) {
    auto result = BasicResult<void>::runtimeError("some runtime error");
    EXPECT_EQ(result.errorMessage(), "some runtime error");
}

TEST_F(BasicResultTest_365, RuntimeErrorWithEmptyMessage_365) {
    auto result = BasicResult<void>::runtimeError("");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultTest_365, RuntimeErrorWithTypedResult_365) {
    auto result = BasicResult<int>::runtimeError("typed runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), "typed runtime error");
}

// ==================== operator bool ====================

TEST_F(BasicResultTest_365, BoolOperatorTrueForOk_365) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(result);
}

TEST_F(BasicResultTest_365, BoolOperatorFalseForLogicError_365) {
    auto result = BasicResult<void>::logicError("error");
    EXPECT_FALSE(result);
}

TEST_F(BasicResultTest_365, BoolOperatorFalseForRuntimeError_365) {
    auto result = BasicResult<void>::runtimeError("error");
    EXPECT_FALSE(result);
}

// ==================== Copy construction from different type ====================

TEST_F(BasicResultTest_365, CopyConstructFromDifferentTypeLogicError_365) {
    auto original = BasicResult<int>::logicError("cross-type error");
    BasicResult<void> copied(original);
    EXPECT_FALSE(static_cast<bool>(copied));
    EXPECT_EQ(copied.type(), ResultType::LogicError);
    EXPECT_EQ(copied.errorMessage(), "cross-type error");
}

TEST_F(BasicResultTest_365, CopyConstructFromDifferentTypeRuntimeError_365) {
    auto original = BasicResult<int>::runtimeError("cross-type runtime");
    BasicResult<void> copied(original);
    EXPECT_FALSE(static_cast<bool>(copied));
    EXPECT_EQ(copied.type(), ResultType::RuntimeError);
    EXPECT_EQ(copied.errorMessage(), "cross-type runtime");
}

// ==================== Boundary / edge cases ====================

TEST_F(BasicResultTest_365, LogicErrorWithLongMessage_365) {
    std::string longMsg(10000, 'x');
    auto result = BasicResult<void>::logicError(std::string(longMsg));
    EXPECT_EQ(result.errorMessage(), longMsg);
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

TEST_F(BasicResultTest_365, RuntimeErrorWithLongMessage_365) {
    std::string longMsg(10000, 'y');
    auto result = BasicResult<void>::runtimeError(std::string(longMsg));
    EXPECT_EQ(result.errorMessage(), longMsg);
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultTest_365, LogicErrorWithSpecialCharacters_365) {
    std::string special = "error\n\t\r\0with special chars";
    auto result = BasicResult<void>::logicError(std::string(special));
    EXPECT_EQ(result.errorMessage(), special);
}

TEST_F(BasicResultTest_365, MultipleOkResultsAreIndependent_365) {
    auto r1 = BasicResult<void>::ok();
    auto r2 = BasicResult<void>::ok();
    EXPECT_TRUE(r1);
    EXPECT_TRUE(r2);
    EXPECT_EQ(r1.type(), r2.type());
}

TEST_F(BasicResultTest_365, MultipleErrorResultsAreIndependent_365) {
    auto r1 = BasicResult<void>::logicError("error1");
    auto r2 = BasicResult<void>::runtimeError("error2");
    EXPECT_NE(r1.type(), r2.type());
    EXPECT_NE(r1.errorMessage(), r2.errorMessage());
}

// ==================== ResultType enum values ====================

TEST_F(BasicResultTest_365, ResultTypeEnumValues_365) {
    EXPECT_EQ(static_cast<int>(ResultType::Ok), 0);
    EXPECT_EQ(static_cast<int>(ResultType::LogicError), 1);
    EXPECT_EQ(static_cast<int>(ResultType::RuntimeError), 2);
}

} // anonymous namespace
