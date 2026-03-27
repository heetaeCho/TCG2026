#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"



using namespace YAML;



class NodeTest_548 : public ::testing::Test {

protected:

    Node defaultNode;

    Node validScalarNode;

    Node invalidNode;



    NodeTest_548() 

        : defaultNode(),

          validScalarNode("some scalar value"),

          invalidNode(Node::Zombie())

    {}

};



TEST_F(NodeTest_548, IsDefined_ReturnsTrueForDefaultConstructedNode_548) {

    EXPECT_TRUE(defaultNode.IsDefined());

}



TEST_F(NodeTest_548, IsDefined_ReturnsTrueForValidScalarNode_548) {

    EXPECT_TRUE(validScalarNode.IsDefined());

}



TEST_F(NodeTest_548, IsDefined_ReturnsFalseForInvalidNode_548) {

    EXPECT_FALSE(invalidNode.IsDefined());

}
