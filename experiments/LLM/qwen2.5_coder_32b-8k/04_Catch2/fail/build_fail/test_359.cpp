#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



class TokenStreamTest_359 : public ::testing::Test {

protected:

    std::vector<std::string> args;

    TokenStream* tokenStream;



    void SetUp() override {

        args = {"arg1", "arg2", "arg3"};

        tokenStream = new TokenStream(args);

    }



    void TearDown() override {

        delete tokenStream;

    }

};



TEST_F(TokenStreamTest_359, InitialCountIsCorrect_359) {

    EXPECT_EQ(tokenStream->count(), args.size());

}



TEST_F(TokenStreamTest_359, IncrementOperatorUpdatesCount_359) {

    size_t initialCount = tokenStream->count();

    ++(*tokenStream);

    EXPECT_EQ(tokenStream->count(), initialCount - 1);

}



TEST_F(TokenStreamTest_359, DereferenceOperatorReturnsCorrectToken_359) {

    Token expectedToken;

    expectedToken.value = args.front(); // Assuming Token has a value field

    EXPECT_EQ((*tokenStream)->value, expectedToken.value);

}



TEST_F(TokenStreamTest_359, BoolConversionReflectsExhaustion_359) {

    while (static_cast<bool>(*tokenStream)) {

        ++(*tokenStream);

    }

    EXPECT_FALSE(static_cast<bool>(*tokenStream));

}



TEST_F(TokenStreamTest_359, BoundaryConditionEmptyArgs_359) {

    TokenStream emptyTokenStream(std::vector<std::string>{});

    EXPECT_EQ(emptyTokenStream.count(), 0u);

    EXPECT_FALSE(static_cast<bool>(emptyTokenStream));

}



TEST_F(TokenStreamTest_359, ExceptionalCaseIncrementPastEnd_359) {

    while (static_cast<bool>(*tokenStream)) {

        ++(*tokenStream);

    }

    // Assuming no exception is thrown and the stream just remains exhausted

    EXPECT_FALSE(static_cast<bool>(*tokenStream));

}
