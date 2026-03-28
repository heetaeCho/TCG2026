#include <gtest/gtest.h>
#include <optional>
#include <string>

// Minimal include to get the class under test
// Based on the interface provided, we need Stream.h
#include "Stream.h"

class RunLengthEncoderTest_223 : public ::testing::Test {
protected:
    RunLengthEncoder encoder;
};

// Test that getPSFilter returns empty optional with psLevel 0
TEST_F(RunLengthEncoderTest_223, GetPSFilterReturnsEmptyOptionalLevel0_223) {
    auto result = encoder.getPSFilter(0, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with psLevel 1
TEST_F(RunLengthEncoderTest_223, GetPSFilterReturnsEmptyOptionalLevel1_223) {
    auto result = encoder.getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with psLevel 2
TEST_F(RunLengthEncoderTest_223, GetPSFilterReturnsEmptyOptionalLevel2_223) {
    auto result = encoder.getPSFilter(2, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with psLevel 3
TEST_F(RunLengthEncoderTest_223, GetPSFilterReturnsEmptyOptionalLevel3_223) {
    auto result = encoder.getPSFilter(3, "");
    EXPECT_FALSE(result.has_value());
}

// Test with negative psLevel
TEST_F(RunLengthEncoderTest_223, GetPSFilterReturnsEmptyOptionalNegativeLevel_223) {
    auto result = encoder.getPSFilter(-1, "");
    EXPECT_FALSE(result.has_value());
}

// Test with large psLevel value
TEST_F(RunLengthEncoderTest_223, GetPSFilterReturnsEmptyOptionalLargeLevel_223) {
    auto result = encoder.getPSFilter(100, "");
    EXPECT_FALSE(result.has_value());
}

// Test with nullptr indent
TEST_F(RunLengthEncoderTest_223, GetPSFilterReturnsEmptyOptionalNullIndent_223) {
    auto result = encoder.getPSFilter(1, nullptr);
    EXPECT_FALSE(result.has_value());
}

// Test with non-empty indent string
TEST_F(RunLengthEncoderTest_223, GetPSFilterReturnsEmptyOptionalWithIndent_223) {
    auto result = encoder.getPSFilter(1, "  ");
    EXPECT_FALSE(result.has_value());
}

// Test with long indent string
TEST_F(RunLengthEncoderTest_223, GetPSFilterReturnsEmptyOptionalWithLongIndent_223) {
    auto result = encoder.getPSFilter(2, "        ");
    EXPECT_FALSE(result.has_value());
}

// Test that the returned optional equals std::nullopt
TEST_F(RunLengthEncoderTest_223, GetPSFilterReturnsNullopt_223) {
    auto result = encoder.getPSFilter(1, "indent");
    EXPECT_EQ(result, std::nullopt);
}

// Test multiple calls return consistent results
TEST_F(RunLengthEncoderTest_223, GetPSFilterConsistentAcrossMultipleCalls_223) {
    auto result1 = encoder.getPSFilter(1, "");
    auto result2 = encoder.getPSFilter(2, "  ");
    auto result3 = encoder.getPSFilter(0, nullptr);
    EXPECT_FALSE(result1.has_value());
    EXPECT_FALSE(result2.has_value());
    EXPECT_FALSE(result3.has_value());
}

// Boundary: INT_MAX psLevel
TEST_F(RunLengthEncoderTest_223, GetPSFilterReturnsEmptyOptionalIntMaxLevel_223) {
    auto result = encoder.getPSFilter(INT_MAX, "");
    EXPECT_FALSE(result.has_value());
}

// Boundary: INT_MIN psLevel
TEST_F(RunLengthEncoderTest_223, GetPSFilterReturnsEmptyOptionalIntMinLevel_223) {
    auto result = encoder.getPSFilter(INT_MIN, "");
    EXPECT_FALSE(result.has_value());
}
