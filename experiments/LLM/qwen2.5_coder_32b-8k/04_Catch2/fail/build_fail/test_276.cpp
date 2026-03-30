#include <gtest/gtest.h>

#include "catch2/catch_tostring.hpp"



using namespace Catch;



TEST_F(StringMakerTest_276, ConvertCharPositive_276) {

    char c = 'A';

    EXPECT_EQ(StringMaker<char>::convert(c), "65");

}



TEST_F(StringMakerTest_276, ConvertCharNegative_276) {

    char c = -1;

    EXPECT_EQ(StringMaker<char>::convert(c), "-1");

}



TEST_F(StringMakerTest_276, ConvertCharZero_276) {

    char c = 0;

    EXPECT_EQ(StringMaker<char>::convert(c), "0");

}



TEST_F(StringMakerTest_276, ConvertCharMax_276) {

    char c = CHAR_MAX;

    EXPECT_EQ(StringMaker<char>::convert(c), std::to_string(CHAR_MAX));

}



TEST_F(StringMakerTest_276, ConvertCharMin_276) {

    char c = CHAR_MIN;

    EXPECT_EQ(StringMaker<char>::convert(c), std::to_string(CHAR_MIN));

}
