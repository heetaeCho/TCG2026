// is_just_info_tests_61.cpp
#include <gtest/gtest.h>
#include <limits>
#include "catch2/internal/catch_result_type.hpp"

// Normal operation: exactly Info should be true.
TEST(IsJustInfoTest_61, ReturnsTrueForInfo_61) {
    EXPECT_TRUE(Catch::isJustInfo(Catch::ResultWas::Info));
}

// Other non-info, non-error statuses should be false.
TEST(IsJustInfoTest_61, ReturnsFalseForOkWarningSkip_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::Ok));
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::Warning));
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::ExplicitSkip));
}

// Representative failure/error codes should be false.
TEST(IsJustInfoTest_61, ReturnsFalseForFailureAndExceptionTypes_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::FailureBit));
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::ExpressionFailed));
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::ExplicitFailure));
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::Exception));
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::ThrewException));
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::DidntThrowException));
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::FatalErrorCondition));
}

// Boundary/edge: negative (Unknown) and arbitrary negative should be false.
TEST(IsJustInfoTest_61, ReturnsFalseForUnknownAndNegativeValues_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::Unknown));
    EXPECT_FALSE(Catch::isJustInfo(-123));
}

// Atypical/composite-like or unrecognized integers should be false.
TEST(IsJustInfoTest_61, ReturnsFalseForCompositeOrUnrecognizedValues_61) {
    // If a caller mistakenly treats flags as bitmasks (e.g., Info | FailureBit),
    // the resulting integer should still not be treated as "just info".
    int composite_like = Catch::ResultWas::Info | Catch::ResultWas::FailureBit; // 1 | 16 == 17
    EXPECT_FALSE(Catch::isJustInfo(composite_like));

    // Arbitrary large unrecognized value.
    EXPECT_FALSE(Catch::isJustInfo(9999));
}

// Extremes: INT_MIN and INT_MAX should be false.
TEST(IsJustInfoTest_61, ReturnsFalseForExtremeIntValues_61) {
    EXPECT_FALSE(Catch::isJustInfo(std::numeric_limits<int>::min()));
    EXPECT_FALSE(Catch::isJustInfo(std::numeric_limits<int>::max()));
}
