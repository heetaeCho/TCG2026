#include "gtest/gtest.h"
#include "graph.h"

// Test fixture for Node tests
class NodeTest_53 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test AddValidationOutEdge adds an edge to validation_out_edges
TEST_F(NodeTest_53, AddValidationOutEdge_AddsEdgeToList_53) {
  Node node("test_path", 0);
  Edge edge1;
  Edge edge2;

  EXPECT_EQ(node.validation_out_edges().size(), 0u);

  node.AddValidationOutEdge(&edge1);
  EXPECT_EQ(node.validation_out_edges().size(), 1u);
  EXPECT_EQ(node.validation_out_edges()[0], &edge1);

  node.AddValidationOutEdge(&edge2);
  EXPECT_EQ(node.validation_out_edges().size(), 2u);
  EXPECT_EQ(node.validation_out_edges()[0], &edge1);
  EXPECT_EQ(node.validation_out_edges()[1], &edge2);
}

// Test that validation_out_edges starts empty
TEST_F(NodeTest_53, ValidationOutEdges_InitiallyEmpty_53) {
  Node node("empty_node", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

// Test adding the same edge multiple times
TEST_F(NodeTest_53, AddValidationOutEdge_DuplicateEdges_53) {
  Node node("dup_node", 0);
  Edge edge;

  node.AddValidationOutEdge(&edge);
  node.AddValidationOutEdge(&edge);

  EXPECT_EQ(node.validation_out_edges().size(), 2u);
  EXPECT_EQ(node.validation_out_edges()[0], &edge);
  EXPECT_EQ(node.validation_out_edges()[1], &edge);
}

// Test adding many validation out edges
TEST_F(NodeTest_53, AddValidationOutEdge_ManyEdges_53) {
  Node node("many_edges_node", 0);
  const int kNumEdges = 100;
  std::vector<Edge> edges(kNumEdges);

  for (int i = 0; i < kNumEdges; ++i) {
    node.AddValidationOutEdge(&edges[i]);
  }

  EXPECT_EQ(node.validation_out_edges().size(), static_cast<size_t>(kNumEdges));
  for (int i = 0; i < kNumEdges; ++i) {
    EXPECT_EQ(node.validation_out_edges()[i], &edges[i]);
  }
}

// Test AddOutEdge and AddValidationOutEdge are independent
TEST_F(NodeTest_53, AddValidationOutEdge_IndependentFromOutEdges_53) {
  Node node("independent_node", 0);
  Edge out_edge;
  Edge validation_edge;

  node.AddOutEdge(&out_edge);
  node.AddValidationOutEdge(&validation_edge);

  EXPECT_EQ(node.out_edges().size(), 1u);
  EXPECT_EQ(node.out_edges()[0], &out_edge);

  EXPECT_EQ(node.validation_out_edges().size(), 1u);
  EXPECT_EQ(node.validation_out_edges()[0], &validation_edge);
}

// Test basic Node constructor and accessors
TEST_F(NodeTest_53, Constructor_PathAndSlashBits_53) {
  Node node("foo/bar", 4);
  EXPECT_EQ(node.path(), "foo/bar");
  EXPECT_EQ(node.slash_bits(), 4u);
}

// Test set_dirty and dirty
TEST_F(NodeTest_53, SetDirty_53) {
  Node node("dirty_node", 0);
  EXPECT_FALSE(node.dirty());
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

// Test MarkDirty
TEST_F(NodeTest_53, MarkDirty_53) {
  Node node("mark_dirty_node", 0);
  EXPECT_FALSE(node.dirty());
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

// Test set_id and id
TEST_F(NodeTest_53, SetId_53) {
  Node node("id_node", 0);
  EXPECT_EQ(node.id(), -1);
  node.set_id(42);
  EXPECT_EQ(node.id(), 42);
}

// Test in_edge and set_in_edge
TEST_F(NodeTest_53, SetInEdge_53) {
  Node node("in_edge_node", 0);
  EXPECT_EQ(node.in_edge(), nullptr);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(node.in_edge(), &edge);
}

// Test dyndep_pending and set_dyndep_pending
TEST_F(NodeTest_53, SetDyndepPending_53) {
  Node node("dyndep_node", 0);
  EXPECT_FALSE(node.dyndep_pending());
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

// Test generated_by_dep_loader and set_generated_by_dep_loader
TEST_F(NodeTest_53, SetGeneratedByDepLoader_53) {
  Node node("dep_loader_node", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test MarkMissing
TEST_F(NodeTest_53, MarkMissing_53) {
  Node node("missing_node", 0);
  node.MarkMissing();
  EXPECT_FALSE(node.exists());
  EXPECT_TRUE(node.status_known());
}

// Test ResetState clears dirty and mtime
TEST_F(NodeTest_53, ResetState_53) {
  Node node("reset_node", 0);
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
  node.ResetState();
  EXPECT_FALSE(node.dirty());
  EXPECT_EQ(node.mtime(), -1);
}

// Test AddOutEdge
TEST_F(NodeTest_53, AddOutEdge_53) {
  Node node("out_edge_node", 0);
  EXPECT_TRUE(node.out_edges().empty());
  Edge edge;
  node.AddOutEdge(&edge);
  EXPECT_EQ(node.out_edges().size(), 1u);
  EXPECT_EQ(node.out_edges()[0], &edge);
}

// Test that validation_out_edges preserves insertion order
TEST_F(NodeTest_53, AddValidationOutEdge_PreservesOrder_53) {
  Node node("order_node", 0);
  Edge edge1, edge2, edge3;

  node.AddValidationOutEdge(&edge1);
  node.AddValidationOutEdge(&edge2);
  node.AddValidationOutEdge(&edge3);

  ASSERT_EQ(node.validation_out_edges().size(), 3u);
  EXPECT_EQ(node.validation_out_edges()[0], &edge1);
  EXPECT_EQ(node.validation_out_edges()[1], &edge2);
  EXPECT_EQ(node.validation_out_edges()[2], &edge3);
}
