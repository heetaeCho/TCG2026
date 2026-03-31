#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/sparse_array.h"
#include "re2/sparse_set.h"
#include <vector>
#include <string>

namespace re2 {

class MarkDominatorTest_414 : public ::testing::Test {
 protected:
  // Helper to compile a regex into a Prog
  Prog* CompileRegex(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = re->CompileToProg(0);
    re->Decref();
    return prog;
  }
};

// Test that MarkDominator runs without crashing on a simple pattern
TEST_F(MarkDominatorTest_414, SimplePattern_414) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  // MarkDominator expects a valid root; use start()
  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  // After MarkDominator, reachable should contain at least the root
  EXPECT_TRUE(reachable.contains(prog->start()));

  delete prog;
}

// Test MarkDominator with an alternation pattern (creates kInstAlt)
TEST_F(MarkDominatorTest_414, AlternationPattern_414) {
  Prog* prog = CompileRegex("a|b");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  EXPECT_TRUE(reachable.contains(prog->start()));
  // Reachable should have multiple entries for alternation
  EXPECT_GT(reachable.size(), 0);

  delete prog;
}

// Test MarkDominator with a more complex pattern involving captures
TEST_F(MarkDominatorTest_414, CapturePattern_414) {
  Prog* prog = CompileRegex("(a)(b)");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  EXPECT_TRUE(reachable.contains(prog->start()));

  delete prog;
}

// Test MarkDominator with a pattern that includes repetition (more complex graph)
TEST_F(MarkDominatorTest_414, RepetitionPattern_414) {
  Prog* prog = CompileRegex("a*b+c?");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  EXPECT_TRUE(reachable.contains(prog->start()));

  delete prog;
}

// Test MarkDominator when predmap has entries that are reachable
TEST_F(MarkDominatorTest_414, WithPredecessorMap_414) {
  Prog* prog = CompileRegex("a|b|c");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  // Set up some predecessors: use instruction IDs that exist
  // Add a predmap entry for some node pointing to a predecessor
  // that is NOT in the reachable set to trigger rootmap addition
  if (n > 2) {
    predvec.push_back({n - 1});  // predecessor that likely won't be reachable from start
    predmap.set(1, 0);  // instruction 1 maps to predvec index 0
  }

  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  EXPECT_TRUE(reachable.contains(prog->start()));

  delete prog;
}

// Test MarkDominator clears reachable and stk before running
TEST_F(MarkDominatorTest_414, ClearsReachableAndStk_414) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  // Pre-populate reachable and stk
  if (n > 1) {
    reachable.insert(0);
  }
  stk.push_back(42);

  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  // stk should be empty after MarkDominator (it processes everything)
  EXPECT_TRUE(stk.empty());

  delete prog;
}

// Test MarkDominator where root is already in rootmap — should still be reachable
TEST_F(MarkDominatorTest_414, RootInRootMap_414) {
  Prog* prog = CompileRegex("a");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  // The root itself being in rootmap shouldn't affect its own reachability
  // (the code checks `if (id != root && rootmap->has_index(id))`)
  rootmap.set(prog->start(), 0);

  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  EXPECT_TRUE(reachable.contains(prog->start()));

  delete prog;
}

// Test MarkDominator with a character class pattern
TEST_F(MarkDominatorTest_414, CharClassPattern_414) {
  Prog* prog = CompileRegex("[a-z]+");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  EXPECT_TRUE(reachable.contains(prog->start()));
  EXPECT_GT(reachable.size(), 0);

  delete prog;
}

// Test MarkDominator with predmap entry whose predecessor IS reachable — rootmap should NOT get that entry
TEST_F(MarkDominatorTest_414, PredecessorReachable_414) {
  Prog* prog = CompileRegex("ab");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  // First run to find what's reachable
  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  // Collect reachable IDs
  std::vector<int> reachable_ids;
  for (SparseSet::const_iterator it = reachable.begin(); it != reachable.end(); ++it) {
    reachable_ids.push_back(*it);
  }

  // Now set up a predmap where the predecessor IS reachable
  SparseArray<int> rootmap2(n);
  SparseArray<int> predmap2(n);
  std::vector<std::vector<int>> predvec2;
  SparseSet reachable2(n);
  std::vector<int> stk2;

  if (reachable_ids.size() >= 2) {
    // Make reachable_ids[1] have a predecessor that IS reachable (reachable_ids[0])
    predvec2.push_back({reachable_ids[0]});
    predmap2.set(reachable_ids[1], 0);
  }

  prog->MarkDominator(prog->start(), &rootmap2, &predmap2, &predvec2,
                       &reachable2, &stk2);

  // If all predecessors are reachable, rootmap should not gain that entry
  // (unless there are other non-reachable predecessors)
  // This is a valid completion — we're just verifying no crash
  EXPECT_TRUE(reachable2.contains(prog->start()));

  delete prog;
}

// Test MarkDominator with empty-width assertions
TEST_F(MarkDominatorTest_414, EmptyWidthPattern_414) {
  Prog* prog = CompileRegex("^abc$");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  EXPECT_TRUE(reachable.contains(prog->start()));

  delete prog;
}

// Test that the full Flatten pipeline (which uses MarkDominator internally) works
TEST_F(MarkDominatorTest_414, FlattenIntegration_414) {
  Prog* prog = CompileRegex("(a|b)*c");
  ASSERT_NE(prog, nullptr);

  // Flatten internally calls MarkSuccessors, MarkDominator, EmitList, etc.
  prog->Flatten();

  // After flatten, the program should still be functional
  EXPECT_GE(prog->size(), 1);

  delete prog;
}

// Test with a nested alternation pattern
TEST_F(MarkDominatorTest_414, NestedAlternation_414) {
  Prog* prog = CompileRegex("(a|b)|(c|d)");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  EXPECT_TRUE(reachable.contains(prog->start()));
  // With nested alternations, there should be multiple reachable nodes
  EXPECT_GT(reachable.size(), 1);

  delete prog;
}

// Test calling MarkDominator twice on the same structures (idempotency of reachable)
TEST_F(MarkDominatorTest_414, CalledTwice_414) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  int first_reachable_size = reachable.size();

  // Call again - reachable and stk should be cleared internally
  prog->MarkDominator(prog->start(), &rootmap, &predmap, &predvec,
                       &reachable, &stk);

  EXPECT_EQ(reachable.size(), first_reachable_size);

  delete prog;
}

}  // namespace re2
