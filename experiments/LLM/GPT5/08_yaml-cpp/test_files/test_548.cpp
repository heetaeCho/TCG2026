// TEST_ID: 548
// File: test_node_isdefined_548.cpp

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

namespace {

class NodeIsDefinedTest_548 : public ::testing::Test {};

TEST_F(NodeIsDefinedTest_548, DefaultConstructedNodeIsDefined_548) {
  YAML::Node n;
  EXPECT_TRUE(n.IsDefined());
}

TEST_F(NodeIsDefinedTest_548, UndefinedTypeNodeIsNotDefined_548) {
  // YAML-cpp exposes an explicit Undefined node type.
  YAML::Node n(YAML::NodeType::Undefined);
  EXPECT_FALSE(n.IsDefined());
}

TEST_F(NodeIsDefinedTest_548, ValidScalarNodeIsDefined_548) {
  YAML::Node n("hello");
  EXPECT_TRUE(n.IsDefined());
}

TEST_F(NodeIsDefinedTest_548, IndexingScalarProducesInvalidOrUndefinedNode_NotDefined_548) {
  // Indexing into a scalar is an invalid operation in yaml-cpp and is expected to
  // produce a node that is not "defined" (observable via the public API).
  YAML::Node scalar("hello");
  YAML::Node child = scalar["k"];
  EXPECT_FALSE(child.IsDefined());
}

TEST_F(NodeIsDefinedTest_548, CopyOfNotDefinedNodeRemainsNotDefined_548) {
  YAML::Node scalar("hello");
  YAML::Node child = scalar["k"];
  ASSERT_FALSE(child.IsDefined());

  YAML::Node copied(child);
  EXPECT_FALSE(copied.IsDefined());
}

TEST_F(NodeIsDefinedTest_548, ChainedIndexingFromNotDefinedNodeStaysNotDefined_548) {
  YAML::Node scalar("hello");
  YAML::Node bad = scalar["k"];
  ASSERT_FALSE(bad.IsDefined());

  YAML::Node bad2 = bad["another"];
  EXPECT_FALSE(bad2.IsDefined());
}

TEST_F(NodeIsDefinedTest_548, MapElementAfterAssignmentIsDefined_548) {
  YAML::Node map(YAML::NodeType::Map);

  map["a"] = 1;
  YAML::Node a = map["a"];

  EXPECT_TRUE(map.IsDefined());
  EXPECT_TRUE(a.IsDefined());
}

TEST_F(NodeIsDefinedTest_548, MissingMapKeyNodeIsStillDefined_548) {
  // Accessing a missing key from a map returns a node; whether it is defined can be
  // checked only via the public API. In yaml-cpp, this is typically a "defined" node
  // that can later be assigned into.
  YAML::Node map(YAML::NodeType::Map);

  YAML::Node missing = map["does_not_exist_yet"];
  // The key point for this test is that the call is safe and the result is observable.
  // We assert the common yaml-cpp behavior that such a node is still "defined".
  EXPECT_TRUE(missing.IsDefined());

  // And after assignment it must be defined.
  missing = 42;
  EXPECT_TRUE(missing.IsDefined());
  EXPECT_TRUE(map["does_not_exist_yet"].IsDefined());
}

}  // namespace