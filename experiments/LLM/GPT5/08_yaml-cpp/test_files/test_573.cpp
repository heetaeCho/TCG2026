// File: test/node_remove_test_573.cpp

#include <gtest/gtest.h>

#include <string>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/exceptions.h>

namespace {

class NodeRemoveTest_573 : public ::testing::Test {};

TEST_F(NodeRemoveTest_573, RemoveExistingStringKeyReturnsTrueAndErases_573) {
  YAML::Node n(YAML::NodeType::Map);
  n.force_insert("a", 1);
  n.force_insert("b", 2);

  ASSERT_EQ(n.size(), 2u);

  EXPECT_TRUE(n.remove("a"));
  EXPECT_EQ(n.size(), 1u);

  // Observable behavior through public API: key should no longer be defined.
  EXPECT_FALSE(n["a"].IsDefined());
  EXPECT_TRUE(n["b"].IsDefined());

  // Removing the same key again should be observable as "not removed".
  EXPECT_FALSE(n.remove("a"));
  EXPECT_EQ(n.size(), 1u);
}

TEST_F(NodeRemoveTest_573, RemoveMissingKeyReturnsFalseAndDoesNotChangeSize_573) {
  YAML::Node n(YAML::NodeType::Map);
  n.force_insert("present", 123);

  ASSERT_EQ(n.size(), 1u);

  EXPECT_FALSE(n.remove("absent"));
  EXPECT_EQ(n.size(), 1u);

  EXPECT_TRUE(n["present"].IsDefined());
  EXPECT_FALSE(n["absent"].IsDefined());
}

TEST_F(NodeRemoveTest_573, RemoveOnEmptyMapReturnsFalse_573) {
  YAML::Node n(YAML::NodeType::Map);
  ASSERT_EQ(n.size(), 0u);

  EXPECT_FALSE(n.remove("nope"));
  EXPECT_EQ(n.size(), 0u);
  EXPECT_FALSE(n["nope"].IsDefined());
}

TEST_F(NodeRemoveTest_573, RemoveWithStdStringKeyWorks_573) {
  YAML::Node n(YAML::NodeType::Map);
  const std::string key = "k";
  n.force_insert(key, "v");

  ASSERT_EQ(n.size(), 1u);
  EXPECT_TRUE(n["k"].IsDefined());

  EXPECT_TRUE(n.remove(key));
  EXPECT_EQ(n.size(), 0u);
  EXPECT_FALSE(n["k"].IsDefined());
}

TEST_F(NodeRemoveTest_573, RemoveWithIntegralKeyWorks_573) {
  YAML::Node n(YAML::NodeType::Map);
  n.force_insert(1, "one");
  n.force_insert(2, "two");

  ASSERT_EQ(n.size(), 2u);

  EXPECT_TRUE(n.remove(1));
  EXPECT_EQ(n.size(), 1u);

  EXPECT_FALSE(n[1].IsDefined());
  EXPECT_TRUE(n[2].IsDefined());
}

TEST_F(NodeRemoveTest_573, RemoveOnDefaultConstructedNodeDoesNotThrow_573) {
  YAML::Node n;  // default constructed

  bool removed = true;  // set opposite to ensure assignment happens
  EXPECT_NO_THROW(removed = n.remove("anything"));
  EXPECT_FALSE(removed);

  // Regardless of internal representation, size() is an observable query.
  EXPECT_EQ(n.size(), 0u);
}

TEST_F(NodeRemoveTest_573, RemoveOnInvalidNodeThrowsYamlException_573) {
  YAML::Node root(YAML::NodeType::Map);
  root.force_insert("exists", 1);

  // Create an invalid node via const operator[] on a missing key.
  const YAML::Node& croot = root;
  YAML::Node invalid = croot["missing"];

  ASSERT_FALSE(invalid.IsDefined());

  // Observable error case: operations on an invalid node are expected to throw.
  EXPECT_THROW(invalid.remove("anything"), YAML::Exception);
}

}  // namespace