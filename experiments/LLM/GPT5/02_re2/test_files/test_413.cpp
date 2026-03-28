// File: prog_mark_successors_test.cc
#include <gtest/gtest.h>
#include <vector>

#include "re2/prog.h"
#include "re2/sparse_array.h"
#include "re2/sparse_set.h"

using namespace re2;

class ProgMarkSuccessorsTest_413 : public ::testing::Test {
protected:
  // Helpers to make building tiny graphs concise and readable.
  static void SetMatch(Prog& p, int id, int match_id = 0) {
    p.inst(id)->InitMatch(match_id);
  }
  static void SetAlt(Prog& p, int id, int out, int out1) {
    p.inst(id)->InitAlt(out, out1);
  }
  static void SetAltMatch(Prog& p, int id, int out, int out1) {
    // Behaves like Alt in MarkSuccessors (adds both as successors).
    p.inst(id)->InitAlt(out, out1);
  }
  static void SetNop(Prog& p, int id, int out) {
    p.inst(id)->InitNop(out);
  }
  static void SetByteRange(Prog& p, int id, int out,
                           int lo = 0, int hi = 255, int fold = 0) {
    p.inst(id)->InitByteRange(lo, hi, fold, out);
  }
};

// Normal traversal with ALT and linear edges.
// Graph:
//   2: Alt(out=1,out1=0)
//   1: ByteRange(..., out=0)
//   0: Match
// start_unanchored = 2, start = 1
TEST_F(ProgMarkSuccessorsTest_413, AltAndLinearTraversal_PopulatesMapsAndReachable_413) {
  Prog p;

  // Program graph
  SetMatch(p, 0, /*match_id=*/123);
  SetByteRange(p, 1, /*out=*/0);
  SetAlt(p, 2, /*out=*/1, /*out1=*/0);

  p.set_start_unanchored(2);
  p.set_start(1);

  // Collaborators
  SparseArray<int> rootmap(16);
  SparseArray<int> predmap(16);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(16);
  std::vector<int> stk;

  // Execute
  p.MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  // Root/starts are always registered.
  EXPECT_TRUE(rootmap.has_index(0));
  EXPECT_TRUE(rootmap.has_index(p.start_unanchored()));
  EXPECT_TRUE(rootmap.has_index(p.start()));

  // ALT adds predecessor lists for both out and out1.
  ASSERT_TRUE(predmap.has_index(1));
  ASSERT_TRUE(predmap.has_index(0));
  {
    int idx1 = predmap.get_existing(1);
    ASSERT_LT(idx1, static_cast<int>(predvec.size()));
    // Node 2 should be recorded as a predecessor of 1
    EXPECT_NE(std::find(predvec[idx1].begin(), predvec[idx1].end(), 2),
              predvec[idx1].end());
  }
  {
    int idx0 = predmap.get_existing(0);
    ASSERT_LT(idx0, static_cast<int>(predvec.size()));
    // Node 2 should be recorded as a predecessor of 0
    EXPECT_NE(std::find(predvec[idx0].begin(), predvec[idx0].end(), 2),
              predvec[idx0].end());
  }

  // Reachable should include everything visited by DFS from start_unanchored.
  EXPECT_TRUE(reachable.contains(2));
  EXPECT_TRUE(reachable.contains(1));
  EXPECT_TRUE(reachable.contains(0));

  // Work stack is emptied by the traversal.
  EXPECT_TRUE(stk.empty());
}

// Clearing behavior and no-pred-list path with NOP -> MATCH.
// Graph:
//   3: Nop(out=0)
//   0: Match
// start_unanchored = 3
TEST_F(ProgMarkSuccessorsTest_413, ClearsInputsAndHandlesLinearPath_NoPredecessors_413) {
  Prog p;

  SetMatch(p, 0);
  SetNop(p, 3, /*out=*/0);

  p.set_start_unanchored(3);
  p.set_start(0);  // also make a start index available

  SparseArray<int> rootmap(8);
  SparseArray<int> predmap(8);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(8);
  std::vector<int> stk;

  // Pre-fill to ensure they are cleared by MarkSuccessors.
  reachable.insert_new(99);
  stk.push_back(42);

  p.MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  // Pre-filled values are cleared by the function before traversal.
  EXPECT_FALSE(reachable.contains(99));
  EXPECT_TRUE(stk.empty());

  // Traversal from 3 should reach 3 and 0.
  EXPECT_TRUE(reachable.contains(3));
  EXPECT_TRUE(reachable.contains(0));

  // No ALT encountered => no predecessor lists should exist.
  EXPECT_EQ(predvec.size(), 0u);
  // predmap size() is observable; it should reflect no entries.
  EXPECT_EQ(predmap.size(), 0);
}

// kInstAltMatch is handled like kInstAlt for predecessor bookkeeping.
// Graph:
//   4: AltMatch(out=0,out1=1)
//   1: Match
//   0: Match
// start_unanchored = 4
TEST_F(ProgMarkSuccessorsTest_413, AltMatch_RecordsBothSuccessorPredecessors_413) {
  Prog p;

  SetMatch(p, 0);
  SetMatch(p, 1);
  SetAltMatch(p, 4, /*out=*/0, /*out1=*/1);

  p.set_start_unanchored(4);
  p.set_start(0);

  SparseArray<int> rootmap(8);
  SparseArray<int> predmap(8);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(8);
  std::vector<int> stk;

  p.MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  // Predecessor lists should exist for both targets.
  ASSERT_TRUE(predmap.has_index(0));
  ASSERT_TRUE(predmap.has_index(1));
  {
    int i0 = predmap.get_existing(0);
    ASSERT_LT(i0, static_cast<int>(predvec.size()));
    EXPECT_NE(std::find(predvec[i0].begin(), predvec[i0].end(), 4),
              predvec[i0].end());
  }
  {
    int i1 = predmap.get_existing(1);
    ASSERT_LT(i1, static_cast<int>(predvec.size()));
    EXPECT_NE(std::find(predvec[i1].begin(), predvec[i1].end(), 4),
              predvec[i1].end());
  }

  // Reachability includes the alt node and both branches’ endpoints.
  EXPECT_TRUE(reachable.contains(4));
  EXPECT_TRUE(reachable.contains(0));
  EXPECT_TRUE(reachable.contains(1));

  // Starts registered in rootmap.
  EXPECT_TRUE(rootmap.has_index(0));
  EXPECT_TRUE(rootmap.has_index(4));
  EXPECT_TRUE(rootmap.has_index(p.start()));
}
