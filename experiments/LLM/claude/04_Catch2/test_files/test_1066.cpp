#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>

// Access the relevant namespaces
using namespace Catch::Clara::Detail;

// ============================================================
// Tests for BasicResult<void>
// ============================================================

class BasicResultVoidTest_1066 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(BasicResultVoidTest_1066, OkReturnsSuccessResult_1066) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultVoidTest_1066, LogicErrorReturnsFalse_1066) {
    auto result = BasicResult<void>::logicError("some logic error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
}

TEST_F(BasicResultVoidTest_1066, LogicErrorPreservesMessage_1066) {
    auto result = BasicResult<void>::logicError("logic error message");
    EXPECT_EQ(result.errorMessage(), "logic error message");
}

TEST_F(BasicResultVoidTest_1066, RuntimeErrorReturnsFalse_1066) {
    auto result = BasicResult<void>::runtimeError("some runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultVoidTest_1066, RuntimeErrorPreservesMessage_1066) {
    auto result = BasicResult<void>::runtimeError("runtime error message");
    EXPECT_EQ(result.errorMessage(), "runtime error message");
}

TEST_F(BasicResultVoidTest_1066, OkResultHasEmptyErrorMessage_1066) {
    auto result = BasicResult<void>::ok();
    EXPECT_TRUE(result.errorMessage().empty());
}

TEST_F(BasicResultVoidTest_1066, LogicErrorWithEmptyMessage_1066) {
    auto result = BasicResult<void>::logicError("");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), "");
}

TEST_F(BasicResultVoidTest_1066, RuntimeErrorWithEmptyMessage_1066) {
    auto result = BasicResult<void>::runtimeError("");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), "");
}

// ============================================================
// Tests for BasicResult<T> with a value type
// ============================================================

class BasicResultIntTest_1066 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(BasicResultIntTest_1066, OkWithValueReturnsSuccess_1066) {
    auto result = BasicResult<int>::ok(42);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultIntTest_1066, LogicErrorReturnsFalse_1066) {
    auto result = BasicResult<int>::logicError("int logic error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), "int logic error");
}

TEST_F(BasicResultIntTest_1066, RuntimeErrorReturnsFalse_1066) {
    auto result = BasicResult<int>::runtimeError("int runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), "int runtime error");
}

TEST_F(BasicResultIntTest_1066, OkWithZeroValue_1066) {
    auto result = BasicResult<int>::ok(0);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultIntTest_1066, OkWithNegativeValue_1066) {
    auto result = BasicResult<int>::ok(-1);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

// ============================================================
// Tests for cross-type construction (converting constructor)
// ============================================================

class BasicResultConvertTest_1066 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(BasicResultConvertTest_1066, ConvertLogicErrorFromIntToVoid_1066) {
    auto intResult = BasicResult<int>::logicError("convert logic error");
    BasicResult<void> voidResult(intResult);
    EXPECT_FALSE(static_cast<bool>(voidResult));
    EXPECT_EQ(voidResult.type(), ResultType::LogicError);
    EXPECT_EQ(voidResult.errorMessage(), "convert logic error");
}

TEST_F(BasicResultConvertTest_1066, ConvertRuntimeErrorFromIntToVoid_1066) {
    auto intResult = BasicResult<int>::runtimeError("convert runtime error");
    BasicResult<void> voidResult(intResult);
    EXPECT_FALSE(static_cast<bool>(voidResult));
    EXPECT_EQ(voidResult.type(), ResultType::RuntimeError);
    EXPECT_EQ(voidResult.errorMessage(), "convert runtime error");
}

TEST_F(BasicResultConvertTest_1066, ConvertLogicErrorFromVoidToInt_1066) {
    auto voidResult = BasicResult<void>::logicError("void to int logic");
    BasicResult<int> intResult(voidResult);
    EXPECT_FALSE(static_cast<bool>(intResult));
    EXPECT_EQ(intResult.type(), ResultType::LogicError);
    EXPECT_EQ(intResult.errorMessage(), "void to int logic");
}

TEST_F(BasicResultConvertTest_1066, ConvertRuntimeErrorFromVoidToInt_1066) {
    auto voidResult = BasicResult<void>::runtimeError("void to int runtime");
    BasicResult<int> intResult(voidResult);
    EXPECT_FALSE(static_cast<bool>(intResult));
    EXPECT_EQ(intResult.type(), ResultType::RuntimeError);
    EXPECT_EQ(intResult.errorMessage(), "void to int runtime");
}

// ============================================================
// Tests for BasicResult with string type
// ============================================================

class BasicResultStringTest_1066 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(BasicResultStringTest_1066, OkWithStringValue_1066) {
    auto result = BasicResult<std::string>::ok(std::string("hello"));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::Ok);
}

TEST_F(BasicResultStringTest_1066, LogicErrorWithStringType_1066) {
    auto result = BasicResult<std::string>::logicError("string logic error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::LogicError);
    EXPECT_EQ(result.errorMessage(), "string logic error");
}

TEST_F(BasicResultStringTest_1066, RuntimeErrorWithStringType_1066) {
    auto result = BasicResult<std::string>::runtimeError("string runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
    EXPECT_EQ(result.errorMessage(), "string runtime error");
}

// ============================================================
// Tests for ResultType enum values
// ============================================================

class ResultTypeTest_1066 : public ::testing::Test {};

TEST_F(ResultTypeTest_1066, EnumValuesAreCorrect_1066) {
    EXPECT_EQ(static_cast<int>(ResultType::Ok), 0);
    EXPECT_EQ(static_cast<int>(ResultType::LogicError), 1);
    EXPECT_EQ(static_cast<int>(ResultType::RuntimeError), 2);
}

// ============================================================
// Boundary / edge case tests
// ============================================================

class BasicResultEdgeCaseTest_1066 : public ::testing::Test {};

TEST_F(BasicResultEdgeCaseTest_1066, LogicErrorWithLongMessage_1066) {
    std::string longMsg(10000, 'x');
    auto result = BasicResult<void>::logicError(std::string(longMsg));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), longMsg);
    EXPECT_EQ(result.errorMessage().size(), 10000u);
}

TEST_F(BasicResultEdgeCaseTest_1066, RuntimeErrorWithSpecialCharacters_1066) {
    std::string specialMsg = "Error: \n\t\r\0 special chars";
    auto result = BasicResult<void>::runtimeError(std::string(specialMsg));
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultEdgeCaseTest_1066, MultipleOkCallsAreIndependent_1066) {
    auto r1 = BasicResult<void>::ok();
    auto r2 = BasicResult<void>::ok();
    EXPECT_TRUE(static_cast<bool>(r1));
    EXPECT_TRUE(static_cast<bool>(r2));
}

TEST_F(BasicResultEdgeCaseTest_1066, MultipleErrorCallsAreIndependent_1066) {
    auto r1 = BasicResult<void>::logicError("error1");
    auto r2 = BasicResult<void>::runtimeError("error2");
    EXPECT_EQ(r1.errorMessage(), "error1");
    EXPECT_EQ(r2.errorMessage(), "error2");
    EXPECT_EQ(r1.type(), ResultType::LogicError);
    EXPECT_EQ(r2.type(), ResultType::RuntimeError);
}

TEST_F(BasicResultEdgeCaseTest_1066, ConvertErrorPreservesExactMessage_1066) {
    std::string msg = "  whitespace  message  ";
    auto original = BasicResult<int>::logicError(std::string(msg));
    BasicResult<void> converted(original);
    EXPECT_EQ(converted.errorMessage(), msg);
}
