#include <gtest/gtest.h>

#include "db/snapshot.h"



using namespace leveldb;



class SnapshotListTest : public ::testing::Test {

protected:

    SnapshotList snapshot_list_;

};



TEST_F(SnapshotListTest_291, NewSnapshotIncreasesCount_291) {

    EXPECT_TRUE(snapshot_list_.empty());

    SnapshotImpl* snapshot = snapshot_list_.New(1);

    EXPECT_FALSE(snapshot_list_.empty());

    delete snapshot;

}



TEST_F(SnapshotListTest_291, NewSnapshotWithValidSequenceNumber_291) {

    SnapshotImpl* snapshot1 = snapshot_list_.New(1);

    SnapshotImpl* snapshot2 = snapshot_list_.New(2);

    EXPECT_EQ(snapshot1->sequence_number(), 1);

    EXPECT_EQ(snapshot2->sequence_number(), 2);

    delete snapshot1;

    delete snapshot2;

}



TEST_F(SnapshotListTest_291, NewSnapshotMaintainsOrder_291) {

    SnapshotImpl* snapshot1 = snapshot_list_.New(1);

    SnapshotImpl* snapshot2 = snapshot_list_.New(2);

    EXPECT_EQ(snapshot_list_.oldest(), snapshot1);

    EXPECT_EQ(snapshot_list_.newest(), snapshot2);

    delete snapshot1;

    delete snapshot2;

}



TEST_F(SnapshotListTest_291, NewSnapshotWithSameSequenceNumberThrows_291) {

    SnapshotImpl* snapshot1 = snapshot_list_.New(1);

    EXPECT_THROW(snapshot_list_.New(1), std::exception);

    delete snapshot1;

}



TEST_F(SnapshotListTest_291, DeleteSnapshotReducesCount_291) {

    SnapshotImpl* snapshot = snapshot_list_.New(1);

    EXPECT_FALSE(snapshot_list_.empty());

    snapshot_list_.Delete(snapshot);

    EXPECT_TRUE(snapshot_list_.empty());

}



TEST_F(SnapshotListTest_291, DeleteSnapshotMaintainsOrder_291) {

    SnapshotImpl* snapshot1 = snapshot_list_.New(1);

    SnapshotImpl* snapshot2 = snapshot_list_.New(2);

    SnapshotImpl* snapshot3 = snapshot_list_.New(3);



    snapshot_list_.Delete(snapshot2);

    EXPECT_EQ(snapshot_list_.oldest(), snapshot1);

    EXPECT_EQ(snapshot_list_.newest(), snapshot3);



    delete snapshot1;

    delete snapshot3;

}



TEST_F(SnapshotListTest_291, DeleteNonExistentSnapshotDoesNothing_291) {

    SnapshotImpl* snapshot = new SnapshotImpl(1);

    EXPECT_TRUE(snapshot_list_.empty());

    snapshot_list_.Delete(snapshot);

    EXPECT_TRUE(snapshot_list_.empty());

    delete snapshot;

}
