#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_252 : public ::testing::Test {

protected:

    node testNode;

};



TEST_F(NodeTest_252, SetTag_NormalOperation_252) {

    std::string tag = "!example";

    testNode.set_tag(tag);

    EXPECT_EQ(testNode.tag(), tag);

}



TEST_F(NodeTest_252, SetTag_BoundaryCondition_EmptyString_252) {

    std::string tag = "";

    testNode.set_tag(tag);

    EXPECT_EQ(testNode.tag(), tag);

}



TEST_F(NodeTest_252, IsDefined_AfterSetTag_252) {

    testNode.set_tag("!example");

    EXPECT_TRUE(testNode.is_defined());

}
