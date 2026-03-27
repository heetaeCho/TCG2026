#include <gtest/gtest.h>

#include "db/snapshot.h"



using namespace leveldb;



class SnapshotListTest : public ::testing::Test {

protected:

    SnapshotList snapshot_list;

};



TEST_F(SnapshotListTest_290, EmptyInitially_290) {

    EXPECT_TRUE(snapshot_list.empty());

}



TEST_F(SnapshotListTest_290, NewSnapshotIncreasesCount_290) {

    snapshot_list.New(1);

    EXPECT_FALSE(snapshot_list.empty());

}



TEST_F(SnapshotListTest_290, NewestReturnsCorrectSnapshot_290) {

    SnapshotImpl* snap1 = snapshot_list.New(1);

    EXPECT_EQ(snap1, snapshot_list.newest());



    SnapshotImpl* snap2 = snapshot_list.New(2);

    EXPECT_EQ(snap2, snapshot_list.newest());

}



TEST_F(SnapshotListTest_290, OldestReturnsCorrectSnapshot_290) {

    SnapshotImpl* snap1 = snapshot_list.New(1);

    EXPECT_EQ(snap1, snapshot_list.oldest());



    SnapshotImpl* snap2 = snapshot_list.New(2);

    EXPECT_EQ(snap1, snapshot_list.oldest());

}



TEST_F(SnapshotListTest_290, DeleteSnapshotReducesCount_290) {

    SnapshotImpl* snap1 = snapshot_list.New(1);

    snapshot_list.Delete(snap1);

    EXPECT_TRUE(snapshot_list.empty());

}



TEST_F(SnapshotListTest_290, DeleteSnapshotMaintainsOrder_290) {

    SnapshotImpl* snap1 = snapshot_list.New(1);

    SnapshotImpl* snap2 = snapshot_list.New(2);



    snapshot_list.Delete(snap1);

    EXPECT_EQ(snap2, snapshot_list.newest());

    EXPECT_EQ(snap2, snapshot_list.oldest());



    snapshot_list.Delete(snap2);

    EXPECT_TRUE(snapshot_list.empty());

}



TEST_F(SnapshotListTest_290, SequenceNumberRetrievedCorrectly_290) {

    SnapshotImpl* snap1 = snapshot_list.New(42);

    EXPECT_EQ(42, snap1->sequence_number());



    SnapshotImpl* snap2 = snapshot_list.New(84);

    EXPECT_EQ(84, snap2->sequence_number());

}



TEST_F(SnapshotListTest_290, DeleteNonExistentSnapshotHasNoEffect_290) {

    SnapshotImpl dummy_snap(1);

    snapshot_list.Delete(&dummy_snap);

    EXPECT_TRUE(snapshot_list.empty());



    SnapshotImpl* snap = snapshot_list.New(1);

    snapshot_list.Delete(&dummy_snap);

    EXPECT_FALSE(snapshot_list.empty());

}
