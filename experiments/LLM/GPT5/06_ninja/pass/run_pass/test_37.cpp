// File: node_slash_bits_test_37.cc

#include <gtest/gtest.h>
#include <limits>
#include <string>

#include "graph.h"

class NodeSlashBitsTest_37 : public ::testing::Test {};

// Normal case: slash_bits() returns the value passed to constructor.
TEST_F(NodeSlashBitsTest_37, ReturnsConstructorValue_37) {
  const uint64_t expected_bits = 0x5u;
  Node node("path/with/slash", expected_bits);

  EXPECT_EQ(node.slash_bits(), expected_bits);
}

// Boundary case: zero slash bits.
TEST_F(NodeSlashBitsTest_37, ZeroSlashBits_37) {
  const uint64_t expected_bits = 0u;
  Node node("path/without/slash", expected_bits);

  EXPECT_EQ(node.slash_bits(), expected_bits);
}

// Boundary case: maximum uint64_t value, and stability across multiple calls.
TEST_F(NodeSlashBitsTest_37, MaxSlashBitsAndMultipleCallsStable_37) {
  const uint64_t expected_bits = std::numeric_limits<uint64_t>::max();
  Node node("any/path", expected_bits);

  EXPECT_EQ(node.slash_bits(), expected_bits);
  EXPECT_EQ(node.slash_bits(), expected_bits);  // multiple calls should be consistent
}
