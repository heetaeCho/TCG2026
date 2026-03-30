// TEST_ID: 642
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/type.h"

namespace {

using YAML::NodeType;
using YAML::detail::node_data;

class NodeDataSetTypeTest_642 : public ::testing::Test {
 protected:
  node_data nd_;
};

TEST_F(NodeDataSetTypeTest_642, UndefinedSetsTypeAndMarksNotDefined_642) {
  // Precondition: default-constructed node_data is not defined in yaml-cpp.
  EXPECT_FALSE(nd_.is_defined());

  nd_.set_type(NodeType::Undefined);

  EXPECT_FALSE(nd_.is_defined());
  EXPECT_EQ(nd_.type(), NodeType::Undefined);
}

TEST_F(NodeDataSetTypeTest_642, NonUndefinedMarksDefinedEvenIfTypeUnchanged_642) {
  // Default constructed node_data has type Null but is not defined.
  EXPECT_EQ(nd_.type(), NodeType::Null);
  EXPECT_FALSE(nd_.is_defined());

  // Setting to a non-Undefined type should mark defined, even if type is unchanged.
  nd_.set_type(NodeType::Null);

  EXPECT_TRUE(nd_.is_defined());
  EXPECT_EQ(nd_.type(), NodeType::Null);
}

TEST_F(NodeDataSetTypeTest_642, SameTypeDoesNotResetScalar_642) {
  nd_.set_scalar("hello");
  ASSERT_TRUE(nd_.is_defined());
  ASSERT_EQ(nd_.type(), NodeType::Scalar);
  ASSERT_EQ(nd_.scalar(), "hello");

  // Setting the same type should not clear the scalar content.
  nd_.set_type(NodeType::Scalar);

  EXPECT_TRUE(nd_.is_defined());
  EXPECT_EQ(nd_.type(), NodeType::Scalar);
  EXPECT_EQ(nd_.scalar(), "hello");
}

TEST_F(NodeDataSetTypeTest_642, ChangingToScalarClearsPreviousScalarContent_642) {
  nd_.set_scalar("payload");
  ASSERT_EQ(nd_.type(), NodeType::Scalar);
  ASSERT_EQ(nd_.scalar(), "payload");

  // Change away from Scalar, then back to Scalar. Transition to Scalar should reset scalar storage.
  nd_.set_type(NodeType::Sequence);
  ASSERT_EQ(nd_.type(), NodeType::Sequence);

  nd_.set_type(NodeType::Scalar);

  EXPECT_EQ(nd_.type(), NodeType::Scalar);
  EXPECT_TRUE(nd_.is_defined());
  EXPECT_EQ(nd_.scalar(), node_data::empty_scalar());
}

TEST_F(NodeDataSetTypeTest_642, UndefinedThenNonUndefinedMarksDefinedAndUpdatesType_642) {
  nd_.set_type(NodeType::Undefined);
  ASSERT_FALSE(nd_.is_defined());
  ASSERT_EQ(nd_.type(), NodeType::Undefined);

  nd_.set_type(NodeType::Map);

  EXPECT_TRUE(nd_.is_defined());
  EXPECT_EQ(nd_.type(), NodeType::Map);
}

}  // namespace