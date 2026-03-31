#include <gtest/gtest.h>
#include <utility>

// Minimal mock of V to act as a node type
struct MockNode {
    int id;
    MockNode() : id(0) {}
    explicit MockNode(int i) : id(i) {}
};

// Reconstruct the node_iterator_value based on the known/inferred dependencies
namespace YAML {
namespace detail {

template <typename V>
struct node_iterator_value {
    std::pair<V*, V*> kv;
    V* pNode;

    node_iterator_value() : kv(nullptr, nullptr), pNode(nullptr) {}

    explicit node_iterator_value(V& rhs) : kv(nullptr, nullptr), pNode(&rhs) {}

    explicit node_iterator_value(V& key, V& value)
        : kv(&key, &value), pNode(nullptr) {}

    V& operator*() const { return *pNode; }

    V* operator->() const { return pNode; }
};

}  // namespace detail
}  // namespace YAML

// ============================================================
// Tests
// ============================================================

class NodeIteratorValueTest_180 : public ::testing::Test {
protected:
    MockNode node1{1};
    MockNode node2{2};
    MockNode node3{3};
};

// Test default constructor initializes pNode to nullptr
TEST_F(NodeIteratorValueTest_180, DefaultConstructor_pNodeIsNull_180) {
    YAML::detail::node_iterator_value<MockNode> val;
    EXPECT_EQ(val.pNode, nullptr);
    EXPECT_EQ(val.kv.first, nullptr);
    EXPECT_EQ(val.kv.second, nullptr);
}

// Test single-node constructor sets pNode correctly
TEST_F(NodeIteratorValueTest_180, SingleNodeConstructor_SetspNode_180) {
    YAML::detail::node_iterator_value<MockNode> val(node1);
    EXPECT_EQ(val.pNode, &node1);
    EXPECT_EQ(val.kv.first, nullptr);
    EXPECT_EQ(val.kv.second, nullptr);
}

// Test key-value constructor sets kv pair and pNode is null
TEST_F(NodeIteratorValueTest_180, KeyValueConstructor_SetsKVPair_180) {
    YAML::detail::node_iterator_value<MockNode> val(node1, node2);
    EXPECT_EQ(val.pNode, nullptr);
    EXPECT_EQ(val.kv.first, &node1);
    EXPECT_EQ(val.kv.second, &node2);
}

// Test operator* returns reference to the pointed node
TEST_F(NodeIteratorValueTest_180, DereferenceOperator_ReturnsNodeReference_180) {
    YAML::detail::node_iterator_value<MockNode> val(node1);
    MockNode& ref = *val;
    EXPECT_EQ(&ref, &node1);
    EXPECT_EQ(ref.id, 1);
}

// Test operator-> returns pointer to the node
TEST_F(NodeIteratorValueTest_180, ArrowOperator_ReturnsNodePointer_180) {
    YAML::detail::node_iterator_value<MockNode> val(node1);
    EXPECT_EQ(val->id, 1);
}

// Test that modifying the node through operator* affects the original
TEST_F(NodeIteratorValueTest_180, DereferenceOperator_ModifiesOriginalNode_180) {
    YAML::detail::node_iterator_value<MockNode> val(node1);
    (*val).id = 42;
    EXPECT_EQ(node1.id, 42);
}

// Test that modifying the node through operator-> affects the original
TEST_F(NodeIteratorValueTest_180, ArrowOperator_ModifiesOriginalNode_180) {
    YAML::detail::node_iterator_value<MockNode> val(node2);
    val->id = 99;
    EXPECT_EQ(node2.id, 99);
}

// Test key-value constructor with same node for key and value
TEST_F(NodeIteratorValueTest_180, KeyValueConstructor_SameNodeForKeyAndValue_180) {
    YAML::detail::node_iterator_value<MockNode> val(node1, node1);
    EXPECT_EQ(val.kv.first, &node1);
    EXPECT_EQ(val.kv.second, &node1);
    EXPECT_EQ(val.pNode, nullptr);
}

// Test single-node constructor with different nodes produces different iterators
TEST_F(NodeIteratorValueTest_180, SingleNodeConstructor_DifferentNodes_180) {
    YAML::detail::node_iterator_value<MockNode> val1(node1);
    YAML::detail::node_iterator_value<MockNode> val2(node2);
    EXPECT_NE(val1.pNode, val2.pNode);
    EXPECT_EQ((*val1).id, 1);
    EXPECT_EQ((*val2).id, 2);
}

// Test key-value constructor: key and value are correctly distinguishable
TEST_F(NodeIteratorValueTest_180, KeyValueConstructor_KeyAndValueDistinguishable_180) {
    YAML::detail::node_iterator_value<MockNode> val(node1, node3);
    EXPECT_EQ(val.kv.first->id, 1);
    EXPECT_EQ(val.kv.second->id, 3);
}

// Test that operator* and operator-> are consistent
TEST_F(NodeIteratorValueTest_180, DereferenceAndArrowConsistency_180) {
    YAML::detail::node_iterator_value<MockNode> val(node1);
    EXPECT_EQ(&(*val), val.operator->());
}

// Test with const-qualified node type
TEST_F(NodeIteratorValueTest_180, ConstNodeType_SingleNodeConstructor_180) {
    const MockNode constNode(10);
    YAML::detail::node_iterator_value<const MockNode> val(constNode);
    EXPECT_EQ(val.pNode, &constNode);
    EXPECT_EQ((*val).id, 10);
    EXPECT_EQ(val->id, 10);
}

// Test with const-qualified node type for key-value
TEST_F(NodeIteratorValueTest_180, ConstNodeType_KeyValueConstructor_180) {
    const MockNode constKey(20);
    const MockNode constVal(30);
    YAML::detail::node_iterator_value<const MockNode> val(constKey, constVal);
    EXPECT_EQ(val.kv.first, &constKey);
    EXPECT_EQ(val.kv.second, &constVal);
    EXPECT_EQ(val.kv.first->id, 20);
    EXPECT_EQ(val.kv.second->id, 30);
}
