#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_569 : public ::testing::Test {

protected:

    Node node;

};



TEST_F(NodeTest_569, PushBack_ValidNode_IncreasesSize_569) {

    size_t initialSize = node.size();

    node.push_back(42);

    EXPECT_EQ(node.size(), initialSize + 1);

}



TEST_F(NodeTest_569, PushBack_MultipleItems_CorrectlyIncreasesSize_569) {

    size_t initialSize = node.size();

    node.push_back(42);

    node.push_back("test");

    node.push_back(3.14);

    EXPECT_EQ(node.size(), initialSize + 3);

}



TEST_F(NodeTest_569, PushBack_OnInvalidNode_ThrowsException_569) {

    Node invalidNode(Zombie{});

    EXPECT_THROW(invalidNode.push_back(42), InvalidNode);

}



TEST_F(NodeTest_569, PushBack_OnEmptyNode_AddsElement_569) {

    Node emptyNode;

    emptyNode.push_back("first");

    EXPECT_EQ(emptyNode.size(), 1);

}



TEST_F(NodeTest_569, PushBack_SequenceNode_AddsElement_569) {

    Node sequenceNode = Node(NodeType::Sequence);

    sequenceNode.push_back(10);

    sequenceNode.push_back(20);

    EXPECT_EQ(sequenceNode.size(), 2);

}



TEST_F(NodeTest_569, PushBack_MapNode_ThrowsException_569) {

    Node mapNode = Node(NodeType::Map);

    EXPECT_THROW(mapNode.push_back("key"), InvalidNode);

}
