#include "gtest/gtest.h"
#include "graph.h"

// Minimal Node definition if needed for compilation
// We rely on the actual project headers being available

class EdgeIsImplicitTest_60 : public ::testing::Test {
protected:
    Edge edge;
    
    // Helper to populate inputs with dummy node pointers
    // We use nullptr-like distinct addresses for simplicity
    void SetupInputs(size_t count) {
        edge.inputs_.clear();
        for (size_t i = 0; i < count; ++i) {
            // Use distinct non-null addresses (cast integers to Node*)
            edge.inputs_.push_back(reinterpret_cast<Node*>(i + 1));
        }
    }
};

// Test: When there are no implicit deps and no order_only deps,
// no index should be considered implicit
TEST_F(EdgeIsImplicitTest_60, NoImplicitNoOrderOnly_AllExplicit_60) {
    SetupInputs(5);
    edge.implicit_deps_ = 0;
    edge.order_only_deps_ = 0;
    
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_FALSE(edge.is_implicit(i)) << "Index " << i << " should not be implicit";
    }
}

// Test: When there are implicit deps but no order_only deps,
// the implicit range should be identified correctly
TEST_F(EdgeIsImplicitTest_60, ImplicitDepsNoOrderOnly_60) {
    // 5 inputs: 3 explicit, 2 implicit, 0 order_only
    SetupInputs(5);
    edge.implicit_deps_ = 2;
    edge.order_only_deps_ = 0;
    
    // Explicit inputs: indices 0, 1, 2
    EXPECT_FALSE(edge.is_implicit(0));
    EXPECT_FALSE(edge.is_implicit(1));
    EXPECT_FALSE(edge.is_implicit(2));
    
    // Implicit inputs: indices 3, 4
    EXPECT_TRUE(edge.is_implicit(3));
    EXPECT_TRUE(edge.is_implicit(4));
}

// Test: When there are both implicit deps and order_only deps
TEST_F(EdgeIsImplicitTest_60, ImplicitAndOrderOnlyDeps_60) {
    // 6 inputs: 2 explicit, 2 implicit, 2 order_only
    // Layout: [explicit, explicit, implicit, implicit, order_only, order_only]
    SetupInputs(6);
    edge.implicit_deps_ = 2;
    edge.order_only_deps_ = 2;
    
    // Explicit: 0, 1
    EXPECT_FALSE(edge.is_implicit(0));
    EXPECT_FALSE(edge.is_implicit(1));
    
    // Implicit: 2, 3
    EXPECT_TRUE(edge.is_implicit(2));
    EXPECT_TRUE(edge.is_implicit(3));
    
    // Order-only: 4, 5 (should NOT be implicit)
    EXPECT_FALSE(edge.is_implicit(4));
    EXPECT_FALSE(edge.is_implicit(5));
}

// Test: When there are only order_only deps and no implicit deps
TEST_F(EdgeIsImplicitTest_60, OnlyOrderOnlyDeps_60) {
    // 4 inputs: 2 explicit, 0 implicit, 2 order_only
    SetupInputs(4);
    edge.implicit_deps_ = 0;
    edge.order_only_deps_ = 2;
    
    EXPECT_FALSE(edge.is_implicit(0));
    EXPECT_FALSE(edge.is_implicit(1));
    EXPECT_FALSE(edge.is_implicit(2));
    EXPECT_FALSE(edge.is_implicit(3));
}

// Test: Single input that is implicit
TEST_F(EdgeIsImplicitTest_60, SingleImplicitInput_60) {
    SetupInputs(1);
    edge.implicit_deps_ = 1;
    edge.order_only_deps_ = 0;
    
    EXPECT_TRUE(edge.is_implicit(0));
}

// Test: Single input that is order_only (not implicit)
TEST_F(EdgeIsImplicitTest_60, SingleOrderOnlyInput_60) {
    SetupInputs(1);
    edge.implicit_deps_ = 0;
    edge.order_only_deps_ = 1;
    
    EXPECT_FALSE(edge.is_implicit(0));
}

