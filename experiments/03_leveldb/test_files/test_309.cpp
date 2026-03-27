#include "gtest/gtest.h"

#include "db/db_impl.h"



using namespace leveldb;



class DBImplTest_309 : public ::testing::Test {

protected:

    Options options;

    std::string dbname = "/tmp/testdb";

    DBImpl* db_impl;



    void SetUp() override {

        options.env = Env::Default();

        db_impl = new DBImpl(options, dbname);

    }



    void TearDown() override {

        delete db_impl;

        DestroyDB(dbname, options);

    }

};



TEST_F(DBImplTest_309, GetSnapshot_ReturnsNonNullPointer_309) {

    const Snapshot* snapshot = db_impl->GetSnapshot();

    EXPECT_NE(snapshot, nullptr);

}



TEST_F(DBImplTest_309, GetSnapshot_ConsistentSequenceNumber_309) {

    uint64_t initial_sequence = db_impl->versions_->LastSequence();

    const Snapshot* snapshot1 = db_impl->GetSnapshot();

    uint64_t sequence_after_snapshot1 = db_impl->versions_->LastSequence();



    EXPECT_EQ(initial_sequence, sequence_after_snapshot1);



    // Simulate some write operations that would increase the sequence number

    WriteOptions wo;

    Status status = db_impl->Put(wo, Slice("key"), Slice("value"));

    ASSERT_TRUE(status.ok());



    uint64_t new_sequence = db_impl->versions_->LastSequence();

    const Snapshot* snapshot2 = db_impl->GetSnapshot();



    EXPECT_NE(sequence_after_snapshot1, new_sequence);

    EXPECT_EQ(new_sequence, db_impl->versions_->LastSequence());

    EXPECT_EQ(snapshot2->sequence_number(), new_sequence);

}



TEST_F(DBImplTest_309, ReleaseSnapshot_DoesNotCrash_309) {

    const Snapshot* snapshot = db_impl->GetSnapshot();

    EXPECT_NO_THROW(db_impl->ReleaseSnapshot(snapshot));

}



TEST_F(DBImplTest_309, GetSnapshot_MultipleSnapshots_309) {

    const Snapshot* snapshot1 = db_impl->GetSnapshot();

    uint64_t seq1 = snapshot1->sequence_number();



    WriteOptions wo;

    Status status = db_impl->Put(wo, Slice("key"), Slice("value"));

    ASSERT_TRUE(status.ok());



    const Snapshot* snapshot2 = db_impl->GetSnapshot();

    uint64_t seq2 = snapshot2->sequence_number();



    EXPECT_NE(seq1, seq2);



    db_impl->ReleaseSnapshot(snapshot1);

    db_impl->ReleaseSnapshot(snapshot2);

}
