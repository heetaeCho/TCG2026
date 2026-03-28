// File: tests/basic_result_ok_365_test.cpp
#include <gtest/gtest.h>

// Include the header that declares Catch::Clara::Detail::BasicResult and ResultType
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace {
using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

// A simple test fixture for organization (name includes TEST_ID 365)
class BasicResultTest_365 : public ::testing::Test {};
} // namespace

// [Normal operation] ok() yields an "Ok" result.
TEST_F(BasicResultTest_365, OkReturnsOkType_365) {
    auto r = BasicResult::ok();

    // Observable behavior checks (treat as black box):
    // If operator bool() is available, it should evaluate to true for Ok results.
    // If type() is available, it should equal ResultType::Ok.
    // If errorMessage() is available, it should be empty for Ok results.
    // We guard each check with if constexpr-style pattern via SFINAE would be overkill here,
    // so we directly call the commonly available interface as per the provided dependencies.

    // Truthiness (explicit operator bool)
    EXPECT_TRUE(static_cast<bool>(r));

    // Type should be Ok
    EXPECT_EQ(r.type(), ResultType::Ok);

    // Error message should be empty for successful result
    EXPECT_TRUE(r.errorMessage().empty());
}

// [Boundary/basic repeatability] Multiple ok() calls are consistent and independent.
TEST_F(BasicResultTest_365, MultipleOkResultsAreIndependentAndOk_365) {
    auto r1 = BasicResult::ok();
    auto r2 = BasicResult::ok();

    EXPECT_TRUE(static_cast<bool>(r1));
    EXPECT_TRUE(static_cast<bool>(r2));
    EXPECT_EQ(r1.type(), ResultType::Ok);
    EXPECT_EQ(r2.type(), ResultType::Ok);
    EXPECT_TRUE(r1.errorMessage().empty());
    EXPECT_TRUE(r2.errorMessage().empty());
}

// [Copy semantics] Copy-constructing preserves the observable Ok state.
TEST_F(BasicResultTest_365, CopyConstructionPreservesOk_365) {
    const auto original = BasicResult::ok();
    auto copy = original;  // copy-construct

    EXPECT_TRUE(static_cast<bool>(copy));
    EXPECT_EQ(copy.type(), ResultType::Ok);
    EXPECT_TRUE(copy.errorMessage().empty());

    // Original remains unchanged/valid
    EXPECT_TRUE(static_cast<bool>(original));
    EXPECT_EQ(original.type(), ResultType::Ok);
    EXPECT_TRUE(original.errorMessage().empty());
}

// [Move semantics] Move-constructing preserves the observable Ok state in the target.
TEST_F(BasicResultTest_365, MoveConstructionPreservesOk_365) {
    auto make_ok = [] { return BasicResult::ok(); };

    auto moved = std::move(make_ok());  // move-construct from a temporary

    EXPECT_TRUE(static_cast<bool>(moved));
    EXPECT_EQ(moved.type(), ResultType::Ok);
    EXPECT_TRUE(moved.errorMessage().empty());
}

// [Exception safety] ok() should not throw.
TEST_F(BasicResultTest_365, OkIsNoThrow_365) {
    EXPECT_NO_THROW({
        auto r = BasicResult::ok();
        (void)r;
    });
}
