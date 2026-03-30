// File: ./TestProjects/ninja/tests/deps_log_deps_test_85.cc

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

#include "deps_log.h"
#include "state.h"

using std::string;
using std::vector;

class DepsLogDepsTest_85 : public ::testing::Test {
 protected:
  DepsLogDepsTest_85() : test_path_("DepsLogDepsTest_85_depslog") {}

  void SetUp() override {
    // Clean up from any previous failed run.
    std::remove(test_path_.c_str());
  }

  void TearDown() override {
    std::remove(test_path_.c_str());
  }

  string test_path_;
};

/// Verify that deps() returns an empty collection for a freshly constructed log.
TEST_F(DepsLogDepsTest_85, DepsInitiallyEmpty_85) {
  DepsLog log;

  const std::vector<DepsLog::Deps*>& deps_vec = log.deps();
  EXPECT_TRUE(deps_vec.empty());
}

/// Verify that deps() returns a stable reference (not a temporary copy).
TEST_F(DepsLogDepsTest_85, DepsReturnsStableReference_85) {
  DepsLog log;

  const std::vector<DepsLog::Deps*>& first = log.deps();
  const std::vector<DepsLog::Deps*>& second = log.deps();

  // If deps() returned by value, these addresses would differ.
  EXPECT_EQ(&first, &second);
}

/// Normal operation: after recording dependencies, deps() exposes the same
/// Deps* object that GetDeps(node) returns.
TEST_F(DepsLogDepsTest_85, DepsContainsRecordedEntry_85) {
  State state;
  DepsLog log;
  string err;

  ASSERT_TRUE(log.OpenForWrite(test_path_, &err));
  ASSERT_TRUE(err.empty());

  // Prepare a small set of input nodes.
  vector<Node*> inputs;
  inputs.push_back(state.GetNode("header1.h", 0));
  inputs.push_back(state.GetNode("header2.h", 0));

  Node* output = state.GetNode("out.o", 0);

  ASSERT_TRUE(log.RecordDeps(output, /*mtime=*/1, inputs));

  // GetDeps should give us a non-null entry for the recorded node.
  DepsLog::Deps* deps_for_out = log.GetDeps(output);
  ASSERT_NE(nullptr, deps_for_out);

  // That same pointer must be visible somewhere in deps().
  const std::vector<DepsLog::Deps*>& all_deps = log.deps();
  auto it = std::find(all_deps.begin(), all_deps.end(), deps_for_out);
  EXPECT_NE(all_deps.end(), it);

  log.Close();
}

/// Boundary/exceptional case: loading from a non-existent deps log succeeds
/// and leaves deps() empty and safe to inspect.
TEST_F(DepsLogDepsTest_85, LoadNonexistentLogLeavesDepsEmpty_85) {
  State state;
  DepsLog log;
  string err;

  // At this point test_path_ does not exist (SetUp removed it).
  ASSERT_TRUE(log.Load(test_path_, &state, &err));
  // For a missing file, Load is expected to succeed without an error message.
  EXPECT_TRUE(err.empty());

  const std::vector<DepsLog::Deps*>& deps_vec = log.deps();
  EXPECT_TRUE(deps_vec.empty());
}
