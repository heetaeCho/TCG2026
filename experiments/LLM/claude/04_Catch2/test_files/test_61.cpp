#include <gtest/gtest.h>
#include "./TestProjects/Catch2/src/catch2/internal/catch_result_type.hpp"

// Test that Info flag returns true
TEST(IsJustInfoTest_61, ReturnsTrue_WhenFlagIsInfo_61) {
    EXPECT_TRUE(Catch::isJustInfo(Catch::ResultWas::Info));
}

// Test that the integer value 1 (which is Info) returns true
TEST(IsJustInfoTest_61, ReturnsTrue_WhenFlagIsOne_61) {
    EXPECT_TRUE(Catch::isJustInfo(1));
}

// Test that Unknown returns false
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsUnknown_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::Unknown));
}

// Test that Ok returns false
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsOk_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::Ok));
}

// Test that Warning returns false
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsWarning_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::Warning));
}

// Test that ExplicitSkip returns false
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsExplicitSkip_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::ExplicitSkip));
}

// Test that FailureBit returns false
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsFailureBit_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::FailureBit));
}

// Test that ExpressionFailed returns false
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsExpressionFailed_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::ExpressionFailed));
}

// Test that ExplicitFailure returns false
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsExplicitFailure_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::ExplicitFailure));
}

// Test that Exception returns false
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsException_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::Exception));
}

// Test that ThrewException returns false
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsThrewException_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::ThrewException));
}

// Test that DidntThrowException returns false
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsDidntThrowException_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::DidntThrowException));
}

// Test that FatalErrorCondition returns false
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsFatalErrorCondition_61) {
    EXPECT_FALSE(Catch::isJustInfo(Catch::ResultWas::FatalErrorCondition));
}

// Boundary: Test with zero
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsZero_61) {
    EXPECT_FALSE(Catch::isJustInfo(0));
}

// Boundary: Test with negative value
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsNegativeOne_61) {
    EXPECT_FALSE(Catch::isJustInfo(-1));
}

// Boundary: Test with large positive value
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsLargePositive_61) {
    EXPECT_FALSE(Catch::isJustInfo(9999));
}

// Boundary: Test with value 2 (adjacent to Info=1)
TEST(IsJustInfoTest_61, ReturnsFalse_WhenFlagIsTwo_61) {
    EXPECT_FALSE(Catch::isJustInfo(2));
}

// Test constexpr nature - can be used at compile time
TEST(IsJustInfoTest_61, IsConstexpr_61) {
    constexpr bool result = Catch::isJustInfo(Catch::ResultWas::Info);
    EXPECT_TRUE(result);
    
    constexpr bool resultFalse = Catch::isJustInfo(Catch::ResultWas::Ok);
    EXPECT_FALSE(resultFalse);
}
