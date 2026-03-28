// File: ./TestProjects/ninja/tests/node_mark_missing_test_32.cc

#include "graph.h"

#include "gtest/gtest.h"

class NodeMarkMissingTest_32 : public ::testing::Test {
protected:
  NodeMarkMissingTest_32()
      : node_("out/foo.o", 0) {}

  Node node_;
};

// [Normal operation]
// Calling MarkMissing on a freshly constructed node should:
//  - mark the node as "status known"
//  - report that it does not exist
//  - give it a non-negative mtime (the implementation sets 0 from an unknown state)
TEST_F(NodeMarkMissingTest_32, MarkMissingOnFreshNodeSetsMissingAndKnown_32) {
  node_.MarkMissing();

  EXPECT_TRUE(node_.status_known());
  EXPECT_FALSE(node_.exists());
  EXPECT_GE(node_.mtime(), 0);
}

// [Boundary condition]
// If the node already has an explicit mtime set (e.g., via UpdatePhonyMtime),
// MarkMissing should not overwrite that mtime, but should still mark it missing.
TEST_F(NodeMarkMissingTest_32, MarkMissingDoesNotOverrideExistingMtime_32) {
  const TimeStamp kCustomMtime = 123;

  Node node_with_mtime("out/bar.o", 0);
  node_with_mtime.UpdatePhonyMtime(kCustomMtime);

  node_with_mtime.MarkMissing();

  EXPECT_TRUE(node_with_mtime.status_known());
  EXPECT_FALSE(node_with_mtime.exists());
  EXPECT_EQ(node_with_mtime.mtime(), kCustomMtime);
}

// [Idempotence / boundary]
// Calling MarkMissing multiple times should be safe (idempotent):
//  - the node remains missing
//  - the mtime remains stable after the first call.
TEST_F(NodeMarkMissingTest_32, MarkMissingIsIdempotent_32) {
  node_.MarkMissing();
  TimeStamp first_mtime = node_.mtime();

  node_.MarkMissing();

  EXPECT_TRUE(node_.status_known());
  EXPECT_FALSE(node_.exists());
  EXPECT_EQ(node_.mtime(), first_mtime);
}
