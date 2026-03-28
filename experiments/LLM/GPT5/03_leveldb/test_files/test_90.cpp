// db/skiplist_node_next_test.cc
#include <gtest/gtest.h>
#include "db/skiplist.h"

namespace {

using leveldb::SkipList;

// If your build exposes Node publicly as shown in the prompt:
using Node = SkipList::Node;

// Helper to build small chain fragments without assuming initial state.
static void Link(Node& from, int n, Node* to) {
  // Prefer public setters; do not assume internal memory ordering details.
  from.SetNext(n, to);
}

TEST(SkipListNodeTest_90, NextReturnsPointerPreviouslySetWithSetNext_90) {
  Node a(/*key*/0);
  Node b(/*key*/1);

  Link(a, /*n=*/0, &b);
  EXPECT_EQ(&b, a.Next(/*n=*/0));
}

TEST(SkipListNodeTest_90, NextReflectsUpdatesAfterMultipleSetNextCalls_90) {
  Node a(0), b(1), c(2);

  Link(a, 0, &b);
  EXPECT_EQ(&b, a.Next(0));

  Link(a, 0, &c);
  EXPECT_EQ(&c, a.Next(0));

  // Setting to nullptr should be observable through Next.
  Link(a, 0, nullptr);
  EXPECT_EQ(nullptr, a.Next(0));
}

TEST(SkipListNodeTest_90, NextObservesPointerSetWithNoBarrierSetNext_90) {
  Node a(0), b(1);

  // Verify interoperability between setters and Next's read.
  a.NoBarrier_SetNext(/*n=*/0, &b);
  EXPECT_EQ(&b, a.Next(/*n=*/0));

  a.NoBarrier_SetNext(/*n=*/0, nullptr);
  EXPECT_EQ(nullptr, a.Next(/*n=*/0));
}

#if GTEST_HAS_DEATH_TEST
TEST(SkipListNodeTest_90, NextWithNegativeIndexTriggersAssertion_90) {
  Node a(0);
  // The interface asserts on n < 0; verify via death test.
  EXPECT_DEATH({ (void)a.Next(-1); }, ".*");
}
#endif

}  // namespace
