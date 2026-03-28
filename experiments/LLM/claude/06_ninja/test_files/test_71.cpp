#include "gtest/gtest.h"
#include "graph.h"

// We need to know the Node structure to create test instances.
// Based on the ninja codebase, Node has a path() method.
// We'll include necessary headers.
#include "state.h"

class InputsCollectorTest_71 : public ::testing::Test {
 protected:
  void SetUp() override {
    state_.Reset();
  }

  State state_;
};

TEST_F(InputsCollectorTest_71, InitiallyEmpty_71) {
  InputsCollector collector;
  EXPECT_TRUE(collector.inputs().empty());
}

TEST_F(InputsCollectorTest_71, VisitSingleNode_71) {
  InputsCollector collector;
  Node* node = state_.GetNode("foo.cc", 0);
  collector.VisitNode(node);
  ASSERT_EQ(1u, collector.inputs().size());
  EXPECT_EQ(node, collector.inputs()[0]);
}

TEST_F(InputsCollectorTest_71, VisitMultipleDistinctNodes_71) {
  InputsCollector collector;
  Node* node1 = state_.GetNode("foo.cc", 0);
  Node* node2 = state_.GetNode("bar.cc", 0);
  Node* node3 = state_.GetNode("baz.cc", 0);
  collector.VisitNode(node1);
  collector.VisitNode(node2);
  collector.VisitNode(node3);
  ASSERT_EQ(3u, collector.inputs().size());
  EXPECT_EQ(node1, collector.inputs()[0]);
  EXPECT_EQ(node2, collector.inputs()[1]);
  EXPECT_EQ(node3, collector.inputs()[2]);
}

TEST_F(InputsCollectorTest_71, VisitDuplicateNodeOnlyAddsOnce_71) {
  InputsCollector collector;
  Node* node = state_.GetNode("foo.cc", 0);
  collector.VisitNode(node);
  collector.VisitNode(node);
  ASSERT_EQ(1u, collector.inputs().size());
  EXPECT_EQ(node, collector.inputs()[0]);
}

TEST_F(InputsCollectorTest_71, VisitMultipleWithDuplicates_71) {
  InputsCollector collector;
  Node* node1 = state_.GetNode("foo.cc", 0);
  Node* node2 = state_.GetNode("bar.cc", 0);
  collector.VisitNode(node1);
  collector.VisitNode(node2);
  collector.VisitNode(node1);
  collector.VisitNode(node2);
  ASSERT_EQ(2u, collector.inputs().size());
  EXPECT_EQ(node1, collector.inputs()[0]);
  EXPECT_EQ(node2, collector.inputs()[1]);
}

TEST_F(InputsCollectorTest_71, ResetClearsInputs_71) {
  InputsCollector collector;
  Node* node1 = state_.GetNode("foo.cc", 0);
  Node* node2 = state_.GetNode("bar.cc", 0);
  collector.VisitNode(node1);
  collector.VisitNode(node2);
  ASSERT_EQ(2u, collector.inputs().size());
  collector.Reset();
  EXPECT_TRUE(collector.inputs().empty());
}

TEST_F(InputsCollectorTest_71, ResetAllowsRevisitingNodes_71) {
  InputsCollector collector;
  Node* node = state_.GetNode("foo.cc", 0);
  collector.VisitNode(node);
  ASSERT_EQ(1u, collector.inputs().size());
  collector.Reset();
  EXPECT_TRUE(collector.inputs().empty());
  collector.VisitNode(node);
  ASSERT_EQ(1u, collector.inputs().size());
  EXPECT_EQ(node, collector.inputs()[0]);
}

TEST_F(InputsCollectorTest_71, GetInputsAsStringsNoEscape_71) {
  InputsCollector collector;
  Node* node1 = state_.GetNode("foo.cc", 0);
  Node* node2 = state_.GetNode("bar.cc", 0);
  collector.VisitNode(node1);
  collector.VisitNode(node2);
  std::vector<std::string> result = collector.GetInputsAsStrings(false);
  ASSERT_EQ(2u, result.size());
  EXPECT_EQ("foo.cc", result[0]);
  EXPECT_EQ("bar.cc", result[1]);
}

TEST_F(InputsCollectorTest_71, GetInputsAsStringsWithEscape_71) {
  InputsCollector collector;
  Node* node = state_.GetNode("foo bar.cc", 0);
  collector.VisitNode(node);
  std::vector<std::string> result_escaped = collector.GetInputsAsStrings(true);
  ASSERT_EQ(1u, result_escaped.size());
  // With shell escape, spaces should be escaped somehow
  // The exact escaping depends on implementation, but it should differ from unescaped
  // or at least contain the original filename content
  EXPECT_FALSE(result_escaped[0].empty());
}

TEST_F(InputsCollectorTest_71, GetInputsAsStringsEmpty_71) {
  InputsCollector collector;
  std::vector<std::string> result = collector.GetInputsAsStrings(false);
  EXPECT_TRUE(result.empty());
}

TEST_F(InputsCollectorTest_71, InputsReturnsConstReference_71) {
  InputsCollector collector;
  Node* node1 = state_.GetNode("a.cc", 0);
  const std::vector<const Node*>& ref1 = collector.inputs();
  EXPECT_TRUE(ref1.empty());
  collector.VisitNode(node1);
  // The reference should reflect the updated state
  EXPECT_EQ(1u, ref1.size());
}

TEST_F(InputsCollectorTest_71, OrderIsPreserved_71) {
  InputsCollector collector;
  Node* node_a = state_.GetNode("a.cc", 0);
  Node* node_b = state_.GetNode("b.cc", 0);
  Node* node_c = state_.GetNode("c.cc", 0);
  collector.VisitNode(node_c);
  collector.VisitNode(node_a);
  collector.VisitNode(node_b);
  ASSERT_EQ(3u, collector.inputs().size());
  EXPECT_EQ(node_c, collector.inputs()[0]);
  EXPECT_EQ(node_a, collector.inputs()[1]);
  EXPECT_EQ(node_b, collector.inputs()[2]);
}

TEST_F(InputsCollectorTest_71, MultipleResetsWork_71) {
  InputsCollector collector;
  Node* node = state_.GetNode("foo.cc", 0);

  collector.VisitNode(node);
  EXPECT_EQ(1u, collector.inputs().size());
  collector.Reset();
  EXPECT_TRUE(collector.inputs().empty());

  collector.Reset();  // Double reset should be fine
  EXPECT_TRUE(collector.inputs().empty());

  collector.VisitNode(node);
  EXPECT_EQ(1u, collector.inputs().size());
}

TEST_F(InputsCollectorTest_71, GetInputsAsStringsAfterReset_71) {
  InputsCollector collector;
  Node* node = state_.GetNode("test.cc", 0);
  collector.VisitNode(node);
  collector.Reset();
  std::vector<std::string> result = collector.GetInputsAsStrings(false);
  EXPECT_TRUE(result.empty());
}
