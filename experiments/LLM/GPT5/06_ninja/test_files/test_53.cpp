// File: node_add_validation_out_edge_test_53.cc

#include "graph.h"

#include <gtest/gtest.h>

class NodeAddValidationOutEdgeTest_53 : public ::testing::Test {
protected:
  NodeAddValidationOutEdgeTest_53()
      : node_("test/path", 0u) {}  // slash_bits can be any valid value

  Node node_;
};

TEST_F(NodeAddValidationOutEdgeTest_53, InitiallyNoValidationOutEdges_53) {
  // A freshly constructed Node should have no validation out edges.
  const std::vector<Edge*>& edges = node_.validation_out_edges();
  EXPECT_TRUE(edges.empty());
}

TEST_F(NodeAddValidationOutEdgeTest_53, SingleEdgeAdded_53) {
  Edge edge;

  node_.AddValidationOutEdge(&edge);

  const std::vector<Edge*>& edges = node_.validation_out_edges();
  ASSERT_EQ(edges.size(), 1u);
  EXPECT_EQ(edges[0], &edge);
}

TEST_F(NodeAddValidationOutEdgeTest_53, MultipleEdgesPreserveOrder_53) {
  Edge edge1;
  Edge edge2;
  Edge edge3;

  node_.AddValidationOutEdge(&edge1);
  node_.AddValidationOutEdge(&edge2);
  node_.AddValidationOutEdge(&edge3);

  const std::vector<Edge*>& edges = node_.validation_out_edges();
  ASSERT_EQ(edges.size(), 3u);
  EXPECT_EQ(edges[0], &edge1);
  EXPECT_EQ(edges[1], &edge2);
  EXPECT_EQ(edges[2], &edge3);
}

TEST_F(NodeAddValidationOutEdgeTest_53, DuplicateEdgesAllowed_53) {
  Edge edge;

  node_.AddValidationOutEdge(&edge);
  node_.AddValidationOutEdge(&edge);

  const std::vector<Edge*>& edges = node_.validation_out_edges();
  ASSERT_EQ(edges.size(), 2u);
  EXPECT_EQ(edges[0], &edge);
  EXPECT_EQ(edges[1], &edge);
}

TEST_F(NodeAddValidationOutEdgeTest_53, NullptrEdgeHandled_53) {
  // Even if a nullptr is passed, the public interface should remain consistent:
  // the container should reflect the added entry.
  node_.AddValidationOutEdge(nullptr);

  const std::vector<Edge*>& edges = node_.validation_out_edges();
  ASSERT_EQ(edges.size(), 1u);
  EXPECT_EQ(edges[0], nullptr);
}
