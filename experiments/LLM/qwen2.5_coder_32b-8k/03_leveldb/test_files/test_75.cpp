#include <gtest/gtest.h>

#include "db/version_set.h"



using namespace leveldb;



class VersionSetTest_75 : public ::testing::Test {

protected:

    Options options;

    TableCache table_cache;

    InternalKeyComparator icmp;

    std::string dbname = "test_db";

    Env* env = nullptr; // Assuming Env is not used in the constructor for simplicity



    VersionSet* version_set;



    void SetUp() override {

        version_set = new VersionSet(dbname, &options, &table_cache, &icmp);

    }



    void TearDown() override {

        delete version_set;

    }

};



TEST_F(VersionSetTest_75, SetLastSequence_NormalOperation_75) {

    uint64_t sequence_number = 100;

    version_set->SetLastSequence(sequence_number);

    EXPECT_EQ(version_set->LastSequence(), sequence_number);

}



TEST_F(VersionSetTest_75, SetLastSequence_BoundaryCondition_Zero_75) {

    uint64_t sequence_number = 0;

    version_set->SetLastSequence(sequence_number);

    EXPECT_EQ(version_set->LastSequence(), sequence_number);

}



TEST_F(VersionSetTest_75, SetLastSequence_ExceptionalCase_SequenceLessThanCurrent_75) {

    uint64_t initial_sequence = 100;

    version_set->SetLastSequence(initial_sequence);

    EXPECT_DEATH(version_set->SetLastSequence(initial_sequence - 1), "assert");

}



TEST_F(VersionSetTest_75, LastSequence_DefaultValue_75) {

    EXPECT_EQ(version_set->LastSequence(), 0U);

}
