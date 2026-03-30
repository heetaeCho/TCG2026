#include <gtest/gtest.h>

#include "TestProjects/re2/util/rune.cc"

#include "TestProjects/re2/util/utf.h"



namespace re2 {



class RunetocharTest_205 : public ::testing::Test {

protected:

    char buffer_[UTFmax + 1];

};



TEST_F(RunetocharTest_205, OneByteSequence_205) {

    Rune rune = 'A'; // ASCII value for 'A' is 65

    int length = runetochar(buffer_, &rune);

    EXPECT_EQ(length, 1);

    EXPECT_EQ(buffer_[0], 'A');

}



TEST_F(RunetocharTest_205, TwoByteSequence_205) {

    Rune rune = 0x00A9; // Copyright symbol

    int length = runetochar(buffer_, &rune);

    EXPECT_EQ(length, 2);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[0]), 0xC2);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[1]), 0xA9);

}



TEST_F(RunetocharTest_205, ThreeByteSequence_205) {

    Rune rune = 0x20AC; // Euro symbol

    int length = runetochar(buffer_, &rune);

    EXPECT_EQ(length, 3);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[0]), 0xE2);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[1]), 0x82);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[2]), 0xAC);

}



TEST_F(RunetocharTest_205, FourByteSequence_205) {

    Rune rune = 0x1F600; // Grinning face emoji

    int length = runetochar(buffer_, &rune);

    EXPECT_EQ(length, 4);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[0]), 0xF0);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[1]), 0x9F);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[2]), 0x98);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[3]), 0x80);

}



TEST_F(RunetocharTest_205, OutOfRangeRune_205) {

    Rune rune = Runemax + 1; // Out of range

    int length = runetochar(buffer_, &rune);

    EXPECT_EQ(length, 3); // Error rune is represented by three bytes

    EXPECT_EQ(static_cast<unsigned char>(buffer_[0]), 0xEF);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[1]), 0xBF);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[2]), 0xBD);

}



TEST_F(RunetocharTest_205, BoundaryOneByte_205) {

    Rune rune = Rune1; // 127

    int length = runetochar(buffer_, &rune);

    EXPECT_EQ(length, 1);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[0]), static_cast<char>(Rune1));

}



TEST_F(RunetocharTest_205, BoundaryTwoByte_205) {

    Rune rune = Rune2; // 2047

    int length = runetochar(buffer_, &rune);

    EXPECT_EQ(length, 2);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[0]), T2 | static_cast<char>(Rune2 >> Bitx));

    EXPECT_EQ(static_cast<unsigned char>(buffer_[1]), Tx | (Rune2 & Maskx));

}



TEST_F(RunetocharTest_205, BoundaryThreeByte_205) {

    Rune rune = Rune3; // 65535

    int length = runetochar(buffer_, &rune);

    EXPECT_EQ(length, 3);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[0]), T3 | static_cast<char>(Rune3 >> (2*Bitx)));

    EXPECT_EQ(static_cast<unsigned char>(buffer_[1]), Tx | ((Rune3 >> Bitx) & Maskx));

    EXPECT_EQ(static_cast<unsigned char>(buffer_[2]), Tx | (Rune3 & Maskx));

}



TEST_F(RunetocharTest_205, BoundaryFourByte_205) {

    Rune rune = Runemax; // 1114111

    int length = runetochar(buffer_, &rune);

    EXPECT_EQ(length, 4);

    EXPECT_EQ(static_cast<unsigned char>(buffer_[0]), T4 | static_cast<char>(Runemax >> (3*Bitx)));

    EXPECT_EQ(static_cast<unsigned char>(buffer_[1]), Tx | ((Runemax >> (2*Bitx)) & Maskx));

    EXPECT_EQ(static_cast<unsigned char>(buffer_[2]), Tx | ((Runemax >> Bitx) & Maskx));

    EXPECT_EQ(static_cast<unsigned char>(buffer_[3]), Tx | (Runemax & Maskx));

}



} // namespace re2
