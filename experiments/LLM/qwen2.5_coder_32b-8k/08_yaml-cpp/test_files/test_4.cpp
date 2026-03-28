#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/token.h"



using namespace YAML;

using namespace testing;



class TokenTest_4 : public Test {

protected:

    Mark mark;

    Token token;

};



TEST_F(TokenTest_4, ConstructorInitializesStatusAndMark_4) {

    // Arrange & Act

    Token testToken(DIRECTIVE, mark);



    // Assert

    EXPECT_EQ(testToken.status, VALID);

    EXPECT_EQ(testToken.mark, mark);

}



TEST_F(TokenTest_4, ConstructorInitializesTypeCorrectly_4) {

    // Arrange & Act

    Token testToken(SCALAR, mark);



    // Assert

    EXPECT_EQ(testToken.type, SCALAR);

}



TEST_F(TokenTest_4, ConstructorInitializesValueEmptyString_4) {

    // Arrange & Act

    Token testToken(TAG, mark);



    // Assert

    EXPECT_TRUE(testToken.value.empty());

}



TEST_F(TokenTest_4, ConstructorInitializesParamsEmptyVector_4) {

    // Arrange & Act

    Token testToken(ANCHOR, mark);



    // Assert

    EXPECT_TRUE(testToken.params.empty());

}



TEST_F(TokenTest_4, OutputOperatorPrintsCorrectFormat_4) {

    // Arrange

    std::ostringstream out;

    token.type = SCALAR;

    token.value = "test_value";

    token.params = {"param1", "param2"};



    // Act

    out << token;



    // Assert

    EXPECT_EQ(out.str(), "SCALAR: test_value param1 param2");

}



TEST_F(TokenTest_4, OutputOperatorHandlesEmptyParams_4) {

    // Arrange

    std::ostringstream out;

    token.type = ANCHOR;

    token.value = "test_anchor";

    token.params.clear();



    // Act

    out << token;



    // Assert

    EXPECT_EQ(out.str(), "ANCHOR: test_anchor");

}



TEST_F(TokenTest_4, OutputOperatorHandlesEmptyValue_4) {

    // Arrange

    std::ostringstream out;

    token.type = TAG;

    token.value = "";

    token.params = {"param1"};



    // Act

    out << token;



    // Assert

    EXPECT_EQ(out.str(), "TAG:  param1");

}
