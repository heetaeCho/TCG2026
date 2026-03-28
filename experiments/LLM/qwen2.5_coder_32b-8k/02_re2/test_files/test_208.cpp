#include <gtest/gtest.h>

#include "re2/util/rune.h"



namespace {



class UtflenTest_208 : public ::testing::Test {

protected:

    // Setup and teardown can be done here if needed.

};



TEST_F(UtflenTest_208, EmptyString_208) {

    EXPECT_EQ(re2::utflen(""), 0);

}



TEST_F(UtflenTest_208, SingleByteCharacter_208) {

    EXPECT_EQ(re2::utflen("a"), 1);

}



TEST_F(UtflenTest_208, MultipleSingleByteCharacters_208) {

    EXPECT_EQ(re2::utflen("hello"), 5);

}



TEST_F(UtflenTest_208, SingleMultiByteCharacter_208) {

    // Assuming a multi-byte character like 'é' which is represented as two bytes in UTF-8

    EXPECT_EQ(re2::utflen("\xc3\xa9"), 1);

}



TEST_F(UtflenTest_208, MultipleMultiByteCharacters_208) {

    // Assuming "café" which has one multi-byte character 'é'

    EXPECT_EQ(re2::utflen("café"), 4);

}



TEST_F(UtflenTest_208, MaxUTF8Character_208) {

    // U+10FFFF is the maximum valid code point in UTF-8 and requires 4 bytes

    EXPECT_EQ(re2::utflen("\xf4\x8f\xbf\xbf"), 1);

}



TEST_F(UtflenTest_208, InvalidUTF8Character_208) {

    // Invalid sequence that should be handled gracefully

    EXPECT_EQ(re2::utflen("\xff"), 1); // This might return 1 as per the implementation

}



TEST_F(UtflenTest_208, NullTerminationHandling_208) {

    EXPECT_EQ(re2::utflen("hello\0world"), 5);

}



}  // namespace
