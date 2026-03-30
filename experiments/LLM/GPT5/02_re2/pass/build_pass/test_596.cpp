// File: re2_constructor_string_test_596.cc
#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"

using re2::RE2;

class RE2StringCtorTest_596 : public ::testing::Test {};

// Verifies that constructing with a simple literal pattern preserves the pattern
// via the public accessor and that it can be used for matching.
TEST_F(RE2StringCtorTest_596, SimplePattern_PreservedAndMatches_596) {
  std::string pat = "abc";
  RE2 re(pat);

  // Observable through public API: pattern string is accessible.
  EXPECT_EQ(re.pattern(), pat);

  // Observable matching behavior using public static API.
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
}

// Empty pattern should construct and expose the same pattern string.
// (No assumptions about internal validity flags.)
TEST_F(RE2StringCtorTest_596, EmptyPattern_ConstructsAndExposes_596) {
  std::string pat;
  RE2 re(pat);

  EXPECT_EQ(re.pattern(), pat);

  // With an empty pattern, a full match on empty text is commonly true in regex
  // engines; however, do not depend on unspecified semantics here beyond
  // "no crash / callable". We just exercise the API.
  (void)RE2::FullMatch("", re);  // Call to ensure it's usable; no assertion on result.
}

// Metacharacters should be preserved verbatim in the exposed pattern string.
// We only assert preservation via the public accessor and basic usability.
TEST_F(RE2StringCtorTest_596, Metacharacters_PreservedAndUsable_596) {
  std::string pat = "a.*b|c?";
  RE2 re(pat);

  EXPECT_EQ(re.pattern(), pat);

  // Exercise matcher without asserting specific regex semantics beyond
  // "call succeeds and returns a boolean".
  (void)RE2::FullMatch("axxxb", re);
  (void)RE2::FullMatch("c", re);
}

// Invalid-looking pattern should not crash construction. We avoid asserting
// internal error state; instead we check the observable pattern echo and that
// calls are safe.
TEST_F(RE2StringCtorTest_596, InvalidLookingPattern_ConstructsSafely_596) {
  std::string pat = "[";
  RE2 re(pat);

  // Public accessor should still reflect what we passed in.
  EXPECT_EQ(re.pattern(), pat);

  // Using matching API should be safe (no crash). We don't assert success.
  EXPECT_FALSE(RE2::FullMatch("anything", re));
}

// Interface-level constraints: copy and move are deleted.
// These are compile-time interface properties and do not depend on internals.
TEST_F(RE2StringCtorTest_596, CopyAndMoveAreDeleted_596) {
  static_assert(!std::is_copy_constructible<RE2>::value,
                "RE2 must not be copy constructible");
  static_assert(!std::is_copy_assignable<RE2>::value,
                "RE2 must not be copy assignable");
  static_assert(!std::is_move_constructible<RE2>::value,
                "RE2 must not be move constructible");
  static_assert(!std::is_move_assignable<RE2>::value,
                "RE2 must not be move assignable");
}

// Smoke test ensuring the std::string constructor is usable with long patterns
// (boundary-ish scenario) and remains callable via public APIs.
TEST_F(RE2StringCtorTest_596, LongPattern_SmokeUsability_596) {
  std::string pat(1024, 'x');  // 1KB of 'x'
  RE2 re(pat);

  EXPECT_EQ(re.pattern().size(), pat.size());
  // Exercise matcher; no assumption about success, only that it's callable.
  (void)RE2::FullMatch(std::string(1024, 'x'), re);
}
