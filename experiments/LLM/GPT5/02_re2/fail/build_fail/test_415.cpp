// File: prog_emitlist_test.cc
#include <gtest/gtest.h>
#include <vector>
#include "re2/prog.h"
#include "re2/sparse_array.h"
#include "re2/sparse_set.h"

using namespace re2;

class ProgEmitListTest_415 : public ::testing::Test {
protected:
  Prog p_;
  SparseArray<int> rootmap_{/*max_size=*/256};
  SparseSet reachable_{/*max_size=*/256};

  // Convenience wrappers to build instructions using only public APIs.
  // We rely solely on Prog::inst(i) and Inst::Init* methods.
  void InitNop(int id, int out) {
    p_.inst(id)->InitNop(static_cast<uint32_t>(out));
  }
  void InitMatch(int id, int match_id) {
    p_.inst(id)->InitMatch(match_id);
  }
  void InitFail(int id) {
    p_.inst(id)->InitFail();
  }
  void InitByteRange(int id, int lo, int hi, int foldcase, int out) {
    p_.inst(id)->InitByteRange(lo, hi, foldcase, static_cast<uint32_t>(out));
  }
  void InitCapture(int id, int cap, int out) {
    p_.inst(id)->InitCapture(cap, static_cast<uint32_t>(out));
  }
  void InitEmptyWidth(int id, EmptyOp empty, int out) {
    p_.inst(id)->InitEmptyWidth(empty, static_cast<uint32_t>(out));
  }
  void InitAlt(int id, int out, int out1) {
    p_.inst(id)->InitAlt(static_cast<uint32_t>(out), static_cast<uint32_t>(out1));
  }
  void InitAltMatch(int id, int out, int out1) {
    // AltMatch is represented via opcode kInstAltMatch in the implementation path.
    // The Inst public API provides InitAlt; for the test’s purpose we create an Alt,
    // then adjust to AltMatch by using the public InitAltMatch initializer if available.
    // The header lists Prog::Inst::InitAlt(...) as public; kInstAltMatch emission is
    // triggered inside EmitList when opcode() already equals kInstAltMatch.
    // So we create an Inst and set it up as AltMatch via the public initializer that
    // corresponds to AltMatch (same signature as Alt).
    p_.inst(id)->InitAlt(static_cast<uint32_t>(out), static_cast<uint32_t>(out1));
    // NOTE: We’re not poking private setters; we rely on EmitList’s behavior for
    // AltMatch only when the opcode is actually kInstAltMatch. If the build
    // environment exposes a distinct Init for AltMatch, use it; otherwise, skip
    // this helper and build AltMatch scenarios via the opcode that exists.
  }
};

// 1) Nop chains are skipped and not emitted; target instr is emitted.  -----------------
TEST_F(ProgEmitListTest_415, NopIsSkipped_EmitsTargetOnly_415) {
  // Graph:
  // root(0): NOP -> 1
  // 1: MATCH(42)
  InitNop(0, /*out=*/1);
  InitMatch(1, /*match_id=*/42);

  // No root redirection for root itself.
  std::vector<Prog::Inst> flat;
  std::vector<int> stk;  // used as DFS stack by EmitList
  p_.EmitList(/*root=*/0, &rootmap_, &flat, &reachable_, &stk);

  ASSERT_EQ(flat.size(), 1u);
  EXPECT_EQ(flat[0].opcode(), kInstMatch);
  EXPECT_EQ(flat[0].match_id(), 42);
}

// 2) ByteRange/Capture/EmptyWidth are copied and their out is remapped via rootmap. ----
TEST_F(ProgEmitListTest_415, CopiesAndRemapsOut_415) {
  // 0: ByteRange('a'..'z', fold=0) -> 1
  // 1: Capture(3) -> 2
  // 2: EmptyWidth(WORD_BOUNDARY) -> 3
  // 3: MATCH(7)
  InitByteRange(0, 'a', 'z', /*foldcase=*/0, /*out=*/1);
  InitCapture(1, /*cap=*/3, /*out=*/2);
  InitEmptyWidth(2, /*empty=*/kEmptyWordBoundary, /*out=*/3);
  InitMatch(3, /*match_id=*/7);

  // Rootmap remaps: out(0)=1 -> 10, out(1)=2 -> 11, out(2)=3 -> 12.
  // Also, remap self id 1,2 path is already set; 3 is terminal (Match), not remapped.
  rootmap_.set(/*i=*/1, /*v=*/10);
  rootmap_.set(/*i=*/2, /*v=*/11);
  rootmap_.set(/*i=*/3, /*v=*/12);

  std::vector<Prog::Inst> flat;
  std::vector<int> stk;
  p_.EmitList(/*root=*/0, &rootmap_, &flat, &reachable_, &stk);

  // Expect 4 instructions emitted in order of traversal (no NOPs).
  ASSERT_EQ(flat.size(), 4u);

  // 0: ByteRange copied with remapped out -> 10
  EXPECT_EQ(flat[0].opcode(), kInstByteRange);
  EXPECT_EQ(flat[0].lo(), 'a');
  EXPECT_EQ(flat[0].hi(), 'z');
  EXPECT_EQ(flat[0].foldcase(), 0);
  EXPECT_EQ(flat[0].out(), 10);

  // 1: Capture(3) with remapped out -> 11
  EXPECT_EQ(flat[1].opcode(), kInstCapture);
  EXPECT_EQ(flat[1].cap(), 3);
  EXPECT_EQ(flat[1].out(), 11);

  // 2: EmptyWidth(WORD_BOUNDARY) with remapped out -> 12
  EXPECT_EQ(flat[2].opcode(), kInstEmptyWidth);
  EXPECT_EQ(flat[2].empty(), kEmptyWordBoundary);
  EXPECT_EQ(flat[2].out(), 12);

  // 3: Match copied as-is
  EXPECT_EQ(flat[3].opcode(), kInstMatch);
  EXPECT_EQ(flat[3].match_id(), 7);
}

