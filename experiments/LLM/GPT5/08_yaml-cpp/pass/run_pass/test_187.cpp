// TEST_ID: 187
// File: node_iterator_operator_star_test_187.cpp

#include <gtest/gtest.h>

#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

namespace {

TEST(NodeIteratorOperatorStarTest_187, SequenceDereferenceYieldsEachElementInOrder_187) {
  YAML::Node seq;
  seq.push_back(10);
  seq.push_back(20);
  seq.push_back(30);

  ASSERT_TRUE(seq.IsSequence());
  ASSERT_EQ(seq.size(), 3u);

  std::vector<int> got;
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    // Exercising YAML::detail::node_iterator_base::operator*() through the public iterator.
    YAML::Node elem = *it;
    ASSERT_TRUE(elem.IsScalar());
    got.push_back(elem.as<int>());
  }

  EXPECT_EQ((std::vector<int>{10, 20, 30}), got);
}

TEST(NodeIteratorOperatorStarTest_187, SequenceDereferenceWorksWithNonScalarNodes_187) {
  YAML::Node seq;
  YAML::Node m;
  m["k"] = "v";
  YAML::Node innerSeq;
  innerSeq.push_back(1);
  innerSeq.push_back(2);

  seq.push_back(m);
  seq.push_back(innerSeq);

  ASSERT_TRUE(seq.IsSequence());
  ASSERT_EQ(seq.size(), 2u);

  auto it = seq.begin();

  YAML::Node first = *it;
  ASSERT_TRUE(first.IsMap());
  EXPECT_EQ(first["k"].as<std::string>(), "v");

  ++it;
  YAML::Node second = *it;
  ASSERT_TRUE(second.IsSequence());
  ASSERT_EQ(second.size(), 2u);
  EXPECT_EQ(second[0].as<int>(), 1);
  EXPECT_EQ(second[1].as<int>(), 2);
}

TEST(NodeIteratorOperatorStarTest_187, MapDereferenceYieldsKeyValuePairs_187) {
  YAML::Node m;
  m["a"] = 1;
  m["b"] = 2;
  m["c"] = 3;

  ASSERT_TRUE(m.IsMap());
  ASSERT_EQ(m.size(), 3u);

  std::map<std::string, int> got;

  for (auto it = m.begin(); it != m.end(); ++it) {
    // Exercising YAML::detail::node_iterator_base::operator*() (Map case).
    // For yaml-cpp iterators, operator*() returns a value_type that supports .first/.second.
    const auto kv = *it;

    const std::string key = kv.first.as<std::string>();
    const int value = kv.second.as<int>();
    got[key] = value;

    // Also ensure operator-> can access the same observable data shape.
    EXPECT_EQ(it->first.as<std::string>(), key);
    EXPECT_EQ(it->second.as<int>(), value);
  }

  EXPECT_EQ(got.size(), 3u);
  EXPECT_EQ(got["a"], 1);
  EXPECT_EQ(got["b"], 2);
  EXPECT_EQ(got["c"], 3);
}

TEST(NodeIteratorOperatorStarTest_187, MapDereferenceHandlesNonScalarKeysAndValues_187) {
  YAML::Node m;

  YAML::Node keyMap;
  keyMap["id"] = 7;

  YAML::Node valueSeq;
  valueSeq.push_back("x");
  valueSeq.push_back("y");

  m[keyMap] = valueSeq;

  ASSERT_TRUE(m.IsMap());
  ASSERT_EQ(m.size(), 1u);

  auto it = m.begin();
  const auto kv = *it;

  ASSERT_TRUE(kv.first.IsMap());
  EXPECT_EQ(kv.first["id"].as<int>(), 7);

  ASSERT_TRUE(kv.second.IsSequence());
  ASSERT_EQ(kv.second.size(), 2u);
  EXPECT_EQ(kv.second[0].as<std::string>(), "x");
  EXPECT_EQ(kv.second[1].as<std::string>(), "y");
}

TEST(NodeIteratorOperatorStarTest_187, EmptySequenceBeginEqualsEnd_187) {
  YAML::Node seq(YAML::NodeType::Sequence);
  ASSERT_TRUE(seq.IsSequence());
  ASSERT_EQ(seq.size(), 0u);

  auto b = seq.begin();
  auto e = seq.end();
  EXPECT_TRUE(b == e);
  EXPECT_FALSE(b != e);

  // Boundary: do not dereference end iterators (undefined behavior).
}

TEST(NodeIteratorOperatorStarTest_187, EmptyMapBeginEqualsEnd_187) {
  YAML::Node m(YAML::NodeType::Map);
  ASSERT_TRUE(m.IsMap());
  ASSERT_EQ(m.size(), 0u);

  auto b = m.begin();
  auto e = m.end();
  EXPECT_TRUE(b == e);
  EXPECT_FALSE(b != e);

  // Boundary: do not dereference end iterators (undefined behavior).
}

}  // namespace