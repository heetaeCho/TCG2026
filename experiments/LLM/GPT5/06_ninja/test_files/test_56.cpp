// File: edge_rule_test_56.cc

#include "graph.h"

#include <gtest/gtest.h>
#include <memory>
#include <string>

// Test fixture for Edge::rule() tests (TEST_ID = 56)
class EdgeRuleTest_56 : public ::testing::Test {
 protected:
  Edge edge_;
  std::unique_ptr<Rule> rule1_;
  std::unique_ptr<Rule> rule2_;

  void SetUp() override {
    // Construct some distinct Rule instances.
    // Assumes Rule is constructible from a std::string name
    // as in the real ninja codebase.
    rule1_.reset(new Rule("rule1"));
    rule2_.reset(new Rule("rule2"));
  }
};

// Normal operation: rule() returns the same Rule object that was assigned.
TEST_F(EdgeRuleTest_56, ReturnsAssignedRule_56) {
  edge_.rule_ = rule1_.get();

  const Rule& returned_rule = edge_.rule();

  // Check that the reference actually refers to the same object.
  EXPECT_EQ(&returned_rule, rule1_.get());
}

// Normal operation with a second, different Rule: rule() follows the current pointer.
TEST_F(EdgeRuleTest_56, ReturnsCurrentRuleAfterReassignment_56) {
  edge_.rule_ = rule1_.get();
  EXPECT_EQ(&edge_.rule(), rule1_.get());

  // Reassign to a different Rule and verify the change is reflected.
  edge_.rule_ = rule2_.get();
  EXPECT_EQ(&edge_.rule(), rule2_.get());
}

// Const-correctness: rule() can be called on a const Edge
// and still returns the correct Rule reference.
TEST_F(EdgeRuleTest_56, ConstEdgeReturnsAssignedRule_56) {
  edge_.rule_ = rule1_.get();
  const Edge& const_edge = edge_;

  const Rule& returned_rule = const_edge.rule();

  EXPECT_EQ(&returned_rule, rule1_.get());
}
