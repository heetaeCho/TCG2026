#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_550 : public ::testing::Test {

protected:

    Node validNode;

    Node nullNode;

    Node undefinedNode;



    NodeTest_550() 

        : validNode(NodeType::Scalar), 

          nullNode(), 

          undefinedNode(Zombie{}) {}

};



TEST_F(NodeTest_550, Type_ReturnsScalarForValidScalarNode_550) {

    EXPECT_EQ(validNode.Type(), NodeType::Scalar);

}



TEST_F(NodeTest_550, Type_ReturnsNullForDefaultConstructedNode_550) {

    EXPECT_EQ(nullNode.Type(), NodeType::Null);

}



TEST_F(NodeTest_550, Type_ThrowsExceptionForUndefinedNode_550) {

    EXPECT_THROW(undefinedNode.Type(), InvalidNode);

}



TEST_F(NodeTest_550, IsDefined_ReturnsTrueForValidNode_550) {

    EXPECT_TRUE(validNode.IsDefined());

}



TEST_F(NodeTest_550, IsDefined_ReturnsFalseForUndefinedNode_550) {

    EXPECT_FALSE(undefinedNode.IsDefined());

}



TEST_F(NodeTest_550, IsNull_ReturnsTrueForDefaultConstructedNode_550) {

    EXPECT_TRUE(nullNode.IsNull());

}



TEST_F(NodeTest_550, IsNull_ReturnsFalseForValidNode_550) {

    EXPECT_FALSE(validNode.IsNull());

}
