// TEST_ID: 575
#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>

namespace {

class NodeRemoveNodeTest_575 : public ::testing::Test {
 protected:
  // Helper to read a key without mutating the map (avoid non-const operator[] side effects).
  static YAML::Node ConstLookup(const YAML::Node& map, const YAML::Node& key) {
    return map[key];
  }
};

TEST_F(NodeRemoveNodeTest_575, RemoveExistingStringKey_ReturnsTrueAndErases_575) {
  YAML::Node map(YAML::NodeType::Map);
  map.force_insert("a", 1);

  const YAML::Node key("a");

  const bool removed = map.remove(key);
  EXPECT_TRUE(removed);

  const YAML::Node value_after = ConstLookup(map, key);
  EXPECT_FALSE(value_after.IsDefined());
  EXPECT_EQ(map.size(), 0u);
}

TEST_F(NodeRemoveNodeTest_575, RemoveMissingKey_ReturnsFalseAndDoesNotChangeSize_575) {
  YAML::Node map(YAML::NodeType::Map);
  map.force_insert("a", 1);
  map.force_insert("b", 2);

  const std::size_t before_size = map.size();
  const YAML::Node missing_key("does_not_exist");

  const bool removed = map.remove(missing_key);
  EXPECT_FALSE(removed);
  EXPECT_EQ(map.size(), before_size);

  // Existing entries should still be there (checked via const lookup).
  EXPECT_TRUE(ConstLookup(map, YAML::Node("a")).IsDefined());
  EXPECT_TRUE(ConstLookup(map, YAML::Node("b")).IsDefined());
}

TEST_F(NodeRemoveNodeTest_575, RemoveSameKeyTwice_SecondCallReturnsFalse_575) {
  YAML::Node map(YAML::NodeType::Map);
  map.force_insert("k", "v");

  const YAML::Node key("k");

  const bool first = map.remove(key);
  EXPECT_TRUE(first);
  EXPECT_EQ(map.size(), 0u);

  const bool second = map.remove(key);
  EXPECT_FALSE(second);
  EXPECT_EQ(map.size(), 0u);
}

TEST_F(NodeRemoveNodeTest_575, RemoveExistingNonStringKey_WorksWithNodeKey_575) {
  YAML::Node map(YAML::NodeType::Map);

  // Use an integer key via the Key/Value overload to ensure a non-string key exists.
  map.force_insert(123, "value");

  const YAML::Node key_node(123);

  const bool removed = map.remove(key_node);
  EXPECT_TRUE(removed);

  const YAML::Node value_after = ConstLookup(map, key_node);
  EXPECT_FALSE(value_after.IsDefined());
  EXPECT_EQ(map.size(), 0u);
}

TEST_F(NodeRemoveNodeTest_575, RemoveOnNonMapNode_DoesNotThrow_575) {
  // We intentionally do not assume how yaml-cpp behaves (convert to map, return false, etc.).
  // This test only verifies the call is safe/observable through the interface.
  YAML::Node scalar("hello");
  YAML::Node key("k");

  EXPECT_NO_THROW({
    (void)scalar.remove(key);
  });
}

}  // namespace