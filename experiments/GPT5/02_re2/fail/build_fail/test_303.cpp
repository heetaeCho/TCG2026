// File: compile_beginrange_test.cc
#include <gtest/gtest.h>
#include "re2/compile.h"  // Adjust include path if needed
#include <cstdint>

using re2::Compiler;
using re2::Frag;
using re2::kNullPatchList;

class CompilerBeginRangeTest_303 : public ::testing::Test {
protected:
  Compiler c_;
};

// [Behavior] BeginRange() clears any cached rune byte suffixes.
// [Observable path] Populate cache via CachedRuneByteSuffix(); verify with
// IsCachedRuneByteSuffix(); then call BeginRange() and confirm it's cleared.
TEST_F(CompilerBeginRangeTest_303, ClearsRuneByteSuffixCache_303) {
  // Arrange: Create a cached entry.
  const uint8_t lo = 0x61;   // 'a'
  const uint8_t hi = 0x7A;   // 'z'
  const bool foldcase = false;
  const int next = 0;

  const int id = c_.CachedRuneByteSuffix(lo, hi, foldcase, next);
  ASSERT_GE(id, 0);  // Should yield a non-negative identifier.
  ASSERT_TRUE(c_.IsCachedRuneByteSuffix(id)) << "Sanity check: cache populated";

  // Act: Begin a new range, which should clear the rune cache.
  c_.BeginRange();

  // Assert: Previously cached id is no longer recognized.
  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(id));
}

// [Behavior] BeginRange() initializes the current range to an empty state.
// [Observable path] Immediately following BeginRange(), EndRange() should
// produce a fragment whose "begin" and "end" reflect an empty range init.
TEST_F(CompilerBeginRangeTest_303, EndRangeAfterFreshBeginIsEmpty_303) {
  // Act: Fresh initialization and immediate completion.
  c_.BeginRange();
  Frag f = c_.EndRange();

  // Assert: The fragment reflects an empty-initialized range.
  // We only assert on fields exposed by Frag and the global kNullPatchList.
  EXPECT_EQ(f.begin, 0u);
  EXPECT_EQ(f.end.head, kNullPatchList.head);
  EXPECT_EQ(f.end.tail, kNullPatchList.tail);
  // Do NOT assert on nullable: not specified/observable for BeginRange alone.
}

// [Behavior] BeginRange() is idempotent with respect to cache clearing.
// [Observable path] Calling BeginRange() multiple times should consistently
// clear prior cache entries; verify with IsCachedRuneByteSuffix().
TEST_F(CompilerBeginRangeTest_303, MultipleBeginRangeKeepsCacheCleared_303) {
  // Arrange: Seed cache.
  const int id = c_.CachedRuneByteSuffix(0x80, 0xFF, /*foldcase=*/false, /*next=*/0);
  ASSERT_TRUE(c_.IsCachedRuneByteSuffix(id));

  // Act: Call BeginRange() twice.
  c_.BeginRange();
  c_.BeginRange();

  // Assert: Cache remains cleared for the old id.
  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(id));
}
