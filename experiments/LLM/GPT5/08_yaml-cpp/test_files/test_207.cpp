// TEST_ID: 207
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"

namespace {

class NodeDataTypeTest_207 : public ::testing::Test {
 protected:
  YAML::detail::node_data data_;
};

TEST_F(NodeDataTypeTest_207, DefaultConstructedIsUndefined_207) {
  EXPECT_EQ(data_.type(), YAML::NodeType::Undefined);
}

TEST_F(NodeDataTypeTest_207, SetTypeWithoutMarkDefinedStillUndefined_207) {
  data_.set_type(YAML::NodeType::Scalar);
  EXPECT_EQ(data_.type(), YAML::NodeType::Undefined);
}

TEST_F(NodeDataTypeTest_207, MarkDefinedWithDefaultTypeExposesNonUndefinedType_207) {
  data_.mark_defined();
  // Observable contract from the provided implementation: once defined, type()
  // returns the stored node type (not NodeType::Undefined).
  EXPECT_NE(data_.type(), YAML::NodeType::Undefined);
}

TEST_F(NodeDataTypeTest_207, MarkDefinedThenSetTypeReflectsNewType_207) {
  data_.mark_defined();
  data_.set_type(YAML::NodeType::Map);
  EXPECT_EQ(data_.type(), YAML::NodeType::Map);
}

TEST_F(NodeDataTypeTest_207, SetTypeThenMarkDefinedReflectsType_207) {
  data_.set_type(YAML::NodeType::Sequence);
  data_.mark_defined();
  EXPECT_EQ(data_.type(), YAML::NodeType::Sequence);
}

TEST_F(NodeDataTypeTest_207, MultipleSetTypeUpdatesObservedTypeWhenDefined_207) {
  data_.mark_defined();

  data_.set_type(YAML::NodeType::Scalar);
  EXPECT_EQ(data_.type(), YAML::NodeType::Scalar);

  data_.set_type(YAML::NodeType::Null);
  EXPECT_EQ(data_.type(), YAML::NodeType::Null);

  data_.set_type(YAML::NodeType::Sequence);
  EXPECT_EQ(data_.type(), YAML::NodeType::Sequence);
}

TEST_F(NodeDataTypeTest_207, MarkDefinedIsIdempotentForTypeObservation_207) {
  data_.set_type(YAML::NodeType::Map);
  data_.mark_defined();
  const auto first = data_.type();

  data_.mark_defined();
  const auto second = data_.type();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, YAML::NodeType::Map);
}

}  // namespace