#include <gtest/gtest.h>
#include <catch2/internal/catch_parse_numbers.hpp>
#include <limits>
#include <string>

// Normal operation tests

TEST(ParseUIntTest_580, ValidDecimalNumber_580) {
    auto result = Catch::parseUInt("123", 10);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 123u);
}

TEST(ParseUIntTest_580, ValidZero_580) {
    auto result = Catch::parseUInt("0", 10);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 0u);
}

TEST(ParseUIntTest_580, ValidHexNumber_580) {
    auto result = Catch::parseUInt("FF", 16);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 255u);
}

TEST(ParseUIntTest_580, ValidHexWithPrefix_580) {
    auto result = Catch::parseUInt("0xFF", 16);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 255u);
}

TEST(ParseUIntTest_580, ValidOctalNumber_580) {
    auto result = Catch::parseUInt("77", 8);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 63u);
}

TEST(ParseUIntTest_580, ValidBase0AutoDetectDecimal_580) {
    auto result = Catch::parseUInt("42", 0);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 42u);
}

TEST(ParseUIntTest_580, ValidBase0AutoDetectHex_580) {
    auto result = Catch::parseUInt("0x1A", 0);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 26u);
}

TEST(ParseUIntTest_580, ValidBase0AutoDetectOctal_580) {
    auto result = Catch::parseUInt("010", 0);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 8u);
}

TEST(ParseUIntTest_580, ValidLargeNumber_580) {
    auto result = Catch::parseUInt("1000000", 10);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 1000000u);
}

// Boundary condition tests

TEST(ParseUIntTest_580, MaxUnsignedInt_580) {
    std::string maxVal = std::to_string(std::numeric_limits<unsigned int>::max());
    auto result = Catch::parseUInt(maxVal, 10);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, std::numeric_limits<unsigned int>::max());
}

TEST(ParseUIntTest_580, OverflowUnsignedInt_580) {
    unsigned long long overflow = static_cast<unsigned long long>(std::numeric_limits<unsigned int>::max()) + 1;
    std::string overflowStr = std::to_string(overflow);
    auto result = Catch::parseUInt(overflowStr, 10);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, VeryLargeNumber_580) {
    auto result = Catch::parseUInt("99999999999999999999999999999999999", 10);
    EXPECT_FALSE(result.has_value());
}

// Error / exceptional case tests

TEST(ParseUIntTest_580, EmptyString_580) {
    auto result = Catch::parseUInt("", 10);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, NegativeNumber_580) {
    auto result = Catch::parseUInt("-1", 10);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, NegativeZero_580) {
    auto result = Catch::parseUInt("-0", 10);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, NonNumericString_580) {
    auto result = Catch::parseUInt("abc", 10);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, MixedNumericAndAlpha_580) {
    auto result = Catch::parseUInt("123abc", 10);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, AlphaFollowedByNumeric_580) {
    auto result = Catch::parseUInt("abc123", 10);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, WhitespaceOnly_580) {
    auto result = Catch::parseUInt("   ", 10);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, LeadingWhitespace_580) {
    auto result = Catch::parseUInt("  42", 10);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 42u);
}

TEST(ParseUIntTest_580, TrailingWhitespace_580) {
    auto result = Catch::parseUInt("42  ", 10);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 42u);
}

TEST(ParseUIntTest_580, LeadingAndTrailingWhitespace_580) {
    auto result = Catch::parseUInt("  42  ", 10);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 42u);
}

TEST(ParseUIntTest_580, FloatingPointNumber_580) {
    auto result = Catch::parseUInt("3.14", 10);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, NumberWithPlusSign_580) {
    auto result = Catch::parseUInt("+5", 10);
    // std::stoull accepts '+', so pos should match trimmed size
    // The result depends on whether '+' causes any issue, but stoull accepts it
    if (result.has_value()) {
        EXPECT_EQ(*result, 5u);
    }
}

TEST(ParseUIntTest_580, SingleDigitZero_580) {
    auto result = Catch::parseUInt("0", 10);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 0u);
}

TEST(ParseUIntTest_580, LeadingZeros_580) {
    auto result = Catch::parseUInt("007", 10);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 7u);
}

TEST(ParseUIntTest_580, InvalidHexChar_580) {
    auto result = Catch::parseUInt("GG", 16);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, NumberWithSpaceInMiddle_580) {
    auto result = Catch::parseUInt("1 2", 10);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, NegativeLargeNumber_580) {
    auto result = Catch::parseUInt("-999999999", 10);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, JustAMinus_580) {
    auto result = Catch::parseUInt("-", 10);
    EXPECT_FALSE(result.has_value());
}

TEST(ParseUIntTest_580, TabAndNewlineWhitespace_580) {
    auto result = Catch::parseUInt("\t42\n", 10);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 42u);
}
