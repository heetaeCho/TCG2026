// File: ./TestProjects/ninja/tests/inputs_collector_reset_test_72.cc

#include <string>
#include <vector>

#include "graph.h"        // Defines InputsCollector, Node, etc.
#include "gtest/gtest.h"

class InputsCollectorTest_72 : public ::testing::Test {
protected:
  // Helper to create a simple Node.  The actual Node implementation is part of
  // the production code; here we just use its public constructor.
  Node MakeNode(const std::string& path) {
    // In the real ninja codebase, Node has a constructor like:
    //   explicit Node(const std::string& path, uint64_t slash_bits);
    // We treat this as a black box and only rely on the public interface.
    return Node(path, 0u);
  }
};

//------------------------------------------------------------------------------
// 1) Normal behavior: Reset on a fresh collector
//------------------------------------------------------------------------------

TEST_F(InputsCollectorTest_72, ResetOnFreshCollectorLeavesEmpty_72) {
  InputsCollector collector;

  // Act
  collector.Reset();

  // Assert: inputs() should be empty after Reset on a fresh collector.
  EXPECT_TRUE(collector.inputs().empty());

  // GetInputsAsStrings should also reflect that there are no collected inputs.
  std::vector<std::string> inputs_strings = collector.GetInputsAsStrings(false);
  EXPECT_TRUE(inputs_strings.empty());
}

//------------------------------------------------------------------------------
// 2) Reset clears previously collected inputs
//------------------------------------------------------------------------------

TEST_F(InputsCollectorTest_72, ResetClearsCollectedInputs_72) {
  InputsCollector collector;

  Node n1 = MakeNode("in1");
  Node n2 = MakeNode("in2");

  // Arrange: collect some inputs via the public VisitNode API.
  collector.VisitNode(&n1);
  collector.VisitNode(&n2);

  // Sanity check: we expect that visiting two distinct nodes results in
  // at least two collected entries (observable via inputs()).
  ASSERT_EQ(2u, collector.inputs().size());

  std::vector<std::string> before_strings =
      collector.GetInputsAsStrings(false);
  ASSERT_EQ(2u, before_strings.size());

  // Act
  collector.Reset();

  // Assert: all previously collected information should be gone.
  EXPECT_TRUE(collector.inputs().empty());

  std::vector<std::string> after_strings =
      collector.GetInputsAsStrings(false);
  EXPECT_TRUE(after_strings.empty());
}

//------------------------------------------------------------------------------
// 3) Reset also clears visited-nodes state so nodes can be revisited
//------------------------------------------------------------------------------
//
// This test verifies the observable behavior that, after Reset(), visiting the
// same node again behaves like visiting it for the first time.  In particular,
// if the collector avoids adding duplicate nodes during a single run, Reset()
// must allow a new run that can collect the node again.
//

TEST_F(InputsCollectorTest_72, ResetClearsVisitedNodesState_72) {
  InputsCollector collector;

  Node n = MakeNode("input");

  // First "run": visit the node once.
  collector.VisitNode(&n);
  ASSERT_EQ(1u, collector.inputs().size());

  // Remember the first run's collected inputs for comparison.
  std::vector<const Node*> first_run_inputs = collector.inputs();

  // Act: reset the collector to start a new run.
  collector.Reset();

  // Second "run": visit the same node again.
  collector.VisitNode(&n);

  // After Reset(), visiting the same node again should produce the same
  // observable behavior as the first run: exactly one collected input.
  EXPECT_EQ(1u, collector.inputs().size());

  std::vector<const Node*> second_run_inputs = collector.inputs();
  ASSERT_EQ(first_run_inputs.size(), second_run_inputs.size());
  EXPECT_EQ(first_run_inputs[0], second_run_inputs[0]);
}

//------------------------------------------------------------------------------
// 4) Reset is idempotent (can be called multiple times safely)
//------------------------------------------------------------------------------

TEST_F(InputsCollectorTest_72, ResetIsIdempotent_72) {
  InputsCollector collector;

  Node n = MakeNode("input");

  // Arrange: collect something first.
  collector.VisitNode(&n);
  ASSERT_FALSE(collector.inputs().empty());

  // Act: call Reset() multiple times.
  collector.Reset();
  std::size_t size_after_first_reset = collector.inputs().size();

  collector.Reset();
  std::size_t size_after_second_reset = collector.inputs().size();

  // Assert: both resets leave the collector in the same empty state.
  EXPECT_EQ(0u, size_after_first_reset);
  EXPECT_EQ(size_after_first_reset, size_after_second_reset);

  // And GetInputsAsStrings should also remain empty.
  EXPECT_TRUE(collector.GetInputsAsStrings(false).empty());
}
