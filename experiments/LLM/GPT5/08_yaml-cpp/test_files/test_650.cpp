// TEST_ID: 650
// File: ./TestProjects/yaml-cpp/test/node_data_insert_test_650.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::detail::node;
using YAML::detail::node_data;

static YAML::detail::shared_memory_holder MakeMemory_650() {
  // Treat as an opaque collaborator; default construction is the least-assumptive option.
  return YAML::detail::shared_memory_holder();
}

static node MakeScalarNode_650(const std::string& s) {
  node n;
  n.set_scalar(s);
  return n;
}

class NodeDataInsertTest_650 : public ::testing::Test {
protected:
  YAML::detail::shared_memory_holder mem_ = MakeMemory_650();
};

}  // namespace

TEST_F(NodeDataInsertTest_650, InsertIntoMapIncreasesSizeAndGetReturnsValue_650) {
  node_data data;
  data.set_type(YAML::NodeType::Map);

  node key = MakeScalarNode_650("k");
  node value = MakeScalarNode_650("v");

  EXPECT_NO_THROW(data.insert(key, value, mem_));

  EXPECT_EQ(data.type(), YAML::NodeType::Map);
  EXPECT_EQ(data.size(), 1u);

  node* found = data.get(key, mem_);
  ASSERT_NE(found, nullptr);
  EXPECT_TRUE(found->equals("v", mem_));
}

TEST_F(NodeDataInsertTest_650, InsertWhenNullConvertsToMapAndStoresPair_650) {
  node_data data;
  data.set_type(YAML::NodeType::Null);

  node key = MakeScalarNode_650("a");
  node value = MakeScalarNode_650("b");

  EXPECT_NO_THROW(data.insert(key, value, mem_));

  EXPECT_EQ(data.type(), YAML::NodeType::Map);
  EXPECT_EQ(data.size(), 1u);

  node* found = data.get(key, mem_);
  ASSERT_NE(found, nullptr);
  EXPECT_TRUE(found->equals("b", mem_));
}

TEST_F(NodeDataInsertTest_650, InsertWhenUndefinedConvertsToMapAndStoresPair_650) {
  node_data data;
  data.set_type(YAML::NodeType::Undefined);

  node key = MakeScalarNode_650("u");
  node value = MakeScalarNode_650("v");

  EXPECT_NO_THROW(data.insert(key, value, mem_));

  EXPECT_EQ(data.type(), YAML::NodeType::Map);
  EXPECT_EQ(data.size(), 1u);

  node* found = data.get(key, mem_);
  ASSERT_NE(found, nullptr);
  EXPECT_TRUE(found->equals("v", mem_));
}

TEST_F(NodeDataInsertTest_650, InsertWhenSequenceConvertsToMapAndStoresPair_650) {
  node_data data;
  data.set_type(YAML::NodeType::Sequence);

  node key = MakeScalarNode_650("skey");
  node value = MakeScalarNode_650("sval");

  EXPECT_NO_THROW(data.insert(key, value, mem_));

  EXPECT_EQ(data.type(), YAML::NodeType::Map);
  EXPECT_EQ(data.size(), 1u);

  node* found = data.get(key, mem_);
  ASSERT_NE(found, nullptr);
  EXPECT_TRUE(found->equals("sval", mem_));
}

TEST_F(NodeDataInsertTest_650, InsertWhenScalarThrowsBadSubscript_650) {
  node_data data;
  data.set_type(YAML::NodeType::Scalar);
  data.set_scalar("scalar-root");

  node key = MakeScalarNode_650("k");
  node value = MakeScalarNode_650("v");

  // Observable error behavior: inserting into a scalar throws.
  EXPECT_THROW(data.insert(key, value, mem_), YAML::BadSubscript);
}

TEST_F(NodeDataInsertTest_650, InsertSameKeyTwiceDoesNotCrashAndKeyRemainsQueryable_650) {
  node_data data;
  data.set_type(YAML::NodeType::Map);

  node key = MakeScalarNode_650("dup");
  node v1 = MakeScalarNode_650("v1");
  node v2 = MakeScalarNode_650("v2");

  ASSERT_NO_THROW(data.insert(key, v1, mem_));
  const std::size_t size_after_first = data.size();
  ASSERT_GE(size_after_first, 1u);

  ASSERT_NO_THROW(data.insert(key, v2, mem_));

  // Do not assume overwrite vs. allow-duplicate behavior; only require it remains usable.
  const std::size_t size_after_second = data.size();
  EXPECT_GE(size_after_second, 1u);
  EXPECT_LE(size_after_second, size_after_first + 1u);

  node* found = data.get(key, mem_);
  ASSERT_NE(found, nullptr);
  // Value could be v1 or v2 depending on implementation; accept either.
  EXPECT_TRUE(found->equals("v1", mem_) || found->equals("v2", mem_));
}