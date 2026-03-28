// File: db/skiplist_node_nobarrier_next_test_92.cc
#include "db/skiplist.h"

#include <gtest/gtest.h>

namespace leveldb {

class SkipListNodeTest_92 : public ::testing::Test {
protected:
  // Helper to create a Node with a default-constructed Key.
  // We don't assume anything about Key other than it is default-constructible
  // and can be copied into Node via its constructor.
  SkipList::Node* MakeNode() {
    static_assert(std::is_default_constructible<Key>::value,
                  "Key must be default-constructible for this test.");
    key_storage_.emplace();                // default-construct Key
    node_storage_.emplace(*key_storage_);  // construct Node with Key
    return &(*node_storage_);
  }

  // Helper to create a second distinct Node.
  SkipList::Node* MakeAnotherNode() {
    other_key_storage_.emplace();
    other_node_storage_.emplace(*other_key_storage_);
    return &(*other_node_storage_);
  }

  // Use std::optional to control construction order/lifetimes deterministically
  std::optional<Key> key_storage_;
  std::optional<SkipList::Node> node_storage_;

  std::optional<Key> other_key_storage_;
  std::optional<SkipList::Node> other_node_storage_;
};

// Normal operation: pointer set by NoBarrier_SetNext is returned by NoBarrier_Next.
TEST_F(SkipListNodeTest_92, NoBarrierNext_ReturnsValueSetByNoBarrierSetNext_92) {
  SkipList::Node* a = MakeNode();
  SkipList::Node* b = MakeAnotherNode();

  a->NoBarrier_SetNext(0, b);
  EXPECT_EQ(b, a->NoBarrier_Next(0));
}

// Normal operation: pointer set by SetNext is observable via NoBarrier_Next.
TEST_F(SkipListNodeTest_92, NoBarrierNext_ObservesValueSetBySetNext_92) {
  SkipList::Node* a = MakeNode();
  SkipList::Node* b = MakeAnotherNode();

  a->SetNext(0, b);
  EXPECT_EQ(b, a->NoBarrier_Next(0));
}

// Boundary-ish case that does not assume internal layout: self-link at level 0.
TEST_F(SkipListNodeTest_92, NoBarrierNext_AllowsSelfPointerAtLevel0_92) {
  SkipList::Node* a = MakeNode();

  a->NoBarrier_SetNext(0, a);
  EXPECT_EQ(a, a->NoBarrier_Next(0));
}

// Error case: negative index should trigger the function's assertion.
// Guarded so it only runs when assertions are enabled and death tests are supported.
#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
TEST_F(SkipListNodeTest_92, NoBarrierNext_NegativeIndexTriggersAssert_92) {
  SkipList::Node* a = MakeNode();
  // Expect an assert failure (process death) when n < 0.
  EXPECT_DEATH({ (void)a->NoBarrier_Next(-1); }, "");
}
#endif  // !NDEBUG && GTEST_HAS_DEATH_TEST

}  // namespace leveldb
