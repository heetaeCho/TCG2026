#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "lexer.h"

#include "eval_env.h"



using ::testing::_;

using ::testing::Return;



class LexerTest : public ::testing::Test {

protected:

    Lexer lexer;

};



TEST_F(LexerTest_9, ReadPath_SuccessfulRead_9) {

    EvalString path;

    std::string err;

    bool result = lexer.ReadPath(&path, &err);

    EXPECT_TRUE(result);

    EXPECT_TRUE(err.empty());

}



TEST_F(LexerTest_9, ReadPath_EmptyInput_ReturnsFalse_9) {

    Lexer emptyLexer("");

    EvalString path;

    std::string err;

    bool result = emptyLexer.ReadPath(&path, &err);

    EXPECT_FALSE(result);

    EXPECT_FALSE(err.empty());

}



TEST_F(LexerTest_9, ReadPath_NullPathPtr_ThrowsError_9) {

    std::string err;

    EXPECT_DEATH(lexer.ReadPath(nullptr, &err), ".*");

}



TEST_F(LexerTest_9, ReadPath_NullErrPtr_ThrowsError_9) {

    EvalString path;

    EXPECT_DEATH(lexer.ReadPath(&path, nullptr), ".*");

}



TEST_F(LexerTest_9, ReadPath_ValidInput_ReturnsTrueAndPopulatesPath_9) {

    Lexer lexer("valid/path/to/file");

    EvalString path;

    std::string err;

    bool result = lexer.ReadPath(&path, &err);

    EXPECT_TRUE(result);

    EXPECT_EQ(path.Unparse(), "valid/path/to/file");

}



TEST_F(LexerTest_9, ReadPath_BadInput_ReturnsFalseAndPopulatesError_9) {

    Lexer lexer("bad:path|with*invalid\\chars");

    EvalString path;

    std::string err;

    bool result = lexer.ReadPath(&path, &err);

    EXPECT_FALSE(result);

    EXPECT_FALSE(err.empty());

}
