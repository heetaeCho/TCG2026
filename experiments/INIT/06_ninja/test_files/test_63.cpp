// File: edgecmp_test_63.cc

#include "graph.h"

#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <algorithm>
#include <limits>

class EdgeCmpTest_63 : public ::testing::Test {
protected:
  EdgeCmp cmp_;
};

// Normal operation: a.id_ < b.id_ → true
TEST_F(EdgeCmpTest_63, ReturnsTrueWhenFirstIdLess_63) {
  Edge a;
  Edge b;

  a.id_ = 1u;
  b.id_ = 2u;

  EXPECT_TRUE(cmp_(&a, &b));
}

// Normal operation: a.id_ > b.id_ → false
TEST_F(EdgeCmpTest_63, ReturnsFalseWhenFirstIdGreater_63) {
  Edge a;
  Edge b;

  a.id_ = 5u;
  b.id_ = 3u;

  EXPECT_FALSE(cmp_(&a, &b));
}

// Boundary / equality: a.id_ == b.id_ → false
TEST_F(EdgeCmpTest_63, ReturnsFalseWhenIdsAreEqual_63) {
  Edge a;
  Edge b;

  a.id_ = 10u;
  b.id_ = 10u;

  EXPECT_FALSE(cmp_(&a, &b));
}

// Boundary: same pointer passed twice → false (not strictly less)
TEST_F(EdgeCmpTest_63, ReturnsFalseWhenComparingSamePointer_63) {
  Edge a;
  a.id_ = 42u;

  EXPECT_FALSE(cmp_(&a, &a));
}

// Usage in standard container: std::set with EdgeCmp orders by id_
TEST_F(EdgeCmpTest_63, OrdersEdgesByIdInStdSet_63) {
  Edge e1;
  Edge e2;
  Edge e3;

  e1.id_ = 10u;
  e2.id_ = 5u;
  e3.id_ = 7u;

  std::set<const Edge*, EdgeCmp> edge_set;
  edge_set.insert(&e1);
  edge_set.insert(&e2);
  edge_set.insert(&e3);

  std::vector<size_t> ordered_ids;
  for (const Edge* e : edge_set) {
    ordered_ids.push_back(e->id_);
  }

  ASSERT_EQ(ordered_ids.size(), 3u);
  EXPECT_EQ(ordered_ids[0], 5u);
  EXPECT_EQ(ordered_ids[1], 7u);
  EXPECT_EQ(ordered_ids[2], 10u);
}

// Boundary values: handles 0 and max size_t correctly
TEST_F(EdgeCmpTest_63, HandlesBoundaryIdValues_63) {
  Edge min_edge;
  Edge max_edge;

  min_edge.id_ = 0u;
  max_edge.id_ = std::numeric_limits<size_t>::max();

  EXPECT_TRUE(cmp_(&min_edge, &max_edge));
  EXPECT_FALSE(cmp_(&max_edge, &min_edge));
}
