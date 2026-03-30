#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_562 : public ::testing::Test {

protected:

    Node node1;

    Node node2;

};



TEST_F(NodeTest_562, IsValidNodesAreEqual_562) {

    EXPECT_TRUE(node1.is(node2));

}



TEST_F(NodeTest_562, InvalidNodeThrowsException_562) {

    Node invalidNode(Zombie{});

    EXPECT_THROW(node1.is(invalidNode), InvalidNode);

}



TEST_F(NodeTest_562, DifferentNodesAreNotEqual_562) {

    Node node3(42); // Assuming this creates a different node

    EXPECT_FALSE(node1.is(node3));

}



TEST_F(NodeTest_562, SameScalarNodesAreEqual_562) {

    Node scalarNode1("same");

    Node scalarNode2("same");

    EXPECT_TRUE(scalarNode1.is(scalarNode2));

}



TEST_F(NodeTest_562, DifferentScalarNodesAreNotEqual_562) {

    Node scalarNode1("different1");

    Node scalarNode2("different2");

    EXPECT_FALSE(scalarNode1.is(scalarNode2));

}
