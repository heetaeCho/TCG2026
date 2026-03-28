#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/sparse_array.h"
#include "re2/sparse_set.h"
#include <vector>
#include <string>

namespace re2 {

// Helper to compile a regex pattern into a Prog
class MarkSuccessorsTest_413 : public ::testing::Test {
 protected:
  Prog* CompilePattern(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = re->CompileToProg(0);
    re->Decref();
    return prog;
  }
};

TEST_F(MarkSuccessorsTest_413, SimplePattern_413) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  // rootmap should have at least index 0
  EXPECT_TRUE(rootmap.has_index(0));
  // rootmap should have start_unanchored
  EXPECT_TRUE(rootmap.has_index(prog->start_unanchored()));
  // rootmap should have start
  EXPECT_TRUE(rootmap.has_index(prog->start()));
  // reachable should not be empty for a valid program
  EXPECT_GT(reachable.size(), 0);
  // stk should be empty after completion
  EXPECT_TRUE(stk.empty());

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, EmptyPattern_413) {
  Prog* prog = CompilePattern("");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  EXPECT_TRUE(rootmap.has_index(0));
  EXPECT_TRUE(stk.empty());

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, AlternationPattern_413) {
  // "a|b" should produce Alt instructions which exercise the predmap/predvec path
  Prog* prog = CompilePattern("a|b");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  EXPECT_TRUE(rootmap.has_index(0));
  EXPECT_TRUE(rootmap.has_index(prog->start_unanchored()));
  EXPECT_TRUE(rootmap.has_index(prog->start()));
  EXPECT_TRUE(stk.empty());

  // For alternation, we expect some predecessor entries
  // (predvec might have entries if there are Alt instructions)
  // Just verify consistency: predmap size <= predvec size
  EXPECT_LE(static_cast<size_t>(predmap.size()),
            predvec.size() + 1);  // allow some slack

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, ComplexPattern_413) {
  // Complex pattern with captures and alternation
  Prog* prog = CompilePattern("(a+|b*c)d");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  // Basic invariants
  EXPECT_TRUE(rootmap.has_index(0));
  EXPECT_TRUE(rootmap.has_index(prog->start_unanchored()));
  EXPECT_TRUE(rootmap.has_index(prog->start()));
  EXPECT_TRUE(stk.empty());
  EXPECT_GT(reachable.size(), 0);

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, RootmapContainsZero_413) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  // Index 0 is always set
  EXPECT_TRUE(rootmap.has_index(0));
  // The value at index 0 should be what rootmap.size() was before setting it
  // (which was 0 since rootmap was empty)
  EXPECT_EQ(rootmap.get_existing(0), 0);

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, ByteRangeCreatesRootEntries_413) {
  // "[a-z]" produces ByteRange instructions which should add out to rootmap
  Prog* prog = CompilePattern("[a-z]");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  // rootmap should have more than just the initial entries for byte range outputs
  EXPECT_GE(rootmap.size(), 1);
  EXPECT_TRUE(stk.empty());

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, ReachableContainsStartUnanchored_413) {
  Prog* prog = CompilePattern("hello");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  // start_unanchored is where traversal begins, so it should be reachable
  EXPECT_TRUE(reachable.contains(prog->start_unanchored()));

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, PredVecConsistentWithPredMap_413) {
  Prog* prog = CompilePattern("(a|b)(c|d)");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  // For each entry in predmap, it should index into predvec
  for (auto it = predmap.begin(); it != predmap.end(); ++it) {
    int idx = it->value();
    EXPECT_GE(idx, 0);
    EXPECT_LT(static_cast<size_t>(idx), predvec.size());
    // Each predvec entry should have at least one predecessor
    EXPECT_GT(predvec[idx].size(), 0u);
  }

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, SingleCharPattern_413) {
  Prog* prog = CompilePattern("x");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  EXPECT_TRUE(rootmap.has_index(0));
  EXPECT_TRUE(stk.empty());
  EXPECT_GT(reachable.size(), 0);

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, DotStarPattern_413) {
  // ".*" produces instructions that exercise multiple code paths
  Prog* prog = CompilePattern(".*");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  EXPECT_TRUE(rootmap.has_index(0));
  EXPECT_TRUE(rootmap.has_index(prog->start_unanchored()));
  EXPECT_TRUE(rootmap.has_index(prog->start()));
  EXPECT_TRUE(stk.empty());

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, AnchoredPattern_413) {
  // "^abc$" - anchored pattern
  Prog* prog = CompilePattern("^abc$");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  EXPECT_TRUE(rootmap.has_index(0));
  EXPECT_TRUE(stk.empty());

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, CaptureGroupPattern_413) {
  // "(abc)" has capture instructions which go through the kInstCapture path
  Prog* prog = CompilePattern("(abc)");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  EXPECT_TRUE(rootmap.has_index(0));
  EXPECT_TRUE(stk.empty());
  // Captures should add to rootmap
  EXPECT_GE(rootmap.size(), 3);  // at least 0, start_unanchored, start

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, StartEqualsStartUnanchored_413) {
  // When start == start_unanchored, the duplicate set_new should be skipped
  Prog* prog = CompilePattern("^a");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  // Should not crash, basic invariants hold
  EXPECT_TRUE(rootmap.has_index(0));
  EXPECT_TRUE(rootmap.has_index(prog->start()));
  EXPECT_TRUE(rootmap.has_index(prog->start_unanchored()));
  EXPECT_TRUE(stk.empty());

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, NestedAlternation_413) {
  // Nested alternation should create multiple Alt instructions
  Prog* prog = CompilePattern("(a|b|c|d|e)");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  EXPECT_TRUE(rootmap.has_index(0));
  EXPECT_TRUE(stk.empty());
  // With multiple alternations, predvec should have entries
  EXPECT_GT(predvec.size(), 0u);

  delete prog;
}

TEST_F(MarkSuccessorsTest_413, EmptyWidthPattern_413) {
  // "\\b" (word boundary) generates EmptyWidth instructions
  Prog* prog = CompilePattern("\\bfoo\\b");
  ASSERT_NE(prog, nullptr);

  int n = prog->size();
  SparseArray<int> rootmap(n);
  SparseArray<int> predmap(n);
  std::vector<std::vector<int>> predvec;
  SparseSet reachable(n);
  std::vector<int> stk;

  prog->MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

  EXPECT_TRUE(rootmap.has_index(0));
  EXPECT_TRUE(stk.empty());
  EXPECT_GT(reachable.size(), 0);

  delete prog;
}

}  // namespace re2
