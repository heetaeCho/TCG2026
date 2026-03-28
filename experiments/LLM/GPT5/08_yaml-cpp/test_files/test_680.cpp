// TEST_ID: 680
#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <string>
#include <vector>

namespace {

class NodeIteratorCtorTest_680 : public ::testing::Test {
 protected:
  // Helper: insert into a map in a way that preserves insertion ordering in yaml-cpp.
  // We prefer force_insert because it allows inserting explicit Undefined nodes without
  // relying on operator[] semantics.
  static void ForceInsert(YAML::Node& map,
                          const std::string& key,
                          const YAML::Node& value) {
    // yaml-cpp provides force_insert on Node for maps in supported versions.
    map.force_insert(YAML::Node(key), value);
  }

  static YAML::Node MakeUndefined() {
    return YAML::Node(YAML::NodeType::Undefined);
  }

  static std::vector<std::string> CollectKeys(const YAML::Node& map) {
    std::vector<std::string> keys;
    for (auto it = map.begin(); it != map.end(); ++it) {
      keys.push_back(it->first.as<std::string>());
    }
    return keys;
  }
};

TEST_F(NodeIteratorCtorTest_680, MapBeginSkipsLeadingUndefinedValue_680) {
  YAML::Node m(YAML::NodeType::Map);

  ForceInsert(m, "undef", MakeUndefined());
  ForceInsert(m, "a", YAML::Node(1));

  auto it = m.begin();
  ASSERT_NE(it, m.end());

  // Observable behavior: iteration should skip entries whose value is undefined.
  EXPECT_EQ(it->first.as<std::string>(), "a");
  EXPECT_EQ(it->second.as<int>(), 1);
}

TEST_F(NodeIteratorCtorTest_680, MapBeginSkipsMultipleLeadingUndefinedValues_680) {
  YAML::Node m(YAML::NodeType::Map);

  ForceInsert(m, "undef1", MakeUndefined());
  ForceInsert(m, "undef2", MakeUndefined());
  ForceInsert(m, "b", YAML::Node(2));

  auto it = m.begin();
  ASSERT_NE(it, m.end());

  EXPECT_EQ(it->first.as<std::string>(), "b");
  EXPECT_EQ(it->second.as<int>(), 2);
}

TEST_F(NodeIteratorCtorTest_680, MapBeginEqualsEndWhenAllEntriesUndefined_680) {
  YAML::Node m(YAML::NodeType::Map);

  ForceInsert(m, "undef1", MakeUndefined());
  ForceInsert(m, "undef2", MakeUndefined());

  // If the iterator constructor advances until a defined entry is found,
  // and none exist, begin() should be equal to end().
  EXPECT_EQ(m.begin(), m.end());
}

TEST_F(NodeIteratorCtorTest_680, IncrementSkipsUndefinedEntriesInTheMiddle_680) {
  YAML::Node m(YAML::NodeType::Map);

  ForceInsert(m, "a", YAML::Node(1));
  ForceInsert(m, "undef", MakeUndefined());
  ForceInsert(m, "b", YAML::Node(2));

  const std::vector<std::string> keys = CollectKeys(m);

  // Observable behavior: undefined-valued entry should not be yielded.
  ASSERT_EQ(keys.size(), 2u);
  EXPECT_EQ(keys[0], "a");
  EXPECT_EQ(keys[1], "b");
}

TEST_F(NodeIteratorCtorTest_680, PostIncrementReturnsPreviousIteratorPosition_680) {
  YAML::Node m(YAML::NodeType::Map);

  ForceInsert(m, "a", YAML::Node(1));
  ForceInsert(m, "b", YAML::Node(2));

  auto it = m.begin();
  ASSERT_NE(it, m.end());

  auto prev = it++;
  ASSERT_NE(prev, m.end());
  ASSERT_NE(it, m.end());

  EXPECT_EQ(prev->first.as<std::string>(), "a");
  EXPECT_EQ(prev->second.as<int>(), 1);

  EXPECT_EQ(it->first.as<std::string>(), "b");
  EXPECT_EQ(it->second.as<int>(), 2);
}

TEST_F(NodeIteratorCtorTest_680, EmptyMapBeginEqualsEnd_680) {
  YAML::Node m(YAML::NodeType::Map);
  EXPECT_EQ(m.begin(), m.end());
}

}  // namespace