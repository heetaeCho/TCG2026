// TEST_ID: 610
#include <gtest/gtest.h>

#include <string>
#include <unordered_map>

#include <yaml-cpp/node/convert.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/exceptions.h>

namespace {

class DecodeUnorderedMapTest_610 : public ::testing::Test {};

TEST_F(DecodeUnorderedMapTest_610, NonMapNodeReturnsFalseAndDoesNotModifyRhs_610) {
  YAML::Node scalar("not_a_map");

  std::unordered_map<std::string, int> rhs;
  rhs["keep"] = 123;

  const bool ok = YAML::convert<std::unordered_map<std::string, int>>::decode(scalar, rhs);

  EXPECT_FALSE(ok);
  ASSERT_EQ(rhs.size(), 1u);
  EXPECT_EQ(rhs.at("keep"), 123);
}

TEST_F(DecodeUnorderedMapTest_610, MapNodeClearsAndPopulatesRhs_610) {
  YAML::Node node(YAML::NodeType::Map);
  node["a"] = 1;
  node["b"] = 2;

  std::unordered_map<std::string, int> rhs;
  rhs["old"] = 999;

  const bool ok = YAML::convert<std::unordered_map<std::string, int>>::decode(node, rhs);

  EXPECT_TRUE(ok);
  ASSERT_EQ(rhs.size(), 2u);
  EXPECT_EQ(rhs.at("a"), 1);
  EXPECT_EQ(rhs.at("b"), 2);
  EXPECT_TRUE(rhs.find("old") == rhs.end());
}

TEST_F(DecodeUnorderedMapTest_610, EmptyMapClearsRhsAndReturnsTrue_610) {
  YAML::Node node(YAML::NodeType::Map);

  std::unordered_map<std::string, int> rhs;
  rhs["x"] = 7;

  const bool ok = YAML::convert<std::unordered_map<std::string, int>>::decode(node, rhs);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(rhs.empty());
}

TEST_F(DecodeUnorderedMapTest_610, DecodesStringToStringMap_610) {
  YAML::Node node(YAML::NodeType::Map);
  node["k1"] = "v1";
  node["k2"] = "v2";

  std::unordered_map<std::string, std::string> rhs;
  rhs["old"] = "oldv";

  const bool ok =
      YAML::convert<std::unordered_map<std::string, std::string>>::decode(node, rhs);

  EXPECT_TRUE(ok);
  ASSERT_EQ(rhs.size(), 2u);
  EXPECT_EQ(rhs.at("k1"), "v1");
  EXPECT_EQ(rhs.at("k2"), "v2");
}

TEST_F(DecodeUnorderedMapTest_610, ValueConversionFailurePropagatesAsException_610) {
  YAML::Node node(YAML::NodeType::Map);
  node["a"] = "not_an_int";

  std::unordered_map<std::string, int> rhs;
  rhs["preexisting"] = 5;

  // decode() uses Node::as<V>() for values; conversion failures are observable via exceptions.
  EXPECT_THROW(
      (YAML::convert<std::unordered_map<std::string, int>>::decode(node, rhs)),
      YAML::BadConversion);
}

TEST_F(DecodeUnorderedMapTest_610, KeyConversionFailurePropagatesAsException_610) {
  YAML::Node node(YAML::NodeType::Map);
  node["not_an_int_key"] = 1;

  std::unordered_map<int, int> rhs;
  rhs[1] = 10;

  // decode() uses Node::as<K>() for keys; conversion failures are observable via exceptions.
  EXPECT_THROW((YAML::convert<std::unordered_map<int, int>>::decode(node, rhs)),
               YAML::BadConversion);
}

TEST_F(DecodeUnorderedMapTest_610, LargeMapDecodesAllEntries_610) {
  YAML::Node node(YAML::NodeType::Map);
  for (int i = 0; i < 100; ++i) {
    node[std::to_string(i)] = i * 10;
  }

  std::unordered_map<std::string, int> rhs;
  rhs["old"] = -1;

  const bool ok = YAML::convert<std::unordered_map<std::string, int>>::decode(node, rhs);

  EXPECT_TRUE(ok);
  ASSERT_EQ(rhs.size(), 100u);
  EXPECT_EQ(rhs.at("0"), 0);
  EXPECT_EQ(rhs.at("1"), 10);
  EXPECT_EQ(rhs.at("42"), 420);
  EXPECT_EQ(rhs.at("99"), 990);
  EXPECT_TRUE(rhs.find("old") == rhs.end());
}

}  // namespace