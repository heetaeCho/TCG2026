#include <gtest/gtest.h>

#include "JsonBox/Convert.h"



using namespace JsonBox;



class ConvertTest_2 : public ::testing::Test {

protected:

    // You can set up any common variables or state here.

};



TEST_F(ConvertTest_2, EncodeToUTF8_SingleASCIICharacter_2) {

    String32 utf32String = {0x41}; // 'A'

    std::string expected = "A";

    EXPECT_EQ(Convert::encodeToUTF8(utf32String), expected);

}



TEST_F(ConvertTest_2, EncodeToUTF8_MultipleASCIICharacters_2) {

    String32 utf32String = {0x41, 0x65, 0x72}; // "Aer"

    std::string expected = "Aer";

    EXPECT_EQ(Convert::encodeToUTF8(utf32String), expected);

}



TEST_F(ConvertTest_2, EncodeToUTF8_TwoByteCharacter_2) {

    String32 utf32String = {0x041F}; // 'П'

    std::string expected = "\xD0\x9F";

    EXPECT_EQ(Convert::encodeToUTF8(utf32String), expected);

}



TEST_F(ConvertTest_2, EncodeToUTF8_ThreeByteCharacter_2) {

    String32 utf32String = {0x1F57A}; // 👺

    std::string expected = "\xF0\x9F\x95\xBA";

    EXPECT_EQ(Convert::encodeToUTF8(utf32String), expected);

}



TEST_F(ConvertTest_2, EncodeToUTF8_FourByteCharacter_2) {

    String32 utf32String = {0x10400}; // 𐀀

    std::string expected = "\xF0\x90\x80\x80";

    EXPECT_EQ(Convert::encodeToUTF8(utf32String), expected);

}



TEST_F(ConvertTest_2, EncodeToUTF8_MultipleUnicodeCharacters_2) {

    String32 utf32String = {0x41, 0x041F, 0x1F57A}; // "AП😜"

    std::string expected = "A\xD0\x9F\xF0\x9F\x95\xBA";

    EXPECT_EQ(Convert::encodeToUTF8(utf32String), expected);

}



TEST_F(ConvertTest_2, EncodeToUTF8_EmptyString_2) {

    String32 utf32String = {};

    std::string expected = "";

    EXPECT_EQ(Convert::encodeToUTF8(utf32String), expected);

}



TEST_F(ConvertTest_2, EncodeToUTF8_HighestValidUnicode_2) {

    String32 utf32String = {0x10FFFF}; // 􏿽

    std::string expected = "\xF4\x8F\xBF\xBF";

    EXPECT_EQ(Convert::encodeToUTF8(utf32String), expected);

}



TEST_F(ConvertTest_2, EncodeToUTF8_OutOfRangeUnicode_2) {

    String32 utf32String = {0x110000}; // Out of range

    std::string expected = "\xF4\x90\x80\x80"; // This is incorrect encoding but the function does not handle errors.

    EXPECT_EQ(Convert::encodeToUTF8(utf32String), expected);

}
