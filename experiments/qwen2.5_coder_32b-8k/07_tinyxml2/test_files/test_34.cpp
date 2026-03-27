#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_34 : public ::testing::Test {};



TEST_F(XMLUtilTest_34, SkipWhiteSpace_NoWhitespace_34) {

    const char* input = "Hello";

    int curLineNum = 0;

    const char* result = XMLUtil::SkipWhiteSpace(input, &curLineNum);

    EXPECT_EQ(result, input);

    EXPECT_EQ(curLineNum, 0);

}



TEST_F(XMLUtilTest_34, SkipWhiteSpace_SpacesOnly_34) {

    const char* input = "   ";

    int curLineNum = 0;

    const char* result = XMLUtil::SkipWhiteSpace(input, &curLineNum);

    EXPECT_EQ(result, input + 3);

    EXPECT_EQ(curLineNum, 0);

}



TEST_F(XMLUtilTest_34, SkipWhiteSpace_MixedWhitespace_34) {

    const char* input = " \t\n ";

    int curLineNum = 0;

    const char* result = XMLUtil::SkipWhiteSpace(input, &curLineNum);

    EXPECT_EQ(result, input + 4);

    EXPECT_EQ(curLineNum, 1);

}



TEST_F(XMLUtilTest_34, SkipWhiteSpace_NewlinesOnly_34) {

    const char* input = "\n\n";

    int curLineNum = 0;

    const char* result = XMLUtil::SkipWhiteSpace(input, &curLineNum);

    EXPECT_EQ(result, input + 2);

    EXPECT_EQ(curLineNum, 2);

}



TEST_F(XMLUtilTest_34, SkipWhiteSpace_NullPointer_34) {

    const char* input = nullptr;

    int curLineNum = 0;

    EXPECT_DEATH(XMLUtil::SkipWhiteSpace(input, &curLineNum), "");

}



TEST_F(XMLUtilTest_34, SkipWhiteSpace_LineNumberNull_34) {

    const char* input = " \n ";

    int* curLineNumPtr = nullptr;

    const char* result = XMLUtil::SkipWhiteSpace(input, curLineNumPtr);

    EXPECT_EQ(result, input + 3);

}



TEST_F(XMLUtilTest_34, SkipWhiteSpace_EmptyString_34) {

    const char* input = "";

    int curLineNum = 0;

    const char* result = XMLUtil::SkipWhiteSpace(input, &curLineNum);

    EXPECT_EQ(result, input);

    EXPECT_EQ(curLineNum, 0);

}
