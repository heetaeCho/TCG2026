#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class StrPairTest_2 : public ::testing::Test {

protected:

    StrPair strPair;

};



TEST_F(StrPairTest_2, Empty_ReturnsTrueForDefaultConstructed_2) {

    EXPECT_TRUE(strPair.Empty());

}



TEST_F(StrPairTest_2, SetStr_MakesEmptyFalse_2) {

    strPair.SetStr("test", 0);

    EXPECT_FALSE(strPair.Empty());

}



TEST_F(StrPairTest_2, GetStr_ReturnsNullForDefaultConstructed_2) {

    EXPECT_EQ(nullptr, strPair.GetStr());

}



TEST_F(StrPairTest_2, GetStr_ReturnsSetString_2) {

    const char* testStr = "test";

    strPair.SetStr(testStr, 0);

    EXPECT_STREQ(testStr, strPair.GetStr());

}



TEST_F(StrPairTest_2, Reset_MakesEmptyTrueAgain_2) {

    strPair.SetStr("test", 0);

    strPair.Reset();

    EXPECT_TRUE(strPair.Empty());

}



TEST_F(StrPairTest_2, ParseText_ReturnsNullForNullInput_2) {

    char* result = strPair.ParseText(nullptr, "endTag", 0, nullptr);

    EXPECT_EQ(nullptr, result);

}



TEST_F(StrPairTest_2, ParseName_ReturnsNullForNullInput_2) {

    char* result = strPair.ParseName(nullptr);

    EXPECT_EQ(nullptr, result);

}



TEST_F(StrPairTest_2, TransferTo_CopiesContent_2) {

    StrPair source;

    source.SetStr("test", 0);



    StrPair target;

    source.TransferTo(&target);



    EXPECT_STREQ(source.GetStr(), target.GetStr());

    EXPECT_TRUE(source.Empty()); // Assuming TransferTo clears the source

}
