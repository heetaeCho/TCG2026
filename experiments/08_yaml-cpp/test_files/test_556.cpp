#include <gtest/gtest.h>

#include <yaml-cpp/node/impl.h>



using YAML::Node;



class NodeTest_556 : public ::testing::Test {

protected:

    Node validNode;

    Node invalidNode;



    NodeTest_556() : validNode(42), invalidNode(Node::Zombie{}) {}

};



TEST_F(NodeTest_556, As_ReturnsValueWhenValid_556) {

    int result = validNode.as<int>();

    EXPECT_EQ(result, 42);

}



TEST_F(NodeTest_556, As_ReturnsFallbackWhenInvalid_556) {

    int fallback = 0;

    int result = invalidNode.as<int>(fallback);

    EXPECT_EQ(result, fallback);

}



TEST_F(NodeTest_556, IsDefined_ReturnsTrueForValidNode_556) {

    bool isDefined = validNode.IsDefined();

    EXPECT_TRUE(isDefined);

}



TEST_F(NodeTest_556, IsDefined_ReturnsFalseForInvalidNode_556) {

    bool isDefined = invalidNode.IsDefined();

    EXPECT_FALSE(isDefined);

}



TEST_F(NodeTest_556, IsValidNode_CanConvertToBool_556) {

    EXPECT_TRUE(static_cast<bool>(validNode));

}



TEST_F(NodeTest_556, IsInvalidNode_ConvertsToFalse_556) {

    EXPECT_FALSE(static_cast<bool>(invalidNode));

}



TEST_F(NodeTest_556, OperatorNot_ReturnsTrueForInvalidNode_556) {

    EXPECT_TRUE(!invalidNode);

}



TEST_F(NodeTest_556, OperatorNot_ReturnsFalseForValidNode_556) {

    EXPECT_FALSE(!validNode);

}
