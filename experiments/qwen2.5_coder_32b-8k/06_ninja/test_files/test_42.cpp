#include <gtest/gtest.h>

#include "graph.h"

#include <string>



class NodeTest_42 : public ::testing::Test {

protected:

    NodeTest_42() : node("test_path", 0) {}



    Node node;

};



TEST_F(NodeTest_42, DyndepPendingInitiallyFalse_42) {

    EXPECT_FALSE(node.dyndep_pending());

}



TEST_F(NodeTest_42, SetDyndepPendingTrueAndGet_42) {

    node.set_dyndep_pending(true);

    EXPECT_TRUE(node.dyndep_pending());

}



TEST_F(NodeTest_42, SetDyndepPendingFalseAndGet_42) {

    node.set_dyndep_pending(false);

    EXPECT_FALSE(node.dyndep_pending());

}



TEST_F(NodeTest_42, PathReturnsCorrectPath_42) {

    EXPECT_EQ("test_path", node.path());

}



TEST_F(NodeTest_42, SlashBitsReturnsCorrectValue_42) {

    EXPECT_EQ(0, node.slash_bits());

}



TEST_F(NodeTest_42, ExistsInitiallyUnknown_42) {

    EXPECT_FALSE(node.exists());

    EXPECT_FALSE(node.status_known());

}



TEST_F(NodeTest_42, MarkMissingSetsExistsToFalse_42) {

    node.MarkMissing();

    EXPECT_FALSE(node.exists());

    EXPECT_TRUE(node.status_known());

}



TEST_F(NodeTest_42, DirtyInitiallyFalse_42) {

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_42, SetDirtyTrueAndGet_42) {

    node.set_dirty(true);

    EXPECT_TRUE(node.dirty());

}



TEST_F(NodeTest_42, MarkDirtySetsDirtyToTrue_42) {

    node.MarkDirty();

    EXPECT_TRUE(node.dirty());

}



TEST_F(NodeTest_42, GeneratedByDepLoaderInitiallyTrue_42) {

    EXPECT_TRUE(node.generated_by_dep_loader());

}



TEST_F(NodeTest_42, SetGeneratedByDepLoaderFalseAndGet_42) {

    node.set_generated_by_dep_loader(false);

    EXPECT_FALSE(node.generated_by_dep_loader());

}



TEST_F(NodeTest_42, InEdgeInitiallyNull_42) {

    EXPECT_EQ(nullptr, node.in_edge());

}



TEST_F(NodeTest_42, SetInEdgeAndGet_42) {

    Edge mock_edge;

    node.set_in_edge(&mock_edge);

    EXPECT_EQ(&mock_edge, node.in_edge());

}



TEST_F(NodeTest_42, OutEdgesInitiallyEmpty_42) {

    EXPECT_TRUE(node.out_edges().empty());

}



TEST_F(NodeTest_42, AddOutEdgeAndGet_42) {

    Edge mock_edge;

    node.AddOutEdge(&mock_edge);

    EXPECT_EQ(1, node.out_edges().size());

    EXPECT_EQ(&mock_edge, node.out_edges()[0]);

}



TEST_F(NodeTest_42, ValidationOutEdgesInitiallyEmpty_42) {

    EXPECT_TRUE(node.validation_out_edges().empty());

}



TEST_F(NodeTest_42, AddValidationOutEdgeAndGet_42) {

    Edge mock_edge;

    node.AddValidationOutEdge(&mock_edge);

    EXPECT_EQ(1, node.validation_out_edges().size());

    EXPECT_EQ(&mock_edge, node.validation_out_edges()[0]);

}



TEST_F(NodeTest_42, IdInitiallyNegativeOne_42) {

    EXPECT_EQ(-1, node.id());

}



TEST_F(NodeTest_42, SetIdAndGet_42) {

    node.set_id(1);

    EXPECT_EQ(1, node.id());

}
