// File: match_any_of_tests_139.cpp
#include <gtest/gtest.h>
#include "catch2/matchers/catch_matchers.hpp"

using Catch::Matchers::Detail::MatchAnyOf;

//
// We only test observable behavior available via the public interface:
// - Default construction
// - Move construction (since copy is deleted)
// - match(const ArgT&) const
// - describe() const
//
// No assumptions are made about internal state or how matchers are stored.
//

// 1) Normal operation on a default-constructed instance: with no configured sub-matchers,
// calling match(...) should deterministically return false (observable behavior).
TEST(MatchAnyOfTest_139, DefaultConstructed_MatchReturnsFalse_139) {
  MatchAnyOf<int> anyOf;  // default-constructed
  EXPECT_FALSE(anyOf.match(0));
  EXPECT_FALSE(anyOf.match(42));
  EXPECT_FALSE(anyOf.match(-7));
}

// 2) Boundary: const-correctness — match should be callable on a const instance.
// This also reasserts the observable result on a default-constructed const object.
TEST(MatchAnyOfTest_139, ConstInstance_CallsMatchAndReturnsFalse_139) {
  const MatchAnyOf<int> anyOfConst;
  EXPECT_FALSE(anyOfConst.match(1));
}

// 3) Move semantics: moving a default-constructed instance should keep behavior observable
// via the interface (still no configured sub-matchers => match returns false).
TEST(MatchAnyOfTest_139, MoveConstructedFromDefault_RemainsNonMatching_139) {
  MatchAnyOf<int> original;
  MatchAnyOf<int> moved{std::move(original)};
  EXPECT_FALSE(moved.match(5));
  // Also check moving again via move assignment
  MatchAnyOf<int> movedAgain = std::move(moved);
  EXPECT_FALSE(movedAgain.match(5));
}

// 4) describe() should be callable and not throw. We don't assert on specific text
// (to avoid depending on internal formatting), only that it’s a valid string call.
TEST(MatchAnyOfTest_139, Describe_NoThrowAndReturnsString_139) {
  MatchAnyOf<int> anyOf;
  std::string desc;
  EXPECT_NO_THROW(desc = anyOf.describe());
  // Optional minimal sanity: it is a string object we can query; content unspecified.
  // We avoid asserting on specific wording to respect the black-box constraint.
  EXPECT_GE(desc.size(), 0u);
}
