// File: ./TestProjects/ninja/tests/edge_priority_greater_test_69.cc

#include "graph.h"

#include "gtest/gtest.h"

// Test fixture for EdgePriorityGreater / EdgePriorityLess
class EdgePriorityGreaterTest_69 : public ::testing::Test {
protected:
  EdgePriorityLess less_;
  EdgePriorityGreater greater_;

  Edge e1_;
  Edge e2_;
};

// Verifies that EdgePriorityGreater behaves consistently with EdgePriorityLess
// when comparing the same Edge pointer.
TEST_F(EdgePriorityGreaterTest_69, CompareSameEdgeDelegatesToLess_69) {
  Edge* edge = &e1_;

  // Treat EdgePriorityLess as a black box and only relate Greater to Less.
  const bool less_result = less_(edge, edge);

  // EdgePriorityGreater(e, e) must match EdgePriorityLess(e, e) with reversed args,
  // which is still (e, e).
  EXPECT_EQ(greater_(edge, edge), less_result);
}

// Verifies the relationship between EdgePriorityGreater and EdgePriorityLess
// when comparing two different edges.
TEST_F(EdgePriorityGreaterTest_69, CompareTwoDifferentEdgesSymmetryWithLess_69) {
  Edge* a = &e1_;
  Edge* b = &e2_;

  // We do not assume anything about which one is "less".
  const bool less_ab = less_(a, b);
  const bool less_ba = less_(b, a);

  // By definition, Greater(a, b) should behave like Less(b, a).
  EXPECT_EQ(greater_(a, b), less_ba);
  EXPECT_EQ(greater_(b, a), less_ab);
}

// Verifies that the EdgePriorityGreater functor consistently mirrors
// EdgePriorityLess with reversed arguments across multiple edge instances.
TEST_F(EdgePriorityGreaterTest_69, MultipleEdgesConsistencyWithLess_69) {
  Edge edges[3];  // Default-constructed edges; we don't rely on their internals.

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      Edge* e_i = &edges[i];
      Edge* e_j = &edges[j];

      // For all pairs (e_i, e_j), Greater(e_i, e_j) must equal Less(e_j, e_i).
      EXPECT_EQ(greater_(e_i, e_j), less_(e_j, e_i))
          << "Mismatch between EdgePriorityGreater and EdgePriorityLess "
             "for pair (" << i << ", " << j << ")";
    }
  }
}
