// File: prog_compute_bytemap_test_411.cc

#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <cstring>

#include "re2/prog.h"

using re2::Prog;

namespace {

// Helper: run ComputeByteMap and copy results out via the public API.
static void BuildAndGetMap(Prog& p, std::array<uint8_t,256>& out_map, int& out_range) {
  p.ComputeByteMap();
  const uint8_t* m = p.bytemap();
  ASSERT_NE(m, nullptr);
  std::memcpy(out_map.data(), m, 256);
  out_range = p.bytemap_range();
}

// Convenience getters for a few representative bytes.
static uint8_t M(const std::array<uint8_t,256>& m, int ch) { return m[static_cast<uint8_t>(ch)]; }

}  // namespace

// -----------------------------------------------------------------------------
// No instructions → all bytes should fall into the same equivalence class.
// (We don't assert an exact range value; we only assert uniformity, which is
// observable via the public bytemap().)
// -----------------------------------------------------------------------------
TEST(Prog_ComputeByteMap_411, NoInst_AllBytesSameClass_411) {
  Prog p;

  std::array<uint8_t,256> bm{};
  int range = -1;
  BuildAndGetMap(p, bm, range);

  uint8_t cls0 = bm[0];
  for (int i = 1; i < 256; ++i) {
    EXPECT_EQ(bm[i], cls0) << "Byte " << i << " mapped to a different class";
  }
  // Range must at least be 1 (there is at least one class).
  EXPECT_GE(range, 1);
}

// -----------------------------------------------------------------------------
// A single ByteRange for one character should split that character into a
// (potentially) distinct class from other bytes.
// -----------------------------------------------------------------------------
TEST(Prog_ComputeByteMap_411, SingleByteRange_SplitsCharFromOthers_411) {
  Prog p;

  // Place a single kInstByteRange for 'x'.
  auto* i0 = p.inst(0);
  ASSERT_NE(i0, nullptr);
  i0->InitByteRange('x', 'x', /*foldcase=*/0, /*out=*/1);

  std::array<uint8_t,256> bm{};
  int range = -1;
  BuildAndGetMap(p, bm, range);

  EXPECT_NE(M(bm, 'x'), M(bm, 'y'));
  EXPECT_NE(M(bm, 'x'), M(bm, 'A'));
  EXPECT_GE(range, 2);
}

// -----------------------------------------------------------------------------
// Foldcase range over [a-z] should also cover [A-Z]; lower and upper letters
// should land in the same class, while a non-letter should differ.
// -----------------------------------------------------------------------------
TEST(Prog_ComputeByteMap_411, FoldCase_LowerAndUpperLettersShareClass_411) {
  Prog p;

  auto* i0 = p.inst(0);
  ASSERT_NE(i0, nullptr);
  i0->InitByteRange('a', 'z', /*foldcase=*/1, /*out=*/7);

  std::array<uint8_t,256> bm{};
  int range = -1;
  BuildAndGetMap(p, bm, range);

  EXPECT_EQ(M(bm, 'a'), M(bm, 'A'));
  EXPECT_EQ(M(bm, 'm'), M(bm, 'M'));
  EXPECT_NE(M(bm, 'a'), M(bm, '.'));  // '.' is not a letter
  EXPECT_GE(range, 2);
}

// -----------------------------------------------------------------------------
// Consecutive ByteRanges with the same 'out' should be treated as one group
// before a merge, so representatives from those ranges can share a class.
// (We only assert observable equality, not internal merging behavior.)
// -----------------------------------------------------------------------------
TEST(Prog_ComputeByteMap_411, ConsecutiveRangesWithSameOut_MayShareClass_411) {
  Prog p;

  // Two separate ranges with the same out.
  auto* i0 = p.inst(0);
  auto* i1 = p.inst(1);
  ASSERT_NE(i0, nullptr);
  ASSERT_NE(i1, nullptr);
  i0->InitByteRange('0', '9', /*foldcase=*/0, /*out=*/42);
  i1->InitByteRange('a', 'f', /*foldcase=*/0, /*out=*/42);

  std::array<uint8_t,256> bm{};
  int range = -1;
  BuildAndGetMap(p, bm, range);

  // Digits and hex letters may collapse to the same class since they were part
  // of the same logical group. We only check equality between representatives,
  // and that some unrelated character differs.
  EXPECT_EQ(M(bm, '0'), M(bm, 'a'));
  EXPECT_NE(M(bm, '0'), M(bm, 'Z'));
  EXPECT_GE(range, 2);
}

