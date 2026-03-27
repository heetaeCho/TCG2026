#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPUtils.cpp"

#include "XMP_Const.h"



TEST(DecodeBase64CharTest_1982, ValidUppercaseCharacter_1982) {

    EXPECT_EQ(DecodeBase64Char('A'), 0);

    EXPECT_EQ(DecodeBase64Char('Z'), 25);

}



TEST(DecodeBase64CharTest_1982, ValidLowercaseCharacter_1982) {

    EXPECT_EQ(DecodeBase64Char('a'), 26);

    EXPECT_EQ(DecodeBase64Char('z'), 51);

}



TEST(DecodeBase64CharTest_1982, ValidDigitCharacter_1982) {

    EXPECT_EQ(DecodeBase64Char('0'), 52);

    EXPECT_EQ(DecodeBase64Char('9'), 61);

}



TEST(DecodeBase64CharTest_1982, PlusCharacter_1982) {

    EXPECT_EQ(DecodeBase64Char('+'), 62);

}



TEST(DecodeBase64CharTest_1982, SlashCharacter_1982) {

    EXPECT_EQ(DecodeBase64Char('/'), 63);

}



TEST(DecodeBase64CharTest_1982, WhitespaceCharactersIgnored_1982) {

    EXPECT_EQ(DecodeBase64Char(' '), 0xFF);

    EXPECT_EQ(DecodeBase64Char('\t'), 0xFF);

    EXPECT_EQ(DecodeBase64Char('\n'), 0xFF);

    EXPECT_EQ(DecodeBase64Char('\r'), 0xFF);

}



TEST(DecodeBase64CharTest_1982, InvalidCharacterThrowsException_1982) {

    EXPECT_THROW(DecodeBase64Char('!'), XMP_Error);

    EXPECT_THROW(DecodeBase64Char('@'), XMP_Error);

    EXPECT_THROW(DecodeBase64Char('['), XMP_Error);

}
