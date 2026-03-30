// File: node_id_test_48.cc

#include <limits>
#include "gtest/gtest.h"

#include "graph.h"  // ./TestProjects/ninja/src/graph.h

// Test fixture for Node id()/set_id() behavior.
class NodeIdTest_48 : public ::testing::Test {
 protected:
  // Helper to create a simple Node.
  Node MakeNode(const std::string& path = "path", uint64_t slash_bits = 0) {
    return Node(path, slash_bits);
  }
};

// Verify that a freshly constructed Node has the expected default id.
TEST_F(NodeIdTest_48, DefaultIdIsMinusOne_48) {
  Node node = MakeNode("a", 0);
  EXPECT_EQ(-1, node.id());
}

// Verify that set_id updates the id, and id() returns the new value.
TEST_F(NodeIdTest_48, SetIdUpdatesId_48) {
  Node node = MakeNode("a", 0);

  node.set_id(42);

  EXPECT_EQ(42, node.id());
}

// Verify that calling set_id multiple times overwrites the previous value.
TEST_F(NodeIdTest_48, SetIdCanBeOverwritten_48) {
  Node node = MakeNode("a", 0);

  node.set_id(1);
  EXPECT_EQ(1, node.id());

  node.set_id(99);
  EXPECT_EQ(99, node.id());
}

// Verify that two different Node instances keep independent ids.
TEST_F(NodeIdTest_48, MultipleNodesMaintainIndependentIds_48) {
  Node node1 = MakeNode("n1", 0);
  Node node2 = MakeNode("n2", 0);

  node1.set_id(10);
  node2.set_id(20);

  EXPECT_EQ(10, node1.id());
  EXPECT_EQ(20, node2.id());
}

// Verify that set_id can handle boundary values of int.
TEST_F(NodeIdTest_48, SetIdHandlesBoundaryValues_48) {
  Node node_min = MakeNode("min", 0);
  Node node_max = MakeNode("max", 0);

  const int kMin = std::numeric_limits<int>::min();
  const int kMax = std::numeric_limits<int>::max();

  node_min.set_id(kMin);
  node_max.set_id(kMax);

  EXPECT_EQ(kMin, node_min.id());
  EXPECT_EQ(kMax, node_max.id());
}
