#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>

using namespace Catch::Clara::Detail;

// We need to understand what ParseResultType values are available.
// Based on the interface, ParseState has a type() method returning ParseResultType.
// We'll test the observable behavior through the public interface.

class ParseStateTest_372 : public ::testing::Test {
protected:
    // Helper to create TokenStream if needed
};

// Test that type() returns the ParseResultType that was passed during construction
TEST_F(ParseStateTest_372, TypeReturnsMatchedWhenConstructedWithMatched_372) {
    TokenStream ts;
    ParseState state(ParseResultType::Matched, ts);
    EXPECT_EQ(state.type(), ParseResultType::Matched);
}

TEST_F(ParseStateTest_372, TypeReturnsNoMatchWhenConstructedWithNoMatch_372) {
    TokenStream ts;
    ParseState state(ParseResultType::NoMatch, ts);
    EXPECT_EQ(state.type(), ParseResultType::NoMatch);
}

TEST_F(ParseStateTest_372, TypeReturnsShortCircuitAllWhenConstructedWithShortCircuitAll_372) {
    TokenStream ts;
    ParseState state(ParseResultType::ShortCircuitAll, ts);
    EXPECT_EQ(state.type(), ParseResultType::ShortCircuitAll);
}

// Test that remainingTokens() returns a valid reference
TEST_F(ParseStateTest_372, RemainingTokensReturnsValidReference_372) {
    TokenStream ts;
    ParseState state(ParseResultType::Matched, ts);
    // Just verify we can call remainingTokens without crashing
    const TokenStream& remaining = state.remainingTokens();
    (void)remaining;  // suppress unused variable warning
}

// Test copy/move semantics - ParseState should be moveable since it takes TokenStream by value
TEST_F(ParseStateTest_372, MoveConstructionPreservesType_372) {
    TokenStream ts;
    ParseState state(ParseResultType::NoMatch, ts);
    ParseState movedState(std::move(state));
    EXPECT_EQ(movedState.type(), ParseResultType::NoMatch);
}

// Boundary: Constructing with empty TokenStream
TEST_F(ParseStateTest_372, ConstructWithEmptyTokenStream_372) {
    TokenStream ts;
    ParseState state(ParseResultType::Matched, ts);
    EXPECT_EQ(state.type(), ParseResultType::Matched);
}

// Test that type() is const-correct (can be called on const object)
TEST_F(ParseStateTest_372, TypeIsConstCorrect_372) {
    TokenStream ts;
    const ParseState state(ParseResultType::Matched, ts);
    EXPECT_EQ(state.type(), ParseResultType::Matched);
}

// Test that remainingTokens() is const-correct
TEST_F(ParseStateTest_372, RemainingTokensIsConstCorrect_372) {
    TokenStream ts;
    const ParseState state(ParseResultType::Matched, ts);
    const TokenStream& remaining = state.remainingTokens();
    (void)remaining;
}
