// File: tests/dfa_workq_insert_446_test.cc
#include <gtest/gtest.h>

#include "re2/dfa.h"      // Assuming Workq is declared here as shown in the prompt
// If Workq is only reachable via dfa.cc, include the proper public header that
// exposes re2::DFA::Workq. Do NOT include .cc files directly in real builds.

namespace re2 {

class WorkqInsertTest_446 : public ::testing::Test {
protected:
  // Choose a small, valid construction domain.
  // We do not depend on or assert any internal mapping semantics.
  const int kN = 10;
  const int kMaxMark = 5;

  // Helper to create a fresh queue for each test.
  DFA::Workq Make() { return DFA::Workq(kN, kMaxMark); }
};

// [Normal] Inserting a previously-absent id should increase size by 1 and make it present.
TEST_F(WorkqInsertTest_446, InsertNewId_IncreasesSizeAndContains_446) {
  auto q = Make();
  EXPECT_EQ(0, q.size());

  const int id = 0; // pick a simple in-range id
  q.insert(id);

  EXPECT_EQ(1, q.size());
  EXPECT_TRUE(q.contains(id));
}

// [Idempotence] Inserting the same id twice should not increase size the second time.
TEST_F(WorkqInsertTest_446, InsertSameIdTwice_DoesNotIncreaseSize_446) {
  auto q = Make();
  const int id = 3;

  q.insert(id);
  ASSERT_EQ(1, q.size());
  ASSERT_TRUE(q.contains(id));

  q.insert(id);  // insert duplicate
  EXPECT_EQ(1, q.size());       // size unchanged
  EXPECT_TRUE(q.contains(id));  // still present
}

// [Multiple distinct ids] Inserting two different absent ids should grow size to 2,
// and both should be reported as contained.
TEST_F(WorkqInsertTest_446, InsertTwoDistinctIds_BothContained_SizeIsTwo_446) {
  auto q = Make();
  const int a = 1;
  const int b = 4;

  q.insert(a);
  q.insert(b);

  EXPECT_EQ(2, q.size());
  EXPECT_TRUE(q.contains(a));
  EXPECT_TRUE(q.contains(b));
}

// [Boundary-ish in-range values] Insert lowest typical id (0) and a high in-range id.
// We avoid asserting any marking semantics; only observable size/contains are checked.
TEST_F(WorkqInsertTest_446, InsertLowAndHighInRangeIds_ContainmentAndSize_446) {
  auto q = Make();

  const int low = 0;
  const int high = kN + kMaxMark - 1; // stays within the constructed capacity range

  q.insert(low);
  q.insert(high);

  EXPECT_EQ(2, q.size());
  EXPECT_TRUE(q.contains(low));
  EXPECT_TRUE(q.contains(high));
}

// [Clear behavior] After clear(), size should be 0 and re-insertion should behave as fresh.
TEST_F(WorkqInsertTest_446, ClearThenReinsert_BehavesLikeFresh_446) {
  auto q = Make();
  const int id = 2;

  q.insert(id);
  ASSERT_EQ(1, q.size());
  ASSERT_TRUE(q.contains(id));

  q.clear();
  EXPECT_EQ(0, q.size());
  EXPECT_FALSE(q.contains(id));

  q.insert(id);
  EXPECT_EQ(1, q.size());
  EXPECT_TRUE(q.contains(id));
}

}  // namespace re2
