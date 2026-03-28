// File: match_any_of_empty_index_sequence_tests_153.cpp

#include <gtest/gtest.h>
#include <array>
#include <string>
#include <utility>

// Include the provided interface
#include "Catch2/src/catch2/matchers/catch_matchers_templated.hpp"

using Catch::Matchers::Detail::match_any_of;

class MatchAnyOfEmptyIndexSeqTest_153 : public ::testing::Test {};

// Normal operation: N = 0 (no matchers) with a simple int argument.
// Expectation: returns false for empty index sequence.
TEST(MatchAnyOfEmptyIndexSeqTest_153, ReturnsFalse_WithZeroMatchers_IntArg_153) {
    std::array<void const*, 0> ptrs{};
    int value = 42;
    EXPECT_FALSE(match_any_of(value, ptrs, std::index_sequence<>{}));
}

// Normal operation: N > 0 array provided, but still an empty index sequence.
// Observable behavior should still be false regardless of array contents.
TEST(MatchAnyOfEmptyIndexSeqTest_153, ReturnsFalse_WithNonZeroArrayButEmptyIndexSeq_StringArg_153) {
    int a = 0, b = 0;
    std::array<void const*, 3> ptrs{
        { static_cast<void const*>(&a), nullptr, static_cast<void const*>(&b) }
    };
    std::string s = "hello";
    EXPECT_FALSE(match_any_of(s, ptrs, std::index_sequence<>{}));
}

// Boundary-style check: accepts const pointer argument and null entries.
// Still using an empty index sequence => expect false.
TEST(MatchAnyOfEmptyIndexSeqTest_153, ReturnsFalse_WithConstPointerArg_AndNullEntries_153) {
    const char* p = "x";
    const void* vp = static_cast<const void*>(p);
    std::array<void const*, 2> ptrs{{ nullptr, vp }};
    EXPECT_FALSE(match_any_of(p, ptrs, std::index_sequence<>{}));
}

// Interface/forwarding robustness: move-only type as Arg (rvalue).
// Confirms the function accepts forwarding references; observable result is false.
struct MoveOnly153 {
    MoveOnly153() = default;
    MoveOnly153(const MoveOnly153&) = delete;
    MoveOnly153(MoveOnly153&&) = default;
    MoveOnly153& operator=(const MoveOnly153&) = delete;
    MoveOnly153& operator=(MoveOnly153&&) = default;
    ~MoveOnly153() = default;
};

TEST(MatchAnyOfEmptyIndexSeqTest_153, AcceptsMoveOnlyRvalue_ReturnsFalse_153) {
    MoveOnly153 mo;
    std::array<void const*, 1> ptrs{{ nullptr }};
    EXPECT_FALSE(match_any_of(std::move(mo), ptrs, std::index_sequence<>{}));
}
