// File: test/node/detail/node_ref_type_test_213.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

namespace {

class NodeRefTypeTest_213 : public ::testing::Test {};

TEST_F(NodeRefTypeTest_213, DefaultConstructedTypeIsNull_213) {
  const YAML::detail::node_ref ref;
  EXPECT_EQ(ref.type(), YAML::NodeType::Null);
}

TEST_F(NodeRefTypeTest_213, SetTypeUpdatesType_213) {
  YAML::detail::node_ref ref;

  ref.set_type(YAML::NodeType::Scalar);
  EXPECT_EQ(ref.type(), YAML::NodeType::Scalar);

  ref.set_type(YAML::NodeType::Sequence);
  EXPECT_EQ(ref.type(), YAML::NodeType::Sequence);

  ref.set_type(YAML::NodeType::Map);
  EXPECT_EQ(ref.type(), YAML::NodeType::Map);

  // Also verify it can be set back.
  ref.set_type(YAML::NodeType::Null);
  EXPECT_EQ(ref.type(), YAML::NodeType::Null);
}

TEST_F(NodeRefTypeTest_213, TypeIsConstCallableAndStableAcrossCalls_213) {
  YAML::detail::node_ref ref;
  ref.set_type(YAML::NodeType::Scalar);

  const YAML::detail::node_ref& cref = ref;
  const auto t1 = cref.type();
  const auto t2 = cref.type();
  EXPECT_EQ(t1, t2);
  EXPECT_EQ(t1, YAML::NodeType::Scalar);
}

TEST_F(NodeRefTypeTest_213, SetTypeAcceptsAllCommonNodeTypeValues_213) {
  YAML::detail::node_ref ref;

  // Boundary-style coverage: exercise all commonly available enum values.
  ref.set_type(YAML::NodeType::Null);
  EXPECT_EQ(ref.type(), YAML::NodeType::Null);

  ref.set_type(YAML::NodeType::Scalar);
  EXPECT_EQ(ref.type(), YAML::NodeType::Scalar);

  ref.set_type(YAML::NodeType::Sequence);
  EXPECT_EQ(ref.type(), YAML::NodeType::Sequence);

  ref.set_type(YAML::NodeType::Map);
  EXPECT_EQ(ref.type(), YAML::NodeType::Map);
}

}  // namespace