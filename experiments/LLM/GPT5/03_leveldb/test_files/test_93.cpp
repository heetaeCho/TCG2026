// db/skiplist_no_barrier_setnext_test.cc
#include "db/skiplist.h"
#include <gtest/gtest.h>

namespace leveldb {

class SkipListNodeTest_93 : public ::testing::Test {
protected:
  using Node = SkipList::Node;

  // NOTE: We assume Key is constructible from an integer-like literal in this codebase.
  // This helper centralizes construction without relying on any internal state.
  Node* MakeNode(int v) {
    // Construct a Key from an int; the Node exposes (const Key key) and a ctor Node(const Key&).
    return new Node(static_cast<typename std::remove_cv<
        typename std::remove_reference<decltype(std::declval<Node>().key)>::type>::type>(v));
  }

  void TearDown() override {
    // No global state to clean; each test deletes what it allocates.
  }
};

// Normal operation: setting a next pointer at level 0 can be read back with NoBarrier_Next.
TEST_F(SkipListNodeTest_93, NoBarrierSetNext_SetsPointerVisibleViaNoBarrierNext_93) {
  std::unique_ptr<SkipListNodeTest_93::Node> a(MakeNode(1));
  std::unique_ptr<SkipListNodeTest_93::Node> b(MakeNode(2));

  a->NoBarrier_SetNext(0, b.get());
  EXPECT_EQ(a->NoBarrier_Next(0), b.get());
}

// Boundary: setting the next pointer to nullptr at level 0 is observable as nullptr.
TEST_F(SkipListNodeTest_93, NoBarrierSetNext_AllowsNullPointer_93) {
  std::unique_ptr<SkipListNodeTest_93::Node> a(MakeNode(10));

  a->NoBarrier_SetNext(0, nullptr);
  EXPECT_EQ(a->NoBarrier_Next(0), nullptr);
}

// Boundary: self-link is allowed (observable via NoBarrier_Next returning self).
TEST_F(SkipListNodeTest_93, NoBarrierSetNext_AllowsSelfLink_93) {
  std::unique_ptr<SkipListNodeTest_93::Node> a(MakeNode(7));

  a->NoBarrier_SetNext(0, a.get());
  EXPECT_EQ(a->NoBarrier_Next(0), a.get());
}

// Exceptional / error case (observable via interface): negative index triggers assertion in debug builds.
// We use a death test guarded by NDEBUG so release builds (where assert may be compiled out) won't fail.
#ifndef NDEBUG
TEST_F(SkipListNodeTest_93, NoBarrierSetNext_NegativeIndexAsserts_93) {
  std::unique_ptr<SkipListNodeTest_93::Node> a(MakeNode(3));
  std::unique_ptr<SkipListNodeTest_93::Node> b(MakeNode(4));

  EXPECT_DEATH(a->NoBarrier_SetNext(-1, b.get()), "");
}
#endif

}  // namespace leveldb
