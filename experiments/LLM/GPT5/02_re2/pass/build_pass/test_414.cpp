// File: prog_mark_dominator_test_414.cc

#include <gtest/gtest.h>
#include <vector>
#include "re2/prog.h"
#include "re2/sparse_array.h"
#include "re2/sparse_set.h"

using re2::Prog;
using re2::SparseArray;
using re2::SparseSet;
using re2::InstOp;

namespace {

// Small helper: ensure program has at least N instructions we can initialize.
// We only rely on the public Prog::inst(int) + Inst::Init* interface and do not
// read any private state.
static void EnsureInsts(Prog* p, int n) {
  // Accessing inst(i) must be valid for 0..n-1. We touch each via InitFail().
  // This stays within public interface (no assumptions on internals).
  for (int i = 0; i < n; ++i) {
    p->inst(i)->InitFail();  // placeholder op we will overwrite below
  }
}

static bool SetContains(const SparseSet& s, int id) {
  for (auto it = s.begin(); it != s.end(); ++it) {
    if (*it == id) return true;
  }
  return false;
}

}  // namespace

// ------------------------------------------------------------
// Basic: single node root that does not branch.
// Reachability should include root. No preds outside reachable,
// so rootmap should remain empty.
// ------------------------------------------------------------
TEST(Prog_MarkDominator_414, SingleNode_NoPreds_RootmapUnchanged_414) {
  Prog prog;

  // Build: one node (id=0) that is terminal (MATCH)
  EnsureInsts(&prog, 1);
  prog.inst(0)->InitMatch(/*id=*/0);

  SparseArray<int> rootmap(/*max_size=*/16);
  SparseArray<int> predmap(/*max_size=*/16);
  std::vector<std::vector<int>> predvec;  // empty: no predecessors anywhere
  SparseSet reachable(/*max_size=*/16);
  std::vector<int> stk;

  prog.MarkDominator(/*root=*/0, &rootmap, &predmap, &predvec, &reachable, &stk);

  // Observable effects:
  // 1) reachable should include the root.
  EXPECT_TRUE(SetContains(reachable, 0));

  // 2) With no predmap/predvec entries, rootmap should remain empty.
  EXPECT_EQ(rootmap.size(), 0);
}

// ------------------------------------------------------------
// NOP -> MATCH linear chain reachable from root.
// Still no external preds for any reachable node, so rootmap unchanged.
// ------------------------------------------------------------
TEST(Prog_MarkDominator_414, Linear_NopToMatch_NoExternalPreds_RootmapUnchanged_414) {
  Prog prog;

  EnsureInsts(&prog, 2);
  // 0: NOP -> 1
  prog.inst(0)->InitNop(/*out=*/1);
  // 1: MATCH
  prog.inst(1)->InitMatch(/*id=*/1);

  SparseArray<int> rootmap(/*max_size=*/16);
  SparseArray<int> predmap(/*max_size=*/16);
  std::vector<std::vector<int>> predvec(2);  // empty lists = no external preds
  SparseSet reachable(/*max_size=*/16);
  std::vector<int> stk;

  prog.MarkDominator(/*root=*/0, &rootmap, &predmap, &predvec, &reachable, &stk);

  // Reachable must contain 0 and 1 (observable via iterator).
  EXPECT_TRUE(SetContains(reachable, 0));
  EXPECT_TRUE(SetContains(reachable, 1));

  // No external preds -> rootmap remains empty.
  EXPECT_EQ(rootmap.size(), 0);
}

