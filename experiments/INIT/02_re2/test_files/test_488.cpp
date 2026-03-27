// File: add_folded_range_test_488.cc

#include <gtest/gtest.h>

// Pull in the translation unit so the internal-linkage function is visible here.
#include "re2/parse.cc"

using namespace re2;

namespace {

// Helper: assert that every rune in [lo, hi] is contained by cc.
// We only use public interface (Contains), no assumptions about internal layout.
static void ExpectRangeContained(CharClassBuilder* cc, Rune lo, Rune hi) {
  for (Rune r = lo; r <= hi; ++r) {
    EXPECT_TRUE(cc->Contains(r)) << "Expected rune " << r << " to be contained";
  }
}

}  // namespace

// ------------------------- Tests -------------------------

// Normal path: adding a fresh range should at minimum contain that base range afterward.
TEST(AddFoldedRangeTest_488, AddsBaseRangeWhenEmpty_488) {
  CharClassBuilder cc;
  // Choose a small ASCII subrange to keep expectations cheap & deterministic.
  const Rune kLo = static_cast<Rune>('A');
  const Rune kHi = static_cast<Rune>('F');

  // Precondition sanity: a fresh builder should not yet contain the bounds.
  EXPECT_FALSE(cc.Contains(kLo));
  EXPECT_FALSE(cc.Contains(kHi));

  // Act
  AddFoldedRange(&cc, kLo, kHi, /*depth=*/0);

  // Assert: the base range is included (folded supersets, if any, are fine).
  ExpectRangeContained(&cc, kLo, kHi);
}

// If the range already exists, AddFoldedRange returns immediately after AddRange()
// reports "already there" and should not disturb previously-added content.
TEST(AddFoldedRangeTest_488, NoChangeWhenRangeAlreadyPresent_488) {
  CharClassBuilder cc;
  const Rune kLo = static_cast<Rune>('a');
  const Rune kHi = static_cast<Rune>('f');

  // Seed with the same range.
  ASSERT_TRUE(cc.AddRange(kLo, kHi));

  // Snapshot an observable property before calling (range membership on edges).
  const bool had_lo = cc.Contains(kLo);
  const bool had_hi = cc.Contains(kHi);

  // Act: calling with the same range should be a no-op beyond confirming presence.
  AddFoldedRange(&cc, kLo, kHi, /*depth=*/0);

  // Assert: edges still present; we don't assume exact size, only containment remains.
  EXPECT_EQ(had_lo, cc.Contains(kLo));
  EXPECT_EQ(had_hi, cc.Contains(kHi));
  ExpectRangeContained(&cc, kLo, kHi);
}

// Depth guard: when depth > 10, the function must early-return without touching cc.
// We rely only on observable state via Contains.
TEST(AddFoldedRangeTest_488, DepthGuardPreventsAnyModification_488) {
  CharClassBuilder cc;
  const Rune kLo = 0x41;  // 'A'
  const Rune kHi = 0x44;  // 'D'

  // Precondition: verify empty around the target interval.
  EXPECT_FALSE(cc.Contains(kLo));
  EXPECT_FALSE(cc.Contains(kHi));

  // Act: trigger the recursion guard.
  AddFoldedRange(&cc, kLo, kHi, /*depth=*/11);

  // Assert: still untouched.
  EXPECT_FALSE(cc.Contains(kLo));
  EXPECT_FALSE(cc.Contains(kHi));
}

// Overlapping calls should still ensure the union is contained (we don't assert internal layout).
TEST(AddFoldedRangeTest_488, OverlappingRangesYieldUnionContained_488) {
  CharClassBuilder cc;

  const Rune lo1 = static_cast<Rune>('B');  // [B..G]
  const Rune hi1 = static_cast<Rune>('G');
  const Rune lo2 = static_cast<Rune>('E');  // [E..K]
  const Rune hi2 = static_cast<Rune>('K');

  AddFoldedRange(&cc, lo1, hi1, /*depth=*/0);
  AddFoldedRange(&cc, lo2, hi2, /*depth=*/0);

  // Expect the union [B..K] to be present at minimum.
  ExpectRangeContained(&cc, std::min(lo1, lo2), std::max(hi1, hi2));
}

// Large interval smoke test: ensure it handles broad ranges without observable errors.
TEST(AddFoldedRangeTest_488, HandlesLargeAsciiInterval_488) {
  CharClassBuilder cc;

  const Rune kLo = 0x20;   // space
  const Rune kHi = 0x7E;   // '~'

  AddFoldedRange(&cc, kLo, kHi, /*depth=*/0);

  // At minimum, the ends of the interval must be contained.
  EXPECT_TRUE(cc.Contains(kLo));
  EXPECT_TRUE(cc.Contains(kHi));
}

