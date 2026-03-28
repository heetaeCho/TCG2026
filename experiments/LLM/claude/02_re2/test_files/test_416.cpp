#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include <vector>

namespace re2 {

class ComputeHintsTest_416 : public ::testing::Test {
 protected:
  Prog prog_;

  // Helper to create a ByteRange instruction
  Prog::Inst MakeByteRange(int lo, int hi, int foldcase, uint32_t out) {
    Prog::Inst inst;
    inst.InitByteRange(lo, hi, foldcase, out);
    return inst;
  }

  // Helper to create a Match instruction (non-ByteRange)
  Prog::Inst MakeMatch(int id) {
    Prog::Inst inst;
    inst.InitMatch(id);
    return inst;
  }

  // Helper to create a Nop instruction (non-ByteRange)
  Prog::Inst MakeNop(uint32_t out) {
    Prog::Inst inst;
    inst.InitNop(out);
    return inst;
  }

  // Helper to create a Fail instruction (non-ByteRange)
  Prog::Inst MakeFail() {
    Prog::Inst inst;
    inst.InitFail();
    return inst;
  }
};

// Test with empty range (begin == end)
TEST_F(ComputeHintsTest_416, EmptyRange_416) {
  std::vector<Prog::Inst> flat;
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, 0);
  // Should not crash; with begin==end, the loop body runs once for id=0
  // and the instruction is a Match (not ByteRange), so it just sets up colors.
  EXPECT_EQ(flat[0].hint(), 0);
}

// Test with a single non-ByteRange instruction
TEST_F(ComputeHintsTest_416, SingleNonByteRange_416) {
  std::vector<Prog::Inst> flat;
  flat.push_back(MakeMatch(0));
  flat.push_back(MakeFail());
  prog_.ComputeHints(&flat, 0, 1);
  // The Match at index 0 is not a ByteRange, so no hint modification expected.
  EXPECT_EQ(flat[0].hint(), 0);
}

// Test with a single ByteRange instruction followed by a non-ByteRange
TEST_F(ComputeHintsTest_416, SingleByteRange_416) {
  std::vector<Prog::Inst> flat;
  flat.push_back(MakeByteRange('a', 'z', 0, 1));
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, 1);
  // With only one ByteRange before the end, first should be end (1),
  // so no hint is set (first == end).
  EXPECT_EQ(flat[0].hint(), 0);
}

// Test with two ByteRange instructions with non-overlapping ranges
TEST_F(ComputeHintsTest_416, TwoNonOverlappingByteRanges_416) {
  std::vector<Prog::Inst> flat;
  // Index 0: range 'a'-'m'
  flat.push_back(MakeByteRange('a', 'm', 0, 2));
  // Index 1: range 'n'-'z'
  flat.push_back(MakeByteRange('n', 'z', 0, 2));
  // Index 2: Match
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, 2);
  // Non-overlapping ranges: no instruction should hint to another
  // because each covers different bytes.
  EXPECT_EQ(flat[0].hint(), 0);
  EXPECT_EQ(flat[1].hint(), 0);
}

// Test with two ByteRange instructions with overlapping ranges
TEST_F(ComputeHintsTest_416, TwoOverlappingByteRanges_416) {
  std::vector<Prog::Inst> flat;
  // Index 0: range 'a'-'z'
  flat.push_back(MakeByteRange('a', 'z', 0, 2));
  // Index 1: range 'a'-'z' (same range)
  flat.push_back(MakeByteRange('a', 'z', 0, 2));
  // Index 2: Match
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, 2);
  // Index 1 processes first (reverse order). When index 0 processes,
  // it finds that index 1 already colored these bytes, so first = 1.
  // hint for index 0 = min(1 - 0, 32767) = 1
  EXPECT_EQ(flat[0].hint(), 1);
  // Index 1 was the first ByteRange processed, first should be end (2), no hint.
  EXPECT_EQ(flat[1].hint(), 0);
}

