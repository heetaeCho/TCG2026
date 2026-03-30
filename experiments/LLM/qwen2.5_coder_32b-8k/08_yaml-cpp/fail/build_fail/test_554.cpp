#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_554 : public ::testing::Test {

protected:

    Node validScalarNode;

    Node nullNode;

    Node undefinedNode;

    Node invalidNode;



    void SetUp() override {

        validScalarNode = Node("valid_scalar");

        nullNode = Node(NodeType::Null);

        undefinedNode = Node(Zombie{});

        invalidNode = Node(Zombie{}, "invalid_key");

    }

};



TEST_F(NodeTest_554, ValidScalar_ReturnsScalarValue_554) {

    as_if<std::string> converter(validScalarNode);

    EXPECT_EQ(converter(), "valid_scalar");

}



TEST_F(NodeTest_554, NullNode_ReturnsNullString_554) {

    as_if<std::string> converter(nullNode);

    EXPECT_EQ(converter(), "null");

}



TEST_F(NodeTest_554, UndefinedNode_ThrowsInvalidNodeException_554) {

    as_if<std::string> converter(undefinedNode);

    EXPECT_THROW(converter(), InvalidNode);

}



TEST_F(NodeTest_554, InvalidNode_ThrowsInvalidNodeExceptionWithKey_554) {

    as_if<std::string> converter(invalidNode);

    EXPECT_THROW(converter(), InvalidNode);

}



TEST_F(NodeTest_554, NonScalarNode_ThrowsTypedBadConversionException_554) {

    Node nonScalarNode = Node(NodeType::Sequence);

    as_if<std::string> converter(nonScalarNode);

    EXPECT_THROW(converter(), TypedBadConversion<std::string>);

}



TEST_F(NodeTest_554, ValidScalarWithFallback_ReturnsScalarValue_554) {

    as_if<std::string> converter(validScalarNode);

    EXPECT_EQ(converter("fallback"), "valid_scalar");

}



TEST_F(NodeTest_554, NullNodeWithFallback_ReturnsNullString_554) {

    as_if<std::string> converter(nullNode);

    EXPECT_EQ(converter("fallback"), "null");

}



TEST_F(NodeTest_554, UndefinedNodeWithFallback_ReturnsFallbackValue_554) {

    as_if<std::string> converter(undefinedNode);

    EXPECT_EQ(converter("fallback"), "fallback");

}



TEST_F(NodeTest_554, InvalidNodeWithFallback_ReturnsFallbackValue_554) {

    as_if<std::string> converter(invalidNode);

    EXPECT_EQ(converter("fallback"), "fallback");

}



TEST_F(NodeTest_554, NonScalarNodeWithFallback_ReturnsFallbackValue_554) {

    Node nonScalarNode = Node(NodeType::Sequence);

    as_if<std::string> converter(nonScalarNode);

    EXPECT_EQ(converter("fallback"), "fallback");

}
