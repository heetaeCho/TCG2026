// TEST_ID: 195
// File: test/node_bool_operator_test_195.cpp

#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>  // Brings in YAML::Node and NodeType

namespace {

class NodeBoolConversionTest_195 : public ::testing::Test {};

TEST_F(NodeBoolConversionTest_195, BoolConversionMatchesIsDefined_DefaultConstructed_195) {
  const YAML::Node n;
  EXPECT_EQ(static_cast<bool>(n), n.IsDefined());
}

TEST_F(NodeBoolConversionTest_195, BoolConversionMatchesIsDefined_NullTypedNode_195) {
  const YAML::Node n(YAML::NodeType::Null);
  EXPECT_EQ(static_cast<bool>(n), n.IsDefined());
}

TEST_F(NodeBoolConversionTest_195, BoolConversionMatchesIsDefined_ScalarConstructedFromInt_195) {
  const YAML::Node n(42);
  EXPECT_EQ(static_cast<bool>(n), n.IsDefined());
}

TEST_F(NodeBoolConversionTest_195, BoolConversionMatchesIsDefined_ScalarConstructedFromString_195) {
  const YAML::Node n(std::string("hello"));
  EXPECT_EQ(static_cast<bool>(n), n.IsDefined());
}

TEST_F(NodeBoolConversionTest_195, BoolConversionMatchesIsDefined_CopyConstructed_195) {
  const YAML::Node original(7);
  const YAML::Node copy(original);
  EXPECT_EQ(static_cast<bool>(copy), copy.IsDefined());
  EXPECT_EQ(static_cast<bool>(copy), static_cast<bool>(original));
  EXPECT_EQ(copy.IsDefined(), original.IsDefined());
}

TEST_F(NodeBoolConversionTest_195, OperatorNotIsLogicalNegationOfBoolConversion_195) {
  const YAML::Node n;
  EXPECT_EQ(!n, !static_cast<bool>(n));
  EXPECT_EQ(!n, !n.IsDefined());
}

TEST_F(NodeBoolConversionTest_195, BoolConversionWorksInIfConditionConsistentWithIsDefined_195) {
  const YAML::Node n;
  const bool defined = n.IsDefined();

  bool took_true_branch = false;
  if (n) {
    took_true_branch = true;
  }

  EXPECT_EQ(took_true_branch, defined);
  EXPECT_EQ(took_true_branch, static_cast<bool>(n));
}

TEST_F(NodeBoolConversionTest_195, BoolConversionWorksInTernaryConsistentWithIsDefined_195) {
  const YAML::Node n;
  const int v = n ? 1 : 0;
  EXPECT_EQ(v, n.IsDefined() ? 1 : 0);
  EXPECT_EQ(v, static_cast<bool>(n) ? 1 : 0);
}

}  // namespace