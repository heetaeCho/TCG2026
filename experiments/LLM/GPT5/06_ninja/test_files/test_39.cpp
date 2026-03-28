// File: graph_node_dirty_test_39.cc

#include "graph.h"

#include "gtest/gtest.h"

// Fixture for testing Node::dirty and related public APIs.
class NodeDirtyTest_39 : public ::testing::Test {
protected:
  NodeDirtyTest_39() : node_("path/to/file", 0u) {}

  Node node_;
};

// Verify that a newly constructed Node reports not dirty by default.
TEST_F(NodeDirtyTest_39, DefaultDirtyStateIsFalse_39) {
  EXPECT_FALSE(node_.dirty());
}

// Verify that set_dirty(true) makes dirty() return true.
TEST_F(NodeDirtyTest_39, SetDirtyTrueSetsFlag_39) {
  EXPECT_FALSE(node_.dirty());

  node_.set_dirty(true);

  EXPECT_TRUE(node_.dirty());
}

// Verify that set_dirty(false) clears a previously set dirty flag.
TEST_F(NodeDirtyTest_39, SetDirtyFalseClearsFlag_39) {
  node_.set_dirty(true);
  ASSERT_TRUE(node_.dirty());

  node_.set_dirty(false);

  EXPECT_FALSE(node_.dirty());
}

// Verify that MarkDirty() causes dirty() to report true.
TEST_F(NodeDirtyTest_39, MarkDirtySetsFlag_39) {
  EXPECT_FALSE(node_.dirty());

  node_.MarkDirty();

  EXPECT_TRUE(node_.dirty());
}

// Verify that ResetState() clears the dirty flag after it has been set.
TEST_F(NodeDirtyTest_39, ResetStateClearsDirtyFlag_39) {
  node_.set_dirty(true);
  ASSERT_TRUE(node_.dirty());

  node_.ResetState();

  EXPECT_FALSE(node_.dirty());
}
