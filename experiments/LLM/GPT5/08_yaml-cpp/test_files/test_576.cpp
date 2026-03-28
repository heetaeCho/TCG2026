// TEST_ID: 576
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

namespace {

class NodeForceInsertTest_576 : public ::testing::Test {
protected:
  static YAML::Node MakeMap() { return YAML::Node(YAML::NodeType::Map); }
};

TEST_F(NodeForceInsertTest_576, ForceInsertIntoEmptyMapCreatesEntry_576) {
  YAML::Node n = MakeMap();
  ASSERT_TRUE(n.IsMap());
  EXPECT_EQ(n.size(), 0u);

  n.force_insert(std::string("k"), std::string("v"));

  EXPECT_TRUE(n.IsMap());
  EXPECT_EQ(n.size(), 1u);

  const YAML::Node v = n["k"];
  EXPECT_TRUE(v.IsDefined());
  EXPECT_TRUE(v.IsScalar());
  EXPECT_EQ(v.as<std::string>(), "v");
}

TEST_F(NodeForceInsertTest_576, ForceInsertMultipleDistinctKeysIncreasesSizeAndRetrievesValues_576) {
  YAML::Node n = MakeMap();
  EXPECT_EQ(n.size(), 0u);

  n.force_insert(std::string("a"), 1);
  n.force_insert(std::string("b"), 2);
  n.force_insert(std::string("c"), 3);

  EXPECT_EQ(n.size(), 3u);

  EXPECT_TRUE(n["a"].IsDefined());
  EXPECT_TRUE(n["b"].IsDefined());
  EXPECT_TRUE(n["c"].IsDefined());

  EXPECT_EQ(n["a"].as<int>(), 1);
  EXPECT_EQ(n["b"].as<int>(), 2);
  EXPECT_EQ(n["c"].as<int>(), 3);
}

TEST_F(NodeForceInsertTest_576, ForceInsertAcceptsEmptyStringKey_576) {
  YAML::Node n = MakeMap();

  n.force_insert(std::string(""), std::string("empty"));

  EXPECT_GE(n.size(), 1u);  // key presence is the key observable here
  const YAML::Node v = n[std::string("")];
  EXPECT_TRUE(v.IsDefined());
  EXPECT_TRUE(v.IsScalar());
  EXPECT_EQ(v.as<std::string>(), "empty");
}

TEST_F(NodeForceInsertTest_576, ForceInsertAcceptsNonStringKeyType_576) {
  YAML::Node n = MakeMap();

  // Key type is templated; verify an integral key can be inserted and retrieved
  // using the same key type through operator[].
  n.force_insert(42, std::string("answer"));

  EXPECT_GE(n.size(), 1u);
  const YAML::Node v = n[42];
  EXPECT_TRUE(v.IsDefined());
  EXPECT_TRUE(v.IsScalar());
  EXPECT_EQ(v.as<std::string>(), "answer");
}

TEST_F(NodeForceInsertTest_576, ForceInsertWithNodeValueStoresThatNode_576) {
  YAML::Node n = MakeMap();

  YAML::Node valueNode("payload");
  n.force_insert(std::string("key"), valueNode);

  const YAML::Node out = n["key"];
  EXPECT_TRUE(out.IsDefined());
  EXPECT_TRUE(out.IsScalar());
  EXPECT_EQ(out.as<std::string>(), "payload");
}

TEST_F(NodeForceInsertTest_576, ForceInsertDoesNotRemoveExistingOtherKeys_576) {
  YAML::Node n = MakeMap();

  n.force_insert(std::string("keep"), std::string("x"));
  n.force_insert(std::string("add"), std::string("y"));

  EXPECT_TRUE(n["keep"].IsDefined());
  EXPECT_TRUE(n["add"].IsDefined());
  EXPECT_EQ(n["keep"].as<std::string>(), "x");
  EXPECT_EQ(n["add"].as<std::string>(), "y");

  // Re-inserting an unrelated key should not invalidate existing keys.
  n.force_insert(std::string("another"), std::string("z"));

  EXPECT_TRUE(n["keep"].IsDefined());
  EXPECT_TRUE(n["add"].IsDefined());
  EXPECT_TRUE(n["another"].IsDefined());
  EXPECT_EQ(n["keep"].as<std::string>(), "x");
  EXPECT_EQ(n["add"].as<std::string>(), "y");
  EXPECT_EQ(n["another"].as<std::string>(), "z");
}

}  // namespace