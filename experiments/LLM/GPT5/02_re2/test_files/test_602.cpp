// File: ./TestProjects/re2/re2/tests/bytemapbuilder_test_602.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cstring>

// Declarations based strictly on the provided interfaces.
namespace re2 {

class Bitmap256 {
 public:
  Bitmap256();
  const int FindNextSetBit (int c);
  void Clear();
  bool Test(int c) const;
  void Set(int c);
 private:
  static int FindLSBSet(uint64_t n);
};

class ByteMapBuilder {
 public:
  ByteMapBuilder();
  void Mark (int lo, int hi);
  void Merge ();
  void Build (uint8_t * bytemap, int * bytemap_range);
};

} // namespace re2

namespace {

// Helper: count ranges in a 256-length bytemap by counting transitions.
// This checks an observable invariant without assuming particular color ids.
int CountRanges(const uint8_t bytemap[256]) {
  int ranges = 0;
  uint8_t prev = 0;
  for (int i = 0; i < 256; ++i) {
    if (i == 0 || bytemap[i] != prev) {
      ++ranges;
      prev = bytemap[i];
    }
  }
  return ranges;
}

struct ByteMapBuilderTest_602 : public ::testing::Test {
  re2::ByteMapBuilder builder;
};

} // namespace

// --- Normal operation ---

// Ensures Build after construction populates the whole buffer and returns
// a sensible, self-consistent range count.
TEST_F(ByteMapBuilderTest_602, ConstructorAndEmptyBuild_602) {
  uint8_t map[256];
  int range = -1;

  // Pre-fill with a sentinel to verify Build actually writes into the buffer.
  std::fill(std::begin(map), std::end(map), static_cast<uint8_t>(0xCC));

  // Calling Merge before Build should be safe and is part of typical usage.
  builder.Merge();
  builder.Build(map, &range);

  // The function should write something into the output array.
  // At minimum, not all bytes should remain the sentinel.
  bool all_sentinel = true;
  for (uint8_t b : map) {
    if (b != 0xCC) { all_sentinel = false; break; }
  }
  EXPECT_FALSE(all_sentinel);

  // The reported range count should be positive and not exceed 256.
  EXPECT_GE(range, 1);
  EXPECT_LE(range, 256);

  // Self-consistency: number of transitions equals bytemap_range.
  EXPECT_EQ(CountRanges(map), range);

  // Idempotence of Build with no intervening changes.
  uint8_t map2[256];
  int range2 = -1;
  builder.Build(map2, &range2);
  EXPECT_EQ(range, range2);
  EXPECT_TRUE(std::equal(std::begin(map), std::end(map), std::begin(map2)));
}

// Marking a mid-range and then building should produce an output different
// from the empty-build case at some observable positions (without assuming
// exactly how it changes).
TEST_F(ByteMapBuilderTest_602, MarkInsideBoundsAndBuild_602) {
  // Baseline (no marks).
  uint8_t base[256];
  int base_range = -1;
  builder.Merge();
  builder.Build(base, &base_range);

  // Now mark a middle slice and rebuild.
  re2::ByteMapBuilder b2;
  b2.Mark(100, 150);
  b2.Merge();
  uint8_t map[256];
  int range = -1;
  b2.Build(map, &range);

  // Still self-consistent.
  EXPECT_GE(range, 1);
  EXPECT_LE(range, 256);
  EXPECT_EQ(CountRanges(map), range);

  // Expect some observable difference vs. baseline (not specifying where).
  bool any_diff = false;
  for (int i = 0; i < 256; ++i) {
    if (map[i] != base[i]) { any_diff = true; break; }
  }
  EXPECT_TRUE(any_diff);
}

// Multiple marks (including overlaps) + repeated Merge/Build should be stable.
TEST_F(ByteMapBuilderTest_602, MultipleMarksIdempotentMerge_602) {
  builder.Mark(10, 30);
  builder.Mark(25, 40);  // overlap
  builder.Mark(200, 210);
  builder.Merge();

  uint8_t map1[256];
  int range1 = -1;
  builder.Build(map1, &range1);

  // Re-running Merge and Build without further Mark should not change results.
  builder.Merge();
  uint8_t map2[256];
  int range2 = -1;
  builder.Build(map2, &range2);

  EXPECT_EQ(range1, range2);
  EXPECT_TRUE(std::equal(std::begin(map1), std::end(map1), std::begin(map2)));
  EXPECT_EQ(CountRanges(map1), range1);
  EXPECT_EQ(CountRanges(map2), range2);
}

// --- Boundary conditions ---

// Mark at the very edges of the domain should be accepted and produce
// a valid build.
TEST_F(ByteMapBuilderTest_602, BoundaryMarks_0_And_255_602) {
  builder.Mark(0, 0);
  builder.Mark(255, 255);
  builder.Merge();

  uint8_t map[256];
  int range = -1;
  builder.Build(map, &range);

  EXPECT_GE(range, 1);
  EXPECT_LE(range, 256);
  EXPECT_EQ(CountRanges(map), range);
}

// --- Exceptional / error-like inputs (as observable through the interface) ---

// Supplying a "reversed" range (lo > hi). We don't assume behavior; we only
// require that Build succeeds and produces a self-consistent mapping.
TEST_F(ByteMapBuilderTest_602, ReversedRangeDoesNotBreakBuild_602) {
  // Capture a baseline to compare against (optional, for a stronger check).
  re2::ByteMapBuilder baseline;
  baseline.Merge();
  uint8_t base[256];
  int base_range = -1;
  baseline.Build(base, &base_range);

  // Now use reversed range.
  builder.Mark(50, 40);  // lo > hi
  builder.Merge();

  uint8_t map[256];
  int range = -1;
  builder.Build(map, &range);

  // Self-consistency checks.
  EXPECT_GE(range, 1);
  EXPECT_LE(range, 256);
  EXPECT_EQ(CountRanges(map), range);

  // At minimum, reversed input should not corrupt memory or crash.
  // It's acceptable if behavior equals baseline (treated as no-op), but we do
  // not require it — so we do not assert equality either way.
}

// Null pointers are not part of the declared contract, but we can still
// defensively verify that passing valid pointers is required by ensuring
// non-null outputs behave; we avoid calling with nullptr to not rely on UB.
// (This test simply confirms non-null usage path works repeatedly.)
TEST_F(ByteMapBuilderTest_602, RepeatedBuildWithValidPointers_602) {
  builder.Mark(1, 1);
  builder.Merge();

  uint8_t map1[256], map2[256];
  int range1 = -1, range2 = -1;

  builder.Build(map1, &range1);
  builder.Build(map2, &range2);

  EXPECT_GE(range1, 1);
  EXPECT_LE(range1, 256);
  EXPECT_GE(range2, 1);
  EXPECT_LE(range2, 256);
  EXPECT_EQ(CountRanges(map1), range1);
  EXPECT_EQ(CountRanges(map2), range2);
}

