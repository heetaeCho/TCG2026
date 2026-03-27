#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class StrPairTest : public ::testing::Test {

protected:

    StrPair strPair;

};



TEST_F(StrPairTest_154, DefaultConstructorInitializesMembers_154) {

    EXPECT_EQ(strPair.GetStr(), nullptr);

}



TEST_F(StrPairTest_154, SetStrSetsStringAndFlags_154) {

    const char* testString = "test";

    int testFlags = 0x123;

    strPair.SetStr(testString, testFlags);



    EXPECT_STREQ(strPair.GetStr(), testString);

}



TEST_F(StrPairTest_154, SetInternedStrSetsString_154) {

    const char* testString = "interned";

    strPair.SetInternedStr(testString);



    EXPECT_STREQ(strPair.GetStr(), testString);

}



TEST_F(StrPairTest_154, EmptyReturnsTrueForDefaultConstructedObject_154) {

    EXPECT_TRUE(strPair.Empty());

}



TEST_F(StrPairTest_154, EmptyReturnsFalseAfterSettingString_154) {

    const char* testString = "non-empty";

    strPair.SetStr(testString, 0);



    EXPECT_FALSE(strPair.Empty());

}



TEST_F(StrPairTest_154, ResetClearsString_154) {

    const char* testString = "reset-test";

    strPair.SetStr(testString, 0);

    strPair.Reset();



    EXPECT_EQ(strPair.GetStr(), nullptr);

}



TEST_F(StrPairTest_154, TransferToTransfersData_154) {

    StrPair source;

    const char* testString = "transfer";

    int testFlags = 0x456;

    source.SetStr(testString, testFlags);



    StrPair destination;

    source.TransferTo(&destination);



    EXPECT_STREQ(destination.GetStr(), testString);

    EXPECT_EQ(source.GetStr(), nullptr);

}



TEST_F(StrPairTest_154, ParseTextParsesTextCorrectly_154) {

    char buffer[] = "This is a <tag>test</tag>";

    const char* endTag = "</tag>";

    int strFlags = 0;

    int curLineNum = 0;



    char* result = strPair.ParseText(buffer, endTag, strFlags, &curLineNum);



    EXPECT_STREQ(strPair.GetStr(), "This is a ");

    EXPECT_STREQ(result, "<tag>test</tag>");

}



TEST_F(StrPairTest_154, ParseNameParsesNameCorrectly_154) {

    char buffer[] = "validName123";

    char* result = strPair.ParseName(buffer);



    EXPECT_STREQ(strPair.GetStr(), "validName123");

    EXPECT_EQ(result, buffer + strlen("validName123"));

}



TEST_F(StrPairTest_154, SetSetsStartEndAndFlags_154) {

    char start[] = "start";

    char end[] = "end";

    int flags = 0x789;

    strPair.Set(start, end, flags);



    EXPECT_STREQ(strPair.GetStr(), start);

}
