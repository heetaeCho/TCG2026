// TEST_ID: 249
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/type.h"  // for YAML::NodeType

namespace YAML {
namespace detail {

class NodeSetTypeTest_249 : public ::testing::Test {
 protected:
  node n;
};

TEST_F(NodeSetTypeTest_249, SetTypeUpdatesType_249) {
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(n.type(), NodeType::Scalar);

  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.type(), NodeType::Sequence);

  n.set_type(NodeType::Map);
  EXPECT_EQ(n.type(), NodeType::Map);
}

TEST_F(NodeSetTypeTest_249, SetTypeNonUndefinedMarksDefined_249) {
  // Observable behavior: calling set_type with a non-Undefined value should
  // result in the node being defined.
  n.set_type(NodeType::Null);
  EXPECT_TRUE(n.is_defined());

  n.set_type(NodeType::Scalar);
  EXPECT_TRUE(n.is_defined());
}

TEST_F(NodeSetTypeTest_249, SetTypeUndefinedDoesNotChangeDefinedState_249) {
  // Do not assume the initial defined state; verify it is unchanged.
  const bool was_defined = n.is_defined();

  n.set_type(NodeType::Undefined);

  EXPECT_EQ(n.type(), NodeType::Undefined);
  EXPECT_EQ(n.is_defined(), was_defined);
}

TEST_F(NodeSetTypeTest_249, SetTypeUndefinedAfterNonUndefinedKeepsDefined_249) {
  // After setting to a non-Undefined type, node should be defined.
  n.set_type(NodeType::Scalar);
  ASSERT_TRUE(n.is_defined());

  // Setting to Undefined should not "undefine" the node (observable state).
  n.set_type(NodeType::Undefined);

  EXPECT_EQ(n.type(), NodeType::Undefined);
  EXPECT_TRUE(n.is_defined());
}

}  // namespace detail
}  // namespace YAML