// File: state_weighted_edge_cmp_test_79.cc

#include "state.h"
#include "graph.h"

#include <set>

#include "gtest/gtest.h"

// NOTE:
// These tests treat WeightedEdgeCmp as a black box and verify only observable
// behavior via its public operator() and its use inside std::set. We do not
// rely on or re-implement any internal logic beyond what is visible from the
// interface and its effects.

// Helper alias in case the header does not already provide one.
using TestDelayedEdges_79 = std::set<Edge*, WeightedEdgeCmp>;

// 1) Boundary behavior with nullptrs: both arguments nullptr.
TEST(WeightedEdgeCmpTest_79, BothNullPointersAreEquivalent_79) {
  WeightedEdgeCmp cmp;
  Edge* a = nullptr;
  Edge* b = nullptr;

  // Comparator should not consider a nullptr "less than" itself.
  EXPECT_FALSE(cmp(a, b));
}

// 2) Boundary behavior with nullptrs: left is nullptr, right is non-nullptr.
TEST(WeightedEdgeCmpTest_79, NullLeftIsLessThanNonNullRight_79) {
  WeightedEdgeCmp cmp;
  Edge* a = nullptr;
  Edge e;
  Edge* b = &e;

  // By design, a null edge should compare "less" than a valid edge.
  EXPECT_TRUE(cmp(a, b));
}

// 3) Boundary behavior with nullptrs: left is non-nullptr, right is nullptr.
TEST(WeightedEdgeCmpTest_79, NonNullLeftIsNotLessThanNullRight_79) {
  WeightedEdgeCmp cmp;
  Edge e;
  Edge* a = &e;
  Edge* b = nullptr;

  // A valid edge should not compare "less" than a null edge.
  EXPECT_FALSE(cmp(a, b));
}

// 4) Normal operation in a std::set: nullptr ordering vs non-nullptrs.
TEST(WeightedEdgeCmpTest_79, SetOrdersNullEdgeFirst_79) {
  TestDelayedEdges_79 delayed_edges;

  Edge e1;
  Edge e2;

  Edge* null_edge = nullptr;

  delayed_edges.insert(&e1);
  delayed_edges.insert(&e2);
  delayed_edges.insert(null_edge);

  ASSERT_EQ(delayed_edges.size(), 3u);

  // Because the comparator treats nullptr as "less", it should appear first.
  auto it = delayed_edges.begin();
  ASSERT_NE(it, delayed_edges.end());
  EXPECT_EQ(*it, null_edge);
}

// 5) Comparator antisymmetry for non-null edges:
//    it should never say both a < b and b < a for valid Edge pointers.
TEST(WeightedEdgeCmpTest_79, ComparatorIsAntisymmetricForNonNullEdges_79) {
  WeightedEdgeCmp cmp;

  Edge e1;
  Edge e2;

  Edge* a = &e1;
  Edge* b = &e2;

  bool a_less_b = cmp(a, b);
  bool b_less_a = cmp(b, a);

  // A strict-weak-order comparator must not have both comparisons true.
  EXPECT_FALSE(a_less_b && b_less_a);
}
