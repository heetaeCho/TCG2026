#include "gtest/gtest.h"
#include "graph.h"
#include <string>
#include <vector>

// Forward declarations and minimal stubs if needed
// We rely on the actual implementations linked from the project.

class EdgePoolTest_57 : public ::testing::Test {
protected:
    Edge edge_;
    
    void SetUp() override {
        // Edge default constructor sets pool_ to nullptr
    }
};

// Test that pool() returns nullptr by default (default-constructed Edge)
TEST_F(EdgePoolTest_57, PoolReturnsNullByDefault_57) {
    EXPECT_EQ(nullptr, edge_.pool());
}

// Test that pool() returns the pool_ member when set
TEST_F(EdgePoolTest_57, PoolReturnsAssignedPool_57) {
    Pool test_pool("test_pool", 5);
    edge_.pool_ = &test_pool;
    EXPECT_EQ(&test_pool, edge_.pool());
}

// Test that pool() returns updated value after reassignment
TEST_F(EdgePoolTest_57, PoolReturnsUpdatedPoolAfterReassignment_57) {
    Pool pool1("pool1", 3);
    Pool pool2("pool2", 7);
    
    edge_.pool_ = &pool1;
    EXPECT_EQ(&pool1, edge_.pool());
    
    edge_.pool_ = &pool2;
    EXPECT_EQ(&pool2, edge_.pool());
}

// Test that pool() returns nullptr after setting back to nullptr
TEST_F(EdgePoolTest_57, PoolReturnsNullAfterReset_57) {
    Pool test_pool("test_pool", 2);
    edge_.pool_ = &test_pool;
    EXPECT_EQ(&test_pool, edge_.pool());
    
    edge_.pool_ = nullptr;
    EXPECT_EQ(nullptr, edge_.pool());
}

// Test outputs_ready() returns false by default
TEST_F(EdgePoolTest_57, OutputsReadyDefaultFalse_57) {
    EXPECT_FALSE(edge_.outputs_ready());
}

// Test outputs_ready() reflects the member
TEST_F(EdgePoolTest_57, OutputsReadyReflectsMember_57) {
    edge_.outputs_ready_ = true;
    EXPECT_TRUE(edge_.outputs_ready());
}

// Test critical_path_weight() default value
TEST_F(EdgePoolTest_57, CriticalPathWeightDefault_57) {
    EXPECT_EQ(-1, edge_.critical_path_weight());
}

// Test set_critical_path_weight and critical_path_weight
TEST_F(EdgePoolTest_57, SetAndGetCriticalPathWeight_57) {
    edge_.set_critical_path_weight(42);
    EXPECT_EQ(42, edge_.critical_path_weight());
}

// Test set_critical_path_weight with zero
TEST_F(EdgePoolTest_57, CriticalPathWeightZero_57) {
    edge_.set_critical_path_weight(0);
    EXPECT_EQ(0, edge_.critical_path_weight());
}

// Test set_critical_path_weight with large value
TEST_F(EdgePoolTest_57, CriticalPathWeightLargeValue_57) {
    int64_t large_val = 9999999999LL;
    edge_.set_critical_path_weight(large_val);
    EXPECT_EQ(large_val, edge_.critical_path_weight());
}

// Test set_critical_path_weight with negative value
TEST_F(EdgePoolTest_57, CriticalPathWeightNegativeValue_57) {
    edge_.set_critical_path_weight(-100);
    EXPECT_EQ(-100, edge_.critical_path_weight());
}

// Test is_implicit with no implicit deps (all explicit)
TEST_F(EdgePoolTest_57, IsImplicitNoImplicitDeps_57) {
    Node node1;
    edge_.inputs_.push_back(&node1);
    edge_.implicit_deps_ = 0;
    edge_.order_only_deps_ = 0;
    
    EXPECT_FALSE(edge_.is_implicit(0));
}

// Test is_implicit with implicit deps
TEST_F(EdgePoolTest_57, IsImplicitWithImplicitDeps_57) {
    Node node1, node2, node3;
    edge_.inputs_.push_back(&node1);  // explicit
    edge_.inputs_.push_back(&node2);  // implicit
    edge_.inputs_.push_back(&node3);  // order_only
    edge_.implicit_deps_ = 1;
    edge_.order_only_deps_ = 1;
    
    EXPECT_FALSE(edge_.is_implicit(0));  // explicit
    EXPECT_TRUE(edge_.is_implicit(1));   // implicit
    EXPECT_FALSE(edge_.is_implicit(2));  // order_only, not implicit
}

// Test is_order_only
TEST_F(EdgePoolTest_57, IsOrderOnly_57) {
    Node node1, node2, node3;
    edge_.inputs_.push_back(&node1);  // explicit
    edge_.inputs_.push_back(&node2);  // implicit
    edge_.inputs_.push_back(&node3);  // order_only
    edge_.implicit_deps_ = 1;
    edge_.order_only_deps_ = 1;
    
    EXPECT_FALSE(edge_.is_order_only(0));  // explicit
    EXPECT_FALSE(edge_.is_order_only(1));  // implicit
    EXPECT_TRUE(edge_.is_order_only(2));   // order_only
}

// Test is_implicit_out with no implicit outputs
TEST_F(EdgePoolTest_57, IsImplicitOutNoImplicitOuts_57) {
    Node node1;
    edge_.outputs_.push_back(&node1);
    edge_.implicit_outs_ = 0;
    
    EXPECT_FALSE(edge_.is_implicit_out(0));
}

// Test is_implicit_out with implicit outputs
TEST_F(EdgePoolTest_57, IsImplicitOutWithImplicitOuts_57) {
    Node node1, node2;
    edge_.outputs_.push_back(&node1);  // explicit output
    edge_.outputs_.push_back(&node2);  // implicit output
    edge_.implicit_outs_ = 1;
    
    EXPECT_FALSE(edge_.is_implicit_out(0));  // explicit
    EXPECT_TRUE(edge_.is_implicit_out(1));   // implicit
}

// Test is_phony with a phony rule
TEST_F(EdgePoolTest_57, IsPhonyWithPhonyRule_57) {
    // We need a Rule named "phony" to test this
    Rule phony_rule("phony");
    edge_.rule_ = &phony_rule;
    EXPECT_TRUE(edge_.is_phony());
}

// Test is_phony with a non-phony rule
TEST_F(EdgePoolTest_57, IsPhonyWithNonPhonyRule_57) {
    Rule regular_rule("cc");
    edge_.rule_ = &regular_rule;
    EXPECT_FALSE(edge_.is_phony());
}

// Test rule() accessor
TEST_F(EdgePoolTest_57, RuleAccessor_57) {
    Rule test_rule("test_rule");
    edge_.rule_ = &test_rule;
    EXPECT_EQ("test_rule", edge_.rule().name());
}

// Test multiple edges can have different pools
TEST_F(EdgePoolTest_57, MultipleEdgesDifferentPools_57) {
    Edge edge1, edge2;
    Pool pool1("pool1", 1);
    Pool pool2("pool2", 2);
    
    edge1.pool_ = &pool1;
    edge2.pool_ = &pool2;
    
    EXPECT_EQ(&pool1, edge1.pool());
    EXPECT_EQ(&pool2, edge2.pool());
    EXPECT_NE(edge1.pool(), edge2.pool());
}
