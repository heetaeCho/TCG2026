// File: ./TestProjects/ninja/tests/node_set_dyndep_pending_test_43.cc

#include "graph.h"

#include <gtest/gtest.h>

class NodeSetDyndepPendingTest_43 : public ::testing::Test {
 protected:
  NodeSetDyndepPendingTest_43()
      : node_("path/to/file", /*slash_bits=*/0) {}

  Node node_;
};

// Normal operation: default state should be not pending.
TEST_F(NodeSetDyndepPendingTest_43, DefaultIsNotPending_43) {
  // Observable behavior right after construction.
  EXPECT_FALSE(node_.dyndep_pending());
}

// Normal operation: setting pending to true should be observable via getter.
TEST_F(NodeSetDyndepPendingTest_43, SetPendingTrue_UpdatesGetter_43) {
  node_.set_dyndep_pending(true);

  EXPECT_TRUE(node_.dyndep_pending());
}

// Normal operation: setting pending to false should be observable via getter.
TEST_F(NodeSetDyndepPendingTest_43, SetPendingFalse_UpdatesGetter_43) {
  node_.set_dyndep_pending(true);
  ASSERT_TRUE(node_.dyndep_pending());  // precondition check on observable state

  node_.set_dyndep_pending(false);

  EXPECT_FALSE(node_.dyndep_pending());
}

// Boundary/robustness: repeated calls with same value keep the state stable.
TEST_F(NodeSetDyndepPendingTest_43, RepeatedSetPendingCallsAreStable_43) {
  node_.set_dyndep_pending(true);
  EXPECT_TRUE(node_.dyndep_pending());

  node_.set_dyndep_pending(true);
  EXPECT_TRUE(node_.dyndep_pending());

  node_.set_dyndep_pending(false);
  EXPECT_FALSE(node_.dyndep_pending());

  node_.set_dyndep_pending(false);
  EXPECT_FALSE(node_.dyndep_pending());
}
