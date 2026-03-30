#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



class ParseStateTest_373 : public ::testing::Test {

protected:

    TokenStream tokens;

    ParseState parseState;



    ParseStateTest_373() 

        : tokens(), 

          parseState(ParseResultType::Ok, tokens) {}

};



TEST_F(ParseStateTest_373, RemainingTokens_ReturnsCorrectReference_373) {

    EXPECT_EQ(&parseState.remainingTokens(), &tokens);

}



// Assuming ParseResultType has some known values like Ok, Error etc.

TEST_F(ParseStateTest_373, Type_ReturnsCorrectValue_373) {

    EXPECT_EQ(parseState.type(), ParseResultType::Ok);

}



// Boundary condition test for TokenStream being empty

TEST_F(ParseStateTest_373, RemainingTokens_EmptyTokenStream_373) {

    TokenStream emptyTokens;

    ParseState emptyParseState(ParseResultType::Ok, emptyTokens);

    EXPECT_TRUE(emptyParseState.remainingTokens().empty());

}



// Exceptional case test if applicable (if ParseResultType can be Error)

TEST_F(ParseStateTest_373, Type_ReturnsError_373) {

    TokenStream errorTokens;

    ParseState errorParseState(ParseResultType::Error, errorTokens);

    EXPECT_EQ(errorParseState.type(), ParseResultType::Error);

}
