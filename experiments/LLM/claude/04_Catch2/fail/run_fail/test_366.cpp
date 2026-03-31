#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>

namespace {

using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

// Use the void specialization (BasicResult<void>) for testing since
// the partial code shows logicError as a static method returning BasicResult
// We test with the default template parameter.

class BasicResultTest_366 : public ::testing::Test {
protected:
    // Helper type alias - using void specialization
    using Result = BasicResult<void>;
};

// --- Normal Operation Tests ---

TEST_F(BasicResultTest_366, OkReturnsSuccessResult_366) {
    auto result = Result::ok();
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultTest_366, LogicErrorReturnsLogicErrorResult_366) {
    auto result = Result::logicError(std::string("some logic error"));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), "some logic error");
}

TEST_F(BasicResultTest_366, RuntimeErrorReturnsRuntimeErrorResult_366) {
    auto result = Result::runtimeError(std::string("some runtime error"));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), "some runtime error");
}

// --- Boundary Conditions ---

TEST_F(BasicResultTest_366, LogicErrorWithEmptyMessage_366) {
    auto result = Result::logicError(std::string(""));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), "");
}

TEST_F(BasicResultTest_366, RuntimeErrorWithEmptyMessage_366) {
    auto result = Result::runtimeError(std::string(""));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), "");
}

TEST_F(BasicResultTest_366, LogicErrorWithLongMessage_366) {
    std::string longMessage(10000, 'x');
    auto result = Result::logicError(std::string(longMessage));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), longMessage);
}

TEST_F(BasicResultTest_366, RuntimeErrorWithLongMessage_366) {
    std::string longMessage(10000, 'y');
    auto result = Result::runtimeError(std::string(longMessage));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), longMessage);
}

// --- Bool Conversion Tests ---

TEST_F(BasicResultTest_366, OkResultConvertsToBoolTrue_366) {
    auto result = Result::ok();
    EXPECT_TRUE(result);
}

TEST_F(BasicResultTest_366, LogicErrorConvertsToBoolFalse_366) {
    auto result = Result::logicError(std::string("error"));
    EXPECT_FALSE(result);
}

TEST_F(BasicResultTest_366, RuntimeErrorConvertsToBoolFalse_366) {
    auto result = Result::runtimeError(std::string("error"));
    EXPECT_FALSE(result);
}

// --- Ok Result Error Message ---

TEST_F(BasicResultTest_366, OkResultHasEmptyErrorMessage_366) {
    auto result = Result::ok();
    EXPECT_TRUE(result.errorMessage().empty());
}

// --- Copy Construction from Different Specialization ---

TEST_F(BasicResultTest_366, CopyConstructFromOtherBasicResultType_366) {
    auto intResult = BasicResult<int>::ok(42);
    BasicResult<void> voidResult(intResult);
    EXPECT_TRUE(static_cast<bool>(voidResult));
    EXPECT_EQ(voidResult.type(), ResultType::Ok);
}

TEST_F(BasicResultTest_366, CopyConstructFromErrorResult_366) {
    auto intResult = BasicResult<int>::logicError(std::string("int error"));
    BasicResult<void> voidResult(intResult);
    EXPECT_FALSE(static_cast<bool>(voidResult));
    EXPECT_EQ(voidResult.type(), ResultType::LogicError);
    EXPECT_EQ(voidResult.errorMessage(), "int error");
}

// --- Ok with Value Tests ---

TEST_F(BasicResultTest_366, OkWithValueReturnsSuccessResult_366) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultTest_366, LogicErrorWithSpecialCharactersInMessage_366) {
    std::string specialMessage = "Error: \n\t\"special\" chars <>&'\\";
    auto result = Result::logicError(std::string(specialMessage));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), specialMessage);
}

TEST_F(BasicResultTest_366, RuntimeErrorWithSpecialCharactersInMessage_366) {
    std::string specialMessage = "Runtime: \0embedded\0nulls";
    // Note: string constructed from literal won't include embedded nulls with this syntax
    // but the message should still match what was passed
    auto result = Result::runtimeError(std::string("Runtime error with unicode: ñ ü ö"));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "Runtime error with unicode: ñ ü ö");
}

// --- Multiple Results Independence ---

TEST_F(BasicResultTest_366, MultipleResultsAreIndependent_366) {
    auto ok = Result::ok();
    auto logic = Result::logicError(std::string("logic"));
    auto runtime = Result::runtimeError(std::string("runtime"));

    EXPECT_TRUE(static_cast<bool>(ok));
    EXPECT_FALSE(static_cast<bool>(logic));
    EXPECT_FALSE(static_cast<bool>(runtime));

    EXPECT_EQ(ok.type(), ResultType::Ok);
    EXPECT_EQ(logic.type(), ResultType::LogicError);
    EXPECT_EQ(runtime.type(), ResultType::RuntimeError);

    EXPECT_TRUE(ok.errorMessage().empty());
    EXPECT_EQ(logic.errorMessage(), "logic");
    EXPECT_EQ(runtime.errorMessage(), "runtime");
}

} // namespace
