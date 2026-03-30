// TEST_ID: 649
//
// Unit tests for YAML::detail::node_data::end() const
//
// Constraints respected:
// - Treat node_data as a black box (no private state access)
// - Test only observable behavior through public interface
// - No re-implementation/inference of internal logic beyond what the interface exposes

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::detail::node_data;
using YAML::detail::const_node_iterator;

class NodeDataEndTest_649 : public ::testing::Test {
 protected:
  node_data data;
};

TEST_F(NodeDataEndTest_649, EndOnFreshObjectIsDefaultIterator_649) {
  const_node_iterator it;
  EXPECT_NO_THROW(it = data.end());
  EXPECT_EQ(it, const_node_iterator());
}

TEST_F(NodeDataEndTest_649, EndRemainsDefaultWhenTypeIsChangedButNotDefined_649) {
  // Even if the type is changed, the object may still be "not defined" from an
  // interface perspective unless explicitly marked defined.
  EXPECT_NO_THROW(data.set_type(YAML::NodeType::Sequence));
  EXPECT_EQ(data.end(), const_node_iterator());

  EXPECT_NO_THROW(data.set_type(YAML::NodeType::Map));
  EXPECT_EQ(data.end(), const_node_iterator());

  EXPECT_NO_THROW(data.set_type(YAML::NodeType::Scalar));
  EXPECT_EQ(data.end(), const_node_iterator());

  EXPECT_NO_THROW(data.set_type(YAML::NodeType::Null));
  EXPECT_EQ(data.end(), const_node_iterator());
}

TEST_F(NodeDataEndTest_649, EndForDefinedNullIsDefaultIterator_649) {
  EXPECT_NO_THROW(data.mark_defined());
  EXPECT_NO_THROW(data.set_type(YAML::NodeType::Null));

  // For non-container node kinds, end() is expected to produce an "empty" iterator.
  EXPECT_EQ(data.end(), const_node_iterator());
}

TEST_F(NodeDataEndTest_649, EndForDefinedScalarIsDefaultIterator_649) {
  EXPECT_NO_THROW(data.mark_defined());
  EXPECT_NO_THROW(data.set_scalar("hello"));
  EXPECT_NO_THROW(data.set_type(YAML::NodeType::Scalar));

  EXPECT_EQ(data.end(), const_node_iterator());
}

TEST_F(NodeDataEndTest_649, BeginEqualsEndForEmptyDefinedSequence_649) {
  EXPECT_NO_THROW(data.mark_defined());
  EXPECT_NO_THROW(data.set_type(YAML::NodeType::Sequence));

  const_node_iterator b;
  const_node_iterator e;
  EXPECT_NO_THROW(b = data.begin());
  EXPECT_NO_THROW(e = data.end());

  // Observable behavior for an empty sequence: empty range.
  EXPECT_EQ(b, e);
}

TEST_F(NodeDataEndTest_649, BeginEqualsEndForEmptyDefinedMap_649) {
  EXPECT_NO_THROW(data.mark_defined());
  EXPECT_NO_THROW(data.set_type(YAML::NodeType::Map));

  const_node_iterator b;
  const_node_iterator e;
  EXPECT_NO_THROW(b = data.begin());
  EXPECT_NO_THROW(e = data.end());

  // Observable behavior for an empty map: empty range.
  EXPECT_EQ(b, e);
}

}  // namespac