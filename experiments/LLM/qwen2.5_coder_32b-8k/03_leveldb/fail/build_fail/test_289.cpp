#include <gtest/gtest.h>

#include "db/snapshot.h"



using namespace leveldb;



class SnapshotListTest : public ::testing::Test {

protected:

    SnapshotList snapshot_list_;

};



TEST_F(SnapshotListTest_289, EmptyInitially_289) {

    EXPECT_TRUE(snapshot_list_.empty());

}



TEST_F(SnapshotListTest_289, NewSnapshotIncreasesCount_289) {

    snapshot_list_.New(10);

    EXPECT_FALSE(snapshot_list_.empty());

}



TEST_F(SnapshotListTest_289, OldestReturnsCorrectSnapshot_289) {

    SnapshotImpl* snap1 = snapshot_list_.New(10);

    SnapshotImpl* snap2 = snapshot_list_.New(20);

    EXPECT_EQ(snap1, snapshot_list_.oldest());

}



TEST_F(SnapshotListTest_289, NewestReturnsCorrectSnapshot_289) {

    SnapshotImpl* snap1 = snapshot_list_.New(10);

    SnapshotImpl* snap2 = snapshot_list_.New(20);

    EXPECT_EQ(snap2, snapshot_list_.newest());

}



TEST_F(SnapshotListTest_289, DeleteMakesListEmpty_289) {

    SnapshotImpl* snap = snapshot_list_.New(10);

    snapshot_list_.Delete(snap);

    EXPECT_TRUE(snapshot_list_.empty());

}



TEST_F(SnapshotListTest_289, DeleteRemovesCorrectSnapshot_289) {

    SnapshotImpl* snap1 = snapshot_list_.New(10);

    SnapshotImpl* snap2 = snapshot_list_.New(20);

    snapshot_list_.Delete(snap1);

    EXPECT_EQ(snap2, snapshot_list_.oldest());

}



TEST_F(SnapshotListTest_289, DeleteNonExistentSnapshotDoesNothing_289) {

    SnapshotImpl* snap1 = snapshot_list_.New(10);

    SnapshotImpl* snap2 = new SnapshotImpl(20); // Manually created snapshot not in list

    EXPECT_DEATH(snapshot_list_.Delete(snap2), ".*");

    delete snap2;

}



TEST_F(SnapshotListTest_289, SequenceNumberIsCorrect_289) {

    SnapshotImpl* snap = snapshot_list_.New(10);

    EXPECT_EQ(10, snap->sequence_number());

}
