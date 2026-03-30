#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest : public ::testing::Test {

protected:

    int curLineNum;

};



TEST_F(XMLUtilTest_35, SkipWhiteSpace_NoWhitespace_35) {

    const char* input = "Hello";

    curLineNum = 0;

    EXPECT_EQ(SkipWhiteSpace(input, &curLineNum), input);

    EXPECT_EQ(curLineNum, 0);

}



TEST_F(XMLUtilTest_35, SkipWhiteSpace_SingleSpace_35) {

    const char* input = " Hello";

    curLineNum = 0;

    EXPECT_EQ(SkipWhiteSpace(input, &curLineNum), input + 1);

    EXPECT_EQ(curLineNum, 0);

}



TEST_F(XMLUtilTest_35, SkipWhiteSpace_MultipleSpaces_35) {

    const char* input = "   Hello";

    curLineNum = 0;

    EXPECT_EQ(SkipWhiteSpace(input, &curLineNum), input + 3);

    EXPECT_EQ(curLineNum, 0);

}



TEST_F(XMLUtilTest_35, SkipWhiteSpace_TabCharacter_35) {

    const char* input = "\tHello";

    curLineNum = 0;

    EXPECT_EQ(SkipWhiteSpace(input, &curLineNum), input + 1);

    EXPECT_EQ(curLineNum, 0);

}



TEST_F(XMLUtilTest_35, SkipWhiteSpace_NewlineCharacter_35) {

    const char* input = "\nHello";

    curLineNum = 0;

    EXPECT_EQ(SkipWhiteSpace(input, &curLineNum), input + 1);

    EXPECT_EQ(curLineNum, 1);

}



TEST_F(XMLUtilTest_35, SkipWhiteSpace_CarriageReturnCharacter_35) {

    const char* input = "\rHello";

    curLineNum = 0;

    EXPECT_EQ(SkipWhiteSpace(input, &curLineNum), input + 1);

    EXPECT_EQ(curLineNum, 0);

}



TEST_F(XMLUtilTest_35, SkipWhiteSpace_MixedWhitespaceCharacters_35) {

    const char* input = "\r\n \tHello";

    curLineNum = 0;

    EXPECT_EQ(SkipWhiteSpace(input, &curLineNum), input + 4);

    EXPECT_EQ(curLineNum, 1);

}



TEST_F(XMLUtilTest_35, SkipWhiteSpace_AllWhitespaceCharacters_35) {

    const char* input = " \t\n\r ";

    curLineNum = 0;

    EXPECT_EQ(SkipWhiteSpace(input, &curLineNum), input + 4);

    EXPECT_EQ(curLineNum, 1);

}



TEST_F(XMLUtilTest_35, SkipWhiteSpace_EmptyString_35) {

    const char* input = "";

    curLineNum = 0;

    EXPECT_EQ(SkipWhiteSpace(input, &curLineNum), input);

    EXPECT_EQ(curLineNum, 0);

}
