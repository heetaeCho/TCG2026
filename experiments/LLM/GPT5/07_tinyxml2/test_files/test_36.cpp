// File: ./TestProjects/tinyxml2/tests/xmlutil_iswhitespace_test_36.cpp

#include <gtest/gtest.h>

#include <clocale>   // std::setlocale
#include <cstdint>   // uint8_t

#include "../tinyxml2.h"

namespace {

class IsWhiteSpaceTest_36 : public ::testing::Test {
protected:
    void SetUp() override {
        // Make ctype classification (isspace) deterministic for the tests.
        std::setlocale(LC_CTYPE, "C");
    }
};

TEST_F(IsWhiteSpaceTest_36, ReturnsTrueForCommonAsciiWhitespace_36) {
    EXPECT_TRUE(tinyxml2::XMLUtil::IsWhiteSpace(' '));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsWhiteSpace('\t'));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsWhiteSpace('\n'));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsWhiteSpace('\r'));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsWhiteSpace('\f'));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsWhiteSpace('\v'));
}

TEST_F(IsWhiteSpaceTest_36, ReturnsFalseForCommonNonWhitespaceAscii_36) {
    EXPECT_FALSE(tinyxml2::XMLUtil::IsWhiteSpace('a'));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsWhiteSpace('Z'));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsWhiteSpace('0'));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsWhiteSpace('_'));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsWhiteSpace('<'));
    EXPECT_FALSE(tinyxml2::XMLUtil::IsWhiteSpace('>'));
}

TEST_F(IsWhiteSpaceTest_36, ReturnsFalseForNulCharacter_36) {
    EXPECT_FALSE(tinyxml2::XMLUtil::IsWhiteSpace('\0'));
}

TEST_F(IsWhiteSpaceTest_36, ReturnsFalseForUtf8ContinuationBytes_36) {
    // UTF-8 continuation bytes are in the range 0x80..0xBF.
    // Use uint8_t to avoid sign-extension surprises, then cast to char.
    for (uint8_t b = 0x80; b <= 0xBF; ++b) {
        const char ch = static_cast<char>(b);
        EXPECT_FALSE(tinyxml2::XMLUtil::IsWhiteSpace(ch)) << "byte=0x" << std::hex << int(b);
    }
}

TEST_F(IsWhiteSpaceTest_36, ReturnsFalseForHighBitNonContinuationByte_36) {
    // 0xC2 is a common leading byte for UTF-8 sequences (e.g., for U+00A0).
    // In the "C" locale, isspace should not treat this as whitespace.
    const char ch = static_cast<char>(0xC2);
    EXPECT_FALSE(tinyxml2::XMLUtil::IsWhiteSpace(ch));
}

TEST_F(IsWhiteSpaceTest_36, ReturnsFalseForByte0xFF_36) {
    // Stress a value that may be negative when char is signed.
    const char ch = static_cast<char>(0xFF);
    EXPECT_FALSE(tinyxml2::XMLUtil::IsWhiteSpace(ch));
}

}  // namespace
