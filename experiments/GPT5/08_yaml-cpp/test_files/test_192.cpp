#include <gtest/gtest.h>
#include <yaml-cpp/node/node.h>

using YAML::Node;
using YAML::NodeType;

/**
 * Test suite for YAML::Node::IsScalar
 */
class NodeIsScalarTest_192 : public ::testing::Test {};

/**
 * Normal operation:
 * A Node explicitly constructed as Scalar should report IsScalar() == true
 */
TEST_F(NodeIsScalarTest_192, ScalarNodeReturnsTrue_192) {
    Node node(NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
}

/**
 * Normal operation:
 * A Node constructed from a scalar value should report IsScalar() == true
 */
TEST_F(NodeIsScalarTest_192, ScalarValueConstructorReturnsTrue_192) {
    Node node("hello");
    EXPECT_TRUE(node.IsScalar());
}

/**
 * Boundary condition:
 * A default-constructed Node should not report IsScalar()
 */
TEST_F(NodeIsScalarTest_192, DefaultConstructedNodeReturnsFalse_192) {
    Node node;
    EXPECT_FALSE(node.IsScalar());
}

/**
 * Boundary condition:
 * A Node explicitly constructed as Null should not report IsScalar()
 */
TEST_F(NodeIsScalarTest_192, NullNodeReturnsFalse_192) {
    Node node(NodeType::Null);
    EXPECT_FALSE(node.IsScalar());
}

/**
 * Boundary condition:
 * A Node explicitly constructed as Sequence should not report IsScalar()
 */
TEST_F(NodeIsScalarTest_192, SequenceNodeReturnsFalse_192) {
    Node node(NodeType::Sequence);
    EXPECT_FALSE(node.IsScalar());
}

/**
 * Boundary condition:
 * A Node explicitly constructed as Map should not report IsScalar()
 */
TEST_F(NodeIsScalarTest_192, MapNodeReturnsFalse_192) {
    Node node(NodeType::Map);
    EXPECT_FALSE(node.IsScalar());
}

/**
 * Exceptional / error-like observable behavior:
 * An undefined Node (via default construction and boolean check)
 * should not report IsScalar()
 */
TEST_F(NodeIsScalarTest_192, UndefinedNodeReturnsFalse_192) {
    Node node;
    EXPECT_FALSE(node);
    EXPECT_FALSE(node.IsScalar());
}

/**
 * Copy semantics:
 * A copied scalar Node should preserve IsScalar() behavior
 */
TEST_F(NodeIsScalarTest_192, CopiedScalarNodeReturnsTrue_192) {
    Node original("scalar");
    Node copy(original);
    EXPECT_TRUE(copy.IsScalar());
}

/**
 * Assignment semantics:
 * Assigning a scalar value should result in IsScalar() == true
 */
TEST_F(NodeIsScalarTest_192, AssignedScalarValueReturnsTrue_192) {
    Node node;
    node = "assigned";
    EXPECT_TRUE(node.IsScalar());
}