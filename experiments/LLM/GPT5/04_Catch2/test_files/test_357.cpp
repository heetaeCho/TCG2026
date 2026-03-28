// File: tokenstream_count_tests_357.cpp
#include <gtest/gtest.h>
#include "Catch2/src/catch2/internal/catch_clara.hpp"

using Catch::Clara::Detail::TokenStream;

class TokenStreamTest_357 : public ::testing::Test {
protected:
    // For convenience, use the Token type from the same namespace.
    using Token = Catch::Clara::Detail::Token;
};

// [Normal] Construct with an empty range -> count() should be 0
TEST_F(TokenStreamTest_357, EmptyRangeCountIsZero_357) {
    std::vector<Token> tokens; // empty
    TokenStream ts(tokens.begin(), tokens.end());

    EXPECT_EQ(ts.count(), static_cast<size_t>(0));
}

// [Normal] Construct with a non-empty range -> count() equals number of tokens
TEST_F(TokenStreamTest_357, NonEmptyRangeCountMatchesSize_357) {
    std::vector<Token> tokens(5); // five default tokens
    TokenStream ts(tokens.begin(), tokens.end());

    EXPECT_EQ(ts.count(), static_cast<size_t>(5));
}

// [Boundary] Single element range -> count() is 1; after one increment, 0
TEST_F(TokenStreamTest_357, SingleElementThenAdvance_357) {
    std::vector<Token> tokens(1);
    TokenStream ts(tokens.begin(), tokens.end());

    ASSERT_EQ(ts.count(), static_cast<size_t>(1));

    // Advance once; ensure count reflects that we consumed one token.
    ++ts;
    EXPECT_EQ(ts.count(), static_cast<size_t>(0));
}

// [Observable behavior] Advancing reduces remaining count
// (without asserting *how* it advances internally)
TEST_F(TokenStreamTest_357, AdvanceDecreasesCount_357) {
    std::vector<Token> tokens(3);
    TokenStream ts(tokens.begin(), tokens.end());

    ASSERT_EQ(ts.count(), static_cast<size_t>(3));

    ++ts;
    EXPECT_EQ(ts.count(), static_cast<size_t>(2));

    ++ts;
    EXPECT_EQ(ts.count(), static_cast<size_t>(1));
}

// [End-state] Exhaust the stream using its boolean conversion;
// count() should report 0 at end.
TEST_F(TokenStreamTest_357, ExhaustingStreamLeadsToZeroCount_357) {
    std::vector<Token> tokens(4);
    TokenStream ts(tokens.begin(), tokens.end());

    // Drive the stream to exhaustion through its public interface.
    while (static_cast<bool>(ts)) {
        ++ts;
    }
    EXPECT_EQ(ts.count(), static_cast<size_t>(0));
}

// [Constructor path] If the Args-based constructor is available in this build,
// verify count() equals the size of Args' underlying sequence.
// This test compiles/executes only if Args is visible.
TEST_F(TokenStreamTest_357, ArgsConstructorCountMatchesInputSize_357) {
#ifdef __cpp_lib_void_t
    // Try to detect Args by ADL; if not available, this block can be adapted
#endif
    // Some builds of Catch2 expose an Args type used by TokenStream's ctor.
    // We guard usage with a try-compile style via constexpr if on a trait.
    // To keep the test standard-compliant and black-box, we SFINAE on availability.

    struct HasArgsCtors {
        template <typename T>
        static auto test(int) -> decltype(
            TokenStream(std::declval<const T&>()), std::true_type{});
        template <typename>
        static auto test(...) -> std::false_type;
    };

    using ArgsVisible = decltype(HasArgsCtors::test<Catch::Clara::Detail::Args>(0));
    if constexpr (ArgsVisible::value) {
        using Args = Catch::Clara::Detail::Args;
        // Create Args with N tokens; depends on Args API.
        // We do not rely on any internals beyond what the interface implies:
        // that the ctor accepts an Args containing a sequence of tokens.
        std::vector<Token> tokens(6);
        Args args;
        // Prefer a minimal, observable way to fill args with tokens if API allows.
        // If Args exposes an append/push or is constructible from a container,
        // use that. Otherwise, skip the rest to avoid assumptions.
        // (This block is intentionally conservative and non-invasive.)

        // If Args provides m_args publicly (as implied by the constructor definition),
        // we can populate it directly; otherwise, we skip to avoid breaking encapsulation.
        if constexpr (std::is_member_object_pointer_v<decltype(&Args::m_args)>) {
            args.m_args = tokens; // uses only public member as implied by header snippet
            TokenStream ts(args);
            EXPECT_EQ(ts.count(), static_cast<size_t>(6));
        } else {
            SUCCEED() << "Args exists but does not expose a way to supply tokens without assumptions.";
        }
    } else {
        GTEST_SKIP() << "Args-based constructor is not available in this build.";
    }
}
