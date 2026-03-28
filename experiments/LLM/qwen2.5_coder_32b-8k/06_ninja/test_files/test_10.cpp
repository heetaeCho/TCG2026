#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "lexer.h"

#include "eval_env.h"



using ::testing::_;

using ::testing::Return;



class LexerTest : public ::testing::Test {

protected:

    Lexer lexer;

    EvalString eval_string;

    std::string error_message;

};



TEST_F(LexerTest_10, ReadVarValue_SuccessfulRead_10) {

    // Arrange

    lexer.Start("testfile", "VAR=value");

    bool result;



    // Act

    result = lexer.ReadVarValue(&eval_string, &error_message);



    // Assert

    EXPECT_TRUE(result);

    EXPECT_EQ(eval_string.Unparse(), "value");

    EXPECT_TRUE(error_message.empty());

}



TEST_F(LexerTest_10, ReadVarValue_EmptyInput_10) {

    // Arrange

    lexer.Start("testfile", "");

    bool result;



    // Act

    result = lexer.ReadVarValue(&eval_string, &error_message);



    // Assert

    EXPECT_FALSE(result);

    EXPECT_TRUE(eval_string.empty());

    EXPECT_FALSE(error_message.empty());

}



TEST_F(LexerTest_10, ReadVarValue_NoEqualSign_10) {

    // Arrange

    lexer.Start("testfile", "VARvalue");

    bool result;



    // Act

    result = lexer.ReadVarValue(&eval_string, &error_message);



    // Assert

    EXPECT_FALSE(result);

    EXPECT_TRUE(eval_string.empty());

    EXPECT_FALSE(error_message.empty());

}



TEST_F(LexerTest_10, ReadVarValue_ErrorInInput_10) {

    // Arrange

    lexer.Start("testfile", "VAR=value invalid");

    bool result;



    // Act

    result = lexer.ReadVarValue(&eval_string, &error_message);



    // Assert

    EXPECT_TRUE(result);

    EXPECT_EQ(eval_string.Unparse(), "value");

    EXPECT_TRUE(error_message.empty());

}



TEST_F(LexerTest_10, ReadVarValue_MissingVariableName_10) {

    // Arrange

    lexer.Start("testfile", "=value");

    bool result;



    // Act

    result = lexer.ReadVarValue(&eval_string, &error_message);



    // Assert

    EXPECT_FALSE(result);

    EXPECT_TRUE(eval_string.empty());

    EXPECT_FALSE(error_message.empty());

}
