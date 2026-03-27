#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class XMLUtilIsPrefixHexTest_39 : public ::testing::Test {};

TEST_F(XMLUtilIsPrefixHexTest_39, NullptrReturnsFalse_39)
{
    const char* p = nullptr;
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex(p));
}

TEST_F(XMLUtilIsPrefixHexTest_39, EmptyStringReturnsFalse_39)
{
    const char* p = "";
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex(p));
}

TEST_F(XMLUtilIsPrefixHexTest_39, WhitespaceOnlyReturnsFalse_39)
{
    const char* p = " \t\r\n";
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex(p));
}

TEST_F(XMLUtilIsPrefixHexTest_39, ExactLowercase0xReturnsTrue_39)
{
    const char* p = "0x";
    EXPECT_TRUE(tinyxml2::XMLUtil::IsPrefixHex(p));
}

TEST_F(XMLUtilIsPrefixHexTest_39, ExactUppercase0XReturnsTrue_39)
{
    const char* p = "0X";
    EXPECT_TRUE(tinyxml2::XMLUtil::IsPrefixHex(p));
}

TEST_F(XMLUtilIsPrefixHexTest_39, WithFollowingCharactersStillTrue_39)
{
    EXPECT_TRUE(tinyxml2::XMLUtil::IsPrefixHex("0x1A"));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsPrefixHex("0XdeadBEEF"));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsPrefixHex("0x0"));
}

TEST_F(XMLUtilIsPrefixHexTest_39, LeadingWhitespaceIsIgnored_39)
{
    EXPECT_TRUE(tinyxml2::XMLUtil::IsPrefixHex("   0x1"));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsPrefixHex("\t0X2"));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsPrefixHex("\r\n  0xABC"));
}

TEST_F(XMLUtilIsPrefixHexTest_39, DoesNotMatchWithoutLeadingZero_39)
{
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex("x1"));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex("X1"));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex("  x1"));
}

TEST_F(XMLUtilIsPrefixHexTest_39, DoesNotMatchZeroWithoutX_39)
{
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex("0"));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex("0 "));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex("  0"));
}

TEST_F(XMLUtilIsPrefixHexTest_39, DoesNotMatchWhenSecondCharIsNotX_39)
{
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex("0y"));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex("0_"));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex("0-"));
}

TEST_F(XMLUtilIsPrefixHexTest_39, DoesNotMatchWhenZeroIsNotTheFirstNonWhitespaceChar_39)
{
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex("10x"));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex("00x"));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex(" a0x"));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsPrefixHex(" \t\n10X"));
}

}  // namespace
