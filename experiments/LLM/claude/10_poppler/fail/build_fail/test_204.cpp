#include <gtest/gtest.h>
#include <optional>
#include <string>

// Include the header containing BufStream
#include "Stream.h"

class BufStreamTest_204 : public ::testing::Test {
protected:
    void SetUp() override {
        // BufStream may require specific construction; adjust as needed
    }
};

// Test that getPSFilter returns empty optional with psLevel 0 and nullptr indent
TEST_F(BufStreamTest_204, GetPSFilterReturnsEmptyOptionalWithLevel0NullIndent_204) {
    BufStream stream;
    auto result = stream.getPSFilter(0, nullptr);
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with psLevel 1 and empty string indent
TEST_F(BufStreamTest_204, GetPSFilterReturnsEmptyOptionalWithLevel1EmptyIndent_204) {
    BufStream stream;
    auto result = stream.getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with psLevel 2 and non-empty indent
TEST_F(BufStreamTest_204, GetPSFilterReturnsEmptyOptionalWithLevel2NonEmptyIndent_204) {
    BufStream stream;
    auto result = stream.getPSFilter(2, "  ");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with psLevel 3 and some indent string
TEST_F(BufStreamTest_204, GetPSFilterReturnsEmptyOptionalWithLevel3_204) {
    BufStream stream;
    auto result = stream.getPSFilter(3, "\t");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with negative psLevel
TEST_F(BufStreamTest_204, GetPSFilterReturnsEmptyOptionalWithNegativeLevel_204) {
    BufStream stream;
    auto result = stream.getPSFilter(-1, "indent");
    EXPECT_FALSE(result.has_value());
}

// Test that getPSFilter returns empty optional with large psLevel
TEST_F(BufStreamTest_204, GetPSFilterReturnsEmptyOptionalWithLargeLevel_204) {
    BufStream stream;
    auto result = stream.getPSFilter(100, "test");
    EXPECT_FALSE(result.has_value());
}

// Test that the returned optional equals std::nullopt
TEST_F(BufStreamTest_204, GetPSFilterReturnsNullopt_204) {
    BufStream stream;
    auto result = stream.getPSFilter(1, "indent");
    EXPECT_EQ(result, std::nullopt);
}

// Test that calling getPSFilter multiple times consistently returns empty optional
TEST_F(BufStreamTest_204, GetPSFilterConsistentlyReturnsEmpty_204) {
    BufStream stream;
    for (int i = 0; i < 10; ++i) {
        auto result = stream.getPSFilter(i, "indent");
        EXPECT_FALSE(result.has_value()) << "Failed on iteration " << i;
    }
}

// Test with various indent strings
TEST_F(BufStreamTest_204, GetPSFilterReturnsEmptyWithVariousIndents_204) {
    BufStream stream;
    const char* indents[] = { nullptr, "", " ", "  ", "\t", "    ", "indent" };
    for (const auto* indent : indents) {
        auto result = stream.getPSFilter(2, indent);
        EXPECT_FALSE(result.has_value());
    }
}

// Test that the returned optional's value_or works correctly (confirming no value)
TEST_F(BufStreamTest_204, GetPSFilterValueOrReturnsFallback_204) {
    BufStream stream;
    auto result = stream.getPSFilter(1, "test");
    std::string fallback = "fallback";
    EXPECT_EQ(result.value_or(fallback), "fallback");
}
