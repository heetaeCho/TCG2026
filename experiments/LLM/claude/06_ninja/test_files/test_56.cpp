#include "gtest/gtest.h"
#include "graph.h"
#include "state.h"

class EdgeTest_56 : public ::testing::Test {
 protected:
  void SetUp() override {
    state_.AddRule(&phony_rule_);
    state_.AddRule(&custom_rule_);
  }

  State state_;
  Rule phony_rule_{"phony"};
  Rule custom_rule_{"custom_rule"};
};

TEST_F(EdgeTest_56, RuleReturnsAssignedRule_56) {
  Edge edge;
  edge.rule_ = &custom_rule_;
  EXPECT_EQ("custom_rule", edge.rule().name());
}

TEST_F(EdgeTest_56, RuleReturnsPhonyRule_56) {
  Edge edge;
  edge.rule_ = &phony_rule_;
  EXPECT_EQ("phony", edge.rule().name());
}

TEST_F(EdgeTest_56, PoolReturnsNullByDefault_56) {
  Edge edge;
  EXPECT_EQ(nullptr, edge.pool());
}

TEST_F(EdgeTest_56, PoolReturnsAssignedPool_56) {
  Edge edge;
  Pool pool("test_pool", 5);
  edge.pool_ = &pool;
  EXPECT_EQ(&pool, edge.pool());
}

TEST_F(EdgeTest_56, OutputsReadyDefaultFalse_56) {
  Edge edge;
  EXPECT_FALSE(edge.outputs_ready());
}

TEST_F(EdgeTest_56, OutputsReadyReflectsState_56) {
  Edge edge;
  edge.outputs_ready_ = true;
  EXPECT_TRUE(edge.outputs_ready());
}

TEST_F(EdgeTest_56, IsPhonyWithPhonyRule_56) {
  Edge edge;
  edge.rule_ = &State::kPhonyRule;
  EXPECT_TRUE(edge.is_phony());
}

TEST_F(EdgeTest_56, IsPhonyWithNonPhonyRule_56) {
  Edge edge;
  edge.rule_ = &custom_rule_;
  EXPECT_FALSE(edge.is_phony());
}

TEST_F(EdgeTest_56, CriticalPathWeightDefault_56) {
  Edge edge;
  EXPECT_EQ(-1, edge.critical_path_weight());
}

TEST_F(EdgeTest_56, SetAndGetCriticalPathWeight_56) {
  Edge edge;
  edge.set_critical_path_weight(42);
  EXPECT_EQ(42, edge.critical_path_weight());
}

TEST_F(EdgeTest_56, SetCriticalPathWeightZero_56) {
  Edge edge;
  edge.set_critical_path_weight(0);
  EXPECT_EQ(0, edge.critical_path_weight());
}

TEST_F(EdgeTest_56, SetCriticalPathWeightLargeValue_56) {
  Edge edge;
  edge.set_critical_path_weight(INT64_MAX);
  EXPECT_EQ(INT64_MAX, edge.critical_path_weight());
}

TEST_F(EdgeTest_56, IsImplicitWithNoImplicitDeps_56) {
  Edge edge;
  edge.rule_ = &custom_rule_;
  // Create some nodes for inputs
  Node node1("input1", 0);
  Node node2("input2", 0);
  edge.inputs_.push_back(&node1);
  edge.inputs_.push_back(&node2);
  edge.implicit_deps_ = 0;
  edge.order_only_deps_ = 0;

  EXPECT_FALSE(edge.is_implicit(0));
  EXPECT_FALSE(edge.is_implicit(1));
}

TEST_F(EdgeTest_56, IsImplicitWithImplicitDeps_56) {
  Edge edge;
  edge.rule_ = &custom_rule_;
  Node node1("input1", 0);
  Node node2("input2", 0);
  Node node3("implicit_input", 0);
  edge.inputs_.push_back(&node1);
  edge.inputs_.push_back(&node2);
  edge.inputs_.push_back(&node3);
  edge.implicit_deps_ = 1;
  edge.order_only_deps_ = 0;

  EXPECT_FALSE(edge.is_implicit(0));
  EXPECT_FALSE(edge.is_implicit(1));
  EXPECT_TRUE(edge.is_implicit(2));
}

TEST_F(EdgeTest_56, IsOrderOnlyWithOrderOnlyDeps_56) {
  Edge edge;
  edge.rule_ = &custom_rule_;
  Node node1("input1", 0);
  Node node2("order_only", 0);
  edge.inputs_.push_back(&node1);
  edge.inputs_.push_back(&node2);
  edge.implicit_deps_ = 0;
  edge.order_only_deps_ = 1;

  EXPECT_FALSE(edge.is_order_only(0));
  EXPECT_TRUE(edge.is_order_only(1));
}