// Test with foldcase enabled and overlapping case-folded range
TEST_F(ComputeHintsTest_416, FoldcaseOverlap_416) {
  std::vector<Prog::Inst> flat;
  // Index 0: range 'A'-'Z', foldcase=1 => also covers 'A'-'Z' folded from 'a'-'z'
  flat.push_back(MakeByteRange('a', 'z', 1, 2));
  // Index 1: range 'A'-'Z', no foldcase
  flat.push_back(MakeByteRange('A', 'Z', 0, 2));
  // Index 2: Match
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, 2);
  // Index 1 covers 'A'-'Z'. Index 0 covers 'a'-'z' and (with foldcase) 'A'-'Z'.
  // The 'A'-'Z' part overlaps with index 1, so first should be 1 for index 0.
  EXPECT_EQ(flat[0].hint(), 1);
}

// Test with three ByteRange instructions, partial overlaps
TEST_F(ComputeHintsTest_416, ThreeByteRangesPartialOverlap_416) {
  std::vector<Prog::Inst> flat;
  // Index 0: range 'a'-'f'
  flat.push_back(MakeByteRange('a', 'f', 0, 3));
  // Index 1: range 'd'-'k'
  flat.push_back(MakeByteRange('d', 'k', 0, 3));
  // Index 2: range 'h'-'z'
  flat.push_back(MakeByteRange('h', 'z', 0, 3));
  // Index 3: Match
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, 3);
  // Processing in reverse: index 2, then 1, then 0.
  // Index 2: first ByteRange, no overlap -> hint = 0
  EXPECT_EQ(flat[2].hint(), 0);
  // Index 1: overlaps with index 2 on 'h'-'k', so first = 2, hint = 2-1 = 1
  EXPECT_EQ(flat[1].hint(), 1);
  // Index 0: overlaps with index 1 on 'd'-'f', so first = 1, hint = 1-0 = 1
  EXPECT_EQ(flat[0].hint(), 1);
}

// Test with begin > 0 (subset of the flat array)
TEST_F(ComputeHintsTest_416, SubsetRange_416) {
  std::vector<Prog::Inst> flat;
  // Index 0: something before our range
  flat.push_back(MakeMatch(0));
  // Index 1: range 'a'-'z'
  flat.push_back(MakeByteRange('a', 'z', 0, 3));
  // Index 2: range 'a'-'z'
  flat.push_back(MakeByteRange('a', 'z', 0, 3));
  // Index 3: Match
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 1, 3);
  // Index 2 processed first, then index 1.
  // Index 1 overlaps with index 2, hint = 2-1 = 1
  EXPECT_EQ(flat[1].hint(), 1);
  EXPECT_EQ(flat[2].hint(), 0);
}

// Test hint capping at 32767
TEST_F(ComputeHintsTest_416, HintCappedAt32767_416) {
  // Create a large flat vector with many ByteRange instructions covering same range
  const int N = 40000;
  std::vector<Prog::Inst> flat;
  for (int i = 0; i < N; i++) {
    flat.push_back(MakeByteRange('a', 'a', 0, N));
  }
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, N);
  // The first instruction (index 0) would want to hint to index 1,
  // so hint = 1 (min(1, 32767)).
  // But let's check that for index 0, the hint doesn't exceed 32767
  // even if the "first" value were very far away.
  int hint0 = flat[0].hint();
  EXPECT_LE(hint0, 32767);
  EXPECT_GE(hint0, 0);
}

// Test with non-ByteRange instructions interspersed
TEST_F(ComputeHintsTest_416, InterspersedNonByteRange_416) {
  std::vector<Prog::Inst> flat;
  // Index 0: ByteRange 'a'-'z'
  flat.push_back(MakeByteRange('a', 'z', 0, 4));
  // Index 1: Nop (non-ByteRange, resets state)
  flat.push_back(MakeNop(2));
  // Index 2: ByteRange 'a'-'z'
  flat.push_back(MakeByteRange('a', 'z', 0, 4));
  // Index 3: ByteRange 'a'-'z'
  flat.push_back(MakeByteRange('a', 'z', 0, 4));
  // Index 4: Match
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, 4);
  // Index 3 and 2 overlap, so index 2 should have hint = 1.
  EXPECT_EQ(flat[2].hint(), 1);
  // Index 3 is the first in its group after the Nop, no hint.
  EXPECT_EQ(flat[3].hint(), 0);
  // Index 0 is before the Nop. The Nop at index 1 resets state,
  // so index 0 should have no overlap info from index 2/3.
  EXPECT_EQ(flat[0].hint(), 0);
}

