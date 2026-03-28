#include "gtest/gtest.h"
#include "build.h"
#include "graph.h"
#include "state.h"
#include "disk_interface.h"
#include "deps_log.h"
#include "build_log.h"
#include "util.h"
#include "test.h"

#include <string>

// Using the test infrastructure from ninja's test utilities
struct PlanTest_87 : public StateTestWithBuiltinRules {
  PlanTest_87() : builder_(NULL), plan_(&builder_) {}

  Builder builder_;
  Plan plan_;

  // Helper to add a simple edge and node to the state
  void AddSimpleEdge() {
    ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
      "build out: cat in\n"));
    GetNode("in")->MarkDirty();
    GetNode("out")->MarkDirty();
    auto* edge = GetNode("out")->in_edge();
    if (edge) edge->MarkDirty();
  }

  void AddMultipleEdges() {
    ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
      "build mid: cat in\n"
      "build out: cat mid\n"));
    GetNode("in")->MarkDirty();
    GetNode("mid")->MarkDirty();
    GetNode("out")->MarkDirty();
    if (GetNode("mid")->in_edge()) GetNode("mid")->in_edge()->MarkDirty();
    if (GetNode("out")->in_edge()) GetNode("out")->in_edge()->MarkDirty();
  }
};

// Test that command_edge_count is initially zero
TEST_F(PlanTest_87, InitialCommandEdgeCountIsZero_87) {
  EXPECT_EQ(0, plan_.command_edge_count());
}

// Test that more_to_do is initially false
TEST_F(PlanTest_87, InitialMoreToDoIsFalse_87) {
  EXPECT_FALSE(plan_.more_to_do());
}

// Test that adding a target increases command_edge_count
TEST_F(PlanTest_87, AddTargetIncreasesCommandEdgeCount_87) {
  AddSimpleEdge();

  std::string err;
  ASSERT_TRUE(plan_.AddTarget(GetNode("out"), &err));
  EXPECT_EQ("", err);

  // After adding a target that needs building, command_edge_count should be > 0
  EXPECT_GT(plan_.command_edge_count(), 0);
}

// Test that adding a target sets more_to_do to true
TEST_F(PlanTest_87, AddTargetSetsMoreToDo_87) {
  AddSimpleEdge();

  std::string err;
  ASSERT_TRUE(plan_.AddTarget(GetNode("out"), &err));
  EXPECT_EQ("", err);

  EXPECT_TRUE(plan_.more_to_do());
}

// Test adding multiple edges in a chain
TEST_F(PlanTest_87, AddTargetWithMultipleEdges_87) {
  AddMultipleEdges();

  std::string err;
  ASSERT_TRUE(plan_.AddTarget(GetNode("out"), &err));
  EXPECT_EQ("", err);

  // Two edges in the chain: in->mid and mid->out
  EXPECT_EQ(2, plan_.command_edge_count());
}

// Test FindWork returns work after adding a dirty target
TEST_F(PlanTest_87, FindWorkReturnsEdgeAfterAddTarget_87) {
  AddSimpleEdge();

  std::string err;
  ASSERT_TRUE(plan_.AddTarget(GetNode("out"), &err));
  EXPECT_EQ("", err);

  Edge* edge = plan_.FindWork();
  ASSERT_NE(nullptr, edge);
}

// Test FindWork returns NULL when no work is available
TEST_F(PlanTest_87, FindWorkReturnsNullWhenEmpty_87) {
  Edge* edge = plan_.FindWork();
  EXPECT_EQ(nullptr, edge);
}

// Test Reset brings plan back to initial state
TEST_F(PlanTest_87, ResetClearsPlan_87) {
  AddSimpleEdge();

  std::string err;
  ASSERT_TRUE(plan_.AddTarget(GetNode("out"), &err));
  EXPECT_EQ("", err);

  plan_.Reset();

  EXPECT_EQ(0, plan_.command_edge_count());
  EXPECT_FALSE(plan_.more_to_do());
}

// Test adding a target that is already up to date
TEST_F(PlanTest_87, AddUpToDateTargetDoesNotIncreaseCount_87) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "build out: cat in\n"));
  // Don't mark anything dirty

  std::string err;
  EXPECT_TRUE(plan_.AddTarget(GetNode("out"), &err));
  EXPECT_EQ("", err);
  EXPECT_EQ(0, plan_.command_edge_count());
}

// Test EdgeFinished after finding work
TEST_F(PlanTest_87, EdgeFinishedReducesWork_87) {
  AddSimpleEdge();

  std::string err;
  ASSERT_TRUE(plan_.AddTarget(GetNode("out"), &err));
  EXPECT_EQ("", err);

  Edge* edge = plan_.FindWork();
  ASSERT_NE(nullptr, edge);

  ASSERT_TRUE(plan_.EdgeFinished(edge, Plan::kEdgeSucceeded, &err));
  EXPECT_EQ("", err);

  // After the only edge finishes, no more work
  EXPECT_FALSE(plan_.more_to_do());
}

// Test that command_edge_count remains consistent after FindWork
TEST_F(PlanTest_87, CommandEdgeCountUnchangedByFindWork_87) {
  AddSimpleEdge();

  std::string err;
  ASSERT_TRUE(plan_.AddTarget(GetNode("out"), &err));

  int count_before = plan_.command_edge_count();
  plan_.FindWork();
  int count_after = plan_.command_edge_count();

  EXPECT_EQ(count_before, count_after);
}

// Test chain: FindWork returns edges in dependency order
TEST_F(PlanTest_87, FindWorkRespectsOrder_87) {
  AddMultipleEdges();

  std::string err;
  ASSERT_TRUE(plan_.AddTarget(GetNode("out"), &err));
  EXPECT_EQ("", err);

  // First work should be the edge building 'mid' (since 'out' depends on 'mid')
  Edge* edge1 = plan_.FindWork();
  ASSERT_NE(nullptr, edge1);

  // No more work available until edge1 finishes
  Edge* edge2 = plan_.FindWork();
  EXPECT_EQ(nullptr, edge2);

  // Finish the first edge
  ASSERT_TRUE(plan_.EdgeFinished(edge1, Plan::kEdgeSucceeded, &err));
  EXPECT_EQ("", err);

  // Now the second edge should be available
  edge2 = plan_.FindWork();
  ASSERT_NE(nullptr, edge2);

  ASSERT_TRUE(plan_.EdgeFinished(edge2, Plan::kEdgeSucceeded, &err));
  EXPECT_EQ("", err);

  EXPECT_FALSE(plan_.more_to_do());
}

// Test EdgeFinished with failure
TEST_F(PlanTest_87, EdgeFinishedWithFailure_87) {
  AddSimpleEdge();

  std::string err;
  ASSERT_TRUE(plan_.AddTarget(GetNode("out"), &err));

  Edge* edge = plan_.FindWork();
  ASSERT_NE(nullptr, edge);

  ASSERT_TRUE(plan_.EdgeFinished(edge, Plan::kEdgeFailed, &err));
}

// Test Dump doesn't crash (just a smoke test)
TEST_F(PlanTest_87, DumpDoesNotCrash_87) {
  plan_.Dump();

  AddSimpleEdge();
  std::string err;
  plan_.AddTarget(GetNode("out"), &err);
  plan_.Dump();
}
