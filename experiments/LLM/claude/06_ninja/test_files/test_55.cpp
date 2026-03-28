#include "gtest/gtest.h"
#include "graph.h"

class EdgeSetCriticalPathWeightTest_55 : public ::testing::Test {
protected:
    Edge edge;
};

TEST_F(EdgeSetCriticalPathWeightTest_55, DefaultCriticalPathWeightIsNegativeOne_55) {
    // The default value of critical_path_weight_ should be -1
    EXPECT_EQ(edge.critical_path_weight(), -1);
}

TEST_F(EdgeSetCriticalPathWeightTest_55, SetPositiveValue_55) {
    edge.set_critical_path_weight(100);
    EXPECT_EQ(edge.critical_path_weight(), 100);
}

TEST_F(EdgeSetCriticalPathWeightTest_55, SetZero_55) {
    edge.set_critical_path_weight(0);
    EXPECT_EQ(edge.critical_path_weight(), 0);
}

TEST_F(EdgeSetCriticalPathWeightTest_55, SetNegativeValue_55) {
    edge.set_critical_path_weight(-42);
    EXPECT_EQ(edge.critical_path_weight(), -42);
}

TEST_F(EdgeSetCriticalPathWeightTest_55, SetLargePositiveValue_55) {
    int64_t large_value = INT64_MAX;
    edge.set_critical_path_weight(large_value);
    EXPECT_EQ(edge.critical_path_weight(), large_value);
}

TEST_F(EdgeSetCriticalPathWeightTest_55, SetLargeNegativeValue_55) {
    int64_t min_value = INT64_MIN;
    edge.set_critical_path_weight(min_value);
    EXPECT_EQ(edge.critical_path_weight(), min_value);
}

TEST_F(EdgeSetCriticalPathWeightTest_55, SetValueMultipleTimes_55) {
    edge.set_critical_path_weight(10);
    EXPECT_EQ(edge.critical_path_weight(), 10);

    edge.set_critical_path_weight(200);
    EXPECT_EQ(edge.critical_path_weight(), 200);

    edge.set_critical_path_weight(-5);
    EXPECT_EQ(edge.critical_path_weight(), -5);
}

TEST_F(EdgeSetCriticalPathWeightTest_55, SetBackToDefault_55) {
    edge.set_critical_path_weight(42);
    EXPECT_EQ(edge.critical_path_weight(), 42);

    edge.set_critical_path_weight(-1);
    EXPECT_EQ(edge.critical_path_weight(), -1);
}

TEST_F(EdgeSetCriticalPathWeightTest_55, SetOne_55) {
    edge.set_critical_path_weight(1);
    EXPECT_EQ(edge.critical_path_weight(), 1);
}

TEST_F(EdgeSetCriticalPathWeightTest_55, SetNegativeOne_55) {
    edge.set_critical_path_weight(-1);
    EXPECT_EQ(edge.critical_path_weight(), -1);
}

TEST_F(EdgeSetCriticalPathWeightTest_55, SetSameValueTwice_55) {
    edge.set_critical_path_weight(999);
    EXPECT_EQ(edge.critical_path_weight(), 999);

    edge.set_critical_path_weight(999);
    EXPECT_EQ(edge.critical_path_weight(), 999);
}
