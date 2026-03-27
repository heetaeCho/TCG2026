#include <gtest/gtest.h>

#include "db/snapshot.h"



using namespace leveldb;



class SnapshotListTest_292 : public ::testing::Test {

protected:

    SnapshotList snapshot_list;

};



TEST_F(SnapshotListTest_292, NewSnapshotIncreasesCount_292) {

    size_t initial_count = snapshot_list.empty() ? 0 : 1;

    SnapshotImpl* snap = snapshot_list.New(1);

    EXPECT_FALSE(snapshot_list.empty());

    delete snap;

}



TEST_F(SnapshotListTest_292, DeleteSnapshotDecreasesCount_292) {

    SnapshotImpl* snap = snapshot_list.New(1);

    snapshot_list.Delete(snap);

    EXPECT_TRUE(snapshot_list.empty());

}



TEST_F(SnapshotListTest_292, NewMultipleSnapshotsOrderCorrect_292) {

    SnapshotImpl* snap1 = snapshot_list.New(1);

    SnapshotImpl* snap2 = snapshot_list.New(2);



    EXPECT_EQ(snapshot_list.oldest(), snap1);

    EXPECT_EQ(snapshot_list.newest(), snap2);



    delete snap1;

    delete snap2;

}



TEST_F(SnapshotListTest_292, DeleteOldestSnapshot_292) {

    SnapshotImpl* snap1 = snapshot_list.New(1);

    SnapshotImpl* snap2 = snapshot_list.New(2);



    snapshot_list.Delete(snap1);

    EXPECT_EQ(snapshot_list.oldest(), snap2);

    EXPECT_EQ(snapshot_list.newest(), snap2);



    delete snap2;

}



TEST_F(SnapshotListTest_292, DeleteNewestSnapshot_292) {

    SnapshotImpl* snap1 = snapshot_list.New(1);

    SnapshotImpl* snap2 = snapshot_list.New(2);



    snapshot_list.Delete(snap2);

    EXPECT_EQ(snapshot_list.oldest(), snap1);

    EXPECT_EQ(snapshot_list.newest(), snap1);



    delete snap1;

}



TEST_F(SnapshotListTest_292, DeleteMiddleSnapshot_292) {

    SnapshotImpl* snap1 = snapshot_list.New(1);

    SnapshotImpl* snap2 = snapshot_list.New(2);

    SnapshotImpl* snap3 = snapshot_list.New(3);



    snapshot_list.Delete(snap2);

    EXPECT_EQ(snapshot_list.oldest(), snap1);

    EXPECT_EQ(snapshot_list.newest(), snap3);



    delete snap1;

    delete snap3;

}



TEST_F(SnapshotListTest_292, DeleteAllSnapshots_292) {

    SnapshotImpl* snap1 = snapshot_list.New(1);

    SnapshotImpl* snap2 = snapshot_list.New(2);

    SnapshotImpl* snap3 = snapshot_list.New(3);



    snapshot_list.Delete(snap1);

    snapshot_list.Delete(snap2);

    snapshot_list.Delete(snap3);

    EXPECT_TRUE(snapshot_list.empty());

}
