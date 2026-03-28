// TEST_ID: 164
#include <gtest/gtest.h>
#include <cstring>

#include "tinyxml2.h"

using tinyxml2::XMLUtil;

class XMLUtilGetCharacterRefTest_164 : public ::testing::Test {
protected:
    XMLUtil util;
};

TEST_F(XMLUtilGetCharacterRefTest_164, DecimalNumericReferenceConvertsAndAdvances_164) {
    const char* input = "&#65;rest"; // 'A'
    char value[8] = {};
    int length = -1;

    const char* out = util.GetCharacterRef(input, value, &length);

    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, input + std::strlen("&#65;")); // points to 'r'
    ASSERT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST_F(XMLUtilGetCharacterRefTest_164, HexNumericReferenceConvertsAndAdvances_164) {
    const char* input = "&#x41;tail"; // 'A'
    char value[8] = {};
    int length = -1;

    const char* out = util.GetCharacterRef(input, value, &length);

    ASSERT_NE(out, nullptr);
    EXPECT_STREQ(out, input + std::strlen("&#x41;")); // points to 't'
    ASSERT_EQ(length, 1);
    EXPECT_EQ(value[0], 'A');
}

TEST_F(XMLUtilGetCharacterRefTest_164, EmojiNumericReferenceProducesValidUtf8_164) {
    const char* input = "&#x1F600;X"; // 😀 U+1F600 -> F0 9F 98 80
    char value[8] = {};
    int length = -1;

    const char* out = util.GetCharacterRef(input, value, &length);

    ASSERT_NE(out, nullptr);
    EXPECT_EQ(*out, 'X');
    ASSERT_EQ(length, 4);
    EXPECT_EQ(static_cast<unsigned char>(value[0]), 0xF0);
    EXPECT_EQ(static_cast<unsigned char>(value[1]), 0x9F);
    EXPECT_EQ(static_cast<unsigned char>(value[2]), 0x98);
    EXPECT_EQ(static_cast<unsigned char>(value[3]), 0x80);
}

TEST_F(XMLUtilGetCharacterRefTest_164, MaxUnicodeCodePointConverts_164) {
    const char* input = "&#x10FFFF;Z"; // U+10FFFF -> F4 8F BF BF
    char value[8] = {};
    int length = -1;

    const char* out = util.GetCharacterRef(input, value, &length);

    ASSERT_NE(out, nullptr);
    EXPECT_EQ(*out, 'Z');
    ASSERT_EQ(length, 4);
    EXPECT_EQ(static_cast<unsigned char>(value[0]), 0xF4);
    EXPECT_EQ(static_cast<unsigned char>(value[1]), 0x8F);
    EXPECT_EQ(static_cast<unsigned char>(value[2]), 0xBF);
    EXPECT_EQ(static_cast<unsigned char>(value[3]), 0xBF);
}

TEST_F(XMLUtilGetCharacterRefTest_164, MissingSemicolonReturnsNullAndZerosLength_164) {
    const char* input = "&#65rest"; // no ';'
    char value[8];
    std::memset(value, 0xAB, sizeof(value));
    int length = 123;

    const char* out = util.GetCharacterRef(input, value, &length);

    EXPECT_EQ(out, nullptr);
    EXPECT_EQ(length, 0); // observable contract: length reset at start
}

TEST_F(XMLUtilGetCharacterRefTest_164, InvalidHexDigitReturnsNullAndZerosLength_164) {
    const char* input = "&#x4G;rest"; // 'G' invalid for hex
    char value[8] = {};
    int length = 77;

    const char* out = util.GetCharacterRef(input, value, &length);

    EXPECT_EQ(out, nullptr);
    EXPECT_EQ(length, 0);
}

TEST_F(XMLUtilGetCharacterRefTest_164, CodePointAboveMaxReturnsNullAndZerosLength_164) {
    // 0x110000 == 1114112 decimal, which is above 0x10FFFF
    const char* input = "&#1114112;end";
    char value[8] = {};
    int length = 5;

    const char* out = util.GetCharacterRef(input, value, &length);

    EXPECT_EQ(out, nullptr);
    EXPECT_EQ(length, 0);
}

TEST_F(XMLUtilGetCharacterRefTest_164, NonNumericEntityReturnsNextCharAndDoesNotSetLength_164) {
    const char* input = "&amp;rest";
    char value[8];
    std::memset(value, 0xCD, sizeof(value));
    int length = 999;

    const char* out = util.GetCharacterRef(input, value, &length);

    ASSERT_NE(out, nullptr);
    EXPECT_EQ(out, input + 1); // observable: returns p+1 when not "&#..."
    EXPECT_EQ(length, 0);      // reset at entry
}
