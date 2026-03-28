// TEST_ID: 574
// File: test/node/operator_index_node_tests_574.cpp

#include <gtest/gtest.h>

#include <string>

// Include the public YAML::Node interface
#include "yaml-cpp/node/node.h"

namespace {

class NodeOperatorIndexNodeTest_574 : public ::testing::Test {
 protected:
  YAML::Node MakeMapWithStringKeyValue(const std::string& key, int value) {
    YAML::Node n(YAML::NodeType::Map);
    n.force_insert(key, value);
    return n;
  }

  YAML::Node MakeMapWithIntKeyValue(int key, const std::string& value) {
    YAML::Node n(YAML::NodeType::Map);
    n.force_insert(key, value);
    return n;
  }
};

TEST_F(NodeOperatorIndexNodeTest_574, ExistingStringKeyReturnsValue_574) {
  YAML::Node map = MakeMapWithStringKeyValue("a", 42);
  const YAML::Node& cmap = map;

  const YAML::Node keyNode("a");
  const YAML::Node valueNode = cmap[keyNode];

  EXPECT_TRUE(valueNode.IsDefined());
  EXPECT_EQ(valueNode.as<int>(), 42);
}

TEST_F(NodeOperatorIndexNodeTest_574, ExistingIntKeyReturnsValue_574) {
  YAML::Node map = MakeMapWithIntKeyValue(7, "seven");
  const YAML::Node& cmap = map;

  const YAML::Node keyNode(7);
  const YAML::Node valueNode = cmap[keyNode];

  EXPECT_TRUE(valueNode.IsDefined());
  EXPECT_EQ(valueNode.as<std::string>(), "seven");
}

TEST_F(NodeOperatorIndexNodeTest_574, MissingKeyReturnsUndefinedNode_574) {
  YAML::Node map = MakeMapWithStringKeyValue("present", 1);
  const YAML::Node& cmap = map;

  const YAML::Node missingKey("absent");
  const YAML::Node missingValue = cmap[missingKey];

  EXPECT_FALSE(missingValue.IsDefined());
  // Do not assume more about the returned "zombie"/undefined node than what the interface exposes.
}

TEST_F(NodeOperatorIndexNodeTest_574, IndexingNonMapDoesNotCrashAndYieldsUndefined_574) {
  const YAML::Node scalarNode("scalar");
  const YAML::Node keyNode("k");

  YAML::Node out;
  EXPECT_NO_THROW(out = scalarNode[keyNode]);

  EXPECT_FALSE(out.IsDefined());
}

TEST_F(NodeOperatorIndexNodeTest_574, UsingInvalidKeyNodeAsKeyThrowsStdException_574) {
  // Create an invalid (undefined/zombie) node via a missing lookup.
  YAML::Node map = MakeMapWithStringKeyValue("a", 1);
  const YAML::Node& cmap = map;

  const YAML::Node invalidKey = cmap[YAML::Node("missing")];
  ASSERT_FALSE(invalidKey.IsDefined());

  // Observable error case: indexing with an invalid key node should surface an error.
  EXPECT_THROW(
      {
        (void)cmap[invalidKey];
      },
      std::exception);
}

}  // namespace