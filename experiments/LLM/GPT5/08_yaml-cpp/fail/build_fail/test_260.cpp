// TEST_ID: 260
#include <gtest/gtest.h>

#include <string>

#include <yaml-cpp/node/detail/node.h>

namespace {

using YAML::detail::node;
using YAML::detail::shared_memory_holder;

shared_memory_holder NullMemory_260() {
  // The interface accepts a shared_memory_holder; tests treat it as an opaque handle.
  return shared_memory_holder{};
}

node MakeScalarNode_260(const std::string& s) {
  node n;
  n.set_scalar(s);
  return n;
}

class RemoveTest_260 : public ::testing::Test {
 protected:
  shared_memory_holder mem_ = NullMemory_260();
};

}  // namespace

TEST_F(RemoveTest_260, RemoveExistingStringKeyDecreasesSizeAndMakesKeyMissing_260) {
  node m;
  m.set_type(YAML::NodeType::Map);

  // Insert two items.
  m.force_insert(std::string("a"), std::string("1"), mem_);
  m.force_insert(std::string("b"), std::string("2"), mem_);

  const std::size_t before = m.size();
  ASSERT_GE(before, 2u);

  // Remove one existing key.
  EXPECT_TRUE(m.remove(std::string("a"), mem_));
  EXPECT_EQ(m.size(), before - 1);

  // Key should no longer be retrievable.
  EXPECT_EQ(m.get(std::string("a"), mem_), nullptr);

  // Other key should remain.
  EXPECT_NE(m.get(std::string("b"), mem_), nullptr);
}

TEST_F(RemoveTest_260, RemoveNonExistentKeyReturnsFalseAndDoesNotChangeSize_260) {
  node m;
  m.set_type(YAML::NodeType::Map);

  m.force_insert(std::string("a"), std::string("1"), mem_);
  const std::size_t before = m.size();
  ASSERT_GE(before, 1u);

  EXPECT_FALSE(m.remove(std::string("does_not_exist"), mem_));
  EXPECT_EQ(m.size(), before);

  // Existing key should still be present.
  EXPECT_NE(m.get(std::string("a"), mem_), nullptr);
}

TEST_F(RemoveTest_260, RemoveFromEmptyMapReturnsFalseAndSizeStaysZero_260) {
  node m;
  m.set_type(YAML::NodeType::Map);

  ASSERT_EQ(m.size(), 0u);
  EXPECT_FALSE(m.remove(std::string("a"), mem_));
  EXPECT_EQ(m.size(), 0u);
}

TEST_F(RemoveTest_260, RemoveUsingConstCharKeyWorksLikeStringKey_260) {
  node m;
  m.set_type(YAML::NodeType::Map);

  m.force_insert(std::string("a"), std::string("1"), mem_);
  const std::size_t before = m.size();
  ASSERT_GE(before, 1u);

  // Template instantiation with a const char* key.
  EXPECT_TRUE(m.remove("a", mem_));
  EXPECT_EQ(m.size(), before - 1);
  EXPECT_EQ(m.get("a", mem_), nullptr);
}

TEST_F(RemoveTest_260, RemoveUsingNodeKeyOverloadRemovesEntry_260) {
  node m;
  m.set_type(YAML::NodeType::Map);

  m.force_insert(std::string("k1"), std::string("v1"), mem_);
  m.force_insert(std::string("k2"), std::string("v2"), mem_);
  const std::size_t before = m.size();
  ASSERT_GE(before, 2u);

  node key = MakeScalarNode_260("k1");

  // Use the non-template overload: bool remove(node& key, shared_memory_holder)
  EXPECT_TRUE(m.remove(key, mem_));
  EXPECT_EQ(m.size(), before - 1);

  EXPECT_EQ(m.get(std::string("k1"), mem_), nullptr);
  EXPECT_NE(m.get(std::string("k2"), mem_), nullptr);
}

TEST_F(RemoveTest_260, RemoveOnNonMapNodeDoesNotIncreaseSize_260) {
  node n;
  // Leave as default type or explicitly set to Null; behavior should be observable via return value/size.
  n.set_null();

  const std::size_t before = n.size();
  // Removing from a non-map / null node should not report success and should not mutate size.
  EXPECT_FALSE(n.remove(std::string("a"), mem_));
  EXPECT_EQ(n.size(), before);
}