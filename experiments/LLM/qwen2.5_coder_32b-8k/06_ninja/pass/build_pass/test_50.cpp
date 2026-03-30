#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



class NodeTest_50 : public ::testing::Test {

protected:

    Node node;



    NodeTest_50() : node("test_path", 123) {}

};



TEST_F(NodeTest_50, OutEdgesInitiallyEmpty_50) {

    EXPECT_TRUE(node.out_edges().empty());

}



TEST_F(NodeTest_50, AddOutEdgeIncreasesCount_50) {

    Edge* edge = new Edge();

    node.AddOutEdge(edge);

    EXPECT_EQ(node.out_edges().size(), 1);

    delete edge;

}



TEST_F(NodeTest_50, MultipleAddOutEdgesIncreaseCount_50) {

    Edge* edge1 = new Edge();

    Edge* edge2 = new Edge();

    node.AddOutEdge(edge1);

    node.AddOutEdge(edge2);

    EXPECT_EQ(node.out_edges().size(), 2);

    delete edge1;

    delete edge2;

}



TEST_F(NodeTest_50, OutEdgesContainAddedEdges_50) {

    Edge* edge = new Edge();

    node.AddOutEdge(edge);

    EXPECT_TRUE(std::find(node.out_edges().begin(), node.out_edges().end(), edge) != node.out_edges().end());

    delete edge;

}



TEST_F(NodeTest_50, ValidationOutEdgesInitiallyEmpty_50) {

    EXPECT_TRUE(node.validation_out_edges().empty());

}



TEST_F(NodeTest_50, AddValidationOutEdgeIncreasesCount_50) {

    Edge* edge = new Edge();

    node.AddValidationOutEdge(edge);

    EXPECT_EQ(node.validation_out_edges().size(), 1);

    delete edge;

}



TEST_F(NodeTest_50, MultipleAddValidationOutEdgesIncreaseCount_50) {

    Edge* edge1 = new Edge();

    Edge* edge2 = new Edge();

    node.AddValidationOutEdge(edge1);

    node.AddValidationOutEdge(edge2);

    EXPECT_EQ(node.validation_out_edges().size(), 2);

    delete edge1;

    delete edge2;

}



TEST_F(NodeTest_50, ValidationOutEdgesContainAddedEdges_50) {

    Edge* edge = new Edge();

    node.AddValidationOutEdge(edge);

    EXPECT_TRUE(std::find(node.validation_out_edges().begin(), node.validation_out_edges().end(), edge) != node.validation_out_edges().end());

    delete edge;

}



TEST_F(NodeTest_50, PathReturnsCorrectPath_50) {

    EXPECT_EQ(node.path(), "test_path");

}



TEST_F(NodeTest_50, SlashBitsReturnsCorrectValue_50) {

    EXPECT_EQ(node.slash_bits(), 123);

}



TEST_F(NodeTest_50, DefaultDirtyStateIsFalse_50) {

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_50, SetDirtyChangesDirtyState_50) {

    node.set_dirty(true);

    EXPECT_TRUE(node.dirty());

}



TEST_F(NodeTest_50, MarkDirtySetsDirtyToTrue_50) {

    node.MarkDirty();

    EXPECT_TRUE(node.dirty());

}
