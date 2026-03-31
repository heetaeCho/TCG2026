#include "gtest/gtest.h"
#include "graph.h"

class EdgePriorityGreaterTest_69 : public ::testing::Test {
protected:
  EdgePriorityGreater greater;
  EdgePriorityLess less;
};

TEST_F(EdgePriorityGreaterTest_69, BothEdgesDefaultConstructed_69) {
  Edge e1, e2;
  // Two default edges should have equal priority; neither should be "greater"
  bool result = greater(&e1, &e2);
  // With default edges, the result should be consistent
  // If less(e2, e1) is false, greater(e1, e2) should be false
  EXPECT_EQ(result, less(&e2, &e1));
}

TEST_F(EdgePriorityGreaterTest_69, GreaterIsReversedLess_69) {
  Edge e1, e2;
  e1.set_critical_path_weight(100);
  e2.set_critical_path_weight(50);

  // greater(e1, e2) should equal less(e2, e1)
  EXPECT_EQ(greater(&e1, &e2), less(&e2, &e1));
  // greater(e2, e1) should equal less(e1, e2)
  EXPECT_EQ(greater(&e2, &e1), less(&e1, &e2));
}

TEST_F(EdgePriorityGreaterTest_69, HigherCriticalPathWeightFirst_69) {
  Edge e1, e2;
  e1.set_critical_path_weight(200);
  e2.set_critical_path_weight(100);

  // e1 has higher critical path weight, so in a "greater" comparator
  // (which reverses "less"), e1 should come first (greater returns true
  // if e1 has higher priority than e2, meaning less(e2, e1) is true)
  bool g12 = greater(&e1, &e2);
  bool g21 = greater(&e2, &e1);

  // They should not both be true (antisymmetry)
  EXPECT_FALSE(g12 && g21);
  // At least one should differ (they are not equal priority)
  EXPECT_NE(g12, g21);
}

TEST_F(EdgePriorityGreaterTest_69, EqualCriticalPathWeight_69) {
  Edge e1, e2;
  e1.set_critical_path_weight(100);
  e2.set_critical_path_weight(100);

  // Same critical path weight; neither strictly greater
  // Reflexivity check: greater(e, e) should be false for strict ordering
  EXPECT_FALSE(greater(&e1, &e1));
  EXPECT_FALSE(greater(&e2, &e2));
}

TEST_F(EdgePriorityGreaterTest_69, Irreflexivity_69) {
  Edge e;
  e.set_critical_path_weight(42);
  // A strict ordering must be irreflexive
  EXPECT_FALSE(greater(&e, &e));
}

TEST_F(EdgePriorityGreaterTest_69, ConsistencyWithLess_69) {
  Edge e1, e2, e3;
  e1.set_critical_path_weight(300);
  e2.set_critical_path_weight(200);
  e3.set_critical_path_weight(100);

  // Verify that greater(a,b) == less(b,a) for all pairs
  EXPECT_EQ(greater(&e1, &e2), less(&e2, &e1));
  EXPECT_EQ(greater(&e1, &e3), less(&e3, &e1));
  EXPECT_EQ(greater(&e2, &e3), less(&e3, &e2));
  EXPECT_EQ(greater(&e2, &e1), less(&e1, &e2));
  EXPECT_EQ(greater(&e3, &e1), less(&e1, &e3));
  EXPECT_EQ(greater(&e3, &e2), less(&e2, &e3));
}

TEST_F(EdgePriorityGreaterTest_69, NegativeCriticalPathWeights_69) {
  Edge e1, e2;
  e1.set_critical_path_weight(-1);
  e2.set_critical_path_weight(-100);

  // Verify consistency even with negative weights
  EXPECT_EQ(greater(&e1, &e2), less(&e2, &e1));
  EXPECT_EQ(greater(&e2, &e1), less(&e1, &e2));
}

TEST_F(EdgePriorityGreaterTest_69, ZeroCriticalPathWeight_69) {
  Edge e1, e2;
  e1.set_critical_path_weight(0);
  e2.set_critical_path_weight(0);

  EXPECT_FALSE(greater(&e1, &e2) && greater(&e2, &e1));
}

TEST_F(EdgePriorityGreaterTest_69, LargeWeightDifference_69) {
  Edge e1, e2;
  e1.set_critical_path_weight(INT64_MAX);
  e2.set_critical_path_weight(0);

  EXPECT_EQ(greater(&e1, &e2), less(&e2, &e1));
  EXPECT_EQ(greater(&e2, &e1), less(&e1, &e2));
  // They should not be considered equal
  EXPECT_TRUE(greater(&e1, &e2) || greater(&e2, &e1));
}

TEST_F(EdgePriorityGreaterTest_69, Antisymmetry_69) {
  Edge e1, e2;
  e1.set_critical_path_weight(10);
  e2.set_critical_path_weight(20);

  // If greater(e1, e2) is true, then greater(e2, e1) must be false
  if (greater(&e1, &e2)) {
    EXPECT_FALSE(greater(&e2, &e1));
  }
  if (greater(&e2, &e1)) {
    EXPECT_FALSE(greater(&e1, &e2));
  }
}

TEST_F(EdgePriorityGreaterTest_69, TransitivityCheck_69) {
  Edge e1, e2, e3;
  e1.set_critical_path_weight(300);
  e2.set_critical_path_weight(200);
  e3.set_critical_path_weight(100);

  // Find the ordering direction
  // If greater(e1, e2) and greater(e2, e3), then greater(e1, e3) must hold
  if (greater(&e1, &e2) && greater(&e2, &e3)) {
    EXPECT_TRUE(greater(&e1, &e3));
  }
  if (greater(&e3, &e2) && greater(&e2, &e1)) {
    EXPECT_TRUE(greater(&e3, &e1));
  }
}
