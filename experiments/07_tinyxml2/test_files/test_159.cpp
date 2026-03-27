#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class StrPairTest : public ::testing::Test {

protected:

    StrPair strPair;

};



TEST_F(StrPairTest_159, ParseName_ValidInput_ReturnsNextCharPointer_159) {

    char input[] = "ValidName123";

    char* result = strPair.ParseName(input);

    EXPECT_EQ(result - input, strlen("ValidName123"));

}



TEST_F(StrPairTest_159, ParseName_EmptyString_ReturnsNull_159) {

    char input[] = "";

    char* result = strPair.ParseName(input);

    EXPECT_EQ(result, static_cast<char*>(nullptr));

}



TEST_F(StrPairTest_159, ParseName_InvalidStartChar_ReturnsNull_159) {

    char input[] = "1InvalidName";

    char* result = strPair.ParseName(input);

    EXPECT_EQ(result, static_cast<char*>(nullptr));

}



TEST_F(StrPairTest_159, ParseName_ValidWithSpecialChars_ReturnsNextCharPointer_159) {

    char input[] = "Valid_Name-123";

    char* result = strPair.ParseName(input);

    EXPECT_EQ(result - input, strlen("Valid_Name-123"));

}



TEST_F(StrPairTest_159, ParseName_ValidWithNumbers_ReturnsNextCharPointer_159) {

    char input[] = "ValidName123";

    char* result = strPair.ParseName(input);

    EXPECT_EQ(result - input, strlen("ValidName123"));

}



TEST_F(StrPairTest_159, ParseName_NullInput_ReturnsNull_159) {

    char* input = nullptr;

    char* result = strPair.ParseName(input);

    EXPECT_EQ(result, static_cast<char*>(nullptr));

}
