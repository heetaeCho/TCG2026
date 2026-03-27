#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "node.h"

#include "nodeevents.h"

#include "nodebuilder.h"



using namespace YAML;

using ::testing::NiceMock;



class NodeCloneTest_508 : public ::testing::Test {

protected:

    Node validNode;

    Node invalidNode;



    NodeCloneTest_508() : validNode(NodeType::Map), invalidNode(Zombie{}) {}

};



TEST_F(NodeCloneTest_508, CloneValidNode_ReturnsNewInstance_508) {

    Node clonedNode = Clone(validNode);

    EXPECT_NE(&clonedNode, &validNode);

    EXPECT_EQ(clonedNode.Type(), validNode.Type());

}



TEST_F(NodeCloneTest_508, CloneInvalidNode_ReturnsInvalidNode_508) {

    Node clonedNode = Clone(invalidNode);

    EXPECT_FALSE(clonedNode.IsValid());

}



TEST_F(NodeCloneTest_508, CloneScalarNode_ReturnsSameType_508) {

    Node scalarNode("scalar_value");

    Node clonedNode = Clone(scalarNode);

    EXPECT_EQ(clonedNode.Type(), NodeType::Scalar);

    EXPECT_EQ(clonedNode.Scalar(), "scalar_value");

}



TEST_F(NodeCloneTest_508, CloneSequenceNode_ReturnsSameType_508) {

    Node sequenceNode;

    sequenceNode.push_back("item1");

    sequenceNode.push_back("item2");



    Node clonedNode = Clone(sequenceNode);

    EXPECT_EQ(clonedNode.Type(), NodeType::Sequence);

    EXPECT_EQ(clonedNode.size(), 2U);

}



TEST_F(NodeCloneTest_508, CloneMapNode_ReturnsSameTypeAndContents_508) {

    Node mapNode;

    mapNode["key1"] = "value1";

    mapNode["key2"] = "value2";



    Node clonedNode = Clone(mapNode);

    EXPECT_EQ(clonedNode.Type(), NodeType::Map);

    EXPECT_EQ(clonedNode["key1"].Scalar(), "value1");

    EXPECT_EQ(clonedNode["key2"].Scalar(), "value2");

}
