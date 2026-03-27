#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"



class NodeTest_191 : public ::testing::Test {

protected:

    YAML::Node node;

};



TEST_F(NodeTest_191, IsNull_ReturnsTrueForNullType_191) {

    YAML::Node nullNode(YAML::NodeType::Null);

    EXPECT_TRUE(nullNode.IsNull());

}



TEST_F(NodeTest_191, IsNull_ReturnsFalseForScalarType_191) {

    YAML::Node scalarNode("value");

    EXPECT_FALSE(scalarNode.IsNull());

}



TEST_F(NodeTest_191, IsNull_ReturnsFalseForSequenceType_191) {

    YAML::Node sequenceNode;

    sequenceNode.push_back(1);

    EXPECT_FALSE(sequenceNode.IsNull());

}



TEST_F(NodeTest_191, IsNull_ReturnsFalseForMapType_191) {

    YAML::Node mapNode;

    mapNode["key"] = "value";

    EXPECT_FALSE(mapNode.IsNull());

}



TEST_F(NodeTest_191, IsDefined_ReturnsTrueForValidNode_191) {

    YAML::Node validNode("defined");

    EXPECT_TRUE(validNode.IsDefined());

}



TEST_F(NodeTest_191, IsDefined_ReturnsFalseForZombieNode_191) {

    YAML::Node zombieNode(YAML::detail::node(), nullptr);

    EXPECT_FALSE(zombieNode.IsDefined());

}



TEST_F(NodeTest_191, Type_ReturnsNull_ForNullType_191) {

    YAML::Node nullNode(YAML::NodeType::Null);

    EXPECT_EQ(nullNode.Type(), YAML::NodeType::Null);

}



TEST_F(NodeTest_191, Type_ReturnsScalar_ForScalarType_191) {

    YAML::Node scalarNode("value");

    EXPECT_EQ(scalarNode.Type(), YAML::NodeType::Scalar);

}



TEST_F(NodeTest_191, Type_ReturnsSequence_ForSequenceType_191) {

    YAML::Node sequenceNode;

    sequenceNode.push_back(1);

    EXPECT_EQ(sequenceNode.Type(), YAML::NodeType::Sequence);

}



TEST_F(NodeTest_191, Type_ReturnsMap_ForMapType_191) {

    YAML::Node mapNode;

    mapNode["key"] = "value";

    EXPECT_EQ(mapNode.Type(), YAML::NodeType::Map);

}



TEST_F(NodeTest_191, IsScalar_ReturnsTrueForScalarNode_191) {

    YAML::Node scalarNode("scalar");

    EXPECT_TRUE(scalarNode.IsScalar());

}



TEST_F(NodeTest_191, IsScalar_ReturnsFalseForNonScalarNode_191) {

    YAML::Node nonScalarNode(YAML::NodeType::Null);

    EXPECT_FALSE(nonScalarNode.IsScalar());

}



TEST_F(NodeTest_191, IsSequence_ReturnsTrueForSequenceNode_191) {

    YAML::Node sequenceNode;

    sequenceNode.push_back(1);

    EXPECT_TRUE(sequenceNode.IsSequence());

}



TEST_F(NodeTest_191, IsSequence_ReturnsFalseForNonSequenceNode_191) {

    YAML::Node nonSequenceNode("not_sequence");

    EXPECT_FALSE(nonSequenceNode.IsSequence());

}



TEST_F(NodeTest_191, IsMap_ReturnsTrueForMapNode_191) {

    YAML::Node mapNode;

    mapNode["key"] = "value";

    EXPECT_TRUE(mapNode.IsMap());

}



TEST_F(NodeTest_191, IsMap_ReturnsFalseForNonMapNode_191) {

    YAML::Node nonMapNode("not_map");

    EXPECT_FALSE(nonMapNode.IsMap());

}



TEST_F(NodeTest_191, OperatorBool_ReturnsTrueForValidNode_191) {

    YAML::Node validNode("value");

    EXPECT_TRUE(static_cast<bool>(validNode));

}



TEST_F(NodeTest_191, OperatorBool_ReturnsFalseForNullNode_191) {

    YAML::Node nullNode(YAML::NodeType::Null);

    EXPECT_FALSE(static_cast<bool>(nullNode));

}



TEST_F(NodeTest_191, OperatorNot_ReturnsTrueForNullNode_191) {

    YAML::Node nullNode(YAML::NodeType::Null);

    EXPECT_TRUE(!nullNode);

}



TEST_F(NodeTest_191, OperatorNot_ReturnsFalseForValidNode_191) {

    YAML::Node validNode("value");

    EXPECT_FALSE(!validNode);

}



TEST_F(NodeTest_191, Size_ReturnsZero_ForEmptySequence_191) {

    YAML::Node sequenceNode;

    EXPECT_EQ(sequenceNode.size(), 0u);

}



TEST_F(NodeTest_191, Size_ReturnsCorrectSize_ForNonEmptySequence_191) {

    YAML::Node sequenceNode;

    sequenceNode.push_back(1);

    sequenceNode.push_back(2);

    EXPECT_EQ(sequenceNode.size(), 2u);

}



TEST_F(NodeTest_191, Size_ReturnsZero_ForEmptyMap_191) {

    YAML::Node mapNode;

    EXPECT_EQ(mapNode.size(), 0u);

}



TEST_F(NodeTest_191, Size_ReturnsCorrectSize_ForNonEmptyMap_191) {

    YAML::Node mapNode;

    mapNode["key1"] = "value1";

    mapNode["key2"] = "value2";

    EXPECT_EQ(mapNode.size(), 2u);

}



TEST_F(NodeTest_191, OperatorBracket_ReturnsExistingValue_ForMapKey_191) {

    YAML::Node mapNode;

    mapNode["key"] = "value";

    EXPECT_EQ(mapNode["key"].as<std::string>(), "value");

}



TEST_F(NodeTest_191, OperatorBracket_CreatesNewEntry_ForNonexistentMapKey_191) {

    YAML::Node mapNode;

    YAML::Node& newNode = mapNode["new_key"];

    EXPECT_FALSE(newNode.IsDefined());

}
