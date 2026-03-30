#include <gtest/gtest.h>

#include "graph.h"

#include <string>



class NodeTest_44 : public ::testing::Test {

protected:

    Node node;



    NodeTest_44() : node("test_path", 123) {}

};



TEST_F(NodeTest_44, InEdge_ReturnsNullptrInitially_44) {

    EXPECT_EQ(node.in_edge(), nullptr);

}



TEST_F(NodeTest_44, SetInEdge_SetsCorrectly_44) {

    Edge mock_edge;

    node.set_in_edge(&mock_edge);

    EXPECT_EQ(node.in_edge(), &mock_edge);

}



TEST_F(NodeTest_44, Path_ReturnsCorrectPath_44) {

    EXPECT_EQ(node.path(), "test_path");

}



TEST_F(NodeTest_44, SlashBits_ReturnsCorrectValue_44) {

    EXPECT_EQ(node.slash_bits(), 123);

}



TEST_F(NodeTest_44, StatIfNecessary_DoesNotThrowException_44) {

    DiskInterface mock_disk_interface;

    std::string err;

    EXPECT_NO_THROW(node.StatIfNecessary(&mock_disk_interface, &err));

}



TEST_F(NodeTest_44, ResetState_ClearsDirtyFlag_44) {

    node.MarkDirty();

    node.ResetState();

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_44, MarkMissing_SetsExistsToFalse_44) {

    node.MarkMissing();

    EXPECT_FALSE(node.exists());

}



TEST_F(NodeTest_44, Exists_ReturnsCorrectValue_44) {

    node.set_in_edge(nullptr);

    EXPECT_FALSE(node.exists());

}



TEST_F(NodeTest_44, StatusKnown_ReturnsTrueAfterStatIfNecessary_44) {

    DiskInterface mock_disk_interface;

    std::string err;

    node.StatIfNecessary(&mock_disk_interface, &err);

    EXPECT_TRUE(node.status_known());

}



TEST_F(NodeTest_44, UpdatePhonyMtime_SetsCorrectTime_44) {

    TimeStamp new_mtime = 1234567890;

    node.UpdatePhonyMtime(new_mtime);

    EXPECT_EQ(node.mtime(), new_mtime);

}



TEST_F(NodeTest_44, Dirty_ReturnsTrueAfterMarkDirty_44) {

    node.MarkDirty();

    EXPECT_TRUE(node.dirty());

}



TEST_F(NodeTest_44, DyndepPending_ReturnsCorrectValue_44) {

    node.set_dyndep_pending(true);

    EXPECT_TRUE(node.dyndep_pending());

}



TEST_F(NodeTest_44, GeneratedByDepLoader_ReturnsCorrectValue_44) {

    node.set_generated_by_dep_loader(false);

    EXPECT_FALSE(node.generated_by_dep_loader());

}



TEST_F(NodeTest_44, Id_ReturnsCorrectId_44) {

    node.set_id(42);

    EXPECT_EQ(node.id(), 42);

}



TEST_F(NodeTest_44, AddOutEdge_AddsEdgeCorrectly_44) {

    Edge mock_edge;

    node.AddOutEdge(&mock_edge);

    const auto& out_edges = node.out_edges();

    EXPECT_EQ(out_edges.size(), 1);

    EXPECT_EQ(out_edges[0], &mock_edge);

}



TEST_F(NodeTest_44, AddValidationOutEdge_AddsEdgeCorrectly_44) {

    Edge mock_edge;

    node.AddValidationOutEdge(&mock_edge);

    const auto& validation_out_edges = node.validation_out_edges();

    EXPECT_EQ(validation_out_edges.size(), 1);

    EXPECT_EQ(validation_out_edges[0], &mock_edge);

}



TEST_F(NodeTest_44, PathDecanonicalized_ReturnsCorrectPath_44) {

    EXPECT_EQ(node.PathDecanonicalized(), Node::PathDecanonicalized("test_path", 123));

}
