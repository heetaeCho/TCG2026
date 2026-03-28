#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



using ::testing::Return;

using ::testing::_;



class NodeTest_46 : public ::testing::Test {

protected:

    Node node;



    NodeTest_46() : node("test_path", 0) {}

};



TEST_F(NodeTest_46, Path_ReturnsCorrectPath_46) {

    EXPECT_EQ(node.path(), "test_path");

}



TEST_F(NodeTest_46, SlashBits_ReturnsCorrectValue_46) {

    EXPECT_EQ(node.slash_bits(), 0);

}



TEST_F(NodeTest_46, GeneratedByDepLoader_ReturnsTrueInitially_46) {

    EXPECT_TRUE(node.generated_by_dep_loader());

}



TEST_F(NodeTest_46, SetGeneratedByDepLoader_ChangesValueCorrectly_46) {

    node.set_generated_by_dep_loader(false);

    EXPECT_FALSE(node.generated_by_dep_loader());



    node.set_generated_by_dep_loader(true);

    EXPECT_TRUE(node.generated_by_dep_loader());

}



TEST_F(NodeTest_46, Dirty_ReturnsFalseInitially_46) {

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_46, SetDirty_ChangesValueCorrectly_46) {

    node.set_dirty(true);

    EXPECT_TRUE(node.dirty());



    node.set_dirty(false);

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_46, MarkDirty_SetsDirtyTrue_46) {

    node.MarkDirty();

    EXPECT_TRUE(node.dirty());

}



TEST_F(NodeTest_46, DyndepPending_ReturnsFalseInitially_46) {

    EXPECT_FALSE(node.dyndep_pending());

}



TEST_F(NodeTest_46, SetDyndepPending_ChangesValueCorrectly_46) {

    node.set_dyndep_pending(true);

    EXPECT_TRUE(node.dyndep_pending());



    node.set_dyndep_pending(false);

    EXPECT_FALSE(node.dyndep_pending());

}



TEST_F(NodeTest_46, InEdge_ReturnsNullptrInitially_46) {

    EXPECT_EQ(node.in_edge(), nullptr);

}



TEST_F(NodeTest_46, SetInEdge_SetsValueCorrectly_46) {

    Edge* mockEdge = new Edge();

    node.set_in_edge(mockEdge);

    EXPECT_EQ(node.in_edge(), mockEdge);



    delete mockEdge;

}



TEST_F(NodeTest_46, OutEdges_ReturnsEmptyInitially_46) {

    EXPECT_TRUE(node.out_edges().empty());

}



TEST_F(NodeTest_46, AddOutEdge_AddsEdgeCorrectly_46) {

    Edge* mockEdge = new Edge();

    node.AddOutEdge(mockEdge);

    EXPECT_EQ(node.out_edges().size(), 1);

    EXPECT_EQ(node.out_edges()[0], mockEdge);



    delete mockEdge;

}



TEST_F(NodeTest_46, ValidationOutEdges_ReturnsEmptyInitially_46) {

    EXPECT_TRUE(node.validation_out_edges().empty());

}



TEST_F(NodeTest_46, AddValidationOutEdge_AddsEdgeCorrectly_46) {

    Edge* mockEdge = new Edge();

    node.AddValidationOutEdge(mockEdge);

    EXPECT_EQ(node.validation_out_edges().size(), 1);

    EXPECT_EQ(node.validation_out_edges()[0], mockEdge);



    delete mockEdge;

}



TEST_F(NodeTest_46, Id_ReturnsNegativeOneInitially_46) {

    EXPECT_EQ(node.id(), -1);

}



TEST_F(NodeTest_46, SetId_SetsValueCorrectly_46) {

    node.set_id(5);

    EXPECT_EQ(node.id(), 5);



    node.set_id(-2);

    EXPECT_EQ(node.id(), -2);

}



// Mocking DiskInterface for testing Stat and StatIfNecessary

class MockDiskInterface : public DiskInterface {

public:

    MOCK_METHOD3(Stat, bool(const std::string&, TimeStamp*, std::string*));

};



TEST_F(NodeTest_46, Stat_CallsDiskInterfaceStat_46) {

    MockDiskInterface mock_disk_interface;

    std::string err;



    EXPECT_CALL(mock_disk_interface, Stat("test_path", _, _))

        .WillOnce(Return(true));



    EXPECT_TRUE(node.Stat(&mock_disk_interface, &err));

}



TEST_F(NodeTest_46, StatIfNecessary_CallsStatWhenNotKnown_46) {

    MockDiskInterface mock_disk_interface;

    std::string err;



    EXPECT_CALL(mock_disk_interface, Stat("test_path", _, _))

        .WillOnce(Return(true));



    EXPECT_TRUE(node.StatIfNecessary(&mock_disk_interface, &err));

}



TEST_F(NodeTest_46, StatIfNecessary_DoesNotCallStatWhenKnown_46) {

    MockDiskInterface mock_disk_interface;

    std::string err;



    node.UpdatePhonyMtime(10);

    EXPECT_CALL(mock_disk_interface, Stat(_, _, _)).Times(0);



    EXPECT_TRUE(node.StatIfNecessary(&mock_disk_interface, &err));

}



TEST_F(NodeTest_46, ResetState_ResetsCorrectly_46) {

    node.set_dirty(true);

    node.set_dyndep_pending(true);

    node.UpdatePhonyMtime(10);

    Edge* mockEdge = new Edge();

    node.AddOutEdge(mockEdge);



    node.ResetState();



    EXPECT_FALSE(node.dirty());

    EXPECT_FALSE(node.dyndep_pending());

    EXPECT_EQ(node.mtime(), -1);

    EXPECT_TRUE(node.out_edges().empty());



    delete mockEdge;

}



TEST_F(NodeTest_46, MarkMissing_SetsCorrectValues_46) {

    node.MarkMissing();

    EXPECT_FALSE(node.exists());

    EXPECT_TRUE(node.status_known());

}



TEST_F(NodeTest_46, Exists_ReturnsFalseInitially_46) {

    EXPECT_FALSE(node.exists());

}



TEST_F(NodeTest_46, StatusKnown_ReturnsFalseInitially_46) {

    EXPECT_FALSE(node.status_known());

}



TEST_F(NodeTest_46, Mtime_ReturnsNegativeOneInitially_46) {

    EXPECT_EQ(node.mtime(), -1);

}



TEST_F(NodeTest_46, UpdatePhonyMtime_SetsMtimeCorrectly_46) {

    node.UpdatePhonyMtime(20);

    EXPECT_EQ(node.mtime(), 20);

}
