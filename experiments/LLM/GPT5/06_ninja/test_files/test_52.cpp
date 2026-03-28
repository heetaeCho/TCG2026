// File: node_add_out_edge_test_52.cc

#include "graph.h"

#include <gtest/gtest.h>

// Fixture for Node::AddOutEdge tests.
// TEST_ID: 52
class NodeAddOutEdgeTest_52 : public ::testing::Test {
 protected:
  NodeAddOutEdgeTest_52()
      : node_("path/to/node", 0u) {}

  Node node_;
};

// Normal operation: adding a single out edge should increase the count
// and store the same pointer.
// TEST_ID: 52
TEST_F(NodeAddOutEdgeTest_52, AddSingleOutEdgeStoresPointer_52) {
  Edge edge;

  size_t before_size = node_.out_edges().size();
  node_.AddOutEdge(&edge);

  const std::vector<Edge*>& out_edges = node_.out_edges();
  ASSERT_EQ(before_size + 1, out_edges.size());
  EXPECT_EQ(&edge, out_edges.back());
}

// Normal operation: adding multiple out edges should preserve insertion order.
// TEST_ID: 52
TEST_F(NodeAddOutEdgeTest_52, AddMultipleOutEdgesMaintainsOrder_52) {
  Edge edge1;
  Edge edge2;
  Edge edge3;

  node_.AddOutEdge(&edge1);
  node_.AddOutEdge(&edge2);
  node_.AddOutEdge(&edge3);

  const std::vector<Edge*>& out_edges = node_.out_edges();
  ASSERT_EQ(3u, out_edges.size());
  EXPECT_EQ(&edge1, out_edges[0]);
  EXPECT_EQ(&edge2, out_edges[1]);
  EXPECT_EQ(&edge3, out_edges[2]);
}

// Boundary case: adding a nullptr as an out edge.
// This checks observable behavior when a null pointer is passed.
// TEST_ID: 52
TEST_F(NodeAddOutEdgeTest_52, AddNullOutEdgeIncreasesSizeAndStoresNull_52) {
  size_t before_size = node_.out_edges().size();

  node_.AddOutEdge(nullptr);

  const std::vector<Edge*>& out_edges = node_.out_edges();
  ASSERT_EQ(before_size + 1, out_edges.size());
  EXPECT_EQ(static_cast<Edge*>(nullptr), out_edges.back());
}

// Boundary / exceptional-like case: adding the same edge multiple times.
// We only verify observable behavior that duplicates are stored as given.
// TEST_ID: 52
TEST_F(NodeAddOutEdgeTest_52, AddDuplicateOutEdgesAllowedAndPreserved_52) {
  Edge edge;

  node_.AddOutEdge(&edge);
  node_.AddOutEdge(&edge);

  const std::vector<Edge*>& out_edges = node_.out_edges();
  ASSERT_GE(out_edges.size(), 2u);

  // Check that the last two entries are the same pointer.
  size_t n = out_edges.size();
  EXPECT_EQ(&edge, out_edges[n - 2]);
  EXPECT_EQ(&edge, out_edges[n - 1]);
}
