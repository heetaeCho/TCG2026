// File: tests/BasicResult_1067_tests.cpp

#include <gtest/gtest.h>
#include <string>

// Include the header under test (adjust the relative path if your tree differs)
#include "Catch2/src/catch2/internal/catch_clara.hpp"

using Catch::Clara::Detail::BasicResult;
using Catch::Clara::Detail::ResultType;

namespace {

// A simple fixture (kept empty for clarity/consistency if you want to expand later)
class BasicResultTest_1067 : public ::testing::Test {};

} // namespace

// Normal operation: logicError factory should set type, store message, and convert to false.
TEST_F(BasicResultTest_1067, LogicError_SetsTypeMessageAndBool_1067) {
    auto r = BasicResult<int>::logicError(std::string{"boom"});
    EXPECT_EQ(r.type(), ResultType::LogicError);
    EXPECT_EQ(r.errorMessage(), "boom");
    EXPECT_FALSE(static_cast<bool>(r));
}

// Normal operation: runtimeError factory should set type, store message, and convert to false.
TEST_F(BasicResultTest_1067, RuntimeError_SetsTypeMessageAndBool_1067) {
    auto r = BasicResult<int>::runtimeError(std::string{"kaboom"});
    EXPECT_EQ(r.type(), ResultType::RuntimeError);
    EXPECT_EQ(r.errorMessage(), "kaboom");
    EXPECT_FALSE(static_cast<bool>(r));
}

// Normal operation: ok(value) should represent success and convert to true.
// We do not assert on stored value (the interface shown does not expose it).
TEST_F(BasicResultTest_1067, OkWithValue_IsSuccessful_1067) {
    auto r = BasicResult<int>::ok(42);
    EXPECT_EQ(r.type(), ResultType::Ok);
    EXPECT_TRUE(static_cast<bool>(r));
    // No assumptions about value retrieval since it's not part of the provided interface snippet.
}

// Boundary condition: empty error message should be preserved as-is.
TEST_F(BasicResultTest_1067, EmptyErrorMessage_Preserved_1067) {
    auto r1 = BasicResult<int>::logicError(std::string{""});
    EXPECT_EQ(r1.type(), ResultType::LogicError);
    EXPECT_TRUE(r1.errorMessage().empty());
    EXPECT_FALSE(static_cast<bool>(r1));

    auto r2 = BasicResult<int>::runtimeError(std::string{""});
    EXPECT_EQ(r2.type(), ResultType::RuntimeError);
    EXPECT_TRUE(r2.errorMessage().empty());
    EXPECT_FALSE(static_cast<bool>(r2));
}

// Boundary condition: very long error message should be preserved intact.
TEST_F(BasicResultTest_1067, VeryLongErrorMessage_Preserved_1067) {
    std::string longMsg(5000, 'x'); // 5k chars
    auto r = BasicResult<int>::logicError(std::move(longMsg));
    EXPECT_EQ(r.type(), ResultType::LogicError);
    EXPECT_EQ(r.errorMessage().size(), 5000u);
    EXPECT_TRUE(std::all_of(r.errorMessage().begin(), r.errorMessage().end(),
                            [](char c){ return c == 'x'; }));
    EXPECT_FALSE(static_cast<bool>(r));
}

// Cross-type copy construction: constructing BasicResult<T2> from BasicResult<T1>
// should preserve the observable status and message.
TEST_F(BasicResultTest_1067, CrossTypeCopyConstruction_PreservesTypeAndMessage_1067) {
    auto source = BasicResult<int>::logicError(std::string{"copy-me"});
    // The interface advertises: template <typename U> explicit BasicResult(BasicResult<U> const& other)
    BasicResult<std::string> dest{source};

    EXPECT_EQ(dest.type(), ResultType::LogicError);
    EXPECT_EQ(dest.errorMessage(), "copy-me");
    EXPECT_FALSE(static_cast<bool>(dest));
}

// Sanity check across factories: Ok vs Error conversions to bool and types are consistent.
TEST_F(BasicResultTest_1067, BoolConversionAndTypeConsistency_1067) {
    auto okRes = BasicResult<int>::ok(1);
    auto logicErr = BasicResult<int>::logicError(std::string{"e1"});
    auto runtimeErr = BasicResult<int>::runtimeError(std::string{"e2"});

    EXPECT_TRUE(static_cast<bool>(okRes));
    EXPECT_EQ(okRes.type(), ResultType::Ok);

    EXPECT_FALSE(static_cast<bool>(logicErr));
    EXPECT_EQ(logicErr.type(), ResultType::LogicError);

    EXPECT_FALSE(static_cast<bool>(runtimeErr));
    EXPECT_EQ(runtimeErr.type(), ResultType::RuntimeError);
}

