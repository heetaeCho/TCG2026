// TEST_ID: 196
#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

namespace {

class NodeOperatorNotTest_196 : public ::testing::Test {};

TEST_F(NodeOperatorNotTest_196, NegatesIsDefined_DefaultConstructed_196) {
  YAML::Node n;
  EXPECT_EQ(!n, !n.IsDefined());
}

TEST_F(NodeOperatorNotTest_196, NegatesIsDefined_ScalarConstructed_196) {
  YAML::Node n("hello");
  EXPECT_EQ(!n, !n.IsDefined());
}

TEST_F(NodeOperatorNotTest_196, NegatesIsDefined_MapMissingKeyResult_196) {
  YAML::Node m(YAML::NodeType::Map);

  const YAML::Node missing = m["no_such_key"];
  EXPECT_EQ(!missing, !missing.IsDefined());
}

TEST_F(NodeOperatorNotTest_196, NegatesIsDefined_SequenceOutOfRangeIndexResult_196) {
  YAML::Node s(YAML::NodeType::Sequence);

  const YAML::Node idx0 = s[0];
  EXPECT_EQ(!idx0, !idx0.IsDefined());
}

TEST_F(NodeOperatorNotTest_196, NegatesIsDefined_AfterReset_196) {
  YAML::Node src("value");
  YAML::Node dst;
  dst.reset(src);

  EXPECT_EQ(!dst, !dst.IsDefined());
}

TEST_F(NodeOperatorNotTest_196, WorksOnConstNode_196) {
  const YAML::Node n("const-value");
  const bool op_not = !n;
  EXPECT_EQ(op_not, !n.IsDefined());
}

}  // namespace