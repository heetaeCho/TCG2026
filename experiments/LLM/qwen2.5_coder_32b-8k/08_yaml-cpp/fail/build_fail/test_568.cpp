#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"



using namespace YAML;



class NodeTest_568 : public ::testing::Test {

protected:

    Node validNode;

    Node emptyNode;

    Node invalidNode;



    NodeTest_568() 

        : validNode(NodeType::Map),

          emptyNode(),

          invalidNode(Zombie{})

    {}

};



TEST_F(NodeTest_568, EndOfValidNode_568) {

    EXPECT_NE(validNode.end(), const_iterator());

}



TEST_F(NodeTest_568, EndOfEmptyNode_568) {

    EXPECT_EQ(emptyNode.end(), const_iterator());

}



TEST_F(NodeTest_568, EndOfInvalidNode_568) {

    EXPECT_EQ(invalidNode.end(), const_iterator());

}
