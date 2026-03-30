// File: assertion_result_succeeded_tests_291.cpp

#include <gtest/gtest.h>
#include "catch2/catch_assertion_result.hpp"

// These tests treat AssertionResult as a black box and only rely on its
// public interface. We do NOT re-implement or infer internal logic.

// Helper to construct a minimal, valid AssertionResult purely via public APIs.
namespace {
    // Bring commonly used names into scope to keep test code terse
    using Catch::AssertionResult;
    using Catch::AssertionResultData;
    using Catch::AssertionInfo;
    using Catch::LazyExpression;
    using Catch::ResultWas;
    using Catch::SourceLineInfo;
    using Catch::StringRef;
    using Catch::ResultDisposition;

    inline AssertionResult MakeResult(ResultWas::OfType t,
                                      StringRef macro = StringRef("REQUIRE"),
                                      StringRef expr  = StringRef("x == 1"),
                                      const char* file = "file.cpp",
                                      std::size_t line = 123) {
        // All types here are constructed via their public interfaces.
        LazyExpression lazy{};
        AssertionResultData data{t, lazy};
        AssertionInfo info{
            macro,
            SourceLineInfo(file, static_cast<std::size_t>(line)),
            expr,
            ResultDisposition::Normal
        };
        return AssertionResult{info, std::move(data)};
    }
} // namespace

// ----- Normal operation ------------------------------------------------------

// Ensures succeeded() agrees with the public isOk() for a variety of result types.
// (We do not assert the actual mapping; only that both public queries are consistent.)
class AssertionResultParamTest_291
    : public ::testing::TestWithParam<ResultWas::OfType> {};

TEST_P(AssertionResultParamTest_291, SucceededEqualsIsOk_ForGivenType_291) {
    auto ar = MakeResult(GetParam());
    EXPECT_EQ(ar.succeeded(), ar.isOk());
    // Sanity: getResultType() must round-trip what we constructed with
    EXPECT_EQ(ar.getResultType(), GetParam());
}

// Cover a representative spread of result types without assuming internal mapping.
INSTANTIATE_TEST_SUITE_P(
    AllKinds_291,
    AssertionResultParamTest_291,
    ::testing::Values(
        ResultWas::OfType::Ok,
        ResultWas::OfType::ExpressionFailed,
        ResultWas::OfType::ExplicitFailure,
        ResultWas::OfType::ThrewException,
        ResultWas::OfType::DidntThrowException,
        ResultWas::OfType::Info,
        ResultWas::OfType::Warning,
        ResultWas::OfType::FatalErrorCondition,
        ResultWas::OfType::NoAssertion // boundary-ish category
    )
);

// ----- Targeted expectations -------------------------------------------------

// For a clearly-successful outcome, succeeded() should be true (observable behavior).
TEST(AssertionResultTest_291, OkType_ReturnsTrue_291) {
    auto ar = MakeResult(ResultWas::OfType::Ok);
    EXPECT_TRUE(ar.succeeded());
    EXPECT_TRUE(ar.isOk());
}

// For an explicit failure outcome, succeeded() should be false (observable behavior).
TEST(AssertionResultTest_291, ExplicitFailure_ReturnsFalse_291) {
    auto ar = MakeResult(ResultWas::OfType::ExplicitFailure);
    EXPECT_FALSE(ar.succeeded());
    EXPECT_FALSE(ar.isOk());
}

// ----- Boundary / robustness -------------------------------------------------

// Repeated calls to a const query should be idempotent and stable.
TEST(AssertionResultTest_291, Succeeded_IsIdempotent_291) {
    auto ar = MakeResult(ResultWas::OfType::ThrewException);
    const bool first = ar.succeeded();
    const bool second = ar.succeeded();
    const bool third = ar.succeeded();
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
    // Also consistent with isOk()
    EXPECT_EQ(first, ar.isOk());
}

// Calling through a const reference should be valid and yield the same result.
TEST(AssertionResultTest_291, Succeeded_CallOnConstObject_291) {
    const auto ar = MakeResult(ResultWas::OfType::Warning);
    // Ensure the method is callable and consistent with isOk()
    EXPECT_EQ(ar.succeeded(), ar.isOk());
}

// Ensure constructing with minimal, valid AssertionInfo works and type round-trips.
TEST(AssertionResultTest_291, GetResultType_RoundTrips_291) {
    auto ar = MakeResult(ResultWas::OfType::DidntThrowException,
                         StringRef("CHECK"), StringRef("f()"));
    EXPECT_EQ(ar.getResultType(), ResultWas::OfType::DidntThrowException);
    // The main contract we test here is succeeded() vs isOk() consistency
    EXPECT_EQ(ar.succeeded(), ar.isOk());
}

