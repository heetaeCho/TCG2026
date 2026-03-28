// File: ./TestProjects/ninja/tests/command_runner_get_active_edges_test_89.cc

#include "gtest/gtest.h"
#include "build.h"  // Declares CommandRunner, Edge, Result, etc.
#include <vector>

// Simple concrete subclass to allow instantiation of CommandRunner.
// We DO NOT override GetActiveEdges(), so we are testing the default
// implementation provided by CommandRunner.
class TestCommandRunner_89 : public CommandRunner {
public:
  // These are trivial implementations just to satisfy the interface.
  // They are NOT re-implementing or simulating any internal logic of CommandRunner.
  size_t CanRunMore() override { return 0u; }
  bool StartCommand(Edge* /*edge*/) override { return false; }
  bool WaitForCommand(Result* /*result*/) override { return false; }
  void Abort() override {}
};

// Test fixture for CommandRunner-related tests (TEST_ID = 89).
class CommandRunnerTest_89 : public ::testing::Test {
protected:
  TestCommandRunner_89 runner_;
};

// Verifies that the default implementation of GetActiveEdges returns an empty vector.
TEST_F(CommandRunnerTest_89, DefaultGetActiveEdgesReturnsEmpty_89) {
  std::vector<Edge*> active_edges = runner_.GetActiveEdges();

  EXPECT_TRUE(active_edges.empty());
  EXPECT_EQ(active_edges.size(), 0u);
}

// Verifies that modifying the returned vector does not affect subsequent calls;
// i.e., each call to GetActiveEdges returns a fresh empty vector.
TEST_F(CommandRunnerTest_89, GetActiveEdgesIsNotAffectedByCallerModifications_89) {
  // First call: should be empty.
  std::vector<Edge*> first_call = runner_.GetActiveEdges();
  EXPECT_TRUE(first_call.empty());

  // Caller modifies the returned vector.
  first_call.push_back(nullptr);
  ASSERT_EQ(first_call.size(), 1u);

  // Second call: should still return an empty vector.
  std::vector<Edge*> second_call = runner_.GetActiveEdges();
  EXPECT_TRUE(second_call.empty());
  EXPECT_EQ(second_call.size(), 0u);
}
