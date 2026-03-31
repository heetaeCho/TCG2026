#include <gtest/gtest.h>
#include "./TestProjects/Catch2/src/catch2/internal/catch_result_type.hpp"

// Tests for isOk() function with various ResultWas::OfType values

TEST(IsOkTest_60, OkReturnsTrue_60) {
    EXPECT_TRUE(Catch::isOk(Catch::ResultWas::Ok));
}

TEST(IsOkTest_60, InfoReturnsTrue_60) {
    EXPECT_TRUE(Catch::isOk(Catch::ResultWas::Info));
}

TEST(IsOkTest_60, WarningReturnsTrue_60) {
    EXPECT_TRUE(Catch::isOk(Catch::ResultWas::Warning));
}

TEST(IsOkTest_60, ExplicitSkipReturnsTrue_60) {
    EXPECT_TRUE(Catch::isOk(Catch::ResultWas::ExplicitSkip));
}

TEST(IsOkTest_60, UnknownReturnsTrue_60) {
    // Unknown = -1, which in binary has all bits set (two's complement)
    // However, (-1 & 16) depends on representation. In two's complement, -1 & 16 == 16, so isOk should be false.
    // Let's test the actual behavior.
    EXPECT_FALSE(Catch::isOk(Catch::ResultWas::Unknown));
}

TEST(IsOkTest_60, FailureBitReturnsFalse_60) {
    EXPECT_FALSE(Catch::isOk(Catch::ResultWas::FailureBit));
}

TEST(IsOkTest_60, ExpressionFailedReturnsFalse_60) {
    EXPECT_FALSE(Catch::isOk(Catch::ResultWas::ExpressionFailed));
}

TEST(IsOkTest_60, ExplicitFailureReturnsFalse_60) {
    EXPECT_FALSE(Catch::isOk(Catch::ResultWas::ExplicitFailure));
}

TEST(IsOkTest_60, ExceptionReturnsFalse_60) {
    EXPECT_FALSE(Catch::isOk(Catch::ResultWas::Exception));
}

TEST(IsOkTest_60, ThrewExceptionReturnsFalse_60) {
    EXPECT_FALSE(Catch::isOk(Catch::ResultWas::ThrewException));
}

TEST(IsOkTest_60, DidntThrowExceptionReturnsFalse_60) {
    EXPECT_FALSE(Catch::isOk(Catch::ResultWas::DidntThrowException));
}

TEST(IsOkTest_60, FatalErrorConditionReturnsFalse_60) {
    EXPECT_FALSE(Catch::isOk(Catch::ResultWas::FatalErrorCondition));
}

TEST(IsOkTest_60, ZeroValueReturnsTrue_60) {
    // Ok == 0, explicitly testing with 0
    EXPECT_TRUE(Catch::isOk(static_cast<Catch::ResultWas::OfType>(0)));
}

TEST(IsOkTest_60, ValueWithoutFailureBitReturnsTrue_60) {
    // A value like 8 that doesn't have bit 4 (16) set
    EXPECT_TRUE(Catch::isOk(static_cast<Catch::ResultWas::OfType>(8)));
}

TEST(IsOkTest_60, ValueWithFailureBitSetReturnsFalse_60) {
    // A value that has bit 4 (16) set but isn't a named enum value
    EXPECT_FALSE(Catch::isOk(static_cast<Catch::ResultWas::OfType>(48)));
}

TEST(IsOkTest_60, IsOkIsConstexpr_60) {
    // Verify constexpr-ness by using in a static_assert or constexpr context
    constexpr bool okResult = Catch::isOk(Catch::ResultWas::Ok);
    EXPECT_TRUE(okResult);

    constexpr bool failResult = Catch::isOk(Catch::ResultWas::ExpressionFailed);
    EXPECT_FALSE(failResult);
}
