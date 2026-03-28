// File: tests/clara_resultvaluebase_move_ctor_1065.cpp
#include <gtest/gtest.h>

// Include Clara internal header from Catch2 used in your codebase
#include "catch2/internal/catch_clara.hpp"

#include <memory>
#include <string>
#include <vector>

namespace {
using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

class ClaraResultValueBaseTest_1065 : public ::testing::Test {};
} // namespace

// [Normal] rvalue string is stored; result is Ok
TEST_F(ClaraResultValueBaseTest_1065, RValueStringStoredAndOk_1065) {
    BasicResult<std::string> res{ ResultType::Ok, std::string("hello") };

    // Observable behavior: success + stored value available
    EXPECT_TRUE(static_cast<bool>(res));                 // operator bool -> Ok
    EXPECT_EQ(res.type(), ResultType::Ok);               // type() is Ok
    EXPECT_EQ(res.value(), "hello");                     // value() matches
}

// [Boundary] move-only type: ensure move construction is supported
TEST_F(ClaraResultValueBaseTest_1065, MoveOnlyTypeConstructs_1065) {
    auto up = std::make_unique<int>(42);
    BasicResult<std::unique_ptr<int>> res{ ResultType::Ok, std::move(up) };

    ASSERT_TRUE(static_cast<bool>(res));
    ASSERT_NE(res.value(), nullptr);
    EXPECT_EQ(*res.value(), 42);

    // After move, source unique_ptr should be empty (property of unique_ptr)
    EXPECT_EQ(up.get(), nullptr);
}

// [Boundary] large value: ensure placement-new handles non-trivial size
TEST_F(ClaraResultValueBaseTest_1065, LargeVectorValueStored_1065) {
    std::vector<int> big(10000, 7);
    BasicResult<std::vector<int>> res{ ResultType::Ok, std::move(big) };

    EXPECT_TRUE(static_cast<bool>(res));
    const auto& v = res.value();
    ASSERT_EQ(v.size(), 10000u);
    EXPECT_EQ(v.front(), 7);
    EXPECT_EQ(v.back(), 7);
}

// [Behavioral quirk under test] First parameter is ignored for rvalue ctor;
// even if a non-Ok is passed, constructor forces Ok (per provided snippet).
TEST_F(ClaraResultValueBaseTest_1065, NonOkTagStillResultsInOkWhenConstructedWithValue_1065) {
    BasicResult<std::string> res{ ResultType::RuntimeError, std::string("x") };

    // Observable state: result reports Ok and value is accessible
    EXPECT_TRUE(static_cast<bool>(res));
    EXPECT_EQ(res.type(), ResultType::Ok);
    EXPECT_EQ(res.value(), "x");
}
