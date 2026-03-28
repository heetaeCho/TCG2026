#include "gtest/gtest.h"
#include "graph.h"

class EdgePriorityLessTest_68 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  EdgePriorityLess less_;
};

// Test that an edge with smaller critical_path_weight is "less" than one with larger
TEST_F(EdgePriorityLessTest_68, SmallerWeightIsLess_68) {
  Edge e1, e2;
  e1.set_critical_path_weight(10);
  e2.set_critical_path_weight(20);
  e1.id_ = 1;
  e2.id_ = 1;

  EXPECT_TRUE(less_(&e1, &e2));
  EXPECT_FALSE(less_(&e2, &e1));
}

// Test that an edge with larger critical_path_weight is not "less"
TEST_F(EdgePriorityLessTest_68, LargerWeightIsNotLess_68) {
  Edge e1, e2;
  e1.set_critical_path_weight(50);
  e2.set_critical_path_weight(30);
  e1.id_ = 1;
  e2.id_ = 1;

  EXPECT_FALSE(less_(&e1, &e2));
  EXPECT_TRUE(less_(&e2, &e1));
}

// Test that when critical_path_weights are equal, larger id_ is "less"
TEST_F(EdgePriorityLessTest_68, EqualWeightLargerIdIsLess_68) {
  Edge e1, e2;
  e1.set_critical_path_weight(10);
  e2.set_critical_path_weight(10);
  e1.id_ = 5;
  e2.id_ = 3;

  EXPECT_TRUE(less_(&e1, &e2));
  EXPECT_FALSE(less_(&e2, &e1));
}

// Test that when critical_path_weights are equal, smaller id_ is not "less"
TEST_F(EdgePriorityLessTest_68, EqualWeightSmallerIdIsNotLess_68) {
  Edge e1, e2;
  e1.set_critical_path_weight(10);
  e2.set_critical_path_weight(10);
  e1.id_ = 2;
  e2.id_ = 7;

  EXPECT_FALSE(less_(&e1, &e2));
  EXPECT_TRUE(less_(&e2, &e1));
}

// Test that identical edges (same weight, same id) are not less than each other
TEST_F(EdgePriorityLessTest_68, IdenticalEdgesNotLess_68) {
  Edge e1, e2;
  e1.set_critical_path_weight(10);
  e2.set_critical_path_weight(10);
  e1.id_ = 5;
  e2.id_ = 5;

  EXPECT_FALSE(less_(&e1, &e2));
  EXPECT_FALSE(less_(&e2, &e1));
}

// Test with zero critical_path_weight
TEST_F(EdgePriorityLessTest_68, ZeroWeightComparison_68) {
  Edge e1, e2;
  e1.set_critical_path_weight(0);
  e2.set_critical_path_weight(100);
  e1.id_ = 1;
  e2.id_ = 2;

  EXPECT_TRUE(less_(&e1, &e2));
  EXPECT_FALSE(less_(&e2, &e1));
}

// Test with negative critical_path_weight values
TEST_F(EdgePriorityLessTest_68, NegativeWeightComparison_68) {
  Edge e1, e2;
  e1.set_critical_path_weight(-5);
  e2.set_critical_path_weight(5);
  e1.id_ = 1;
  e2.id_ = 1;

  EXPECT_TRUE(less_(&e1, &e2));
  EXPECT_FALSE(less_(&e2, &e1));
}

// Test with both negative critical_path_weights
TEST_F(EdgePriorityLessTest_68, BothNegativeWeights_68) {
  Edge e1, e2;
  e1.set_critical_path_weight(-10);
  e2.set_critical_path_weight(-3);
  e1.id_ = 1;
  e2.id_ = 1;

  EXPECT_TRUE(less_(&e1, &e2));
  EXPECT_FALSE(less_(&e2, &e1));
}

// Test with large critical_path_weight values
TEST_F(EdgePriorityLessTest_68, LargeWeightValues_68) {
  Edge e1, e2;
  e1.set_critical_path_weight(INT64_MAX - 1);
  e2.set_critical_path_weight(INT64_MAX);
  e1.id_ = 1;
  e2.id_ = 1;

  EXPECT_TRUE(less_(&e1, &e2));
  EXPECT_FALSE(less_(&e2, &e1));
}

// Test with zero id when weights are equal
TEST_F(EdgePriorityLessTest_68, ZeroIdComparison_68) {
  Edge e1, e2;
  e1.set_critical_path_weight(10);
  e2.set_critical_path_weight(10);
  e1.id_ = 0;
  e2.id_ = 1;

  // e2 has larger id, so e2 should be less than e1
  EXPECT_FALSE(less_(&e1, &e2));
  EXPECT_TRUE(less_(&e2, &e1));
}

// Test strict weak ordering: irreflexivity
TEST_F(EdgePriorityLessTest_68, StrictWeakOrderingIrreflexivity_68) {
  Edge e;
  e.set_critical_path_weight(42);
  e.id_ = 7;

  EXPECT_FALSE(less_(&e, &e));
}

// Test that weight takes priority over id
TEST_F(EdgePriorityLessTest_68, WeightTakesPriorityOverId_68) {
  Edge e1, e2;
  e1.set_critical_path_weight(5);
  e2.set_critical_path_weight(10);
  // e1 has larger id, which would make it "less" if weights were equal
  // But since weights differ, weight should dominate
  e1.id_ = 100;
  e2.id_ = 1;

  EXPECT_TRUE(less_(&e1, &e2));
  EXPECT_FALSE(less_(&e2, &e1));
}

// Test with same weight and consecutive ids
TEST_F(EdgePriorityLessTest_68, SameWeightConsecutiveIds_68) {
  Edge e1, e2;
  e1.set_critical_path_weight(42);
  e2.set_critical_path_weight(42);
  e1.id_ = 10;
  e2.id_ = 9;

  // e1 has larger id, so e1 is "less"
  EXPECT_TRUE(less_(&e1, &e2));
  EXPECT_FALSE(less_(&e2, &e1));
}
