#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



TEST(IsNameStartCharTest_37, NormalOperation_LowercaseLetter_37) {

    EXPECT_TRUE(XMLUtil::IsNameStartChar('a'));

}



TEST(IsNameStartCharTest_37, NormalOperation_UppercaseLetter_37) {

    EXPECT_TRUE(XMLUtil::IsNameStartChar('Z'));

}



TEST(IsNameStartCharTest_37, NormalOperation_Colon_37) {

    EXPECT_TRUE(XMLUtil::IsNameStartChar(':'));

}



TEST(IsNameStartCharTest_37, NormalOperation_Underscore_37) {

    EXPECT_TRUE(XMLUtil::IsNameStartChar('_'));

}



TEST(IsNameStartCharTest_37, BoundaryCondition_AsciiNonLetter_37) {

    EXPECT_FALSE(XMLUtil::IsNameStartChar('0'));

    EXPECT_FALSE(XMLUtil::IsNameStartChar('@'));

}



TEST(IsNameStartCharTest_37, BoundaryCondition_HighAscii_37) {

    EXPECT_TRUE(XMLUtil::IsNameStartChar(128));

    EXPECT_TRUE(XMLUtil::IsNameStartChar(255));

}



TEST(IsNameStartCharTest_37, ExceptionalCase_NullCharacter_37) {

    EXPECT_FALSE(XMLUtil::IsNameStartChar('\0'));

}
