#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"

#include <type_traits>



using namespace Catch::Clara::Detail;



class ParseStateTest_372 : public ::testing::Test {

protected:

    TokenStream createTokenStream() {

        // Assuming TokenStream has a constructor that can be called without arguments

        return TokenStream();

    }

};



TEST_F(ParseStateTest_372, TypeReturnsCorrectValue_372) {

    ParseResultType expectedType = ParseResultType::Parsed;

    TokenStream tokens = createTokenStream();

    ParseState state(expectedType, tokens);

    

    EXPECT_EQ(state.type(), expectedType);

}



TEST_F(ParseStateTest_372, RemainingTokensReturnsCorrectValue_372) {

    TokenStream expectedTokens = createTokenStream();

    ParseResultType type = ParseResultType::Parsed;

    ParseState state(type, expectedTokens);

    

    EXPECT_EQ(&state.remainingTokens(), &expectedTokens);

}



TEST_F(ParseStateTest_372, TypeBoundaryCondition_372) {

    ParseResultType boundaryType = static_cast<ParseResultType>(-1); // Assuming ParseResultType is an enum

    TokenStream tokens = createTokenStream();

    ParseState state(boundaryType, tokens);

    

    EXPECT_EQ(state.type(), boundaryType);

}



TEST_F(ParseStateTest_372, RemainingTokensBoundaryCondition_372) {

    TokenStream emptyTokens;

    ParseResultType type = ParseResultType::Parsed;

    ParseState state(type, emptyTokens);

    

    EXPECT_TRUE(state.remainingTokens().empty());

}
