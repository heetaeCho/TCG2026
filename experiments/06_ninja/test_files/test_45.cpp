#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



using namespace testing;



class NodeTest_45 : public Test {

protected:

    Node* node;

    Edge* edge;



    void SetUp() override {

        node = new Node("test_path", 0);

        edge = new Edge();

    }



    void TearDown() override {

        delete node;

        delete edge;

    }

};



TEST_F(NodeTest_45, SetInEdge_NormalOperation_45) {

    node->set_in_edge(edge);

    EXPECT_EQ(node->in_edge(), edge);

}



TEST_F(NodeTest_45, SetInEdge_BoundaryConditionNull_45) {

    node->set_in_edge(nullptr);

    EXPECT_EQ(node->in_edge(), nullptr);

}



TEST_F(NodeTest_45, Path_ReturnsCorrectPath_45) {

    EXPECT_EQ(node->path(), "test_path");

}



TEST_F(NodeTest_45, SlashBits_ReturnsCorrectValue_45) {

    EXPECT_EQ(node->slash_bits(), 0);

}



TEST_F(NodeTest_45, DefaultInEdge_IsNullptr_45) {

    EXPECT_EQ(node->in_edge(), nullptr);

}
