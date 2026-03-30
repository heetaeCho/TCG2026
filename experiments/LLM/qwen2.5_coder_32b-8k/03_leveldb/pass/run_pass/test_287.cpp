#include <gtest/gtest.h>

#include "db/snapshot.h"



using namespace leveldb;



class SnapshotImplTest_287 : public ::testing::Test {

protected:

    SequenceNumber test_sequence_number = 42;

    std::unique_ptr<SnapshotImpl> snapshot;



    void SetUp() override {

        snapshot = std::make_unique<SnapshotImpl>(test_sequence_number);

    }

};



TEST_F(SnapshotImplTest_287, ConstructorSetsSequenceNumber_287) {

    EXPECT_EQ(snapshot->sequence_number(), test_sequence_number);

}



TEST_F(SnapshotImplTest_287, SequenceNumberIsConst_287) {

    const SequenceNumber expected_sequence_number = snapshot->sequence_number();

    EXPECT_EQ(expected_sequence_number, test_sequence_number);

}
