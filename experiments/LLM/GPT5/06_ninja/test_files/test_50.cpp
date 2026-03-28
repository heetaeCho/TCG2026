// File: node_out_edges_test_50.cc

#include <gtest/gtest.h>
#include "graph.h"

// If Edge is not fully defined in graph.h in this test context,
// provide a minimal definition so we can create Edge instances.
// (If Edge is already defined in your build, remove this.)
#ifndef NODE_OUT_EDGES_TEST_50_EDGE_DEFINED
#define NODE_OUT_EDGES_TEST_50_EDGE_DEFINED
struct Edge {};
#endif

class NodeOutEdgesTest_50 : public ::testing::Test {
protected:
  NodeOutEdgesTest_50()
      : node_("path/to/node", 0u) {}

  Node node_;
};

TEST_F(NodeOutEdgesTest_50, OutEdgesInitiallyEmpty_50) {
  const std::vector<Edge*>& out_edges = node_.out_edges();
  EXPECT_TRUE(out_edges.empty());
}

TEST_F(NodeOutEdgesTest_50, AddOutEdgeReflectsInOutEdgesAccessor_50) {
  Edge edge1;
  Edge edge2;

  node_.AddOutEdge(&edge1);
  node_.AddOutEdge(&edge2);

  const std::vector<Edge*>& out_edges = node_.out_edges();
  ASSERT_EQ(out_edges.size(), 2u);
  EXPECT_EQ(out_edges[0], &edge1);
  EXPECT_EQ(out_edges[1], &edge2);
}

TEST_F(NodeOutEdgesTest_50, MultipleCallsReturnSameUnderlyingContainer_50) {
  const std::vector<Edge*>& first = node_.out_edges();
  const std::vector<Edge*>& second = node_.out_edges();

  // Since the function returns "const std::vector<Edge*>&", we expect
  // both references to refer to the same underlying container.
  EXPECT_EQ(&first, &second);
}

TEST_F(NodeOutEdgesTest_50, AddOutEdgeDoesNotAffectValidationOutEdges_50) {
  Edge edge;
  node_.AddOutEdge(&edge);

  const std::vector<Edge*>& out_edges = node_.out_edges();
  const std::vector<Edge*>& validation_out_edges = node_.validation_out_edges();

  // Sanity check: out_edges has 1 element.
  ASSERT_EQ(out_edges.size(), 1u);
  EXPECT_EQ(out_edges[0], &edge);

  // Adding an out edge should not implicitly populate validation_out_edges.
  EXPECT_TRUE(validation_out_edges.empty());
}
