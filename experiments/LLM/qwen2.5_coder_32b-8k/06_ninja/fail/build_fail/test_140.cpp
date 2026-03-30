#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util.h"



using namespace std;



class GetShellEscapedStringTest : public ::testing::Test {

protected:

    string result;

};



TEST_F(GetShellEscapedStringTest_140, NormalOperationNoSpecialChars_140) {

    string input = "normalstring";

    GetShellEscapedString(input, &result);

    EXPECT_EQ(result, "'normalstring'");

}



TEST_F(GetShellEscapedStringTest_140, NormalOperationWithSpaces_140) {

    string input = "normal string with spaces";

    GetShellEscapedString(input, &result);

    EXPECT_EQ(result, "'normal string with spaces'");

}



TEST_F(GetShellEscapedStringTest_140, BoundaryConditionEmptyString_140) {

    string input = "";

    GetShellEscapedString(input, &result);

    EXPECT_EQ(result, "''");

}



TEST_F(GetShellEscapedStringTest_140, BoundaryConditionSingleQuote_140) {

    string input = "'";

    GetShellEscapedString(input, &result);

    EXPECT_EQ(result, "'\\''");

}



TEST_F(GetShellEscapedStringTest_140, NormalOperationMultipleQuotes_140) {

    string input = "hello'world'";

    GetShellEscapedString(input, &result);

    EXPECT_EQ(result, "'hello\\''world\\''");

}



TEST_F(GetShellEscapedStringTest_140, ExceptionalCaseNullResultPointer_140) {

    string input = "someinput";

    EXPECT_DEATH(GetShellEscapedString(input, nullptr), "");

}
