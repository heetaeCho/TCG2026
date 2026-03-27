#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"

#include "disk_interface.h"  // Assuming DiskInterface is defined in this header



using ::testing::Return;

using ::testing::StrEq;



class NodeTest_38 : public ::testing::Test {

protected:

    Node node_;

    MockDiskInterface mock_disk_;



    NodeTest_38() : node_("test_path", 12345) {}

};



TEST_F(NodeTest_38, Path_ReturnsCorrectPath_38) {

    EXPECT_EQ(node_.path(), "test_path");

}



TEST_F(NodeTest_38, SlashBits_ReturnsCorrectValue_38) {

    EXPECT_EQ(node_.slash_bits(), 12345);

}



TEST_F(NodeTest_38, Mtime_InitiallyReturnsNegativeOne_38) {

    EXPECT_EQ(node_.mtime(), static_cast<TimeStamp>(-1));

}



TEST_F(NodeTest_38, Exists_StatusInitiallyUnknown_38) {

    EXPECT_FALSE(node_.exists());

    EXPECT_FALSE(node_.status_known());

}



TEST_F(NodeTest_38, Stat_WithSuccessfulDiskInterfaceCall_ReturnsTrueAndUpdatesMtime_38) {

    TimeStamp test_mtime = 123456789;

    EXPECT_CALL(mock_disk_, Stat(StrEq("test_path"), _))

        .WillOnce(DoAll(SetArgReferee<1>(test_mtime), Return(true)));



    std::string err;

    bool result = node_.Stat(&mock_disk_, &err);

    

    EXPECT_TRUE(result);

    EXPECT_EQ(node_.mtime(), test_mtime);

    EXPECT_TRUE(node_.exists());

    EXPECT_TRUE(node_.status_known());

}



TEST_F(NodeTest_38, Stat_WithFailedDiskInterfaceCall_ReturnsFalseAndDoesNotUpdateMtime_38) {

    std::string error_message = "Stat failed";

    EXPECT_CALL(mock_disk_, Stat(StrEq("test_path"), _))

        .WillOnce(DoAll(SetArgReferee<1>(error_message), Return(false)));



    std::string err;

    bool result = node_.Stat(&mock_disk_, &err);

    

    EXPECT_FALSE(result);

    EXPECT_EQ(err, error_message);

    EXPECT_EQ(node_.mtime(), static_cast<TimeStamp>(-1));

    EXPECT_FALSE(node_.exists());

    EXPECT_TRUE(node_.status_known());

}



TEST_F(NodeTest_38, UpdatePhonyMtime_UpdatesMtimeToProvidedValue_38) {

    TimeStamp new_mtime = 987654321;

    node_.UpdatePhonyMtime(new_mtime);

    EXPECT_EQ(node_.mtime(), new_mtime);

}



TEST_F(NodeTest_38, ResetState_ResetsAllFlagsAndClearsVectors_38) {

    node_.MarkMissing();

    node_.set_dirty(true);

    node_.set_dyndep_pending(true);



    std::vector<Edge*> edges = {new Edge(), new Edge()};

    node_.AddOutEdge(edges[0]);

    node_.AddValidationOutEdge(edges[1]);



    node_.ResetState();



    EXPECT_FALSE(node_.exists());

    EXPECT_TRUE(node_.status_known());

    EXPECT_FALSE(node_.dirty());

    EXPECT_FALSE(node_.dyndep_pending());

    EXPECT_EQ(node_.out_edges().size(), 0);

    EXPECT_EQ(node_.validation_out_edges().size(), 0);



    delete edges[0];

    delete edges[1];

}



TEST_F(NodeTest_38, MarkMissing_SetsExistsToFalseAndStatusKnownToTrue_38) {

    node_.MarkMissing();

    EXPECT_FALSE(node_.exists());

    EXPECT_TRUE(node_.status_known());

}



