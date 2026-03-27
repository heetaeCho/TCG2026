#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"



using namespace YAML;



class NodeTest_555 : public ::testing::Test {

protected:

    Node validNode;

    Node invalidNode;



    NodeTest_555() : validNode(123), invalidNode(Zombie(), "InvalidKey") {}

};



TEST_F(NodeTest_555, AsValidNodeReturnsCorrectValue_555) {

    EXPECT_EQ(validNode.as<int>(), 123);

}



TEST_F(NodeTest_555, AsInvalidNodeThrowsException_555) {

    EXPECT_THROW(invalidNode.as<int>(), InvalidNode);

}



TEST_F(NodeTest_555, IsDefinedValidNodeReturnsTrue_555) {

    EXPECT_TRUE(validNode.IsDefined());

}



TEST_F(NodeTest_555, IsDefinedInvalidNodeReturnsFalse_555) {

    EXPECT_FALSE(invalidNode.IsDefined());

}



TEST_F(NodeTest_555, IsValidNodeReturnsTrue_555) {

    EXPECT_TRUE(validNode.m_isValid);

}



TEST_F(NodeTest_555, IsInvalidNodeReturnsFalse_555) {

    EXPECT_FALSE(invalidNode.m_isValid);

}



TEST_F(NodeTest_555, TypeOfValidNodeIsCorrect_555) {

    EXPECT_EQ(validNode.Type(), NodeType::value::ScalarType);

}



TEST_F(NodeTest_555, ScalarOfValidNodeReturnsCorrectValue_555) {

    EXPECT_EQ(validNode.Scalar(), "123");

}



TEST_F(NodeTest_555, TagOfValidNodeIsEmptyStringByDefault_555) {

    EXPECT_EQ(validNode.Tag(), "");

}
