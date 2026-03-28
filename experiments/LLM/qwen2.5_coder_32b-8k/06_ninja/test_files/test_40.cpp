#include <gtest/gtest.h>

#include "graph.h"



class NodeTest_40 : public ::testing::Test {

protected:

    void SetUp() override {

        node = new Node("test_path", 123);

    }



    void TearDown() override {

        delete node;

    }



    Node* node;

};



TEST_F(NodeTest_40, SetDirtyChangesState_40) {

    EXPECT_FALSE(node->dirty());

    node->set_dirty(true);

    EXPECT_TRUE(node->dirty());



    node->set_dirty(false);

    EXPECT_FALSE(node->dirty());

}



TEST_F(NodeTest_40, DefaultDirtyState_40) {

    Node default_node("default_path", 456);

    EXPECT_FALSE(default_node.dirty());

}



TEST_F(NodeTest_40, MarkDirtySetsTrue_40) {

    node->set_dirty(false);

    node->MarkDirty();

    EXPECT_TRUE(node->dirty());

}
