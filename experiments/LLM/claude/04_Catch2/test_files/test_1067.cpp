#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>

// Alias for convenience
using ResultType = Catch::Clara::Detail::ResultType;

template <typename T>
using BasicResult = Catch::Clara::Detail::BasicResult<T>;

// ============================================================
// Tests for BasicResult<void>
// ============================================================

class BasicResultVoidTest_1067 : public ::testing::Test {};

TEST_F(BasicResultVoidTest_1067, OkReturnsTrue_1067) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultVoidTest_1067, OkHasTypeOk_1067) {
    auto result = BasicResult<void>::ok();
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultVoidTest_1067, OkHasEmptyErrorMessage_1067) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultVoidTest_1067, LogicErrorReturnsFalse_1067) {
    auto result = BasicResult<void>::logicError("some logic error");
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultVoidTest_1067, LogicErrorHasTypeLogicError_1067) {
    auto result = BasicResult<void>::logicError("some logic error");
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

TEST_F(BasicResultVoidTest_1067, LogicErrorPreservesMessage_1067) {
    auto result = BasicResult<void>::logicError("specific logic error message");
    EXPECT_EQ(result.errorMessage(), "specific logic error message");
}

TEST_F(BasicResultVoidTest_1067, RuntimeErrorReturnsFalse_1067) {
    auto result = BasicResult<void>::runtimeError("some runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultVoidTest_1067, RuntimeErrorHasTypeRuntimeError_1067) {
    auto result = BasicResult<void>::runtimeError("some runtime error");
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultVoidTest_1067, RuntimeErrorPreservesMessage_1067) {
    auto result = BasicResult<void>::runtimeError("specific runtime error message");
    EXPECT_EQ(result.errorMessage(), "specific runtime error message");
}

TEST_F(BasicResultVoidTest_1067, LogicErrorWithEmptyMessage_1067) {
    auto result = BasicResult<void>::logicError("");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), "");
}

TEST_F(BasicResultVoidTest_1067, RuntimeErrorWithEmptyMessage_1067) {
    auto result = BasicResult<void>::runtimeError("");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), "");
}

// ============================================================
// Tests for BasicResult<int>
// ============================================================

class BasicResultIntTest_1067 : public ::testing::Test {};

