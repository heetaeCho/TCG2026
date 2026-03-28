#include <gtest/gtest.h>

#include "graph.h"

#include "disk_interface.h"  // Assuming DiskInterface is defined here



class NodeTest_35 : public ::testing::Test {

protected:

    Node node_;

    std::string test_path = "/test/path";

    uint64_t test_slash_bits = 123;



    NodeTest_35() : node_(test_path, test_slash_bits) {}

};



TEST_F(NodeTest_35, PathReturnsCorrectValue_35) {

    EXPECT_EQ(node_.path(), test_path);

}



TEST_F(NodeTest_35, SlashBitsReturnsCorrectValue_35) {

    EXPECT_EQ(node_.slash_bits(), test_slash_bits);

}



TEST_F(NodeTest_35, StatIfNecessaryCallsStat_35) {

    MockDiskInterface mock_disk_interface;

    std::string err;



    EXPECT_CALL(mock_disk_interface, Stat(test_path, _))

        .WillOnce(::testing::Return(true));



    bool result = node_.StatIfNecessary(&mock_disk_interface, &err);

    EXPECT_TRUE(result);

}



TEST_F(NodeTest_35, StatIfNecessaryHandlesError_35) {

    MockDiskInterface mock_disk_interface;

    std::string err;



    EXPECT_CALL(mock_disk_interface, Stat(test_path, _))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<1>("Stat failed"),

            ::testing::Return(false)));



    bool result = node_.StatIfNecessary(&mock_disk_interface, &err);

    EXPECT_FALSE(result);

    EXPECT_EQ(err, "Stat failed");

}



TEST_F(NodeTest_35, UpdatePhonyMtimeSetsCorrectValue_35) {

    TimeStamp test_mtime = 12345;

    node_.UpdatePhonyMtime(test_mtime);

    EXPECT_EQ(node_.mtime(), test_mtime);

}



TEST_F(NodeTest_35, ResetStateClearsFlags_35) {

    node_.set_dirty(true);

    node_.MarkMissing();

    node_.ResetState();



    EXPECT_FALSE(node_.dirty());

    EXPECT_FALSE(node_.exists());

    EXPECT_TRUE(node_.status_known());

}



TEST_F(NodeTest_35, MarkDirtySetsFlagToTrue_35) {

    node_.MarkDirty();

    EXPECT_TRUE(node_.dirty());

}



TEST_F(NodeTest_35, SetDirtyUpdatesFlagCorrectly_35) {

    node_.set_dirty(false);

    EXPECT_FALSE(node_.dirty());



    node_.set_dirty(true);

    EXPECT_TRUE(node_.dirty());

}



TEST_F(NodeTest_35, DyndepPendingReturnsInitialValue_35) {

    EXPECT_FALSE(node_.dyndep_pending());

}



TEST_F(NodeTest_35, SetDyndepPendingUpdatesFlagCorrectly_35) {

    node_.set_dyndep_pending(true);

    EXPECT_TRUE(node_.dyndep_pending());



    node_.set_dyndep_pending(false);

    EXPECT_FALSE(node_.dyndep_pending());

}



TEST_F(NodeTest_35, InEdgeReturnsInitialValue_35) {

    EXPECT_EQ(node_.in_edge(), nullptr);

}



TEST_F(NodeTest_35, SetInEdgeUpdatesPointerCorrectly_35) {

    Edge test_edge;

    node_.set_in_edge(&test_edge);

    EXPECT_EQ(node_.in_edge(), &test_edge);

}



TEST_F(NodeTest_35, GeneratedByDepLoaderReturnsInitialValue_35) {

    EXPECT_TRUE(node_.generated_by_dep_loader());

}



TEST_F(NodeTest_35, SetGeneratedByDepLoaderUpdatesFlagCorrectly_35) {

    node_.set_generated_by_dep_loader(false);

    EXPECT_FALSE(node_.generated_by_dep_loader());



    node_.set_generated_by_dep_loader(true);

    EXPECT_TRUE(node_.generated_by_dep_loader());

}



TEST_F(NodeTest_35, IdReturnsInitialValue_35) {

    EXPECT_EQ(node_.id(), -1);

}



TEST_F(NodeTest_35, SetIdUpdatesValueCorrectly_35) {

    int test_id = 42;

    node_.set_id(test_id);

    EXPECT_EQ(node_.id(), test_id);

}



TEST_F(NodeTest_35, OutEdgesInitiallyEmpty_35) {

    EXPECT_TRUE(node_.out_edges().empty());

}



TEST_F(NodeTest_35, AddOutEdgeAddsEdgeCorrectly_35) {

    Edge edge;

    node_.AddOutEdge(&edge);

    EXPECT_EQ(node_.out_edges().size(), 1);

    EXPECT_EQ(node_.out_edges()[0], &edge);

}



TEST_F(NodeTest_35, ValidationOutEdgesInitiallyEmpty_35) {

    EXPECT_TRUE(node_.validation_out_edges().empty());

}



TEST_F(NodeTest_35, AddValidationOutEdgeAddsEdgeCorrectly_35) {

    Edge edge;

    node_.AddValidationOutEdge(&edge);

    EXPECT_EQ(node_.validation_out_edges().size(), 1);

    EXPECT_EQ(node_.validation_out_edges()[0], &edge);

}
