#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class StrPairTest_158 : public ::testing::Test {

protected:

    StrPair strPair;

};



TEST_F(StrPairTest_158, ParseText_NormalOperation_158) {

    int curLineNum = 0;

    char text[] = "SampleText</Tag>";

    const char* endTag = "</Tag>";

    char* result = strPair.ParseText(text, endTag, 0, &curLineNum);

    

    EXPECT_STREQ("SampleText", strPair.GetStr());

    EXPECT_EQ(result, text + strlen("SampleText</Tag>"));

    EXPECT_EQ(curLineNum, 0);

}



TEST_F(StrPairTest_158, ParseText_MultipleLines_158) {

    int curLineNum = 0;

    char text[] = "Sample\nText\n</Tag>";

    const char* endTag = "</Tag>";

    char* result = strPair.ParseText(text, endTag, 0, &curLineNum);

    

    EXPECT_STREQ("Sample\nText\n", strPair.GetStr());

    EXPECT_EQ(result, text + strlen("Sample\nText\n</Tag>"));

    EXPECT_EQ(curLineNum, 2);

}



TEST_F(StrPairTest_158, ParseText_EndTagNotFound_158) {

    int curLineNum = 0;

    char text[] = "SampleText";

    const char* endTag = "</Tag>";

    char* result = strPair.ParseText(text, endTag, 0, &curLineNum);

    

    EXPECT_STREQ("", strPair.GetStr());

    EXPECT_EQ(result, static_cast<char*>(nullptr));

    EXPECT_EQ(curLineNum, 0);

}



TEST_F(StrPairTest_158, ParseText_EmptyInput_158) {

    int curLineNum = 0;

    char text[] = "";

    const char* endTag = "</Tag>";

    char* result = strPair.ParseText(text, endTag, 0, &curLineNum);

    

    EXPECT_STREQ("", strPair.GetStr());

    EXPECT_EQ(result, static_cast<char*>(nullptr));

    EXPECT_EQ(curLineNum, 0);

}



TEST_F(StrPairTest_158, ParseText_EndTagAtStart_158) {

    int curLineNum = 0;

    char text[] = "</Tag>SampleText";

    const char* endTag = "</Tag>";

    char* result = strPair.ParseText(text, endTag, 0, &curLineNum);

    

    EXPECT_STREQ("", strPair.GetStr());

    EXPECT_EQ(result, text + strlen("</Tag>"));

    EXPECT_EQ(curLineNum, 0);

}



TEST_F(StrPairTest_158, ParseText_EndTagInMiddle_158) {

    int curLineNum = 0;

    char text[] = "Sample</Tag>Text";

    const char* endTag = "</Tag>";

    char* result = strPair.ParseText(text, endTag, 0, &curLineNum);

    

    EXPECT_STREQ("Sample", strPair.GetStr());

    EXPECT_EQ(result, text + strlen("Sample</Tag>"));

    EXPECT_EQ(curLineNum, 0);

}
