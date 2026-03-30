#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PageLabelInfo_p.h"



class PageLabelInfoTest_1933 : public ::testing::Test {};



TEST_F(PageLabelInfoTest_1933, FromRoman_SimpleValidInput_1933) {

    EXPECT_EQ(fromRoman("I"), 1);

    EXPECT_EQ(fromRoman("V"), 5);

    EXPECT_EQ(fromRoman("X"), 10);

    EXPECT_EQ(fromRoman("L"), 50);

    EXPECT_EQ(fromRoman("C"), 100);

    EXPECT_EQ(fromRoman("D"), 500);

    EXPECT_EQ(fromRoman("M"), 1000);

}



TEST_F(PageLabelInfoTest_1933, FromRoman_CombinedValidInput_1933) {

    EXPECT_EQ(fromRoman("III"), 3);

    EXPECT_EQ(fromRoman("IV"), 4);

    EXPECT_EQ(fromRoman("IX"), 9);

    EXPECT_EQ(fromRoman("XLVII"), 47);

    EXPECT_EQ(fromRoman("MCMLXXI"), 1971);

}



TEST_F(PageLabelInfoTest_1933, FromRoman_LowercaseValidInput_1933) {

    EXPECT_EQ(fromRoman("iii"), 3);

    EXPECT_EQ(fromRoman("iv"), 4);

    EXPECT_EQ(fromRoman("ix"), 9);

    EXPECT_EQ(fromRoman("xlvii"), 47);

    EXPECT_EQ(fromRoman("mcmlxxi"), 1971);

}



TEST_F(PageLabelInfoTest_1933, FromRoman_MixedCaseValidInput_1933) {

    EXPECT_EQ(fromRoman("MiXeD"), 1064);

    EXPECT_EQ(fromRoman("MdCcLXXi"), 2171);

}



TEST_F(PageLabelInfoTest_1933, FromRoman_InvalidInput_ReturnsNegative_1933) {

    EXPECT_LT(fromRoman("MMMM"), 0); // Invalid Roman numeral

    EXPECT_LT(fromRoman("IIII"), 0); // Invalid Roman numeral

    EXPECT_LT(fromRoman("IXX"), 0);  // Invalid Roman numeral

    EXPECT_LT(fromRoman("IL"), 0);   // Invalid Roman numeral

    EXPECT_LT(fromRoman("XM"), 0);   // Invalid Roman numeral

    EXPECT_LT(fromRoman("VX"), 0);   // Invalid Roman numeral

}



TEST_F(PageLabelInfoTest_1933, FromRoman_EmptyString_ReturnsNegative_1933) {

    EXPECT_LT(fromRoman(""), 0);

}



TEST_F(PageLabelInfoTest_1933, FromRoman_NonRomanCharacters_ReturnsNegative_1933) {

    EXPECT_LT(fromRoman("ABCD"), 0);

    EXPECT_LT(fromRoman("1234"), 0);

    EXPECT_LT(fromRoman("!@#$"), 0);

}



TEST_F(PageLabelInfoTest_1933, FromRoman_BoundaryCases_ReturnsCorrect_1933) {

    EXPECT_EQ(fromRoman("MCMXCIX"), 1999); // Largest valid Roman numeral

    EXPECT_EQ(fromRoman("I"), 1);          // Smallest valid Roman numeral

}
