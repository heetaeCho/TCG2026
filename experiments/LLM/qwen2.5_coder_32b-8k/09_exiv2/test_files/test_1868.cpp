#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



class XMP_NodeTest_1868 : public ::testing::Test {

protected:

    void SetUp() override {

        parent = new XMP_Node(nullptr, "parent", 0);

        node = new XMP_Node(parent, "node", "value", 0);

        

        child1 = new XMP_Node(node, "child1", "value1", 0);

        child2 = new XMP_Node(node, "child2", "value2", 0);



        node->children.push_back(child1);

        node->children.push_back(child2);

    }



    void TearDown() override {

        delete node;

        delete parent;

    }



    XMP_Node* parent;

    XMP_Node* node;

    XMP_Node* child1;

    XMP_Node* child2;

};



TEST_F(XMP_NodeTest_1868, RemoveChildren_RemovesAllChildren_1868) {

    node->RemoveChildren();

    EXPECT_TRUE(node->children.empty());

}



TEST_F(XMP_NodeTest_1868, RemoveChildren_ChildrenDeleted_1868) {

    node->RemoveChildren();

    EXPECT_EQ(child1, nullptr);

    EXPECT_EQ(child2, nullptr);

}



TEST_F(XMP_NodeTest_1868, RemoveChildren_NoChildrenInitially_1868) {

    XMP_Node noChildrenNode(parent, "noChildren", 0);

    noChildrenNode.RemoveChildren();

    EXPECT_TRUE(noChildrenNode.children.empty());

}



TEST_F(XMP_NodeTest_1868, RemoveChildren_ParentPointerRemainsIntact_1868) {

    node->RemoveChildren();

    EXPECT_EQ(node->parent, parent);

}
