// File: test_basicresult_logicerror_366.cpp
#include <gtest/gtest.h>
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace {
using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

class BasicResultTest_366 : public ::testing::Test {};
} // namespace

// Verifies that logicError sets the result type to LogicError and keeps the message as provided.
TEST_F(BasicResultTest_366, LogicError_SetsTypeAndMessage_366) {
    std::string msg = "invalid flag '--foo'";
    auto r = BasicResult::logicError(std::move(msg));

    // Observable behavior via public interface
    EXPECT_EQ(r.type(), ResultType::LogicError);
    EXPECT_EQ(r.errorMessage(), std::string("invalid flag '--foo'"));
}

// Verifies that an empty message is accepted and preserved.
TEST_F(BasicResultTest_366, LogicError_AllowsEmptyMessage_366) {
    std::string empty;
    auto r = BasicResult::logicError(std::move(empty));

    EXPECT_EQ(r.type(), ResultType::LogicError);
    EXPECT_TRUE(r.errorMessage().empty());
}

// Verifies that the boolean conversion reflects an error state (i.e., not "ok").
TEST_F(BasicResultTest_366, LogicError_IsFalseInBooleanContext_366) {
    auto r = BasicResult::logicError(std::string{"boom"});
    // By convention, only Ok should convert to true; errors should be false.
    EXPECT_FALSE(static_cast<bool>(r));
}

// Verifies behavior with a large error message (boundary-ish condition).
TEST_F(BasicResultTest_366, LogicError_PreservesLargeMessage_366) {
    const std::size_t N = 10000;
    std::string big(N, 'x');
    auto r = BasicResult::logicError(std::move(big));

    EXPECT_EQ(r.type(), ResultType::LogicError);
    ASSERT_EQ(r.errorMessage().size(), N);
    // Spot-check prefix/suffix to ensure content integrity via observable interface
    EXPECT_EQ(r.errorMessage().substr(0, 3), "xxx");
    EXPECT_EQ(r.errorMessage().substr(N - 3, 3), "xxx");
}
