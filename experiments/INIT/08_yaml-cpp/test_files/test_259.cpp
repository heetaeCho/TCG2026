// TEST_ID: 259
#include <gtest/gtest.h>

#include <type_traits>
#include <string>

#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::node;
using YAML::detail::shared_memory_holder;

shared_memory_holder MakeMemoryHolder() {
  if constexpr (std::is_default_constructible_v<shared_memory_holder>) {
    return shared_memory_holder{};
  } else if constexpr (std::is_constructible_v<shared_memory_holder, std::nullptr_t>) {
    return shared_memory_holder{nullptr};
  } else {
    // Fall back to value-initialization if possible (keeps tests black-box).
    return shared_memory_holder();
  }
}

class NodeGetTest_259 : public ::testing::Test {
protected:
  shared_memory_holder mem_ = MakeMemoryHolder();
};

}  // namespace

TEST_F(NodeGetTest_259, GetOnEmptyNodeReturnsNullptrForStringKey_259) {
  node n;
  node* got = n.get(std::string("missing"), mem_);
  EXPECT_EQ(got, nullptr);
}

TEST_F(NodeGetTest_259, GetOnEmptyNodeReturnsNullptrForCStringKey_259) {
  node n;
  node* got = n.get("missing", mem_);
  EXPECT_EQ(got, nullptr);
}

TEST_F(NodeGetTest_259, GetReturnsInsertedValueForStdStringKey_259) {
  node parent;
  parent.set_type(YAML::NodeType::Map);

  node key;
  key.set_scalar("k1");

  node value;
  value.set_scalar("v1");

  parent.insert(key, value, mem_);

  node* got = parent.get(std::string("k1"), mem_);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got->scalar(), "v1");
}

TEST_F(NodeGetTest_259, GetReturnsNullptrForMissingKeyWhenOtherKeysExist_259) {
  node parent;
  parent.set_type(YAML::NodeType::Map);

  node key1;
  key1.set_scalar("k1");
  node value1;
  value1.set_scalar("v1");
  parent.insert(key1, value1, mem_);

  node* got = parent.get(std::string("k2"), mem_);
  EXPECT_EQ(got, nullptr);
}

TEST_F(NodeGetTest_259, GetWorksWithCStringKeyAfterInsert_259) {
  node parent;
  parent.set_type(YAML::NodeType::Map);

  node key;
  key.set_scalar("hello");
  node value;
  value.set_scalar("world");
  parent.insert(key, value, mem_);

  node* got = parent.get("hello", mem_);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got->scalar(), "world");
}