#include "gtest/gtest.h"
#include "graph.h"
#include "state.h"

// We need to work with Edge objects. In ninja, Edges are typically created
// through State. We'll create minimal setups.

class EdgePriorityQueueTest_70 : public ::testing::Test {
 protected:
  void SetUp() override {
    queue_.clear();
  }

  EdgePriorityQueue queue_;
  State state_;

  // Helper to create an edge via the State object
  Edge* CreateEdge() {
    Rule* rule = new Rule("testrule");
    Edge* edge = state_.AddEdge(rule);
    return edge;
  }
};

TEST_F(EdgePriorityQueueTest_70, InitiallyEmpty_70) {
  EXPECT_TRUE(queue_.empty());
  EXPECT_EQ(0u, queue_.size());
}

TEST_F(EdgePriorityQueueTest_70, ClearOnEmptyQueue_70) {
  // Clearing an already empty queue should not cause issues
  queue_.clear();
  EXPECT_TRUE(queue_.empty());
  EXPECT_EQ(0u, queue_.size());
}

TEST_F(EdgePriorityQueueTest_70, PushSingleElement_70) {
  Edge* edge = CreateEdge();
  queue_.push(edge);
  EXPECT_FALSE(queue_.empty());
  EXPECT_EQ(1u, queue_.size());
  EXPECT_EQ(edge, queue_.top());
}

TEST_F(EdgePriorityQueueTest_70, ClearAfterPush_70) {
  Edge* edge = CreateEdge();
  queue_.push(edge);
  EXPECT_EQ(1u, queue_.size());

  queue_.clear();
  EXPECT_TRUE(queue_.empty());
  EXPECT_EQ(0u, queue_.size());
}

TEST_F(EdgePriorityQueueTest_70, ClearAfterMultiplePushes_70) {
  Edge* e1 = CreateEdge();
  Edge* e2 = CreateEdge();
  Edge* e3 = CreateEdge();

  queue_.push(e1);
  queue_.push(e2);
  queue_.push(e3);
  EXPECT_EQ(3u, queue_.size());

  queue_.clear();
  EXPECT_TRUE(queue_.empty());
  EXPECT_EQ(0u, queue_.size());
}

TEST_F(EdgePriorityQueueTest_70, PushAndPop_70) {
  Edge* edge = CreateEdge();
  queue_.push(edge);
  EXPECT_FALSE(queue_.empty());

  Edge* top = queue_.top();
  queue_.pop();
  EXPECT_TRUE(queue_.empty());
  EXPECT_EQ(edge, top);
}

TEST_F(EdgePriorityQueueTest_70, PushMultipleAndPopAll_70) {
  Edge* e1 = CreateEdge();
  Edge* e2 = CreateEdge();
  Edge* e3 = CreateEdge();

  queue_.push(e1);
  queue_.push(e2);
  queue_.push(e3);
  EXPECT_EQ(3u, queue_.size());

  queue_.pop();
  EXPECT_EQ(2u, queue_.size());
  queue_.pop();
  EXPECT_EQ(1u, queue_.size());
  queue_.pop();
  EXPECT_TRUE(queue_.empty());
}

TEST_F(EdgePriorityQueueTest_70, ClearThenPushAgain_70) {
  Edge* e1 = CreateEdge();
  Edge* e2 = CreateEdge();

  queue_.push(e1);
  queue_.clear();
  EXPECT_TRUE(queue_.empty());

  // Queue should be reusable after clear
  queue_.push(e2);
  EXPECT_EQ(1u, queue_.size());
  EXPECT_EQ(e2, queue_.top());
}

TEST_F(EdgePriorityQueueTest_70, MultipleClearCalls_70) {
  Edge* e1 = CreateEdge();
  queue_.push(e1);

  queue_.clear();
  queue_.clear();
  queue_.clear();

  EXPECT_TRUE(queue_.empty());
  EXPECT_EQ(0u, queue_.size());
}

TEST_F(EdgePriorityQueueTest_70, SizeAfterMixedOperations_70) {
  Edge* e1 = CreateEdge();
  Edge* e2 = CreateEdge();
  Edge* e3 = CreateEdge();

  queue_.push(e1);
  queue_.push(e2);
  EXPECT_EQ(2u, queue_.size());

  queue_.pop();
  EXPECT_EQ(1u, queue_.size());

  queue_.push(e3);
  EXPECT_EQ(2u, queue_.size());

  queue_.clear();
  EXPECT_EQ(0u, queue_.size());
}
