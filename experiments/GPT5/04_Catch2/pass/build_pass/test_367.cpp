// BasicResult_runtimeError_tests_367.cpp
#include <gtest/gtest.h>
#include <string>

// Include the header under test (path based on prompt)
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

//
// Tests
//

// Verifies that runtimeError sets the result type to ResultType::RuntimeError.
TEST(BasicResultRuntimeErrorTest_367, ReturnsRuntimeErrorType_367) {
    auto res = BasicResult<int>::runtimeError(std::string("boom"));
    EXPECT_EQ(res.type(), ResultType::RuntimeError);
}

// Verifies that a runtime error evaluates to false in boolean context.
TEST(BasicResultRuntimeErrorTest_367, IsFalseInBooleanContext_367) {
    auto res = BasicResult<int>::runtimeError(std::string("err"));
    EXPECT_FALSE(static_cast<bool>(res));
}

// Verifies the error message is preserved and retrievable via errorMessage().
TEST(BasicResultRuntimeErrorTest_367, PreservesErrorMessage_367) {
    std::string msg = "something went wrong";
    auto res = BasicResult<int>::runtimeError(std::string(msg)); // pass rvalue per interface
    EXPECT_EQ(res.errorMessage(), msg);
}

// Verifies behavior with an empty error message (boundary condition).
TEST(BasicResultRuntimeErrorTest_367, AllowsEmptyMessage_367) {
    auto res = BasicResult<int>::runtimeError(std::string{});
    EXPECT_EQ(res.type(), ResultType::RuntimeError);
    EXPECT_TRUE(res.errorMessage().empty());
    EXPECT_FALSE(static_cast<bool>(res));
}

// Verifies cross-type copying via the templated copy constructor preserves observable state.
TEST(BasicResultRuntimeErrorTest_367, CrossTypeCopyPreservesState_367) {
    auto src = BasicResult<int>::runtimeError(std::string("bad thing"));
    BasicResult<std::string> dst(src);  // copy from different BasicResult<U>

    EXPECT_EQ(dst.type(), ResultType::RuntimeError);
    EXPECT_EQ(dst.errorMessage(), "bad thing");
    EXPECT_FALSE(static_cast<bool>(dst));
}
