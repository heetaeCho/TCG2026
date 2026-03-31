#include "gtest/gtest.h"
#include "graph.h"

class EdgeCriticalPathWeightTest_54 : public ::testing::Test {
protected:
    Edge edge_;
};

TEST_F(EdgeCriticalPathWeightTest_54, DefaultCriticalPathWeightIsNegativeOne_54) {
    // Default constructed Edge should have critical_path_weight_ == -1
    EXPECT_EQ(-1, edge_.critical_path_weight());
}

TEST_F(EdgeCriticalPathWeightTest_54, SetAndGetCriticalPathWeightZero_54) {
    edge_.set_critical_path_weight(0);
    EXPECT_EQ(0, edge_.critical_path_weight());
}

TEST_F(EdgeCriticalPathWeightTest_54, SetAndGetCriticalPathWeightPositive_54) {
    edge_.set_critical_path_weight(42);
    EXPECT_EQ(42, edge_.critical_path_weight());
}

TEST_F(EdgeCriticalPathWeightTest_54, SetAndGetCriticalPathWeightNegative_54) {
    edge_.set_critical_path_weight(-100);
    EXPECT_EQ(-100, edge_.critical_path_weight());
}

TEST_F(EdgeCriticalPathWeightTest_54, SetAndGetCriticalPathWeightLargeValue_54) {
    int64_t large_value = INT64_MAX;
    edge_.set_critical_path_weight(large_value);
    EXPECT_EQ(large_value, edge_.critical_path_weight());
}

TEST_F(EdgeCriticalPathWeightTest_54, SetAndGetCriticalPathWeightMinValue_54) {
    int64_t min_value = INT64_MIN;
    edge_.set_critical_path_weight(min_value);
    EXPECT_EQ(min_value, edge_.critical_path_weight());
}

TEST_F(EdgeCriticalPathWeightTest_54, SetCriticalPathWeightOverwritesPreviousValue_54) {
    edge_.set_critical_path_weight(10);
    EXPECT_EQ(10, edge_.critical_path_weight());
    
    edge_.set_critical_path_weight(20);
    EXPECT_EQ(20, edge_.critical_path_weight());
}

TEST_F(EdgeCriticalPathWeightTest_54, SetCriticalPathWeightBackToDefault_54) {
    edge_.set_critical_path_weight(500);
    EXPECT_EQ(500, edge_.critical_path_weight());
    
    edge_.set_critical_path_weight(-1);
    EXPECT_EQ(-1, edge_.critical_path_weight());
}

TEST_F(EdgeCriticalPathWeightTest_54, CriticalPathWeightIsConstMethod_54) {
    const Edge& const_edge = edge_;
    EXPECT_EQ(-1, const_edge.critical_path_weight());
}

TEST_F(EdgeCriticalPathWeightTest_54, SetCriticalPathWeightOne_54) {
    edge_.set_critical_path_weight(1);
    EXPECT_EQ(1, edge_.critical_path_weight());
}

TEST_F(EdgeCriticalPathWeightTest_54, MultipleEdgesIndependent_54) {
    Edge edge2;
    edge_.set_critical_path_weight(100);
    edge2.set_critical_path_weight(200);
    
    EXPECT_EQ(100, edge_.critical_path_weight());
    EXPECT_EQ(200, edge2.critical_path_weight());
}
