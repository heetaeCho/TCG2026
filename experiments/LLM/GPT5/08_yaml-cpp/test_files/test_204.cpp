// TEST_ID: 204
#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

namespace {

class IteratorBaseOperatorArrowTest_204 : public ::testing::Test {};

TEST_F(IteratorBaseOperatorArrowTest_204, MapIteratorArrowAccessMatchesDereference_204) {
  YAML::Node n;
  n["a"] = 1;
  n["b"] = 2;

  auto it = n.begin();
  ASSERT_NE(it, n.end());

  // operator-> should provide access equivalent to dereferencing the iterator.
  EXPECT_EQ(it->first.as<std::string>(), (*it).first.as<std::string>());
  EXPECT_EQ(it->second.as<int>(), (*it).second.as<int>());

  ++it;
  ASSERT_NE(it, n.end());
  EXPECT_EQ(it->first.as<std::string>(), (*it).first.as<std::string>());
  EXPECT_EQ(it->second.as<int>(), (*it).second.as<int>());
}

TEST_F(IteratorBaseOperatorArrowTest_204, SequenceIteratorArrowAccessMatchesDereference_204) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(10);
  seq.push_back(20);

  auto it = seq.begin();
  ASSERT_NE(it, seq.end());

  // For sequences, iterators behave like iterators over nodes; -> should match *.
  EXPECT_EQ(it->as<int>(), (*it).as<int>());

  ++it;
  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), (*it).as<int>());
}

TEST_F(IteratorBaseOperatorArrowTest_204, ConstMapIteratorArrowAccessMatchesDereference_204) {
  YAML::Node n;
  n["k"] = "v";

  const YAML::Node& cn = n;
  auto it = cn.begin();
  ASSERT_NE(it, cn.end());

  EXPECT_EQ(it->first.as<std::string>(), (*it).first.as<std::string>());
  EXPECT_EQ(it->second.as<std::string>(), (*it).second.as<std::string>());
}

TEST_F(IteratorBaseOperatorArrowTest_204, ProxyFromOperatorArrowIsUsable_204) {
  YAML::Node n;
  n["x"] = 42;

  auto it = n.begin();
  ASSERT_NE(it, n.end());

  // Capture the proxy returned by operator-> and ensure it can be used.
  auto proxy = it.operator->();
  EXPECT_EQ(proxy->first.as<std::string>(), (*it).first.as<std::string>());
  EXPECT_EQ(proxy->second.as<int>(), (*it).second.as<int>());
}

TEST_F(IteratorBaseOperatorArrowTest_204, ArrowOperatorDoesNotChangeIteratorPosition_204) {
  YAML::Node n;
  n["p"] = 1;
  n["q"] = 2;

  auto it = n.begin();
  ASSERT_NE(it, n.end());

  const auto k1 = (*it).first.as<std::string>();
  (void)it->first.as<std::string>();   // access via operator->
  (void)it->second.as<int>();          // access via operator->
  const auto k2 = (*it).first.as<std::string>();

  // Accessing via -> should not advance or alter which element the iterator refers to.
  EXPECT_EQ(k1, k2);
}

}  // namespace