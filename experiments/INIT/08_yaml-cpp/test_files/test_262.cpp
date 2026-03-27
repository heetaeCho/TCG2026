// TEST_ID: 262
#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node.h>

namespace {

using YAML::detail::node;

// Helper: most yaml-cpp internals accept a default-constructed shared_memory_holder.
// (We intentionally don't assume any particular allocator behavior.)
static YAML::detail::shared_memory_holder DefaultMemory_262() {
  return YAML::detail::shared_memory_holder{};
}

class RemoveTest_262 : public ::testing::Test {
 protected:
  YAML::detail::shared_memory_holder mem_ = DefaultMemory_262();

  static node MakeScalar_262(const std::string& s) {
    node n;
    n.set_scalar(s);
    return n;  // Note: node is non-copyable; RVO/move elision applies.
  }
};

TEST_F(RemoveTest_262, RemoveFromEmptyNodeReturnsFalseAndKeepsSize_262) {
  node map;
  map.set_type(YAML::NodeType::Map);

  node key;
  key.set_scalar("missing");

  EXPECT_EQ(map.size(), 0u);

  bool removed = true;  // ensure return value is actually written
  EXPECT_NO_THROW(removed = map.remove(key, mem_));
  EXPECT_FALSE(removed);

  EXPECT_EQ(map.size(), 0u);
  EXPECT_EQ(map.get(key, mem_), nullptr);
}

TEST_F(RemoveTest_262, InsertThenRemoveExistingKeyReturnsTrueAndErases_262) {
  node map;
  map.set_type(YAML::NodeType::Map);

  node key;
  key.set_scalar("k");
  node value;
  value.set_scalar("v");

  map.insert(key, value, mem_);
  ASSERT_EQ(map.size(), 1u);
  ASSERT_NE(map.get(key, mem_), nullptr);

  bool removed = false;
  EXPECT_NO_THROW(removed = map.remove(key, mem_));
  EXPECT_TRUE(removed);

  EXPECT_EQ(map.size(), 0u);
  EXPECT_EQ(map.get(key, mem_), nullptr);
}

TEST_F(RemoveTest_262, RemoveNonExistentKeyReturnsFalseAndDoesNotAffectExistingEntries_262) {
  node map;
  map.set_type(YAML::NodeType::Map);

  node key1;
  key1.set_scalar("k1");
  node value1;
  value1.set_scalar("v1");

  map.insert(key1, value1, mem_);
  ASSERT_EQ(map.size(), 1u);
  ASSERT_NE(map.get(key1, mem_), nullptr);

  node missing;
  missing.set_scalar("k2");

  bool removed = true;
  EXPECT_NO_THROW(removed = map.remove(missing, mem_));
  EXPECT_FALSE(removed);

  // Existing entry remains.
  EXPECT_EQ(map.size(), 1u);
  EXPECT_NE(map.get(key1, mem_), nullptr);
  EXPECT_EQ(map.get(missing, mem_), nullptr);
}

}  // namespace