#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"

#include "yaml-cpp/node/impl.h"



using namespace YAML;



class NodeTest_551 : public ::testing::Test {

protected:

    Node node;

};



TEST_F(NodeTest_551, AsWithFallback_ReturnsFallbackWhenNodeIsInvalid_551) {

    Node invalidNode(Zombie());

    int fallback = 42;

    EXPECT_EQ(invalidNode.as<int>(fallback), fallback);

}



TEST_F(NodeTest_551, AsWithFallback_ReturnsDecodedValueWhenNodeIsValid_551) {

    Node validNode(42);

    int fallback = 0;

    EXPECT_EQ(validNode.as<int>(fallback), 42);

}



TEST_F(NodeTest_551, AsWithoutFallback_ThrowsExceptionForInvalidNode_551) {

    Node invalidNode(Zombie());

    EXPECT_THROW(invalidNode.as<int>(), Exception);

}



TEST_F(NodeTest_551, IsDefined_ReturnsFalseForInvalidNode_551) {

    Node invalidNode(Zombie());

    EXPECT_FALSE(invalidNode.IsDefined());

}



TEST_F(NodeTest_551, IsDefined_ReturnsTrueForValidNode_551) {

    Node validNode(42);

    EXPECT_TRUE(validNode.IsDefined());

}



TEST_F(NodeTest_551, Type_ReturnsCorrectTypeForScalarNode_551) {

    Node scalarNode("example");

    EXPECT_EQ(scalarNode.Type(), NodeType::Scalar);

}



TEST_F(NodeTest_551, Type_ReturnsCorrectTypeForSequenceNode_551) {

    Node sequenceNode;

    sequenceNode.push_back(42);

    sequenceNode.push_back("test");

    EXPECT_EQ(sequenceNode.Type(), NodeType::Sequence);

}



TEST_F(NodeTest_551, Type_ReturnsCorrectTypeForMapNode_551) {

    Node mapNode;

    mapNode["key"] = "value";

    EXPECT_EQ(mapNode.Type(), NodeType::Map);

}



TEST_F(NodeTest_551, Scalar_ReturnsEmptyStringForNonScalarNode_551) {

    Node nonScalarNode;

    nonScalarNode.push_back(42);

    EXPECT_TRUE(nonScalarNode.Scalar().empty());

}



TEST_F(NodeTest_551, Scalar_ReturnsCorrectValueForScalarNode_551) {

    Node scalarNode("example");

    EXPECT_EQ(scalarNode.Scalar(), "example");

}
