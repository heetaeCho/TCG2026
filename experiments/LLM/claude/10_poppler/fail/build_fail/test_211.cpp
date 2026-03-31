#include <gtest/gtest.h>
#include <optional>
#include <string>

// Include the header containing ASCIIHexEncoder
#include "Stream.h"

class ASCIIHexEncoderTest_211 : public ::testing::Test {
protected:
    ASCIIHexEncoder encoder;
};

// Test that getPSFilter returns an empty optional for psLevel 0
TEST_F(ASCIIHexEncoderTest_211, GetPSFilterReturnsEmptyOptionalLevel0_211) {
    auto result = encoder.getPSFilter(0, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns an empty optional for psLevel 1
TEST_F(ASCIIHexEncoderTest_211, GetPSFilterReturnsEmptyOptionalLevel1_211) {
    auto result = encoder.getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns an empty optional for psLevel 2
TEST_F(ASCIIHexEncoderTest_211, GetPSFilterReturnsEmptyOptionalLevel2_211) {
    auto result = encoder.getPSFilter(2, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns an empty optional for psLevel 3
TEST_F(ASCIIHexEncoderTest_211, GetPSFilterReturnsEmptyOptionalLevel3_211) {
    auto result = encoder.getPSFilter(3, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns an empty optional with a non-empty indent string
TEST_F(ASCIIHexEncoderTest_211, GetPSFilterReturnsEmptyOptionalWithIndent_211) {
    auto result = encoder.getPSFilter(1, "  ");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns an empty optional with nullptr indent
TEST_F(ASCIIHexEncoderTest_211, GetPSFilterReturnsEmptyOptionalWithNullIndent_211) {
    auto result = encoder.getPSFilter(1, nullptr);
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns an empty optional with negative psLevel
TEST_F(ASCIIHexEncoderTest_211, GetPSFilterReturnsEmptyOptionalNegativeLevel_211) {
    auto result = encoder.getPSFilter(-1, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns an empty optional with large psLevel
TEST_F(ASCIIHexEncoderTest_211, GetPSFilterReturnsEmptyOptionalLargeLevel_211) {
    auto result = encoder.getPSFilter(100, "indent");
    EXPECT_FALSE(result.has_value());
}

// Test that the returned optional compares equal to std::nullopt
TEST_F(ASCIIHexEncoderTest_211, GetPSFilterResultEqualsNullopt_211) {
    auto result = encoder.getPSFilter(2, "\t");
    EXPECT_EQ(result, std::nullopt);
}

// Test multiple consecutive calls return empty optional consistently
TEST_F(ASCIIHexEncoderTest_211, GetPSFilterConsistentlyReturnsEmpty_211) {
    for (int i = 0; i < 10; ++i) {
        auto result = encoder.getPSFilter(i, "test");
        EXPECT_FALSE(result.has_value()) << "Failed on iteration " << i;
    }
}
