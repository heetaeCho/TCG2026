// File: tests/match_any_of_describe_140_test.cpp
#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "catch2/matchers/catch_matchers.hpp"

namespace {

using Catch::Matchers::Detail::MatchAnyOf;

// We instantiate with an arbitrary type parameter; describe() itself is type-agnostic.
using IntAnyOf = MatchAnyOf<int>;

// -----------------------------
// Interface / trait-level tests
// -----------------------------

// Copy operations are deleted in the interface; move operations are allowed.
static_assert(!std::is_copy_constructible<IntAnyOf>::value,
              "MatchAnyOf should NOT be copy-constructible per interface");
static_assert(!std::is_copy_assignable<IntAnyOf>::value,
              "MatchAnyOf should NOT be copy-assignable per interface");
static_assert(std::is_move_constructible<IntAnyOf>::value,
              "MatchAnyOf should be move-constructible per interface");
static_assert(std::is_move_assignable<IntAnyOf>::value,
              "MatchAnyOf should be move-assignable per interface");

// -----------------------------
// Behavior tests for describe()
// -----------------------------

// [Normal/Boundary] Default-constructed object (no sub-matchers).
TEST(MatchAnyOfDescribeTest_140, Describe_DefaultConstructedShowsEmptyGroup_140) {
    IntAnyOf sut;  // default-constructed
    // Observable behavior: The returned string format for empty composition.
    const std::string desc = sut.describe();
    EXPECT_EQ(desc, "( )");
}

// [Stability] Calling describe() repeatedly should be consistent/idempotent.
TEST(MatchAnyOfDescribeTest_140, Describe_RepeatedCallsAreConsistent_140) {
    IntAnyOf sut;
    const std::string first = sut.describe();
    const std::string second = sut.describe();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "( )");
}

// [Move semantics] After move-constructing, observable describe() output remains valid.
TEST(MatchAnyOfDescribeTest_140, Describe_MoveConstructedStillValid_140) {
    IntAnyOf original;
    IntAnyOf moved(std::move(original));
    EXPECT_EQ(moved.describe(), "( )");
}

// [Move assignment] After move-assigning, observable describe() output remains valid.
TEST(MatchAnyOfDescribeTest_140, Describe_MoveAssignedStillValid_140) {
    IntAnyOf a;
    IntAnyOf b;
    b = std::move(a);
    EXPECT_EQ(b.describe(), "( )");
}

} // namespace
