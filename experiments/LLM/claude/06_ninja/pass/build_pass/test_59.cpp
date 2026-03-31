#include "gtest/gtest.h"
#include "graph.h"

class EdgeOutputsReadyTest_59 : public ::testing::Test {
protected:
  Edge edge;
};

TEST_F(EdgeOutputsReadyTest_59, DefaultOutputsReadyIsFalse_59) {
  // A default-constructed Edge should have outputs_ready_ = false
  EXPECT_FALSE(edge.outputs_ready());
}

TEST_F(EdgeOutputsReadyTest_59, OutputsReadyReturnsTrueWhenSet_59) {
  // When outputs_ready_ is set to true, outputs_ready() should return true
  edge.outputs_ready_ = true;
  EXPECT_TRUE(edge.outputs_ready());
}

TEST_F(EdgeOutputsReadyTest_59, OutputsReadyReturnsFalseWhenExplicitlyFalse_59) {
  // When outputs_ready_ is explicitly set to false, outputs_ready() should return false
  edge.outputs_ready_ = false;
  EXPECT_FALSE(edge.outputs_ready());
}

TEST_F(EdgeOutputsReadyTest_59, OutputsReadyReflectsToggle_59) {
  // Toggle outputs_ready_ and verify outputs_ready() reflects changes
  edge.outputs_ready_ = true;
  EXPECT_TRUE(edge.outputs_ready());

  edge.outputs_ready_ = false;
  EXPECT_FALSE(edge.outputs_ready());

  edge.outputs_ready_ = true;
  EXPECT_TRUE(edge.outputs_ready());
}

TEST_F(EdgeOutputsReadyTest_59, OutputsReadyIsConstMethod_59) {
  // Verify outputs_ready() can be called on a const Edge
  const Edge& const_edge = edge;
  EXPECT_FALSE(const_edge.outputs_ready());
}

TEST_F(EdgeOutputsReadyTest_59, OutputsReadyTrueOnConstEdge_59) {
  edge.outputs_ready_ = true;
  const Edge& const_edge = edge;
  EXPECT_TRUE(const_edge.outputs_ready());
}

TEST_F(EdgeOutputsReadyTest_59, MultipleEdgesIndependent_59) {
  // Verify that outputs_ready on different Edge instances are independent
  Edge edge2;
  edge.outputs_ready_ = true;
  edge2.outputs_ready_ = false;

  EXPECT_TRUE(edge.outputs_ready());
  EXPECT_FALSE(edge2.outputs_ready());
}
