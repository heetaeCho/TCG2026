// TEST_ID: 199
#include <gtest/gtest.h>

#include <string>
#include <type_traits>

// Prefer the public yaml-cpp API; it exercises YAML::detail::iterator_base internally.
#include <yaml-cpp/yaml.h>

namespace {

class IteratorBaseTest_199 : public ::testing::Test {};

TEST_F(IteratorBaseTest_199, PreIncrementAdvancesAndReturnsSelf_199) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(1);
  seq.push_back(2);
  seq.push_back(3);

  YAML::Node::iterator it = seq.begin();
  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 1);

  // operator++() should return *this (a reference to the same iterator object).
  auto* addr_before = std::addressof(it);
  YAML::Node::iterator& ret = ++it;
  EXPECT_EQ(std::addressof(ret), addr_before);

  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 2);
}

TEST_F(IteratorBaseTest_199, PostIncrementReturnsOldValueAndAdvances_199) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(10);
  seq.push_back(20);

  YAML::Node::iterator it = seq.begin();
  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 10);

  YAML::Node::iterator old = it++;
  ASSERT_NE(old, seq.end());
  EXPECT_EQ(old->as<int>(), 10);

  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 20);

  EXPECT_NE(old, it);
}

TEST_F(IteratorBaseTest_199, IncrementReachesEndOnSingleElementSequence_199) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back("only");

  YAML::Node::iterator it = seq.begin();
  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<std::string>(), "only");

  ++it;
  EXPECT_EQ(it, seq.end());
}

TEST_F(IteratorBaseTest_199, WorksForMapIterationWithArrowAndIncrement_199) {
  YAML::Node map(YAML::NodeType::Map);
  map["a"] = 1;
  map["b"] = 2;

  YAML::Node::iterator it = map.begin();
  YAML::Node::iterator end = map.end();
  ASSERT_NE(it, end);

  // operator->() should provide access to key/value pair for map iterators.
  const std::string k1 = it->first.as<std::string>();
  const int v1 = it->second.as<int>();

  ++it;
  if (it != end) {
    const std::string k2 = it->first.as<std::string>();
    const int v2 = it->second.as<int>();

    // Keys should be different between two distinct elements (order not assumed).
    EXPECT_NE(k1, k2);

    // Values should correspond to inserted content (order not assumed).
    const bool first_ok = (k1 == "a" && v1 == 1) || (k1 == "b" && v1 == 2);
    const bool second_ok = (k2 == "a" && v2 == 1) || (k2 == "b" && v2 == 2);
    EXPECT_TRUE(first_ok);
    EXPECT_TRUE(second_ok);
  }
}

TEST_F(IteratorBaseTest_199, IteratorConvertibleToConstIterator_199) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(7);
  seq.push_back(8);

  YAML::Node::iterator it = seq.begin();
  ASSERT_NE(it, seq.end());

  // This exercises the templated converting copy constructor path (iterator -> const_iterator).
  YAML::Node::const_iterator cit(it);
  ASSERT_NE(cit, seq.end());
  EXPECT_EQ(cit->as<int>(), it->as<int>());

  ++it;
  ++cit;
  if (it != seq.end() && cit != seq.end()) {
    EXPECT_EQ(cit->as<int>(), it->as<int>());
  }
}

}  // namespace