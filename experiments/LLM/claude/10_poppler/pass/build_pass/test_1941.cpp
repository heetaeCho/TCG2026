#include <gtest/gtest.h>
#include <optional>
#include <string>
#include <string_view>

// Include the header under test
#include "./TestProjects/poppler/poppler/DistinguishedNameParser.h"

using namespace DN::detail;

// --- Normal Operation Tests ---

TEST(ParseHexStringTest_1941, ValidHexStringTwoChars_1941)
{
    auto result = parseHexString("4A");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), 1u);
    EXPECT_EQ(static_cast<unsigned char>((*result)[0]), 0x4A);
}

TEST(ParseHexStringTest_1941, ValidHexStringFourChars_1941)
{
    auto result = parseHexString("4A6F");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>((*result)[0]), 0x4A);
    EXPECT_EQ(static_cast<unsigned char>((*result)[1]), 0x6F);
}

TEST(ParseHexStringTest_1941, ValidHexStringAllZeros_1941)
{
    auto result = parseHexString("0000");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), 2u);
    EXPECT_EQ((*result)[0], '\0');
    EXPECT_EQ((*result)[1], '\0');
}

TEST(ParseHexStringTest_1941, ValidHexStringFF_1941)
{
    auto result = parseHexString("FF");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), 1u);
    EXPECT_EQ(static_cast<unsigned char>((*result)[0]), 0xFF);
}

TEST(ParseHexStringTest_1941, ValidHexStringLowercase_1941)
{
    auto result = parseHexString("ab");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), 1u);
    EXPECT_EQ(static_cast<unsigned char>((*result)[0]), 0xAB);
}

TEST(ParseHexStringTest_1941, ValidHexStringMixedCase_1941)
{
    auto result = parseHexString("aB");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), 1u);
    EXPECT_EQ(static_cast<unsigned char>((*result)[0]), 0xAB);
}

TEST(ParseHexStringTest_1941, ValidHexStringLonger_1941)
{
    auto result = parseHexString("48656C6C6F");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), 5u);
    EXPECT_EQ(*result, "Hello");
}

TEST(ParseHexStringTest_1941, ValidHexStringAllDigits_1941)
{
    auto result = parseHexString("3132");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), 2u);
    EXPECT_EQ(*result, "12");
}

// --- Boundary Condition Tests ---

TEST(ParseHexStringTest_1941, EmptyString_1941)
{
    auto result = parseHexString("");
    EXPECT_FALSE(result.has_value());
}

TEST(ParseHexStringTest_1941, SingleCharacter_1941)
{
    auto result = parseHexString("A");
    EXPECT_FALSE(result.has_value());
}

TEST(ParseHexStringTest_1941, OddLengthString_1941)
{
    auto result = parseHexString("ABC");
    EXPECT_FALSE(result.has_value());
}

TEST(ParseHexStringTest_1941, OddLengthFiveChars_1941)
{
    auto result = parseHexString("ABCDE");
    EXPECT_FALSE(result.has_value());
}

TEST(ParseHexStringTest_1941, MinimumValidInput_1941)
{
    auto result = parseHexString("00");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), 1u);
    EXPECT_EQ(static_cast<unsigned char>((*result)[0]), 0x00);
}

// --- Error / Invalid Input Tests ---

TEST(ParseHexStringTest_1941, InvalidCharacterG_1941)
{
    auto result = parseHexString("GG");
    EXPECT_FALSE(result.has_value());
}

TEST(ParseHexStringTest_1941, InvalidCharacterInMiddle_1941)
{
    auto result = parseHexString("4G");
    EXPECT_FALSE(result.has_value());
}

TEST(ParseHexStringTest_1941, SpaceInString_1941)
{
    auto result = parseHexString("4A 6F");
    EXPECT_FALSE(result.has_value());
}

TEST(ParseHexStringTest_1941, InvalidCharacterAtEnd_1941)
{
    auto result = parseHexString("4AZZ");
    EXPECT_FALSE(result.has_value());
}

TEST(ParseHexStringTest_1941, InvalidCharacterMixed_1941)
{
    auto result = parseHexString("4A6G");
    EXPECT_FALSE(result.has_value());
}

TEST(ParseHexStringTest_1941, SpecialCharacters_1941)
{
    auto result = parseHexString("!@");
    EXPECT_FALSE(result.has_value());
}

TEST(ParseHexStringTest_1941, NullCharacterInHex_1941)
{
    // String with non-hex characters like newline
    auto result = parseHexString("4A\n6");
    EXPECT_FALSE(result.has_value());
}

// --- Additional Correctness Tests ---

TEST(ParseHexStringTest_1941, AllHexDigitsCoverage_1941)
{
    // Test all hex digit characters: 0-9, a-f, A-F
    auto result = parseHexString("0123456789abcdefABCDEF01");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), 12u);
}

TEST(ParseHexStringTest_1941, ResultSizeIsHalfInput_1941)
{
    std::string input = "AABBCCDD";
    auto result = parseHexString(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), input.size() / 2);
}

TEST(ParseHexStringTest_1941, VerifyByteValues_1941)
{
    auto result = parseHexString("0102030405");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result->size(), 5u);
    EXPECT_EQ(static_cast<unsigned char>((*result)[0]), 0x01);
    EXPECT_EQ(static_cast<unsigned char>((*result)[1]), 0x02);
    EXPECT_EQ(static_cast<unsigned char>((*result)[2]), 0x03);
    EXPECT_EQ(static_cast<unsigned char>((*result)[3]), 0x04);
    EXPECT_EQ(static_cast<unsigned char>((*result)[4]), 0x05);
}

TEST(ParseHexStringTest_1941, HighByteValues_1941)
{
    auto result = parseHexString("FE");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(static_cast<unsigned char>((*result)[0]), 0xFE);
}

TEST(ParseHexStringTest_1941, LowercaseFF_1941)
{
    auto result = parseHexString("ff");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(static_cast<unsigned char>((*result)[0]), 0xFF);
}
