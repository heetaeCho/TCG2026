#include "gtest/gtest.h"

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_193 : public ::testing::Test {

protected:

    Node nodeSequence;

    Node nodeScalar;

    Node nodeUndefined;



    NodeTest_193() 

        : nodeSequence(NodeType::Sequence),

          nodeScalar("test"),

          nodeUndefined(Zombie()) {}

};



TEST_F(NodeTest_193, IsSequence_ReturnsTrueForSequence_193) {

    EXPECT_TRUE(nodeSequence.IsSequence());

}



TEST_F(NodeTest_193, IsSequence_ReturnsFalseForScalar_193) {

    EXPECT_FALSE(nodeScalar.IsSequence());

}



TEST_F(NodeTest_193, IsSequence_ReturnsFalseForUndefinedNode_193) {

    EXPECT_FALSE(nodeUndefined.IsSequence());

}



TEST_F(NodeTest_193, IsDefined_ReturnsTrueForValidNodes_193) {

    EXPECT_TRUE(nodeSequence.IsDefined());

    EXPECT_TRUE(nodeScalar.IsDefined());

}



TEST_F(NodeTest_193, IsDefined_ReturnsFalseForUndefinedNode_193) {

    EXPECT_FALSE(nodeUndefined.IsDefined());

}



TEST_F(NodeTest_193, Type_ReturnsCorrectTypeForSequence_193) {

    EXPECT_EQ(nodeSequence.Type(), NodeType::Sequence);

}



TEST_F(NodeTest_193, Type_ReturnsCorrectTypeForScalar_193) {

    EXPECT_EQ(nodeScalar.Type(), NodeType::Scalar);

}



TEST_F(NodeTest_193, Scalar_ReturnsCorrectValueForScalarNode_193) {

    EXPECT_EQ(nodeScalar.Scalar(), "test");

}



TEST_F(NodeTest_193, Scalar_ThrowsExceptionForSequenceNode_193) {

    EXPECT_THROW(nodeSequence.Scalar(), InvalidNode);

}



TEST_F(NodeTest_193, Scalar_ThrowsExceptionForUndefinedNode_193) {

    EXPECT_THROW(nodeUndefined.Scalar(), InvalidNode);

}
