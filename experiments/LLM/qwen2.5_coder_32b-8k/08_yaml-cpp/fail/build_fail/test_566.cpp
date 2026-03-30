#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"



namespace YAML {

    class NodeTest_566 : public ::testing::Test {

    protected:

        Node validNode;

        Node invalidNode;



        NodeTest_566() : validNode(), invalidNode(Node(Node::Zombie{})) {}

    };



    TEST_F(NodeTest_566, Size_ReturnsZeroForEmptyNode_566) {

        EXPECT_EQ(validNode.size(), 0);

    }



    TEST_F(NodeTest_566, Size_ThrowsExceptionForInvalidNode_566) {

        EXPECT_THROW(invalidNode.size(), InvalidNode);

    }



    // Assuming validNode can be made to have a size > 0 through some other means

    TEST_F(NodeTest_566, Size_ReturnsCorrectSizeForNonEmptyNode_566) {

        // This test assumes there's a way to populate the node with elements

        // For example, using push_back or operator[]

        validNode.push_back(1);

        EXPECT_EQ(validNode.size(), 1);

    }



    TEST_F(NodeTest_566, Size_ReturnsZeroForNullNode_566) {

        Node nullNode;

        nullNode.set_null();

        EXPECT_EQ(nullNode.size(), 0);

    }

}
