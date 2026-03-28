#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



class TokenStreamTest_358 : public ::testing::Test {

protected:

    std::vector<Token> args;

    TokenStream tokenStream;



    TokenStreamTest_358() : args({Token(), Token()}), tokenStream(args) {}

};



TEST_F(TokenStreamTest_358, InitialCountIsZero_358) {

    EXPECT_EQ(tokenStream.count(), 0);

}



TEST_F(TokenStreamTest_358, IncrementOperatorIncreasesCount_358) {

    ++tokenStream;

    EXPECT_EQ(tokenStream.count(), 1);

}



TEST_F(TokenStreamTest_358, DoubleIncrementOperatorIncreasesCountTwice_358) {

    ++tokenStream;

    ++tokenStream;

    EXPECT_EQ(tokenStream.count(), 2);

}



TEST_F(TokenStreamTest_358, DereferenceOperatorReturnsFirstTokenAfterIncrement_358) {

    ++tokenStream;

    EXPECT_EQ(*tokenStream, args[0]);

}



TEST_F(TokenStreamTest_358, ArrowOperatorPointsToFirstTokenAfterIncrement_358) {

    ++tokenStream;

    EXPECT_EQ(*tokenStream.operator->(), args[0]);

}



TEST_F(TokenStreamTest_358, BoolConversionReturnsTrueWhenTokensAreAvailable_358) {

    EXPECT_TRUE(static_cast<bool>(tokenStream));

}



TEST_F(TokenStreamTest_358, BoolConversionReturnsFalseAfterExhaustingTokens_358) {

    ++tokenStream;

    ++tokenStream;

    EXPECT_FALSE(static_cast<bool>(tokenStream));

}



TEST_F(TokenStreamTest_358, DereferenceOperatorThrowsWhenNoTokensAvailable_358) {

    ++tokenStream;

    ++tokenStream;

    EXPECT_THROW(*tokenStream, std::runtime_error);

}



TEST_F(TokenStreamTest_358, ArrowOperatorThrowsWhenNoTokensAvailable_358) {

    ++tokenStream;

    ++tokenStream;

    EXPECT_THROW(tokenStream.operator->(), std::runtime_error);

}
