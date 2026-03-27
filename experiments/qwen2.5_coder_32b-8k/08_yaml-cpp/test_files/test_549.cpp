#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"



using namespace YAML;



class NodeTest : public ::testing::Test {

protected:

    Node validNode;

    Node invalidNode;

    

    NodeTest() : validNode(NodeType::Map), invalidNode(Zombie{}) {}

};



TEST_F(NodeTest_549, ValidNodeMark_ReturnsValidMark_549) {

    Mark mark = validNode.Mark();

    EXPECT_FALSE(mark.is_null());

}



TEST_F(NodeTest_549, InvalidNodeMark_ThrowsInvalidNodeException_549) {

    EXPECT_THROW(invalidNode.Mark(), InvalidNode);

}



TEST_F(NodeTest_549, NullNodeMark_ReturnsNullMark_549) {

    Node nullNode;

    Mark mark = nullNode.Mark();

    EXPECT_TRUE(mark.is_null());

}
