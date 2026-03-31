#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeEqualsTest_668 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new Memory);
  }

  shared_memory_holder pMemory;
};

// Test that a node with a string scalar equals the same C-string
TEST_F(NodeEqualsTest_668, EqualsMatchingCString_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals("hello", pMemory));
}

// Test that a node with a string scalar does not equal a different C-string
TEST_F(NodeEqualsTest_668, NotEqualsDifferentCString_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test that a node with an empty string scalar equals empty C-string
TEST_F(NodeEqualsTest_668, EqualsEmptyCString_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("");

  EXPECT_TRUE(n.equals("", pMemory));
}

// Test that a node with a non-empty scalar does not equal empty C-string
TEST_F(NodeEqualsTest_668, NonEmptyScalarNotEqualsEmptyCString_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("notempty");

  EXPECT_FALSE(n.equals("", pMemory));
}

// Test that a null node does not equal any C-string
TEST_F(NodeEqualsTest_668, NullNodeNotEqualsCString_668) {
  node& n = pMemory->create_node();
  n.set_null();

  EXPECT_FALSE(n.equals("hello", pMemory));
}

// Test that a sequence node does not equal a C-string
TEST_F(NodeEqualsTest_668, SequenceNodeNotEqualsCString_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);

  EXPECT_FALSE(n.equals("hello", pMemory));
}

// Test that a map node does not equal a C-string
TEST_F(NodeEqualsTest_668, MapNodeNotEqualsCString_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);

  EXPECT_FALSE(n.equals("hello", pMemory));
}

// Test that an undefined node does not equal a C-string
TEST_F(NodeEqualsTest_668, UndefinedNodeNotEqualsCString_668) {
  node& n = pMemory->create_node();
  // By default node should be undefined
  EXPECT_FALSE(n.equals("hello", pMemory));
}

// Test template version of equals with std::string
TEST_F(NodeEqualsTest_668, EqualsMatchingStdString_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  std::string rhs = "test";
  EXPECT_TRUE(n.equals(rhs, pMemory));
}

// Test template version of equals with different std::string
TEST_F(NodeEqualsTest_668, NotEqualsDifferentStdString_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  std::string rhs = "other";
  EXPECT_FALSE(n.equals(rhs, pMemory));
}

// Test equals with numeric value when scalar is numeric string
TEST_F(NodeEqualsTest_668, EqualsIntegerValue_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("42");

  EXPECT_TRUE(n.equals(42, pMemory));
}

// Test equals with non-matching integer
TEST_F(NodeEqualsTest_668, NotEqualsIntegerValue_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("42");

  EXPECT_FALSE(n.equals(99, pMemory));
}

// Test equals with special characters in string
TEST_F(NodeEqualsTest_668, EqualsSpecialCharsCString_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello\nworld\ttab");

  EXPECT_TRUE(n.equals("hello\nworld\ttab", pMemory));
}

// Test equals with very long string
TEST_F(NodeEqualsTest_668, EqualsLongCString_668) {
  std::string longStr(10000, 'a');
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar(longStr);

  EXPECT_TRUE(n.equals(longStr.c_str(), pMemory));
}

// Test equals with substring (should not match)
TEST_F(NodeEqualsTest_668, SubstringNotEquals_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello world");

  EXPECT_FALSE(n.equals("hello", pMemory));
}

// Test equals case sensitivity
TEST_F(NodeEqualsTest_668, CaseSensitiveComparison_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("Hello");

  EXPECT_FALSE(n.equals("hello", pMemory));
}

// Test boolean value equality
TEST_F(NodeEqualsTest_668, EqualsBooleanTrue_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("true");

  EXPECT_TRUE(n.equals(true, pMemory));
}

// Test boolean value inequality
TEST_F(NodeEqualsTest_668, NotEqualsBooleanFalse_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("true");

  EXPECT_FALSE(n.equals(false, pMemory));
}

// Test double value equality
TEST_F(NodeEqualsTest_668, EqualsDoubleValue_668) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("3.14");

  EXPECT_TRUE(n.equals(3.14, pMemory));
}

}  // namespace detail
}  // namespace YAML
