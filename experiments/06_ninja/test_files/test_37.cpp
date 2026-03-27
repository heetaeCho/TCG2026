#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



using ::testing::_;

using ::testing::Return;

using ::testing::StrEq;



class NodeTest_37 : public ::testing::Test {

protected:

    DiskInterface* mock_disk_interface;

    std::string error_message;



    void SetUp() override {

        mock_disk_interface = new MockDiskInterface();

    }



    void TearDown() override {

        delete mock_disk_interface;

    }

};



TEST_F(NodeTest_37, SlashBits_ReturnsCorrectValue_37) {

    Node node("test_path", 123);

    EXPECT_EQ(node.slash_bits(), 123);

}



TEST_F(NodeTest_37, Path_ReturnsCorrectPath_37) {

    Node node("test_path", 0);

    EXPECT_EQ(node.path(), "test_path");

}



TEST_F(NodeTest_37, StatIfNecessary_CallsDiskInterfaceStat_37) {

    EXPECT_CALL(*mock_disk_interface, Stat(StrEq("test_path"), _))

        .WillOnce(Return(true));



    Node node("test_path", 0);

    bool result = node.StatIfNecessary(mock_disk_interface, &error_message);



    EXPECT_TRUE(result);

}



TEST_F(NodeTest_37, StatIfNecessary_ReturnsFalseOnDiskInterfaceFailure_37) {

    EXPECT_CALL(*mock_disk_interface, Stat(StrEq("test_path"), _))

        .WillOnce(Return(false));



    Node node("test_path", 0);

    bool result = node.StatIfNecessary(mock_disk_interface, &error_message);



    EXPECT_FALSE(result);

}



TEST_F(NodeTest_37, ResetState_ClearsDirtyFlag_37) {

    Node node("test_path", 0);

    node.MarkDirty();

    node.ResetState();



    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_37, MarkMissing_SetsExistsToFalse_37) {

    Node node("test_path", 0);

    node.MarkMissing();



    EXPECT_FALSE(node.exists());

}



TEST_F(NodeTest_37, UpdatePhonyMtime_SetsCorrectMTime_37) {

    TimeStamp mtime = 123456;

    Node node("test_path", 0);

    node.UpdatePhonyMtime(mtime);



    EXPECT_EQ(node.mtime(), mtime);

}



TEST_F(NodeTest_37, PathDecanonicalized_ReturnsCorrectPath_37) {

    Node node("/path/to/test", 1);

    std::string decanonicalized = node.PathDecanonicalized();



    EXPECT_EQ(decanonicalized, "path/to/test");

}



TEST_F(NodeTest_37, SettersAndGetters_WorkAsExpected_37) {

    Node node("test_path", 0);



    Edge mock_edge;

    node.set_in_edge(&mock_edge);

    EXPECT_EQ(node.in_edge(), &mock_edge);



    node.set_id(42);

    EXPECT_EQ(node.id(), 42);



    node.set_dyndep_pending(true);

    EXPECT_TRUE(node.dyndep_pending());



    node.set_generated_by_dep_loader(false);

    EXPECT_FALSE(node.generated_by_dep_loader());

}



TEST_F(NodeTest_37, AddOutEdge_AddsToOutEdgesVector_37) {

    Node node("test_path", 0);

    Edge* mock_edge = new Edge();



    node.AddOutEdge(mock_edge);



    const std::vector<Edge*>& out_edges = node.out_edges();

    EXPECT_EQ(out_edges.size(), 1);

    EXPECT_EQ(out_edges[0], mock_edge);



    delete mock_edge;

}



TEST_F(NodeTest_37, AddValidationOutEdge_AddsToValidationOutEdgesVector_37) {

    Node node("test_path", 0);

    Edge* mock_edge = new Edge();



    node.AddValidationOutEdge(mock_edge);



    const std::vector<Edge*>& validation_out_edges = node.validation_out_edges();

    EXPECT_EQ(validation_out_edges.size(), 1);

    EXPECT_EQ(validation_out_edges[0], mock_edge);



    delete mock_edge;

}



TEST_F(NodeTest_37, Dump_DoesNotCrashOnEmptyNode_37) {

    Node node("test_path", 0);

    // Assuming Dump does not return anything and only prints to stdout/stderr

    node.Dump("");

}
