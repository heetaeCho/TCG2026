#include <gtest/gtest.h>

#include "./TestProjects/poppler/utils/HtmlOutputDev.cc"

#include <string>



TEST(print_uni_str_Test_2732, EmptyUnicodeString_ReturnsEmptyString_2732) {

    const Unicode u[] = {};

    unsigned uLen = 0;

    EXPECT_EQ(print_uni_str(u, uLen), "");

}



TEST(print_uni_str_Test_2732, SingleAsciiCharacter_ReturnsCorrectString_2732) {

    const Unicode u[] = {65}; // 'A'

    unsigned uLen = 1;

    EXPECT_EQ(print_uni_str(u, uLen), "A");

}



TEST(print_uni_str_Test_2732, MultipleAsciiCharacters_ReturnsConcatenatedString_2732) {

    const Unicode u[] = {65, 66, 67}; // 'ABC'

    unsigned uLen = 3;

    EXPECT_EQ(print_uni_str(u, uLen), "ABC");

}



TEST(print_uni_str_Test_2732, SingleNonAsciiCharacter_ReturnsQuestionMark_2732) {

    const Unicode u[] = {0x80}; // Non-ASCII character

    unsigned uLen = 1;

    EXPECT_EQ(print_uni_str(u, uLen), "?");

}



TEST(print_uni_str_Test_2732, MixedAsciiAndNonAsciiCharacters_ReturnsQuestionMarkForNonAscii_2732) {

    const Unicode u[] = {65, 0x80, 66}; // 'A?B'

    unsigned uLen = 3;

    EXPECT_EQ(print_uni_str(u, uLen), "A?B");

}



TEST(print_uni_str_Test_2732, AllNonAsciiCharacters_ReturnsQuestionMarks_2732) {

    const Unicode u[] = {0x80, 0x81, 0x82}; // '???'

    unsigned uLen = 3;

    EXPECT_EQ(print_uni_str(u, uLen), "???");

}
