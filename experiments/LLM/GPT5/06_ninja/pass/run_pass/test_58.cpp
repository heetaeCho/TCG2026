// File: edge_weight_test_58.cc

#include "graph.h"

#include <gtest/gtest.h>

class EdgeWeightTest_58 : public ::testing::Test {
protected:
  Edge edge_;
};

// Normal operation: default-constructed Edge should have a well-defined weight.
// Based on the given implementation snippet, this is expected to be 1.
TEST_F(EdgeWeightTest_58, DefaultConstructedEdgeWeightIsOne_58) {
  EXPECT_EQ(1, edge_.weight());
}

// Normal operation: calling weight() multiple times should be stable and
// not modify any observable state.
TEST_F(EdgeWeightTest_58, MultipleCallsReturnSameValue_58) {
  int first = edge_.weight();
  int second = edge_.weight();
  int third = edge_.weight();

  EXPECT_EQ(1, first);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

// Interface / const-correctness: weight() is declared const; it should be
// callable on a const Edge and return the same observable value.
TEST_F(EdgeWeightTest_58, ConstEdgeWeightIsAccessibleAndOne_58) {
  const Edge& const_edge_ref = edge_;
  EXPECT_EQ(1, const_edge_ref.weight());
}
