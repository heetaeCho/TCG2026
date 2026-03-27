#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_572 : public ::testing::Test {

protected:

    Node root;

};



TEST_F(NodeTest_572, AccessExistingKey_572) {

    root["key"] = 42;

    const Node node = root["key"];

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(node.as<int>(), 42);

}



TEST_F(NodeTest_572, AccessNonExistingKey_572) {

    const Node node = root["nonexistent"];

    EXPECT_FALSE(node.IsDefined());

}



TEST_F(NodeTest_572, AccessEmptyNode_572) {

    Node emptyNode;

    const Node node = emptyNode["key"];

    EXPECT_FALSE(node.IsDefined());

}



TEST_F(NodeTest_572, AccessMultipleKeys_572) {

    root["level1"]["level2"] = 42;

    const Node node = root["level1"]["level2"];

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(node.as<int>(), 42);

}



TEST_F(NodeTest_572, AccessEmptyStringKey_572) {

    root[""] = 42;

    const Node node = root[std::string()];

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(node.as<int>(), 42);

}



TEST_F(NodeTest_572, AccessNumericKeyAsString_572) {

    root["123"] = 42;

    const Node node = root["123"];

    EXPECT_TRUE(node.IsDefined());

    EXPECT_EQ(node.as<int>(), 42);

}
