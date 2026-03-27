#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"

#include <vector>



using namespace Catch::Clara::Detail;



class TokenStreamTest_652 : public ::testing::Test {

protected:

    std::vector<Token> args;

    TokenStream* tokenStream;



    void SetUp() override {

        args = {Token(), Token(), Token()};

        tokenStream = new TokenStream(args.begin(), args.end());

    }



    void TearDown() override {

        delete tokenStream;

    }

};



TEST_F(TokenStreamTest_652, InitialCount_652) {

    EXPECT_EQ(tokenStream->count(), 3);

}



TEST_F(TokenStreamTest_652, IncrementOperatorRemovesFirstToken_652) {

    ++(*tokenStream);

    EXPECT_EQ(tokenStream->count(), 2);

}



TEST_F(TokenStreamTest_652, DoubleIncrementOperatorRemovesTwoTokens_652) {

    ++(*tokenStream);

    ++(*tokenStream);

    EXPECT_EQ(tokenStream->count(), 1);

}



TEST_F(TokenStreamTest_652, TripleIncrementOperatorLeavesOneToken_652) {

    ++(*tokenStream);

    ++(*tokenStream);

    ++(*tokenStream);

    EXPECT_EQ(tokenStream->count(), 1);

}



TEST_F(TokenStreamTest_652, IncrementPastEndDoesNotUnderflow_652) {

    for (size_t i = 0; i < args.size(); ++i) {

        ++(*tokenStream);

    }

    ++(*tokenStream); // Should not cause issues

    EXPECT_EQ(tokenStream->count(), 1);

}



TEST_F(TokenStreamTest_652, DereferenceOperatorReturnsCurrentToken_652) {

    Token firstToken = *tokenStream;

    EXPECT_TRUE(firstToken == args[0]);

    ++(*tokenStream);

    Token secondToken = *tokenStream;

    EXPECT_TRUE(secondToken == args[1]);

}



TEST_F(TokenStreamTest_652, ArrowOperatorReturnsPointerToCurrentToken_652) {

    const Token* firstTokenPtr = tokenStream->operator->();

    EXPECT_EQ(firstTokenPtr, &args[0]);

    ++(*tokenStream);

    const Token* secondTokenPtr = tokenStream->operator->();

    EXPECT_EQ(secondTokenPtr, &args[1]);

}



TEST_F(TokenStreamTest_652, BoolOperatorReturnsTrueWhenTokensLeft_652) {

    EXPECT_TRUE(static_cast<bool>(*tokenStream));

    ++(*tokenStream);

    EXPECT_TRUE(static_cast<bool>(*tokenStream));

}



TEST_F(TokenStreamTest_652, BoolOperatorReturnsFalseWhenNoTokensLeft_652) {

    for (size_t i = 0; i < args.size(); ++i) {

        ++(*tokenStream);

    }

    EXPECT_FALSE(static_cast<bool>(*tokenStream));

}
