#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>

namespace {

using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

// Test fixture
class BasicResultTest_371 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Tests for ok() static factory (no value)
// ============================================================

TEST_F(BasicResultTest_371, OkResultHasOkType_371) {
    auto result = BasicResult<void>::ok();
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultTest_371, OkResultBoolConversionIsTrue_371) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_371, OkResultErrorMessageIsEmpty_371) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultTest_371, OkResultEnforceOkDoesNotAbort_371) {
    auto result = BasicResult<void>::ok();
    EXPECT_NO_FATAL_FAILURE(result.enforceOk());
}

// ============================================================
// Tests for ok(value) static factory (with value)
// ============================================================

TEST_F(BasicResultTest_371, OkWithValueHasOkType_371) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultTest_371, OkWithValueBoolConversionIsTrue_371) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_371, OkWithValueErrorMessageIsEmpty_371) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultTest_371, OkWithValueEnforceOkDoesNotAbort_371) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_NO_FATAL_FAILURE(result.enforceOk());
}

TEST_F(BasicResultTest_371, OkWithStringValue_371) {
    auto result = BasicResult<std::string>::ok(std::string("hello"));
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(static_cast<bool>(result));
}

// ============================================================
// Tests for logicError() static factory
// ============================================================

TEST_F(BasicResultTest_371, LogicErrorHasLogicErrorType_371) {
    auto result = BasicResult<void>::logicError(std::string("some logic error"));
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

TEST_F(BasicResultTest_371, LogicErrorBoolConversionIsFalse_371) {
    auto result = BasicResult<void>::logicError(std::string("some logic error"));
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_371, LogicErrorHasCorrectMessage_371) {
    auto result = BasicResult<void>::logicError(std::string("specific error message"));
    EXPECT_EQ(result.errorMessage(), "specific error message");
}

TEST_F(BasicResultTest_371, LogicErrorEnforceOkAborts_371) {
    auto result = BasicResult<void>::logicError(std::string("error"));
    EXPECT_DEATH(result.enforceOk(), "");
}

TEST_F(BasicResultTest_371, LogicErrorWithEmptyMessage_371) {
    auto result = BasicResult<void>::logicError(std::string(""));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "");
}

// ============================================================
// Tests for runtimeError() static factory
// ============================================================

TEST_F(BasicResultTest_371, RuntimeErrorHasRuntimeErrorType_371) {
    auto result = BasicResult<void>::runtimeError(std::string("some runtime error"));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultTest_371, RuntimeErrorBoolConversionIsFalse_371) {
    auto result = BasicResult<void>::runtimeError(std::string("some runtime error"));
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_371, RuntimeErrorHasCorrectMessage_371) {
    auto result = BasicResult<void>::runtimeError(std::string("runtime issue"));
    EXPECT_EQ(result.errorMessage(), "runtime issue");
}

TEST_F(BasicResultTest_371, RuntimeErrorEnforceOkAborts_371) {
    auto result = BasicResult<void>::runtimeError(std::string("error"));
    EXPECT_DEATH(result.enforceOk(), "");
}

TEST_F(BasicResultTest_371, RuntimeErrorWithEmptyMessage_371) {
    auto result = BasicResult<void>::runtimeError(std::string(""));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_FALSE(static_cast<bool>(result));
}

// ============================================================
// Tests for copy construction from different BasicResult types
// ============================================================

TEST_F(BasicResultTest_371, CopyConstructFromLogicErrorPreservesType_371) {
    auto original = BasicResult<int>::logicError(std::string("copy error"));
    BasicResult<void> copied(original);
    EXPECT_EQ(copied.type(), ResultType::LogicError);
    EXPECT_EQ(copied.errorMessage(), "copy error");
}

TEST_F(BasicResultTest_371, CopyConstructFromRuntimeErrorPreservesType_371) {
    auto original = BasicResult<int>::runtimeError(std::string("runtime copy error"));
    BasicResult<void> copied(original);
    EXPECT_EQ(copied.type(), ResultType::RuntimeError);
    EXPECT_EQ(copied.errorMessage(), "runtime copy error");
}

TEST_F(BasicResultTest_371, CopyConstructFromOkPreservesType_371) {
    auto original = BasicResult<void>::ok();
    BasicResult<void> copied(original);
    EXPECT_EQ(copied.type(), ResultType::Ok);
    EXPECT_TRUE(static_cast<bool>(copied));
}

// ============================================================
// Tests with typed results (int)
// ============================================================

TEST_F(BasicResultTest_371, IntLogicErrorResult_371) {
    auto result = BasicResult<int>::logicError(std::string("int logic error"));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "int logic error");
}

TEST_F(BasicResultTest_371, IntRuntimeErrorResult_371) {
    auto result = BasicResult<int>::runtimeError(std::string("int runtime error"));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "int runtime error");
}

// ============================================================
// Boundary / edge cases
// ============================================================

TEST_F(BasicResultTest_371, LogicErrorWithLongMessage_371) {
    std::string longMessage(10000, 'x');
    auto result = BasicResult<void>::logicError(std::string(longMessage));
    EXPECT_EQ(result.errorMessage(), longMessage);
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

TEST_F(BasicResultTest_371, RuntimeErrorWithLongMessage_371) {
    std::string longMessage(10000, 'y');
    auto result = BasicResult<void>::runtimeError(std::string(longMessage));
    EXPECT_EQ(result.errorMessage(), longMessage);
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultTest_371, OkResultWithZeroValue_371) {
    auto result = BasicResult<int>::ok(0);
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_371, OkResultWithNegativeValue_371) {
    auto result = BasicResult<int>::ok(-1);
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultTest_371, LogicErrorWithSpecialCharactersInMessage_371) {
    std::string msg = "error\n\twith\0special chars";
    auto result = BasicResult<void>::logicError(std::string(msg));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), msg);
}

} // anonymous namespace
