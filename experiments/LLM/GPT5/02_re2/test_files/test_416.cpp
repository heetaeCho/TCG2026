// File: ./TestProjects/re2/re2/tests/prog_compute_hints_test.cc
#include "gtest/gtest.h"
#include "re2/prog.h"

namespace re2 {

class ProgComputeHintsTest_416 : public ::testing::Test {
protected:
  Prog prog_;  // Used only to call the member function.
};

// Normal operation: a single ByteRange followed by a non-ByteRange “barrier”.
// Expect the hint on the ByteRange to equal the forward distance to the barrier.
TEST_F(ProgComputeHintsTest_416, ByteRangeFollowedByBarrier_SetsDistance1_416) {
  std::vector<Prog::Inst> flat(2);

  // id = 1 (end): non-byte-range (NOP) acts as a barrier
  flat[1].InitNop(/*out=*/0);

  // id = 0: a simple byte range
  flat[0].InitByteRange(/*lo=*/'a', /*hi=*/'z', /*foldcase=*/0, /*out=*/0);

  prog_.ComputeHints(&flat, /*begin=*/0, /*end=*/1);

  // Observable behavior: hint reflects distance to the next relevant inst.
  EXPECT_EQ(flat[0].hint(), 1);
}

// Non-byte-range inst itself should not gain a hint (observable as 0 via API).
TEST_F(ProgComputeHintsTest_416, NonByteRange_HintRemainsZero_416) {
  std::vector<Prog::Inst> flat(2);

  // id = 1: barrier
  flat[1].InitNop(0);

  // id = 0: also non-byte-range
  flat[0].InitNop(0);

  prog_.ComputeHints(&flat, /*begin=*/0, /*end=*/1);

  EXPECT_EQ(flat[0].hint(), 0);
}

// Disjoint later byte-ranges plus a barrier far ahead:
// The hint for id=7 should be the forward distance to the barrier (10 - 7 = 3).
TEST_F(ProgComputeHintsTest_416, DisjointRanges_UsesNextBarrierDistance_416) {
  const int begin = 0;
  const int end   = 10;  // inclusive end index
  std::vector<Prog::Inst> flat(end + 1);

  // Barrier at id=10
  flat[10].InitNop(0);

  // Later disjoint byte ranges that do NOT cover id=7's codepoint.
  // They shouldn't change the distance for id=7’s range.
  flat[9].InitByteRange(100, 100, /*foldcase=*/0, 0);
  flat[8].InitByteRange(101, 101, /*foldcase=*/0, 0);

  // Target under test at id=7: covers 102 only.
  flat[7].InitByteRange(102, 102, /*foldcase=*/0, 0);

  // (Earlier indices 0..6 don't affect id=7's hint; leave as default-constructed.)

  prog_.ComputeHints(&flat, begin, end);

  EXPECT_EQ(flat[7].hint(), 3);
}

// Foldcase path covered: range overlaps 'a'..'z' with foldcase=true.
// We only assert observable hint behavior (distance), not internal fold bits.
TEST_F(ProgComputeHintsTest_416, FoldcaseOverLowerLetters_SetsDistance_416) {
  std::vector<Prog::Inst> flat(2);

  // Barrier at id=1
  flat[1].InitNop(0);

  // id=0 overlaps 'a'..'z' and requests foldcase
  // (implementation may also consider 'A'..'Z', but we only verify hint distance)
  flat[0].InitByteRange('`', 'c', /*foldcase=*/1, 0);  // overlaps 'a'..'c'

  prog_.ComputeHints(&flat, /*begin=*/0, /*end=*/1);

  EXPECT_EQ(flat[0].hint(), 1);
}

// Foldcase specified but range outside 'a'..'z' should still behave predictably.
// We assert only the observable hint (distance to the barrier).
TEST_F(ProgComputeHintsTest_416, FoldcaseOutsideLowerLetters_StillSetsDistance_416) {
  std::vector<Prog::Inst> flat(2);

  // Barrier at id=1
  flat[1].InitNop(0);

  // id=0: digits range, foldcase requested (no-op for letters),
  // observable outcome is still the distance to the barrier.
  flat[0].InitByteRange('0', '9', /*foldcase=*/1, 0);

  prog_.ComputeHints(&flat, /*begin=*/0, /*end=*/1);

  EXPECT_EQ(flat[0].hint(), 1);
}

}  // namespace re2
