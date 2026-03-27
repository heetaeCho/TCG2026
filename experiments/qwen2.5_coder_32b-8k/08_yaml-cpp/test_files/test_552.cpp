#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/impl.h"

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_552 : public ::testing::Test {

protected:

    Node node;

};



TEST_F(NodeTest_552, ScalarValue_ReturnsCorrectString_552) {

    Node scalarNode("test_scalar");

    EXPECT_EQ(scalarNode.Scalar(), "test_scalar");

}



TEST_F(NodeTest_552, NonScalarType_ReturnsFallback_552) {

    Node nonScalarNode(NodeType::Map);

    std::string fallback = "fallback_value";

    EXPECT_EQ(nonScalarNode.as<std::string>(fallback), fallback);

}



TEST_F(NodeTest_552, NullNode_ReturnsNullString_552) {

    Node nullNode(NodeType::Null);

    std::string result = nullNode.as<std::string>("not_null");

    EXPECT_EQ(result, "null");

}



TEST_F(NodeTest_552, ValidNode_IsDefinedReturnsTrue_552) {

    Node validNode("valid_node");

    EXPECT_TRUE(validNode.IsDefined());

}



TEST_F(NodeTest_552, InvalidNode_IsDefinedReturnsFalse_552) {

    Node invalidNode(Zombie{});

    EXPECT_FALSE(invalidNode.IsDefined());

}



TEST_F(NodeTest_552, ScalarType_ReturnsTrue_552) {

    Node scalarNode("scalar");

    EXPECT_TRUE(scalarNode.IsScalar());

}



TEST_F(NodeTest_552, NonScalarType_ReturnsFalse_552) {

    Node nonScalarNode(NodeType::Map);

    EXPECT_FALSE(nonScalarNode.IsScalar());

}
