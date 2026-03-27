#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"



namespace YAML {



class NodeTest : public ::testing::Test {

protected:

    Node mapNode;

    Node scalarNode;



    NodeTest() : mapNode(NodeType::Map), scalarNode("scalar_value") {}

};



TEST_F(NodeTest_194, IsMap_ReturnsTrueForMapNode_194) {

    EXPECT_TRUE(mapNode.IsMap());

}



TEST_F(NodeTest_194, IsMap_ReturnsFalseForScalarNode_194) {

    EXPECT_FALSE(scalarNode.IsMap());

}



TEST_F(NodeTest_194, IsDefined_ReturnsTrueForValidNodes_194) {

    EXPECT_TRUE(mapNode.IsDefined());

    EXPECT_TRUE(scalarNode.IsDefined());

}



TEST_F(NodeTest_194, IsNull_ReturnsFalseForNonEmptyNodes_194) {

    EXPECT_FALSE(mapNode.IsNull());

    EXPECT_FALSE(scalarNode.IsNull());

}



TEST_F(NodeTest_194, IsScalar_ReturnsTrueForScalarNode_194) {

    EXPECT_TRUE(scalarNode.IsScalar());

}



TEST_F(NodeTest_194, IsScalar_ReturnsFalseForMapNode_194) {

    EXPECT_FALSE(mapNode.IsScalar());

}



TEST_F(NodeTest_194, Type_ReturnsMapForMapNode_194) {

    EXPECT_EQ(mapNode.Type(), NodeType::Map);

}



TEST_F(NodeTest_194, Type_ReturnsScalarForScalarNode_194) {

    EXPECT_EQ(scalarNode.Type(), NodeType::Scalar);

}



TEST_F(NodeTest_194, Scalar_ReturnsCorrectValueForScalarNode_194) {

    EXPECT_EQ(scalarNode.Scalar(), "scalar_value");

}



TEST_F(NodeTest_194, Size_ReturnsZeroForEmptyMap_194) {

    EXPECT_EQ(mapNode.size(), 0);

}



TEST_F(NodeTest_194, OperatorBool_ReturnsTrueForNonEmptyNodes_194) {

    EXPECT_TRUE(static_cast<bool>(mapNode));

    EXPECT_TRUE(static_cast<bool>(scalarNode));

}



TEST_F(NodeTest_194, OperatorNot_ReturnsFalseForNonEmptyNodes_194) {

    EXPECT_FALSE(!mapNode);

    EXPECT_FALSE(!scalarNode);

}



} // namespace YAML
