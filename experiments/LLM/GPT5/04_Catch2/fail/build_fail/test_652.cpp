// File: token_stream_increment_652_tests.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;

class TokenStreamTest_652 : public ::testing::Test {
protected:
    // Helper to build a stream from plain argv-like strings via Args.
    static TokenStream MakeStreamFromArgs(const std::vector<std::string>& argv) {
        Args args;
        // We only rely on the existence of Args::m_args as hinted by the header snippet.
        // If your Args type provides a different way to construct, replace the two lines below
        // with the project-appropriate construction, still keeping the test logic intact.
        args.m_args = argv;
        return TokenStream(args);
    }
};

// 1) Basic contract: prefix ++ returns a reference to the same object.
TEST_F(TokenStreamTest_652, PrefixIncrement_ReturnsSelf_652) {
    auto ts = MakeStreamFromArgs({"one"});
    TokenStream& ret = ++ts;
    EXPECT_EQ(&ret, &ts);
}

// 2) Normal operation: advancing reduces the observable count by exactly 1.
TEST_F(TokenStreamTest_652, Increment_DecrementsCountByOne_652) {
    auto ts = MakeStreamFromArgs({"one", "two", "three"});
    ASSERT_TRUE(static_cast<bool>(ts));       // should have at least one token
    const auto before = ts.count();
    ++ts;
    const auto after = ts.count();
    ASSERT_GE(before, static_cast<size_t>(1));
    EXPECT_EQ(after + 1, before);             // count decreased by exactly one
}

// 3) Chaining ++ twice reduces count by 2, when there are at least two tokens.
TEST_F(TokenStreamTest_652, ChainedIncrement_DecrementsByTwo_652) {
    auto ts = MakeStreamFromArgs({"a", "b", "c"});
    ASSERT_TRUE(static_cast<bool>(ts));
    const auto before = ts.count();
    ++(++ts);                                 // chained prefix increments
    const auto after = ts.count();
    // If there were < 2 tokens, behavior still should not increase count.
    ASSERT_GE(before, static_cast<size_t>(2));
    EXPECT_EQ(after + 2, before);
}

// 4) Dereference changes after ++ (observable token progression).
//    We do not assume exact token contents; only that we advance to a different token.
TEST_F(TokenStreamTest_652, DerefYieldsNextTokenAfterIncrement_652) {
    auto ts = MakeStreamFromArgs({"first", "second"});
    ASSERT_TRUE(static_cast<bool>(ts));
    const auto firstTok = *ts;                // observable Token
    ++ts;
    ASSERT_TRUE(static_cast<bool>(ts));       // still has at least one token left
    const auto secondTok = *ts;
    // We only rely on Token being comparable or at least inequality-comparable.
    EXPECT_NE(firstTok, secondTok);
}

// 5) Boundary: consuming all tokens leads to falsy stream; further ++ keeps it falsy.
TEST_F(TokenStreamTest_652, IncrementAtEnd_RemainsExhausted_652) {
    auto ts = MakeStreamFromArgs({"only"});
    ASSERT_TRUE(static_cast<bool>(ts));
    ++ts;                                     // consume the single token
    EXPECT_FALSE(static_cast<bool>(ts));      // stream is now exhausted

    // Calling ++ on an already-exhausted stream must be safe and keep it exhausted.
    ++ts;
    EXPECT_FALSE(static_cast<bool>(ts));
}

// 6) Buffer-heavy scenario: if initial buffer holds >=2 tokens internally,
//    one ++ erases the front buffered token (net effect: count still drops by 1).
//    We cannot (and do not) assert internal buffering, only the public count contract.
TEST_F(TokenStreamTest_652, BufferedAdvance_StillDecrementsCountByOne_652) {
    // Use multiple argv entries to maximize likelihood of initial multi-token buffering
    // (without relying on internal details).
    auto ts = MakeStreamFromArgs({"--opt", "val", "-f", "pos"});
    ASSERT_TRUE(static_cast<bool>(ts));
    const auto before = ts.count();
    ++ts;
    const auto after = ts.count();
    EXPECT_EQ(after + 1, before);
}

// 7) Safety: ++ is noexcept from the perspective of the observable interface.
//    We can at least verify it does not throw with empty input & with non-empty input.
TEST_F(TokenStreamTest_652, Increment_DoesNotThrow_652) {
    // Empty stream case
    {
        auto empty = MakeStreamFromArgs({});
        EXPECT_NO_THROW(++empty);
    }
    // Non-empty stream case
    {
        auto ts = MakeStreamFromArgs({"x", "y"});
        EXPECT_NO_THROW(++ts);
    }
}
