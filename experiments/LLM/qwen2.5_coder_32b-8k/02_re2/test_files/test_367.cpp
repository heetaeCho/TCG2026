#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/regexp.cc"

#include <string>



namespace re2 {



class ConvertRunesToBytesTest_367 : public ::testing::Test {

protected:

    std::string bytes;

};



TEST_F(ConvertRunesToBytesTest_367, Latin1Conversion_367) {

    bool latin1 = true;

    Rune runes[] = { 65, 66, 67 }; // A, B, C

    int nrunes = sizeof(runes) / sizeof(runes[0]);

    

    ConvertRunesToBytes(latin1, runes, nrunes, &bytes);

    

    EXPECT_EQ(bytes, "ABC");

}



TEST_F(ConvertRunesToBytesTest_367, Latin1EmptyInput_367) {

    bool latin1 = true;

    Rune runes[] = {};

    int nrunes = sizeof(runes) / sizeof(runes[0]);

    

    ConvertRunesToBytes(latin1, runes, nrunes, &bytes);

    

    EXPECT_TRUE(bytes.empty());

}



TEST_F(ConvertRunesToBytesTest_367, UTFConversion_SingleByteChars_367) {

    bool latin1 = false;

    Rune runes[] = { 65, 66, 67 }; // A, B, C in UTF-8

    int nrunes = sizeof(runes) / sizeof(runes[0]);

    

    ConvertRunesToBytes(latin1, runes, nrunes, &bytes);

    

    EXPECT_EQ(bytes, "ABC");

}



TEST_F(ConvertRunesToBytesTest_367, UTFConversion_MultiByteChars_367) {

    bool latin1 = false;

    Rune runes[] = { 0x041F, 0x0420 }; // П, Р in UTF-8

    int nrunes = sizeof(runes) / sizeof(runes[0]);

    

    ConvertRunesToBytes(latin1, runes, nrunes, &bytes);

    

    EXPECT_EQ(bytes, "\xD0\x9F\xD0\xA0");

}



TEST_F(ConvertRunesToBytesTest_367, UTFConversion_BoundaryCondition_367) {

    bool latin1 = false;

    Rune runes[] = { 0x007F, 0x0080 }; // DEL, € in UTF-8

    int nrunes = sizeof(runes) / sizeof(runes[0]);

    

    ConvertRunesToBytes(latin1, runes, nrunes, &bytes);

    

    EXPECT_EQ(bytes, "\x7F\xE2\x82\xAC");

}



TEST_F(ConvertRunesToBytesTest_367, UTFConversion_ErrorHandling_367) {

    bool latin1 = false;

    Rune runes[] = { 0xD800 }; // High surrogate in UTF-16, invalid in UTF-8

    int nrunes = sizeof(runes) / sizeof(runes[0]);

    

    ConvertRunesToBytes(latin1, runes, nrunes, &bytes);

    

    EXPECT_EQ(bytes, "\xEF\xBF\xBD"); // Expected to be replaced by Runeerror (U+FFFD)

}



}  // namespace re2
