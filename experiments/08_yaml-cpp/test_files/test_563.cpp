#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"

#include "yaml-cpp/node/node.h"



using namespace YAML;



class NodeTest_563 : public ::testing::Test {

protected:

    Node node;

};



TEST_F(NodeTest_563, Constructor_Default_563) {

    EXPECT_TRUE(node.IsDefined());

}



TEST_F(NodeTest_563, Constructor_Value_563) {

    Node intNode(42);

    EXPECT_TRUE(intNode.IsScalar());



    Node strNode("test");

    EXPECT_TRUE(strNode.IsScalar());

}



TEST_F(NodeTest_563, Assignment_Operator_563) {

    node = 10;

    EXPECT_EQ(node.as<int>(), 10);



    node = "Hello";

    EXPECT_EQ(node.as<std::string>(), "Hello");



    Node anotherNode = node;

    EXPECT_TRUE(anotherNode.IsScalar());

    EXPECT_EQ(anotherNode.as<std::string>(), "Hello");

}



TEST_F(NodeTest_563, IsDefined_Valid_563) {

    EXPECT_TRUE(node.IsDefined());



    Node undefinedNode(Zombie{});

    EXPECT_FALSE(undefinedNode.IsDefined());

}



TEST_F(NodeTest_563, Reset_Method_563) {

    node = 42;

    Node anotherNode(10);



    node.reset(anotherNode);

    EXPECT_EQ(node.as<int>(), 10);

}



TEST_F(NodeTest_563, Scalar_Type_563) {

    node = "test";

    EXPECT_TRUE(node.IsScalar());

    EXPECT_EQ(node.Scalar(), "test");

}



TEST_F(NodeTest_563, Tag_Method_563) {

    node.SetTag("tag:yaml.org,2002:int");

    EXPECT_EQ(node.Tag(), "tag:yaml.org,2002:int");

}



TEST_F(NodeTest_563, Style_Method_563) {

    node.SetStyle(EmitterStyle::Flow);

    EXPECT_EQ(node.Style(), EmitterStyle::Flow);



    node.SetStyle(EmitterStyle::Block);

    EXPECT_EQ(node.Style(), EmitterStyle::Block);

}



TEST_F(NodeTest_563, Is_Type_Checks_563) {

    Node nullNode;

    EXPECT_TRUE(nullNode.IsNull());



    Node scalarNode("value");

    EXPECT_TRUE(scalarNode.IsScalar());



    Node sequenceNode(std::vector<int>{1, 2, 3});

    EXPECT_TRUE(sequenceNode.IsSequence());



    Node mapNode({{"key", "value"}});

    EXPECT_TRUE(mapNode.IsMap());

}



TEST_F(NodeTest_563, Bool_Conversion_Operator_563) {

    Node validNode("test");

    EXPECT_TRUE(static_cast<bool>(validNode));



    Node invalidNode(Zombie{});

    EXPECT_FALSE(static_cast<bool>(invalidNode));

}



TEST_F(NodeTest_563, Logical_Not_Operator_563) {

    Node validNode("test");

    EXPECT_FALSE(!validNode);



    Node invalidNode(Zombie{});

    EXPECT_TRUE(!invalidNode);

}
