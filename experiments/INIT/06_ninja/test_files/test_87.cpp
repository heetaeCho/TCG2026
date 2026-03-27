// File: ./TestProjects/ninja/tests/plan_command_edge_count_test_87.cc

#include "build.h"

#include "gtest/gtest.h"

// TEST_ID: 87
// Unit tests for Plan::command_edge_count(), treating Plan as a black box
// and relying only on observable behavior via its public interface.

class PlanTest_87 : public ::testing::Test {
protected:
  PlanTest_87()
      : plan_(nullptr) {  // We only pass the pointer through; tests never dereference builder_.
  }

  Plan plan_;
};

// Verifies that a newly constructed Plan reports zero command edges.
// This matches the intuitive contract that, before any targets are added,
// there is no work scheduled.
TEST_F(PlanTest_87, DefaultCommandEdgeCountIsZero_87) {
  EXPECT_EQ(0, plan_.command_edge_count());
}

// Verifies that calling command_edge_count() repeatedly without mutating
// the Plan returns a consistent value.
TEST_F(PlanTest_87, CommandEdgeCountIsConsistentAcrossCalls_87) {
  int first = plan_.command_edge_count();
  int second = plan_.command_edge_count();
  EXPECT_EQ(first, second);
}

// Verifies that calling other const methods (like more_to_do) does not
// change the reported command edge count. This checks that read-only
// queries do not accidentally mutate the counter underlying
// command_edge_count().
TEST_F(PlanTest_87, CommandEdgeCountUnchangedByConstQuery_87) {
  int before = plan_.command_edge_count();

  // Call another const method that inspects, but should not mutate, the plan.
  (void)plan_.more_to_do();

  int after = plan_.command_edge_count();
  EXPECT_EQ(before, after);
}
