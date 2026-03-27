#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



// Test Fixture

class TokenStreamTest_356 : public ::testing::Test {

protected:

    std::vector<Token> args;

    TokenStream tokenStream;



    void SetUp() override {

        args = {Token(), Token(), Token()};

        tokenStream = TokenStream(args);

    }

};



// Normal operation tests



TEST_F(TokenStreamTest_356, InitialStateReturnsTrue_356) {

    EXPECT_TRUE(static_cast<bool>(tokenStream));

}



TEST_F(TokenStreamTest_356, IncrementOperatorAdvancesIterator_356) {

    auto initialCount = tokenStream.count();

    ++tokenStream;

    EXPECT_EQ(tokenStream.count(), initialCount - 1);

}



TEST_F(TokenStreamTest_356, DereferenceOperatorReturnsCurrentToken_356) {

    Token currentToken = *tokenStream;

    EXPECT_TRUE(currentToken == args.front());

}



// Boundary conditions tests



TEST_F(TokenStreamTest_356, EmptyConstructorInitializesEmptyStream_356) {

    TokenStream emptyStream(std::vector<Token>{});

    EXPECT_FALSE(static_cast<bool>(emptyStream));

}



TEST_F(TokenStreamTest_356, IncrementOnLastTokenSetsStreamToFalse_356) {

    while (tokenStream) {

        ++tokenStream;

    }

    EXPECT_FALSE(static_cast<bool>(tokenStream));

}



// Exceptional or error cases tests



TEST_F(TokenStreamTest_356, DereferenceOperatorThrowsWhenEmpty_356) {

    TokenStream emptyStream(std::vector<Token>{});

    EXPECT_THROW(*emptyStream, std::out_of_range);

}



TEST_F(TokenStreamTest_356, ArrowOperatorThrowsWhenEmpty_356) {

    TokenStream emptyStream(std::vector<Token>{});

    EXPECT_THROW(emptyStream->, std::out_of_range);

}
