// File: ./TestProjects/ninja/tests/node_dyndep_pending_test_42.cc

#include "graph.h"

#include "gtest/gtest.h"

class NodeDyndepPendingTest_42 : public ::testing::Test {
 protected:
  NodeDyndepPendingTest_42()
      : node_("out.o", 0) {}

  Node node_;
};

// Verify that a freshly constructed Node is not dyndep-pending.
TEST_F(NodeDyndepPendingTest_42, DefaultIsNotPending_42) {
  EXPECT_FALSE(node_.dyndep_pending());
}

// Verify that setting dyndep_pending to true is observable via the getter.
TEST_F(NodeDyndepPendingTest_42, SetPendingTrue_42) {
  node_.set_dyndep_pending(true);
  EXPECT_TRUE(node_.dyndep_pending());
}

// Verify that setting dyndep_pending to false clears a previously true state.
TEST_F(NodeDyndepPendingTest_42, SetPendingFalseClears_42) {
  node_.set_dyndep_pending(true);
  ASSERT_TRUE(node_.dyndep_pending());

  node_.set_dyndep_pending(false);
  EXPECT_FALSE(node_.dyndep_pending());
}

// Verify that multiple updates always reflect the last value that was set.
TEST_F(NodeDyndepPendingTest_42, MultipleUpdatesReflectLastValue_42) {
  node_.set_dyndep_pending(true);
  EXPECT_TRUE(node_.dyndep_pending());

  node_.set_dyndep_pending(false);
  EXPECT_FALSE(node_.dyndep_pending());

  node_.set_dyndep_pending(true);
  EXPECT_TRUE(node_.dyndep_pending());
}
