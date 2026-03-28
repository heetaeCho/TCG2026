#include <gtest/gtest.h>

#include "graph.h"

#include <string>



using namespace Node;



class NodeTest_31 : public ::testing::Test {

protected:

    std::string path = "/test/path";

    uint64_t slash_bits = 0;

    Node node;



    NodeTest_31() : node(path, slash_bits) {}

};



TEST_F(NodeTest_31, ResetState_SetsMTimeToNegativeOne_31) {

    node.ResetState();

    EXPECT_EQ(node.mtime(), -1);

}



TEST_F(NodeTest_31, ResetState_SetsExistsToUnknown_31) {

    node.ResetState();

    EXPECT_FALSE(node.status_known());

}



TEST_F(NodeTest_31, ResetState_SetsDirtyToFalse_31) {

    node.MarkDirty();

    node.ResetState();

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_31, MarkMissing_SetsExistsToMissing_31) {

    node.MarkMissing();

    EXPECT_EQ(node.exists(), false);

    EXPECT_TRUE(node.status_known());

}



TEST_F(NodeTest_31, Exists_ReturnsCorrectStatus_31) {

    node.MarkMissing();

    EXPECT_FALSE(node.exists());



    node.ResetState();

    EXPECT_FALSE(node.exists());

}



TEST_F(NodeTest_31, StatusKnown_ReturnsTrueAfterMarking_31) {

    node.MarkMissing();

    EXPECT_TRUE(node.status_known());



    node.ResetState();

    EXPECT_FALSE(node.status_known());

}



TEST_F(NodeTest_31, Path_ReturnsCorrectPath_31) {

    EXPECT_EQ(node.path(), path);

}



TEST_F(NodeTest_31, SlashBits_ReturnsCorrectSlashBits_31) {

    EXPECT_EQ(node.slash_bits(), slash_bits);

}



TEST_F(NodeTest_31, MTime_ReturnsInitialMTime_31) {

    EXPECT_EQ(node.mtime(), -1);

}



TEST_F(NodeTest_31, Dirty_ReturnsFalseInitially_31) {

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_31, SetDirty_ChangesDirtyStatus_31) {

    node.set_dirty(true);

    EXPECT_TRUE(node.dirty());



    node.set_dirty(false);

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_31, MarkDirty_SetsDirtyToTrue_31) {

    node.MarkDirty();

    EXPECT_TRUE(node.dirty());

}



TEST_F(NodeTest_31, DyndepPending_ReturnsFalseInitially_31) {

    EXPECT_FALSE(node.dyndep_pending());

}



TEST_F(NodeTest_31, SetDyndepPending_ChangesDyndepPendingStatus_31) {

    node.set_dyndep_pending(true);

    EXPECT_TRUE(node.dyndep_pending());



    node.set_dyndep_pending(false);

    EXPECT_FALSE(node.dyndep_pending());

}



TEST_F(NodeTest_31, InEdge_ReturnsNullInitially_31) {

    EXPECT_EQ(node.in_edge(), nullptr);

}



TEST_F(NodeTest_31, SetInEdge_ChangesInEdge_31) {

    Edge* edge = new Edge();

    node.set_in_edge(edge);

    EXPECT_EQ(node.in_edge(), edge);

    delete edge;

}



TEST_F(NodeTest_31, GeneratedByDepLoader_ReturnsTrueInitially_31) {

    EXPECT_TRUE(node.generated_by_dep_loader());

}



TEST_F(NodeTest_31, SetGeneratedByDepLoader_ChangesGeneratedStatus_31) {

    node.set_generated_by_dep_loader(false);

    EXPECT_FALSE(node.generated_by_dep_loader());



    node.set_generated_by_dep_loader(true);

    EXPECT_TRUE(node.generated_by_dep_loader());

}



TEST_F(NodeTest_31, Id_ReturnsNegativeOneInitially_31) {

    EXPECT_EQ(node.id(), -1);

}



TEST_F(NodeTest_31, SetId_ChangesId_31) {

    int id = 42;

    node.set_id(id);

    EXPECT_EQ(node.id(), id);

}



TEST_F(NodeTest_31, OutEdges_ReturnsEmptyVectorInitially_31) {

    EXPECT_TRUE(node.out_edges().empty());

}



TEST_F(NodeTest_31, AddOutEdge_AddsEdgeToOutEdges_31) {

    Edge* edge = new Edge();

    node.AddOutEdge(edge);

    EXPECT_EQ(node.out_edges().size(), 1);

    EXPECT_EQ(node.out_edges()[0], edge);

    delete edge;

}



TEST_F(NodeTest_31, ValidationOutEdges_ReturnsEmptyVectorInitially_31) {

    EXPECT_TRUE(node.validation_out_edges().empty());

}



TEST_F(NodeTest_31, AddValidationOutEdge_AddsEdgeToValidationOutEdges_31) {

    Edge* edge = new Edge();

    node.AddValidationOutEdge(edge);

    EXPECT_EQ(node.validation_out_edges().size(), 1);

    EXPECT_EQ(node.validation_out_edges()[0], edge);

    delete edge;

}
