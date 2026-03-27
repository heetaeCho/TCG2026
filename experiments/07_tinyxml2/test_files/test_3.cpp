#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class StrPairTest : public ::testing::Test {

protected:

    StrPair strPair;

};



TEST_F(StrPairTest_3, SetInternedStr_SetsString_3) {

    const char* testStr = "testString";

    strPair.SetInternedStr(testStr);

    EXPECT_STREQ(strPair.GetStr(), testStr);

}



TEST_F(StrPairTest_3, Reset_ClearsString_3) {

    strPair.SetInternedStr("testString");

    strPair.Reset();

    EXPECT_TRUE(strPair.Empty());

}



TEST_F(StrPairTest_3, Empty_ReturnsTrueInitially_3) {

    EXPECT_TRUE(strPair.Empty());

}



TEST_F(StrPairTest_3, Empty_ReturnsFalseAfterSet_3) {

    strPair.SetInternedStr("testString");

    EXPECT_FALSE(strPair.Empty());

}



TEST_F(StrPairTest_3, GetStr_ReturnsNullAfterReset_3) {

    strPair.SetInternedStr("testString");

    strPair.Reset();

    EXPECT_STREQ(strPair.GetStr(), nullptr);

}
