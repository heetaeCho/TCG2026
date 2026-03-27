// File: none_match_tests_186.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Header from the prompt (public interface under test)
#include <catch2/matchers/catch_matchers_quantifiers.hpp>

// We only test via the public interface in the header above.
using Catch::Matchers::NoneMatch;
using Catch::Matchers::NoneMatchMatcher;

// A lightweight matcher-shaped type we can pass through the API.
// It has visible copy/move counters so we can observe forwarding
// semantics *without* inspecting any internal state of NoneMatch.
struct CopyMoveProbe {
    static inline int copies = 0;
    static inline int moves  = 0;

    static void Reset() { copies = 0; moves = 0; }

    CopyMoveProbe() = default;
    CopyMoveProbe(const CopyMoveProbe&) { ++copies; }
    CopyMoveProbe(CopyMoveProbe&&) noexcept { ++moves; }

    // Minimal "matcher-like" surface (never used by tests to assert logic)
    // Kept empty to avoid relying on Catch2 internals.
};

// A move-only matcher-shaped type to ensure move-only arguments are supported.
struct MoveOnlyMatcher {
    MoveOnlyMatcher() = default;
    MoveOnlyMatcher(const MoveOnlyMatcher&) = delete;
    MoveOnlyMatcher& operator=(const MoveOnlyMatcher&) = delete;
    MoveOnlyMatcher(MoveOnlyMatcher&&) noexcept = default;
    MoveOnlyMatcher& operator=(MoveOnlyMatcher&&) noexcept = default;

    // Minimal "matcher-like" surface (unused).
};

// ---------- Tests ----------

TEST(NoneMatchTest_186, ReturnsExpectedTypeForLvalue_186) {
    CopyMoveProbe m;
    using Result = decltype(NoneMatch(m));
    // For a forwarding reference parameter, passing an lvalue deduces T&.
    static_assert(std::is_same_v<Result, NoneMatchMatcher<CopyMoveProbe&>>,
                  "NoneMatch should return NoneMatchMatcher<T&> for lvalues");
    SUCCEED();
}

TEST(NoneMatchTest_186, ReturnsExpectedTypeForConstLvalue_186) {
    const CopyMoveProbe m{};
    using Result = decltype(NoneMatch(m));
    // Lvalue const should deduce as const T&.
    static_assert(std::is_same_v<Result, NoneMatchMatcher<const CopyMoveProbe&>>,
                  "NoneMatch should return NoneMatchMatcher<const T&> for const lvalues");
    SUCCEED();
}

TEST(NoneMatchTest_186, ReturnsExpectedTypeForRvalue_186) {
    CopyMoveProbe m;
    using Result = decltype(NoneMatch(std::move(m)));
    // Rvalue should deduce as T (non-reference).
    static_assert(std::is_same_v<Result, NoneMatchMatcher<CopyMoveProbe>>,
                  "NoneMatch should return NoneMatchMatcher<T> for rvalues");
    SUCCEED();
}

TEST(NoneMatchTest_186, ForwardsMoveOnlyMatcher_186) {
    // Verifies that a move-only matcher can be forwarded and wrapped.
    MoveOnlyMatcher mm;
    auto wrapper = NoneMatch(std::move(mm));
    (void)wrapper; // Only verifying that construction compiles/works.
    SUCCEED();
}

TEST(NoneMatchTest_186, PerfectForwardingMovesRvalues_NoCopy_186) {
    CopyMoveProbe::Reset();

    auto wrapper = NoneMatch(CopyMoveProbe{}); // rvalue
    (void)wrapper;

    // Observable effect: constructing the wrapper from an rvalue should
    // require a move construction of the passed-in object, not a copy.
    EXPECT_EQ(CopyMoveProbe::copies, 0);
    EXPECT_GE(CopyMoveProbe::moves, 1); // at least one move to transfer ownership
}
