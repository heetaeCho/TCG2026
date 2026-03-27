#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node.h>



using namespace YAML::detail;



class NodeTest_250 : public ::testing::Test {

protected:

    node testNode;

};



TEST_F(NodeTest_250, SetNull_MarksAsDefined_250) {

    EXPECT_FALSE(testNode.is_defined());

    testNode.set_null();

    EXPECT_TRUE(testNode.is_defined());

}



TEST_F(NodeTest_250, SetNull_TypeIsNull_250) {

    testNode.set_null();

    EXPECT_EQ(testNode.type(), NodeType::Undefined);

}



TEST_F(NodeTest_250, MarkDefined_SetsDefinedFlag_250) {

    EXPECT_FALSE(testNode.is_defined());

    testNode.mark_defined();

    EXPECT_TRUE(testNode.is_defined());

}
