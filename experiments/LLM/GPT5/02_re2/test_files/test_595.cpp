// File: re2_constructor_charptr_test_595.cc

#include <gtest/gtest.h>
#include "re2/re2.h"
#include <type_traits>
#include <string>

using re2::RE2;

// ------------------------------
// Constructor behavior (char*)
// ------------------------------

TEST(RE2Constructor_595, ConstructsFromCString_595) {
  // Normal operation: constructing from a simple C string should succeed.
  // We assert no-throw and check observable state via public API.
  EXPECT_NO_THROW({
    RE2 re("abc");
    // If pattern() is exposed publicly, verify it mirrors the input.
    EXPECT_EQ(re.pattern(), std::string("abc"));
    // If ok() is available, verify the instance is usable.
    EXPECT_TRUE(re.ok());
  });
}

TEST(RE2Constructor_595, EmptyPattern_595) {
  // Boundary condition: empty pattern should be accepted and observable via pattern().
  RE2 re("");
  EXPECT_EQ(re.pattern(), std::string(""));
  EXPECT_TRUE(re.ok());
}

TEST(RE2Constructor_595, LongPattern_595) {
  // Boundary-ish: long pattern should be accepted without crashing.
  std::string long_pat(10000, 'a');
  RE2 re(long_pat.c_str());
  EXPECT_EQ(re.pattern(), long_pat);
  EXPECT_TRUE(re.ok());
}

TEST(RE2Constructor_595, EmbeddedNulInLiteralTruncatesAtFirstNul_595) {
  // Observable behavior when constructed from const char* with an embedded NUL.
  // Since the constructor takes const char*, only the prefix up to the first NUL
  // is normally observable via public pattern().
  const char pat_with_nul[] = {'a','\0','b','c'}; // not a typical C-string past the NUL
  RE2 re(pat_with_nul); // passes a const char*; typical behavior stops at first '\0'
  EXPECT_EQ(re.pattern(), std::string("a"));
  EXPECT_TRUE(re.ok());
}

// ------------------------------
// Deleted copy/move semantics
// ------------------------------

TEST(RE2Constructor_595, CopyAndMoveAreDeleted_595) {
  // Compile-time checks for deleted copy/move semantics (as declared public=delete).
  static_assert(!std::is_copy_constructible<RE2>::value,
                "RE2 must not be copy-constructible");
  static_assert(!std::is_move_constructible<RE2>::value,
                "RE2 must not be move-constructible");
  static_assert(!std::is_copy_assignable<RE2>::value,
                "RE2 must not be copy-assignable");
  static_assert(!std::is_move_assignable<RE2>::value,
                "RE2 must not be move-assignable");
}
