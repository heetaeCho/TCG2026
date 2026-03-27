#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class StrPairTest_157 : public ::testing::Test {

protected:

    StrPair strPair;

};



TEST_F(StrPairTest_157, SetStr_SetsStringCorrectly_157) {

    const char* testString = "HelloWorld";

    int flags = 0;

    strPair.SetStr(testString, flags);

    EXPECT_STREQ(strPair.GetStr(), testString);

}



TEST_F(StrPairTest_157, SetStr_WithNullString_ThrowsAssertion_157) {

    const char* nullString = nullptr;

    int flags = 0;

#ifdef TIXMLASSERT

    EXPECT_DEATH({ strPair.SetStr(nullString, flags); }, "TIXMLASSERT");

#else

    EXPECT_THROW(strPair.SetStr(nullString, flags), std::exception);

#endif

}



TEST_F(StrPairTest_157, SetStr_MultipleTimes_SetsStringCorrectlyEachTime_157) {

    const char* testString1 = "FirstString";

    const char* testString2 = "SecondString";

    int flags = 0;

    strPair.SetStr(testString1, flags);

    EXPECT_STREQ(strPair.GetStr(), testString1);



    strPair.SetStr(testString2, flags);

    EXPECT_STREQ(strPair.GetStr(), testString2);

}



TEST_F(StrPairTest_157, GetStr_ReturnsEmptyString_WhenNotSet_157) {

    EXPECT_STREQ(strPair.GetStr(), "");

}



TEST_F(StrPairTest_157, SetStr_WithFlags_SetsCorrectly_157) {

    const char* testString = "TestString";

    int flags = StrPair::NEEDS_FLUSH | StrPair::NEEDS_DELETE;

    strPair.SetStr(testString, flags);

    // Assuming there is a way to verify the flags, which isn't directly provided in interface

    EXPECT_STREQ(strPair.GetStr(), testString);  // This is the observable behavior we can check

}



TEST_F(StrPairTest_157, Reset_ClearsTheString_157) {

    const char* testString = "HelloWorld";

    int flags = 0;

    strPair.SetStr(testString, flags);

    EXPECT_STREQ(strPair.GetStr(), testString);



    strPair.Reset();

    EXPECT_STREQ(strPair.GetStr(), "");

}



TEST_F(StrPairTest_157, Empty_ReturnsTrue_WhenNotSet_157) {

    EXPECT_TRUE(strPair.Empty());

}



TEST_F(StrPairTest_157, Empty_ReturnsFalse_AfterSettingString_157) {

    const char* testString = "HelloWorld";

    int flags = 0;

    strPair.SetStr(testString, flags);

    EXPECT_FALSE(strPair.Empty());

}



TEST_F(StrPairTest_157, Empty_ReturnsTrue_AfterResetting_157) {

    const char* testString = "HelloWorld";

    int flags = 0;

    strPair.SetStr(testString, flags);

    strPair.Reset();

    EXPECT_TRUE(strPair.Empty());

}
