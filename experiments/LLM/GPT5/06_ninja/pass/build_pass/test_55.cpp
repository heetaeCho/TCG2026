#include "graph.h"

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

class EdgeCriticalPathWeightTest_55 : public ::testing::Test {
protected:
  Edge edge_;
};

// Normal operation: setting a positive weight should be observable via the getter.
TEST_F(EdgeCriticalPathWeightTest_55, SetPositiveWeightUpdatesGetter_55) {
  int64_t weight = 123;
  edge_.set_critical_path_weight(weight);

  EXPECT_EQ(weight, edge_.critical_path_weight());
}

// Boundary condition: setting weight to zero should be reflected by the getter.
TEST_F(EdgeCriticalPathWeightTest_55, SetZeroWeightUpdatesGetter_55) {
  int64_t weight = 0;
  edge_.set_critical_path_weight(weight);

  EXPECT_EQ(weight, edge_.critical_path_weight());
}

// Boundary condition: setting a negative weight should be reflected by the getter.
TEST_F(EdgeCriticalPathWeightTest_55, SetNegativeWeightUpdatesGetter_55) {
  int64_t weight = -42;
  edge_.set_critical_path_weight(weight);

  EXPECT_EQ(weight, edge_.critical_path_weight());
}

// Extreme boundary: setting maximum int64_t should be handled and observable.
TEST_F(EdgeCriticalPathWeightTest_55, SetMaxInt64WeightUpdatesGetter_55) {
  int64_t weight = std::numeric_limits<int64_t>::max();
  edge_.set_critical_path_weight(weight);

  EXPECT_EQ(weight, edge_.critical_path_weight());
}

// Extreme boundary: setting minimum int64_t should be handled and observable.
TEST_F(EdgeCriticalPathWeightTest_55, SetMinInt64WeightUpdatesGetter_55) {
  int64_t weight = std::numeric_limits<int64_t>::min();
  edge_.set_critical_path_weight(weight);

  EXPECT_EQ(weight, edge_.critical_path_weight());
}
