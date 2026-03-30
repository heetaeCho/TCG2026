#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



using ::testing::Return;

using ::testing::_;



class NodeTest_48 : public ::testing::Test {

protected:

    NodeTest_48() : node_("test_path", 123) {}



    Node node_;

};



TEST_F(NodeTest_48, IdReturnsCorrectValue_48) {

    EXPECT_EQ(node_.id(), -1);

}



TEST_F(NodeTest_48, PathReturnsCorrectValue_48) {

    EXPECT_EQ(node_.path(), "test_path");

}



TEST_F(NodeTest_48, SlashBitsReturnsCorrectValue_48) {

    EXPECT_EQ(node_.slash_bits(), 123);

}



TEST_F(NodeTest_48, StatIfNecessaryCallsStatWhenNotKnown_48) {

    MockDiskInterface mock_disk_interface;

    std::string err;



    EXPECT_CALL(mock_disk_interface, Stat(_, _))

        .WillOnce(Return(true));



    node_.StatIfNecessary(&mock_disk_interface, &err);

}



TEST_F(NodeTest_48, StatIfNecessaryDoesNotCallStatWhenKnown_48) {

    MockDiskInterface mock_disk_interface;

    std::string err;



    node_.set_id(1); // Assuming setting id to a non-negative value marks status as known

    EXPECT_CALL(mock_disk_interface, Stat(_, _))

        .Times(0);



    node_.StatIfNecessary(&mock_disk_interface, &err);

}



TEST_F(NodeTest_48, UpdatePhonyMtimeSetsCorrectValue_48) {

    TimeStamp new_mtime = 12345;

    node_.UpdatePhonyMtime(new_mtime);

    EXPECT_EQ(node_.mtime(), new_mtime);

}



TEST_F(NodeTest_48, ResetStateResetsFlags_48) {

    node_.set_dirty(true);

    node_.set_dyndep_pending(true);

    node_.ResetState();

    EXPECT_FALSE(node_.dirty());

    EXPECT_FALSE(node_.dyndep_pending());

}



TEST_F(NodeTest_48, MarkMissingSetsExistsToFalse_48) {

    node_.MarkMissing();

    EXPECT_FALSE(node_.exists());

}



TEST_F(NodeTest_48, MarkDirtySetsDirtyFlagTrue_48) {

    node_.MarkDirty();

    EXPECT_TRUE(node_.dirty());

}



TEST_F(NodeTest_48, SettersUpdateValuesCorrectly_48) {

    Edge* mock_edge = new Edge(); // Assuming Edge is a simple struct/class

    node_.set_id(1);

    node_.set_in_edge(mock_edge);

    node_.set_generated_by_dep_loader(false);



    EXPECT_EQ(node_.id(), 1);

    EXPECT_EQ(node_.in_edge(), mock_edge);

    EXPECT_FALSE(node_.generated_by_dep_loader());

}



TEST_F(NodeTest_48, AddOutEdgeAddsToOutEdges_48) {

    Edge* edge = new Edge();

    node_.AddOutEdge(edge);

    EXPECT_EQ(node_.out_edges().size(), 1);

    EXPECT_EQ(node_.out_edges()[0], edge);

}



TEST_F(NodeTest_48, AddValidationOutEdgeAddsToValidationOutEdges_48) {

    Edge* edge = new Edge();

    node_.AddValidationOutEdge(edge);

    EXPECT_EQ(node_.validation_out_edges().size(), 1);

    EXPECT_EQ(node_.validation_out_edges()[0], edge);

}



// Mock class for DiskInterface

class MockDiskInterface : public DiskInterface {

public:

    MOCK_METHOD(bool, Stat, (const std::string&, std::string*), (override));

};


