// File: compiler_is_cached_rune_byte_suffix_test_307.cc

#include <gtest/gtest.h>

// Pull in the declaration/definition of re2::Compiler and its collaborators
// (In this kata setup, the class is defined in compile.cc.)
#include "re2/compile.cc"

namespace re2 {

class CompilerIsCachedRuneByteSuffixTest_307 : public ::testing::Test {
protected:
  Compiler c_;  // default-constructed compiler per provided interface
};

// Normal operation: an instruction produced via the "uncached" path should not
// be considered cached before anything is inserted into the cache.
TEST_F(CompilerIsCachedRuneByteSuffixTest_307, UncachedInstructionIsNotCachedInitially_307) {
  const uint8_t lo = 10, hi = 20;
  const bool foldcase = false;
  const int next = 0;

  int id = c_.UncachedRuneByteSuffix(lo, hi, foldcase, next);
  ASSERT_GE(id, 0);  // observable: we obtained a valid instruction id

  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(id));
}

// Normal operation: once the same key is cached via CachedRuneByteSuffix,
// IsCachedRuneByteSuffix should return true for any instruction with that key.
TEST_F(CompilerIsCachedRuneByteSuffixTest_307, BecomesCachedAfterCachingSameKey_307) {
  const uint8_t lo = 65, hi = 90;
  const bool foldcase = false;
  const int next = 1;

  int id_uncached = c_.UncachedRuneByteSuffix(lo, hi, foldcase, next);
  ASSERT_GE(id_uncached, 0);
  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(id_uncached));

  int id_cached = c_.CachedRuneByteSuffix(lo, hi, foldcase, next);
  ASSERT_GE(id_cached, 0);

  // Now the key is in the cache; both instructions should report cached.
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id_uncached));
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id_cached));
}

// Boundary values for byte range (0..255) should be handled.
// After caching exactly that key, the corresponding instruction should be cached.
TEST_F(CompilerIsCachedRuneByteSuffixTest_307, BoundaryByteRangeIsRecognized_307) {
  const uint8_t lo = 0, hi = 255;
  const bool foldcase = true;   // also test foldcase=true with boundary range
  const int next = 2;

  int id_uncached = c_.UncachedRuneByteSuffix(lo, hi, foldcase, next);
  ASSERT_GE(id_uncached, 0);
  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(id_uncached));

  (void)c_.CachedRuneByteSuffix(lo, hi, foldcase, next);

  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id_uncached));
}

// Distinct keys should not collide.
// If we cache (lo,hi,foldcase,next) but query a different key via a different instruction,
// IsCachedRuneByteSuffix should return false.
TEST_F(CompilerIsCachedRuneByteSuffixTest_307, DifferentRangeNotConsideredCached_307) {
  const uint8_t lo_cached = 1, hi_cached = 5;
  const bool foldcase_cached = false;
  const int next_cached = 3;

  // Put one key in the cache
  (void)c_.CachedRuneByteSuffix(lo_cached, hi_cached, foldcase_cached, next_cached);

  // Create a different key via the uncached path (different 'hi')
  const uint8_t lo_other = lo_cached, hi_other = 6;
  const bool foldcase_other = foldcase_cached;
  const int next_other = next_cached;
  int id_other = c_.UncachedRuneByteSuffix(lo_other, hi_other, foldcase_other, next_other);
  ASSERT_GE(id_other, 0);

  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(id_other));
}

// The foldcase flag should be part of the cache identity.
// Caching with foldcase=false should not satisfy a query for foldcase=true (and vice versa).
TEST_F(CompilerIsCachedRuneByteSuffixTest_307, FoldcaseAffectsCachingIdentity_307) {
  const uint8_t lo = 97, hi = 122; // 'a'..'z'
  const int next = 4;

  // Cache with foldcase=false
  (void)c_.CachedRuneByteSuffix(lo, hi, /*foldcase=*/false, next);

  // Create an *uncached* instruction differing only by foldcase=true
  int id_foldcase_true = c_.UncachedRuneByteSuffix(lo, hi, /*foldcase=*/true, next);
  ASSERT_GE(id_foldcase_true, 0);

  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(id_foldcase_true));
}

// The 'next' (out) value should also influence the cache identity.
TEST_F(CompilerIsCachedRuneByteSuffixTest_307, NextOutAffectsCachingIdentity_307) {
  const uint8_t lo = 50, hi = 60;
  const bool foldcase = false;

  // Cache with next=7
  (void)c_.CachedRuneByteSuffix(lo, hi, foldcase, /*next=*/7);

  // Uncached instruction identical except for next=8
  int id_next8 = c_.UncachedRuneByteSuffix(lo, hi, foldcase, /*next=*/8);
  ASSERT_GE(id_next8, 0);

  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(id_next8));
}

}  // namespace re2
