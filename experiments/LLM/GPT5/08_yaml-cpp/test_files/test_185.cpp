// File: node_iterator_base_increment_test_185.cpp
#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <set>
#include <string>
#include <vector>

namespace {

class NodeIteratorBaseIncrementTest_185 : public ::testing::Test {};

TEST_F(NodeIteratorBaseIncrementTest_185, SequencePreIncrementMovesToNextElement_185) {
  YAML::Node seq = YAML::Load("[10, 20, 30]");

  auto it = seq.begin();
  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 10);

  ++it;
  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 20);

  ++it;
  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 30);

  ++it;
  EXPECT_EQ(it, seq.end());
}

TEST_F(NodeIteratorBaseIncrementTest_185, SequenceSingleElementPreIncrementReachesEnd_185) {
  YAML::Node seq = YAML::Load("[42]");

  auto it = seq.begin();
  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 42);

  ++it;
  EXPECT_EQ(it, seq.end());
}

TEST_F(NodeIteratorBaseIncrementTest_185, SequenceEmptyBeginEqualsEnd_185) {
  YAML::Node seq = YAML::Load("[]");
  EXPECT_EQ(seq.begin(), seq.end());
}

TEST_F(NodeIteratorBaseIncrementTest_185, MapPreIncrementAdvancesAndVisitsAllDefinedValues_185) {
  YAML::Node map = YAML::Load("{a: 1, b: 2, c: 3}");

  std::set<std::string> keys;
  std::vector<int> values;

  for (auto it = map.begin(); it != map.end(); ++it) {
    keys.insert(it->first.as<std::string>());
    values.push_back(it->second.as<int>());
  }

  EXPECT_EQ(keys.size(), 3u);
  EXPECT_TRUE(keys.count("a"));
  EXPECT_TRUE(keys.count("b"));
  EXPECT_TRUE(keys.count("c"));
  EXPECT_EQ(values.size(), 3u);
}

TEST_F(NodeIteratorBaseIncrementTest_185, MapPreIncrementSkipsUndefinedValuesIfTheyExist_185) {
  // Construct a map with one explicitly-undefined value.
  // This test verifies observable behavior: iteration via ++ should not yield entries
  // whose value node is undefined (if the iterator is defined to skip them).
  YAML::Node map;
  map["a"] = 1;
  map["b"] = YAML::Node();  // undefined
  map["c"] = 3;

  std::set<std::string> visited_keys;
  for (auto it = map.begin(); it != map.end(); ++it) {
    const std::string k = it->first.as<std::string>();

    // If the iterator yields an entry, its value should be defined (observable via IsDefined()).
    EXPECT_TRUE(it->second.IsDefined()) << "Iterator produced an undefined value for key: " << k;

    visited_keys.insert(k);
  }

  // Must contain the defined keys.
  EXPECT_TRUE(visited_keys.count("a"));
  EXPECT_TRUE(visited_keys.count("c"));

  // If undefined values are skipped by ++ (as implied by the interface/partial implementation),
  // "b" should not be visited.
  EXPECT_FALSE(visited_keys.count("b"));
}

TEST_F(NodeIteratorBaseIncrementTest_185, MapEmptyBeginEqualsEnd_185) {
  YAML::Node map = YAML::Load("{}");
  EXPECT_EQ(map.begin(), map.end());
}

}  // namespace