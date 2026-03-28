// File: prefilter_tree_dtor_test_571.cc

#include <gtest/gtest.h>
#include "re2/prefilter_tree.h"

namespace re2 {

// A tiny test double for Prefilter to observe destruction via a counter.
// We assume Prefilter is a polymorphic base in the codebase.
class TestPrefilter_571 : public Prefilter {
 public:
  static int live_count;

  TestPrefilter_571() { ++live_count; }
  ~TestPrefilter_571() override { --live_count; }

  // Implement the minimal interface surface if Prefilter has pure virtuals.
  // If Prefilter in your codebase has additional pure virtual methods,
  // provide trivial overrides here to satisfy the linker without
  // re-implementing any logic relevant to PrefilterTree.
  // (Leave empty if not required by your actual Prefilter definition.)
};

int TestPrefilter_571::live_count = 0;

// ---------- Tests ----------

TEST(PrefilterTreeDtorTest_571, DestroyEmptyTree_NoDeletes_571) {
  // Arrange
  int start = TestPrefilter_571::live_count;

  // Act: create and destroy an empty tree
  {
    PrefilterTree tree;
    // No additions; just ensure no deletes/crashes in ~PrefilterTree()
  }

  // Assert: nothing was deleted (counter unchanged)
  EXPECT_EQ(TestPrefilter_571::live_count, start);
}

TEST(PrefilterTreeDtorTest_571, DestroyTree_DeletesAllPrefilters_571) {
  // Arrange
  ASSERT_EQ(TestPrefilter_571::live_count, 0);
  TestPrefilter_571* p1 = new TestPrefilter_571();
  TestPrefilter_571* p2 = new TestPrefilter_571();
  TestPrefilter_571* p3 = new TestPrefilter_571();
  ASSERT_EQ(TestPrefilter_571::live_count, 3);

  // Act: add to tree, then destroy tree (scope exit)
  {
    PrefilterTree tree;
    tree.Add(p1);
    tree.Add(p2);
    tree.Add(p3);
    // When 'tree' is destroyed, it should delete the stored Prefilter*s.
  }

  // Assert: all added instances were deleted by ~PrefilterTree()
  EXPECT_EQ(TestPrefilter_571::live_count, 0);
}

TEST(PrefilterTreeDtorTest_571, OnlyAddedPointersAreDeleted_571) {
  // Arrange
  ASSERT_EQ(TestPrefilter_571::live_count, 0);
  TestPrefilter_571* added = new TestPrefilter_571();
  TestPrefilter_571* not_added = new TestPrefilter_571();
  ASSERT_EQ(TestPrefilter_571::live_count, 2);

  // Act: add only one to the tree and destroy the tree
  {
    PrefilterTree tree;
    tree.Add(added);
  }  // tree destroyed here, should delete 'added' only

  // Assert: one live (the not-added one), proving the tree does not
  // delete pointers it wasn’t given
  EXPECT_EQ(TestPrefilter_571::live_count, 1);

  // Cleanup: delete the one that was not added
  delete not_added;
  EXPECT_EQ(TestPrefilter_571::live_count, 0);
}

}  // namespace re2
