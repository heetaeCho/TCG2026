// File: ./TestProjects/ninja/tests/edge_is_order_only_test_61.cc

#include "graph.h"
#include "gtest/gtest.h"

class EdgeIsOrderOnlyTest_61 : public ::testing::Test {
 protected:
  Edge edge_;
};

// TEST_ID 61
// Case: No order-only deps => all valid indices should be non-order-only.
TEST_F(EdgeIsOrderOnlyTest_61, NoOrderOnlyDeps_AllIndicesNonOrderOnly_61) {
  edge_.inputs_.resize(3);     // indices: 0,1,2
  edge_.order_only_deps_ = 0;  // no order-only deps

  EXPECT_FALSE(edge_.is_order_only(0));
  EXPECT_FALSE(edge_.is_order_only(1));
  EXPECT_FALSE(edge_.is_order_only(2));
}

// TEST_ID 61
// Case: Exactly one order-only dep at the end => only last index is order-only.
TEST_F(EdgeIsOrderOnlyTest_61, SingleOrderOnlyDep_OnlyLastIndexIsOrderOnly_61) {
  edge_.inputs_.resize(3);     // indices: 0,1,2
  edge_.order_only_deps_ = 1;  // last one is order-only

  EXPECT_FALSE(edge_.is_order_only(0));
  EXPECT_FALSE(edge_.is_order_only(1));
  EXPECT_TRUE(edge_.is_order_only(2));
}

// TEST_ID 61
// Case: Multiple order-only deps at the end => last N indices are order-only.
TEST_F(EdgeIsOrderOnlyTest_61, MultipleOrderOnlyDeps_LastIndicesAreOrderOnly_61) {
  edge_.inputs_.resize(5);     // indices: 0,1,2,3,4
  edge_.order_only_deps_ = 2;  // indices 3,4 are order-only

  EXPECT_FALSE(edge_.is_order_only(0));
  EXPECT_FALSE(edge_.is_order_only(1));
  EXPECT_FALSE(edge_.is_order_only(2));
  EXPECT_TRUE(edge_.is_order_only(3));
  EXPECT_TRUE(edge_.is_order_only(4));
}

// TEST_ID 61
// Case: All inputs are order-only => every valid index is order-only.
TEST_F(EdgeIsOrderOnlyTest_61, AllInputsOrderOnly_AllIndicesOrderOnly_61) {
  edge_.inputs_.resize(4);     // indices: 0,1,2,3
  edge_.order_only_deps_ = 4;  // all are order-only

  EXPECT_TRUE(edge_.is_order_only(0));
  EXPECT_TRUE(edge_.is_order_only(1));
  EXPECT_TRUE(edge_.is_order_only(2));
  EXPECT_TRUE(edge_.is_order_only(3));
}
