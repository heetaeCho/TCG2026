// File: re2_fullmatchn_test_252.cc
#include <string>
#include "gtest/gtest.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

using re2::RE2;

namespace {

// Basic exact full-match succeeds.
TEST(RE2_FullMatchN_252, ExactMatchReturnsTrue_252) {
  RE2 re("abc");
  // No captures: pass nullptr/0 for args.
  EXPECT_TRUE(RE2::FullMatchN("abc", re, /*args=*/nullptr, /*n=*/0));
}

// Partial-only match must fail because FullMatchN anchors both ends.
TEST(RE2_FullMatchN_252, PartialMatchReturnsFalse_252) {
  RE2 re("bc");               // would match substring in "abc"
  EXPECT_FALSE(RE2::FullMatchN("abc", re, nullptr, 0));
}

// Empty pattern matches only empty string for a full match.
TEST(RE2_FullMatchN_252, EmptyPatternBehavior_252) {
  RE2 re("");                 // empty pattern
  EXPECT_TRUE(RE2::FullMatchN("", re, nullptr, 0));
  EXPECT_FALSE(RE2::FullMatchN("a", re, nullptr, 0));
}

// FullMatchN should parse and populate capture arguments on success.
TEST(RE2_FullMatchN_252, CapturesAreParsedIntoArgsOnSuccess_252) {
  RE2 re("(\\d+)-(\\w+)");
  int number = 0;
  std::string word;

  RE2::Arg a0(&number);
  RE2::Arg a1(&word);
  const RE2::Arg* args[] = { &a0, &a1 };

  ASSERT_TRUE(RE2::FullMatchN("123-abc", re, args, 2));
  EXPECT_EQ(number, 123);
  EXPECT_EQ(word, "abc");
}

// When match fails, provided destination variables should remain unchanged.
TEST(RE2_FullMatchN_252, FailedMatchDoesNotModifyOutputs_252) {
  RE2 re("(\\d+)-(\\w+)");
  int number = 42;            // sentinel
  std::string word = "keep";

  RE2::Arg a0(&number);
  RE2::Arg a1(&word);
  const RE2::Arg* args[] = { &a0, &a1 };

  EXPECT_FALSE(RE2::FullMatchN("nope", re, args, 2));
  EXPECT_EQ(number, 42);
  EXPECT_EQ(word, "keep");
}

// Pattern with no captures should still succeed with args=null and n=0.
TEST(RE2_FullMatchN_252, NoCapturesWithNoArgs_252) {
  RE2 re("a+");
  EXPECT_TRUE(RE2::FullMatchN("aaaa", re, nullptr, 0));
  EXPECT_FALSE(RE2::FullMatchN("", re, nullptr, 0));
}

// A non-anchored-looking pattern is still treated as full-match by FullMatchN.
TEST(RE2_FullMatchN_252, NonAnchoredPatternStillRequiresFullString_252) {
  RE2 re("a");  // would match at position 0 in "aa" if partial, but must fail for full
  EXPECT_TRUE(RE2::FullMatchN("a", re, nullptr, 0));
  EXPECT_FALSE(RE2::FullMatchN("aa", re, nullptr, 0));
}

}  // namespace
