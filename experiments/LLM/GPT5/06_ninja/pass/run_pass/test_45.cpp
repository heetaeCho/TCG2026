// File: ./TestProjects/ninja/src/graph_set_in_edge_test.cc

#include "graph.h"

#include <gtest/gtest.h>

class NodeSetInEdgeTest_45 : public ::testing::Test {
 protected:
  NodeSetInEdgeTest_45()
      : node_("out.o", /*slash_bits=*/0) {}

  Node node_;
  Edge edge1_;
  Edge edge2_;
};

// TEST_ID = 45
TEST_F(NodeSetInEdgeTest_45, DefaultInEdgeIsNull_45) {
  // Newly constructed Node should have no incoming edge.
  EXPECT_EQ(nullptr, node_.in_edge());
}

// TEST_ID = 45
TEST_F(NodeSetInEdgeTest_45, SetInEdgeStoresPointer_45) {
  node_.set_in_edge(&edge1_);

  // After setting, in_edge() should return the same pointer.
  EXPECT_EQ(&edge1_, node_.in_edge());
}

// TEST_ID = 45
TEST_F(NodeSetInEdgeTest_45, SetInEdgeCanBeUpdated_45) {
  node_.set_in_edge(&edge1_);
  EXPECT_EQ(&edge1_, node_.in_edge());

  // Setting again with a different edge should update the value.
  node_.set_in_edge(&edge2_);
  EXPECT_EQ(&edge2_, node_.in_edge());
}

// TEST_ID = 45
TEST_F(NodeSetInEdgeTest_45, SetInEdgeAcceptsNullToClear_45) {
  node_.set_in_edge(&edge1_);
  ASSERT_EQ(&edge1_, node_.in_edge());

  // Passing nullptr should be handled and clear the in_edge association.
  node_.set_in_edge(nullptr);
  EXPECT_EQ(nullptr, node_.in_edge());
}