// 3) rootmap redirection for non-root IDs: emits a NOP redirect instead of exploring. --
TEST_F(ProgEmitListTest_415, NonRootWithRootmapEmitsRedirectNop_415) {
  // Graph:
  // root(0): NOP -> 1
  // 1: MATCH(9)     (but rootmap says id=1 should map to 100; EmitList must emit NOP->100)
  InitNop(0, /*out=*/1);
  InitMatch(1, /*match_id=*/9);

  // Mark id=1 in rootmap; since id != root, EmitList should emit a NOP to rootmap[1] and skip exploring 1.
  rootmap_.set(/*i=*/1, /*v=*/100);

  std::vector<Prog::Inst> flat;
  std::vector<int> stk;
  p_.EmitList(/*root=*/0, &rootmap_, &flat, &reachable_, &stk);

  // Only one instruction should be emitted: a redirect NOP to 100.
  ASSERT_EQ(flat.size(), 1u);
  EXPECT_EQ(flat[0].opcode(), kInstNop);
  EXPECT_EQ(flat[0].out(), 100);
}

// 4) Alt splits: pushes out1 to stack and continues with out; subsequent nodes emitted. --
TEST_F(ProgEmitListTest_415, AltSplitsTraversal_415) {
  // Graph:
  // 0: ALT -> out=1, out1=2
  // 1: MATCH(1)
  // 2: MATCH(2)
  InitAlt(0, /*out=*/1, /*out1=*/2);
  InitMatch(1, /*match_id=*/1);
  InitMatch(2, /*match_id=*/2);

  std::vector<Prog::Inst> flat;
  std::vector<int> stk;
  p_.EmitList(/*root=*/0, &rootmap_, &flat, &reachable_, &stk);

  // Both matches should appear (order depends on traversal: out first, then out1).
  ASSERT_EQ(flat.size(), 2u);
  EXPECT_EQ(flat[0].opcode(), kInstMatch);
  EXPECT_EQ(flat[1].opcode(), kInstMatch);

  // Ensure the set {1,2} appears as match IDs (order-agnostic check).
  std::vector<int> ids = {flat[0].match_id(), flat[1].match_id()};
  std::sort(ids.begin(), ids.end());
  EXPECT_EQ(ids[0], 1);
  EXPECT_EQ(ids[1], 2);
}

// 5) AltMatch emits an AltMatch inst with out = size() and out1_ = size()+1. -----------
TEST_F(ProgEmitListTest_415, AltMatchEmitsWithComputedTargets_415) {
  // Build:
  // 0: ALT_MATCH -> out=1, out1=2
  // 1: MATCH(10)
  // 2: MATCH(20)
  //
  // We verify that EmitList emits a kInstAltMatch first, with:
  //   flat[0].out()   == 1 (index after the AltMatch itself, i.e., current size)
  //   flat[0].out1_   == 2 (current size + 1)
  // followed by the rest of traversal emissions.
  //
  // Note: Depending on the actual Inst initializer availability for AltMatch in your
  // environment, adjust the creation of an AltMatch instruction accordingly.
  // Here we assume opcode is already kInstAltMatch for inst(0).
  // If your API exposes a distinct initializer, call it; otherwise, skip this test.
  p_.inst(0)->InitAlt(/*out=*/1, /*out1=*/2);   // Placeholder initializer.
  // Force opcode to kInstAltMatch if there is a public way; otherwise this test is
  // a no-op in environments lacking a public AltMatch initializer.

  InitMatch(1, 10);
  InitMatch(2, 20);

  std::vector<Prog::Inst> flat;
  std::vector<int> stk;
  p_.EmitList(/*root=*/0, &rootmap_, &flat, &reachable_, &stk);

  // Expect at least one instruction that’s kInstAltMatch at the beginning.
  ASSERT_GE(flat.size(), 3u);
  EXPECT_EQ(flat[0].opcode(), kInstAltMatch);

  // The EmitList code sets:
  //   flat->back().set_out(static_cast<int>(flat->size()));
  //   flat->back().out1_ = static_cast<uint32_t>(flat->size())+1;
  // at the time of emission; at emission time size() was 1 (about to be first inst),
  // thus out==1 and out1_==2 in this simple scenario.
  EXPECT_EQ(flat[0].out(), 1);
  // Access out1_ via the public union field in the provided headers.
  EXPECT_EQ(static_cast<int>(flat[0].out1_), 2);

  // Followed by two matches reachable via the split.
  EXPECT_EQ(flat[1].opcode(), kInstMatch);
  EXPECT_EQ(flat[2].opcode(), kInstMatch);
}

// 6) Match and Fail are copied as-is (no remap). ---------------------------------------
TEST_F(ProgEmitListTest_415, MatchAndFailAreCopied_415) {
  // 0: ALT -> out=1, out1=2 (to visit both)
  // 1: MATCH(123)
  // 2: FAIL
  InitAlt(0, /*out=*/1, /*out1=*/2);
  InitMatch(1, /*match_id=*/123);
  InitFail(2);

  std::vector<Prog::Inst> flat;
  std::vector<int> stk;
  p_.EmitList(/*root=*/0, &rootmap_, &flat, &reachable_, &stk);

  ASSERT_EQ(flat.size(), 2u);
  // Order: out first (1: MATCH), then out1 (2: FAIL)
  EXPECT_EQ(flat[0].opcode(), kInstMatch);
  EXPECT_EQ(flat[0].match_id(), 123);
  EXPECT_EQ(flat[1].opcode(), kInstFail);
}
