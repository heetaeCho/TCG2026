#include "gtest/gtest.h"
#include "graph.h"
#include "state.h"
#include "test.h"

class InputsCollectorTest_72 : public testing::Test {
 protected:
  void SetUp() override {
    collector_.Reset();
  }

  InputsCollector collector_;
  State state_;
};

TEST_F(InputsCollectorTest_72, ResetClearsInputs_72) {
  // After Reset, inputs should be empty
  collector_.Reset();
  EXPECT_TRUE(collector_.inputs().empty());
}

TEST_F(InputsCollectorTest_72, InitiallyEmpty_72) {
  InputsCollector fresh_collector;
  EXPECT_TRUE(fresh_collector.inputs().empty());
}

TEST_F(InputsCollectorTest_72, VisitNodeAddsToInputs_72) {
  Node* node = state_.GetNode("foo.c", 0);
  collector_.VisitNode(node);
  EXPECT_FALSE(collector_.inputs().empty());
}

TEST_F(InputsCollectorTest_72, VisitSameNodeTwiceDoesNotDuplicate_72) {
  Node* node = state_.GetNode("foo.c", 0);
  collector_.VisitNode(node);
  size_t size_after_first = collector_.inputs().size();
  collector_.VisitNode(node);
  size_t size_after_second = collector_.inputs().size();
  // Visiting the same node again should not add a duplicate
  EXPECT_EQ(size_after_first, size_after_second);
}

TEST_F(InputsCollectorTest_72, VisitMultipleDistinctNodes_72) {
  Node* node1 = state_.GetNode("foo.c", 0);
  Node* node2 = state_.GetNode("bar.c", 0);
  Node* node3 = state_.GetNode("baz.c", 0);
  collector_.VisitNode(node1);
  collector_.VisitNode(node2);
  collector_.VisitNode(node3);
  EXPECT_EQ(3u, collector_.inputs().size());
}

TEST_F(InputsCollectorTest_72, ResetAfterVisitClearsAll_72) {
  Node* node1 = state_.GetNode("foo.c", 0);
  Node* node2 = state_.GetNode("bar.c", 0);
  collector_.VisitNode(node1);
  collector_.VisitNode(node2);
  EXPECT_EQ(2u, collector_.inputs().size());
  collector_.Reset();
  EXPECT_TRUE(collector_.inputs().empty());
}

TEST_F(InputsCollectorTest_72, ResetAllowsRevisitingNodes_72) {
  Node* node = state_.GetNode("foo.c", 0);
  collector_.VisitNode(node);
  EXPECT_EQ(1u, collector_.inputs().size());
  collector_.Reset();
  EXPECT_TRUE(collector_.inputs().empty());
  // After reset, the same node should be visitable again
  collector_.VisitNode(node);
  EXPECT_EQ(1u, collector_.inputs().size());
}

TEST_F(InputsCollectorTest_72, GetInputsAsStringsNoEscape_72) {
  Node* node1 = state_.GetNode("foo.c", 0);
  Node* node2 = state_.GetNode("bar.c", 0);
  collector_.VisitNode(node1);
  collector_.VisitNode(node2);
  std::vector<std::string> strings = collector_.GetInputsAsStrings(false);
  EXPECT_EQ(2u, strings.size());
  // Check that the node paths are present
  bool found_foo = false, found_bar = false;
  for (const auto& s : strings) {
    if (s == "foo.c") found_foo = true;
    if (s == "bar.c") found_bar = true;
  }
  EXPECT_TRUE(found_foo);
  EXPECT_TRUE(found_bar);
}

TEST_F(InputsCollectorTest_72, GetInputsAsStringsWithEscape_72) {
  Node* node = state_.GetNode("foo bar.c", 0);
  collector_.VisitNode(node);
  std::vector<std::string> strings = collector_.GetInputsAsStrings(true);
  EXPECT_EQ(1u, strings.size());
  // When shell_escape is true, spaces should be escaped somehow
  // At minimum, the string should not be empty
  EXPECT_FALSE(strings[0].empty());
}

TEST_F(InputsCollectorTest_72, GetInputsAsStringsEmptyCollector_72) {
  std::vector<std::string> strings = collector_.GetInputsAsStrings(false);
  EXPECT_TRUE(strings.empty());
}

TEST_F(InputsCollectorTest_72, InputsReturnsConstReference_72) {
  Node* node = state_.GetNode("test.c", 0);
  collector_.VisitNode(node);
  const std::vector<const Node*>& ref1 = collector_.inputs();
  const std::vector<const Node*>& ref2 = collector_.inputs();
  // Should return the same reference
  EXPECT_EQ(&ref1, &ref2);
}

TEST_F(InputsCollectorTest_72, MultipleResetsAreIdempotent_72) {
  collector_.Reset();
  collector_.Reset();
  collector_.Reset();
  EXPECT_TRUE(collector_.inputs().empty());
}

TEST_F(InputsCollectorTest_72, InputsContainCorrectNodes_72) {
  Node* node1 = state_.GetNode("a.c", 0);
  Node* node2 = state_.GetNode("b.c", 0);
  collector_.VisitNode(node1);
  collector_.VisitNode(node2);
  const auto& inputs = collector_.inputs();
  bool found_node1 = false, found_node2 = false;
  for (const auto* n : inputs) {
    if (n == node1) found_node1 = true;
    if (n == node2) found_node2 = true;
  }
  EXPECT_TRUE(found_node1);
  EXPECT_TRUE(found_node2);
}
