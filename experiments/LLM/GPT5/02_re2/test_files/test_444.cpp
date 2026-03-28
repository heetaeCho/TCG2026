// File: dfa_workq_mark_test.cc
#include <gtest/gtest.h>

// Assume these headers exist at the given relative paths in your project.
#include "re2/dfa.cc"          // for DFA::Workq declaration/definition used in tests
#include "re2/sparse_set.h"    // for SparseSet APIs used indirectly/observably

namespace re2 {

class WorkqMarkTest_444 : public ::testing::Test {
protected:
  // Helper to build a small Workq with known n/maxmark.
  // We choose small numbers to make expectations about "mark slots" (>= n) easy.
  // Note: We only rely on public API (constructor + inherited SparseSet methods).
  WorkqMarkTest_444() : n_(3), maxmark_(2), w_(n_, maxmark_) {}

  int n_;
  int maxmark_;
  DFA::Workq w_;
};

// [Behavior] On a brand-new Workq, calling mark() should be a no-op if the
// queue has not recorded any work yet (observable via size()).
TEST_F(WorkqMarkTest_444, InitialMarkIsNoOp_444) {
  // Initially empty.
  EXPECT_EQ(w_.size(), 0);

  // First mark() should not change observable size.
  w_.mark();
  EXPECT_EQ(w_.size(), 0);
}

// [Behavior] After inserting a "normal" work item, a subsequent mark() should
// enqueue exactly one additional entry (observable via size()). This does not
// assert internal details—only that a new element appears.
TEST_F(WorkqMarkTest_444, MarkAfterWorkAddsExactlyOne_444) {
  ASSERT_EQ(w_.size(), 0);

  // Insert a normal id in [0, n_). We use 0.
  w_.insert_new(0);
  ASSERT_EQ(w_.size(), 1);  // one observable item

  // Now call mark() and expect one more observable element.
  w_.mark();
  EXPECT_EQ(w_.size(), 2);
}

// [Boundary] If we interleave work and marks up to the configured capacity,
// size should never exceed n_ + maxmark_ (the documented Workq bound).
TEST_F(WorkqMarkTest_444, SizeNeverExceedsCapacity_444) {
  // Capacity bound exposed by constructor arguments (n_ + maxmark_).
  const int capacity = n_ + maxmark_;

  // Insert up to n_ normal items (ids in [0, n_))—observe growth up to n_.
  for (int i = 0; i < n_; ++i) {
    w_.insert(i);  // use public API; behavior is observable via size()
  }
  ASSERT_LE(w_.size(), capacity);

  // Try to add more "mark" entries than maxmark_ allows; size must cap at capacity.
  for (int i = 0; i < maxmark_ + 3; ++i) {
    w_.mark();
  }
  EXPECT_LE(w_.size(), capacity);
}

// [Idempotence-ish / No consecutive growth] Calling mark() repeatedly without
// adding any new work should not grow unboundedly. We verify that after
// an initial mark growth (if any), subsequent immediate mark() calls do not
// increase the size beyond capacity and (commonly) don't change size at all.
// (We only assert the safe, observable upper-bound property.)
TEST_F(WorkqMarkTest_444, RepeatedMarkWithoutWorkDoesNotGrowUnbounded_444) {
  // Start from an empty queue; first mark on a fresh queue is a no-op.
  w_.mark();
  const int before = w_.size();

  // Insert one work item, then mark once—size should increase by at most 1.
  w_.insert_new(1);
  const int after_insert = w_.size();
  w_.mark();
  const int after_one_mark = w_.size();
  ASSERT_GE(after_one_mark, after_insert);
  ASSERT_LE(after_one_mark, after_insert + 1);

  // Subsequent mark() calls without further work should not increase size
  // beyond capacity; also a practical check that it doesn't keep growing.
  const int capacity = n_ + maxmark_;
  for (int i = 0; i < 10; ++i) {
    w_.mark();
    EXPECT_LE(w_.size(), capacity);
  }
  // Ensure we didn't accidentally grow from the immediate prior size in a loop
  // (kept bounded). We don't assert exact equality to keep it black-box friendly.
  EXPECT_LE(w_.size(), capacity);

  // Sanity: initial no-op didn't change anything.
  EXPECT_EQ(before, 0);
}

}  // namespace re2
