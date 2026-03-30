// File: ./TestProjects/ninja/tests/node_status_known_test.cc

#include "graph.h"

#include "gtest/gtest.h"

/// Simple fixture for constructing a Node instance to exercise status_known().
class NodeStatusKnownTest_34 : public ::testing::Test {
protected:
  NodeStatusKnownTest_34()
      : node_("out", 0u) {}  // path, slash_bits

  Node node_;
};

// -----------------------------------------------------------------------------
// Basic behavior
// -----------------------------------------------------------------------------

// Newly constructed nodes have unknown existence status.
TEST_F(NodeStatusKnownTest_34, DefaultStatusIsUnknown_34) {
  EXPECT_FALSE(node_.status_known());
}

// MarkMissing() should make the status known (missing).
TEST_F(NodeStatusKnownTest_34, MarkMissingMakesStatusKnown_34) {
  ASSERT_FALSE(node_.status_known());  // sanity check initial state

  node_.MarkMissing();

  EXPECT_TRUE(node_.status_known());
}

// ResetState() should clear any previously-known status back to unknown.
TEST_F(NodeStatusKnownTest_34, ResetStateClearsKnownStatus_34) {
  // First move to a "known" state.
  node_.MarkMissing();
  ASSERT_TRUE(node_.status_known());

  // Then reset.
  node_.ResetState();

  EXPECT_FALSE(node_.status_known());
}

// Calling MarkMissing() multiple times should leave the status known.
TEST_F(NodeStatusKnownTest_34, MarkMissingIsIdempotentForStatusKnown_34) {
  ASSERT_FALSE(node_.status_known());  // initial unknown

  node_.MarkMissing();
  node_.MarkMissing();  // second call should not revert status

  EXPECT_TRUE(node_.status_known());
}
