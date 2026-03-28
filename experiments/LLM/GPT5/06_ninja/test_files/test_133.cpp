// TEST_ID: 133

#include "util.h"

#include <gtest/gtest.h>
#include <string>
#include <stdint.h>

using std::string;

// Simple helper so tests read nicely.
static void CanonicalizeWrapper_133(string* path, uint64_t* slash_bits) {
  CanonicalizePath(path, slash_bits);
}

//------------------------------------------------------------------------------
// Basic behavior and non-Windows semantics
//------------------------------------------------------------------------------

TEST(CanonicalizePathStringTest_133, EmptyPath_RemainsEmpty_133) {
  string path;  // empty
  uint64_t slash_bits = 0xDEADBEEF;  // arbitrary non-zero to detect changes

  CanonicalizeWrapper_133(&path, &slash_bits);

  // For an empty path, the wrapper should not introduce any characters.
  EXPECT_TRUE(path.empty());
  // We deliberately do *not* assert anything about slash_bits here, since
  // the interface does not specify its value for an empty path.
}

TEST(CanonicalizePathStringTest_133, SimpleRelativePath_Unchanged_133) {
  string path = "foo/bar.h";
  uint64_t slash_bits = 123;  // will be overwritten if needed

  CanonicalizeWrapper_133(&path, &slash_bits);

  // A simple already-canonical relative path should not be modified.
  EXPECT_EQ("foo/bar.h", path);
#if !defined(_WIN32)
  // On non-Windows platforms, backslash tracking is unused and should remain 0.
  EXPECT_EQ(0u, slash_bits);
#endif
}

TEST(CanonicalizePathStringTest_133, DotAndDotDotComponents_AreNormalized_133) {
  string path = "./x/foo/../bar.h";
  uint64_t slash_bits = 0;

  CanonicalizeWrapper_133(&path, &slash_bits);

  // Known canonicalization behavior from util.h / existing tests:
  // "./x/foo/../bar.h" -> "x/bar.h".
  EXPECT_EQ("x/bar.h", path);
#if !defined(_WIN32)
  EXPECT_EQ(0u, slash_bits);
#endif
}

#if !defined(_WIN32)
TEST(CanonicalizePathStringTest_133, RootAndDoubleSlash_NonWindows_133) {
  // "/" should canonicalize to empty (as in existing CanonicalizePath tests).
  {
    string path = "/";
    uint64_t slash_bits = 0;

    CanonicalizeWrapper_133(&path, &slash_bits);

    EXPECT_EQ("", path);
    EXPECT_EQ(0u, slash_bits);
  }

  // "//foo" collapses to "/foo" on non-Windows platforms.
  {
    string path = "//foo";
    uint64_t slash_bits = 0;

    CanonicalizeWrapper_133(&path, &slash_bits);

    EXPECT_EQ("/foo", path);
    EXPECT_EQ(0u, slash_bits);
  }
}
#endif  // !defined(_WIN32)

//------------------------------------------------------------------------------
// Windows-specific slash_bits tracking behavior
//------------------------------------------------------------------------------

#if defined(_WIN32)

TEST(CanonicalizePathStringTest_133, BackslashesBecomeSlashes_AndBitsTracked_133) {
  string path = "a\\foo.h";
  uint64_t slash_bits = 0;

  CanonicalizeWrapper_133(&path, &slash_bits);

  // Backslash should be normalized to '/'.
  EXPECT_EQ("a/foo.h", path);
  // There is exactly one slash, and it came from a backslash.
  // By contract, bit 0 corresponds to the first slash in the canonical path.
  EXPECT_EQ(1u, slash_bits);
}

TEST(CanonicalizePathStringTest_133, MixedSlashes_SlashBitsForBackslashesOnly_133) {
  // Here only the *third* slash in the canonical path comes from a backslash.
  string path = "a/bcd/efh\\foo.h";
  uint64_t slash_bits = 0;

  CanonicalizeWrapper_133(&path, &slash_bits);

  EXPECT_EQ("a/bcd/efh/foo.h", path);
  // Slashes in canonical path:
  //   0: between "a" and "bcd"      (original '/')
  //   1: between "bcd" and "efh"    (original '/')
  //   2: between "efh" and "foo.h"  (original '\')
  // Only the third slash (#2) should set its bit: 1 << 2 == 4.
  EXPECT_EQ(4u, slash_bits);
}

TEST(CanonicalizePathStringTest_133, MultipleBackslashes_SetMultipleBits_133) {
  string path = "a\\bcd/efh\\foo.h";
  uint64_t slash_bits = 0;

  CanonicalizeWrapper_133(&path, &slash_bits);

  EXPECT_EQ("a/bcd/efh/foo.h", path);
  // Canonical slashes:
  //   #0: from '\'  -> bit 0
  //   #1: from '/'  -> no bit
  //   #2: from '\'  -> bit 2
  // So slash_bits == (1 << 0) | (1 << 2) == 1 + 4 == 5.
  EXPECT_EQ(5u, slash_bits);
}

TEST(CanonicalizePathStringTest_133, CanonicalPath_IdempotentAndClearsBits_133) {
  // After one canonicalization, all slashes are '/'.
  string path = "a\\bcd\\efh\\foo.h";
  uint64_t slash_bits = 0;

  CanonicalizeWrapper_133(&path, &slash_bits);
  EXPECT_EQ("a/bcd/efh/foo.h", path);
  EXPECT_EQ(7u, slash_bits);  // three slashes, all from backslashes

  // Canonicalizing again should not change the path and should report no
  // backslashes this time (all slashes are already '/').
  CanonicalizeWrapper_133(&path, &slash_bits);
  EXPECT_EQ("a/bcd/efh/foo.h", path);
  EXPECT_EQ(0u, slash_bits);
}

#endif  // defined(_WIN32)
