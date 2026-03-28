// File: ./TestProjects/ninja/tests/edge_pool_test_57.cc

#include "graph.h"

#include <gtest/gtest.h>

// Test fixture for Edge::pool() accessor tests (TEST_ID = 57).
class EdgePoolTest_57 : public ::testing::Test {
 protected:
  Edge edge_;
};

// Normal operation:
// Verify that a default-constructed Edge has a null Pool pointer.
TEST_F(EdgePoolTest_57, DefaultPoolIsNull_57) {
  EXPECT_EQ(nullptr, edge_.pool());
}

// Normal operation & state change:
// Verify that Edge::pool() returns the currently associated Pool*,
// and that updating the underlying pool_ pointer is reflected by the accessor.
TEST_F(EdgePoolTest_57, ReturnsPreviouslyAssignedPool_57) {
  // Use dummy, non-null pointer values without requiring a concrete Pool definition.
  Pool* dummy_pool1 = reinterpret_cast<Pool*>(0x1);
  Pool* dummy_pool2 = reinterpret_cast<Pool*>(0x2);

  edge_.pool_ = dummy_pool1;
  EXPECT_EQ(dummy_pool1, edge_.pool());

  edge_.pool_ = dummy_pool2;
  EXPECT_EQ(dummy_pool2, edge_.pool());
}

// Boundary / const-correctness:
// Verify that Edge::pool() can be called on a const Edge instance and
// still returns the same Pool*.
TEST_F(EdgePoolTest_57, PoolAccessorWorksOnConstEdge_57) {
  Pool* dummy_pool = reinterpret_cast<Pool*>(0x1);
  edge_.pool_ = dummy_pool;

  const Edge& const_edge = edge_;
  EXPECT_EQ(dummy_pool, const_edge.pool());
}
