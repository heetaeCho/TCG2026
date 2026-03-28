#include <gtest/gtest.h>
#include <utility>

// Minimal mock of V to test node_iterator_value
// We replicate the structure based on the known/inferred dependencies

namespace YAML {
namespace detail {

template <typename V>
struct node_iterator_value : public std::pair<V*, V*> {
  V* pNode;

  node_iterator_value() : std::pair<V*, V*>(nullptr, nullptr), pNode(nullptr) {}

  explicit node_iterator_value(V& rhs)
      : std::pair<V*, V*>(nullptr, nullptr), pNode(&rhs) {}

  explicit node_iterator_value(V& key, V& value)
      : std::pair<V*, V*>(&key, &value), pNode(nullptr) {}

  V& operator*() const { return *pNode; }

  V& operator->() const { return *pNode; }
};

}  // namespace detail
}  // namespace YAML

// A simple type to use as V
struct TestNode {
  int value;
  TestNode() : value(0) {}
  explicit TestNode(int v) : value(v) {}
};

class NodeIteratorValueTest_179 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction sets pNode to nullptr
TEST_F(NodeIteratorValueTest_179, DefaultConstruction_pNodeIsNull_179) {
  YAML::detail::node_iterator_value<TestNode> val;
  EXPECT_EQ(val.pNode, nullptr);
  // The pair (kv) should also be null
  EXPECT_EQ(val.first, nullptr);
  EXPECT_EQ(val.second, nullptr);
}

// Test single-node construction sets pNode correctly
TEST_F(NodeIteratorValueTest_179, SingleNodeConstruction_pNodeSet_179) {
  TestNode node(42);
  YAML::detail::node_iterator_value<TestNode> val(node);
  EXPECT_EQ(val.pNode, &node);
  EXPECT_EQ(val.first, nullptr);
  EXPECT_EQ(val.second, nullptr);
}

// Test key-value construction sets pair correctly and pNode is null
TEST_F(NodeIteratorValueTest_179, KeyValueConstruction_PairSet_179) {
  TestNode key(10);
  TestNode value(20);
  YAML::detail::node_iterator_value<TestNode> val(key, value);
  EXPECT_EQ(val.pNode, nullptr);
  EXPECT_EQ(val.first, &key);
  EXPECT_EQ(val.second, &value);
}

// Test operator* dereferences pNode correctly
TEST_F(NodeIteratorValueTest_179, OperatorDereference_ReturnspNodeValue_179) {
  TestNode node(99);
  YAML::detail::node_iterator_value<TestNode> val(node);
  TestNode& ref = *val;
  EXPECT_EQ(ref.value, 99);
  EXPECT_EQ(&ref, &node);
}

// Test operator-> dereferences pNode correctly
TEST_F(NodeIteratorValueTest_179, OperatorArrow_ReturnspNodeRef_179) {
  TestNode node(55);
  YAML::detail::node_iterator_value<TestNode> val(node);
  TestNode& ref = val.operator->();
  EXPECT_EQ(ref.value, 55);
  EXPECT_EQ(&ref, &node);
}

// Test modifying the node through operator*
TEST_F(NodeIteratorValueTest_179, OperatorDereference_ModifyNode_179) {
  TestNode node(1);
  YAML::detail::node_iterator_value<TestNode> val(node);
  (*val).value = 100;
  EXPECT_EQ(node.value, 100);
}

// Test that key-value pair pointers match original nodes
TEST_F(NodeIteratorValueTest_179, KeyValueConstruction_PointersMatch_179) {
  TestNode key(1);
  TestNode value(2);
  YAML::detail::node_iterator_value<TestNode> val(key, value);
  EXPECT_EQ(val.first->value, 1);
  EXPECT_EQ(val.second->value, 2);
}

// Test with const type
TEST_F(NodeIteratorValueTest_179, ConstNodeType_SingleNode_179) {
  const TestNode node(77);
  YAML::detail::node_iterator_value<const TestNode> val(node);
  EXPECT_EQ(val.pNode, &node);
  const TestNode& ref = *val;
  EXPECT_EQ(ref.value, 77);
}

// Test with const type key-value
TEST_F(NodeIteratorValueTest_179, ConstNodeType_KeyValue_179) {
  const TestNode key(3);
  const TestNode value(4);
  YAML::detail::node_iterator_value<const TestNode> val(key, value);
  EXPECT_EQ(val.first, &key);
  EXPECT_EQ(val.second, &value);
  EXPECT_EQ(val.pNode, nullptr);
}

// Test that two independently constructed values from the same node point to the same address
TEST_F(NodeIteratorValueTest_179, TwoValuesFromSameNode_179) {
  TestNode node(10);
  YAML::detail::node_iterator_value<TestNode> val1(node);
  YAML::detail::node_iterator_value<TestNode> val2(node);
  EXPECT_EQ(&(*val1), &(*val2));
}

// Test copy behavior
TEST_F(NodeIteratorValueTest_179, CopyConstructor_179) {
  TestNode node(33);
  YAML::detail::node_iterator_value<TestNode> val1(node);
  YAML::detail::node_iterator_value<TestNode> val2 = val1;
  EXPECT_EQ(val2.pNode, &node);
  EXPECT_EQ(&(*val2), &node);
}

// Test assignment
TEST_F(NodeIteratorValueTest_179, AssignmentOperator_179) {
  TestNode node1(11);
  TestNode node2(22);
  YAML::detail::node_iterator_value<TestNode> val1(node1);
  YAML::detail::node_iterator_value<TestNode> val2(node2);
  val1 = val2;
  EXPECT_EQ(val1.pNode, &node2);
  EXPECT_EQ((*val1).value, 22);
}
