// File: tests/basic_result_error_message_370_tests.cpp

#include <gtest/gtest.h>

// Include the provided interface header
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Detail::BasicResult;

//
// Test fixture kept minimal; we treat BasicResult as a black box.
//
class BasicResultErrorMessageTest_370 : public ::testing::Test {};

// [Normal] errorMessage() should be empty (or at least not crash) for an OK result constructed via ok().
TEST_F(BasicResultErrorMessageTest_370, ErrorMessageEmptyForOk_370) {
    // We avoid inferring internal logic; we only check observable return.
    auto okRes = BasicResult<void>::ok();
    // The interface promises a const& to a string. It should be a valid reference.
    const std::string& msg = okRes.errorMessage();
    // For a successful/OK result, message is expected to be empty by convention.
    // If the implementation chose a non-empty value, this still verifies the accessor’s stability
    // and compares against the most conventional expectation.
    EXPECT_TRUE(msg.empty());
}

// [Normal] errorMessage() should expose the provided message for logicError().
TEST_F(BasicResultErrorMessageTest_370, ErrorMessageMatchesLogicError_370) {
    const char* kText = "logic blew up";
    auto res = BasicResult<int>::logicError(std::string{kText});
    EXPECT_EQ(res.errorMessage(), kText);
}

// [Normal] errorMessage() should expose the provided message for runtimeError().
TEST_F(BasicResultErrorMessageTest_370, ErrorMessageMatchesRuntimeError_370) {
    std::string provided = "runtime exploded";
    auto res = BasicResult<void>::runtimeError(std::move(provided));
    // Even though we moved-from `provided`, we only assert observable behavior of the result’s message.
    EXPECT_EQ(res.errorMessage(), "runtime exploded");
}

// [Boundary] Passing a long message should be retrievable intact via errorMessage().
TEST_F(BasicResultErrorMessageTest_370, ErrorMessagePreservesLongInput_370) {
    std::string longMsg(4096, 'x'); // long but reasonable boundary
    auto res = BasicResult<void>::logicError(std::move(longMsg));
    EXPECT_EQ(res.errorMessage().size(), 4096u);
    EXPECT_TRUE(std::all_of(res.errorMessage().begin(), res.errorMessage().end(),
                            [](char c){ return c == 'x'; }));
}

// [Boundary] Passing an empty string still yields a valid reference and an empty message.
TEST_F(BasicResultErrorMessageTest_370, ErrorMessageHandlesEmptyInput_370) {
    auto res = BasicResult<int>::runtimeError(std::string{});
    const std::string& ref = res.errorMessage();
    EXPECT_TRUE(ref.empty());
}

// [Behavior] errorMessage() returns a const reference; repeated calls should reference the same string object.
TEST_F(BasicResultErrorMessageTest_370, ErrorMessageIsStableConstRef_370) {
    auto res = BasicResult<void>::logicError(std::string{"A message"});
    const std::string& a = res.errorMessage();
    const std::string& b = res.errorMessage();
    // Same address indicates the same referenced object (observable via public API).
    EXPECT_EQ(&a, &b);
    EXPECT_EQ(a, "A message");
}

// [Inter-type Copy] Copy-constructing BasicResult<T> from BasicResult<U> should preserve the observable message.
TEST_F(BasicResultErrorMessageTest_370, ErrorMessagePreservedAcrossConvertingCopy_370) {
    auto from = BasicResult<void>::logicError(std::string{"x-type to y-type"});
    BasicResult<int> to(from);  // uses the templated converting copy-ctor per the provided interface
    EXPECT_EQ(to.errorMessage(), "x-type to y-type");
}

// [Robustness] Ensure rvalue temporary message survives into the result (lifetime test via observable behavior).
TEST_F(BasicResultErrorMessageTest_370, ErrorMessageFromTemporaryString_370) {
    auto res = BasicResult<void>::logicError(std::string("temp message"));
    EXPECT_EQ(res.errorMessage(), "temp message");
}
