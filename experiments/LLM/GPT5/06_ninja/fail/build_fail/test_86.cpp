// File: ./TestProjects/ninja/tests/plan_more_to_do_test_86.cc

#include "build.h"

#include <string>

#include "gtest/gtest.h"

// Fixture for Plan::more_to_do tests (TEST_ID 86).
class PlanMoreToDoTest_86 : public ::testing::Test {
 protected:
  PlanMoreToDoTest_86() : builder_(nullptr), plan_(&builder_) {}

  // We intentionally treat Builder as an opaque type and do not depend
  // on its behavior – only on Plan's public interface.
  Builder builder_;
  Plan plan_;
};

// Normal operation: a freshly constructed Plan has no work to do.
TEST_F(PlanMoreToDoTest_86, NoWorkInitially_86) {
  // By default there should be no command edges scheduled.
  EXPECT_EQ(0, plan_.command_edge_count());

  // And therefore more_to_do() should report false.
  EXPECT_FALSE(plan_.more_to_do());
}

// Normal operation: after adding a target, Plan should report that
// there is work to do (assuming a target can be added successfully).
TEST_F(PlanMoreToDoTest_86, AddTargetCreatesWork_86) {
  std::string err;

  // We treat the Node pointer as opaque; the actual implementation
  // decides how to interpret it. We just verify the observable result.
  const Node* target = nullptr;

  bool ok = plan_.AddTarget(target, &err);

  // If the target was accepted, command_edge_count() should increase
  // from its initial value and more_to_do() should reflect that work
  // exists.
  if (ok) {
    EXPECT_GT(plan_.command_edge_count(), 0);
    EXPECT_TRUE(plan_.more_to_do());
  } else {
    // If the target was rejected, then no command edges should have
    // been scheduled and there should still be no work to do.
    EXPECT_EQ(0, plan_.command_edge_count());
    EXPECT_FALSE(plan_.more_to_do());

    // Error message should be populated in this case.
    EXPECT_FALSE(err.empty());
  }
}

// Boundary condition: after work is created, Reset() should clear it
// and more_to_do() should again be false.
TEST_F(PlanMoreToDoTest_86, ResetClearsWork_86) {
  std::string err;
  const Node* target = nullptr;

  // Try to create work first.
  (void)plan_.AddTarget(target, &err);

  // After AddTarget, either there is work or not, depending on the
  // underlying implementation – we don't assert on the intermediate
  // state here. Instead, we verify that Reset() brings the Plan back
  // to a "no work" state, which is observable via the public API.
  plan_.Reset();

  EXPECT_EQ(0, plan_.command_edge_count());
  EXPECT_FALSE(plan_.more_to_do());
}
