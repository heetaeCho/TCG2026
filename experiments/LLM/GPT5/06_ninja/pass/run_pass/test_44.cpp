// File: graph_in_edge_test.cc

#include "graph.h"
#include "gtest/gtest.h"

class NodeInEdgeTest_44 : public ::testing::Test {
protected:
  NodeInEdgeTest_44() : node_("test/path", 0) {}

  Node node_;
};

// Verify that a newly constructed Node has no incoming edge.
TEST_F(NodeInEdgeTest_44, DefaultInEdgeIsNull_44) {
  EXPECT_EQ(nullptr, node_.in_edge());
}

// Verify that set_in_edge stores the provided pointer and in_edge() returns it.
TEST_F(NodeInEdgeTest_44, SetInEdgeStoresPointer_44) {
  Edge* edge_ptr = reinterpret_cast<Edge*>(0x1);

  node_.set_in_edge(edge_ptr);

  EXPECT_EQ(edge_ptr, node_.in_edge());
}

// Verify that calling set_in_edge multiple times updates the stored pointer.
TEST_F(NodeInEdgeTest_44, SetInEdgeCanBeUpdated_44) {
  Edge* edge_ptr1 = reinterpret_cast<Edge*>(0x1);
  Edge* edge_ptr2 = reinterpret_cast<Edge*>(0x2);

  node_.set_in_edge(edge_ptr1);
  EXPECT_EQ(edge_ptr1, node_.in_edge());

  node_.set_in_edge(edge_ptr2);
  EXPECT_EQ(edge_ptr2, node_.in_edge());
}

// Verify that set_in_edge accepts a nullptr and in_edge() reflects that.
TEST_F(NodeInEdgeTest_44, SetInEdgeAcceptsNullPointer_44) {
  Edge* edge_ptr = reinterpret_cast<Edge*>(0x1);

  // First set a non-null pointer.
  node_.set_in_edge(edge_ptr);
  ASSERT_EQ(edge_ptr, node_.in_edge());

  // Then reset to nullptr and verify.
  node_.set_in_edge(nullptr);
  EXPECT_EQ(nullptr, node_.in_edge());
}
