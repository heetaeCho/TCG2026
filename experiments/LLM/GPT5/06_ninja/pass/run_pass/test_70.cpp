// File: ./TestProjects/ninja/tests/edge_priority_queue_clear_test_70.cc

#include "graph.h"

#include "gtest/gtest.h"

// Fixture for EdgePriorityQueue tests (with TEST_ID in the name as requested).
class EdgePriorityQueueTest_70 : public ::testing::Test {
 protected:
  EdgePriorityQueue queue_;
};

// Normal operation: calling clear() on an empty queue should keep it empty.
TEST_F(EdgePriorityQueueTest_70, ClearOnEmptyQueue_70) {
  // Initial state: newly constructed priority queue should be empty.
  EXPECT_TRUE(queue_.empty());
  EXPECT_EQ(queue_.size(), 0u);

  // Act
  queue_.clear();

  // Still empty after clear.
  EXPECT_TRUE(queue_.empty());
  EXPECT_EQ(queue_.size(), 0u);
}

// Normal operation: clear() after a single push removes the element(s).
// Uses a single element so that the comparator is never invoked in reheapification
// (we treat the internal behavior as a black box and avoid depending on it).
TEST_F(EdgePriorityQueueTest_70, ClearAfterSinglePush_70) {
  Edge* edge = nullptr;  // Treated as an opaque pointer; we never dereference it.

  // Push a single element.
  queue_.push(edge);
  ASSERT_FALSE(queue_.empty());
  ASSERT_EQ(queue_.size(), 1u);

  // Act
  queue_.clear();

  // The queue should be logically reset.
  EXPECT_TRUE(queue_.empty());
  EXPECT_EQ(queue_.size(), 0u);
}

// Boundary / reuse case: queue can be reused normally after clear().
TEST_F(EdgePriorityQueueTest_70, ReuseQueueAfterClear_70) {
  Edge* edge = nullptr;

  // First use: push and then clear.
  queue_.push(edge);
  ASSERT_FALSE(queue_.empty());
  ASSERT_EQ(queue_.size(), 1u);

  queue_.clear();
  EXPECT_TRUE(queue_.empty());
  EXPECT_EQ(queue_.size(), 0u);

  // Second use: queue should behave like a fresh priority queue.
  Edge* edge2 = nullptr;
  queue_.push(edge2);

  EXPECT_FALSE(queue_.empty());
  EXPECT_EQ(queue_.size(), 1u);
}
