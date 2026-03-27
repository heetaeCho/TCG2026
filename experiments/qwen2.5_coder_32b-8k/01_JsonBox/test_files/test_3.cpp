#include <gtest/gtest.h>

#include "JsonBox/Convert.h"



namespace {



class ConvertTest_3 : public ::testing::Test {

protected:

    JsonBox::Convert converter;

};



TEST_F(ConvertTest_3, DecodeUTF8_EmptyString_3) {

    std::string utf8String = "";

    JsonBox::String32 result = converter.decodeUTF8(utf8String);

    EXPECT_TRUE(result.empty());

}



TEST_F(ConvertTest_3, DecodeUTF8_SingleASCIICharacter_3) {

    std::string utf8String = "A";

    JsonBox::String32 result = converter.decodeUTF8(utf8String);

    ASSERT_EQ(1, result.size());

    EXPECT_EQ('A', result[0]);

}



TEST_F(ConvertTest_3, DecodeUTF8_MultipleASCIICharacters_3) {

    std::string utf8String = "Hello";

    JsonBox::String32 result = converter.decodeUTF8(utf8String);

    ASSERT_EQ(5, result.size());

    EXPECT_EQ('H', result[0]);

    EXPECT_EQ('e', result[1]);

    EXPECT_EQ('l', result[2]);

    EXPECT_EQ('l', result[3]);

    EXPECT_EQ('o', result[4]);

}



TEST_F(ConvertTest_3, DecodeUTF8_SingleTwoByteCharacter_3) {

    std::string utf8String = "\xC3\xA9"; // 'é'

    JsonBox::String32 result = converter.decodeUTF8(utf8String);

    ASSERT_EQ(1, result.size());

    EXPECT_EQ(0xE9, result[0]);

}



TEST_F(ConvertTest_3, DecodeUTF8_SingleThreeByteCharacter_3) {

    std::string utf8String = "\xE2\x9C\x94"; // '✓'

    JsonBox::String32 result = converter.decodeUTF8(utf8String);

    ASSERT_EQ(1, result.size());

    EXPECT_EQ(0x2714, result[0]);

}



TEST_F(ConvertTest_3, DecodeUTF8_SingleFourByteCharacter_3) {

    std::string utf8String = "\xF0\x9F\x92\xA9"; // '💩'

    JsonBox::String32 result = converter.decodeUTF8(utf8String);

    ASSERT_EQ(1, result.size());

    EXPECT_EQ(0x1F4A9, result[0]);

}



TEST_F(ConvertTest_3, DecodeUTF8_MixedCharacters_3) {

    std::string utf8String = "Hello \xC3\xA9 world \xE2\x9C\x94 \xF0\x9F\x92\xA9!";

    JsonBox::String32 result = converter.decodeUTF8(utf8String);

    ASSERT_EQ(15, result.size());

    EXPECT_EQ('H', result[0]);

    EXPECT_EQ('e', result[1]);

    EXPECT_EQ('l', result[2]);

    EXPECT_EQ('l', result[3]);

    EXPECT_EQ('o', result[4]);

    EXPECT_EQ(' ', result[5]);

    EXPECT_EQ(0xE9, result[6]);

    EXPECT_EQ(' ', result[7]);

    EXPECT_EQ('w', result[8]);

    EXPECT_EQ('o', result[9]);

    EXPECT_EQ('r', result[10]);

    EXPECT_EQ('l', result[11]);

    EXPECT_EQ('d', result[12]);

    EXPECT_EQ(' ', result[13]);

    EXPECT_EQ(0x2714, result[14]);

}



TEST_F(ConvertTest_3, DecodeUTF8_InvalidUTF8String_3) {

    std::string utf8String = "\xC3\xA9\xE2\x9C"; // Truncated '✓'

    JsonBox::String32 result = converter.decodeUTF8(utf8String);

    ASSERT_EQ(1, result.size());

    EXPECT_EQ(0xE9, result[0]);

}



} // namespace
