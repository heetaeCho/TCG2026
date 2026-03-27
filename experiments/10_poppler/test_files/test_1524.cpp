#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "UTF.cc" // Assuming UTF.cc includes the necessary headers and definitions



class Utf8ToUcs4Test : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed, though typically not required for this function

    }



    void TearDown() override {

        // Teardown code if needed, though typically not required for this function

    }

};



TEST_F(Utf8ToUcs4Test_1524, ValidAsciiCharacters_1524) {

    std::string_view utf8 = "Hello";

    std::vector<Unicode> expected = {72, 101, 108, 108, 111};

    EXPECT_EQ(utf8ToUCS4(utf8), expected);

}



TEST_F(Utf8ToUcs4Test_1524, ValidUtf8TwoByteCharacters_1524) {

    std::string_view utf8 = "\xc3\xa9\xc3\xac";

    std::vector<Unicode> expected = {233, 236};

    EXPECT_EQ(utf8ToUCS4(utf8), expected);

}



TEST_F(Utf8ToUcs4Test_1524, ValidUtf8ThreeByteCharacters_1524) {

    std::string_view utf8 = "\xe0\xa4\x95\xe0\xa4\xb9";

    std::vector<Unicode> expected = {2325, 2361};

    EXPECT_EQ(utf8ToUCS4(utf8), expected);

}



TEST_F(Utf8ToUcs4Test_1524, ValidUtf8FourByteCharacters_1524) {

    std::string_view utf8 = "\xf0\x9d\x9c\x93\xf0\xa0\x87\x9b";

    std::vector<Unicode> expected = {119867, 66515};

    EXPECT_EQ(utf8ToUCS4(utf8), expected);

}



TEST_F(Utf8ToUcs4Test_1524, InvalidSingleByteCharacter_1524) {

    std::string_view utf8 = "\x80";

    std::vector<Unicode> expected = {REPLACEMENT_CHAR};

    EXPECT_EQ(utf8ToUCS4(utf8), expected);

}



TEST_F(Utf8ToUcs4Test_1524, InvalidTwoByteSequence_1524) {

    std::string_view utf8 = "\xc3";

    std::vector<Unicode> expected = {REPLACEMENT_CHAR};

    EXPECT_EQ(utf8ToUCS4(utf8), expected);

}



TEST_F(Utf8ToUcs4Test_1524, InvalidThreeByteSequence_1524) {

    std::string_view utf8 = "\xe0\xa4";

    std::vector<Unicode> expected = {REPLACEMENT_CHAR};

    EXPECT_EQ(utf8ToUCS4(utf8), expected);

}



TEST_F(Utf8ToUcs4Test_1524, InvalidFourByteSequence_1524) {

    std::string_view utf8 = "\xf0\x9d";

    std::vector<Unicode> expected = {REPLACEMENT_CHAR};

    EXPECT_EQ(utf8ToUCS4(utf8), expected);

}



TEST_F(Utf8ToUcs4Test_1524, MixedValidAndInvalidCharacters_1524) {

    std::string_view utf8 = "H\x80ello";

    std::vector<Unicode> expected = {72, REPLACEMENT_CHAR, 101, 108, 108, 111};

    EXPECT_EQ(utf8ToUCS4(utf8), expected);

}



TEST_F(Utf8ToUcs4Test_1524, EmptyString_1524) {

    std::string_view utf8 = "";

    std::vector<Unicode> expected = {};

    EXPECT_EQ(utf8ToUCS4(utf8), expected);

}
