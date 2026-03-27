// File: edge_priority_less_test_68.cc

#include <gtest/gtest.h>

#include "graph.h"  // Contains definitions of Edge and EdgePriorityLess

class EdgePriorityLessTest_68 : public ::testing::Test {
 protected:
  // Helper to initialize an Edge with given critical path weight and id.
  void InitEdge(Edge* edge, int64_t critical_path_weight, size_t id) {
    ASSERT_NE(edge, nullptr);
    edge->set_critical_path_weight(critical_path_weight);
    edge->id_ = id;  // public field used by EdgePriorityLess
  }
};

// Normal operation: comparator orders by smaller critical_path_weight first.
TEST_F(EdgePriorityLessTest_68, FirstHasSmallerCriticalPath_68) {
  Edge e1;
  Edge e2;

  InitEdge(&e1, /*critical_path_weight=*/10, /*id=*/1);
  InitEdge(&e2, /*critical_path_weight=*/20, /*id=*/2);

  EdgePriorityLess less;
  EXPECT_TRUE(less(&e1, &e2));
  EXPECT_FALSE(less(&e2, &e1));
}

// Normal operation: comparator returns false when first has larger critical_path_weight.
TEST_F(EdgePriorityLessTest_68, FirstHasLargerCriticalPath_68) {
  Edge e1;
  Edge e2;

  InitEdge(&e1, /*critical_path_weight=*/30, /*id=*/1);
  InitEdge(&e2, /*critical_path_weight=*/10, /*id=*/2);

  EdgePriorityLess less;
  EXPECT_FALSE(less(&e1, &e2));
  EXPECT_TRUE(less(&e2, &e1));
}

// Tie on critical_path_weight: comparator breaks ties using id_,
// returning true when first.id_ > second.id_.
TEST_F(EdgePriorityLessTest_68, TieOnCriticalPath_FirstIdGreater_68) {
  Edge e1;
  Edge e2;

  InitEdge(&e1, /*critical_path_weight=*/50, /*id=*/5);
  InitEdge(&e2, /*critical_path_weight=*/50, /*id=*/3);

  EdgePriorityLess less;
  EXPECT_TRUE(less(&e1, &e2));
  EXPECT_FALSE(less(&e2, &e1));
}

// Tie on critical_path_weight: comparator returns false when first.id_ < second.id_.
TEST_F(EdgePriorityLessTest_68, TieOnCriticalPath_FirstIdSmaller_68) {
  Edge e1;
  Edge e2;

  InitEdge(&e1, /*critical_path_weight=*/50, /*id=*/2);
  InitEdge(&e2, /*critical_path_weight=*/50, /*id=*/7);

  EdgePriorityLess less;
  EXPECT_FALSE(less(&e1, &e2));
  EXPECT_TRUE(less(&e2, &e1));
}

// Boundary condition: same critical_path_weight and same id_
// should not be considered "less" in either direction.
TEST_F(EdgePriorityLessTest_68, TieOnCriticalPathAndId_68) {
  Edge e1;
  Edge e2;

  InitEdge(&e1, /*critical_path_weight=*/100, /*id=*/42);
  InitEdge(&e2, /*critical_path_weight=*/100, /*id=*/42);

  EdgePriorityLess less;
  EXPECT_FALSE(less(&e1, &e2));
  EXPECT_FALSE(less(&e2, &e1));
}
