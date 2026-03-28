// File: catch_result_type_isOk_test_60.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_result_type.hpp"

namespace {
using Catch::ResultWas::OfType;
using Catch::ResultWas::Ok;
using Catch::ResultWas::Info;
using Catch::ResultWas::Warning;
using Catch::ResultWas::ExplicitSkip;
using Catch::ResultWas::FailureBit;
using Catch::ResultWas::ExpressionFailed;
using Catch::ResultWas::ExplicitFailure;
using Catch::ResultWas::Exception;
using Catch::ResultWas::ThrewException;
using Catch::ResultWas::DidntThrowException;
using Catch::ResultWas::FatalErrorCondition;
using Catch::ResultWas::Unknown;

// Optional compile-time check that the interface is constexpr-usable
static_assert(Catch::isOk(Ok), "isOk(Ok) should be usable in constant expressions");
} // namespace

// --- Non-failure outcomes should be considered OK ---

class IsOk_NonFailure_60 : public ::testing::TestWithParam<OfType> {};
TEST_P(IsOk_NonFailure_60, ReturnsTrueForNonFailureOutcomes_60) {
    EXPECT_TRUE(Catch::isOk(GetParam()));
}
INSTANTIATE_TEST_SUITE_P(
    NonFailureCases_60,
    IsOk_NonFailure_60,
    ::testing::Values(Ok, Info, Warning, ExplicitSkip)
);

// --- Failure-related outcomes should not be OK ---

class IsOk_Failure_60 : public ::testing::TestWithParam<OfType> {};
TEST_P(IsOk_Failure_60, ReturnsFalseForFailureOutcomes_60) {
    EXPECT_FALSE(Catch::isOk(GetParam()));
}
INSTANTIATE_TEST_SUITE_P(
    FailureCases_60,
    IsOk_Failure_60,
    ::testing::Values(
        FailureBit,           // boundary: mask alone
        ExpressionFailed,     // expression-based failure
        ExplicitFailure,      // explicit failure
        Exception,            // generic exception category
        ThrewException,       // threw when it shouldn't
        DidntThrowException,  // didn't throw when it should
        FatalErrorCondition   // fatal error condition
    )
);

// --- Boundary / atypical values ---

TEST(IsOk_Boundaries_60, ReturnsTrueForOkZero_60) {
    // Boundary at zero value
    EXPECT_TRUE(Catch::isOk(Ok));
}

TEST(IsOk_Boundaries_60, ReturnsFalseForUnknownMinusOne_60) {
    // Atypical/unknown enum value (negative)
    EXPECT_FALSE(Catch::isOk(Unknown));
}

// --- Spot checks for clarity ---

TEST(IsOk_SpotChecks_60, InfoWarningSkipAreOk_60) {
    EXPECT_TRUE(Catch::isOk(Info));
    EXPECT_TRUE(Catch::isOk(Warning));
    EXPECT_TRUE(Catch::isOk(ExplicitSkip));
}

TEST(IsOk_SpotChecks_60, ExceptionsAreNotOk_60) {
    EXPECT_FALSE(Catch::isOk(Exception));
    EXPECT_FALSE(Catch::isOk(ThrewException));
    EXPECT_FALSE(Catch::isOk(DidntThrowException));
}
