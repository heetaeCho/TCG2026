// File: patchlist_patch_test_286.cc
#include <gtest/gtest.h>

#include "re2/prog.h"
// Bring in the PatchList definition & Patch() implementation.
#include "re2/compile.cc"

using re2::Prog;
using re2::PatchList;

namespace {

// Small helper used **only** for test setup based on what Patch() itself
// reads from l.head (>>1 for index, &1 for choosing out1 vs out).
static inline uint32_t EncodedLink(int inst_index, bool use_out1) {
  return (static_cast<uint32_t>(inst_index) << 1) | (use_out1 ? 1u : 0u);
}

}  // namespace

// Suite: PatchListTest_286

// Normal case: single node targets out; Patch should set out() to p and stop.
TEST(PatchListTest_286, SingleOutPatch_286) {
  Prog::Inst insts[1];
  // out() initially points to 0 (end of list), so Patch will set and stop.
  insts[0].InitNop(/*out=*/0);

  const uint32_t p = 1234;
  PatchList l;
  l.head = EncodedLink(/*inst_index=*/0, /*use_out1=*/false);
  l.tail = 0;  // not used by Patch()

  // Precondition sanity.
  ASSERT_NE(insts[0].out(), static_cast<int>(p));

  PatchList::Patch(insts, l, p);

  EXPECT_EQ(insts[0].out(), static_cast<int>(p));
  // Non-target field should remain unchanged.
  EXPECT_EQ(insts[0].out1(), 0);
}

// Normal case: single node targets out1; Patch should set out1() to p and stop.
TEST(PatchListTest_286, SingleOut1Patch_286) {
  Prog::Inst insts[1];
  // Use Alt to be able to read out1().
  insts[0].InitAlt(/*out=*/0, /*out1=*/0);

  const uint32_t p = 5678;
  PatchList l;
  l.head = EncodedLink(/*inst_index=*/0, /*use_out1=*/true);
  l.tail = 0;

  // Precondition sanity.
  ASSERT_NE(insts[0].out1(), static_cast<int>(p));

  PatchList::Patch(insts, l, p);

  EXPECT_EQ(insts[0].out1(), static_cast<int>(p));
  // Non-target field should remain unchanged.
  EXPECT_EQ(insts[0].out(), 0);
}

// Mixed multi-node chain: out -> out1 -> out.
// Ensures Patch follows next links and patches each targeted field to p.
TEST(PatchListTest_286, MultiNodeMixedFields_286) {
  Prog::Inst insts[3];

  // inst[0]: out() links to (inst[1], out1)
  insts[0].InitNop(EncodedLink(/*inst_index=*/1, /*use_out1=*/true));
  // inst[1]: out1() links to (inst[2], out)
  insts[1].InitAlt(/*out=*/0, /*out1=*/EncodedLink(/*inst_index=*/2, /*use_out1=*/false));
  // inst[2]: out() links to end (0)
  insts[2].InitNop(/*out=*/0);

  const uint32_t p = 9999;

  PatchList l;
  // Start list at (inst[0], out)
  l.head = EncodedLink(/*inst_index=*/0, /*use_out1=*/false);
  l.tail = 0;

  // Sanity: ensure all targeted fields are different from p before patch.
  ASSERT_NE(insts[0].out(), static_cast<int>(p));
  ASSERT_NE(insts[1].out1(), static_cast<int>(p));
  ASSERT_NE(insts[2].out(), static_cast<int>(p));

  PatchList::Patch(insts, l, p);

  // All three targeted fields should be patched to p.
  EXPECT_EQ(insts[0].out(), static_cast<int>(p));
  EXPECT_EQ(insts[1].out1(), static_cast<int>(p));
  EXPECT_EQ(insts[2].out(), static_cast<int>(p));

  // Non-target fields remain as they were.
  // inst[0].out1() was never targeted.
  EXPECT_EQ(insts[0].out1(), 0);
  // inst[1].out() was never targeted and was initialized to 0.
  EXPECT_EQ(insts[1].out(), 0);
  // inst[2] has no out1() initialization; expect default (commonly 0).
  EXPECT_EQ(insts[2].out1(), 0);
}

// Boundary: empty list (head == 0) is a no-op.
TEST(PatchListTest_286, NoOpOnEmptyList_286) {
  Prog::Inst insts[2];
  // Give them recognizable non-zero values to detect accidental changes.
  insts[0].InitAlt(/*out=*/42, /*out1=*/84);
  insts[1].InitAlt(/*out=*/7,  /*out1=*/13);

  PatchList l;
  l.head = 0;
  l.tail = 0;

  const uint32_t p = 123456;

  // Capture pre-state.
  const int o0  = insts[0].out();
  const int o10 = insts[0].out1();
  const int o1  = insts[1].out();
  const int o11 = insts[1].out1();

  PatchList::Patch(insts, l, p);

  // Nothing should change.
  EXPECT_EQ(insts[0].out(),  o0);
  EXPECT_EQ(insts[0].out1(), o10);
  EXPECT_EQ(insts[1].out(),  o1);
  EXPECT_EQ(insts[1].out1(), o11);
}

// Verifies non-target field is not modified while traversing.
// Case 1: Target out — out1 must stay intact.
// Case 2: Target out1 — out must stay intact.
TEST(PatchListTest_286, NonTargetFieldUnaffected_286) {
  // Case 1: Patch 'out' and ensure 'out1' unchanged.
  {
    Prog::Inst inst;
    inst.InitAlt(/*out=*/0, /*out1=*/77);  // recognizable out1
    PatchList l;
    l.head = EncodedLink(/*inst_index=*/0, /*use_out1=*/false);
    l.tail = 0;

    PatchList::Patch(&inst, l, /*p=*/555);

    EXPECT_EQ(inst.out(), 555);
    EXPECT_EQ(inst.out1(), 77);  // untouched
  }

  // Case 2: Patch 'out1' and ensure 'out' unchanged.
  {
    Prog::Inst inst;
    inst.InitAlt(/*out=*/88, /*out1=*/0);  // recognizable out
    PatchList l;
    l.head = EncodedLink(/*inst_index=*/0, /*use_out1=*/true);
    l.tail = 0;

    PatchList::Patch(&inst, l, /*p=*/666);

    EXPECT_EQ(inst.out1(), 666);
    EXPECT_EQ(inst.out(), 88);  // untouched
  }
}
