#include <gtest/gtest.h>

#include <yaml-cpp/node/node.h>



class NodeTest_196 : public ::testing::Test {

protected:

    YAML::Node validNode;

    YAML::Node invalidNode;



    void SetUp() override {

        validNode = YAML::Node();

        invalidNode = YAML::Node(YAML::Zombie{});

    }

};



TEST_F(NodeTest_196, IsDefined_ValidNode_ReturnsTrue_196) {

    EXPECT_TRUE(validNode.IsDefined());

}



TEST_F(NodeTest_196, IsDefined_InvalidNode_ReturnsFalse_196) {

    EXPECT_FALSE(invalidNode.IsDefined());

}



TEST_F(NodeTest_196, OperatorBool_ValidNode_ReturnsTrue_196) {

    EXPECT_TRUE(static_cast<bool>(validNode));

}



TEST_F(NodeTest_196, OperatorBool_InvalidNode_ReturnsFalse_196) {

    EXPECT_FALSE(static_cast<bool>(invalidNode));

}



TEST_F(NodeTest_196, OperatorNot_ValidNode_ReturnsFalse_196) {

    EXPECT_FALSE(!validNode);

}



TEST_F(NodeTest_196, OperatorNot_InvalidNode_ReturnsTrue_196) {

    EXPECT_TRUE(!invalidNode);

}



TEST_F(NodeTest_196, Type_ValidNode_ReturnsNodeTypeValue_196) {

    YAML::NodeType::value type = validNode.Type();

    EXPECT_TRUE(type == YAML::NodeType::Undefined || 

                type == YAML::NodeType::Null ||

                type == YAML::NodeType::Scalar ||

                type == YAML::NodeType::Sequence ||

                type == YAML::NodeType::Map);

}



TEST_F(NodeTest_196, Type_InvalidNode_ReturnsUndefined_196) {

    EXPECT_EQ(invalidNode.Type(), YAML::NodeType::Undefined);

}
