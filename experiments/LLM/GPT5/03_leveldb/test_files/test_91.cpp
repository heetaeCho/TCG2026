// File: db/skiplist_setnext_test.cc
#include "db/skiplist.h"
#include <gtest/gtest.h>

namespace {

using leveldb::SkipList;

// Test fixture kept minimal; we don't assume any internal details.
class SkipListNodeTest_91 : public ::testing::Test {
protected:
  // Convenience alias for readability.
  using Node = SkipList::Node;

  // Helper to create a node for a given key value.
  // We rely only on the public constructor signature exposed by the header.
  template <typename K>
  Node* MakeNode(const K& key) {
    return new Node(key);
  }

  // Clean up helper.
  static void Destroy(Node* n) { delete n; }
};

// --- Normal operation ---

TEST_F(SkipListNodeTest_91, SetNext_SetsPointerVisibleViaNext_91) {
  auto* a = MakeNode(1);
  auto* b = MakeNode(2);

  a->SetNext(0, b);
  EXPECT_EQ(a->Next(0), b);

  Destroy(a);
  Destroy(b);
}

TEST_F(SkipListNodeTest_91, SetNext_VisibleThroughNoBarrierNext_91) {
  auto* a = MakeNode(10);
  auto* b = MakeNode(20);

  a->SetNext(0, b);
  EXPECT_EQ(a->NoBarrier_Next(0), b);

  Destroy(a);
  Destroy(b);
}

// --- Boundary conditions ---

TEST_F(SkipListNodeTest_91, SetNext_AllowsNullptrAndClearsLink_91) {
  auto* a = MakeNode(100);

  // First set to a non-null to ensure we can observe a change.
  auto* b = MakeNode(200);
  a->SetNext(0, b);
  ASSERT_EQ(a->Next(0), b);

  // Now clear with nullptr and verify via both accessors.
  a->SetNext(0, nullptr);
  EXPECT_EQ(a->Next(0), nullptr);
  EXPECT_EQ(a->NoBarrier_Next(0), nullptr);

  Destroy(a);
  Destroy(b);
}

TEST_F(SkipListNodeTest_91, SetNext_OverwritesExistingLink_91) {
  auto* a = MakeNode(1);
  auto* b = MakeNode(2);
  auto* c = MakeNode(3);

  a->SetNext(0, b);
  ASSERT_EQ(a->Next(0), b);

  a->SetNext(0, c);
  EXPECT_EQ(a->Next(0), c);
  EXPECT_EQ(a->NoBarrier_Next(0), c);

  Destroy(a);
  Destroy(b);
  Destroy(c);
}

// --- Exceptional / error cases (observable via assert) ---

// This test verifies the interface contract that n must be >= 0.
// It uses death testing for debug builds where assert() is active.
TEST_F(SkipListNodeTest_91, SetNext_NegativeIndex_TriggersAssert_91) {
#ifndef NDEBUG
  auto* a = MakeNode(42);
  auto* b = MakeNode(43);

  // Set an environment for death test.
  // We don't assert specific message text; any death is acceptable.
  EXPECT_DEATH({ a->SetNext(-1, b); }, ".*");

  Destroy(a);
  Destroy(b);
#else
  GTEST_SKIP() << "Assertions are disabled in release builds (NDEBUG set).";
#endif
}

// --- Cross-verification with NoBarrier setter (still black-box) ---

TEST_F(SkipListNodeTest_91, NoBarrierSetNext_LinkVisibleViaNextAfterSetNext_91) {
  auto* a = MakeNode(7);
  auto* b = MakeNode(8);

  // Establish a known state with SetNext.
  a->SetNext(0, nullptr);
  ASSERT_EQ(a->Next(0), nullptr);

  // Change link using the no-barrier variant, then confirm visibility through Next().
  a->NoBarrier_SetNext(0, b);
  EXPECT_EQ(a->Next(0), b);

  Destroy(a);
  Destroy(b);
}

} // namespace
