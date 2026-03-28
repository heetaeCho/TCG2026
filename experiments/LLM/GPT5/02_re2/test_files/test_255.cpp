// File: re2_find_and_consume_n_255_test.cc
#include "re2/re2.h"
#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

using re2::RE2;
using absl::string_view;

class RE2_FindAndConsumeN_255 : public ::testing::Test {};

// Normal operation: finds a match anywhere and consumes through the end of that match.
TEST_F(RE2_FindAndConsumeN_255, MatchesAnywhereConsumesThroughMatch_255) {
  RE2 re("(\\d+)");
  string_view input("abc123def");

  const RE2::Arg* args[] = {nullptr};
  bool ok = RE2::FindAndConsumeN(&input, re, args, /*n=*/0);

  EXPECT_TRUE(ok);
  // Should consume "abc123" leaving "def".
  EXPECT_EQ(input, "def");
}

// Boundary: match at the start should consume exactly the match length.
TEST_F(RE2_FindAndConsumeN_255, MatchAtStartConsumesOnlyMatch_255) {
  RE2 re("\\d+");
  string_view input("123def");

  const RE2::Arg* args[] = {nullptr};
  bool ok = RE2::FindAndConsumeN(&input, re, args, /*n=*/0);

  EXPECT_TRUE(ok);
  // Should consume "123" leaving "def".
  EXPECT_EQ(input, "def");
}

// No match: returns false and leaves input unchanged.
TEST_F(RE2_FindAndConsumeN_255, NoMatchLeavesInputUnchanged_255) {
  RE2 re("\\d+");
  string_view input("abcdef");  // no digits

  const RE2::Arg* args[] = {nullptr};
  bool ok = RE2::FindAndConsumeN(&input, re, args, /*n=*/0);

  EXPECT_FALSE(ok);
  EXPECT_EQ(input, "abcdef");
}

// Empty input: returns false and input stays empty.
TEST_F(RE2_FindAndConsumeN_255, EmptyInputUnchangedOnFailure_255) {
  RE2 re("foo");
  string_view input("");  // empty

  const RE2::Arg* args[] = {nullptr};
  bool ok = RE2::FindAndConsumeN(&input, re, args, /*n=*/0);

  EXPECT_FALSE(ok);
  EXPECT_TRUE(input.empty());
}

// Repeated consumption: subsequent calls continue from the updated input.
TEST_F(RE2_FindAndConsumeN_255, MultipleCallsConsumeProgressively_255) {
  RE2 re("\\d+");
  string_view input("a1b2c");

  const RE2::Arg* args[] = {nullptr};

  bool ok1 = RE2::FindAndConsumeN(&input, re, args, /*n=*/0);
  EXPECT_TRUE(ok1);
  // First call should consume "a1", leaving "b2c".
  EXPECT_EQ(input, "b2c");

  bool ok2 = RE2::FindAndConsumeN(&input, re, args, /*n=*/0);
  EXPECT_TRUE(ok2);
  // Second call should consume "b2", leaving "c".
  EXPECT_EQ(input, "c");

  // Third call should fail (no more digits) and leave input unchanged.
  string_view before = input;
  bool ok3 = RE2::FindAndConsumeN(&input, re, args, /*n=*/0);
  EXPECT_FALSE(ok3);
  EXPECT_EQ(input, before);
}

// Overlapping/adjacent matches: only the first match is consumed per call.
TEST_F(RE2_FindAndConsumeN_255, AdjacentMatchesConsumeFirstOnlyPerCall_255) {
  RE2 re("foo");
  string_view input("foofoo");

  const RE2::Arg* args[] = {nullptr};
  bool ok = RE2::FindAndConsumeN(&input, re, args, /*n=*/0);

  EXPECT_TRUE(ok);
  // Should consume the first "foo" only, leaving the second "foo".
  EXPECT_EQ(input, "foo");
}
