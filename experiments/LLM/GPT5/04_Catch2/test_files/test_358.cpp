// TokenStream_operator_deref_tests_358.cpp
#include <gtest/gtest.h>

// Include the real header from your project build.
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Detail::TokenStream;

namespace {

// Helper to silence “unused variable” warnings in EXPECT_NO_FATAL_FAILURE blocks.
template <typename T>
void DoNotOptimizeAway(const T&) {}

} // namespace

// NOTE:
// - We do NOT infer any internal logic.
// - We use only the public interface: iterator-ctor, operator*, operator->, operator++,
//   explicit operator bool(), and count() (only when helpful for guards).
// - Death tests rely on the assertion present in operator* when the buffer is empty.

// Normal operation: dereferencing a non-empty stream should NOT trigger the assertion.
TEST(TokenStreamTest_358, DerefDoesNotAssertWhenNonEmpty_358) {
    // Arrange: create a small token source. We do not depend on Token internals;
    // we just require that the iterator range is non-empty for the stream to have tokens.
    // The real implementation defines Iterator/Token; the header will provide these.
    using Iterator = decltype(
        std::declval<TokenStream&>(), // just to make sure we include the header
        std::declval<TokenStream const&>(), // avoid unused warnings
        std::declval<void>(), // no-op
        std::declval<TokenStream>() // and get us a type context
    ); // (This line is only to keep the compiler happy about including the header.)

    // We assume the real header provides a valid way to construct via iterators.
    // To keep the test strictly on public surface, we build a minimal container of tokens
    // and use its begin()/end() as iterators.
    // The concrete Token type is available from the header; we do not examine it.
    std::vector<Catch::Clara::Detail::Token> backing(1); // 1 token => non-empty

    TokenStream ts(backing.begin(), backing.end());

    // Act & Assert: deref must not hit the internal assert.
    EXPECT_NO_FATAL_FAILURE({
        auto t = *ts;
        DoNotOptimizeAway(t);
    });

    // Also check that operator-> returns a non-null pointer when dereference is valid.
    EXPECT_NO_FATAL_FAILURE({
        auto ptr = ts.operator->();
        EXPECT_NE(ptr, nullptr);
    });
}

// Exceptional/error case: dereferencing an empty stream should trigger the assertion.
// This is an observable behavior via death test due to assert(!m_tokenBuffer.empty()).
TEST(TokenStreamTest_358, DerefOnEmptyStreamAsserts_358) {
    // Arrange: empty source -> iterator range is empty
    std::vector<Catch::Clara::Detail::Token> empty;

    // Construct with an empty iterator range. By interface contract, the buffer will
    // be empty until/if the implementation loads something; deref should assert.
    TokenStream ts(empty.begin(), empty.end());

    // Act & Assert: operator* should trigger the debug assertion -> death test.
    // Death tests typically require a regex; we don't depend on the exact message.
    EXPECT_DEATH(
        {
            // NOLINTNEXTLINE(bugprone-use-after-move)
            (void)*ts;
        },
        ".*"
    );
}

// Boundary/progression: after pre-incrementing a single-token stream, dereference should die.
// This checks the interaction of operator++ with operator*, without asserting internal logic.
TEST(TokenStreamTest_358, DerefAfterExhaustionAsserts_358) {
    // Arrange: single-token range
    std::vector<Catch::Clara::Detail::Token> backing(1);

    TokenStream ts(backing.begin(), backing.end());

    // Sanity: first deref is fine
    EXPECT_NO_FATAL_FAILURE({
        auto t0 = *ts;
        DoNotOptimizeAway(t0);
    });

    // Act: advance the stream (consuming the only token)
    ++ts;

    // Assert: now dereferencing should assert (stream exhausted)
    EXPECT_DEATH(
        {
            (void)*ts;
        },
        ".*"
    );
}

