#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_685 : public ::testing::Test {

protected:

    void SetUp() override {}

};



TEST_F(NodeTest_685, DefaultConstructor_IsDefined_ReturnsTrue_685) {

    Node node;

    EXPECT_TRUE(node.IsDefined());

}



TEST_F(NodeTest_685, TypeConstructor_SetsCorrectType_685) {

    Node node(NodeType::Map);

    EXPECT_EQ(node.Type(), NodeType::Map);

}



TEST_F(NodeTest_685, IsNull_OnDefaultNode_ReturnsTrue_685) {

    Node node;

    EXPECT_TRUE(node.IsNull());

}



TEST_F(NodeTest_685, IsScalar_OnDefaultNode_ReturnsFalse_685) {

    Node node;

    EXPECT_FALSE(node.IsScalar());

}



TEST_F(NodeTest_685, IsSequence_OnDefaultNode_ReturnsFalse_685) {

    Node node;

    EXPECT_FALSE(node.IsSequence());

}



TEST_F(NodeTest_685, IsMap_OnDefaultNode_ReturnsFalse_685) {

    Node node;

    EXPECT_FALSE(node.IsMap());

}



TEST_F(NodeTest_685, BooleanConversion_DefaultNode_IsTrue_685) {

    Node node;

    EXPECT_TRUE(static_cast<bool>(node));

}



TEST_F(NodeTest_685, NotOperator_DefaultNode_IsFalse_685) {

    Node node;

    EXPECT_FALSE(!node);

}



TEST_F(NodeTest_685, Scalar_OnDefaultNode_ReturnsEmptyString_685) {

    Node node;

    EXPECT_EQ(node.Scalar(), "");

}



TEST_F(NodeTest_685, Tag_OnDefaultNode_ReturnsEmptyString_685) {

    Node node;

    EXPECT_EQ(node.Tag(), "");

}



TEST_F(NodeTest_685, Style_OnDefaultNode_ReturnsBlockStyle_685) {

    Node node;

    EXPECT_EQ(node.Style(), EmitterStyle::Block);

}



TEST_F(NodeTest_685, Size_OnDefaultNode_ReturnsZero_685) {

    Node node;

    EXPECT_EQ(node.size(), 0);

}



TEST_F(NodeTest_685, Begin_EqualsEnd_OnEmptyNode_685) {

    Node node;

    EXPECT_EQ(node.begin(), node.end());

}



TEST_F(NodeTest_685, Remove_NonExistingKey_ReturnsFalse_685) {

    Node node(NodeType::Map);

    EXPECT_FALSE(node.remove("non_existent_key"));

}



TEST_F(NodeTest_685, ForceInsert_AddsKeyValuePairs_685) {

    Node node(NodeType::Map);

    node.force_insert("key", "value");

    EXPECT_EQ(node["key"].Scalar(), "value");

}
