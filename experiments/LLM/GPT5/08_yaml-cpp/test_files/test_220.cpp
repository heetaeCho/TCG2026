// TEST_ID: 220
#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node_ref.h>

namespace {

class NodeRefSetTypeTest_220 : public ::testing::Test {
 protected:
  YAML::detail::node_ref ref_;
};

TEST_F(NodeRefSetTypeTest_220, SetTypeUpdatesObservableType_220) {
  ref_.set_type(YAML::NodeType::Scalar);
  EXPECT_EQ(ref_.type(), YAML::NodeType::Scalar);
}

TEST_F(NodeRefSetTypeTest_220, SetTypeCanBeOverwritten_220) {
  ref_.set_type(YAML::NodeType::Sequence);
  EXPECT_EQ(ref_.type(), YAML::NodeType::Sequence);

  ref_.set_type(YAML::NodeType::Map);
  EXPECT_EQ(ref_.type(), YAML::NodeType::Map);
}

TEST_F(NodeRefSetTypeTest_220, SetTypeAcceptsNull_220) {
  ref_.set_type(YAML::NodeType::Null);
  EXPECT_EQ(ref_.type(), YAML::NodeType::Null);
}

TEST_F(NodeRefSetTypeTest_220, SetTypeIsIdempotentForSameValue_220) {
  ref_.set_type(YAML::NodeType::Scalar);
  EXPECT_EQ(ref_.type(), YAML::NodeType::Scalar);

  // Re-applying the same value should keep the observable type unchanged.
  ref_.set_type(YAML::NodeType::Scalar);
  EXPECT_EQ(ref_.type(), YAML::NodeType::Scalar);
}

}  // namespace