// Test: Single explicit input
TEST_F(EdgeIsImplicitTest_60, SingleExplicitInput_60) {
    SetupInputs(1);
    edge.implicit_deps_ = 0;
    edge.order_only_deps_ = 0;
    
    EXPECT_FALSE(edge.is_implicit(0));
}

// Test: Boundary - first implicit index
TEST_F(EdgeIsImplicitTest_60, BoundaryFirstImplicitIndex_60) {
    // 10 inputs: 5 explicit, 3 implicit, 2 order_only
    SetupInputs(10);
    edge.implicit_deps_ = 3;
    edge.order_only_deps_ = 2;
    
    // Last explicit index
    EXPECT_FALSE(edge.is_implicit(4));
    // First implicit index
    EXPECT_TRUE(edge.is_implicit(5));
    // Last implicit index
    EXPECT_TRUE(edge.is_implicit(7));
    // First order_only index
    EXPECT_FALSE(edge.is_implicit(8));
}

// Test: All inputs are implicit (no explicit, no order_only)
TEST_F(EdgeIsImplicitTest_60, AllInputsImplicit_60) {
    SetupInputs(3);
    edge.implicit_deps_ = 3;
    edge.order_only_deps_ = 0;
    
    EXPECT_TRUE(edge.is_implicit(0));
    EXPECT_TRUE(edge.is_implicit(1));
    EXPECT_TRUE(edge.is_implicit(2));
}

// Test: All inputs are order_only (no explicit, no implicit)
TEST_F(EdgeIsImplicitTest_60, AllInputsOrderOnly_60) {
    SetupInputs(3);
    edge.implicit_deps_ = 0;
    edge.order_only_deps_ = 3;
    
    EXPECT_FALSE(edge.is_implicit(0));
    EXPECT_FALSE(edge.is_implicit(1));
    EXPECT_FALSE(edge.is_implicit(2));
}

// Test: Large number of inputs with mixed types
TEST_F(EdgeIsImplicitTest_60, LargeInputMixed_60) {
    // 100 inputs: 50 explicit, 30 implicit, 20 order_only
    SetupInputs(100);
    edge.implicit_deps_ = 30;
    edge.order_only_deps_ = 20;
    
    // Check some explicit
    EXPECT_FALSE(edge.is_implicit(0));
    EXPECT_FALSE(edge.is_implicit(49));
    
    // Check implicit range [50, 79]
    EXPECT_TRUE(edge.is_implicit(50));
    EXPECT_TRUE(edge.is_implicit(65));
    EXPECT_TRUE(edge.is_implicit(79));
    
    // Check order_only range [80, 99]
    EXPECT_FALSE(edge.is_implicit(80));
    EXPECT_FALSE(edge.is_implicit(99));
}

// Test: is_implicit with zero inputs (edge case, though index would be out of range)
// This tests that the method doesn't crash in degenerate cases
TEST_F(EdgeIsImplicitTest_60, EmptyInputs_60) {
    edge.inputs_.clear();
    edge.implicit_deps_ = 0;
    edge.order_only_deps_ = 0;
    
    // With no inputs, calling is_implicit(0) may have undefined behavior,
    // but we include this as a boundary awareness test
    // We don't actually call it since it would be out of bounds
    EXPECT_EQ(edge.inputs_.size(), 0u);
}

// Test: Exactly at the boundary between implicit and order_only
TEST_F(EdgeIsImplicitTest_60, ExactBoundaryImplicitOrderOnly_60) {
    // 4 inputs: 1 explicit, 1 implicit, 2 order_only
    SetupInputs(4);
    edge.implicit_deps_ = 1;
    edge.order_only_deps_ = 2;
    
    EXPECT_FALSE(edge.is_implicit(0)); // explicit
    EXPECT_TRUE(edge.is_implicit(1));  // implicit
    EXPECT_FALSE(edge.is_implicit(2)); // order_only
    EXPECT_FALSE(edge.is_implicit(3)); // order_only
}
