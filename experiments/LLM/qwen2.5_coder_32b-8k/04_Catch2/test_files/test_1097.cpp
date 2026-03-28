#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



class TokenStreamTest_1097 : public ::testing::Test {

protected:

    std::vector<Token> args;

    TokenStream tokenStream;



    TokenStreamTest_1097() : args({Token("arg1"), Token("arg2")}), tokenStream(args) {}

};



TEST_F(TokenStreamTest_1097, InitialCount_1097) {

    EXPECT_EQ(tokenStream.count(), 2);

}



TEST_F(TokenStreamTest_1097, IncrementOperator_1097) {

    ++tokenStream;

    EXPECT_EQ(tokenStream.count(), 1);

}



TEST_F(TokenStreamTest_1097, DereferenceOperator_1097) {

    EXPECT_EQ((*tokenStream).value, "arg1");

}



TEST_F(TokenStreamTest_1097, ArrowOperator_1097) {

    EXPECT_EQ(tokenStream->value, "arg1");

}



TEST_F(TokenStreamTest_1097, BoolConversion_1097) {

    EXPECT_TRUE(static_cast<bool>(tokenStream));

    ++tokenStream;

    ++tokenStream;

    EXPECT_FALSE(static_cast<bool>(tokenStream));

}



TEST_F(TokenStreamTest_1097, EmptyInitialization_1097) {

    TokenStream emptyTokenStream(std::vector<Token>().begin(), std::vector<Token>().end());

    EXPECT_EQ(emptyTokenStream.count(), 0);

    EXPECT_FALSE(static_cast<bool>(emptyTokenStream));

}



TEST_F(TokenStreamTest_1097, SingleElement_1097) {

    std::vector<Token> singleArg({Token("single")});

    TokenStream singleTokenStream(singleArg.begin(), singleArg.end());

    EXPECT_EQ(singleTokenStream.count(), 1);

    EXPECT_TRUE(static_cast<bool>(singleTokenStream));

    EXPECT_EQ((*singleTokenStream).value, "single");

    ++singleTokenStream;

    EXPECT_FALSE(static_cast<bool>(singleTokenStream));

}
