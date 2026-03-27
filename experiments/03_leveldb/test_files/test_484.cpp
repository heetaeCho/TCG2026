#include <gtest/gtest.h>

#include "db/snapshot.h"



using namespace leveldb;



class SnapshotListTest_484 : public ::testing::Test {

protected:

    SnapshotList* snapshot_list_;



    void SetUp() override {

        snapshot_list_ = new SnapshotList();

    }



    void TearDown() override {

        delete snapshot_list_;

    }

};



TEST_F(SnapshotListTest_484, InitiallyEmpty_484) {

    EXPECT_TRUE(snapshot_list_->empty());

}



TEST_F(SnapshotListTest_484, NewSnapshotMakesItNotEmpty_484) {

    snapshot_list_->New(1);

    EXPECT_FALSE(snapshot_list_->empty());

}



TEST_F(SnapshotListTest_484, OldestAndNewestSameForSingleSnapshot_484) {

    SequenceNumber seq_num = 1;

    SnapshotImpl* snapshot = snapshot_list_->New(seq_num);

    EXPECT_EQ(snapshot, snapshot_list_->oldest());

    EXPECT_EQ(snapshot, snapshot_list_->newest());

}



TEST_F(SnapshotListTest_484, OldestAndNewestCorrectForMultipleSnapshots_484) {

    SequenceNumber seq_num1 = 1;

    SequenceNumber seq_num2 = 2;

    SnapshotImpl* snapshot1 = snapshot_list_->New(seq_num1);

    SnapshotImpl* snapshot2 = snapshot_list_->New(seq_num2);



    EXPECT_EQ(snapshot1, snapshot_list_->oldest());

    EXPECT_EQ(snapshot2, snapshot_list_->newest());

}



TEST_F(SnapshotListTest_484, DeleteSnapshotMakesItEmptyAgain_484) {

    SequenceNumber seq_num = 1;

    SnapshotImpl* snapshot = snapshot_list_->New(seq_num);

    snapshot_list_->Delete(snapshot);

    EXPECT_TRUE(snapshot_list_->empty());

}



TEST_F(SnapshotListTest_484, DeleteOldestSnapshotCorrectlyUpdatesOldest_484) {

    SequenceNumber seq_num1 = 1;

    SequenceNumber seq_num2 = 2;

    SnapshotImpl* snapshot1 = snapshot_list_->New(seq_num1);

    SnapshotImpl* snapshot2 = snapshot_list_->New(seq_num2);



    snapshot_list_->Delete(snapshot1);

    EXPECT_EQ(snapshot2, snapshot_list_->oldest());

}



TEST_F(SnapshotListTest_484, DeleteNewestSnapshotCorrectlyUpdatesNewest_484) {

    SequenceNumber seq_num1 = 1;

    SequenceNumber seq_num2 = 2;

    SnapshotImpl* snapshot1 = snapshot_list_->New(seq_num1);

    SnapshotImpl* snapshot2 = snapshot_list_->New(seq_num2);



    snapshot_list_->Delete(snapshot2);

    EXPECT_EQ(snapshot1, snapshot_list_->newest());

}



TEST_F(SnapshotListTest_484, SequenceNumberCorrectlyRetrieved_484) {

    SequenceNumber seq_num = 1;

    SnapshotImpl* snapshot = new SnapshotImpl(seq_num);

    EXPECT_EQ(seq_num, snapshot->sequence_number());

    delete snapshot;

}
