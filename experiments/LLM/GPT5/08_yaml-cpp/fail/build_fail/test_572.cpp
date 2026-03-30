// TEST_ID: 572
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/node.h"

namespace {

class NodeOperatorIndexConstTest_572 : public ::testing::Test {
 protected:
  static YAML::Node MakeMapWithOneEntry(const std::string& key,
                                       const std::string& value) {
    YAML::Node n(YAML::NodeType::Map);
    n.force_insert(key, value);
    return n;
  }
};

TEST_F(NodeOperatorIndexConstTest_572, ExistingKeyReturnsDefinedScalarNode_572) {
  YAML::Node n = MakeMapWithOneEntry("a", "1");
  const YAML::Node cn = n;

  YAML::Node v;
  ASSERT_NO_THROW(v = cn["a"]);

  EXPECT_TRUE(v.IsDefined());
  EXPECT_TRUE(v.IsScalar());
  EXPECT_EQ(v.as<std::string>(), "1");
  EXPECT_EQ(v.Scalar(), "1");
}

TEST_F(NodeOperatorIndexConstTest_572, MissingKeyReturnsUndefinedAndFallbackWorks_572) {
  YAML::Node n = MakeMapWithOneEntry("present", "value");
  const YAML::Node cn = n;

  YAML::Node missing;
  ASSERT_NO_THROW(missing = cn["absent"]);

  // Observable behavior for a missing key: the returned node should be non-defined,
  // and conversions with fallback should return the fallback.
  EXPECT_FALSE(missing.IsDefined());
  EXPECT_FALSE(static_cast<bool>(missing));
  EXPECT_EQ(missing.as<std::string>("fallback"), "fallback");
}

TEST_F(NodeOperatorIndexConstTest_572, IndexingEmptyMapDoesNotThrowAndReturnsUsableNode_572) {
  const YAML::Node emptyMap(YAML::NodeType::Map);

  YAML::Node v;
  EXPECT_NO_THROW(v = emptyMap["x"]);

  // Even if the key is missing, the returned node must be safe to query via the public API.
  EXPECT_NO_THROW((void)v.IsDefined());
  EXPECT_NO_THROW((void)static_cast<bool>(v));
  EXPECT_NO_THROW((void)v.as<std::string>("fallback"));
}

TEST_F(NodeOperatorIndexConstTest_572, DifferentKeyTypesFindSameEntry_572) {
  YAML::Node n(YAML::NodeType::Map);
  n.force_insert(std::string("k"), "v");
  const YAML::Node cn = n;

  const YAML::Node byConstChar = cn["k"];
  const YAML::Node byString = cn[std::string("k")];

  ASSERT_TRUE(byConstChar.IsDefined());
  ASSERT_TRUE(byString.IsDefined());
  EXPECT_EQ(byConstChar.as<std::string>(), "v");
  EXPECT_EQ(byString.as<std::string>(), "v");
}

TEST_F(NodeOperatorIndexConstTest_572, IndexingNonMapNodeDoesNotThrowAndFallbackWorks_572) {
  const YAML::Node scalar("scalar-value");

  YAML::Node v;
  EXPECT_NO_THROW(v = scalar["any-key"]);

  // For non-map nodes, indexing should be safe; if it doesn't produce a defined node,
  // fallback conversion should still behave sensibly.
  EXPECT_EQ(v.as<std::string>("fallback"), "fallback");
}

TEST_F(NodeOperatorIndexConstTest_572, AccessingMissingKeyDoesNotBreakExistingKeyAccess_572) {
  YAML::Node n(YAML::NodeType::Map);
  n.force_insert("a", "1");
  n.force_insert("b", "2");
  const YAML::Node cn = n;

  // Touch a missing key first.
  YAML::Node missing;
  ASSERT_NO_THROW(missing = cn["missing"]);
  (void)missing.as<std::string>("fallback");  // Should be safe regardless.

  // Existing keys should still be retrievable and correct.
  EXPECT_EQ(cn["a"].as<std::string>(), "1");
  EXPECT_EQ(cn["b"].as<std::string>(), "2");
}

}  // namespace