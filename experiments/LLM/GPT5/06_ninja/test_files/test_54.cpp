// File: ./TestProjects/ninja/tests/edge_critical_path_weight_test_54.cc

#include "graph.h"

#include <gtest/gtest.h>
#include <limits>

class EdgeCriticalPathWeightTest_54 : public ::testing::Test {
 protected:
  Edge edge_;
};

// Normal operation: default-constructed Edge has the expected initial
// critical path weight (observable via the public getter).
TEST_F(EdgeCriticalPathWeightTest_54, DefaultCriticalPathWeightIsMinusOne_54) {
  EXPECT_EQ(-1, edge_.critical_path_weight());
}

// Normal operation: setting a positive critical path weight is reflected
// by the getter.
TEST_F(EdgeCriticalPathWeightTest_54, SetPositiveCriticalPathWeight_54) {
  const int64_t kValue = 42;
  edge_.set_critical_path_weight(kValue);

  EXPECT_EQ(kValue, edge_.critical_path_weight());
}

// Boundary condition: setting the critical path weight to zero.
TEST_F(EdgeCriticalPathWeightTest_54, SetZeroCriticalPathWeight_54) {
  const int64_t kValue = 0;
  edge_.set_critical_path_weight(kValue);

  EXPECT_EQ(kValue, edge_.critical_path_weight());
}

// Boundary condition: setting a negative critical path weight.
TEST_F(EdgeCriticalPathWeightTest_54, SetNegativeCriticalPathWeight_54) {
  const int64_t kValue = -5;
  edge_.set_critical_path_weight(kValue);

  EXPECT_EQ(kValue, edge_.critical_path_weight());
}

// Boundary condition: setting extreme int64_t values should be preserved.
TEST_F(EdgeCriticalPathWeightTest_54, SetExtremeCriticalPathWeights_54) {
  const int64_t kMax = std::numeric_limits<int64_t>::max();
  const int64_t kMin = std::numeric_limits<int64_t>::min();

  edge_.set_critical_path_weight(kMax);
  EXPECT_EQ(kMax, edge_.critical_path_weight());

  edge_.set_critical_path_weight(kMin);
  EXPECT_EQ(kMin, edge_.critical_path_weight());
}

// Behavioral check: multiple calls to the setter should result in
// the getter returning the most recently set value.
TEST_F(EdgeCriticalPathWeightTest_54, MultipleSetsUseLastValue_54) {
  edge_.set_critical_path_weight(10);
  edge_.set_critical_path_weight(20);
  edge_.set_critical_path_weight(30);

  EXPECT_EQ(30, edge_.critical_path_weight());
}
