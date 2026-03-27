// TEST_ID: 685
#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"

namespace {

class NodeImplTest_685 : public ::testing::Test {};

TEST_F(NodeImplTest_685, ConstructNullTypeReportsNullAndType_685) {
  YAML::Node n(YAML::NodeType::Null);

  EXPECT_TRUE(n.IsDefined());
  EXPECT_EQ(n.Type(), YAML::NodeType::Null);

  EXPECT_TRUE(n.IsNull());
  EXPECT_FALSE(n.IsScalar());
  EXPECT_FALSE(n.IsSequence());
  EXPECT_FALSE(n.IsMap());
  EXPECT_TRUE(static_cast<bool>(n));
  EXPECT_FALSE(!n);
}

TEST_F(NodeImplTest_685, ConstructScalarTypeReportsScalarAndType_685) {
  YAML::Node n(YAML::NodeType::Scalar);

  EXPECT_TRUE(n.IsDefined());
  EXPECT_EQ(n.Type(), YAML::NodeType::Scalar);

  EXPECT_FALSE(n.IsNull());
  EXPECT_TRUE(n.IsScalar());
  EXPECT_FALSE(n.IsSequence());
  EXPECT_FALSE(n.IsMap());
  EXPECT_TRUE(static_cast<bool>(n));
}

TEST_F(NodeImplTest_685, ConstructSequenceTypeReportsSequenceAndType_685) {
  YAML::Node n(YAML::NodeType::Sequence);

  EXPECT_TRUE(n.IsDefined());
  EXPECT_EQ(n.Type(), YAML::NodeType::Sequence);

  EXPECT_FALSE(n.IsNull());
  EXPECT_FALSE(n.IsScalar());
  EXPECT_TRUE(n.IsSequence());
  EXPECT_FALSE(n.IsMap());
  EXPECT_TRUE(static_cast<bool>(n));
}

TEST_F(NodeImplTest_685, ConstructMapTypeReportsMapAndType_685) {
  YAML::Node n(YAML::NodeType::Map);

  EXPECT_TRUE(n.IsDefined());
  EXPECT_EQ(n.Type(), YAML::NodeType::Map);

  EXPECT_FALSE(n.IsNull());
  EXPECT_FALSE(n.IsScalar());
  EXPECT_FALSE(n.IsSequence());
  EXPECT_TRUE(n.IsMap());
  EXPECT_TRUE(static_cast<bool>(n));
}

TEST_F(NodeImplTest_685, ConstructUndefinedTypeReportsUndefined_685) {
  // Boundary/error-like observable case: explicit Undefined construction.
  YAML::Node n(YAML::NodeType::Undefined);

  EXPECT_TRUE(n.IsDefined());                 // Construction should yield a defined Node handle
  EXPECT_EQ(n.Type(), YAML::NodeType::Undefined);

  // For Undefined, the specific IsNull/IsScalar/... semantics are implementation-defined;
  // only verify it does not claim to be a concrete container/scalar type.
  EXPECT_FALSE(n.IsNull());
  EXPECT_FALSE(n.IsScalar());
  EXPECT_FALSE(n.IsSequence());
  EXPECT_FALSE(n.IsMap());
  EXPECT_TRUE(static_cast<bool>(n));
}

TEST_F(NodeImplTest_685, ConstructDoesNotThrowForAllNodeTypes_685) {
  EXPECT_NO_THROW({ YAML::Node n0(YAML::NodeType::Null); });
  EXPECT_NO_THROW({ YAML::Node n1(YAML::NodeType::Scalar); });
  EXPECT_NO_THROW({ YAML::Node n2(YAML::NodeType::Sequence); });
  EXPECT_NO_THROW({ YAML::Node n3(YAML::NodeType::Map); });
  EXPECT_NO_THROW({ YAML::Node n4(YAML::NodeType::Undefined); });
}

TEST_F(NodeImplTest_685, CopyConstructionPreservesTypeAndKindQueries_685) {
  YAML::Node original(YAML::NodeType::Sequence);
  YAML::Node copy(original);

  EXPECT_TRUE(copy.IsDefined());
  EXPECT_EQ(copy.Type(), YAML::NodeType::Sequence);
  EXPECT_TRUE(copy.IsSequence());
  EXPECT_FALSE(copy.IsMap());
  EXPECT_FALSE(copy.IsScalar());
  EXPECT_FALSE(copy.IsNull());
}

TEST_F(NodeImplTest_685, AssignmentFromNodePreservesTypeAndKindQueries_685) {
  YAML::Node a(YAML::NodeType::Map);
  YAML::Node b(YAML::NodeType::Scalar);

  b = a;

  EXPECT_TRUE(b.IsDefined());
  EXPECT_EQ(b.Type(), YAML::NodeType::Map);
  EXPECT_TRUE(b.IsMap());
  EXPECT_FALSE(b.IsSequence());
  EXPECT_FALSE(b.IsScalar());
  EXPECT_FALSE(b.IsNull());
}

}  // namespace