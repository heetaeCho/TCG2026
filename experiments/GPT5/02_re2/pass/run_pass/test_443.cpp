// File: workq_test_443.cc

#include <gtest/gtest.h>

#include "re2/dfa.cc"         // Provides re2::DFA::Workq (per prompt)
#include "re2/sparse_set.h"   // Provides SparseSet interface used by Workq

namespace re2 {

class WorkqTest_443 : public ::testing::Test {
protected:
  // Choose small, simple parameters to exercise boundaries.
  // n = number of "normal" ids ; maxmark = available marks capacity.
  static constexpr int kN = 8;
  static constexpr int kMaxMark = 3;

  DFA::Workq Make() { return DFA::Workq(kN, kMaxMark); }
};

// -----------------------------------------------------------------------------
// Construction & basic properties
// -----------------------------------------------------------------------------

TEST_F(WorkqTest_443, ConstructedIsEmpty_443) {
  DFA::Workq q = Make();
  EXPECT_EQ(q.size(), 0) << "Newly constructed Workq should be empty.";
}

TEST_F(WorkqTest_443, MaxmarkReflectsCtorArgument_443) {
  DFA::Workq q1(kN, kMaxMark);
  DFA::Workq q2(kN, kMaxMark + 5);
  EXPECT_EQ(q1.maxmark(), kMaxMark);
  EXPECT_EQ(q2.maxmark(), kMaxMark + 5);
}

// -----------------------------------------------------------------------------
// Insert & Contains behavior via public SparseSet interface
// -----------------------------------------------------------------------------

TEST_F(WorkqTest_443, InsertUniqueIdsIncreaseSizeAndAreContainable_443) {
  DFA::Workq q = Make();

  // Insert a couple of normal ids within [0, n).
  const int a = 0;
  const int b = kN - 1;

  EXPECT_FALSE(q.contains(a));
  EXPECT_FALSE(q.contains(b));

  q.insert(a);
  EXPECT_EQ(q.size(), 1);
  EXPECT_TRUE(q.contains(a));

  q.insert(b);
  EXPECT_EQ(q.size(), 2);
  EXPECT_TRUE(q.contains(b));
}

TEST_F(WorkqTest_443, InsertingDuplicatesDoesNotGrowUniqueCount_443) {
  DFA::Workq q = Make();
  const int id = 3;

  q.insert(id);
  ASSERT_EQ(q.size(), 1);
  ASSERT_TRUE(q.contains(id));

  // Re-insert same id via insert() should not add a new unique element.
  q.insert(id);
  EXPECT_EQ(q.size(), 1);
  EXPECT_TRUE(q.contains(id));
}

TEST_F(WorkqTest_443, InsertNewOnFreshIdAddsIt_443) {
  DFA::Workq q = Make();
  const int id = 5;

  EXPECT_FALSE(q.contains(id));
  q.insert_new(id);  // Behavior for duplicates is unspecified; only use fresh id.
  EXPECT_TRUE(q.contains(id));
  EXPECT_EQ(q.size(), 1);
}

// -----------------------------------------------------------------------------
// Clear behavior (observable through size()/contains())
// -----------------------------------------------------------------------------

TEST_F(WorkqTest_443, ClearEmptiesTheSetAndResetsMembership_443) {
  DFA::Workq q = Make();
  const int x = 1, y = 2, z = 3;

  q.insert(x);
  q.insert(y);
  q.insert(z);
  ASSERT_EQ(q.size(), 3);

  q.clear();
  EXPECT_EQ(q.size(), 0);
  EXPECT_FALSE(q.contains(x));
  EXPECT_FALSE(q.contains(y));
  EXPECT_FALSE(q.contains(z));

  // After clear, inserting again should work normally.
  q.insert(x);
  EXPECT_EQ(q.size(), 1);
  EXPECT_TRUE(q.contains(x));
}

// -----------------------------------------------------------------------------
// Mark / is_mark observable interactions without assuming internal encoding
// -----------------------------------------------------------------------------

TEST_F(WorkqTest_443, MarkAddsMarkElementsDetectableByIsMark_443) {
  DFA::Workq q = Make();

  // Before any mark(), there should be no elements for which is_mark(i) is true.
  // We can check among whatever the set currently holds (empty).
  int pre_mark_count = 0;
  for (auto it = q.begin(); it != q.end(); ++it) {
    pre_mark_count += q.is_mark(*it) ? 1 : 0;
  }
  EXPECT_EQ(pre_mark_count, 0);

  // Call mark() up to maxmark() times; after each call, at least one more
  // mark-identified element should be present among the elements.
  const int times = q.maxmark();
  int total_mark_detected = 0;

  for (int t = 0; t < times; ++t) {
    q.mark();

    // Count elements that the Workq itself identifies as "mark".
    int marked_now = 0;
    for (auto it = q.begin(); it != q.end(); ++it) {
      if (q.is_mark(*it)) {
        ++marked_now;
      }
    }
    // Expect non-decreasing number of mark-identified elements.
    EXPECT_GE(marked_now, total_mark_detected);
    total_mark_detected = marked_now;
  }

  // After exactly maxmark() times, we should have detected at least one mark.
  EXPECT_GE(total_mark_detected, 1);
}

TEST_F(WorkqTest_443, MarkDoesNotBreakInsertsOfNormalIds_443) {
  DFA::Workq q = Make();

  // Add some marks (within advertised capacity).
  for (int i = 0; i < q.maxmark(); ++i) {
    q.mark();
  }

  // Inserting normal ids should still succeed and be findable by contains().
  const int a = 2, b = 4;
  q.insert(a);
  q.insert(b);

  EXPECT_TRUE(q.contains(a));
  EXPECT_TRUE(q.contains(b));
  // And size should be at least the number of unique normal ids plus any mark-related entries.
  EXPECT_GE(q.size(), 2);
}

}  // namespace re2
