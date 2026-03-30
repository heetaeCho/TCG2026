#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_567 : public ::testing::Test {

protected:

    Node node;

};



TEST_F(NodeTest_567, BeginReturnsValidIteratorForDefinedNode_567) {

    Node definedNode;

    EXPECT_NE(definedNode.begin(), definedNode.end());

}



TEST_F(NodeTest_567, BeginReturnsInvalidIteratorForUndefinedNode_567) {

    Node undefinedNode(Zombie{});

    EXPECT_EQ(undefinedNode.begin(), undefinedNode.end());

}



TEST_F(NodeTest_567, BeginReturnsValidIteratorForEmptySequence_567) {

    Node emptySequence(YAML::NodeType::Sequence);

    EXPECT_NE(emptySequence.begin(), emptySequence.end());

}



TEST_F(NodeTest_567, BeginReturnsInvalidIteratorForScalarNode_567) {

    Node scalarNode("scalar_value");

    EXPECT_EQ(scalarNode.begin(), scalarNode.end());

}



TEST_F(NodeTest_567, BeginReturnsValidIteratorForNonEmptySequence_567) {

    Node sequence(YAML::NodeType::Sequence);

    sequence.push_back(1);

    sequence.push_back(2);

    EXPECT_NE(sequence.begin(), sequence.end());

}



TEST_F(NodeTest_567, BeginReturnsInvalidIteratorForMapWithNoEntries_567) {

    Node mapNode(YAML::NodeType::Map);

    EXPECT_EQ(mapNode.begin(), mapNode.end());

}
