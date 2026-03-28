// File: tests/contains_matcher_955_tests.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>
#include <memory>
#include <functional>

// Include exactly the public interface we were given.
#include "Catch2/extras/catch_amalgamated.hpp"

// A simple move-only equality functor (not copyable, only movable)
struct MoveOnlyEq {
    MoveOnlyEq() = default;
    MoveOnlyEq(const MoveOnlyEq&) = delete;
    MoveOnlyEq& operator=(const MoveOnlyEq&) = delete;
    MoveOnlyEq(MoveOnlyEq&&) = default;
    MoveOnlyEq& operator=(MoveOnlyEq&&) = default;

    template <typename A, typename B>
    bool operator()(const A&, const B&) const {
        // We do not assert behavior of matching — not part of the exposed interface here.
        return true;
    }
};

// A move-only wrapper for element values to ensure forwarding supports move-only T
struct MoveOnlyInt {
    int v{};
    MoveOnlyInt(int x) : v(x) {}
    MoveOnlyInt(const MoveOnlyInt&) = delete;
    MoveOnlyInt& operator=(const MoveOnlyInt&) = delete;
    MoveOnlyInt(MoveOnlyInt&&) = default;
    MoveOnlyInt& operator=(MoveOnlyInt&&) = default;
};

// Fixture (kept minimal; not relying on any internal state)
class ContainsMatcherTest_955 : public ::testing::Test {};

// --- Tests ---

TEST_F(ContainsMatcherTest_955, ConstructsWithLvalueAndStdEqualTo_955) {
    int needle = 3;

    auto matcher = Catch::Matchers::Contains(needle, std::equal_to<int>{});
    // We cannot assert its internal behavior; only that the type is usable and movable.
    (void)matcher;

    // Basic type traits: move-constructible is a reasonable expectation for matcher objects.
    using MatcherT = decltype(matcher);
    EXPECT_TRUE(std::is_move_constructible<MatcherT>::value);
}

TEST_F(ContainsMatcherTest_955, ConstructsWithRvalueAndLambdaEquality_955) {
    auto matcher = Catch::Matchers::Contains(std::string{"abc"}, 
        [](const std::string&, const std::string&) { return true; });
    (void)matcher;

    using MatcherT = decltype(matcher);
    EXPECT_TRUE(std::is_move_constructible<MatcherT>::value);
}

TEST_F(ContainsMatcherTest_955, AcceptsMoveOnlyEquality_955) {
    MoveOnlyEq eq;
    auto matcher = Catch::Matchers::Contains(42, std::move(eq));
    (void)matcher;

    using MatcherT = decltype(matcher);
    EXPECT_TRUE(std::is_move_constructible<MatcherT>::value);
}

TEST_F(ContainsMatcherTest_955, AcceptsMoveOnlyElement_955) {
    // Ensure the factory can take a move-only element type.
    auto matcher = Catch::Matchers::Contains(MoveOnlyInt{7}, std::equal_to<int>{});
    (void)matcher;

    using MatcherT = decltype(matcher);
    EXPECT_TRUE(std::is_move_constructible<MatcherT>::value);
}

TEST_F(ContainsMatcherTest_955, AcceptsMoveOnlyElementAndMoveOnlyEquality_955) {
    // Both element and equality are move-only — this stresses perfect-forwarding.
    auto matcher = Catch::Matchers::Contains(MoveOnlyInt{9}, MoveOnlyEq{});
    (void)matcher;

    using MatcherT = decltype(matcher);
    EXPECT_TRUE(std::is_move_constructible<MatcherT>::value);
}

TEST_F(ContainsMatcherTest_955, WorksWithCustomComparableTypeAndStdEqualTo_955) {
    struct S {
        int x{};
    };
    // Provide equality that compares S to S through their x fields.
    struct Eq {
        bool operator()(const S& a, const S& b) const { return a.x == b.x; }
    };

    S s{123};
    auto matcher = Catch::Matchers::Contains(s, Eq{});
    (void)matcher;

    using MatcherT = decltype(matcher);
    EXPECT_TRUE(std::is_move_constructible<MatcherT>::value);
}
