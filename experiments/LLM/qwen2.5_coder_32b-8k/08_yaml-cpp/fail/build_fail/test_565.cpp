#include "gtest/gtest.h"

#include "yaml-cpp/node/impl.h"



using namespace YAML;



class NodeTest_565 : public ::testing::Test {

protected:

    Node validNode;

    Node invalidNode;



    NodeTest_565() : validNode(NodeType::Undefined), invalidNode(Zombie(), "InvalidKey") {}

};



TEST_F(NodeTest_565, ResetWithValidNodes_565) {

    Node anotherValidNode;

    validNode.reset(anotherValidNode);

    EXPECT_TRUE(validNode.IsValid());

}



TEST_F(NodeTest_565, ResetWithInvalidLhsNode_565) {

    try {

        invalidNode.reset(validNode);

        FAIL() << "Expected an exception to be thrown";

    } catch (const InvalidNode& e) {

        EXPECT_EQ(e.msg, "InvalidKey");

    }

}



TEST_F(NodeTest_565, ResetWithInvalidRhsNode_565) {

    try {

        validNode.reset(invalidNode);

        FAIL() << "Expected an exception to be thrown";

    } catch (const InvalidNode& e) {

        EXPECT_EQ(e.msg, "InvalidKey");

    }

}



TEST_F(NodeTest_565, ResetWithBothNodesInvalid_565) {

    Node anotherInvalidNode(Zombie(), "AnotherInvalidKey");

    try {

        invalidNode.reset(anotherInvalidNode);

        FAIL() << "Expected an exception to be thrown";

    } catch (const InvalidNode& e) {

        EXPECT_EQ(e.msg, "InvalidKey");

    }

}



TEST_F(NodeTest_565, ResetSameNode_565) {

    validNode.reset(validNode);

    EXPECT_TRUE(validNode.IsValid());

}
