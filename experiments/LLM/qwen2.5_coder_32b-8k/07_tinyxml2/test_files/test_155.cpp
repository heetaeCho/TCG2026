#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class StrPairTest : public ::testing::Test {

protected:

    StrPair strPair;

};



TEST_F(StrPairTest_155, TransferToSelfDoesNothing_155) {

    // Arrange

    char testStr[] = "test";

    strPair.Set(testStr, testStr + strlen(testStr), 0);



    // Act

    strPair.TransferTo(&strPair);



    // Assert

    EXPECT_STREQ(strPair.GetStr(), "test");

}



TEST_F(StrPairTest_155, TransferToTransfersData_155) {

    // Arrange

    char testStr[] = "test";

    StrPair other;

    strPair.Set(testStr, testStr + strlen(testStr), 0);



    // Act

    strPair.TransferTo(&other);



    // Assert

    EXPECT_STREQ(other.GetStr(), "test");

    EXPECT_TRUE(strPair.Empty());

}



TEST_F(StrPairTest_155, TransferToTargetInitiallyEmpty_155) {

    // Arrange

    char testStr[] = "test";

    StrPair other;

    strPair.Set(testStr, testStr + strlen(testStr), 0);



    // Act

    strPair.TransferTo(&other);



    // Assert

    EXPECT_STREQ(other.GetStr(), "test");

}



TEST_F(StrPairTest_155, ResetMakesEmpty_155) {

    // Arrange

    char testStr[] = "test";

    strPair.Set(testStr, testStr + strlen(testStr), 0);



    // Act

    strPair.Reset();



    // Assert

    EXPECT_TRUE(strPair.Empty());

}



TEST_F(StrPairTest_155, SetStrAssignsCorrectly_155) {

    // Arrange

    const char* testStr = "test";



    // Act

    strPair.SetStr(testStr, 0);



    // Assert

    EXPECT_STREQ(strPair.GetStr(), "test");

}



TEST_F(StrPairTest_155, EmptyInitiallyTrue_155) {

    // Arrange & Act



    // Assert

    EXPECT_TRUE(strPair.Empty());

}



TEST_F(StrPairTest_155, SetInternedStrAssignsCorrectly_155) {

    // Arrange

    const char* testStr = "test";



    // Act

    strPair.SetInternedStr(testStr);



    // Assert

    EXPECT_STREQ(strPair.GetStr(), "test");

}
