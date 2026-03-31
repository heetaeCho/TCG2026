#include "gtest/gtest.h"
#include "graph.h"
#include <string>
#include <vector>

// Minimal mock for DiskInterface if needed
#include "disk_interface.h"

class NodeResetStateTest_31 : public ::testing::Test {
protected:
  void SetUp() override {
    node_ = new Node("test/path", 0);
  }

  void TearDown() override {
    delete node_;
  }

  Node* node_;
};

// Test that ResetState sets mtime to -1
TEST_F(NodeResetStateTest_31, ResetStateSetsNegativeMtime_31) {
  // Dirty the node first to change its state
  node_->set_dirty(true);
  node_->ResetState();
  EXPECT_EQ(-1, node_->mtime());
}

// Test that ResetState clears dirty flag
TEST_F(NodeResetStateTest_31, ResetStateClearsDirtyFlag_31) {
  node_->set_dirty(true);
  EXPECT_TRUE(node_->dirty());
  node_->ResetState();
  EXPECT_FALSE(node_->dirty());
}

// Test that ResetState sets existence status to unknown
TEST_F(NodeResetStateTest_31, ResetStateSetsExistenceUnknown_31) {
  // Mark missing to change existence status
  node_->MarkMissing();
  EXPECT_TRUE(node_->status_known());
  node_->ResetState();
  EXPECT_FALSE(node_->status_known());
}

// Test that ResetState on a fresh node is idempotent
TEST_F(NodeResetStateTest_31, ResetStateOnFreshNodeIsIdempotent_31) {
  // Fresh node should already have default state
  node_->ResetState();
  EXPECT_EQ(-1, node_->mtime());
  EXPECT_FALSE(node_->dirty());
  EXPECT_FALSE(node_->status_known());
}

// Test that ResetState can be called multiple times
TEST_F(NodeResetStateTest_31, ResetStateMultipleCalls_31) {
  node_->set_dirty(true);
  node_->MarkMissing();
  node_->ResetState();
  node_->ResetState();
  node_->ResetState();
  EXPECT_EQ(-1, node_->mtime());
  EXPECT_FALSE(node_->dirty());
  EXPECT_FALSE(node_->status_known());
}

// Test that ResetState does not affect path
TEST_F(NodeResetStateTest_31, ResetStateDoesNotAffectPath_31) {
  node_->ResetState();
  EXPECT_EQ("test/path", node_->path());
}

// Test that ResetState does not affect slash_bits
TEST_F(NodeResetStateTest_31, ResetStateDoesNotAffectSlashBits_31) {
  Node node_with_bits("test\\path", 5);
  node_with_bits.ResetState();
  EXPECT_EQ(5u, node_with_bits.slash_bits());
}

// Test that ResetState does not affect in_edge
TEST_F(NodeResetStateTest_31, ResetStateDoesNotAffectInEdge_31) {
  node_->ResetState();
  EXPECT_EQ(nullptr, node_->in_edge());
}

// Test that ResetState does not affect out_edges
TEST_F(NodeResetStateTest_31, ResetStateDoesNotAffectOutEdges_31) {
  node_->ResetState();
  EXPECT_TRUE(node_->out_edges().empty());
}

// Test that ResetState does not affect id
TEST_F(NodeResetStateTest_31, ResetStateDoesNotAffectId_31) {
  node_->set_id(42);
  node_->ResetState();
  EXPECT_EQ(42, node_->id());
}

// Test that ResetState does not affect dyndep_pending
TEST_F(NodeResetStateTest_31, ResetStateDoesNotAffectDyndepPending_31) {
  node_->set_dyndep_pending(true);
  node_->ResetState();
  // ResetState only resets mtime_, exists_, dirty_. 
  // dyndep_pending should remain unchanged.
  EXPECT_TRUE(node_->dyndep_pending());
}

// Test that after MarkDirty then ResetState, dirty is cleared
TEST_F(NodeResetStateTest_31, ResetStateAfterMarkDirty_31) {
  node_->MarkDirty();
  EXPECT_TRUE(node_->dirty());
  node_->ResetState();
  EXPECT_FALSE(node_->dirty());
}

// Test that after MarkMissing then ResetState, exists returns correct state
TEST_F(NodeResetStateTest_31, ResetStateAfterMarkMissing_31) {
  node_->MarkMissing();
  EXPECT_FALSE(node_->exists());
  EXPECT_TRUE(node_->status_known());
  node_->ResetState();
  EXPECT_FALSE(node_->status_known());
}

// Test ResetState does not affect generated_by_dep_loader
TEST_F(NodeResetStateTest_31, ResetStateDoesNotAffectGeneratedByDepLoader_31) {
  node_->set_generated_by_dep_loader(false);
  node_->ResetState();
  EXPECT_FALSE(node_->generated_by_dep_loader());
}

// Test ResetState does not affect validation_out_edges
TEST_F(NodeResetStateTest_31, ResetStateDoesNotAffectValidationOutEdges_31) {
  node_->ResetState();
  EXPECT_TRUE(node_->validation_out_edges().empty());
}

// Test with empty path node
TEST_F(NodeResetStateTest_31, ResetStateWithEmptyPathNode_31) {
  Node empty_node("", 0);
  empty_node.set_dirty(true);
  empty_node.ResetState();
  EXPECT_EQ(-1, empty_node.mtime());
  EXPECT_FALSE(empty_node.dirty());
  EXPECT_FALSE(empty_node.status_known());
  EXPECT_EQ("", empty_node.path());
}
