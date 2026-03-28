// test_node_scalar_557.cpp
#include <gtest/gtest.h>

#include <string>

// Prefer the public umbrella header used by most yaml-cpp users.
#include <yaml-cpp/yaml.h>

namespace {

class NodeScalarTest_557 : public ::testing::Test {};

TEST_F(NodeScalarTest_557, DefaultConstructedNodeReturnsEmptyScalar_557) {
  const YAML::Node n;
  // For a default node, Scalar() should be observable and not throw.
  EXPECT_NO_THROW({
    const std::string& s = n.Scalar();
    EXPECT_TRUE(s.empty());
  });
}

TEST_F(NodeScalarTest_557, ConstructedFromStdStringReturnsSameScalar_557) {
  const YAML::Node n(std::string("hello"));
  const std::string& s = n.Scalar();
  EXPECT_EQ(s, "hello");
}

TEST_F(NodeScalarTest_557, ConstructedFromCStringReturnsSameScalar_557) {
  const YAML::Node n("world");
  const std::string& s = n.Scalar();
  EXPECT_EQ(s, "world");
}

TEST_F(NodeScalarTest_557, ConstructedFromEmptyStringReturnsEmptyScalar_557) {
  const YAML::Node n(std::string(""));
  const std::string& s = n.Scalar();
  EXPECT_TRUE(s.empty());
}

TEST_F(NodeScalarTest_557, ScalarReferenceIsStableAcrossCallsForScalarNode_557) {
  const YAML::Node n("stable");
  const std::string& a = n.Scalar();
  const std::string& b = n.Scalar();
  EXPECT_EQ(&a, &b);  // same referenced string object across calls
  EXPECT_EQ(a, "stable");
}

TEST_F(NodeScalarTest_557, ScalarReferenceIsStableAcrossCallsForDefaultNode_557) {
  const YAML::Node n;
  const std::string& a = n.Scalar();
  const std::string& b = n.Scalar();
  EXPECT_EQ(&a, &b);
  EXPECT_TRUE(a.empty());
}

TEST_F(NodeScalarTest_557, ScalarOnInvalidNodeThrowsInvalidNode_557) {
  // Create an invalid node through observable public API: indexing into an
  // undefined node typically yields an invalid node in yaml-cpp.
  const YAML::Node root;            // default/undefined-ish handle
  const YAML::Node invalid = root["missing_key_557"];

  EXPECT_THROW(
      {
        (void)invalid.Scalar();
      },
      YAML::InvalidNode);
}

TEST_F(NodeScalarTest_557, ScalarOnNestedInvalidNodeThrowsInvalidNode_557) {
  const YAML::Node root;
  const YAML::Node invalid = root["a"]["b"]["c"];

  EXPECT_THROW(
      {
        (void)invalid.Scalar();
      },
      YAML::InvalidNode);
}

}  // namespace