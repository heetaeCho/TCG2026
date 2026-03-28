#include <gtest/gtest.h>
#include <optional>
#include <string>
#include "FlateEncoder.h"

class FlateEncoderTest_1652 : public ::testing::Test {
protected:
    FlateEncoder encoder;
};

// Test that getPSFilter returns empty optional with default/typical arguments
TEST_F(FlateEncoderTest_1652, GetPSFilterReturnsEmptyOptional_1652) {
    auto result = encoder.getPSFilter(1, "  ");
    EXPECT_FALSE(result.has_value());
}

// Test getPSFilter with psLevel 0
TEST_F(FlateEncoderTest_1652, GetPSFilterWithPSLevel0_1652) {
    auto result = encoder.getPSFilter(0, "");
    EXPECT_FALSE(result.has_value());
}

// Test getPSFilter with psLevel 1
TEST_F(FlateEncoderTest_1652, GetPSFilterWithPSLevel1_1652) {
    auto result = encoder.getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test getPSFilter with psLevel 2
TEST_F(FlateEncoderTest_1652, GetPSFilterWithPSLevel2_1652) {
    auto result = encoder.getPSFilter(2, "");
    EXPECT_FALSE(result.has_value());
}

// Test getPSFilter with psLevel 3
TEST_F(FlateEncoderTest_1652, GetPSFilterWithPSLevel3_1652) {
    auto result = encoder.getPSFilter(3, "");
    EXPECT_FALSE(result.has_value());
}

// Test getPSFilter with negative psLevel
TEST_F(FlateEncoderTest_1652, GetPSFilterWithNegativePSLevel_1652) {
    auto result = encoder.getPSFilter(-1, "  ");
    EXPECT_FALSE(result.has_value());
}

// Test getPSFilter with very large psLevel
TEST_F(FlateEncoderTest_1652, GetPSFilterWithLargePSLevel_1652) {
    auto result = encoder.getPSFilter(9999, "    ");
    EXPECT_FALSE(result.has_value());
}

// Test getPSFilter with nullptr indent
TEST_F(FlateEncoderTest_1652, GetPSFilterWithNullptrIndent_1652) {
    auto result = encoder.getPSFilter(1, nullptr);
    EXPECT_FALSE(result.has_value());
}

// Test getPSFilter with empty string indent
TEST_F(FlateEncoderTest_1652, GetPSFilterWithEmptyIndent_1652) {
    auto result = encoder.getPSFilter(2, "");
    EXPECT_FALSE(result.has_value());
}

// Test getPSFilter with long indent string
TEST_F(FlateEncoderTest_1652, GetPSFilterWithLongIndent_1652) {
    auto result = encoder.getPSFilter(1, "                    ");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns std::nullopt equivalent (no value)
TEST_F(FlateEncoderTest_1652, GetPSFilterReturnsNullopt_1652) {
    auto result = encoder.getPSFilter(2, "\t");
    EXPECT_EQ(result, std::nullopt);
}

// Test calling getPSFilter multiple times yields consistent results
TEST_F(FlateEncoderTest_1652, GetPSFilterConsistentAcrossMultipleCalls_1652) {
    auto result1 = encoder.getPSFilter(1, "  ");
    auto result2 = encoder.getPSFilter(2, "    ");
    auto result3 = encoder.getPSFilter(3, "");
    EXPECT_FALSE(result1.has_value());
    EXPECT_FALSE(result2.has_value());
    EXPECT_FALSE(result3.has_value());
}

// Test getPSFilter with INT_MIN
TEST_F(FlateEncoderTest_1652, GetPSFilterWithIntMinPSLevel_1652) {
    auto result = encoder.getPSFilter(INT_MIN, "");
    EXPECT_FALSE(result.has_value());
}

// Test getPSFilter with INT_MAX
TEST_F(FlateEncoderTest_1652, GetPSFilterWithIntMaxPSLevel_1652) {
    auto result = encoder.getPSFilter(INT_MAX, "");
    EXPECT_FALSE(result.has_value());
}
