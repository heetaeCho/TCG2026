// test_node_type_240.cpp
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/type.h"  // for YAML::NodeType::value and enumerators

namespace {

using YAML::NodeType;
using YAML::detail::node;

class NodeTypeTest_240 : public ::testing::Test {};

TEST_F(NodeTypeTest_240, DefaultConstructedTypeIsStableAcrossCalls_240) {
  node n;

  const NodeType::value t1 = n.type();
  const NodeType::value t2 = n.type();

  // Black-box: we don't assume what the default type is, only that repeated
  // calls are stable for an unmodified node.
  EXPECT_EQ(t1, t2);
}

TEST_F(NodeTypeTest_240, TypeReflectsSetTypeNull_240) {
  node n;

  n.set_type(NodeType::Null);
  EXPECT_EQ(n.type(), NodeType::Null);
}

TEST_F(NodeTypeTest_240, TypeReflectsSetTypeScalar_240) {
  node n;

  n.set_type(NodeType::Scalar);
  EXPECT_EQ(n.type(), NodeType::Scalar);
}

TEST_F(NodeTypeTest_240, TypeReflectsSetTypeSequence_240) {
  node n;

  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.type(), NodeType::Sequence);
}

TEST_F(NodeTypeTest_240, TypeReflectsSetTypeMap_240) {
  node n;

  n.set_type(NodeType::Map);
  EXPECT_EQ(n.type(), NodeType::Map);
}

TEST_F(NodeTypeTest_240, TypeUpdatesAfterMultipleSetTypeCalls_240) {
  node n;

  n.set_type(NodeType::Null);
  EXPECT_EQ(n.type(), NodeType::Null);

  n.set_type(NodeType::Scalar);
  EXPECT_EQ(n.type(), NodeType::Scalar);

  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.type(), NodeType::Sequence);

  n.set_type(NodeType::Map);
  EXPECT_EQ(n.type(), NodeType::Map);
}

TEST_F(NodeTypeTest_240, ConstNodeTypeCallableAndMatches_240) {
  node n;
  n.set_type(NodeType::Scalar);

  const node& cn = n;
  EXPECT_EQ(cn.type(), NodeType::Scalar);
}

TEST_F(NodeTypeTest_240, TypeIsPerInstanceNotAffectedByOtherNodes_240) {
  node a;
  node b;

  a.set_type(NodeType::Sequence);
  b.set_type(NodeType::Map);

  EXPECT_EQ(a.type(), NodeType::Sequence);
  EXPECT_EQ(b.type(), NodeType::Map);

  // Changing one should not change the other.
  a.set_type(NodeType::Null);
  EXPECT_EQ(a.type(), NodeType::Null);
  EXPECT_EQ(b.type(), NodeType::Map);
}

}  // namespace