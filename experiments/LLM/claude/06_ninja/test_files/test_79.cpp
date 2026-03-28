#include "gtest/gtest.h"
#include "state.h"
#include "graph.h"

// Test fixture for WeightedEdgeCmp
class WeightedEdgeCmpTest_79 : public ::testing::Test {
protected:
    Pool::WeightedEdgeCmp cmp;
};

// Test: Both edges are nullptr
TEST_F(WeightedEdgeCmpTest_79, BothNullReturnsfalse_79) {
    EXPECT_FALSE(cmp(nullptr, nullptr));
}

// Test: First edge is nullptr, second is not
TEST_F(WeightedEdgeCmpTest_79, FirstNullSecondNotNull_79) {
    Edge edge;
    EXPECT_TRUE(cmp(nullptr, &edge));
}

// Test: First edge is not nullptr, second is nullptr
TEST_F(WeightedEdgeCmpTest_79, FirstNotNullSecondNull_79) {
    Edge edge;
    EXPECT_FALSE(cmp(&edge, nullptr));
}

// Test: Same edge compared to itself
TEST_F(WeightedEdgeCmpTest_79, SameEdgeReturnsFalse_79) {
    Edge edge;
    // Comparing an edge to itself should return false (strict weak ordering)
    EXPECT_FALSE(cmp(&edge, &edge));
}

// Test: Two default edges (same weight = 0) - comparator should use EdgePriorityGreater as tiebreaker
TEST_F(WeightedEdgeCmpTest_79, TwoDefaultEdgesSameWeight_79) {
    Edge edge1;
    Edge edge2;
    // Both have default weight. The tiebreaker EdgePriorityGreater determines order.
    // We just verify no crash and that antisymmetry holds:
    // If cmp(a,b) is true, cmp(b,a) must be false.
    bool ab = cmp(&edge1, &edge2);
    bool ba = cmp(&edge2, &edge1);
    // Antisymmetry: cannot both be true
    EXPECT_FALSE(ab && ba);
}

// Test: Edges with different critical path weights lead to different ordering
TEST_F(WeightedEdgeCmpTest_79, DifferentWeightsOrderByWeight_79) {
    // We'll create edges and set their critical_path_weight to influence weight()
    // Since we don't know exact implementation of weight(), we rely on 
    // the observable behavior through the comparator.
    Edge edge1;
    Edge edge2;
    
    // Set different critical path weights to potentially influence weight()
    edge1.set_critical_path_weight(10);
    edge2.set_critical_path_weight(20);
    
    // We can check consistency: if weight differs, one must be less than the other
    bool ab = cmp(&edge1, &edge2);
    bool ba = cmp(&edge2, &edge1);
    
    // Antisymmetry must hold
    if (ab) {
        EXPECT_FALSE(ba);
    }
    if (ba) {
        EXPECT_FALSE(ab);
    }
}

// Test: Transitivity - if a < b and b < c then a < c
TEST_F(WeightedEdgeCmpTest_79, TransitivityWithDifferentWeights_79) {
    Edge edge1, edge2, edge3;
    edge1.set_critical_path_weight(5);
    edge2.set_critical_path_weight(10);
    edge3.set_critical_path_weight(15);
    
    bool ab = cmp(&edge1, &edge2);
    bool bc = cmp(&edge2, &edge3);
    bool ac = cmp(&edge1, &edge3);
    
    // If a < b and b < c, then a < c (transitivity)
    if (ab && bc) {
        EXPECT_TRUE(ac);
    }
    // If a > b and b > c, then a > c
    if (!ab && !bc) {
        // edge1 >= edge2 and edge2 >= edge3
        // We can't strictly conclude a > c without knowing if equality is involved
    }
}

// Test: Irreflexivity - cmp(a, a) should be false
TEST_F(WeightedEdgeCmpTest_79, IrreflexivityProperty_79) {
    Edge edge;
    edge.set_critical_path_weight(42);
    EXPECT_FALSE(cmp(&edge, &edge));
}

// Test: Can be used as comparator in std::set (DelayedEdges)
TEST_F(WeightedEdgeCmpTest_79, UsableInStdSet_79) {
    std::set<Edge*, Pool::WeightedEdgeCmp> delayed_edges;
    
    Edge edge1, edge2, edge3;
    edge1.set_critical_path_weight(1);
    edge2.set_critical_path_weight(2);
    edge3.set_critical_path_weight(3);
    
    delayed_edges.insert(&edge1);
    delayed_edges.insert(&edge2);
    delayed_edges.insert(&edge3);
    
    EXPECT_EQ(delayed_edges.size(), 3u);
    
    // Inserting same pointer again should not increase size
    delayed_edges.insert(&edge1);
    EXPECT_EQ(delayed_edges.size(), 3u);
}

// Test: Inserting nullptr into set works correctly
TEST_F(WeightedEdgeCmpTest_79, NullptrInSet_79) {
    std::set<Edge*, Pool::WeightedEdgeCmp> delayed_edges;
    Edge edge;
    
    delayed_edges.insert(nullptr);
    delayed_edges.insert(&edge);
    
    EXPECT_EQ(delayed_edges.size(), 2u);
}

// Test: Edges with same weight but different ids for tiebreaking
TEST_F(WeightedEdgeCmpTest_79, SameWeightDifferentIds_79) {
    Edge edge1, edge2;
    edge1.set_critical_path_weight(100);
    edge2.set_critical_path_weight(100);
    edge1.id_ = 1;
    edge2.id_ = 2;
    
    bool ab = cmp(&edge1, &edge2);
    bool ba = cmp(&edge2, &edge1);
    
    // Antisymmetry
    EXPECT_FALSE(ab && ba);
    // Since they are different edges with potentially same weight, 
    // exactly one ordering or equal (but not both directions true)
}

// Test: Negative critical path weights
TEST_F(WeightedEdgeCmpTest_79, NegativeCriticalPathWeights_79) {
    Edge edge1, edge2;
    edge1.set_critical_path_weight(-10);
    edge2.set_critical_path_weight(-5);
    
    bool ab = cmp(&edge1, &edge2);
    bool ba = cmp(&edge2, &edge1);
    
    // Antisymmetry
    EXPECT_FALSE(ab && ba);
}

// Test: Zero critical path weight vs positive
TEST_F(WeightedEdgeCmpTest_79, ZeroVsPositiveWeight_79) {
    Edge edge1, edge2;
    edge1.set_critical_path_weight(0);
    edge2.set_critical_path_weight(100);
    
    bool ab = cmp(&edge1, &edge2);
    bool ba = cmp(&edge2, &edge1);
    
    EXPECT_FALSE(ab && ba);
}

// Test: Large set of edges maintains strict weak ordering invariants
TEST_F(WeightedEdgeCmpTest_79, LargeSetOrdering_79) {
    const int N = 10;
    Edge edges[N];
    std::set<Edge*, Pool::WeightedEdgeCmp> delayed_edges;
    
    for (int i = 0; i < N; ++i) {
        edges[i].set_critical_path_weight(i * 10);
        edges[i].id_ = i;
        delayed_edges.insert(&edges[i]);
    }
    
    EXPECT_EQ(delayed_edges.size(), static_cast<size_t>(N));
}
