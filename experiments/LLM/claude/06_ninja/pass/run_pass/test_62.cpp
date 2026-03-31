#include "gtest/gtest.h"
#include "graph.h"

class EdgeIsImplicitOutTest_62 : public ::testing::Test {
protected:
    Edge edge;
    
    void SetUp() override {
        // Reset edge to default state
        edge = Edge();
    }
    
    // Helper to add dummy output nodes
    void AddOutputNodes(size_t count) {
        for (size_t i = 0; i < count; ++i) {
            edge.outputs_.push_back(nullptr);
        }
    }
};

// Test: When implicit_outs_ is 0, no output is implicit
TEST_F(EdgeIsImplicitOutTest_62, NoImplicitOuts_AllExplicit_62) {
    AddOutputNodes(3);
    edge.implicit_outs_ = 0;
    
    EXPECT_FALSE(edge.is_implicit_out(0));
    EXPECT_FALSE(edge.is_implicit_out(1));
    EXPECT_FALSE(edge.is_implicit_out(2));
}

// Test: When all outputs are implicit
TEST_F(EdgeIsImplicitOutTest_62, AllOutputsImplicit_62) {
    AddOutputNodes(3);
    edge.implicit_outs_ = 3;
    
    EXPECT_TRUE(edge.is_implicit_out(0));
    EXPECT_TRUE(edge.is_implicit_out(1));
    EXPECT_TRUE(edge.is_implicit_out(2));
}

// Test: Mixed explicit and implicit outputs
TEST_F(EdgeIsImplicitOutTest_62, MixedExplicitAndImplicit_62) {
    AddOutputNodes(5);
    edge.implicit_outs_ = 2;
    
    // Explicit outputs: indices 0, 1, 2 (outputs_.size() - implicit_outs_ = 3)
    EXPECT_FALSE(edge.is_implicit_out(0));
    EXPECT_FALSE(edge.is_implicit_out(1));
    EXPECT_FALSE(edge.is_implicit_out(2));
    
    // Implicit outputs: indices 3, 4
    EXPECT_TRUE(edge.is_implicit_out(3));
    EXPECT_TRUE(edge.is_implicit_out(4));
}

// Test: Boundary - index exactly at the boundary between explicit and implicit
TEST_F(EdgeIsImplicitOutTest_62, BoundaryIndex_62) {
    AddOutputNodes(4);
    edge.implicit_outs_ = 1;
    
    // Boundary: outputs_.size() - implicit_outs_ = 3
    // Index 2 is last explicit (index < 3)
    EXPECT_FALSE(edge.is_implicit_out(2));
    // Index 3 is first implicit (index >= 3)
    EXPECT_TRUE(edge.is_implicit_out(3));
}

// Test: Single output that is explicit
TEST_F(EdgeIsImplicitOutTest_62, SingleExplicitOutput_62) {
    AddOutputNodes(1);
    edge.implicit_outs_ = 0;
    
    EXPECT_FALSE(edge.is_implicit_out(0));
}

// Test: Single output that is implicit
TEST_F(EdgeIsImplicitOutTest_62, SingleImplicitOutput_62) {
    AddOutputNodes(1);
    edge.implicit_outs_ = 1;
    
    EXPECT_TRUE(edge.is_implicit_out(0));
}

// Test: Two outputs, one explicit and one implicit
TEST_F(EdgeIsImplicitOutTest_62, TwoOutputsOneImplicit_62) {
    AddOutputNodes(2);
    edge.implicit_outs_ = 1;
    
    EXPECT_FALSE(edge.is_implicit_out(0));
    EXPECT_TRUE(edge.is_implicit_out(1));
}

// Test: Large number of outputs with some implicit
TEST_F(EdgeIsImplicitOutTest_62, LargeNumberOfOutputs_62) {
    AddOutputNodes(100);
    edge.implicit_outs_ = 10;
    
    // Last explicit index: 89
    EXPECT_FALSE(edge.is_implicit_out(89));
    // First implicit index: 90
    EXPECT_TRUE(edge.is_implicit_out(90));
    // Last implicit index: 99
    EXPECT_TRUE(edge.is_implicit_out(99));
    // First index
    EXPECT_FALSE(edge.is_implicit_out(0));
}

// Test: Index equal to outputs_.size() - implicit_outs_ (boundary, should be implicit)
TEST_F(EdgeIsImplicitOutTest_62, IndexAtExactBoundary_62) {
    AddOutputNodes(10);
    edge.implicit_outs_ = 5;
    
    // Boundary = 10 - 5 = 5
    // Index 4 should be explicit
    EXPECT_FALSE(edge.is_implicit_out(4));
    // Index 5 should be implicit (>= boundary)
    EXPECT_TRUE(edge.is_implicit_out(5));
}
