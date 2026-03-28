// File: test/node/node_ismap_test_194.cpp

#include <gtest/gtest.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/type.h>

namespace {

using YAML::Node;
using YAML::NodeType;

class NodeIsMapTest_194 : public ::testing::Test {};

TEST_F(NodeIsMapTest_194, MapNodeReportsIsMapTrue_194) {
  Node n(NodeType::Map);
  EXPECT_TRUE(n.IsMap());
}

TEST_F(NodeIsMapTest_194, NonMapNodesReportIsMapFalse_194) {
  EXPECT_FALSE(Node(NodeType::Null).IsMap());
  EXPECT_FALSE(Node(NodeType::Scalar).IsMap());
  EXPECT_FALSE(Node(NodeType::Sequence).IsMap());
#if defined(YAML_CPP_VERSION) || 1
  // NodeType::Undefined exists in yaml-cpp; include this check if available.
  EXPECT_FALSE(Node(NodeType::Undefined).IsMap());
#endif
}

TEST_F(NodeIsMapTest_194, CopyConstructionPreservesIsMap_194) {
  Node original(NodeType::Map);
  Node copy(original);
  EXPECT_TRUE(copy.IsMap());
}

TEST_F(NodeIsMapTest_194, CopyAssignmentPreservesIsMap_194) {
  Node map(NodeType::Map);
  Node other(NodeType::Scalar);

  other = map;
  EXPECT_TRUE(other.IsMap());
}

TEST_F(NodeIsMapTest_194, AssignmentUpdatesIsMapBasedOnNewType_194) {
  Node n(NodeType::Map);
  EXPECT_TRUE(n.IsMap());

  n = Node(NodeType::Sequence);
  EXPECT_FALSE(n.IsMap());

  n = Node(NodeType::Map);
  EXPECT_TRUE(n.IsMap());
}

}  // namespace