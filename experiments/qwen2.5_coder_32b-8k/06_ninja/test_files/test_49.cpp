#include <gtest/gtest.h>

#include "graph.h"



class NodeTest_49 : public ::testing::Test {

protected:

    Node node_;



    NodeTest_49() : node_("test_path", 123) {}

};



TEST_F(NodeTest_49, SetIdAndGetId_NormalOperation_49) {

    int new_id = 42;

    node_.set_id(new_id);

    EXPECT_EQ(node_.id(), new_id);

}



TEST_F(NodeTest_49, GetPath_ReturnsCorrectPath_49) {

    EXPECT_EQ(node_.path(), "test_path");

}



TEST_F(NodeTest_49, GetSlashBits_ReturnsCorrectSlashBits_49) {

    EXPECT_EQ(node_.slash_bits(), 123);

}



TEST_F(NodeTest_49, DefaultIdIsNegativeOne_49) {

    Node default_node("default_path", 0);

    EXPECT_EQ(default_node.id(), -1);

}



// Assuming TimeStamp and DiskInterface are defined elsewhere

class MockDiskInterface : public DiskInterface {

public:

    MOCK_METHOD(bool, Stat, (const std::string&, TimeStamp*, std::string*), (override));

};



TEST_F(NodeTest_49, Stat_CallsDiskInterfaceStat_49) {

    MockDiskInterface mock_disk_interface;

    std::string error;



    EXPECT_CALL(mock_disk_interface, Stat("test_path", testing::_, &error)).Times(1);



    node_.Stat(&mock_disk_interface, &error);

}



TEST_F(NodeTest_49, UpdatePhonyMtime_SetsCorrectMtime_49) {

    TimeStamp new_mtime = 12345;

    node_.UpdatePhonyMtime(new_mtime);

    EXPECT_EQ(node_.mtime(), new_mtime);

}



TEST_F(NodeTest_49, ResetState_ClearsFlagsAndInEdge_49) {

    node_.set_dirty(true);

    node_.set_dyndep_pending(true);

    node_.set_in_edge(reinterpret_cast<Edge*>(1));

    node_.ResetState();



    EXPECT_FALSE(node_.dirty());

    EXPECT_FALSE(node_.dyndep_pending());

    EXPECT_EQ(node_.in_edge(), nullptr);

}



TEST_F(NodeTest_49, MarkMissing_SetsExistsToFalseAndStatusKnownToTrue_49) {

    node_.MarkMissing();

    EXPECT_FALSE(node_.exists());

    EXPECT_TRUE(node_.status_known());

}



TEST_F(NodeTest_49, DefaultExistenceStatusIsUnknown_49) {

    Node default_node("default_path", 0);

    EXPECT_EQ(default_node.exists(), false);

    EXPECT_EQ(default_node.status_known(), false);

}