// -----------------------------------------------------------------------------
// An EmptyWidth instruction containing begin/end-of-line flags should ensure
// '\n' is distinguished from other bytes (observably different class).
// -----------------------------------------------------------------------------
TEST(Prog_ComputeByteMap_411, EmptyWidth_BeginEndLine_MarksNewline_411) {
  Prog p;

  auto* i0 = p.inst(0);
  ASSERT_NE(i0, nullptr);
  i0->InitEmptyWidth(static_cast<re2::EmptyOp>(re2::kEmptyBeginLine | re2::kEmptyEndLine),
                     /*out=*/0);

  std::array<uint8_t,256> bm{};
  int range = -1;
  BuildAndGetMap(p, bm, range);

  EXPECT_NE(M(bm, '\n'), M(bm, 'A'));
  EXPECT_NE(M(bm, '\n'), M(bm, ' '));
  EXPECT_GE(range, 2);
}

// -----------------------------------------------------------------------------
// An EmptyWidth instruction involving word-boundary behavior should partition
// word characters vs. non-word characters (observably different classes).
// We only check representative bytes and do not assume exact range count.
// -----------------------------------------------------------------------------
TEST(Prog_ComputeByteMap_411, EmptyWidth_WordBoundary_WordVsNonWordDiffer_411) {
  Prog p;

  auto* i0 = p.inst(0);
  ASSERT_NE(i0, nullptr);
  i0->InitEmptyWidth(re2::kEmptyWordBoundary, /*out=*/0);

  std::array<uint8_t,256> bm{};
  int range = -1;
  BuildAndGetMap(p, bm, range);

  // Representatives: 'a' and '1' are typically word chars; ' ' is not.
  EXPECT_EQ(M(bm, 'a'), M(bm, '1'));
  EXPECT_NE(M(bm, 'a'), M(bm, ' '));
  EXPECT_GE(range, 2);
}

// -----------------------------------------------------------------------------
// Adding multiple EmptyWidth instructions that both imply word-boundary
// handling should not change the outcome beyond the first (idempotent effect
// through the public result). We compare byte maps of two separately built
// programs for equality.
// -----------------------------------------------------------------------------
TEST(Prog_ComputeByteMap_411, EmptyWidth_WordBoundary_MarkedOnce_ProducesSameMap_411) {
  Prog p1;
  auto* a0 = p1.inst(0);
  ASSERT_NE(a0, nullptr);
  a0->InitEmptyWidth(re2::kEmptyWordBoundary, /*out=*/0);

  Prog p2;
  auto* b0 = p2.inst(0);
  auto* b1 = p2.inst(1);
  ASSERT_NE(b0, nullptr);
  ASSERT_NE(b1, nullptr);
  b0->InitEmptyWidth(re2::kEmptyWordBoundary, /*out=*/0);
  b1->InitEmptyWidth(re2::kEmptyNonWordBoundary, /*out=*/0);  // also triggers the same path

  std::array<uint8_t,256> bm1{}, bm2{};
  int r1 = -1, r2 = -1;
  BuildAndGetMap(p1, bm1, r1);
  BuildAndGetMap(p2, bm2, r2);

  EXPECT_EQ(r1, r2);
  for (int i = 0; i < 256; ++i) {
    EXPECT_EQ(bm1[i], bm2[i]) << "Class differs at byte " << i;
  }
}
