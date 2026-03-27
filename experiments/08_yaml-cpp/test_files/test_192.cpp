#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_192 : public ::testing::Test {

protected:

    Node scalarNode;

    Node sequenceNode;

    Node mapNode;

    Node undefinedNode;



    NodeTest_192()

        : scalarNode(NodeType::Scalar),

          sequenceNode(NodeType::Sequence),

          mapNode(NodeType::Map),

          undefinedNode(Zombie{}) {}

};



TEST_F(NodeTest_192, IsScalar_ReturnsTrueForScalarNode_192) {

    EXPECT_TRUE(scalarNode.IsScalar());

}



TEST_F(NodeTest_192, IsScalar_ReturnsFalseForSequenceNode_192) {

    EXPECT_FALSE(sequenceNode.IsScalar());

}



TEST_F(NodeTest_192, IsScalar_ReturnsFalseForMapNode_192) {

    EXPECT_FALSE(mapNode.IsScalar());

}



TEST_F(NodeTest_192, IsScalar_ReturnsFalseForUndefinedNode_192) {

    EXPECT_FALSE(undefinedNode.IsScalar());

}



TEST_F(NodeTest_192, Type_ReturnsScalarForScalarNode_192) {

    EXPECT_EQ(scalarNode.Type(), NodeType::Scalar);

}



TEST_F(NodeTest_192, Type_ReturnsSequenceForSequenceNode_192) {

    EXPECT_EQ(sequenceNode.Type(), NodeType::Sequence);

}



TEST_F(NodeTest_192, Type_ReturnsMapForMapNode_192) {

    EXPECT_EQ(mapNode.Type(), NodeType::Map);

}



TEST_F(NodeTest_192, IsDefined_ReturnsTrueForScalarNode_192) {

    EXPECT_TRUE(scalarNode.IsDefined());

}



TEST_F(NodeTest_192, IsDefined_ReturnsFalseForUndefinedNode_192) {

    EXPECT_FALSE(undefinedNode.IsDefined());

}



TEST_F(NodeTest_192, IsNull_ReturnsFalseForScalarNode_192) {

    EXPECT_FALSE(scalarNode.IsNull());

}



TEST_F(NodeTest_192, IsNull_ReturnsTrueForUndefinedNode_192) {

    EXPECT_TRUE(undefinedNode.IsNull());

}
