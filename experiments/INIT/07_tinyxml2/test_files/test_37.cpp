#include <gtest/gtest.h>

#include <clocale>

#include "tinyxml2.h"

namespace {

class XMLUtilIsNameStartCharTest_37 : public ::testing::Test {
protected:
    void SetUp() override {
        // Stabilize classification for isalpha() to avoid locale-dependent surprises.
        // Using "C" locale ensures ASCII behavior for our tests that use ASCII inputs.
        std::setlocale(LC_CTYPE, "C");
    }
};

TEST_F(XMLUtilIsNameStartCharTest_37, ReturnsTrueForAsciiLetters_37) {
    EXPECT_TRUE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>('A')));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>('Z')));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>('a')));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>('z')));
}

TEST_F(XMLUtilIsNameStartCharTest_37, ReturnsTrueForColonAndUnderscore_37) {
    EXPECT_TRUE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>(':')));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>('_')));
}

TEST_F(XMLUtilIsNameStartCharTest_37, ReturnsFalseForDigits_37) {
    EXPECT_FALSE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>('0')));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>('9')));
}

TEST_F(XMLUtilIsNameStartCharTest_37, ReturnsFalseForCommonNonStartPunctuation_37) {
    EXPECT_FALSE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>('-')));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>('.')));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>(' ')));
}

TEST_F(XMLUtilIsNameStartCharTest_37, ReturnsTrueForNonAsciiBytesAtOrAbove128_Boundary_37) {
    EXPECT_TRUE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>(128)));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>(255)));
}

TEST_F(XMLUtilIsNameStartCharTest_37, ReturnsFalseForAsciiByteBelow128WhenNotAlphaColonOrUnderscore_Boundary_37) {
    EXPECT_FALSE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>(127)));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsNameStartChar(static_cast<unsigned char>(0)));
}

}  // namespace
