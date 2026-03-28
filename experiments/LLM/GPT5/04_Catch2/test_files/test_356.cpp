// File: token_stream_bool_tests_356.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Detail::TokenStream;

namespace {

// Helper: build a Token vector in the least-assuming way possible.
// We only rely on the fact that Token is copyable and default-constructible,
// or at least constructible from something trivially available. If Token has
// a default ctor, we use it; otherwise, we fall back to constructing from a
// string if available (SFINAE is overkill for a test, so we keep it simple).
template <typename TokenT>
std::vector<TokenT> MakeNTokens(size_t n) {
    std::vector<TokenT> v;
    v.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        // Prefer default construction if possible.
        // If Token does not have a default ctor in the real codebase,
        // replace the line below with the simplest valid ctor for Token.
        v.emplace_back(TokenT{});
    }
    return v;
}

} // namespace

// Normal operation: non-empty stream should be truthy.
TEST(TokenStreamTest_356, BoolTrue_WhenNonEmptyRange_356) {
    using Token = decltype(*std::declval<TokenStream&>().operator->());
    // Build a minimal non-empty token sequence
    auto tokens = MakeNTokens<std::remove_cv_t<std::remove_pointer_t<decltype(std::declval<const Token*>())>>>(1);

    TokenStream ts(tokens.begin(), tokens.end());
    EXPECT_TRUE(static_cast<bool>(ts));
}

// Boundary: empty range should be falsy.
TEST(TokenStreamTest_356, BoolFalse_WhenEmptyRange_356) {
    using Token = decltype(*std::declval<TokenStream&>().operator->());
    std::vector<std::remove_cv_t<std::remove_pointer_t<decltype(std::declval<const Token*>())>>> tokens; // empty

    TokenStream ts(tokens.begin(), tokens.end());
    EXPECT_FALSE(static_cast<bool>(ts));
}

// Iteration behavior: truthiness transitions to false after consuming all elements.
TEST(TokenStreamTest_356, BoolBecomesFalse_AfterConsumingAll_356) {
    using Token = decltype(*std::declval<TokenStream&>().operator->());
    auto tokens = MakeNTokens<std::remove_cv_t<std::remove_pointer_t<decltype(std::declval<const Token*>())>>>(3);

    TokenStream ts(tokens.begin(), tokens.end());

    // Initially should be true (non-empty)
    ASSERT_TRUE(static_cast<bool>(ts));

    // Consume items one by one; after last increment, stream should become false
    size_t observed = 0;
    while (static_cast<bool>(ts)) {
        ++ts;       // advance
        ++observed; // only counts how many times we advanced while truthy
    }
    // We cannot assert internal counts; we only assert final state (false)
    EXPECT_FALSE(static_cast<bool>(ts));
    // observed should be >= 1 and <= number of inputs; we don't rely on precise internals
    EXPECT_GE(observed, 1u);
    EXPECT_LE(observed, 3u);
}

// Idempotence at end: Once falsy, staying falsy on further increments (observable).
TEST(TokenStreamTest_356, RemainsFalse_WhenAdvancedPastEnd_356) {
    using Token = decltype(*std::declval<TokenStream&>().operator->());
    auto tokens = MakeNTokens<std::remove_cv_t<std::remove_pointer_t<decltype(std::declval<const Token*>())>>>(1);

    TokenStream ts(tokens.begin(), tokens.end());
    ASSERT_TRUE(static_cast<bool>(ts)); // non-empty

    // Advance once; now it should be at end (for a single element)
    ++ts;
    EXPECT_FALSE(static_cast<bool>(ts));

    // Further increments should not make it truthy again (observable contract)
    ++ts;
    EXPECT_FALSE(static_cast<bool>(ts));
}

// Robustness: Alternating check/advance across multiple elements keeps truthiness true
// until the last element is consumed, then becomes false.
TEST(TokenStreamTest_356, StaysTrue_UntilLastElementConsumed_ThenFalse_356) {
    using Token = decltype(*std::declval<TokenStream&>().operator->());
    auto tokens = MakeNTokens<std::remove_cv_t<std::remove_pointer_t<decltype(std::declval<const Token*>())>>>(2);

    TokenStream ts(tokens.begin(), tokens.end());
    ASSERT_TRUE(static_cast<bool>(ts)); // element #1 available

    // After first advance, still should be true (element #2 available)
    ++ts;
    EXPECT_TRUE(static_cast<bool>(ts));

    // After second advance, should become false (no elements left)
    ++ts;
    EXPECT_FALSE(static_cast<bool>(ts));
}
