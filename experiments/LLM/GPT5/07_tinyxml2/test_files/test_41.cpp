// File: test_xmlutil_isutf8continuation_41.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class XMLUtilTest_41 : public ::testing::Test {};

TEST_F(XMLUtilTest_41, AsciiCharactersReturnFalse_41)
{
    EXPECT_FALSE(tinyxml2::XMLUtil::IsUTF8Continuation('\0'));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsUTF8Continuation('A'));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsUTF8Continuation(static_cast<char>(0x7F)));
}

TEST_F(XMLUtilTest_41, HighBitSetReturnsTrue_41)
{
    EXPECT_TRUE(tinyxml2::XMLUtil::IsUTF8Continuation(static_cast<char>(0x80)));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsUTF8Continuation(static_cast<char>(0xFF)));
}

TEST_F(XMLUtilTest_41, ValuesAroundBoundaryBehaveAsExpected_41)
{
    const char below = static_cast<char>(0x7F);
    const char at    = static_cast<char>(0x80);
    const char above = static_cast<char>(0x81);

    EXPECT_FALSE(tinyxml2::XMLUtil::IsUTF8Continuation(below));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsUTF8Continuation(at));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsUTF8Continuation(above));
}

TEST_F(XMLUtilTest_41, SignedCharNegativeValueDoesNotBreakDetection_41)
{
    // On platforms where 'char' is signed, 0xFF becomes -1.
    // This test ensures the function still treats it as having the high bit set.
    const unsigned char u = 0xFF;
    const char c = static_cast<char>(u);

    EXPECT_TRUE(tinyxml2::XMLUtil::IsUTF8Continuation(c));
}

}  // namespace
