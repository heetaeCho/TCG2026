// TEST_ID: 607
//
// Unit tests for YAML::convert<std::map<...>>::encode
// File under test: yaml-cpp/node/convert.h

#include <gtest/gtest.h>

#include <map>
#include <string>

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/convert.h>

namespace {

struct ReverseStringLess_607 {
  bool operator()(const std::string& a, const std::string& b) const { return a > b; }
};

}  // namespace

TEST(ConvertMapEncodeTest_607, EmptyMapEncodesToEmptyMapNode_607) {
  const std::map<std::string, int> input;

  const YAML::Node node = YAML::convert<std::map<std::string, int>>::encode(input);

  EXPECT_TRUE(node.IsDefined());
  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ(node.size(), 0u);
}

TEST(ConvertMapEncodeTest_607, StringIntMapEncodesAllEntries_607) {
  const std::map<std::string, int> input{
      {"a", 1},
      {"b", 2},
      {"c", 3},
  };

  const YAML::Node node = YAML::convert<std::map<std::string, int>>::encode(input);

  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ(node.size(), input.size());

  EXPECT_EQ(node["a"].as<int>(), 1);
  EXPECT_EQ(node["b"].as<int>(), 2);
  EXPECT_EQ(node["c"].as<int>(), 3);
}

TEST(ConvertMapEncodeTest_607, IntStringMapEncodesAllEntries_607) {
  const std::map<int, std::string> input{
      {1, "one"},
      {2, "two"},
      {42, "forty-two"},
  };

  const YAML::Node node = YAML::convert<std::map<int, std::string>>::encode(input);

  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ(node.size(), input.size());

  EXPECT_EQ(node[1].as<std::string>(), "one");
  EXPECT_EQ(node[2].as<std::string>(), "two");
  EXPECT_EQ(node[42].as<std::string>(), "forty-two");
}

TEST(ConvertMapEncodeTest_607, CustomComparatorMapEncodesEntries_607) {
  const std::map<std::string, int, ReverseStringLess_607> input{
      {"alpha", 10},
      {"beta", 20},
      {"gamma", 30},
  };

  using MapType = std::map<std::string, int, ReverseStringLess_607>;
  const YAML::Node node = YAML::convert<MapType>::encode(input);

  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ(node.size(), input.size());

  // Order is not asserted (black-box). Only presence/value correctness.
  EXPECT_EQ(node["alpha"].as<int>(), 10);
  EXPECT_EQ(node["beta"].as<int>(), 20);
  EXPECT_EQ(node["gamma"].as<int>(), 30);
}

TEST(ConvertMapEncodeTest_607, EncodeDoesNotDependOnMapLifetimeAfterCall_607) {
  std::map<std::string, int> input{
      {"x", 100},
      {"y", 200},
  };

  const YAML::Node node = YAML::convert<std::map<std::string, int>>::encode(input);

  // Mutate the original map after encoding.
  input["x"] = 999;
  input.erase("y");
  input["z"] = 300;

  // The encoded node should still reflect what was encoded at the time of the call.
  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ(node.size(), 2u);
  EXPECT_EQ(node["x"].as<int>(), 100);
  EXPECT_EQ(node["y"].as<int>(), 200);
}

TEST(ConvertMapEncodeTest_607, LargerMapEncodesCorrectSizeAndSampledValues_607) {
  std::map<int, int> input;
  for (int i = 0; i < 1000; ++i) {
    input.emplace(i, i * i);
  }

  const YAML::Node node = YAML::convert<std::map<int, int>>::encode(input);

  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ(node.size(), input.size());

  // Sample a few keys for correctness (avoid asserting anything about iteration order).
  EXPECT_EQ(node[0].as<int>(), 0);
  EXPECT_EQ(node[1].as<int>(), 1);
  EXPECT_EQ(node[10].as<int>(), 100);
  EXPECT_EQ(node[123].as<int>(), 15129);
  EXPECT_EQ(node[999].as<int>(), 998001);
}