// File: node_set_id_test_49.cc

#include <limits>
#include <string>

#include "graph.h"

#include "gtest/gtest.h"

class NodeSetIdTest_49 : public ::testing::Test {
protected:
  NodeSetIdTest_49()
      : node_("dummy/path", 0u) {  // Use minimal valid constructor args from interface
  }

  Node node_;
};

// Normal operation: setting a typical positive id and reading it back.
TEST_F(NodeSetIdTest_49, SetIdStoresPositiveValue_49) {
  node_.set_id(10);
  EXPECT_EQ(10, node_.id());
}

// Boundary: setting zero as id (often used as a special value in some systems).
TEST_F(NodeSetIdTest_49, SetIdStoresZero_49) {
  node_.set_id(0);
  EXPECT_EQ(0, node_.id());
}

// Boundary: setting a negative id (check that interface accepts and returns it as-is).
TEST_F(NodeSetIdTest_49, SetIdStoresNegativeValue_49) {
  node_.set_id(-123);
  EXPECT_EQ(-123, node_.id());
}

// Boundary: setting the maximum int value.
TEST_F(NodeSetIdTest_49, SetIdStoresMaxInt_49) {
  const int kMaxInt = std::numeric_limits<int>::max();
  node_.set_id(kMaxInt);
  EXPECT_EQ(kMaxInt, node_.id());
}

// Behavioral check: multiple calls should overwrite the previous value with the last one.
TEST_F(NodeSetIdTest_49, SetIdOverwritesPreviousValue_49) {
  node_.set_id(1);
  EXPECT_EQ(1, node_.id());

  node_.set_id(42);
  EXPECT_EQ(42, node_.id());
}
