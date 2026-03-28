#include <gtest/gtest.h>

#include <re2/prefilter.cc>



namespace re2 {



class RuneToStringTest : public ::testing::Test {

protected:

    // No additional setup needed for this simple function.

};



TEST_F(RuneToStringTest_Normal_550, ConvertsSingleByteRune_550) {

    Rune r = 'A';  // Single byte ASCII character

    EXPECT_EQ(RuneToString(r), "A");

}



TEST_F(RuneToStringTest_Normal_550, ConvertsTwoByteRune_550) {

    Rune r = 0x00C4;  // Latin capital letter A with diaeresis (Ä)

    EXPECT_EQ(RuneToString(r), "Ä");

}



TEST_F(RuneToStringTest_Normal_550, ConvertsThreeByteRune_550) {

    Rune r = 0x263A;  // Smiling face

    EXPECT_EQ(RuneToString(r), "☺");

}



TEST_F(RuneToStringTest_Normal_550, ConvertsFourByteRune_550) {

    Rune r = 0x1F600;  // Grinning face

    EXPECT_EQ(RuneToString(r), "😀");

}



TEST_F(RuneToStringTest_Boundary_550, ConvertsRuneselfValue_550) {

    Rune r = Runeself;  // Should be a single byte representation

    std::string expected(1, static_cast<char>(r));

    EXPECT_EQ(RuneToString(r), expected);

}



TEST_F(RuneToStringTest_Boundary_550, ConvertsRunemaxValue_550) {

    Rune r = Runemax;  // Maximum valid Unicode code point

    char buf[UTFmax];

    int n = runetochar(buf, &r);

    EXPECT_EQ(RuneToString(r), std::string(buf, n));

}



TEST_F(RuneToStringTest_Error_550, ConvertsRuneerrorValue_550) {

    Rune r = Runeerror;  // Replacement character for invalid sequences

    std::string expected(1, static_cast<char>(r & 0xFF));  // Expected to be a single byte representation of the lower 8 bits

    EXPECT_EQ(RuneToString(r), "\xEF\xBF\xBD");  // UTF-8 encoding for U+FFFD

}



}  // namespace re2
