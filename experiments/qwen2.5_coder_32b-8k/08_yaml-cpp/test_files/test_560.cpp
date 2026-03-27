#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"

#include "yaml-cpp/emitterstyle.h"



using namespace YAML;



class NodeTest_560 : public ::testing::Test {

protected:

    Node validNode;

    Node invalidNode;



    NodeTest_560() : validNode(), invalidNode(Node::Zombie()) {}

};



TEST_F(NodeTest_560, Style_ReturnsDefaultForValidNode_560) {

    EXPECT_EQ(validNode.Style(), EmitterStyle::Default);

}



TEST_F(NodeTest_560, Style_ThrowsExceptionForInvalidNode_560) {

    EXPECT_THROW(invalidNode.Style(), InvalidNode);

}



TEST_F(NodeTest_560, Style_ReturnsSetStyle_560) {

    validNode.SetStyle(EmitterStyle::Block);

    EXPECT_EQ(validNode.Style(), EmitterStyle::Block);



    validNode.SetStyle(EmitterStyle::Flow);

    EXPECT_EQ(validNode.Style(), EmitterStyle::Flow);

}
