// File: ./TestProjects/ninja/tests/deps_log_nodes_test_84.cc

#include "deps_log.h"

#include <gtest/gtest.h>
#include <string>

// We only care about DepsLog::nodes() accessor here.
// Do NOT rely on any private state or internal implementation details.

class DepsLogTest_84 : public ::testing::Test {
 protected:
  DepsLog log_;  // Fresh DepsLog for each test.
};

// [Normal operation]
// Newly constructed DepsLog should report an empty nodes() container.
TEST_F(DepsLogTest_84, NodesInitiallyEmpty_84) {
  const std::vector<Node*>& nodes = log_.nodes();
  EXPECT_TRUE(nodes.empty());
  EXPECT_EQ(nodes.size(), 0u);
}

// [Boundary condition]
// nodes() should consistently return a reference to the same underlying
// container across multiple calls (no copies or different instances).
TEST_F(DepsLogTest_84, NodesReferenceStableAcrossCalls_84) {
  const std::vector<Node*>* first_ref = &log_.nodes();
  const std::vector<Node*>* second_ref = &log_.nodes();

  // Both references should point to the same internal container.
  EXPECT_EQ(first_ref, second_ref);

  // And it should still be empty at this point.
  EXPECT_TRUE(first_ref->empty());
}

// [Normal + boundary]
// Opening and closing the deps log for writing should not implicitly
// populate or modify the nodes() list.
TEST_F(DepsLogTest_84, NodesUnaffectedByOpenForWriteAndClose_84) {
  // Capture initial state.
  const std::vector<Node*>& before = log_.nodes();
  ASSERT_TRUE(before.empty());

  std::string err;
  // Use a test-local path; exact location is not important for this test.
  EXPECT_TRUE(log_.OpenForWrite("deps_log_nodes_test_84.nd", &err));
  EXPECT_TRUE(err.empty());

  // After OpenForWrite, nodes() should still refer to the same vector
  // and remain empty because we have not recorded any deps.
  const std::vector<Node*>* ref_before = &before;
  const std::vector<Node*>* ref_after_open = &log_.nodes();
  EXPECT_EQ(ref_before, ref_after_open);
  EXPECT_TRUE(log_.nodes().empty());

  // Closing should also not affect nodes().
  log_.Close();
  const std::vector<Node*>* ref_after_close = &log_.nodes();
  EXPECT_EQ(ref_before, ref_after_close);
  EXPECT_TRUE(log_.nodes().empty());
}
