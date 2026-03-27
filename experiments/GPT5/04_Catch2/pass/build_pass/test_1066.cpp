// File: tests/basic_result_converting_ctor_1066.tests.cpp

#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace {
using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

template <typename T>
static std::string TypeName(); // (not used; avoid RTTI reliance)
} // namespace

// Fixture kept minimal to avoid any internal/state coupling
class BasicResultConvertingCtorTest_1066 : public ::testing::Test {};

// [Normal] Converting from a LogicError result preserves the error type and message.
TEST_F(BasicResultConvertingCtorTest_1066, Convert_LogicError_PreservesTypeAndMessage_1066) {
    // Source error with one T
    auto src = BasicResult<int>::logicError(std::string("bad argument"));

    // Convert to a different T via the explicit converting ctor
    BasicResult<std::string> dst{src};

    // Observable behavior checks
    EXPECT_EQ(dst.type(), ResultType::LogicError);
    EXPECT_FALSE(static_cast<bool>(dst)); // error results are expected to be "false"
    EXPECT_EQ(dst.errorMessage(), std::string("bad argument"));
}

// [Normal] Converting from a RuntimeError result preserves the error type and message.
TEST_F(BasicResultConvertingCtorTest_1066, Convert_RuntimeError_PreservesTypeAndMessage_1066) {
    auto src = BasicResult<double>::runtimeError(std::string("IO failure"));

    BasicResult<long> dst{src};

    EXPECT_EQ(dst.type(), ResultType::RuntimeError);
    EXPECT_FALSE(static_cast<bool>(dst));
    EXPECT_EQ(dst.errorMessage(), std::string("IO failure"));
}

// [Boundary] Empty error message remains unchanged through conversion.
TEST_F(BasicResultConvertingCtorTest_1066, Convert_EmptyMessage_Preserved_1066) {
    auto src = BasicResult<int>::runtimeError(std::string{});

    BasicResult<unsigned> dst{src};

    EXPECT_EQ(dst.type(), ResultType::RuntimeError);
    EXPECT_FALSE(static_cast<bool>(dst));
    EXPECT_TRUE(dst.errorMessage().empty());
}

// [Interaction/Non-mutation] Converting does not modify the source result’s observable state.
TEST_F(BasicResultConvertingCtorTest_1066, Convert_DoesNotModifySource_1066) {
    auto src = BasicResult<int>::logicError(std::string("original"));

    // Keep a copy of the source's observable state
    const auto srcTypeBefore = src.type();
    const auto srcMsgBefore  = src.errorMessage();
    const auto srcBoolBefore = static_cast<bool>(src);

    // Perform conversion
    BasicResult<char> dst{src};

    // Destination correctness
    EXPECT_EQ(dst.type(), ResultType::LogicError);
    EXPECT_FALSE(static_cast<bool>(dst));
    EXPECT_EQ(dst.errorMessage(), std::string("original"));

    // Source unchanged
    EXPECT_EQ(src.type(), srcTypeBefore);
    EXPECT_EQ(src.errorMessage(), srcMsgBefore);
    EXPECT_EQ(static_cast<bool>(src), srcBoolBefore);
}

/*
NOTE (intentionally not executed):
The provided partial implementation asserts that the converting constructor
is not used for Ok results. Because that assertion is not an observable behavior
we can portably check in a unit test without depending on build mode, we do not
create a test that converts from an Ok result (it could abort in debug builds).
If desired for documentation, a disabled test can be added:

TEST_F(BasicResultConvertingCtorTest_1066, DISABLED_Convert_FromOk_IsNotSupported_1066) {
    auto okSrc = BasicResult<int>::ok();
    // BasicResult<float> dst{okSrc}; // Could trigger an assert in debug builds
}

This keeps the suite fully black-box and stable across build configurations.
*/
