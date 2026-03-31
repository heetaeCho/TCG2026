#include "gtest/gtest.h"
#include "graph.h"

class EdgeWeightTest_58 : public ::testing::Test {
protected:
    Edge edge_;
};

TEST_F(EdgeWeightTest_58, WeightReturnsOne_58) {
    EXPECT_EQ(1, edge_.weight());
}

TEST_F(EdgeWeightTest_58, WeightIsConstant_58) {
    // Calling weight multiple times should always return the same value
    EXPECT_EQ(edge_.weight(), edge_.weight());
    EXPECT_EQ(1, edge_.weight());
}

TEST_F(EdgeWeightTest_58, WeightOnDifferentEdgeInstances_58) {
    Edge edge1;
    Edge edge2;
    EXPECT_EQ(edge1.weight(), edge2.weight());
    EXPECT_EQ(1, edge1.weight());
    EXPECT_EQ(1, edge2.weight());
}

TEST_F(EdgeWeightTest_58, WeightOnConstEdge_58) {
    const Edge constEdge;
    EXPECT_EQ(1, constEdge.weight());
}

TEST_F(EdgeWeightTest_58, DefaultConstructedEdgeWeight_58) {
    Edge defaultEdge;
    EXPECT_EQ(1, defaultEdge.weight());
}
