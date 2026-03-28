#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/ninja/src/graph.h"



using ::testing::_;

using ::testing::Return;



class NodeTest_39 : public ::testing::Test {

protected:

    NodeTest_39() : node("test_path", 0) {}



    Node node;

};



TEST_F(NodeTest_39, DirtyReturnsFalseInitially_39) {

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_39, SetDirtyTrueChangesState_39) {

    node.set_dirty(true);

    EXPECT_TRUE(node.dirty());

}



TEST_F(NodeTest_39, SetDirtyFalseChangesState_39) {

    node.set_dirty(false);

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_39, MarkDirtySetsDirtyToTrue_39) {

    node.MarkDirty();

    EXPECT_TRUE(node.dirty());

}



// Assuming DiskInterface and TimeStamp are defined elsewhere

class MockDiskInterface : public DiskInterface {

public:

    MOCK_METHOD2(Stat, bool(const std::string&, TimeStamp*));

};



TEST_F(NodeTest_39, StatIfNecessaryCallsStat_39) {

    MockDiskInterface mock_disk_interface;

    std::string err;



    EXPECT_CALL(mock_disk_interface, Stat("test_path", _))

        .WillOnce(Return(true));



    node.StatIfNecessary(&mock_disk_interface, &err);

}



TEST_F(NodeTest_39, ResetStateDoesNotAffectDirty_39) {

    node.set_dirty(true);

    node.ResetState();

    EXPECT_TRUE(node.dirty()); // Assuming ResetState does not reset dirty flag

}



TEST_F(NodeTest_39, MarkMissingDoesNotAffectDirty_39) {

    node.set_dirty(true);

    node.MarkMissing();

    EXPECT_TRUE(node.dirty()); // Assuming MarkMissing does not reset dirty flag

}
