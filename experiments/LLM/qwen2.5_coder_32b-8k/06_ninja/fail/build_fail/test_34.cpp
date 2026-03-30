#include <gtest/gtest.h>

#include "graph.h"

#include <string>



class NodeTest : public ::testing::Test {

protected:

    Node node;



    NodeTest() : node("test_path", 123) {}

};



TEST_F(NodeTest_34, StatusKnownInitiallyFalse_34) {

    EXPECT_FALSE(node.status_known());

}



TEST_F(NodeTest_34, StatusKnownAfterStatExists_34) {

    DiskInterface mock_disk_interface;

    std::string error_message;



    // Assuming Stat returns true and sets exists_ to ExistenceStatusExists

    EXPECT_CALL(mock_disk_interface, Stat(&node, &error_message))

        .WillOnce(::testing::Return(true));



    bool result = node.Stat(&mock_disk_interface, &error_message);

    EXPECT_TRUE(result);

    EXPECT_TRUE(node.status_known());

}



TEST_F(NodeTest_34, StatusKnownAfterStatMissing_34) {

    DiskInterface mock_disk_interface;

    std::string error_message;



    // Assuming Stat returns false and sets exists_ to ExistenceStatusMissing

    EXPECT_CALL(mock_disk_interface, Stat(&node, &error_message))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<1>("File not found"),

            ::testing::Return(false)));



    bool result = node.Stat(&mock_disk_interface, &error_message);

    EXPECT_FALSE(result);

    EXPECT_TRUE(node.status_known());

}



TEST_F(NodeTest_34, StatIfNecessaryCallsStatWhenStatusUnknown_34) {

    DiskInterface mock_disk_interface;

    std::string error_message;



    EXPECT_CALL(mock_disk_interface, Stat(&node, &error_message))

        .WillOnce(::testing::Return(true));



    node.StatIfNecessary(&mock_disk_interface, &error_message);

    EXPECT_TRUE(node.status_known());

}



TEST_F(NodeTest_34, StatIfNecessaryDoesNotCallStatWhenStatusKnown_34) {

    DiskInterface mock_disk_interface;

    std::string error_message;



    // Initially mark status as known

    node.MarkMissing();



    EXPECT_CALL(mock_disk_interface, Stat(&node, &error_message))

        .Times(0);



    node.StatIfNecessary(&mock_disk_interface, &error_message);

    EXPECT_TRUE(node.status_known());

}



TEST_F(NodeTest_34, ResetStateResetsAllFlags_34) {

    // Set some flags to non-default values

    node.MarkDirty();

    node.set_dyndep_pending(true);



    node.ResetState();



    EXPECT_FALSE(node.dirty());

    EXPECT_FALSE(node.dyndep_pending());

}



TEST_F(NodeTest_34, MarkMissingSetsStatusKnownAndExistenceStatusMissing_34) {

    node.MarkMissing();

    EXPECT_TRUE(node.status_known());

    EXPECT_EQ(node.exists(), false);

}



TEST_F(NodeTest_34, ExistsInitiallyUnknown_34) {

    EXPECT_FALSE(node.exists());

}



TEST_F(NodeTest_34, SetIdAndGetIdConsistent_34) {

    int test_id = 10;

    node.set_id(test_id);

    EXPECT_EQ(node.id(), test_id);

}



TEST_F(NodeTest_34, AddOutEdgeAndRetrieve_34) {

    Edge* mock_edge = new Edge();

    node.AddOutEdge(mock_edge);



    const std::vector<Edge*>& out_edges = node.out_edges();

    EXPECT_EQ(out_edges.size(), 1);

    EXPECT_EQ(out_edges[0], mock_edge);



    delete mock_edge;

}



TEST_F(NodeTest_34, AddValidationOutEdgeAndRetrieve_34) {

    Edge* mock_edge = new Edge();

    node.AddValidationOutEdge(mock_edge);



    const std::vector<Edge*>& validation_out_edges = node.validation_out_edges();

    EXPECT_EQ(validation_out_edges.size(), 1);

    EXPECT_EQ(validation_out_edges[0], mock_edge);



    delete mock_edge;

}



TEST_F(NodeTest_34, PathDecanonicalizedReturnsPath_34) {

    EXPECT_EQ(node.PathDecanonicalized(), "test_path");

}
