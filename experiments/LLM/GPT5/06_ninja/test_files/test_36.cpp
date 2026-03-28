#include "graph.h"

#include <gtest/gtest.h>
#include <string>

class NodePathDecanonicalizedTest_36 : public ::testing::Test {
 protected:
  // Helper to construct a Node with given path and slash_bits.
  Node MakeNode(const std::string& path, uint64_t slash_bits) {
    return Node(path, slash_bits);
  }
};

// Normal case: verifies that the member PathDecanonicalized() delegates
// to the static PathDecanonicalized(path, slash_bits) with the stored values.
TEST_F(NodePathDecanonicalizedTest_36,
       PathDecanonicalized_UsesStoredPathAndSlashBits_36) {
  const std::string path = "foo/bar/baz";
  const uint64_t slash_bits = 0xA5u;  // arbitrary non-zero pattern

  Node node = MakeNode(path, slash_bits);

  std::string expected = Node::PathDecanonicalized(path, slash_bits);
  std::string actual = node.PathDecanonicalized();

  EXPECT_EQ(expected, actual);
}

// Boundary case: empty path and zero slash_bits should also be delegated
// correctly to the static helper.
TEST_F(NodePathDecanonicalizedTest_36,
       PathDecanonicalized_EmptyPathAndZeroSlashBits_36) {
  const std::string path;  // empty
  const uint64_t slash_bits = 0u;

  Node node = MakeNode(path, slash_bits);

  std::string expected = Node::PathDecanonicalized(path, slash_bits);
  std::string actual = node.PathDecanonicalized();

  EXPECT_EQ(expected, actual);
}

// Side-effect check: calling PathDecanonicalized() should not modify
// observable Node state accessible via public getters.
TEST_F(NodePathDecanonicalizedTest_36,
       PathDecanonicalized_DoesNotModifyObservableState_36) {
  const std::string path = "some/canonical/path";
  const uint64_t slash_bits = 0xFFu;

  Node node = MakeNode(path, slash_bits);

  // Capture observable state before the call.
  const std::string& path_before = node.path();
  uint64_t slash_bits_before = node.slash_bits();

  // Call the method under test multiple times.
  std::string result1 = node.PathDecanonicalized();
  std::string result2 = node.PathDecanonicalized();

  // Path and slash_bits should remain unchanged.
  EXPECT_EQ(path_before, node.path());
  EXPECT_EQ(slash_bits_before, node.slash_bits());

  // Multiple calls should be consistent.
  EXPECT_EQ(result1, result2);
}
