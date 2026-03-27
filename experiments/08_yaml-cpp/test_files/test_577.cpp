#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_577 : public ::testing::Test {

protected:

    Node defaultNode;

    Node scalarNode;

    Node sequenceNode;

    Node mapNode;



    NodeTest_577() 

        : defaultNode(), 

          scalarNode("scalarValue"), 

          sequenceNode(NodeType::Sequence), 

          mapNode(NodeType::Map) {}



    virtual void SetUp() {

        sequenceNode.push_back("item1");

        sequenceNode.push_back(42);

        mapNode["key1"] = "value1";

        mapNode[2] = "value2";

    }

};



TEST_F(NodeTest_577, IsDefined_ReturnsTrueForDefaultNode_577) {

    EXPECT_TRUE(defaultNode.IsDefined());

}



TEST_F(NodeTest_577, IsDefined_ReturnsTrueForScalarNode_577) {

    EXPECT_TRUE(scalarNode.IsDefined());

}



TEST_F(NodeTest_577, IsDefined_ReturnsTrueForSequenceNode_577) {

    EXPECT_TRUE(sequenceNode.IsDefined());

}



TEST_F(NodeTest_577, IsDefined_ReturnsTrueForMapNode_577) {

    EXPECT_TRUE(mapNode.IsDefined());

}



TEST_F(NodeTest_577, IsNull_ReturnsFalseForDefaultNode_577) {

    EXPECT_FALSE(defaultNode.IsNull());

}



TEST_F(NodeTest_577, IsNull_ReturnsFalseForScalarNode_577) {

    EXPECT_FALSE(scalarNode.IsNull());

}



TEST_F(NodeTest_577, IsNull_ReturnsFalseForSequenceNode_577) {

    EXPECT_FALSE(sequenceNode.IsNull());

}



TEST_F(NodeTest_577, IsNull_ReturnsFalseForMapNode_577) {

    EXPECT_FALSE(mapNode.IsNull());

}



TEST_F(NodeTest_577, IsScalar_ReturnsTrueForScalarNode_577) {

    EXPECT_TRUE(scalarNode.IsScalar());

}



TEST_F(NodeTest_577, IsScalar_ReturnsFalseForSequenceNode_577) {

    EXPECT_FALSE(sequenceNode.IsScalar());

}



TEST_F(NodeTest_577, IsScalar_ReturnsFalseForMapNode_577) {

    EXPECT_FALSE(mapNode.IsScalar());

}



TEST_F(NodeTest_577, IsSequence_ReturnsTrueForSequenceNode_577) {

    EXPECT_TRUE(sequenceNode.IsSequence());

}



TEST_F(NodeTest_577, IsSequence_ReturnsFalseForScalarNode_577) {

    EXPECT_FALSE(scalarNode.IsSequence());

}



TEST_F(NodeTest_577, IsSequence_ReturnsFalseForMapNode_577) {

    EXPECT_FALSE(mapNode.IsSequence());

}



TEST_F(NodeTest_577, IsMap_ReturnsTrueForMapNode_577) {

    EXPECT_TRUE(mapNode.IsMap());

}



TEST_F(NodeTest_577, IsMap_ReturnsFalseForScalarNode_577) {

    EXPECT_FALSE(scalarNode.IsMap());

}



TEST_F(NodeTest_577, IsMap_ReturnsFalseForSequenceNode_577) {

    EXPECT_FALSE(sequenceNode.IsMap());

}



TEST_F(NodeTest_577, Scalar_ReturnsCorrectValueForScalarNode_577) {

    EXPECT_EQ(scalarNode.Scalar(), "scalarValue");

}



TEST_F(NodeTest_577, Size_ReturnsCorrectSizeForSequenceNode_577) {

    EXPECT_EQ(sequenceNode.size(), 2);

}



TEST_F(NodeTest_577, Size_ReturnsCorrectSizeForMapNode_577) {

    EXPECT_EQ(mapNode.size(), 2);

}



TEST_F(NodeTest_577, OperatorBracket_ReturnsCorrectValueForMapNodeWithKeyString_577) {

    EXPECT_EQ(mapNode["key1"].Scalar(), "value1");

}



TEST_F(NodeTest_577, OperatorBracket_ReturnsCorrectValueForMapNodeWithKeyInt_577) {

    EXPECT_EQ(mapNode[2].Scalar(), "value2");

}



TEST_F(NodeTest_577, Remove_ReturnsTrueAndRemovesItemFromMapNode_577) {

    EXPECT_TRUE(mapNode.remove("key1"));

    EXPECT_EQ(mapNode.size(), 1);

}



TEST_F(NodeTest_577, ForceInsert_AddsNewItemToMapNode_577) {

    mapNode.force_insert("newKey", "newValue");

    EXPECT_EQ(mapNode["newKey"].Scalar(), "newValue");

    EXPECT_EQ(mapNode.size(), 3);

}



TEST_F(NodeTest_577, OperatorEquality_ReturnsTrueForEqualNodes_577) {

    Node anotherDefaultNode;

    EXPECT_TRUE(defaultNode == anotherDefaultNode);



    Node anotherScalarNode("scalarValue");

    EXPECT_TRUE(scalarNode == anotherScalarNode);

}



TEST_F(NodeTest_577, OperatorEquality_ReturnsFalseForDifferentNodes_577) {

    EXPECT_FALSE(defaultNode == scalarNode);

}
