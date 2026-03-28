// File: bytemapbuilder_merge_test_409.cc

#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <utility>

// We include the declaration/definition unit that exposes ByteMapBuilder's interface
// available to the test build in this kata setup.
#include "re2/prog.cc"  // Provides namespace re2 { class ByteMapBuilder { ... } }

namespace {

using re2::ByteMapBuilder;

struct BuildOutput {
  std::array<uint8_t, 256> bytemap{};   // zero-initialized
  std::array<int, 512>     rangebuf{};  // intentionally oversized & zero-initialized
};

// Helper: run Merge+Build and capture outputs.
static BuildOutput CaptureBuild(ByteMapBuilder& b) {
  BuildOutput out;
  b.Merge();
  b.Build(out.bytemap.data(), out.rangebuf.data());
  return out;
}

// Helper: equality on observable Build outputs.
static ::testing::AssertionResult EqualOutputs(const BuildOutput& a,
                                               const BuildOutput& b) {
  if (a.bytemap != b.bytemap) {
    return ::testing::AssertionFailure() << "bytemap differs";
  }
  if (a.rangebuf != b.rangebuf) {
    return ::testing::AssertionFailure() << "rangebuf differs";
  }
  return ::testing::AssertionSuccess();
}

// ---------- Tests ----------

// Default construction -> deterministic result.
// Ensures the “no marks” state builds consistently.
TEST(ByteMapBuilderTest_409, DefaultBuildDeterministic_409) {
  ByteMapBuilder b1;
  ByteMapBuilder b2;

  const auto out1 = CaptureBuild(b1);
  const auto out2 = CaptureBuild(b2);

  EXPECT_TRUE(EqualOutputs(out1, out2));
}

// Calling Merge multiple times without new marks should be idempotent.
TEST(ByteMapBuilderTest_409, MergeIsIdempotent_409) {
  ByteMapBuilder b;
  // Optional: some marks to make the state non-trivial.
  b.Mark(10, 20);
  b.Mark(100, 120);

  // First merge+build.
  const auto out1 = CaptureBuild(b);

  // Repeat merge+build without adding more marks.
  const auto out2 = CaptureBuild(b);

  EXPECT_TRUE(EqualOutputs(out1, out2));
}

// Order-independence: marking the same disjoint ranges in different orders
// should yield identical observable Build results.
TEST(ByteMapBuilderTest_409, OrderIndependenceForDisjointRanges_409) {
  // First builder: ascending order.
  ByteMapBuilder a;
  a.Mark(0, 0);
  a.Mark(50, 60);
  a.Mark(200, 220);

  // Second builder: different order.
  ByteMapBuilder b;
  b.Mark(200, 220);
  b.Mark(0, 0);
  b.Mark(50, 60);

  const auto outA = CaptureBuild(a);
  const auto outB = CaptureBuild(b);

  EXPECT_TRUE(EqualOutputs(outA, outB));
}

// Boundary handling at edges of the domain: [0,0] and [255,255].
// Verifies no crash and order-independence at extremes.
TEST(ByteMapBuilderTest_409, BoundarySingletonsAtEdges_409) {
  ByteMapBuilder a;
  a.Mark(0, 0);
  a.Mark(255, 255);

  ByteMapBuilder b;
  b.Mark(255, 255);
  b.Mark(0, 0);

  const auto outA = CaptureBuild(a);
  const auto outB = CaptureBuild(b);

  EXPECT_TRUE(EqualOutputs(outA, outB));
}

// Overlapping marks that represent the same overall set should be equivalent.
// Example: [10,30] plus [20,40] vs a single [10,40].
TEST(ByteMapBuilderTest_409, OverlappingMarksEquivalentToUnion_409) {
  ByteMapBuilder with_overlap;
  with_overlap.Mark(10, 30);
  with_overlap.Mark(20, 40);

  ByteMapBuilder as_union;
  as_union.Mark(10, 40);

  const auto outOverlap = CaptureBuild(with_overlap);
  const auto outUnion   = CaptureBuild(as_union);

  EXPECT_TRUE(EqualOutputs(outOverlap, outUnion));
}

// Covering full range via a single mark vs multiple segments that partition the range
// should produce identical observable Build results (same overall coverage).
TEST(ByteMapBuilderTest_409, FullRangeSingleVsPartitioned_409) {
  ByteMapBuilder single;
  single.Mark(0, 255);

  ByteMapBuilder partitioned;
  partitioned.Mark(0, 127);
  partitioned.Mark(128, 255);

  const auto outSingle = CaptureBuild(single);
  const auto outParts  = CaptureBuild(partitioned);

  EXPECT_TRUE(EqualOutputs(outSingle, outParts));
}

// Adding duplicate marks should not change the final observable result.
// (Same range repeated.)
TEST(ByteMapBuilderTest_409, DuplicateMarksNoEffect_409) {
  ByteMapBuilder a;
  a.Mark(50, 80);
  a.Mark(50, 80);  // duplicate

  ByteMapBuilder b;
  b.Mark(50, 80);

  const auto outA = CaptureBuild(a);
  const auto outB = CaptureBuild(b);

  EXPECT_TRUE(EqualOutputs(outA, outB));
}

// Stress around adjacent splits: two adjacent ranges [30,40] and [41,50]
// vs their combined [30,50] should be equivalent.
TEST(ByteMapBuilderTest_409, AdjacentRangesEquivalentToCombined_409) {
  ByteMapBuilder adjacent;
  adjacent.Mark(30, 40);
  adjacent.Mark(41, 50);

  ByteMapBuilder combined;
  combined.Mark(30, 50);

  const auto outAdj = CaptureBuild(adjacent);
  const auto outComb = CaptureBuild(combined);

  EXPECT_TRUE(EqualOutputs(outAdj, outComb));
}

}  // namespace
