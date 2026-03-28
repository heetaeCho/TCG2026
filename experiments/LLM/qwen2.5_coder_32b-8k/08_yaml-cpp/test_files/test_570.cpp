#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"



using namespace YAML;



class NodeTest_570 : public ::testing::Test {

protected:

    Node node1;

    Node node2;

};



TEST_F(NodeTest_570, PushBackValidNodes_570) {

    std::size_t initialSize = node1.size();

    node1.push_back(node2);

    EXPECT_EQ(node1.size(), initialSize + 1);

}



TEST_F(NodeTest_570, PushBackSameNodeTwice_570) {

    std::size_t initialSize = node1.size();

    node1.push_back(node2);

    node1.push_back(node2);

    EXPECT_EQ(node1.size(), initialSize + 2);

}



TEST_F(NodeTest_570, PushBackOnUndefinedNode_570) {

    Node undefinedNode(Zombie{});

    std::size_t initialSize = node1.size();

    node1.push_back(undefinedNode);

    EXPECT_EQ(node1.size(), initialSize); // No change as the push should fail silently

}



TEST_F(NodeTest_570, SizeAfterMultiplePushBacks_570) {

    Node node3;

    std::size_t initialSize = node1.size();

    node1.push_back(node2);

    node1.push_back(node3);

    EXPECT_EQ(node1.size(), initialSize + 2);

}



TEST_F(NodeTest_570, PushBackEmptyNode_570) {

    Node emptyNode;

    std::size_t initialSize = node1.size();

    node1.push_back(emptyNode);

    EXPECT_EQ(node1.size(), initialSize + 1);

}
