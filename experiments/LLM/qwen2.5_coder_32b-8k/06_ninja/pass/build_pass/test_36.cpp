#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"

#include <string>



using namespace testing;



class NodeTest_36 : public ::testing::Test {

protected:

    NodeTest_36() : node("/path/to/node", 0) {}



    Node node;

};



TEST_F(NodeTest_36, PathDecanonicalized_ReturnsCorrectPath_36) {

    EXPECT_EQ(node.PathDecanonicalized(), "/path/to/node");

}



TEST_F(NodeTest_36, Path_ReturnsCorrectPath_36) {

    EXPECT_EQ(node.path(), "/path/to/node");

}



TEST_F(NodeTest_36, SlashBits_ReturnsInitializedValue_36) {

    EXPECT_EQ(node.slash_bits(), 0);

}



TEST_F(NodeTest_36, Exists_DefaultStatusUnknown_36) {

    EXPECT_FALSE(node.exists());

    EXPECT_FALSE(node.status_known());

}



TEST_F(NodeTest_36, Dirty_DefaultFalse_36) {

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_36, DyndepPending_DefaultFalse_36) {

    EXPECT_FALSE(node.dyndep_pending());

}



TEST_F(NodeTest_36, InEdge_DefaultNullptr_36) {

    EXPECT_EQ(node.in_edge(), nullptr);

}



TEST_F(NodeTest_36, OutEdges_DefaultEmpty_36) {

    EXPECT_TRUE(node.out_edges().empty());

}



TEST_F(NodeTest_36, ValidationOutEdges_DefaultEmpty_36) {

    EXPECT_TRUE(node.validation_out_edges().empty());

}



TEST_F(NodeTest_36, Id_DefaultMinusOne_36) {

    EXPECT_EQ(node.id(), -1);

}



TEST_F(NodeTest_36, GeneratedByDepLoader_DefaultTrue_36) {

    EXPECT_TRUE(node.generated_by_dep_loader());

}



TEST_F(NodeTest_36, MarkDirty_SetsDirtyFlag_36) {

    node.MarkDirty();

    EXPECT_TRUE(node.dirty());

}



TEST_F(NodeTest_36, SetDyndepPending_SetsPendingFlag_36) {

    node.set_dyndep_pending(true);

    EXPECT_TRUE(node.dyndep_pending());

}



TEST_F(NodeTest_36, SetInEdge_SetsInEdgePointer_36) {

    Edge mock_edge;

    node.set_in_edge(&mock_edge);

    EXPECT_EQ(node.in_edge(), &mock_edge);

}



TEST_F(NodeTest_36, AddOutEdge_AddsToOutEdges_36) {

    Edge mock_edge;

    node.AddOutEdge(&mock_edge);

    EXPECT_EQ(node.out_edges().size(), 1);

    EXPECT_EQ(node.out_edges()[0], &mock_edge);

}



TEST_F(NodeTest_36, AddValidationOutEdge_AddsToValidationOutEdges_36) {

    Edge mock_edge;

    node.AddValidationOutEdge(&mock_edge);

    EXPECT_EQ(node.validation_out_edges().size(), 1);

    EXPECT_EQ(node.validation_out_edges()[0], &mock_edge);

}



TEST_F(NodeTest_36, SetId_SetsNodeId_36) {

    node.set_id(42);

    EXPECT_EQ(node.id(), 42);

}



TEST_F(NodeTest_36, SetGeneratedByDepLoader_SetsFlag_36) {

    node.set_generated_by_dep_loader(false);

    EXPECT_FALSE(node.generated_by_dep_loader());

}
