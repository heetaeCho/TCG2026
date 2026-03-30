#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"

#include "yaml-cpp/node/node.h"



class NodeTest_686 : public ::testing::Test {

protected:

    YAML::Node node;

};



TEST_F(NodeTest_686, DefaultConstructorCreatesValidNode_686) {

    YAML::Node defaultNode;

    EXPECT_TRUE(defaultNode.IsValid());

}



TEST_F(NodeTest_686, ScalarConstructorCreatesScalarNode_686) {

    YAML::Node scalarNode("test");

    EXPECT_EQ(scalarNode.Scalar(), "test");

}



TEST_F(NodeTest_686, AssignmentOperatorAssignsValue_686) {

    YAML::Node node1;

    node1 = 42;

    EXPECT_EQ(node1.as<int>(), 42);

}



TEST_F(NodeTest_686, ResetFunctionChangesNodeValue_686) {

    YAML::Node node1(42);

    YAML::Node node2("test");

    node1.reset(node2);

    EXPECT_EQ(node1.Scalar(), "test");

}



TEST_F(NodeTest_686, SizeReturnsCorrectSizeForSequence_686) {

    YAML::Node seqNode(YAML::NodeType::Sequence);

    seqNode.push_back(1);

    seqNode.push_back(2);

    EXPECT_EQ(seqNode.size(), 2);

}



TEST_F(NodeTest_686, IsDefinedReturnsTrueForValidNode_686) {

    YAML::Node validNode("defined");

    EXPECT_TRUE(validNode.IsDefined());

}



TEST_F(NodeTest_686, IsNullReturnsFalseForNonEmptyNode_686) {

    YAML::Node nonNullNode("not null");

    EXPECT_FALSE(nonNullNode.IsNull());

}



TEST_F(NodeTest_686, TypeReturnsCorrectTypeForScalar_686) {

    YAML::Node scalarNode("scalar");

    EXPECT_EQ(scalarNode.Type(), YAML::NodeType::Scalar);

}



TEST_F(NodeTest_686, AsFunctionConvertsToCorrectType_686) {

    YAML::Node intNode(123);

    EXPECT_EQ(intNode.as<int>(), 123);

}



TEST_F(NodeTest_686, AsFunctionUsesFallbackForInvalidConversion_686) {

    YAML::Node invalidNode("not a number");

    EXPECT_EQ(invalidNode.as<int>(456), 456);

}



TEST_F(NodeTest_686, OperatorBoolReturnsTrueForValidNode_686) {

    YAML::Node validNode("value");

    EXPECT_TRUE(static_cast<bool>(validNode));

}



TEST_F(NodeTest_686, OperatorNotReturnsFalseForValidNode_686) {

    YAML::Node validNode("value");

    EXPECT_FALSE(!validNode);

}
