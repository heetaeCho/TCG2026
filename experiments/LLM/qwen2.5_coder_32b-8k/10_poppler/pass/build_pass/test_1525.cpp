#include <gtest/gtest.h>

#include <string_view>



// Assuming the function to be tested is declared in a header file named UTF.h

#include "UTF.h"



class Utf8CountUtf16CodeUnitsTest_1525 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(Utf8CountUtf16CodeUnitsTest_1525, EmptyString_1525) {

    std::string_view utf8 = "";

    EXPECT_EQ(utf8CountUtf16CodeUnits(utf8), 0);

}



TEST_F(Utf8CountUtf16CodeUnitsTest_1525, SingleAsciiCharacter_1525) {

    std::string_view utf8 = "A";

    EXPECT_EQ(utf8CountUtf16CodeUnits(utf8), 1);

}



TEST_F(Utf8CountUtf16CodeUnitsTest_1525, SingleTwoByteUtf8Character_1525) {

    std::string_view utf8 = "\xc3\xa9"; // é

    EXPECT_EQ(utf8CountUtf16CodeUnits(utf8), 1);

}



TEST_F(Utf8CountUtf16CodeUnitsTest_1525, SingleThreeByteUtf8Character_1525) {

    std::string_view utf8 = "\xe0\xa4\xb9"; // ह

    EXPECT_EQ(utf8CountUtf16CodeUnits(utf8), 1);

}



TEST_F(Utf8CountUtf16CodeUnitsTest_1525, SingleFourByteUtf8Character_1525) {

    std::string_view utf8 = "\xf0\x9d\x84\x9e"; // 𝄞

    EXPECT_EQ(utf8CountUtf16CodeUnits(utf8), 2);

}



TEST_F(Utf8CountUtf16CodeUnitsTest_1525, MultipleCharactersMixed_1525) {

    std::string_view utf8 = "A\xc3\xa9\xe0\xa4\xb9\xf0\x9d\x84\x9e";

    EXPECT_EQ(utf8CountUtf16CodeUnits(utf8), 5);

}



TEST_F(Utf8CountUtf16CodeUnitsTest_1525, InvalidUtf8SequenceSingleByteReject_1525) {

    std::string_view utf8 = "\x80"; // invalid single byte

    EXPECT_EQ(utf8CountUtf16CodeUnits(utf8), 1);

}



TEST_F(Utf8CountUtf16CodeUnitsTest_1525, InvalidUtf8SequenceMultiByteReject_1525) {

    std::string_view utf8 = "\xe0\xa4"; // invalid multi-byte

    EXPECT_EQ(utf8CountUtf16CodeUnits(utf8), 1);

}



TEST_F(Utf8CountUtf16CodeUnitsTest_1525, InvalidUtf8SequenceEndMidCharacter_1525) {

    std::string_view utf8 = "\xf0\x9d"; // invalid end mid-character

    EXPECT_EQ(utf8CountUtf16CodeUnits(utf8), 1);

}



TEST_F(Utf8CountUtf16CodeUnitsTest_1525, InvalidUtf8SequenceMultipleRejects_1525) {

    std::string_view utf8 = "\x80\xe0\xa4\xf0\x9d";

    EXPECT_EQ(utf8CountUtf16CodeUnits(utf8), 3);

}
