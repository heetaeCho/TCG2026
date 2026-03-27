#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/impl.h"

#include "yaml-cpp/node/node.h"



using namespace YAML;

using ::testing::_;

using ::testing::Return;



class NodeTest : public ::testing::Test {

protected:

    Node validNode;

    Node invalidNode;



    NodeTest() : validNode(NodeType::Scalar), invalidNode(Zombie{}, "InvalidKey") {}

};



TEST_F(NodeTest_553, As_ReturnsCorrectValueForValidNode_553) {

    int expectedValue = 42;

    validNode = expectedValue;



    EXPECT_EQ(validNode.as<int>(), expectedValue);

}



TEST_F(NodeTest_553, As_ThrowsInvalidNodeExceptionForInvalidNode_553) {

    EXPECT_THROW(invalidNode.as<int>(), InvalidNode);

}



TEST_F(NodeTest_553, AsWithFallback_ReturnsFallbackForInvalidNode_553) {

    int fallbackValue = 42;



    EXPECT_EQ(invalidNode.as<int>(fallbackValue), fallbackValue);

}



TEST_F(NodeTest_553, AsWithFallback_DoesNotThrowForValidNode_553) {

    int expectedValue = 42;

    validNode = expectedValue;



    EXPECT_NO_THROW(validNode.as<int>(0));

    EXPECT_EQ(validNode.as<int>(0), expectedValue);

}



TEST_F(NodeTest_553, IsDefined_ReturnsTrueForValidNode_553) {

    EXPECT_TRUE(validNode.IsDefined());

}



TEST_F(NodeTest_553, IsDefined_ReturnsFalseForInvalidNode_553) {

    EXPECT_FALSE(invalidNode.IsDefined());

}



TEST_F(NodeTest_553, Mark_DoesNotThrowForValidNode_553) {

    EXPECT_NO_THROW(validNode.Mark());

}



TEST_F(NodeTest_553, Mark_DoesNotThrowForInvalidNode_553) {

    EXPECT_NO_THROW(invalidNode.Mark());

}



TEST_F(NodeTest_553, Type_ReturnsCorrectTypeForValidScalarNode_553) {

    validNode = "scalar";



    EXPECT_EQ(validNode.Type(), NodeType::Scalar);

}



TEST_F(NodeTest_553, IsNull_ReturnsFalseForValidNode_553) {

    EXPECT_FALSE(validNode.IsNull());

}



TEST_F(NodeTest_553, IsNull_ReturnsTrueForInvalidNode_553) {

    EXPECT_TRUE(invalidNode.IsNull());

}