TEST_F(NodeTest_38, StatIfNecessary_WithExistingFile_DoesNotCallStat_38) {

    node_.set_id(1);

    node_.set_dirty(false);

    node_.MarkDirty();  // Mark it dirty first

    node_.ResetState();

    EXPECT_CALL(mock_disk_, Stat(_, _)).Times(0);



    std::string err;

    bool result = node_.StatIfNecessary(&mock_disk_, &err);

    

    EXPECT_FALSE(result);  // Should return false as no stat call was made and mtime is -1

}



TEST_F(NodeTest_38, StatIfNecessary_WithNonExistingFile_CallsStatOnceAndUpdatesMtime_38) {

    node_.set_id(1);

    node_.set_dirty(false);



    TimeStamp test_mtime = 123456789;

    EXPECT_CALL(mock_disk_, Stat(StrEq("test_path"), _))

        .WillOnce(DoAll(SetArgReferee<1>(test_mtime), Return(true)));



    std::string err;

    bool result = node_.StatIfNecessary(&mock_disk_, &err);

    

    EXPECT_TRUE(result);

    EXPECT_EQ(node_.mtime(), test_mtime);

    EXPECT_TRUE(node_.exists());

    EXPECT_TRUE(node_.status_known());

}



TEST_F(NodeTest_38, StatIfNecessary_WithDirtyFile_CallsStatOnceAndUpdatesMtime_38) {

    node_.set_id(1);

    node_.MarkDirty();



    TimeStamp test_mtime = 123456789;

    EXPECT_CALL(mock_disk_, Stat(StrEq("test_path"), _))

        .WillOnce(DoAll(SetArgReferee<1>(test_mtime), Return(true)));



    std::string err;

    bool result = node_.StatIfNecessary(&mock_disk_, &err);

    

    EXPECT_TRUE(result);

    EXPECT_EQ(node_.mtime(), test_mtime);

    EXPECT_TRUE(node_.exists());

    EXPECT_TRUE(node_.status_known());

}



TEST_F(NodeTest_38, PathDecanonicalized_ReturnsPathAsIs_38) {

    EXPECT_EQ(node_.PathDecanonicalized(), "test_path");

}



TEST_F(NodeTest_38, InEdge_SetAndGetWorksCorrectly_38) {

    Edge* test_edge = new Edge();

    node_.set_in_edge(test_edge);

    EXPECT_EQ(node_.in_edge(), test_edge);



    delete test_edge;

}



TEST_F(NodeTest_38, OutEdges_AddMultipleAndGetAll_38) {

    Edge* edge1 = new Edge();

    Edge* edge2 = new Edge();



    node_.AddOutEdge(edge1);

    node_.AddOutEdge(edge2);



    const std::vector<Edge*>& out_edges = node_.out_edges();

    EXPECT_EQ(out_edges.size(), 2);

    EXPECT_EQ(out_edges[0], edge1);

    EXPECT_EQ(out_edges[1], edge2);



    delete edge1;

    delete edge2;

}



TEST_F(NodeTest_38, ValidationOutEdges_AddMultipleAndGetAll_38) {

    Edge* edge1 = new Edge();

    Edge* edge2 = new Edge();



    node_.AddValidationOutEdge(edge1);

    node_.AddValidationOutEdge(edge2);



    const std::vector<Edge*>& validation_out_edges = node_.validation_out_edges();

    EXPECT_EQ(validation_out_edges.size(), 2);

    EXPECT_EQ(validation_out_edges[0], edge1);

    EXPECT_EQ(validation_out_edges[1], edge2);



    delete edge1;

    delete edge2;

}



TEST_F(NodeTest_38, GeneratedByDepLoader_SetAndGetWorksCorrectly_38) {

    node_.set_generated_by_dep_loader(false);

    EXPECT_FALSE(node_.generated_by_dep_loader());

    node_.set_generated_by_dep_loader(true);

    EXPECT_TRUE(node_.generated_by_dep_loader());

}



TEST_F(NodeTest_38, DyndepPending_SetAndGetWorksCorrectly_38) {

    node_.set_dyndep_pending(false);

    EXPECT_FALSE(node_.dyndep_pending());

    node_.set_dyndep_pending(true);

    EXPECT_TRUE(node_.dyndep_pending());

}
