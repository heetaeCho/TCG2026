// File: node_set_dirty_test_40.cc

#include "graph.h"

#include "gtest/gtest.h"

namespace {

class NodeSetDirtyTest_40 : public ::testing::Test {
protected:
  NodeSetDirtyTest_40()
      : node_("out.o", /*slash_bits=*/0) {}

  Node node_;
};

// TEST_ID = 40
TEST_F(NodeSetDirtyTest_40, NewlyCreatedNodeNotDirtyByDefault_40) {
  // A freshly constructed Node should not be dirty.
  EXPECT_FALSE(node_.dirty());
}

// TEST_ID = 40
TEST_F(NodeSetDirtyTest_40, SetDirtyTrueThenFalse_UpdatesDirtyFlag_40) {
  // Start from a clean state.
  EXPECT_FALSE(node_.dirty());

  // When we set dirty to true, the node should report dirty.
  node_.set_dirty(true);
  EXPECT_TRUE(node_.dirty());

  // When we set dirty to false again, the node should report clean.
  node_.set_dirty(false);
  EXPECT_FALSE(node_.dirty());
}

// TEST_ID = 40
TEST_F(NodeSetDirtyTest_40, MultipleSetDirtyCallsRemainConsistent_40) {
  // Repeated calls with the same value should keep the reported state stable.
  node_.set_dirty(true);
  EXPECT_TRUE(node_.dirty());
  node_.set_dirty(true);
  EXPECT_TRUE(node_.dirty());

  node_.set_dirty(false);
  EXPECT_FALSE(node_.dirty());
  node_.set_dirty(false);
  EXPECT_FALSE(node_.dirty());
}

// TEST_ID = 40
TEST_F(NodeSetDirtyTest_40, SetDirtyDoesNotAffectPathOrSlashBits_40) {
  const std::string original_path = node_.path();
  const uint64_t original_slash_bits = node_.slash_bits();

  node_.set_dirty(true);
  EXPECT_TRUE(node_.dirty());
  EXPECT_EQ(original_path, node_.path());
  EXPECT_EQ(original_slash_bits, node_.slash_bits());

  node_.set_dirty(false);
  EXPECT_FALSE(node_.dirty());
  EXPECT_EQ(original_path, node_.path());
  EXPECT_EQ(original_slash_bits, node_.slash_bits());
}

}  // namespace
