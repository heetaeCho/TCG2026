#include <gtest/gtest.h>
#include <optional>
#include <string>

// Include the header containing RGBGrayEncoder
#include "Stream.h"

class RGBGrayEncoderTest_239 : public ::testing::Test {
protected:
    RGBGrayEncoder encoder;
};

// Test that getPSFilter returns empty optional with psLevel 0 and nullptr indent
TEST_F(RGBGrayEncoderTest_239, GetPSFilterReturnsEmptyOptionalWithLevel0NullIndent_239) {
    auto result = encoder.getPSFilter(0, nullptr);
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with psLevel 1
TEST_F(RGBGrayEncoderTest_239, GetPSFilterReturnsEmptyOptionalWithLevel1_239) {
    auto result = encoder.getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with psLevel 2
TEST_F(RGBGrayEncoderTest_239, GetPSFilterReturnsEmptyOptionalWithLevel2_239) {
    auto result = encoder.getPSFilter(2, "  ");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with psLevel 3
TEST_F(RGBGrayEncoderTest_239, GetPSFilterReturnsEmptyOptionalWithLevel3_239) {
    auto result = encoder.getPSFilter(3, "\t");
    EXPECT_FALSE(result.has_value());
}

// Test with negative psLevel
TEST_F(RGBGrayEncoderTest_239, GetPSFilterReturnsEmptyOptionalWithNegativeLevel_239) {
    auto result = encoder.getPSFilter(-1, "indent");
    EXPECT_FALSE(result.has_value());
}

// Test with large psLevel
TEST_F(RGBGrayEncoderTest_239, GetPSFilterReturnsEmptyOptionalWithLargeLevel_239) {
    auto result = encoder.getPSFilter(100, "indent");
    EXPECT_FALSE(result.has_value());
}

// Test with non-empty indent string
TEST_F(RGBGrayEncoderTest_239, GetPSFilterReturnsEmptyOptionalWithNonEmptyIndent_239) {
    auto result = encoder.getPSFilter(2, "    ");
    EXPECT_FALSE(result.has_value());
}

// Test that the returned optional compares equal to std::nullopt
TEST_F(RGBGrayEncoderTest_239, GetPSFilterResultEqualsNullopt_239) {
    auto result = encoder.getPSFilter(1, "test");
    EXPECT_EQ(result, std::nullopt);
}

// Test multiple consecutive calls return empty optional consistently
TEST_F(RGBGrayEncoderTest_239, GetPSFilterConsistentlyReturnsEmpty_239) {
    for (int i = 0; i < 10; ++i) {
        auto result = encoder.getPSFilter(i, "indent");
        EXPECT_FALSE(result.has_value()) << "Failed on iteration " << i;
    }
}

// Test with empty string indent
TEST_F(RGBGrayEncoderTest_239, GetPSFilterWithEmptyStringIndent_239) {
    auto result = encoder.getPSFilter(0, "");
    EXPECT_FALSE(result.has_value());
}
