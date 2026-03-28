// File: test/node/detail/node_equals_char_test_668.cpp

#include <gtest/gtest.h>

#include <string>

// The class under test lives here (per prompt).
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/impl.h"

namespace {

using YAML::detail::node;
using YAML::detail::shared_memory_holder;

// Helper: pass a "null" / empty memory holder without assuming internals.
inline shared_memory_holder NullMem() { return shared_memory_holder{}; }

class NodeEqualsCharTest_668 : public ::testing::Test {
protected:
  shared_memory_holder mem_ = NullMem();
};

TEST_F(NodeEqualsCharTest_668, ScalarMatchesReturnsTrue_668) {
  node n;
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals("hello", mem_));
}

TEST_F(NodeEqualsCharTest_668, ScalarDifferentReturnsFalse_668) {
  node n;
  n.set_scalar("hello");

  EXPECT_FALSE(n.equals("world", mem_));
}

TEST_F(NodeEqualsCharTest_668, EmptyScalarAndEmptyRhsReturnsTrue_668) {
  node n;
  n.set_scalar("");

  EXPECT_TRUE(n.equals("", mem_));
}

TEST_F(NodeEqualsCharTest_668, EmptyScalarAndNonEmptyRhsReturnsFalse_668) {
  node n;
  n.set_scalar("");

  EXPECT_FALSE(n.equals("x", mem_));
}

TEST_F(NodeEqualsCharTest_668, NonEmptyScalarAndEmptyRhsReturnsFalse_668) {
  node n;
  n.set_scalar("x");

  EXPECT_FALSE(n.equals("", mem_));
}

TEST_F(NodeEqualsCharTest_668, LongScalarMatchesReturnsTrue_668) {
  const std::string long_value(4096, 'a');

  node n;
  n.set_scalar(long_value);

  EXPECT_TRUE(n.equals(long_value.c_str(), mem_));
}

TEST_F(NodeEqualsCharTest_668, NonStringTypeReturnsFalse_668) {
  // If the node isn't convertible/decodable as a std::string, equals() should
  // return false (observable behavior implied by the implementation).
  node n;
  n.set_type(YAML::NodeType::Sequence);

  EXPECT_FALSE(n.equals("anything", mem_));
}

TEST_F(NodeEqualsCharTest_668, SequenceNodeStillReturnsFalseForEmptyString_668) {
  node n;
  n.set_type(YAML::NodeType::Sequence);

  EXPECT_FALSE(n.equals("", mem_));
}

}  // namespace