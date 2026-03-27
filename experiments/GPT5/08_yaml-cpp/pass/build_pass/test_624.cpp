// TEST_ID: 624
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::memory_holder;
using YAML::detail::node;

class MemoryHolderMergeTest_624 : public ::testing::Test {
 protected:
  static node& MakeNode(memory_holder& h) { return h.create_node(); }
};

TEST_F(MemoryHolderMergeTest_624, MergeEmptyIntoEmptyIsSafe_624) {
  memory_holder lhs;
  memory_holder rhs;

  EXPECT_NO_THROW(lhs.merge(rhs));

  // After merge both objects should remain usable via the public interface.
  EXPECT_NO_THROW((void)MakeNode(lhs));
  EXPECT_NO_THROW((void)MakeNode(rhs));
}

TEST_F(MemoryHolderMergeTest_624, MergeEmptyIntoNonEmptyIsSafe_624) {
  memory_holder lhs;
  memory_holder rhs;

  node* rhs_first = nullptr;
  ASSERT_NO_THROW(rhs_first = &MakeNode(rhs));

  EXPECT_NO_THROW(lhs.merge(rhs));

  // Both remain usable after merge.
  EXPECT_NO_THROW((void)MakeNode(lhs));
  EXPECT_NO_THROW((void)MakeNode(rhs));

  // The node reference obtained before merge should still be a valid reference
  // to some node object; we can at least compare that it still denotes an object.
  ASSERT_NE(rhs_first, nullptr);
}

TEST_F(MemoryHolderMergeTest_624, MergeNonEmptyIntoEmptyIsSafe_624) {
  memory_holder lhs;
  memory_holder rhs;

  node* lhs_first = nullptr;
  ASSERT_NO_THROW(lhs_first = &MakeNode(lhs));

  EXPECT_NO_THROW(lhs.merge(rhs));

  // Both remain usable after merge.
  EXPECT_NO_THROW((void)MakeNode(lhs));
  EXPECT_NO_THROW((void)MakeNode(rhs));

  ASSERT_NE(lhs_first, nullptr);
}

TEST_F(MemoryHolderMergeTest_624, MergeNonEmptyBothThenBothUsable_624) {
  memory_holder lhs;
  memory_holder rhs;

  node* lhs_n1 = nullptr;
  node* rhs_n1 = nullptr;
  ASSERT_NO_THROW(lhs_n1 = &MakeNode(lhs));
  ASSERT_NO_THROW(rhs_n1 = &MakeNode(rhs));
  ASSERT_NE(lhs_n1, nullptr);
  ASSERT_NE(rhs_n1, nullptr);

  EXPECT_NO_THROW(lhs.merge(rhs));

  // After merge, both holders should still be able to create nodes.
  node* lhs_after = nullptr;
  node* rhs_after = nullptr;
  EXPECT_NO_THROW(lhs_after = &MakeNode(lhs));
  EXPECT_NO_THROW(rhs_after = &MakeNode(rhs));

  // Sanity: newly created node references should refer to objects (and typically
  // be distinct references from the earlier ones).
  ASSERT_NE(lhs_after, nullptr);
  ASSERT_NE(rhs_after, nullptr);
}

TEST_F(MemoryHolderMergeTest_624, RepeatedMergeIsSafeAfterFirstMerge_624) {
  memory_holder lhs;
  memory_holder rhs;

  ASSERT_NO_THROW((void)MakeNode(lhs));
  ASSERT_NO_THROW((void)MakeNode(rhs));

  ASSERT_NO_THROW(lhs.merge(rhs));

  // Merging again should be safe/observable as non-failing.
  EXPECT_NO_THROW(lhs.merge(rhs));

  // Still usable.
  EXPECT_NO_THROW((void)MakeNode(lhs));
  EXPECT_NO_THROW((void)MakeNode(rhs));
}

TEST_F(MemoryHolderMergeTest_624, SelfMergeIsSafe_624) {
  memory_holder holder;

  ASSERT_NO_THROW((void)MakeNode(holder));

  // Self-merge should be safe (no crash/throw) and leave holder usable.
  EXPECT_NO_THROW(holder.merge(holder));
  EXPECT_NO_THROW((void)MakeNode(holder));
}

}  // namespace