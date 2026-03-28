// File: ./TestProjects/ninja/tests/edge_is_implicit_out_test_62.cc

#include "graph.h"

#include <gtest/gtest.h>

// Fixture for Edge::is_implicit_out tests (TEST_ID = 62)
class EdgeIsImplicitOutTest_62 : public ::testing::Test {
protected:
  Edge edge_;
};

// Normal operation: no implicit outputs -> all indices are explicit.
TEST_F(EdgeIsImplicitOutTest_62, NoImplicitOutputs_AllIndicesExplicit_62) {
  // Arrange
  edge_.outputs_.resize(3, nullptr);  // 3 outputs
  edge_.implicit_outs_ = 0;

  // Act & Assert
  EXPECT_FALSE(edge_.is_implicit_out(0));
  EXPECT_FALSE(edge_.is_implicit_out(1));
  EXPECT_FALSE(edge_.is_implicit_out(2));
}

// Normal operation: some implicit outputs at the end.
TEST_F(EdgeIsImplicitOutTest_62, SomeImplicitOutputs_LastNAreImplicit_62) {
  // Arrange
  edge_.outputs_.resize(5, nullptr);  // indices: 0 1 2 3 4
  edge_.implicit_outs_ = 2;           // last 2 (3,4) are implicit outputs

  // Act & Assert
  EXPECT_FALSE(edge_.is_implicit_out(0));  // explicit
  EXPECT_FALSE(edge_.is_implicit_out(1));  // explicit
  EXPECT_FALSE(edge_.is_implicit_out(2));  // explicit
  EXPECT_TRUE(edge_.is_implicit_out(3));   // implicit
  EXPECT_TRUE(edge_.is_implicit_out(4));   // implicit
}

// Boundary condition: all outputs are implicit.
TEST_F(EdgeIsImplicitOutTest_62, AllOutputsImplicit_AllIndicesImplicit_62) {
  // Arrange
  edge_.outputs_.resize(4, nullptr);  // indices: 0 1 2 3
  edge_.implicit_outs_ = 4;           // all 4 are implicit

  // Act & Assert
  EXPECT_TRUE(edge_.is_implicit_out(0));
  EXPECT_TRUE(edge_.is_implicit_out(1));
  EXPECT_TRUE(edge_.is_implicit_out(2));
  EXPECT_TRUE(edge_.is_implicit_out(3));
}

// Boundary condition: single output which is implicit.
TEST_F(EdgeIsImplicitOutTest_62, SingleOutputMarkedImplicit_62) {
  // Arrange
  edge_.outputs_.resize(1, nullptr);  // index: 0
  edge_.implicit_outs_ = 1;           // that single output is implicit

  // Act & Assert
  EXPECT_TRUE(edge_.is_implicit_out(0));
}

// Edge / exceptional boundary: zero outputs, index 0 behavior.
TEST_F(EdgeIsImplicitOutTest_62, ZeroOutputs_IndexZeroBehavior_62) {
  // Arrange
  edge_.outputs_.clear();
  edge_.implicit_outs_ = 0;

  // Act & Assert
  // Document and lock in the current observable behavior when called with
  // index 0 and no outputs configured.
  EXPECT_TRUE(edge_.is_implicit_out(0));
}
