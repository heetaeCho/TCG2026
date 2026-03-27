// File: tests/MatchAnyOfGeneric_test.cpp
#include <gtest/gtest.h>
#include <string>
#include <utility>

// Header under test (path from the prompt)
#include "Catch2/src/catch2/matchers/catch_matchers_templated.hpp"

using Catch::Matchers::Detail::MatchAnyOfGeneric;

// --- Minimal standalone matcher types used only as collaborators in tests ---

// Matches anything (always true).
struct AlwaysTrueMatcher {
  template <typename T>
  bool match(const T&) const { return true; }
  std::string describe() const { return "always true"; }
};

// Matches nothing (always false).
struct AlwaysFalseMatcher {
  template <typename T>
  bool match(const T&) const { return false; }
  std::string describe() const { return "always false"; }
};

// Equality matcher for a specific value (type T must be equality-comparable).
template <typename T>
struct EqualsMatcher {
  explicit EqualsMatcher(const T& expected) : expected_(expected) {}
  bool match(const T& value) const { return value == expected_; }
  std::string describe() const { return "equals(expected)"; }
private:
  T expected_;
};

// --- Tests ---

// Normal operation: returns true when any of the provided matchers would match.
TEST(MatchAnyOfGeneric_161, ReturnsTrueWhenAnyMatcherMatches_161) {
  AlwaysFalseMatcher m1;
  AlwaysTrueMatcher  m2;

  MatchAnyOfGeneric<AlwaysFalseMatcher, AlwaysTrueMatcher> anyOf(m1, m2);

  int arg = 42;
  EXPECT_TRUE(anyOf.match(arg));
}

// Normal operation: returns false when none of the provided matchers match.
TEST(MatchAnyOfGeneric_161, ReturnsFalseWhenNoMatchersMatch_161) {
  AlwaysFalseMatcher m1, m2;

  MatchAnyOfGeneric<AlwaysFalseMatcher, AlwaysFalseMatcher> anyOf(m1, m2);

  int arg = 0;
  EXPECT_FALSE(anyOf.match(arg));
}

// Boundary: with a single matcher, behavior should mirror that matcher.
TEST(MatchAnyOfGeneric_161, SingleMatcherBehavesLikeThatMatcher_161) {
  EqualsMatcher<int> equal42(42);

  MatchAnyOfGeneric<EqualsMatcher<int>> anyOf(equal42);

  EXPECT_TRUE(anyOf.match(42));
  EXPECT_FALSE(anyOf.match(0));
}

// Type coverage: works with non-int types (e.g., std::string).
TEST(MatchAnyOfGeneric_161, WorksWithStringArguments_161) {
  EqualsMatcher<std::string> eq_hello(std::string("hello"));
  AlwaysFalseMatcher never;

  MatchAnyOfGeneric<EqualsMatcher<std::string>, AlwaysFalseMatcher> anyOf(eq_hello, never);

  EXPECT_TRUE(anyOf.match(std::string("hello")));
  EXPECT_FALSE(anyOf.match(std::string("world")));
}

// Argument category: can accept rvalues and lvalues via template Arg&&.
TEST(MatchAnyOfGeneric_161, AcceptsLvaluesAndRvalues_161) {
  EqualsMatcher<int> eq1(1);
  AlwaysFalseMatcher never;

  MatchAnyOfGeneric<EqualsMatcher<int>, AlwaysFalseMatcher> anyOf(eq1, never);

  int one = 1;                // lvalue
  EXPECT_TRUE(anyOf.match(one));
  EXPECT_TRUE(anyOf.match(1)); // rvalue
  EXPECT_FALSE(anyOf.match(2));
}

// Describe: returns a string (we only assert non-emptiness to avoid assuming format).
TEST(MatchAnyOfGeneric_161, DescribeReturnsNonEmptyString_161) {
  AlwaysTrueMatcher  m1;
  AlwaysFalseMatcher m2;

  MatchAnyOfGeneric<AlwaysTrueMatcher, AlwaysFalseMatcher> anyOf(m1, m2);

  std::string d = anyOf.describe();
  // We do not assert exact formatting; only that it is a string with some content.
  EXPECT_FALSE(d.empty());
}
