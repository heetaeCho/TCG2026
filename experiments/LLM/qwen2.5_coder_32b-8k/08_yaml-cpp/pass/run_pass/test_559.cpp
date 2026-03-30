#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"



using YAML::Node;



class NodeTest_559 : public ::testing::Test {

protected:

    Node node;

};



TEST_F(NodeTest_559, SetTag_SetsCorrectTag_559) {

    std::string tag = "!mytag";

    node.SetTag(tag);

    EXPECT_EQ(node.Tag(), tag);

}



TEST_F(NodeTest_559, SetTag_EmptyStringSetsEmptyTag_559) {

    std::string tag = "";

    node.SetTag(tag);

    EXPECT_EQ(node.Tag(), tag);

}



TEST_F(NodeTest_559, SetTag_SpecialCharactersInTag_559) {

    std::string tag = "!@#$%^&*()";

    node.SetTag(tag);

    EXPECT_EQ(node.Tag(), tag);

}



TEST_F(NodeTest_559, SetTag_LongStringTag_559) {

    std::string long_tag(1024, 'a');

    node.SetTag(long_tag);

    EXPECT_EQ(node.Tag(), long_tag);

}
