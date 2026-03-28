#include "gtest/gtest.h"
#include "state.h"

// Test fixture for Pool class
class PoolTest_76 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that name() returns the name passed to the constructor
TEST_F(PoolTest_76, NameReturnsConstructedName_76) {
  Pool pool("test_pool", 5);
  EXPECT_EQ("test_pool", pool.name());
}

// Test that name() returns empty string when constructed with empty name
TEST_F(PoolTest_76, NameReturnsEmptyString_76) {
  Pool pool("", 0);
  EXPECT_EQ("", pool.name());
}

// Test that depth() returns the depth passed to the constructor
TEST_F(PoolTest_76, DepthReturnsConstructedDepth_76) {
  Pool pool("test_pool", 10);
  EXPECT_EQ(10, pool.depth());
}

// Test that depth() returns zero when constructed with zero depth
TEST_F(PoolTest_76, DepthReturnsZero_76) {
  Pool pool("zero_pool", 0);
  EXPECT_EQ(0, pool.depth());
}

// Test that current_use() starts at zero
TEST_F(PoolTest_76, CurrentUseStartsAtZero_76) {
  Pool pool("test_pool", 5);
  EXPECT_EQ(0, pool.current_use());
}

// Test is_valid() with positive depth
TEST_F(PoolTest_76, IsValidWithPositiveDepth_76) {
  Pool pool("valid_pool", 5);
  EXPECT_TRUE(pool.is_valid());
}

// Test is_valid() with zero depth (depth of 0 means infinite/no limit, which is valid)
TEST_F(PoolTest_76, IsValidWithZeroDepth_76) {
  Pool pool("zero_pool", 0);
  EXPECT_TRUE(pool.is_valid());
}

// Test is_valid() with negative depth
TEST_F(PoolTest_76, IsInvalidWithNegativeDepth_76) {
  Pool pool("invalid_pool", -1);
  EXPECT_FALSE(pool.is_valid());
}

// Test ShouldDelayEdge() when pool has no current use and positive depth
TEST_F(PoolTest_76, ShouldNotDelayEdgeWhenUnderLimit_76) {
  Pool pool("test_pool", 5);
  EXPECT_FALSE(pool.ShouldDelayEdge());
}

// Test ShouldDelayEdge() with zero depth (unlimited pool)
TEST_F(PoolTest_76, ShouldNotDelayEdgeWithZeroDepth_76) {
  Pool pool("unlimited_pool", 0);
  EXPECT_FALSE(pool.ShouldDelayEdge());
}

// Test that name with special characters is preserved
TEST_F(PoolTest_76, NameWithSpecialCharacters_76) {
  Pool pool("pool-with_special.chars/123", 3);
  EXPECT_EQ("pool-with_special.chars/123", pool.name());
}

// Test that a pool with depth 1 exists and has correct properties
TEST_F(PoolTest_76, PoolWithDepthOne_76) {
  Pool pool("single_pool", 1);
  EXPECT_EQ("single_pool", pool.name());
  EXPECT_EQ(1, pool.depth());
  EXPECT_EQ(0, pool.current_use());
  EXPECT_TRUE(pool.is_valid());
}

// Test that a pool with large depth is valid
TEST_F(PoolTest_76, PoolWithLargeDepth_76) {
  Pool pool("large_pool", 100000);
  EXPECT_EQ(100000, pool.depth());
  EXPECT_TRUE(pool.is_valid());
  EXPECT_FALSE(pool.ShouldDelayEdge());
}

// Test EdgeScheduled and EdgeFinished affect current_use
// We need an Edge to test this. We'll use State to create one.
#include "graph.h"

class PoolEdgeTest_76 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(PoolEdgeTest_76, EdgeScheduledIncreasesCurrentUse_76) {
  Pool pool("test_pool", 5);
  
  // Create a minimal edge with a weight
  Edge edge;
  edge.pool_ = &pool;
  edge.weight_ = 1;
  
  EXPECT_EQ(0, pool.current_use());
  pool.EdgeScheduled(edge);
  EXPECT_EQ(1, pool.current_use());
}

TEST_F(PoolEdgeTest_76, EdgeFinishedDecreasesCurrentUse_76) {
  Pool pool("test_pool", 5);
  
  Edge edge;
  edge.pool_ = &pool;
  edge.weight_ = 1;
  
  pool.EdgeScheduled(edge);
  EXPECT_EQ(1, pool.current_use());
  pool.EdgeFinished(edge);
  EXPECT_EQ(0, pool.current_use());
}

TEST_F(PoolEdgeTest_76, ShouldDelayEdgeWhenAtCapacity_76) {
  Pool pool("test_pool", 1);
  
  Edge edge;
  edge.pool_ = &pool;
  edge.weight_ = 1;
  
  EXPECT_FALSE(pool.ShouldDelayEdge());
  pool.EdgeScheduled(edge);
  EXPECT_TRUE(pool.ShouldDelayEdge());
}

TEST_F(PoolEdgeTest_76, MultipleEdgesScheduledAndFinished_76) {
  Pool pool("test_pool", 3);
  
  Edge edge1, edge2, edge3;
  edge1.pool_ = &pool;
  edge1.weight_ = 1;
  edge2.pool_ = &pool;
  edge2.weight_ = 1;
  edge3.pool_ = &pool;
  edge3.weight_ = 1;
  
  pool.EdgeScheduled(edge1);
  pool.EdgeScheduled(edge2);
  EXPECT_EQ(2, pool.current_use());
  EXPECT_FALSE(pool.ShouldDelayEdge());
  
  pool.EdgeScheduled(edge3);
  EXPECT_EQ(3, pool.current_use());
  EXPECT_TRUE(pool.ShouldDelayEdge());
  
  pool.EdgeFinished(edge1);
  EXPECT_EQ(2, pool.current_use());
  EXPECT_FALSE(pool.ShouldDelayEdge());
}

TEST_F(PoolEdgeTest_76, DelayEdgeAndRetrieveReadyEdges_76) {
  Pool pool("test_pool", 1);
  
  Edge edge1, edge2;
  edge1.pool_ = &pool;
  edge1.weight_ = 1;
  edge2.pool_ = &pool;
  edge2.weight_ = 1;
  
  // Schedule first edge, filling the pool
  pool.EdgeScheduled(edge1);
  EXPECT_TRUE(pool.ShouldDelayEdge());
  
  // Delay the second edge
  pool.DelayEdge(&edge2);
  
  // Finish the first edge
  pool.EdgeFinished(edge1);
  
  // Retrieve ready edges
  EdgePriorityQueue ready_queue;
  pool.RetrieveReadyEdges(&ready_queue);
  
  // The delayed edge should now be retrievable
  EXPECT_FALSE(ready_queue.empty());
}
