#include "yaml-cpp/node/node.h"

#include <gtest/gtest.h>



namespace YAML {

    class NodeTest_195 : public ::testing::Test {};



    TEST_F(NodeTest_195, IsDefined_ReturnsTrueForValidNode_195) {

        Node node;

        EXPECT_TRUE(node.IsDefined());

    }



    TEST_F(NodeTest_195, IsDefined_ReturnsFalseForZombieNode_195) {

        Node::Zombie zombie;

        Node zombieNode(zombie);

        EXPECT_FALSE(zombieNode.IsDefined());

    }



    TEST_F(NodeTest_195, BoolConversion_ReturnsTrueForValidNode_195) {

        Node node;

        EXPECT_TRUE(static_cast<bool>(node));

    }



    TEST_F(NodeTest_195, BoolConversion_ReturnsFalseForZombieNode_195) {

        Node::Zombie zombie;

        Node zombieNode(zombie);

        EXPECT_FALSE(static_cast<bool>(zombieNode));

    }



    TEST_F(NodeTest_195, IsNull_ReturnsTrueForNullType_195) {

        Node node(NodeType::Null);

        EXPECT_TRUE(node.IsNull());

    }



    TEST_F(NodeTest_195, IsScalar_ReturnsTrueForScalarType_195) {

        Node node(NodeType::Scalar);

        EXPECT_TRUE(node.IsScalar());

    }



    TEST_F(NodeTest_195, IsSequence_ReturnsTrueForSequenceType_195) {

        Node node(NodeType::Sequence);

        EXPECT_TRUE(node.IsSequence());

    }



    TEST_F(NodeTest_195, IsMap_ReturnsTrueForMapType_195) {

        Node node(NodeType::Map);

        EXPECT_TRUE(node.IsMap());

    }



    TEST_F(NodeTest_195, Type_ReturnsNodeTypeForValidNode_195) {

        Node scalarNode(NodeType::Scalar);

        EXPECT_EQ(scalarNode.Type(), NodeType::Scalar);



        Node sequenceNode(NodeType::Sequence);

        EXPECT_EQ(sequenceNode.Type(), NodeType::Sequence);



        Node mapNode(NodeType::Map);

        EXPECT_EQ(mapNode.Type(), NodeType::Map);



        Node nullNode(NodeType::Null);

        EXPECT_EQ(nullNode.Type(), NodeType::Null);

    }



    TEST_F(NodeTest_195, Scalar_ReturnsEmptyStringForNonScalarNode_195) {

        Node node(NodeType::Sequence);

        EXPECT_TRUE(node.Scalar().empty());

    }



    TEST_F(NodeTest_195, Tag_ReturnsEmptyStringForUntaggedNode_195) {

        Node node;

        EXPECT_TRUE(node.Tag().empty());

    }

}
