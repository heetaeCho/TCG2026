// ExeName_parse_tests_666.cpp
#include <gtest/gtest.h>

// Catch2 / Clara internals used by the public interface under test
#include <catch2/internal/catch_clara.hpp>

using Catch::Clara::ExeName;
using Catch::Detail::InternalParseResult;
using Catch::Detail::TokenStream;
using Catch::Detail::Token;
using Catch::Detail::TokenType;
using Catch::Detail::ParseState;
using Catch::Detail::ParseResultType;

namespace {

// Small helper to build a TokenStream from words, without assuming any internal logic.
TokenStream makeWordStream(std::initializer_list<std::string> words) {
    std::vector<Token> toks;
    toks.reserve(words.size());
    for (const auto& w : words) {
        toks.emplace_back(TokenType::Word, w);
    }
    return TokenStream(toks.begin(), toks.end());
}

} // namespace

// 1) Normal operation: parse should succeed with a parse *state* that reports `NoMatch`
//    and it should not consume tokens.
//    Rationale: The exposed behavior of ExeName::parse returns an ok ParseState with NoMatch,
//    and forwards the (unchanged) token stream.
TEST(ExeNameParse_666, ParseReturnsOkAndNoMatchWithoutConsumingTokens_666) {
    ExeName sut;

    auto tokens = makeWordStream({"--flag", "value", "pos1"});
    // Keep a copy of the stream to check that the first token stays the same after parse
    auto tokensCopy = tokens;

    InternalParseResult res = sut.parse("prog-name", tokens);

    // Observable outcomes to verify (no assumptions about private state):
    // a) Result is "ok" (no error)
    ASSERT_TRUE(res.succeeded()) << "Expected parse to succeed (ok state).";

    // b) The parse *state* says NoMatch
    const ParseState& st = res.value();
    EXPECT_EQ(st.type(), ParseResultType::NoMatch) << "ExeName should report NoMatch.";

    // c) Remaining tokens are unchanged (no consumption)
    const TokenStream& remaining = st.remainingTokens();
    // Compare the first token's spelling to ensure no consumption
    ASSERT_FALSE(remaining.atEnd()) << "Remaining tokens should not be empty.";
    ASSERT_FALSE(tokensCopy.atEnd()) << "Original tokens should not be empty.";
    EXPECT_EQ((*remaining).token, (*tokensCopy).token)
        << "First remaining token should be identical to the original first token.";

    // Also check that the sequence length is unchanged by walking both streams in lockstep.
    auto walk = remaining;
    auto walkCopy = tokensCopy;
    while (!walk.atEnd() && !walkCopy.atEnd()) {
        EXPECT_EQ((*walk).token, (*walkCopy).token);
        ++walk;
        ++walkCopy;
    }
    EXPECT_TRUE(walk.atEnd() && walkCopy.atEnd())
        << "Remaining token stream length should match the original.";
}

// 2) Boundary condition: empty token stream.
//    Expect still ok + NoMatch, and (trivially) no tokens consumed.
TEST(ExeNameParse_666, EmptyTokenStreamYieldsOkNoMatchAndStaysEmpty_666) {
    ExeName sut;

    auto tokens = makeWordStream({}); // empty
    InternalParseResult res = sut.parse("prog", tokens);

    ASSERT_TRUE(res.succeeded());
    const ParseState& st = res.value();
    EXPECT_EQ(st.type(), ParseResultType::NoMatch);

    const TokenStream& remaining = st.remainingTokens();
    EXPECT_TRUE(remaining.atEnd()) << "Remaining tokens should still be empty.";
}

// 3) Input variance: different exe-name strings should not affect the observable result.
//    (Still ok + NoMatch and no token consumption.)
TEST(ExeNameParse_666, DifferentExeNamesDoNotAffectNoMatchOrTokens_666) {
    ExeName sut;

    auto tokens = makeWordStream({"-a", "-b", "x"});
    auto tokensCopy = tokens;

    InternalParseResult res1 = sut.parse("", tokens);
    ASSERT_TRUE(res1.succeeded());
    EXPECT_EQ(res1.value().type(), ParseResultType::NoMatch);

    // Compare tokens against original copy
    auto rem1 = res1.value().remainingTokens();
    // First token unchanged
    ASSERT_FALSE(rem1.atEnd());
    ASSERT_FALSE(tokensCopy.atEnd());
    EXPECT_EQ((*rem1).token, (*tokensCopy).token);

    // Try again with a different exe name
    InternalParseResult res2 = sut.parse("another-exe-name", tokensCopy);
    ASSERT_TRUE(res2.succeeded());
    EXPECT_EQ(res2.value().type(), ParseResultType::NoMatch);

    auto rem2 = res2.value().remainingTokens();
    ASSERT_FALSE(rem2.atEnd());
    EXPECT_EQ((*rem2).token, (*tokensCopy).token)
        << "Token stream should still be untouched across different exe-name inputs.";
}
