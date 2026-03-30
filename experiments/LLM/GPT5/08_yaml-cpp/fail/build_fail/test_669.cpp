// TEST_ID: 669
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node_data.h"

using YAML::detail::memory_holder;
using YAML::detail::node;
using YAML::detail::node_data;

namespace {

class NodeDataGetTest_669 : public ::testing::Test {
 protected:
  void SetUp() override {
    mem = std::make_shared<memory_holder>();
  }

  // NOTE: In yaml-cpp internals, shared_memory_holder is typically an alias to a shared_ptr.
  // We keep it as "auto" compatible by matching the parameter type in calls.
  std::shared_ptr<memory_holder> mem;
};

TEST_F(NodeDataGetTest_669, NullTypeReturnsNullptr_669) {
  node_data nd;
  nd.set_null();

  const node_data& cnd = nd;
  EXPECT_EQ(cnd.get(0, mem), nullptr);
  EXPECT_EQ(cnd.get(std::string("key"), mem), nullptr);
}

TEST_F(NodeDataGetTest_669, UndefinedTypeReturnsNullptr_669) {
  node_data nd;
  nd.set_type(YAML::NodeType::Undefined);

  const node_data& cnd = nd;
  EXPECT_EQ(cnd.get(0, mem), nullptr);
  EXPECT_EQ(cnd.get(std::string("key"), mem), nullptr);
}

TEST_F(NodeDataGetTest_669, SequenceReturnsElementByIndex_669) {
  node_data nd;
  nd.set_type(YAML::NodeType::Sequence);

  node& n0 = mem->create_node();
  node& n1 = mem->create_node();
  node& n2 = mem->create_node();

  nd.push_back(n0, mem);
  nd.push_back(n1, mem);
  nd.push_back(n2, mem);

  const node_data& cnd = nd;

  EXPECT_EQ(cnd.get(0, mem), &n0);
  EXPECT_EQ(cnd.get(1, mem), &n1);
  EXPECT_EQ(cnd.get(2, mem), &n2);
}

TEST_F(NodeDataGetTest_669, SequenceOutOfRangeReturnsNullptr_669) {
  node_data nd;
  nd.set_type(YAML::NodeType::Sequence);

  node& n0 = mem->create_node();
  nd.push_back(n0, mem);

  const node_data& cnd = nd;

  EXPECT_EQ(cnd.get(1, mem), nullptr);
  EXPECT_EQ(cnd.get(static_cast<std::size_t>(999999), mem), nullptr);
}

TEST_F(NodeDataGetTest_669, ScalarTypeThrowsBadSubscript_669) {
  node_data nd;
  nd.set_type(YAML::NodeType::Scalar);
  nd.set_scalar("hello");

  const node_data& cnd = nd;

  EXPECT_THROW((void)cnd.get(0, mem), YAML::BadSubscript);
  EXPECT_THROW((void)cnd.get(std::string("key"), mem), YAML::BadSubscript);
}

TEST_F(NodeDataGetTest_669, MapReturnsValueForExistingKeyNode_669) {
  node_data nd;
  nd.set_type(YAML::NodeType::Map);

  node& key = mem->create_node();
  node& value = mem->create_node();

  // If available in this codebase, setting scalar makes the equality intent explicit.
  // (If these members are not present on node, compilation will fail and should be
  // adjusted to whatever public node interface exists in the codebase.)
  key.set_scalar("k");
  value.set_scalar("v");

  nd.insert(key, value, mem);

  const node_data& cnd = nd;
  node* found = cnd.get(key, mem);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, &value);
}

TEST_F(NodeDataGetTest_669, MapMissingKeyReturnsNullptr_669) {
  node_data nd;
  nd.set_type(YAML::NodeType::Map);

  node& key1 = mem->create_node();
  node& val1 = mem->create_node();
  key1.set_scalar("k1");
  val1.set_scalar("v1");
  nd.insert(key1, val1, mem);

  node& key2 = mem->create_node();
  key2.set_scalar("k2");

  const node_data& cnd = nd;
  EXPECT_EQ(cnd.get(key2, mem), nullptr);
}

}  // namespace