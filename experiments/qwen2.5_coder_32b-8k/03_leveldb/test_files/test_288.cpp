#include <gtest/gtest.h>

#include "db/snapshot.h"



using namespace leveldb;



class SnapshotListTest_288 : public ::testing::Test {

protected:

    SnapshotList snapshot_list_;

};



TEST_F(SnapshotListTest_288, InitiallyEmpty_288) {

    EXPECT_TRUE(snapshot_list_.empty());

}



TEST_F(SnapshotListTest_288, NewSnapshotNotEmpty_288) {

    SequenceNumber seq_num = 1;

    snapshot_list_.New(seq_num);

    EXPECT_FALSE(snapshot_list_.empty());

}



TEST_F(SnapshotListTest_288, DeleteLastSnapshotEmptyAgain_288) {

    SequenceNumber seq_num = 1;

    SnapshotImpl* snapshot = snapshot_list_.New(seq_num);

    snapshot_list_.Delete(snapshot);

    EXPECT_TRUE(snapshot_list_.empty());

}



TEST_F(SnapshotListTest_288, OldestReturnsCorrectSnapshot_288) {

    SequenceNumber seq_num1 = 1;

    SequenceNumber seq_num2 = 2;

    SnapshotImpl* snapshot1 = snapshot_list_.New(seq_num1);

    SnapshotImpl* snapshot2 = snapshot_list_.New(seq_num2);

    EXPECT_EQ(snapshot1, snapshot_list_.oldest());

}



TEST_F(SnapshotListTest_288, NewestReturnsCorrectSnapshot_288) {

    SequenceNumber seq_num1 = 1;

    SequenceNumber seq_num2 = 2;

    SnapshotImpl* snapshot1 = snapshot_list_.New(seq_num1);

    SnapshotImpl* snapshot2 = snapshot_list_.New(seq_num2);

    EXPECT_EQ(snapshot2, snapshot_list_.newest());

}



TEST_F(SnapshotListTest_288, OldestAndNewestSameForSingleSnapshot_288) {

    SequenceNumber seq_num = 1;

    SnapshotImpl* snapshot = snapshot_list_.New(seq_num);

    EXPECT_EQ(snapshot, snapshot_list_.oldest());

    EXPECT_EQ(snapshot, snapshot_list_.newest());

}



TEST_F(SnapshotListTest_288, DeleteOldestSnapshotCorrectly_288) {

    SequenceNumber seq_num1 = 1;

    SequenceNumber seq_num2 = 2;

    SnapshotImpl* snapshot1 = snapshot_list_.New(seq_num1);

    SnapshotImpl* snapshot2 = snapshot_list_.New(seq_num2);

    snapshot_list_.Delete(snapshot1);

    EXPECT_EQ(snapshot2, snapshot_list_.oldest());

}



TEST_F(SnapshotListTest_288, DeleteNewestSnapshotCorrectly_288) {

    SequenceNumber seq_num1 = 1;

    SequenceNumber seq_num2 = 2;

    SnapshotImpl* snapshot1 = snapshot_list_.New(seq_num1);

    SnapshotImpl* snapshot2 = snapshot_list_.New(seq_num2);

    snapshot_list_.Delete(snapshot2);

    EXPECT_EQ(snapshot1, snapshot_list_.newest());

}
