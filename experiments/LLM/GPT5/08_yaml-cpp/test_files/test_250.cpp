// TEST_ID: 250
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/type.h"

namespace {

using YAML::detail::node;

class NodeSetNullTest_250 : public ::testing::Test {};

TEST_F(NodeSetNullTest_250, SetNullMakesNodeDefined_250) {
  node n;
  n.set_null();

  EXPECT_TRUE(n.is_defined());
}

TEST_F(NodeSetNullTest_250, SetNullSetsTypeToNull_250) {
  node n;
  n.set_null();

  EXPECT_EQ(n.type(), YAML::NodeType::Null);
}

TEST_F(NodeSetNullTest_250, SetNullIsIdempotent_250) {
  node n;
  n.set_null();
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ(n.type(), YAML::NodeType::Null);

  // Calling again should be safe and keep observable state consistent.
  n.set_null();
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ(n.type(), YAML::NodeType::Null);
}

TEST_F(NodeSetNullTest_250, SetNullDoesNotBreakMarkAccess_250) {
  node n;
  n.set_null();

  // Observable behavior: mark() remains callable without crashing/throwing.
  (void)n.mark();
  SUCCEED();
}

}  // namespace