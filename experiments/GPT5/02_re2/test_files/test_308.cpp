// File: ./TestProjects/re2/re2/tests/compiler_addsuffix_test.cc

#include "gtest/gtest.h"
#include "re2/compile.h"   // Compiler, Frag
#include "re2/prog.h"      // Prog::Inst (type presence)
#include <cstdint>

using re2::Compiler;
using re2::Frag;

class CompilerTest_308 : public ::testing::Test {
protected:
  Compiler c_;
};

// [Normal] When the current suffix set is empty (begin == 0), AddSuffix
// should establish the first id as the root. This is observable via EndRange().
TEST_F(CompilerTest_308, AddSuffix_SetsBeginWhenEmpty_308) {
  c_.BeginRange();

  // First addition should become the begin id directly.
  c_.AddSuffix(123);

  Frag res = c_.EndRange();
  EXPECT_EQ(res.begin, 123) << "First suffix should initialize the range root.";
}

// [Normal] Adding a second suffix should produce a non-zero root that is not
// equal to either leaf id (i.e., an Alt node was created internally).
// We do NOT assume internal details; we only check observable facts:
//  - EndRange().begin becomes a non-zero program id distinct from the two ids
//  - FindByteRange(root, id) returns a non-empty fragment for each id added
TEST_F(CompilerTest_308, AddSuffix_BuildsAltOnSecondSuffix_308) {
  c_.BeginRange();

  const int id1 = 10;
  const int id2 = 20;

  c_.AddSuffix(id1);  // first: sets begin to id1
  c_.AddSuffix(id2);  // second: should combine using an Alt inst (internally)

  Frag res = c_.EndRange();

  // Root becomes some allocated instruction id (implementation-defined),
  // but should be non-zero and not either leaf id.
  EXPECT_NE(res.begin, 0u);
  EXPECT_NE(static_cast<int>(res.begin), id1);
  EXPECT_NE(static_cast<int>(res.begin), id2);

  // Observable behavior via the public search helper: both leaves should be
  // discoverable under the returned root.
  Frag f1 = c_.FindByteRange(res.begin, id1);
  Frag f2 = c_.FindByteRange(res.begin, id2);

  EXPECT_NE(f1.begin, 0u) << "id1 should be present in the constructed suffix tree.";
  EXPECT_NE(f2.begin, 0u) << "id2 should be present in the constructed suffix tree.";
}

// [Boundary] Adding multiple distinct suffix ids should keep the root valid
// and keep all previously-added leaves reachable. This extends the previous
// case without asserting internal structure.
TEST_F(CompilerTest_308, AddSuffix_MultipleIdsRemainReachable_308) {
  c_.BeginRange();

  const int ids[] = {3, 7, 11, 19};
  for (int id : ids) {
    c_.AddSuffix(id);
  }

  Frag res = c_.EndRange();
  EXPECT_NE(res.begin, 0u) << "Root must be valid after multiple additions.";

  for (int id : ids) {
    Frag f = c_.FindByteRange(res.begin, id);
    EXPECT_NE(f.begin, 0u) << "Expected id " << id << " to be reachable from the root.";
  }
}