TEST_F(EdgeTest_56, IsImplicitOutWithNoImplicitOuts_56) {
  Edge edge;
  edge.rule_ = &custom_rule_;
  Node node1("output1", 0);
  edge.outputs_.push_back(&node1);
  edge.implicit_outs_ = 0;

  EXPECT_FALSE(edge.is_implicit_out(0));
}

TEST_F(EdgeTest_56, IsImplicitOutWithImplicitOuts_56) {
  Edge edge;
  edge.rule_ = &custom_rule_;
  Node node1("output1", 0);
  Node node2("implicit_output", 0);
  edge.outputs_.push_back(&node1);
  edge.outputs_.push_back(&node2);
  edge.implicit_outs_ = 1;

  EXPECT_FALSE(edge.is_implicit_out(0));
  EXPECT_TRUE(edge.is_implicit_out(1));
}

TEST_F(EdgeTest_56, DefaultEdgeFieldValues_56) {
  Edge edge;
  EXPECT_EQ(nullptr, edge.rule_);
  EXPECT_EQ(nullptr, edge.pool_);
  EXPECT_TRUE(edge.inputs_.empty());
  EXPECT_TRUE(edge.outputs_.empty());
  EXPECT_TRUE(edge.validations_.empty());
  EXPECT_EQ(nullptr, edge.dyndep_);
  EXPECT_EQ(nullptr, edge.env_);
  EXPECT_EQ(VisitNone, edge.mark_);
  EXPECT_EQ(0u, edge.id_);
  EXPECT_EQ(-1, edge.critical_path_weight_);
  EXPECT_FALSE(edge.outputs_ready_);
  EXPECT_FALSE(edge.deps_loaded_);
  EXPECT_FALSE(edge.deps_missing_);
  EXPECT_FALSE(edge.generated_by_dep_loader_);
  EXPECT_EQ(0, edge.command_start_time_);
  EXPECT_EQ(0, edge.implicit_deps_);
  EXPECT_EQ(0, edge.order_only_deps_);
  EXPECT_EQ(0, edge.implicit_outs_);
  EXPECT_EQ(-1, edge.prev_elapsed_time_millis);
}

TEST_F(EdgeTest_56, WeightForPhonyEdge_56) {
  Edge edge;
  edge.rule_ = &State::kPhonyRule;
  EXPECT_EQ(0, edge.weight());
}

TEST_F(EdgeTest_56, WeightForNonPhonyEdge_56) {
  Edge edge;
  edge.rule_ = &custom_rule_;
  EXPECT_EQ(1, edge.weight());
}

TEST_F(EdgeTest_56, RuleReferenceIsConst_56) {
  Edge edge;
  edge.rule_ = &custom_rule_;
  const Rule& rule_ref = edge.rule();
  EXPECT_EQ(&custom_rule_, &rule_ref);
}

TEST_F(EdgeTest_56, MultipleImplicitAndOrderOnly_56) {
  Edge edge;
  edge.rule_ = &custom_rule_;
  Node node1("explicit1", 0);
  Node node2("explicit2", 0);
  Node node3("implicit1", 0);
  Node node4("implicit2", 0);
  Node node5("order_only1", 0);
  edge.inputs_.push_back(&node1);
  edge.inputs_.push_back(&node2);
  edge.inputs_.push_back(&node3);
  edge.inputs_.push_back(&node4);
  edge.inputs_.push_back(&node5);
  edge.implicit_deps_ = 2;
  edge.order_only_deps_ = 1;

  // Explicit deps: index 0, 1
  EXPECT_FALSE(edge.is_implicit(0));
  EXPECT_FALSE(edge.is_order_only(0));
  EXPECT_FALSE(edge.is_implicit(1));
  EXPECT_FALSE(edge.is_order_only(1));

  // Implicit deps: index 2, 3
  EXPECT_TRUE(edge.is_implicit(2));
  EXPECT_FALSE(edge.is_order_only(2));
  EXPECT_TRUE(edge.is_implicit(3));
  EXPECT_FALSE(edge.is_order_only(3));

  // Order only: index 4
  EXPECT_TRUE(edge.is_order_only(4));
  // Order only deps are also past the implicit boundary, so they might
  // also be considered implicit depending on implementation
}

TEST_F(EdgeTest_56, MultipleImplicitOuts_56) {
  Edge edge;
  edge.rule_ = &custom_rule_;
  Node node1("out1", 0);
  Node node2("out2", 0);
  Node node3("implicit_out1", 0);
  Node node4("implicit_out2", 0);
  edge.outputs_.push_back(&node1);
  edge.outputs_.push_back(&node2);
  edge.outputs_.push_back(&node3);
  edge.outputs_.push_back(&node4);
  edge.implicit_outs_ = 2;

  EXPECT_FALSE(edge.is_implicit_out(0));
  EXPECT_FALSE(edge.is_implicit_out(1));
  EXPECT_TRUE(edge.is_implicit_out(2));
  EXPECT_TRUE(edge.is_implicit_out(3));
}
