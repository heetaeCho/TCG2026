#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class StrPairTest : public ::testing::Test {

protected:

    StrPair strPair;

};



TEST_F(StrPairTest_156, ResetClearsFlagsAndPointers_156) {

    // Arrange

    char testStr[] = "test";

    strPair.SetStr(testStr, StrPair::NEEDS_DELETE);



    // Act

    strPair.Reset();



    // Assert

    EXPECT_EQ(strPair.GetStr(), nullptr);

}



TEST_F(StrPairTest_156, ResetDoesNotCrashOnEmpty_156) {

    // Arrange & Act

    strPair.Reset();  // Already empty by default



    // Assert

    EXPECT_EQ(strPair.GetStr(), nullptr);

}



TEST_F(StrPairTest_156, SetStrAssignsStringCorrectly_156) {

    // Arrange

    const char* testStr = "test";



    // Act

    strPair.SetStr(testStr, 0);



    // Assert

    EXPECT_STREQ(strPair.GetStr(), testStr);

}



TEST_F(StrPairTest_156, SetStrWithNEEDS_DELETEFreesMemory_156) {

    // Arrange

    char* dynamicString = new char[5];

    strcpy(dynamicString, "test");



    // Act

    strPair.SetStr(dynamicString, StrPair::NEEDS_DELETE);

    strPair.Reset();  // This should free the memory



    // Assert (indirectly by checking if Reset did not crash)

}



TEST_F(StrPairTest_156, GetStrReturnsEmptyWhenUnset_156) {

    // Arrange & Act

    const char* result = strPair.GetStr();



    // Assert

    EXPECT_EQ(result, nullptr);

}