// Test with full byte range (0-255)
TEST_F(ComputeHintsTest_416, FullByteRange_416) {
  std::vector<Prog::Inst> flat;
  flat.push_back(MakeByteRange(0, 255, 0, 2));
  flat.push_back(MakeByteRange(0, 255, 0, 2));
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, 2);
  EXPECT_EQ(flat[0].hint(), 1);
  EXPECT_EQ(flat[1].hint(), 0);
}

// Test with single byte range (lo == hi)
TEST_F(ComputeHintsTest_416, SingleByteValue_416) {
  std::vector<Prog::Inst> flat;
  flat.push_back(MakeByteRange('x', 'x', 0, 2));
  flat.push_back(MakeByteRange('x', 'x', 0, 2));
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, 2);
  EXPECT_EQ(flat[0].hint(), 1);
  EXPECT_EQ(flat[1].hint(), 0);
}

// Test with no overlap - different single bytes
TEST_F(ComputeHintsTest_416, DifferentSingleBytes_416) {
  std::vector<Prog::Inst> flat;
  flat.push_back(MakeByteRange('a', 'a', 0, 2));
  flat.push_back(MakeByteRange('b', 'b', 0, 2));
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, 2);
  EXPECT_EQ(flat[0].hint(), 0);
  EXPECT_EQ(flat[1].hint(), 0);
}

// Test foldcase with range partially in a-z
TEST_F(ComputeHintsTest_416, FoldcasePartialRange_416) {
  std::vector<Prog::Inst> flat;
  // Index 0: range 'x'-'z' with foldcase => also covers 'X'-'Z'
  flat.push_back(MakeByteRange('x', 'z', 1, 2));
  // Index 1: range 'X'-'Z' without foldcase
  flat.push_back(MakeByteRange('X', 'Z', 0, 2));
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, 2);
  // Overlap on 'X'-'Z' due to foldcase
  EXPECT_EQ(flat[0].hint(), 1);
}

// Test foldcase where range doesn't intersect a-z
TEST_F(ComputeHintsTest_416, FoldcaseNoIntersectionWithLowercase_416) {
  std::vector<Prog::Inst> flat;
  // Range 0-31 with foldcase: lo > 'z' is false but hi < 'a', so no fold
  flat.push_back(MakeByteRange(0, 31, 1, 2));
  flat.push_back(MakeByteRange(0, 31, 0, 2));
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, 2);
  // Both cover 0-31, overlapping
  EXPECT_EQ(flat[0].hint(), 1);
}

// Test begin == end with a single instruction at that index
TEST_F(ComputeHintsTest_416, BeginEqualsEnd_416) {
  std::vector<Prog::Inst> flat;
  flat.push_back(MakeByteRange('a', 'z', 0, 0));
  prog_.ComputeHints(&flat, 0, 0);
  // When begin == end, the loop processes id = 0 only.
  // id == end (0 == 0), so it's treated as non-ByteRange reset.
  EXPECT_EQ(flat[0].hint(), 0);
}

// Test with many overlapping ByteRange instructions
TEST_F(ComputeHintsTest_416, ManyOverlappingRanges_416) {
  std::vector<Prog::Inst> flat;
  const int N = 100;
  for (int i = 0; i < N; i++) {
    flat.push_back(MakeByteRange('a', 'z', 0, N));
  }
  flat.push_back(MakeMatch(0));
  prog_.ComputeHints(&flat, 0, N);
  // Each instruction except the last ByteRange should hint to the next
  for (int i = 0; i < N - 1; i++) {
    EXPECT_EQ(flat[i].hint(), 1) << "at index " << i;
  }
  // Last ByteRange has no subsequent overlapping instruction
  EXPECT_EQ(flat[N - 1].hint(), 0);
}

}  // namespace re2
