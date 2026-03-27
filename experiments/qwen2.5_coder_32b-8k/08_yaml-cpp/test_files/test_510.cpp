#include <gtest/gtest.h>

#include "scanner.h"

#include "token.h"



using namespace YAML;



class SimpleKeyTest_510 : public ::testing::Test {

protected:

    Mark mark;

    std::size_t flowLevel = 0;

    Token tokenValid;

    IndentMarker indentMarkerValid;



    void SetUp() override {

        mark.column = 0;

        mark.line = 0;

        mark.index = 0;



        tokenValid = Token(TOKEN_TYPE_NONE, mark);

        indentMarkerValid = IndentMarker(0, INDENT_TYPE_BLOCK);



        simpleKey = SimpleKey(mark, flowLevel);

    }



    SimpleKey simpleKey;

};



TEST_F(SimpleKeyTest_510, InvalidateSetsStatusToInvalid_510) {

    // Arrange

    simpleKey.pIndent = &indentMarkerValid;

    simpleKey.pMapStart = &tokenValid;

    simpleKey.pKey = &tokenValid;



    // Act

    simpleKey.Invalidate();



    // Assert

    EXPECT_EQ(indentMarkerValid.status, IndentMarker::INVALID);

    EXPECT_EQ(tokenValid.status, Token::INVALID);

}



TEST_F(SimpleKeyTest_510, InvalidateWithNullIndentPointer_510) {

    // Arrange

    simpleKey.pMapStart = &tokenValid;

    simpleKey.pKey = &tokenValid;



    // Act

    simpleKey.Invalidate();



    // Assert

    EXPECT_EQ(tokenValid.status, Token::INVALID);

}



TEST_F(SimpleKeyTest_510, InvalidateWithNullMapStartPointer_510) {

    // Arrange

    simpleKey.pIndent = &indentMarkerValid;

    simpleKey.pKey = &tokenValid;



    // Act

    simpleKey.Invalidate();



    // Assert

    EXPECT_EQ(indentMarkerValid.status, IndentMarker::INVALID);

    EXPECT_EQ(tokenValid.status, Token::INVALID);

}



TEST_F(SimpleKeyTest_510, InvalidateWithNullKeyPointer_510) {

    // Arrange

    simpleKey.pIndent = &indentMarkerValid;

    simpleKey.pMapStart = &tokenValid;



    // Act

    simpleKey.Invalidate();



    // Assert

    EXPECT_EQ(indentMarkerValid.status, IndentMarker::INVALID);

    EXPECT_EQ(tokenValid.status, Token::INVALID);

}



TEST_F(SimpleKeyTest_510, InvalidateWithAllNullPointers_510) {

    // Arrange



    // Act

    simpleKey.Invalidate();



    // Assert

    // No pointers to modify, so no assertions needed

}
