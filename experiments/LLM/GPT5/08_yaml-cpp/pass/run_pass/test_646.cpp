// TEST_ID: 646
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::detail::node_data;

class NodeDataSetScalarTest_646 : public ::testing::Test {};

TEST_F(NodeDataSetScalarTest_646, SetScalarMakesNodeDefinedAndScalarType_646) {
  node_data nd;

  const std::string value = "hello";
  EXPECT_NO_THROW(nd.set_scalar(value));

  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), YAML::NodeType::Scalar);
}

TEST_F(NodeDataSetScalarTest_646, SetScalarStoresExactValue_646) {
  node_data nd;

  const std::string value = "some scalar value";
  nd.set_scalar(value);

  EXPECT_EQ(nd.scalar(), value);
}

TEST_F(NodeDataSetScalarTest_646, SetScalarAcceptsEmptyString_646) {
  node_data nd;

  const std::string value;
  EXPECT_NO_THROW(nd.set_scalar(value));

  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), YAML::NodeType::Scalar);
  EXPECT_EQ(nd.scalar(), value);
}

TEST_F(NodeDataSetScalarTest_646, SetScalarOverwritesPreviousScalar_646) {
  node_data nd;

  nd.set_scalar("first");
  EXPECT_EQ(nd.scalar(), "first");
  EXPECT_EQ(nd.type(), YAML::NodeType::Scalar);
  EXPECT_TRUE(nd.is_defined());

  nd.set_scalar("second");
  EXPECT_EQ(nd.scalar(), "second");
  EXPECT_EQ(nd.type(), YAML::NodeType::Scalar);
  EXPECT_TRUE(nd.is_defined());
}

TEST_F(NodeDataSetScalarTest_646, SetScalarHandlesEmbeddedNullBytes_646) {
  node_data nd;

  const std::string value_with_null(std::string("abc\0def", 7));
  EXPECT_NO_THROW(nd.set_scalar(value_with_null));

  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), YAML::NodeType::Scalar);
  EXPECT_EQ(nd.scalar().size(), value_with_null.size());
  EXPECT_EQ(nd.scalar(), value_with_null);
}

TEST_F(NodeDataSetScalarTest_646, SetScalarHandlesLargeInput_646) {
  node_data nd;

  std::string large(1 << 20, 'x');  // 1 MiB
  EXPECT_NO_THROW(nd.set_scalar(large));

  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), YAML::NodeType::Scalar);
  EXPECT_EQ(nd.scalar().size(), large.size());
  EXPECT_EQ(nd.scalar(), large);
}

}  // namespace