TEST_F(BasicResultIntTest_1067, OkWithValueReturnsTrue_1067) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(BasicResultIntTest_1067, OkWithValueHasTypeOk_1067) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultIntTest_1067, OkWithValueHasEmptyErrorMessage_1067) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultIntTest_1067, LogicErrorReturnsFalse_1067) {
    auto result = BasicResult<int>::logicError("int logic error");
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultIntTest_1067, LogicErrorHasCorrectType_1067) {
    auto result = BasicResult<int>::logicError("int logic error");
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

TEST_F(BasicResultIntTest_1067, LogicErrorPreservesMessage_1067) {
    auto result = BasicResult<int>::logicError("int logic error");
    EXPECT_EQ(result.errorMessage(), "int logic error");
}

TEST_F(BasicResultIntTest_1067, RuntimeErrorReturnsFalse_1067) {
    auto result = BasicResult<int>::runtimeError("int runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(BasicResultIntTest_1067, RuntimeErrorHasCorrectType_1067) {
    auto result = BasicResult<int>::runtimeError("int runtime error");
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultIntTest_1067, RuntimeErrorPreservesMessage_1067) {
    auto result = BasicResult<int>::runtimeError("int runtime error");
    EXPECT_EQ(result.errorMessage(), "int runtime error");
}

TEST_F(BasicResultIntTest_1067, OkWithZeroValue_1067) {
    auto result = BasicResult<int>::ok(0);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultIntTest_1067, OkWithNegativeValue_1067) {
    auto result = BasicResult<int>::ok(-1);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

// ============================================================
// Tests for BasicResult<std::string>
// ============================================================

class BasicResultStringTest_1067 : public ::testing::Test {};

TEST_F(BasicResultStringTest_1067, OkWithStringValue_1067) {
    auto result = BasicResult<std::string>::ok(std::string("hello"));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultStringTest_1067, LogicErrorWithStringType_1067) {
    auto result = BasicResult<std::string>::logicError("string logic error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), "string logic error");
}

TEST_F(BasicResultStringTest_1067, RuntimeErrorWithStringType_1067) {
    auto result = BasicResult<std::string>::runtimeError("string runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), "string runtime error");
}

// ============================================================
// Tests for copy construction between different BasicResult types
// ============================================================

class BasicResultCopyTest_1067 : public ::testing::Test {};

TEST_F(BasicResultCopyTest_1067, CopyFromIntToVoidOk_1067) {
    auto intResult = BasicResult<int>::ok(42);
    BasicResult<void> voidResult(intResult);
    EXPECT_TRUE(static_cast<bool>(voidResult));
    EXPECT_EQ(voidResult.type(), ResultType::Ok);
}

TEST_F(BasicResultCopyTest_1067, CopyFromIntToVoidLogicError_1067) {
    auto intResult = BasicResult<int>::logicError("cross-type logic error");
    BasicResult<void> voidResult(intResult);
    EXPECT_FALSE(static_cast<bool>(voidResult));
    EXPECT_EQ(voidResult.type(), ResultType::LogicError);
    EXPECT_EQ(voidResult.errorMessage(), "cross-type logic error");
}

TEST_F(BasicResultCopyTest_1067, CopyFromIntToVoidRuntimeError_1067) {
    auto intResult = BasicResult<int>::runtimeError("cross-type runtime error");
    BasicResult<void> voidResult(intResult);
    EXPECT_FALSE(static_cast<bool>(voidResult));
    EXPECT_EQ(voidResult.type(), ResultType::RuntimeError);
    EXPECT_EQ(voidResult.errorMessage(), "cross-type runtime error");
}

// ============================================================
// Tests for long error messages (boundary-like)
// ============================================================

class BasicResultBoundaryTest_1067 : public ::testing::Test {};

TEST_F(BasicResultBoundaryTest_1067, LogicErrorWithVeryLongMessage_1067) {
    std::string longMessage(10000, 'x');
    auto result = BasicResult<void>::logicError(std::string(longMessage));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), longMessage);
}

TEST_F(BasicResultBoundaryTest_1067, RuntimeErrorWithVeryLongMessage_1067) {
    std::string longMessage(10000, 'y');
    auto result = BasicResult<void>::runtimeError(std::string(longMessage));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), longMessage);
}

TEST_F(BasicResultBoundaryTest_1067, ErrorMessageWithSpecialCharacters_1067) {
    std::string specialMessage = "Error: \n\t\r\0 special chars!";
    auto result = BasicResult<void>::logicError(std::string(specialMessage));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), specialMessage);
}

// ============================================================
// Tests for ResultType enum values
// ============================================================

class ResultTypeTest_1067 : public ::testing::Test {};

TEST_F(ResultTypeTest_1067, EnumValuesAreDistinct_1067) {
    EXPECT_NE(ResultType::Ok, ResultType::LogicError);
    EXPECT_NE(ResultType::Ok, ResultType::RuntimeError);
    EXPECT_NE(ResultType::LogicError, ResultType::RuntimeError);
}

TEST_F(ResultTypeTest_1067, OkIsZero_1067) {
    EXPECT_EQ(static_cast<int>(ResultType::Ok), 0);
}

TEST_F(ResultTypeTest_1067, LogicErrorIsOne_1067) {
    EXPECT_EQ(static_cast<int>(ResultType::LogicError), 1);
}

TEST_F(ResultTypeTest_1067, RuntimeErrorIsTwo_1067) {
    EXPECT_EQ(static_cast<int>(ResultType::RuntimeError), 2);
}
