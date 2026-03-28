// File: ./TestProjects/ninja/tests/node_generated_by_dep_loader_test_46.cc

#include "graph.h"

#include "gtest/gtest.h"

class NodeGeneratedByDepLoaderTest_46 : public ::testing::Test {};

// TEST_ID: 46
// Verifies the default value of generated_by_dep_loader() for a freshly
// constructed Node.
TEST_F(NodeGeneratedByDepLoaderTest_46,
       DefaultGeneratedByDepLoaderIsTrue_46) {
  Node node("out.o", /*slash_bits=*/0);

  EXPECT_TRUE(node.generated_by_dep_loader());
}

// TEST_ID: 46
// Verifies that set_generated_by_dep_loader(false) is observable through
// generated_by_dep_loader().
TEST_F(NodeGeneratedByDepLoaderTest_46,
       SetterUpdatesToFalse_46) {
  Node node("out.o", /*slash_bits=*/0);

  node.set_generated_by_dep_loader(false);

  EXPECT_FALSE(node.generated_by_dep_loader());
}

// TEST_ID: 46
// Verifies that the flag can be toggled multiple times and that the last
// call to set_generated_by_dep_loader() determines the observable state.
TEST_F(NodeGeneratedByDepLoaderTest_46,
       SetterCanToggleMultipleTimes_46) {
  Node node("out.o", /*slash_bits=*/0);

  // First disable, then enable again and verify each step via the getter.
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());

  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());

  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
}
