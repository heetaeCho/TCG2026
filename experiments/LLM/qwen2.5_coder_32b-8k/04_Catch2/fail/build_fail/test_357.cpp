#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



class TokenStreamTest_357 : public ::testing::Test {

protected:

    std::vector<Token> args;

    TokenStream tokenStream;



    TokenStreamTest_357() : args({Token(), Token()}), tokenStream(args) {}

};



TEST_F(TokenStreamTest_357, CountReturnsCorrectValueInitially_357) {

    EXPECT_EQ(tokenStream.count(), 2);

}



TEST_F(TokenStreamTest_357, IncrementOperatorReducesCount_357) {

    ++tokenStream;

    EXPECT_EQ(tokenStream.count(), 1);

}



TEST_F(TokenStreamTest_357, CountReturnsZeroAfterAllTokensConsumed_357) {

    ++tokenStream;

    ++tokenStream;

    EXPECT_EQ(tokenStream.count(), 0);

}



TEST_F(TokenStreamTest_357, BoolOperatorReturnsTrueInitially_357) {

    EXPECT_TRUE(static_cast<bool>(tokenStream));

}



TEST_F(TokenStreamTest_357, BoolOperatorReturnsFalseWhenAllTokensConsumed_357) {

    ++tokenStream;

    ++tokenStream;

    EXPECT_FALSE(static_cast<bool>(tokenStream));

}