// ------------------------------------------------------------
// ALT branching: 0 -(out)-> 1, and 0 -(out1)-> 2, both end at MATCH.
// predmap/predvec declare that node 1 has a predecessor '99' which is
// *not* reachable from root. That should cause rootmap to gain an index
// for node 1 (observable via has_index/size).
// ------------------------------------------------------------
TEST(Prog_MarkDominator_414, AltBranch_ExternalPredOnReachableNode_AddsToRootmap_414) {
  Prog prog;

  EnsureInsts(&prog, 4);
  // 0: ALT to 1 and 2
  prog.inst(0)->InitAlt(/*out=*/1, /*out1=*/2);
  // 1: MATCH
  prog.inst(1)->InitMatch(/*id=*/1);
  // 2: MATCH
  prog.inst(2)->InitMatch(/*id=*/2);
  // 3: (unused but allocated) FAIL
  prog.inst(3)->InitFail();

  SparseArray<int> rootmap(/*max_size=*/16);
  SparseArray<int> predmap(/*max_size=*/16);
  // predvec for indices referenced by predmap
  std::vector<std::vector<int>> predvec;

  // We want: predmap.has_index(1) == true, and predvec[ predmap.get_existing(1) ]
  // contains an external predecessor '99' which is *not* reachable from root.
  // To do that, we set predmap[1] = 0 and make predvec[0] = {99}
  // (The exact index value stored by set_new is opaque; we only follow API.)
  predvec.resize(1);
  predvec[0] = {99};
  predmap.set_new(/*i=*/1, /*v=*/0);

  SparseSet reachable(/*max_size=*/16);
  std::vector<int> stk;

  prog.MarkDominator(/*root=*/0, &rootmap, &predmap, &predvec, &reachable, &stk);

  // Sanity: 0,1,2 are reachable.
  EXPECT_TRUE(SetContains(reachable, 0));
  EXPECT_TRUE(SetContains(reachable, 1));
  EXPECT_TRUE(SetContains(reachable, 2));

  // Because node 1 had an external predecessor (99) not in 'reachable',
  // MarkDominator should have recorded node 1 in rootmap exactly once.
  EXPECT_TRUE(rootmap.has_index(1));
  EXPECT_EQ(rootmap.size(), 1);
}

// ------------------------------------------------------------
// External predecessor on a node that is *not* reachable from root
// should NOT cause rootmap to change, because the target id isn't
// even visited.
// Here, root=2; only 2 is reachable (MATCH), while we put external
// preds on id=1 in predmap/predvec. rootmap should remain empty.
// ------------------------------------------------------------
TEST(Prog_MarkDominator_414, ExternalPredOnUnreachableNode_DoesNotAffectRootmap_414) {
  Prog prog;

  EnsureInsts(&prog, 2);
  // 0: MATCH (unreachable in this test)
  prog.inst(0)->InitMatch(/*id=*/0);
  // 1: MATCH (we’ll use root=1 so only 1 is visited; 0 remains unreachable)
  prog.inst(1)->InitMatch(/*id=*/1);

  SparseArray<int> rootmap(/*max_size=*/16);
  SparseArray<int> predmap(/*max_size=*/16);
  std::vector<std::vector<int>> predvec(1);
  // Put a pred entry for id=0 (unreachable), with an external predecessor.
  predvec[0] = {12345};
  predmap.set_new(/*i=*/0, /*v=*/0);

  SparseSet reachable(/*max_size=*/16);
  std::vector<int> stk;

  prog.MarkDominator(/*root=*/1, &rootmap, &predmap, &predvec, &reachable, &stk);

  // Reachable contains only 1.
  EXPECT_TRUE(SetContains(reachable, 1));
  EXPECT_FALSE(SetContains(reachable, 0));

  // Since the pred target (0) was not in reachable, rootmap is unchanged.
  EXPECT_EQ(rootmap.size(), 0);
}

// ------------------------------------------------------------
// Idempotency on same id: If multiple external preds exist for the
// same reachable node, rootmap should still only get one new index.
// This verifies we don't rely on private counters — only observable size/has_index.
// ------------------------------------------------------------
TEST(Prog_MarkDominator_414, MultipleExternalPreds_SetsRootmapOnce_414) {
  Prog prog;

  EnsureInsts(&prog, 2);
  // 0: NOP -> 1
  prog.inst(0)->InitNop(/*out=*/1);
  // 1: MATCH
  prog.inst(1)->InitMatch(/*id=*/1);

  SparseArray<int> rootmap(/*max_size=*/16);
  SparseArray<int> predmap(/*max_size=*/16);
  std::vector<std::vector<int>> predvec(1);
  // Two different external preds pointing into id=1.
  predvec[0] = {100, 200, 300};
  predmap.set_new(/*i=*/1, /*v=*/0);

  SparseSet reachable(/*max_size=*/16);
  std::vector<int> stk;

  prog.MarkDominator(/*root=*/0, &rootmap, &predmap, &predvec, &reachable, &stk);

  // Reachable must include 0 and 1.
  EXPECT_TRUE(SetContains(reachable, 0));
  EXPECT_TRUE(SetContains(reachable, 1));

  // rootmap should have exactly one entry for id=1.
  EXPECT_TRUE(rootmap.has_index(1));
  EXPECT_EQ(rootmap.size(), 1);
}

